/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#define pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#include <linux/module.h>
#include <linux/proc_fs.h>
#include "msm_led_flash.h"

#define FLASH_NAME "camera-led-flash"

/*#define CONFIG_MSMB_CAMERA_DEBUG*/
#undef CDBG
#ifdef CONFIG_MSMB_CAMERA_DEBUG
#define CDBG(fmt, args...) pr_err(fmt, ##args)
#else
#define CDBG(fmt, args...) do { } while (0)
#endif

extern int32_t msm_led_torch_create_classdev(
				struct platform_device *pdev, void *data);

static enum flash_type flashtype;
static struct msm_led_flash_ctrl_t fctrl;

static int32_t torch_status = 0;

static int32_t msm_led_trigger_get_subdev_id(struct msm_led_flash_ctrl_t *fctrl,
	void *arg)
{
	uint32_t *subdev_id = (uint32_t *)arg;
	if (!subdev_id) {
		pr_err("%s:%d failed\n", __func__, __LINE__);
		return -EINVAL;
	}
	*subdev_id = fctrl->pdev->id;
	CDBG("%s:%d subdev_id %d\n", __func__, __LINE__, *subdev_id);
	return 0;
}
ssize_t proc_flash_led_write (struct file *file, const char __user *buf, size_t nbytes, loff_t *ppos)
{
    char string[nbytes];

	uint32_t i = 0;
    sscanf(buf, "%s", string);
    if (!strcmp((const char *)string, (const char *)"on"))
    {
		CDBG("proc_flash_led_write on called\n");
		for (i = 0; i < fctrl.torch_num_sources; i++)
			if (fctrl.torch_trigger[i])
				led_trigger_event(fctrl.torch_trigger[i], fctrl.torch_op_current[i]);
		torch_status = 1;
    }
    else if (!strcmp((const char *)string, (const char *)"off"))
    {
		CDBG("proc_flash_led_write off called\n");
		for (i = 0; i < fctrl.flash_num_sources; i++)
			if (fctrl.flash_trigger[i])
				led_trigger_event(fctrl.flash_trigger[i], 0);
		for (i = 0; i < fctrl.torch_num_sources; i++)
			if (fctrl.torch_trigger[i])
				led_trigger_event(fctrl.torch_trigger[i], 0);
		torch_status = 0;
    }
    else if (!strcmp((const char *)string, (const char *)"led1_on"))
    {
		CDBG("proc_flash_led_write led1_on called\n");
		if (fctrl.torch_trigger[0])
			led_trigger_event(fctrl.torch_trigger[0], fctrl.torch_op_current[0]);
		torch_status = 1;
    }
    else if (!strcmp((const char *)string, (const char *)"led1_off"))
    {
		CDBG("proc_flash_led_write led1_on called\n");
		if (fctrl.torch_trigger[0])
			led_trigger_event(fctrl.torch_trigger[0],0);
		torch_status = 0;
    }
    else if (!strcmp((const char *)string, (const char *)"led2_on"))
    {
		CDBG("proc_flash_led_write led2_on called\n");
		if (fctrl.torch_trigger[1])
			led_trigger_event(fctrl.torch_trigger[1], fctrl.torch_op_current[1]);
		torch_status = 1;
    }
    else if (!strcmp((const char *)string, (const char *)"led2_off"))
    {
		CDBG("proc_flash_led_write led2_off called\n");
		if (fctrl.torch_trigger[0])
			led_trigger_event(fctrl.torch_trigger[1],0);
		torch_status = 0;
    }
    return nbytes;
}
ssize_t proc_flash_led_read (struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
{
	CDBG("proc_flash_led_read buf:%p,nbytes:%d\n",buf,nbytes);
	if(buf != NULL && nbytes > 2){
		if(torch_status)
			strncpy(buf,"on",2);
		else
			strncpy(buf,"off",3);
	}
    return nbytes;
}
EXPORT_SYMBOL(proc_flash_led_write);

static int32_t msm_led_trigger_config(struct msm_led_flash_ctrl_t *fctrl,
	void *data)
{
	int rc = 0;
	struct msm_camera_led_cfg_t *cfg = (struct msm_camera_led_cfg_t *)data;
	uint32_t i;
	uint32_t curr_l, max_curr_l;
	CDBG("called led_state %d\n", cfg->cfgtype);

	if (!fctrl) {
		pr_err("failed\n");
		return -EINVAL;
	}

	switch (cfg->cfgtype) {
	case MSM_CAMERA_LED_OFF:
		/* Flash off */
		for (i = 0; i < fctrl->flash_num_sources; i++)
			if (fctrl->flash_trigger[i])
				led_trigger_event(fctrl->flash_trigger[i], 0);
		/* Torch off */
		for (i = 0; i < fctrl->torch_num_sources; i++)
			if (fctrl->torch_trigger[i])
				led_trigger_event(fctrl->torch_trigger[i], 0);
		torch_status = 0;
		break;

	case MSM_CAMERA_LED_LOW:
		for (i = 0; i < fctrl->torch_num_sources; i++)
			if (fctrl->torch_trigger[i]) {
				max_curr_l = fctrl->torch_max_current[i];
				if (cfg->torch_current[i] >= 0 &&
					cfg->torch_current[i] < max_curr_l) {
					curr_l = cfg->torch_current[i];
				} else {
					curr_l = fctrl->torch_op_current[i];
					pr_debug("LED torch %d clamped %d\n",
						i, curr_l);
				}
				led_trigger_event(fctrl->torch_trigger[i],
						curr_l);
			}
		torch_status = 1;
		break;

	case MSM_CAMERA_LED_HIGH:
		/* Torch off */
		for (i = 0; i < fctrl->torch_num_sources; i++)
			if (fctrl->torch_trigger[i])
				led_trigger_event(fctrl->torch_trigger[i], 0);

		for (i = 0; i < fctrl->flash_num_sources; i++)
			if (fctrl->flash_trigger[i]) {
				max_curr_l = fctrl->flash_max_current[i];
				if (cfg->flash_current[i] >= 0 &&
					cfg->flash_current[i] < max_curr_l) {
					curr_l = cfg->flash_current[i];
				} else {
					curr_l = fctrl->flash_op_current[i];
					pr_debug("LED flash %d clamped %d\n",
						i, curr_l);
				}
				led_trigger_event(fctrl->flash_trigger[i],
					curr_l);
			}
		break;

	case MSM_CAMERA_LED_INIT:
	case MSM_CAMERA_LED_RELEASE:
		/* Flash off */
		for (i = 0; i < fctrl->flash_num_sources; i++)
			if (fctrl->flash_trigger[i])
				led_trigger_event(fctrl->flash_trigger[i], 0);
		/* Torch off */
		for (i = 0; i < fctrl->torch_num_sources; i++)
			if (fctrl->torch_trigger[i])
				led_trigger_event(fctrl->torch_trigger[i], 0);

		torch_status = 0;
		break;

	default:
		rc = -EFAULT;
		break;
	}
	CDBG("flash_set_led_state: return %d\n", rc);
	return rc;
}

static const struct of_device_id msm_led_trigger_dt_match[] = {
	{.compatible = "qcom,camera-led-flash"},
	{}
};

MODULE_DEVICE_TABLE(of, msm_led_trigger_dt_match);

static struct platform_driver msm_led_trigger_driver = {
	.driver = {
		.name = FLASH_NAME,
		.owner = THIS_MODULE,
		.of_match_table = msm_led_trigger_dt_match,
	},
};

const struct file_operations proc_flash_led_operations = {
	.owner	= THIS_MODULE,
	.write	= proc_flash_led_write,
	.read	= proc_flash_led_read,
};
static int32_t msm_led_trigger_probe(struct platform_device *pdev)
{
	int32_t rc = 0, rc_1 = 0, i = 0;
	struct device_node *of_node = pdev->dev.of_node;
	struct device_node *flash_src_node = NULL;
	uint32_t count = 0;
	struct led_trigger *temp = NULL;
  struct proc_dir_entry * rcdir;
	CDBG("called\n");
	//return -EINVAL;
	rcdir = proc_create_data("CTP_FLASH_CTRL", S_IFREG | S_IWUGO | S_IWUSR |S_IRUGO, NULL, &proc_flash_led_operations, NULL);
        rcdir = proc_create_data("CTP_TORCH_CTRL", S_IFREG | S_IWUGO | S_IWUSR |S_IRUGO, NULL, &proc_flash_led_operations, NULL);
	if(rcdir==NULL)
	{
		CDBG("proc_create_data fail\n");
	}
	if (!of_node) {
		pr_err("of_node NULL\n");
		return -EINVAL;
	}

	fctrl.pdev = pdev;
	fctrl.flash_num_sources = 0;
	fctrl.torch_num_sources = 0;

	rc = of_property_read_u32(of_node, "cell-index", &pdev->id);
	if (rc < 0) {
		pr_err("failed\n");
		return -EINVAL;
	}
	CDBG("pdev id %d\n", pdev->id);

	rc = of_property_read_u32(of_node,
			"qcom,flash-type", &flashtype);
	if (rc < 0) {
		pr_err("flash-type: read failed\n");
		return -EINVAL;
	}

	/* Flash source */
	if (of_get_property(of_node, "qcom,flash-source", &count)) {
		count /= sizeof(uint32_t);
		CDBG("qcom,flash-source count %d\n", count);
		if (count > MAX_LED_TRIGGERS) {
			pr_err("invalid count qcom,flash-source %d\n", count);
			return -EINVAL;
		}
		fctrl.flash_num_sources = count;
		for (i = 0; i < fctrl.flash_num_sources; i++) {
			flash_src_node = of_parse_phandle(of_node,
				"qcom,flash-source", i);
			if (!flash_src_node) {
				pr_err("flash_src_node %d NULL\n", i);
				continue;
			}

			rc = of_property_read_string(flash_src_node,
				"linux,default-trigger",
				&fctrl.flash_trigger_name[i]);
			if (rc < 0) {
				pr_err("default-trigger: read failed\n");
				of_node_put(flash_src_node);
				continue;
			}

			CDBG("default trigger %s\n",
				fctrl.flash_trigger_name[i]);

			if (flashtype == GPIO_FLASH) {
				/* use fake current */
				fctrl.flash_op_current[i] = LED_FULL;
			} else {
				rc = of_property_read_u32(flash_src_node,
					"qcom,current",
					&fctrl.flash_op_current[i]);
				rc_1 = of_property_read_u32(flash_src_node,
					"qcom,max-current",
					&fctrl.flash_max_current[i]);
				if ((rc < 0) || (rc_1 < 0)) {
					pr_err("current: read failed\n");
					of_node_put(flash_src_node);
					continue;
				}
			}

			of_node_put(flash_src_node);

			CDBG("max_current[%d] %d\n",
				i, fctrl.flash_op_current[i]);

			led_trigger_register_simple(fctrl.flash_trigger_name[i],
				&fctrl.flash_trigger[i]);

			if (flashtype == GPIO_FLASH)
				if (fctrl.flash_trigger[i])
					temp = fctrl.flash_trigger[i];
		}
	}
	/* Torch source */
	if (of_get_property(of_node, "qcom,torch-source", &count)) {
		count /= sizeof(uint32_t);
		CDBG("qcom,torch-source count %d\n", count);
		if (count > MAX_LED_TRIGGERS) {
			pr_err("invalid count qcom,torch-source %d\n", count);
			return -EINVAL;
		}
		fctrl.torch_num_sources = count;

		for (i = 0; i < fctrl.torch_num_sources; i++) {
			flash_src_node = of_parse_phandle(of_node,
				"qcom,torch-source", i);
			if (!flash_src_node) {
				pr_err("torch_src_node %d NULL\n", i);
				continue;
			}
			rc = of_property_read_string(flash_src_node,
				"linux,default-trigger",
				&fctrl.torch_trigger_name[i]);
			if (rc < 0) {
				pr_err("default-trigger: read failed\n");
				of_node_put(flash_src_node);
				continue;
			}
			CDBG("default trigger %s\n",
			fctrl.torch_trigger_name[i]);

			if (flashtype == GPIO_FLASH) {
			/* use fake current */
			fctrl.torch_op_current[i] = LED_HALF;
			} else {
				rc = of_property_read_u32(flash_src_node,
					"qcom,current",
					&fctrl.torch_op_current[i]);
				rc_1 = of_property_read_u32(flash_src_node,
					"qcom,max-current",
					&fctrl.torch_max_current[i]);
				if ((rc < 0) || (rc_1 < 0)) {
					pr_err("current: read failed\n");
					of_node_put(flash_src_node);
					continue;
				}
			}
			of_node_put(flash_src_node);

			CDBG("torch max_current[%d] %d\n",
				i, fctrl.torch_op_current[i]);

			led_trigger_register_simple(fctrl.torch_trigger_name[i],
				&fctrl.torch_trigger[i]);

			if (flashtype == GPIO_FLASH)
				if (temp && !fctrl.torch_trigger[i])
					fctrl.torch_trigger[i] = temp;
		}
	}

	rc = msm_led_flash_create_v4lsubdev(pdev, &fctrl);
	if (!rc)
		msm_led_torch_create_classdev(pdev, &fctrl);

	return rc;
}

static int __init msm_led_trigger_add_driver(void)
{
	CDBG("called\n");
	return platform_driver_probe(&msm_led_trigger_driver,
		msm_led_trigger_probe);
}

static struct msm_flash_fn_t msm_led_trigger_func_tbl = {
	.flash_get_subdev_id = msm_led_trigger_get_subdev_id,
	.flash_led_config = msm_led_trigger_config,
};

static struct msm_led_flash_ctrl_t fctrl = {
	.func_tbl = &msm_led_trigger_func_tbl,
};

module_init(msm_led_trigger_add_driver);
MODULE_DESCRIPTION("LED TRIGGER FLASH");
MODULE_LICENSE("GPL v2");
