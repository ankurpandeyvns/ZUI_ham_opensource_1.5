
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
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/leds.h>
#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>
#include <linux/spmi.h>
#include <linux/qpnp/pwm.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>
#include <linux/string.h>

#define WLED_MOD_EN_REG(base, n)	(base + 0x60 + n*0x10)
#define WLED_IDAC_DLY_REG(base, n)	(WLED_MOD_EN_REG(base, n) + 0x01)
#define WLED_FULL_SCALE_REG(base, n)	(WLED_IDAC_DLY_REG(base, n) + 0x01)
#define WLED_MOD_SRC_SEL_REG(base, n)	(WLED_FULL_SCALE_REG(base, n) + 0x01)

#define SHENQI_RGB 1
#define SHENQI_KPD 1
#if SHENQI_KPD
        struct pwm_device       *pwm_dev_button1;
        struct pwm_device       *pwm_dev_button2;
int qpnp_kpdbl_enable(bool onoff,int brightness);
#endif

/* wled control registers */
#define WLED_BRIGHTNESS_CNTL_LSB(base, n)	(base + 0x40 + 2*n)
#define WLED_BRIGHTNESS_CNTL_MSB(base, n)	(base + 0x41 + 2*n)
#define WLED_MOD_CTRL_REG(base)			(base + 0x46)
#define WLED_SYNC_REG(base)			(base + 0x47)
#define WLED_FDBCK_CTRL_REG(base)		(base + 0x48)
#define WLED_SWITCHING_FREQ_REG(base)		(base + 0x4C)
#define WLED_OVP_CFG_REG(base)			(base + 0x4D)
#define WLED_BOOST_LIMIT_REG(base)		(base + 0x4E)
#define WLED_CURR_SINK_REG(base)		(base + 0x4F)
#define WLED_HIGH_POLE_CAP_REG(base)		(base + 0x58)
#define WLED_CURR_SINK_MASK		0xE0
#define WLED_CURR_SINK_SHFT		0x05
#define WLED_DISABLE_ALL_SINKS		0x00
#define WLED_SWITCH_FREQ_MASK		0x0F
#define WLED_OVP_VAL_MASK		0x03
#define WLED_OVP_VAL_BIT_SHFT		0x00
#define WLED_BOOST_LIMIT_MASK		0x07
#define WLED_BOOST_LIMIT_BIT_SHFT	0x00
#define WLED_BOOST_ON			0x80
#define WLED_BOOST_OFF			0x00
#define WLED_EN_MASK			0x80
#define WLED_NO_MASK			0x00
#define WLED_CP_SELECT_MAX		0x03
#define WLED_CP_SELECT_MASK		0x02
#define WLED_USE_EXT_GEN_MOD_SRC	0x01
#define WLED_CTL_DLY_STEP		200
#define WLED_CTL_DLY_MAX		1400
#define WLED_MAX_CURR			25
#define WLED_NO_CURRENT			0x00
#define WLED_OVP_DELAY			1000
#define WLED_MSB_MASK			0x0F
#define WLED_MAX_CURR_MASK		0x1F
#define WLED_OP_FDBCK_MASK		0x07
#define WLED_OP_FDBCK_BIT_SHFT		0x00
#define WLED_OP_FDBCK_DEFAULT		0x00

#define WLED_MAX_LEVEL			4095
#define WLED_8_BIT_MASK			0xFF
#define WLED_4_BIT_MASK			0x0F
#define WLED_8_BIT_SHFT			0x08
#define WLED_MAX_DUTY_CYCLE		0xFFF

#define WLED_SYNC_VAL			0x07
#define WLED_SYNC_RESET_VAL		0x00

#define PMIC_VER_8026			0x04
#define PMIC_VERSION_REG		0x0105

#define WLED_DEFAULT_STRINGS		0x01
#define WLED_DEFAULT_OVP_VAL		0x02
#define WLED_BOOST_LIM_DEFAULT		0x03
#define WLED_CP_SEL_DEFAULT		0x00
#define WLED_CTRL_DLY_DEFAULT		0x00
#define WLED_SWITCH_FREQ_DEFAULT	0x0B

#define FLASH_SAFETY_TIMER(base)	(base + 0x40)
#define FLASH_MAX_CURR(base)		(base + 0x41)
#define FLASH_LED_0_CURR(base)		(base + 0x42)
#define FLASH_LED_1_CURR(base)		(base + 0x43)
#define FLASH_CLAMP_CURR(base)		(base + 0x44)
#define FLASH_LED_TMR_CTRL(base)	(base + 0x48)
#define FLASH_HEADROOM(base)		(base + 0x4A)
#define FLASH_STARTUP_DELAY(base)	(base + 0x4B)
#define FLASH_MASK_ENABLE(base)		(base + 0x4C)
#define FLASH_VREG_OK_FORCE(base)	(base + 0x4F)
#define FLASH_ENABLE_CONTROL(base)	(base + 0x46)
#define FLASH_LED_STROBE_CTRL(base)	(base + 0x47)
#define FLASH_LED_UNLOCK_SECURE(base)	(base + 0xD0)
#define FLASH_LED_TORCH(base)		(base + 0xE4)
#define FLASH_FAULT_DETECT(base)	(base + 0x51)
#define FLASH_PERIPHERAL_SUBTYPE(base)	(base + 0x05)
#define FLASH_CURRENT_RAMP(base)	(base + 0x54)

#define FLASH_MAX_LEVEL			0x4F
#define TORCH_MAX_LEVEL			0x0F
#define	FLASH_NO_MASK			0x00

#define FLASH_MASK_1			0x20
#define FLASH_MASK_REG_MASK		0xE0
#define FLASH_HEADROOM_MASK		0x03
#define FLASH_SAFETY_TIMER_MASK		0x7F
#define FLASH_CURRENT_MASK		0xFF
#define FLASH_MAX_CURRENT_MASK		0x7F
#define FLASH_TMR_MASK			0x03
#define FLASH_TMR_WATCHDOG		0x03
#define FLASH_TMR_SAFETY		0x00
#define FLASH_FAULT_DETECT_MASK		0X80
#define FLASH_HW_VREG_OK		0x40
#define FLASH_VREG_MASK			0xC0
#define FLASH_STARTUP_DLY_MASK		0x02
#define FLASH_CURRENT_RAMP_MASK		0xBF

#define FLASH_ENABLE_ALL		0xE0
#define FLASH_ENABLE_MODULE		0x80
#define FLASH_ENABLE_MODULE_MASK	0x80
#define FLASH_DISABLE_ALL		0x00
#define FLASH_ENABLE_MASK		0xE0
#define FLASH_ENABLE_LED_0		0xC0
#define FLASH_ENABLE_LED_1		0xA0
#define FLASH_INIT_MASK			0xE0
#define	FLASH_SELFCHECK_ENABLE		0x80
#define FLASH_RAMP_STEP_27US		0xBF

#define FLASH_HW_SW_STROBE_SEL_MASK	0x04
#define FLASH_STROBE_MASK		0xC7
#define FLASH_LED_0_OUTPUT		0x80
#define FLASH_LED_1_OUTPUT		0x40
#define FLASH_TORCH_OUTPUT		0xC0

#define FLASH_CURRENT_PRGM_MIN		1
#define FLASH_CURRENT_PRGM_SHIFT	1
#define FLASH_CURRENT_MAX		0x4F
#define FLASH_CURRENT_TORCH		0x07

#define FLASH_DURATION_200ms		0x13
#define FLASH_CLAMP_200mA		0x0F

#define FLASH_TORCH_MASK		0x03
#define FLASH_LED_TORCH_ENABLE		0x00
#define FLASH_LED_TORCH_DISABLE		0x03
#define FLASH_UNLOCK_SECURE		0xA5
#define FLASH_SECURE_MASK		0xFF

#define FLASH_SUBTYPE_DUAL		0x01
#define FLASH_SUBTYPE_SINGLE		0x02

#define FLASH_RAMP_UP_DELAY_US		1000
#define FLASH_RAMP_DN_DELAY_US		2160

#define LED_TRIGGER_DEFAULT		"none"

#define RGB_LED_SRC_SEL(base)		(base + 0x45)
#define RGB_LED_EN_CTL(base)		(base + 0x46)
#define RGB_LED_ATC_CTL(base)		(base + 0x47)

#define RGB_MAX_LEVEL			LED_FULL
#define RGB_LED_ENABLE_RED		0x80
#define RGB_LED_ENABLE_GREEN		0x40
#define RGB_LED_ENABLE_BLUE		0x20
#define RGB_LED_SOURCE_VPH_PWR		0x01
#define RGB_LED_ENABLE_MASK		0xE0
#define RGB_LED_SRC_MASK		0x03
#define QPNP_LED_PWM_FLAGS	(PM_PWM_LUT_LOOP | PM_PWM_LUT_RAMP_UP)
#define QPNP_LUT_RAMP_STEP_DEFAULT      150
#define QPNP_LUT_RAMP_STEP_DEFAULT1     255
#define	PWM_LUT_MAX_SIZE		63
#define	PWM_GPLED_LUT_MAX_SIZE		31
#define RGB_LED_DISABLE			0x00

#define MPP_MAX_LEVEL			LED_FULL
#define LED_MPP_MODE_CTRL(base)		(base + 0x40)
#define LED_MPP_VIN_CTRL(base)		(base + 0x41)
#define LED_MPP_EN_CTRL(base)		(base + 0x46)
#define LED_MPP_SINK_CTRL(base)		(base + 0x4C)

#define LED_MPP_CURRENT_MIN		5
#define LED_MPP_CURRENT_MAX		40
#define LED_MPP_VIN_CTRL_DEFAULT	0
#define LED_MPP_CURRENT_PER_SETTING	5
#define LED_MPP_SOURCE_SEL_DEFAULT	LED_MPP_MODE_ENABLE

#define LED_MPP_SINK_MASK		0x07
#define LED_MPP_MODE_MASK		0x7F
#define LED_MPP_VIN_MASK		0x03
#define LED_MPP_EN_MASK			0x80
#define LED_MPP_SRC_MASK		0x0F
#define LED_MPP_MODE_CTRL_MASK		0x70

#define LED_MPP_MODE_SINK		(0x06 << 4)
#define LED_MPP_MODE_ENABLE		0x01
#define LED_MPP_MODE_OUTPUT		0x10
#define LED_MPP_MODE_DISABLE		0x00
#define LED_MPP_EN_ENABLE		0x80
#define LED_MPP_EN_DISABLE		0x00

#define MPP_SOURCE_DTEST1		0x08

#define KPDBL_MAX_LEVEL			LED_FULL
#define KPDBL_ROW_SRC_SEL(base)		(base + 0x40)
#define KPDBL_ENABLE(base)		(base + 0x46)
#define KPDBL_ROW_SRC(base)		(base + 0xE5)

#define KPDBL_ROW_SRC_SEL_VAL_MASK	0x0F
#define KPDBL_ROW_SCAN_EN_MASK		0x80
#define KPDBL_ROW_SCAN_VAL_MASK		0x0F
#define KPDBL_ROW_SCAN_EN_SHIFT		7
#define KPDBL_MODULE_EN			0x80
#define KPDBL_MODULE_DIS		0x00
#define KPDBL_MODULE_EN_MASK		0x80
#define NUM_KPDBL_LEDS			4
#define KPDBL_MASTER_BIT_INDEX		0

/**
 * enum qpnp_leds - QPNP supported led ids
 * @QPNP_ID_WLED - White led backlight
 */
enum qpnp_leds {
	QPNP_ID_WLED = 0,
	QPNP_ID_FLASH1_LED0,
	QPNP_ID_FLASH1_LED1,
	QPNP_ID_RGB_RED,
	QPNP_ID_RGB_GREEN,
	QPNP_ID_RGB_BLUE,
	QPNP_ID_LED_MPP,
	QPNP_ID_KPDBL,
	QPNP_ID_MAX,
};

/* current boost limit */
enum wled_current_boost_limit {
	WLED_CURR_LIMIT_105mA,
	WLED_CURR_LIMIT_385mA,
	WLED_CURR_LIMIT_525mA,
	WLED_CURR_LIMIT_805mA,
	WLED_CURR_LIMIT_980mA,
	WLED_CURR_LIMIT_1260mA,
	WLED_CURR_LIMIT_1400mA,
	WLED_CURR_LIMIT_1680mA,
};

/* over voltage protection threshold */
enum wled_ovp_threshold {
	WLED_OVP_35V,
	WLED_OVP_32V,
	WLED_OVP_29V,
	WLED_OVP_27V,
};

enum flash_headroom {
	HEADROOM_250mV = 0,
	HEADROOM_300mV,
	HEADROOM_400mV,
	HEADROOM_500mV,
};

enum flash_startup_dly {
	DELAY_10us = 0,
	DELAY_32us,
	DELAY_64us,
	DELAY_128us,
};

enum led_mode {
	PWM_MODE = 0,
	LPG_MODE,
	MANUAL_MODE,
};

static u8 wled_debug_regs[] = {
	/* common registers */
	0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	/* LED1 */
	0x60, 0x61, 0x62, 0x63, 0x66,
	/* LED2 */
	0x70, 0x71, 0x72, 0x73, 0x76,
	/* LED3 */
	0x80, 0x81, 0x82, 0x83, 0x86,
};

static u8 flash_debug_regs[] = {
	0x40, 0x41, 0x42, 0x43, 0x44, 0x48, 0x49, 0x4b, 0x4c,
	0x4f, 0x46, 0x47,
};

static u8 rgb_pwm_debug_regs[] = {
	0x45, 0x46, 0x47,
};

static u8 mpp_debug_regs[] = {
	0x40, 0x41, 0x42, 0x45, 0x46, 0x4c,
};

static u8 kpdbl_debug_regs[] = {
	0x40, 0x46, 0xb1, 0xb3, 0xb4, 0xe5,
};

/**
 *  pwm_config_data - pwm configuration data
 *  @lut_params - lut parameters to be used by pwm driver
 *  @pwm_device - pwm device
 *  @pwm_channel - pwm channel to be configured for led
 *  @pwm_period_us - period for pwm, in us
 *  @mode - mode the led operates in
 *  @old_duty_pcts - storage for duty pcts that may need to be reused
 *  @default_mode - default mode of LED as set in device tree
 *  @use_blink - use blink sysfs entry
 *  @blinking - device is currently blinking w/LPG mode
 */
struct pwm_config_data {
	struct lut_params	lut_params;
	struct pwm_device	*pwm_dev;
	int			pwm_channel;
	u32			pwm_period_us;
	struct pwm_duty_cycles	*duty_cycles;
	int	*old_duty_pcts;
	u8	mode;
	u8	default_mode;
	bool use_blink;
	bool blinking;
};

/**
 *  wled_config_data - wled configuration data
 *  @num_strings - number of wled strings supported
 *  @ovp_val - over voltage protection threshold
 *  @boost_curr_lim - boot current limit
 *  @cp_select - high pole capacitance
 *  @ctrl_delay_us - delay in activation of led
 *  @dig_mod_gen_en - digital module generator
 *  @cs_out_en - current sink output enable
 *  @op_fdbck - selection of output as feedback for the boost
 */
struct wled_config_data {
	u8	num_strings;
	u8	ovp_val;
	u8	boost_curr_lim;
	u8	cp_select;
	u8	ctrl_delay_us;
	u8	switch_freq;
	u8	op_fdbck;
	u8	pmic_version;
	bool	dig_mod_gen_en;
	bool	cs_out_en;
};

/**
 *  mpp_config_data - mpp configuration data
 *  @pwm_cfg - device pwm configuration
 *  @current_setting - current setting, 5ma-40ma in 5ma increments
 *  @source_sel - source selection
 *  @mode_ctrl - mode control
 *  @vin_ctrl - input control
 *  @min_brightness - minimum brightness supported
 *  @pwm_mode - pwm mode in use
 */
struct mpp_config_data {
	struct pwm_config_data	*pwm_cfg;
	u8	current_setting;
	u8	source_sel;
	u8	mode_ctrl;
	u8	vin_ctrl;
	u8	min_brightness;
	u8 pwm_mode;
};

/**
 *  flash_config_data - flash configuration data
 *  @current_prgm - current to be programmed, scaled by max level
 *  @clamp_curr - clamp current to use
 *  @headroom - headroom value to use
 *  @duration - duration of the flash
 *  @enable_module - enable address for particular flash
 *  @trigger_flash - trigger flash
 *  @startup_dly - startup delay for flash
 *  @strobe_type - select between sw and hw strobe
 *  @peripheral_subtype - module peripheral subtype
 *  @current_addr - address to write for current
 *  @second_addr - address of secondary flash to be written
 *  @safety_timer - enable safety timer or watchdog timer
 *  @torch_enable - enable flash LED torch mode
 *  @flash_reg_get - flash regulator attached or not
 *  @flash_wa_reg_get - workaround regulator attached or not
 *  @flash_on - flash status, on or off
 *  @torch_on - torch status, on or off
 *  @flash_boost_reg - boost regulator for flash
 *  @torch_boost_reg - boost regulator for torch
 *  @flash_wa_reg - flash regulator for wa
 */
struct flash_config_data {
	u8	current_prgm;
	u8	clamp_curr;
	u8	headroom;
	u8	duration;
	u8	enable_module;
	u8	trigger_flash;
	u8	startup_dly;
	u8	strobe_type;
	u8	peripheral_subtype;
	u16	current_addr;
	//u16	second_addr;
	bool	safety_timer;
	bool	torch_enable;
	bool	flash_reg_get;
	bool	torch_reg_get;
	bool    flash_wa_reg_get;
	bool	flash_on;
	bool	torch_on;
	bool	torch_mode_enable;
	struct regulator *flash_boost_reg;
	struct regulator *torch_boost_reg;
	struct regulator *flash_wa_reg;
};

/**
 *  kpdbl_config_data - kpdbl configuration data
 *  @pwm_cfg - device pwm configuration
 *  @mode - running mode: pwm or lut
 *  @row_id - row id of the led
 *  @row_src_vbst - 0 for vph_pwr and 1 for vbst
 *  @row_src_en - enable row source
 *  @always_on - always on row
 *  @lut_params - lut parameters to be used by pwm driver
 *  @duty_cycles - duty cycles for lut
 *  @pwm_mode - pwm mode in use
 */
struct kpdbl_config_data {
	struct pwm_config_data	*pwm_cfg;
	u32	row_id;
	bool	row_src_vbst;
	bool	row_src_en;
	bool	always_on;
	struct pwm_duty_cycles  *duty_cycles;
	struct lut_params	lut_params;
	u8	pwm_mode;
};

#if SHENQI_RGB
/**
 *  rgb_config_data - rgb configuration data
 *  @lut_params - lut parameters to be used by pwm driver
 *  @pwm_device - pwm device
 *  @pwm_channel - pwm channel to be configured for led
 *  @pwm_period_us - period for pwm, in us
 *  @mode - mode the led operates in
 */
struct rgb_config_data {
        struct lut_params       lut_params;
        struct pwm_device       *pwm_dev;
        int                     pwm_channel;
        u32                     pwm_period_us;
        struct pwm_duty_cycles  *duty_cycles;
        struct pwm_duty_cycles  *duty_cycles1;
        struct lut_params       lut_params1;
        u8      mode;
        u8      enable;
};
#else
/**
 *  rgb_config_data - rgb configuration data
 *  @pwm_cfg - device pwm configuration
 *  @enable - bits to enable led
 */
struct rgb_config_data {
        struct pwm_config_data  *pwm_cfg;
        u8      enable;
};
#endif
/**
 * struct qpnp_led_data - internal led data structure
 * @led_classdev - led class device
 * @delayed_work - delayed work for turning off the LED
 * @workqueue - dedicated workqueue to handle concurrency
 * @work - workqueue for led
 * @id - led index
 * @base_reg - base register given in device tree
 * @lock - to protect the transactions
 * @reg - cached value of led register
 * @num_leds - number of leds in the module
 * @max_current - maximum current supported by LED
 * @default_on - true: default state max, false, default state 0
 * @turn_off_delay_ms - number of msec before turning off the LED
 */
struct qpnp_led_data {
	struct led_classdev	cdev;
	struct spmi_device	*spmi_dev;
	struct delayed_work	dwork;
	struct workqueue_struct *workqueue;
	struct work_struct	work;
	int			id;
	u16			base;
	u8			reg;
	u8			num_leds;
	struct mutex		lock;
	struct wled_config_data *wled_cfg;
	struct flash_config_data	*flash_cfg;
	struct kpdbl_config_data	*kpdbl_cfg;
	struct rgb_config_data	*rgb_cfg;
	struct mpp_config_data	*mpp_cfg;
	int			max_current;
	bool			default_on;
	bool                    in_order_command_processing;
	int			turn_off_delay_ms;
#if SHENQI_RGB
        int led_blink;
        int led_breath;
#endif
};

static int num_kpbl_leds_on;

static DEFINE_MUTEX(flash_lock);
static struct pwm_device *kpdbl_master;
static u32 kpdbl_master_period_us;
DECLARE_BITMAP(kpdbl_leds_in_use, NUM_KPDBL_LEDS);
static bool is_kpdbl_master_turn_on;

static int
qpnp_led_masked_write(struct qpnp_led_data *led, u16 addr, u8 mask, u8 val)
{
	int rc;
	u8 reg;

	rc = spmi_ext_register_readl(led->spmi_dev->ctrl, led->spmi_dev->sid,
		addr, &reg, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read from addr=%x, rc(%d)\n", addr, rc);
	}

	reg &= ~mask;
	reg |= val;

	rc = spmi_ext_register_writel(led->spmi_dev->ctrl, led->spmi_dev->sid,
		addr, &reg, 1);
	if (rc)
		dev_err(&led->spmi_dev->dev,
			"Unable to write to addr=%x, rc(%d)\n", addr, rc);
	return rc;
}

static void qpnp_dump_regs(struct qpnp_led_data *led, u8 regs[], u8 array_size)
{
	int i;
	u8 val;

	pr_debug("===== %s LED register dump start =====\n", led->cdev.name);
	for (i = 0; i < array_size; i++) {
		spmi_ext_register_readl(led->spmi_dev->ctrl,
					led->spmi_dev->sid,
					led->base + regs[i],
					&val, sizeof(val));
		pr_debug("%s: 0x%x = 0x%x\n", led->cdev.name,
					led->base + regs[i], val);
	}
	pr_debug("===== %s LED register dump end =====\n", led->cdev.name);
}

static int qpnp_wled_sync(struct qpnp_led_data *led)
{
	int rc;
	u8 val;

	/* sync */
	val = WLED_SYNC_VAL;
	rc = spmi_ext_register_writel(led->spmi_dev->ctrl, led->spmi_dev->sid,
		WLED_SYNC_REG(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED set sync reg failed(%d)\n", rc);
		return rc;
	}

	val = WLED_SYNC_RESET_VAL;
	rc = spmi_ext_register_writel(led->spmi_dev->ctrl, led->spmi_dev->sid,
		WLED_SYNC_REG(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED reset sync reg failed(%d)\n", rc);
		return rc;
	}
	return 0;
}

static int qpnp_wled_set(struct qpnp_led_data *led)
{
	int rc, duty, level;
	u8 val, i, num_wled_strings, sink_val;

	num_wled_strings = led->wled_cfg->num_strings;

	level = led->cdev.brightness;

	if (level > WLED_MAX_LEVEL)
		level = WLED_MAX_LEVEL;
	if (level == 0) {
		for (i = 0; i < num_wled_strings; i++) {
			rc = qpnp_led_masked_write(led,
				WLED_FULL_SCALE_REG(led->base, i),
				WLED_MAX_CURR_MASK, WLED_NO_CURRENT);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Write max current failure (%d)\n",
					rc);
				return rc;
			}
		}

		rc = qpnp_wled_sync(led);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED sync failed(%d)\n", rc);
			return rc;
		}

		rc = spmi_ext_register_readl(led->spmi_dev->ctrl,
			led->spmi_dev->sid, WLED_CURR_SINK_REG(led->base),
			&sink_val, 1);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED read sink reg failed(%d)\n", rc);
			return rc;
		}

		if (led->wled_cfg->pmic_version == PMIC_VER_8026) {
			val = WLED_DISABLE_ALL_SINKS;
			rc = spmi_ext_register_writel(led->spmi_dev->ctrl,
				led->spmi_dev->sid,
				WLED_CURR_SINK_REG(led->base), &val, 1);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"WLED write sink reg failed(%d)\n", rc);
				return rc;
			}

			usleep(WLED_OVP_DELAY);
		}

		val = WLED_BOOST_OFF;
		rc = spmi_ext_register_writel(led->spmi_dev->ctrl,
			led->spmi_dev->sid, WLED_MOD_CTRL_REG(led->base),
			&val, 1);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED write ctrl reg failed(%d)\n", rc);
			return rc;
		}

		for (i = 0; i < num_wled_strings; i++) {
			rc = qpnp_led_masked_write(led,
				WLED_FULL_SCALE_REG(led->base, i),
				WLED_MAX_CURR_MASK, (u8)led->max_current);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Write max current failure (%d)\n",
					rc);
				return rc;
			}
		}

		rc = qpnp_wled_sync(led);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED sync failed(%d)\n", rc);
			return rc;
		}

		rc = spmi_ext_register_writel(led->spmi_dev->ctrl,
			led->spmi_dev->sid, WLED_CURR_SINK_REG(led->base),
			&sink_val, 1);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED write sink reg failed(%d)\n", rc);
			return rc;
		}

	} else {
		val = WLED_BOOST_ON;
		rc = spmi_ext_register_writel(led->spmi_dev->ctrl,
			led->spmi_dev->sid, WLED_MOD_CTRL_REG(led->base),
			&val, 1);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED write ctrl reg failed(%d)\n", rc);
			return rc;
		}
	}

	duty = (WLED_MAX_DUTY_CYCLE * level) / WLED_MAX_LEVEL;

	/* program brightness control registers */
	for (i = 0; i < num_wled_strings; i++) {
		rc = qpnp_led_masked_write(led,
			WLED_BRIGHTNESS_CNTL_MSB(led->base, i), WLED_MSB_MASK,
			(duty >> WLED_8_BIT_SHFT) & WLED_4_BIT_MASK);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED set brightness MSB failed(%d)\n", rc);
			return rc;
		}
		val = duty & WLED_8_BIT_MASK;
		rc = spmi_ext_register_writel(led->spmi_dev->ctrl,
			led->spmi_dev->sid,
			WLED_BRIGHTNESS_CNTL_LSB(led->base, i), &val, 1);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED set brightness LSB failed(%d)\n", rc);
			return rc;
		}
	}

	rc = qpnp_wled_sync(led);
	if (rc) {
		dev_err(&led->spmi_dev->dev, "WLED sync failed(%d)\n", rc);
		return rc;
	}
	return 0;
}

static int qpnp_mpp_set(struct qpnp_led_data *led)
{
	int rc;
	u8 val;
	int duty_us, duty_ns, period_us;

	if (led->cdev.brightness) {
		if (led->cdev.brightness < led->mpp_cfg->min_brightness) {
			dev_warn(&led->spmi_dev->dev,
				"brightness is less than supported..." \
				"set to minimum supported\n");
			led->cdev.brightness = led->mpp_cfg->min_brightness;
		}

		if (led->mpp_cfg->pwm_mode != MANUAL_MODE) {
			if (!led->mpp_cfg->pwm_cfg->blinking) {
				led->mpp_cfg->pwm_cfg->mode =
					led->mpp_cfg->pwm_cfg->default_mode;
				led->mpp_cfg->pwm_mode =
					led->mpp_cfg->pwm_cfg->default_mode;
			}
		}
		if (led->mpp_cfg->pwm_mode == PWM_MODE) {
			/*config pwm for brightness scaling*/
			period_us = led->mpp_cfg->pwm_cfg->pwm_period_us;
			if (period_us > INT_MAX / NSEC_PER_USEC) {
				duty_us = (period_us * led->cdev.brightness) /
					LED_FULL;
				rc = pwm_config_us(
					led->mpp_cfg->pwm_cfg->pwm_dev,
					duty_us,
					period_us);
			} else {
				duty_ns = ((period_us * NSEC_PER_USEC) /
					LED_FULL) * led->cdev.brightness;
				rc = pwm_config(
					led->mpp_cfg->pwm_cfg->pwm_dev,
					duty_ns,
					period_us * NSEC_PER_USEC);
			}
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev, "Failed to " \
					"configure pwm for new values\n");
				return rc;
			}
		}

		if (led->mpp_cfg->pwm_mode != MANUAL_MODE)
			pwm_enable(led->mpp_cfg->pwm_cfg->pwm_dev);
		else {
			if (led->cdev.brightness < LED_MPP_CURRENT_MIN)
				led->cdev.brightness = LED_MPP_CURRENT_MIN;

			val = (led->cdev.brightness / LED_MPP_CURRENT_MIN) - 1;

			rc = qpnp_led_masked_write(led,
					LED_MPP_SINK_CTRL(led->base),
					LED_MPP_SINK_MASK, val);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Failed to write sink control reg\n");
				return rc;
			}
		}

		val = (led->mpp_cfg->source_sel & LED_MPP_SRC_MASK) |
			(led->mpp_cfg->mode_ctrl & LED_MPP_MODE_CTRL_MASK);

		rc = qpnp_led_masked_write(led,
			LED_MPP_MODE_CTRL(led->base), LED_MPP_MODE_MASK,
			val);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
					"Failed to write led mode reg\n");
			return rc;
		}

		rc = qpnp_led_masked_write(led,
				LED_MPP_EN_CTRL(led->base), LED_MPP_EN_MASK,
				LED_MPP_EN_ENABLE);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
					"Failed to write led enable " \
					"reg\n");
			return rc;
		}
	} else {
		if (led->mpp_cfg->pwm_mode != MANUAL_MODE) {
			led->mpp_cfg->pwm_cfg->mode =
				led->mpp_cfg->pwm_cfg->default_mode;
			led->mpp_cfg->pwm_mode =
				led->mpp_cfg->pwm_cfg->default_mode;
			pwm_disable(led->mpp_cfg->pwm_cfg->pwm_dev);
		}
		rc = qpnp_led_masked_write(led,
					LED_MPP_MODE_CTRL(led->base),
					LED_MPP_MODE_MASK,
					LED_MPP_MODE_DISABLE);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
					"Failed to write led mode reg\n");
			return rc;
		}

		rc = qpnp_led_masked_write(led,
					LED_MPP_EN_CTRL(led->base),
					LED_MPP_EN_MASK,
					LED_MPP_EN_DISABLE);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
					"Failed to write led enable reg\n");
			return rc;
		}
	}

	if (led->mpp_cfg->pwm_mode != MANUAL_MODE)
		led->mpp_cfg->pwm_cfg->blinking = false;
	qpnp_dump_regs(led, mpp_debug_regs, ARRAY_SIZE(mpp_debug_regs));

	return 0;
}

static int qpnp_flash_regulator_operate(struct qpnp_led_data *led, bool on)
{
	int rc, i;
	struct qpnp_led_data *led_array;
	bool regulator_on = false;

	led_array = dev_get_drvdata(&led->spmi_dev->dev);
	if (!led_array) {
		dev_err(&led->spmi_dev->dev,
				"Unable to get LED array\n");
		return -EINVAL;
	}

	for (i = 0; i < led->num_leds; i++)
		regulator_on |= led_array[i].flash_cfg->flash_on;

	if (!on)
		goto regulator_turn_off;

	if (!regulator_on && !led->flash_cfg->flash_on) {
		for (i = 0; i < led->num_leds; i++) {
			if (led_array[i].flash_cfg->flash_reg_get) {
				if (led_array[i].flash_cfg->flash_wa_reg_get) {
					rc = regulator_enable(
						led_array[i].flash_cfg->
							flash_wa_reg);
					if (rc) {
						dev_err(&led->spmi_dev->dev,
							"Flash wa regulator"
							"enable failed(%d)\n",
							rc);
						return rc;
					}
				}

				rc = regulator_enable(
					led_array[i].flash_cfg->\
					flash_boost_reg);
				if (rc) {
					if (led_array[i].flash_cfg->
							flash_wa_reg_get)
						/* Disable flash wa regulator
						 * when flash boost regulator
						 * enable fails
						 */
						regulator_disable(
							led_array[i].flash_cfg->
								flash_wa_reg);
					dev_err(&led->spmi_dev->dev,
						"Flash boost regulator enable"
						"failed(%d)\n", rc);
					return rc;
				}
				led->flash_cfg->flash_on = true;
			}
			break;
		}
	}

	return 0;

regulator_turn_off:
	if (regulator_on && led->flash_cfg->flash_on) {
		for (i = 0; i < led->num_leds; i++) {
			if (led_array[i].flash_cfg->flash_reg_get) {
				rc = qpnp_led_masked_write(led,
					FLASH_ENABLE_CONTROL(led->base),
					FLASH_ENABLE_MASK,
					FLASH_DISABLE_ALL);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Enable reg write failed(%d)\n",
						rc);
				}

				rc = regulator_disable(led_array[i].flash_cfg->\
							flash_boost_reg);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Flash boost regulator disable"
						"failed(%d)\n", rc);
					return rc;
				}
				if (led_array[i].flash_cfg->flash_wa_reg_get) {
					rc = regulator_disable(
						led_array[i].flash_cfg->
							flash_wa_reg);
					if (rc) {
						dev_err(&led->spmi_dev->dev,
							"Flash_wa regulator"
							"disable failed(%d)\n",
							rc);
						return rc;
					}
				}
				led->flash_cfg->flash_on = false;
			}
			break;
		}
	}

	return 0;
}

static int qpnp_torch_regulator_operate(struct qpnp_led_data *led, bool on)
{
	int rc, i;
	struct qpnp_led_data *led_array;
	bool regulator_on = false;

	led_array = dev_get_drvdata(&led->spmi_dev->dev);
	if (!led_array) {
		dev_err(&led->spmi_dev->dev,
				"Unable to get LED array\n");
		return -EINVAL;
	}

	for (i = 0; i < led->num_leds; i++)
		regulator_on |= led_array[i].flash_cfg->torch_on;

	if (!on)
		goto regulator_turn_off;

	if (!regulator_on && !led->flash_cfg->torch_on) {
		for (i = 0; i < led->num_leds; i++) {
			if (led_array[i].flash_cfg->torch_reg_get) {

				rc = regulator_enable(
					led_array[i].flash_cfg->\
					torch_boost_reg);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
					"Regulator enable failed(%d)\n", rc);
					return rc;
				}
				led->flash_cfg->torch_on = true;
			}
			break;
		}
	}

	return 0;

regulator_turn_off:
	if (regulator_on && led->flash_cfg->torch_on) {
		for (i = 0; i < led->num_leds; i++) {
			if (led_array[i].flash_cfg->torch_reg_get) {
				rc = qpnp_led_masked_write(led,	FLASH_ENABLE_CONTROL(led->base),
				FLASH_ENABLE_MODULE_MASK, FLASH_DISABLE_ALL);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Enable reg write failed(%d)\n",
						rc);
				}

				rc = regulator_disable(led_array[i].flash_cfg->\
							torch_boost_reg);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Flash boost regulator disable"
						"failed(%d)\n", rc);
					return rc;
				}
				led->flash_cfg->torch_on = false;
			}
			break;
		}
	}

	return 0;
}
static int qpnp_torch_mode_enable_operate(struct qpnp_led_data *led, bool on)
{
	int rc, i;
	struct qpnp_led_data *led_array;
	bool torch_mode_enable = false;

	led_array = dev_get_drvdata(&led->spmi_dev->dev);
	if (!led_array) {
		dev_err(&led->spmi_dev->dev,
				"Unable to get LED array\n");
		return -EINVAL;
	}
	for (i = 0; i < led->num_leds; i++)
	torch_mode_enable |= led_array[i].flash_cfg->torch_mode_enable;
	if(on){
		if (!torch_mode_enable && !led->flash_cfg->torch_mode_enable) {
			rc = qpnp_led_masked_write(led,
				FLASH_LED_TORCH(led->base),
				FLASH_TORCH_MASK, FLASH_LED_TORCH_ENABLE);
			if(rc == 0)
				led->flash_cfg->torch_mode_enable = true;
		}
		return rc;
	} else {
		if (torch_mode_enable && led->flash_cfg->torch_mode_enable) {
			rc = qpnp_led_masked_write(led,
				FLASH_LED_TORCH(led->base),
				FLASH_TORCH_MASK, FLASH_LED_TORCH_DISABLE);
			if(rc == 0)
				led->flash_cfg->torch_mode_enable = false;
		}
	}
	return 0;
}
static int qpnp_flash_set(struct qpnp_led_data *led)
{
	int rc, error;
	int val = led->cdev.brightness;
			//dev_err(&led->spmi_dev->dev,
				//"qpnp_flash_set torch_enable:%d, val:%d\n",led->flash_cfg->torch_enable, val);
	if (led->flash_cfg->torch_enable)
		led->flash_cfg->current_prgm =
			(val * TORCH_MAX_LEVEL / led->max_current);
	else
		led->flash_cfg->current_prgm =
			(val * FLASH_MAX_LEVEL / led->max_current);

	/* Set led current */
	if (val > 0) {
		if (led->flash_cfg->torch_enable) {
			if (led->flash_cfg->peripheral_subtype ==
							FLASH_SUBTYPE_DUAL) {
				rc = qpnp_torch_regulator_operate(led, true);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
					"Torch regulator operate failed(%d)\n",
					rc);
					return rc;
				}
			} else if (led->flash_cfg->peripheral_subtype ==
							FLASH_SUBTYPE_SINGLE) {
				rc = qpnp_flash_regulator_operate(led, true);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
					"Flash regulator operate failed(%d)\n",
					rc);
					goto error_flash_set;
				}
			}

			rc = qpnp_led_masked_write(led,
				FLASH_LED_UNLOCK_SECURE(led->base),
				FLASH_SECURE_MASK, FLASH_UNLOCK_SECURE);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Secure reg write failed(%d)\n", rc);
				goto error_reg_write;
			}
			rc = qpnp_torch_mode_enable_operate(led,true);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Torch reg write failed(%d)\n", rc);
				goto error_reg_write;
			}

			rc = qpnp_led_masked_write(led,
				led->flash_cfg->current_addr,
				FLASH_CURRENT_MASK,
				led->flash_cfg->current_prgm);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Current reg write failed(%d)\n", rc);
				goto error_reg_write;
			}
#if 0
			rc = qpnp_led_masked_write(led,
				led->flash_cfg->second_addr,
				FLASH_CURRENT_MASK,
				led->flash_cfg->current_prgm);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"2nd Current reg write failed(%d)\n",
					rc);
				goto error_reg_write;
			}
#endif
			qpnp_led_masked_write(led, FLASH_MAX_CURR(led->base),
				FLASH_CURRENT_MASK,
				TORCH_MAX_LEVEL);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Max current reg write failed(%d)\n",
					rc);
				goto error_reg_write;
			}

			rc = qpnp_led_masked_write(led,
				FLASH_ENABLE_CONTROL(led->base),
				FLASH_ENABLE_MASK,
				led->flash_cfg->enable_module);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Enable reg write failed(%d)\n",
					rc);
				goto error_reg_write;
			}

			if (!led->flash_cfg->strobe_type)
				led->flash_cfg->trigger_flash &=
						~FLASH_HW_SW_STROBE_SEL_MASK;
			else
				led->flash_cfg->trigger_flash |=
						FLASH_HW_SW_STROBE_SEL_MASK;

			rc = qpnp_led_masked_write(led,
				FLASH_LED_STROBE_CTRL(led->base),
				led->flash_cfg->trigger_flash,
				led->flash_cfg->trigger_flash);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"LED %d strobe reg write failed(%d)\n",
					led->id, rc);
				goto error_reg_write;
			}
		} else {
			rc = qpnp_flash_regulator_operate(led, true);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Flash regulator operate failed(%d)\n",
					rc);
				goto error_flash_set;
			}

			/* Set flash safety timer */
			rc = qpnp_led_masked_write(led,
				FLASH_SAFETY_TIMER(led->base),
				FLASH_SAFETY_TIMER_MASK,
				led->flash_cfg->duration);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Safety timer reg write failed(%d)\n",
					rc);
				goto error_flash_set;
			}

			/* Set max current */
			rc = qpnp_led_masked_write(led,
				FLASH_MAX_CURR(led->base), FLASH_CURRENT_MASK,
				FLASH_MAX_LEVEL);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Max current reg write failed(%d)\n",
					rc);
				goto error_flash_set;
			}

			/* Set clamp current */
			rc = qpnp_led_masked_write(led,
				FLASH_CLAMP_CURR(led->base),
				FLASH_CURRENT_MASK,
				led->flash_cfg->clamp_curr);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Clamp current reg write failed(%d)\n",
					rc);
				goto error_flash_set;
			}

			rc = qpnp_led_masked_write(led,
				led->flash_cfg->current_addr,
				FLASH_CURRENT_MASK,
				led->flash_cfg->current_prgm);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Current reg write failed(%d)\n", rc);
				goto error_flash_set;
			}

			rc = qpnp_led_masked_write(led,
				FLASH_ENABLE_CONTROL(led->base),
				led->flash_cfg->enable_module,
				led->flash_cfg->enable_module);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Enable reg write failed(%d)\n", rc);
				goto error_flash_set;
			}

			/*
			 * Add 1ms delay for bharger enter stable state
			 */
			usleep(FLASH_RAMP_UP_DELAY_US);

			if (!led->flash_cfg->strobe_type)
				led->flash_cfg->trigger_flash &=
						~FLASH_HW_SW_STROBE_SEL_MASK;
			else
				led->flash_cfg->trigger_flash |=
						FLASH_HW_SW_STROBE_SEL_MASK;

			rc = qpnp_led_masked_write(led,
				FLASH_LED_STROBE_CTRL(led->base),
				led->flash_cfg->trigger_flash,
				led->flash_cfg->trigger_flash);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
				"LED %d strobe reg write failed(%d)\n",
				led->id, rc);
				goto error_flash_set;
			}
		}
	} else {
		rc = qpnp_led_masked_write(led,
			FLASH_LED_STROBE_CTRL(led->base),
			led->flash_cfg->trigger_flash,
			FLASH_DISABLE_ALL);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"LED %d flash write failed(%d)\n", led->id, rc);
			if (led->flash_cfg->torch_enable)
				goto error_torch_set;
			else
				goto error_flash_set;
		}

		if (led->flash_cfg->torch_enable) {
			rc = qpnp_led_masked_write(led,
				FLASH_LED_UNLOCK_SECURE(led->base),
				FLASH_SECURE_MASK, FLASH_UNLOCK_SECURE);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Secure reg write failed(%d)\n", rc);
				goto error_torch_set;
			}

			rc = qpnp_torch_mode_enable_operate(led,false);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Torch reg write failed(%d)\n", rc);
				goto error_torch_set;
			}

			if (led->flash_cfg->peripheral_subtype ==
							FLASH_SUBTYPE_DUAL) {
				rc = qpnp_torch_regulator_operate(led, false);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Torch regulator operate failed(%d)\n",
						rc);
					return rc;
				}
			} else if (led->flash_cfg->peripheral_subtype ==
							FLASH_SUBTYPE_SINGLE) {
				rc = qpnp_flash_regulator_operate(led, false);
				if (rc) {
					dev_err(&led->spmi_dev->dev,
						"Flash regulator operate failed(%d)\n",
						rc);
					return rc;
				}
			}
		} else {
			/*
			 * Disable module after ramp down complete for stable
			 * behavior
			 */
			usleep(FLASH_RAMP_DN_DELAY_US);

			rc = qpnp_led_masked_write(led,
				FLASH_ENABLE_CONTROL(led->base),
				led->flash_cfg->enable_module &
				~FLASH_ENABLE_MODULE_MASK,
				FLASH_DISABLE_ALL);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Enable reg write failed(%d)\n", rc);
				if (led->flash_cfg->torch_enable)
					goto error_torch_set;
				else
					goto error_flash_set;
			}

			rc = qpnp_flash_regulator_operate(led, false);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Flash regulator operate failed(%d)\n",
					rc);
				return rc;
			}
		}
	}

	qpnp_dump_regs(led, flash_debug_regs, ARRAY_SIZE(flash_debug_regs));

	return 0;

error_reg_write:
	if (led->flash_cfg->peripheral_subtype == FLASH_SUBTYPE_SINGLE)
		goto error_flash_set;

error_torch_set:
	error = qpnp_torch_regulator_operate(led, false);
	if (error) {
		dev_err(&led->spmi_dev->dev,
			"Torch regulator operate failed(%d)\n", rc);
		return error;
	}
	return rc;

error_flash_set:
	error = qpnp_flash_regulator_operate(led, false);
	if (error) {
		dev_err(&led->spmi_dev->dev,
			"Flash regulator operate failed(%d)\n", rc);
		return error;
	}
	return rc;
}

#if SHENQI_KPD
int qpnp_kpdbl_enable(bool onoff,int brightness)
{
        int duty_us;
        int rc;
    	
        //printk("%s,onoff is %d,brightness is %d\n",__func__,onoff,brightness);
        if (onoff) {
                /*
                rc = qpnp_led_masked_write(led, KPDBL_ENABLE(led->base),
                                KPDBL_MODULE_EN_MASK, KPDBL_MODULE_EN);
                                */
                duty_us = (1000*brightness) / KPDBL_MAX_LEVEL;
                rc = pwm_config_us(pwm_dev_button2, duty_us*3/2,
                                1000);
                if (rc < 0) {
                        printk( "pwm config failed\n");
                        return rc;
                }
                rc = pwm_enable(pwm_dev_button2);
                if (rc < 0) {
                printk( "pwm enable failed\n");
                        return rc;
                }
                rc = pwm_config_us(pwm_dev_button1, duty_us,
                                1000);
                if (rc < 0) {
                        printk( "pwm config failed\n");
                        return rc;
                }
                rc = pwm_enable(pwm_dev_button1);
                if (rc < 0) {
                printk( "pwm enable failed\n");
                        return rc;
                }
        } else {
                pwm_disable(pwm_dev_button1);
                pwm_disable(pwm_dev_button2);
                /*
                rc = qpnp_led_masked_write(led, KPDBL_ENABLE(led->base),
                                KPDBL_MODULE_EN_MASK, KPDBL_MODULE_DIS);
                if (rc) {
                        dev_err(&led->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
                */
        }


        return 0;
}
#endif

static int qpnp_kpdbl_set(struct qpnp_led_data *led)
{
	int rc;
	int duty_us, duty_ns, period_us;

	if (led->cdev.brightness) {
		if (!led->kpdbl_cfg->pwm_cfg->blinking)
			led->kpdbl_cfg->pwm_cfg->mode =
				led->kpdbl_cfg->pwm_cfg->default_mode;
		if (!num_kpbl_leds_on) {
			rc = qpnp_led_masked_write(led, KPDBL_ENABLE(led->base),
					KPDBL_MODULE_EN_MASK, KPDBL_MODULE_EN);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Enable reg write failed(%d)\n", rc);
				return rc;
			}
		}

		if (led->kpdbl_cfg->pwm_cfg->mode == PWM_MODE) {
			period_us = led->kpdbl_cfg->pwm_cfg->pwm_period_us;
			if (period_us > INT_MAX / NSEC_PER_USEC) {
				duty_us = (period_us * led->cdev.brightness) /
					KPDBL_MAX_LEVEL;
				rc = pwm_config_us(
					led->kpdbl_cfg->pwm_cfg->pwm_dev,
					duty_us,
					period_us);
			} else {
				duty_ns = ((period_us * NSEC_PER_USEC) /
					KPDBL_MAX_LEVEL) * led->cdev.brightness;
				rc = pwm_config(
					led->kpdbl_cfg->pwm_cfg->pwm_dev,
					duty_ns,
					period_us * NSEC_PER_USEC);
			}
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev, "pwm config failed\n");
				return rc;
			}
		}

		rc = pwm_enable(led->kpdbl_cfg->pwm_cfg->pwm_dev);
		if (rc < 0) {
			dev_err(&led->spmi_dev->dev, "pwm enable failed\n");
			return rc;
		}

		num_kpbl_leds_on++;

	} else {
		led->kpdbl_cfg->pwm_cfg->mode =
			led->kpdbl_cfg->pwm_cfg->default_mode;

		/* Before disabling GPLED1, check if any other GPLED 2/3/4 is
		 * on. If any of the other GPLED 2/3/4 is on, then have the
		 * GPLED1 channel enabled with 0 brightness.
		 */
		if (led->kpdbl_cfg->always_on) {
			rc = pwm_config_us(led->kpdbl_cfg->pwm_cfg->pwm_dev, 0,
				led->kpdbl_cfg->pwm_cfg->pwm_period_us);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
						"pwm config failed\n");
				return rc;
			}

			rc = pwm_enable(led->kpdbl_cfg->pwm_cfg->pwm_dev);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev, "pwm enable failed\n");
				return rc;
			}
		} else
			pwm_disable(led->kpdbl_cfg->pwm_cfg->pwm_dev);

		if (num_kpbl_leds_on > 0)
			num_kpbl_leds_on--;

		if (!num_kpbl_leds_on) {
			rc = qpnp_led_masked_write(led, KPDBL_ENABLE(led->base),
					KPDBL_MODULE_EN_MASK, KPDBL_MODULE_DIS);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
					"Failed to write led enable reg\n");
				return rc;
			}
		}
	}

	led->kpdbl_cfg->pwm_cfg->blinking = false;

	qpnp_dump_regs(led, kpdbl_debug_regs, ARRAY_SIZE(kpdbl_debug_regs));

	return 0;
}
#if SHENQI_RGB

static int qpnp_rgb_set(struct qpnp_led_data *led)
{
        int duty_us;
        int rc;

        if (led->cdev.brightness) {
                if (led->rgb_cfg->mode == PWM_MODE) {
                        duty_us = (led->rgb_cfg->pwm_period_us *
                                led->cdev.brightness) / LED_FULL;
                        rc = pwm_config_us(led->rgb_cfg->pwm_dev, duty_us,
                                        led->rgb_cfg->pwm_period_us);
                        if (rc < 0) {
                                dev_err(&led->spmi_dev->dev,
                                        "pwm config failed\n");
                                return rc;
                        }
                }
#if 1
                if (led->rgb_cfg->mode == LPG_MODE) {

                        rc = pwm_lut_config(led->rgb_cfg->pwm_dev,
                                PM_PWM_PERIOD_MIN, /* ignored by hardware */
                                led->rgb_cfg->duty_cycles->duty_pcts,
                                led->rgb_cfg->lut_params);
                        if (rc < 0) {
                                dev_err(&led->spmi_dev->dev, "Failed to " \
                                        "configure pwm LUT\n");
                                return rc;
                        }
                }
#endif
                rc = qpnp_led_masked_write(led,
                        RGB_LED_EN_CTL(led->base),
                        led->rgb_cfg->enable, led->rgb_cfg->enable);
                if (rc) {
                        dev_err(&led->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
                rc = pwm_enable(led->rgb_cfg->pwm_dev);
                if (rc < 0) {
                        dev_err(&led->spmi_dev->dev, "pwm enable failed\n");
                        return rc;
                }
        } else {
                pwm_disable(led->rgb_cfg->pwm_dev);
                rc = qpnp_led_masked_write(led,
                        RGB_LED_EN_CTL(led->base),
                        led->rgb_cfg->enable, RGB_LED_DISABLE);
                if (rc) {
                        dev_err(&led->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
        }

        qpnp_dump_regs(led, rgb_pwm_debug_regs, ARRAY_SIZE(rgb_pwm_debug_regs));

        return 0;
}
#else
static int qpnp_rgb_set(struct qpnp_led_data *led)
{
        int duty_us;
        int rc;

        if (led->cdev.brightness) {
                if (!led->rgb_cfg->pwm_cfg->blinking)
                        led->rgb_cfg->pwm_cfg->mode =
                                led->rgb_cfg->pwm_cfg->default_mode;
                if (led->rgb_cfg->pwm_cfg->mode == PWM_MODE) {
                        duty_us = (led->rgb_cfg->pwm_cfg->pwm_period_us *
                                led->cdev.brightness) / LED_FULL;
                        rc = pwm_config_us(led->rgb_cfg->pwm_cfg->pwm_dev, duty_us,
                                        led->rgb_cfg->pwm_cfg->pwm_period_us);
                        if (rc < 0) {
                                dev_err(&led->spmi_dev->dev,
                                        "pwm config failed\n");
                                return rc;
                        }
                }
                rc = qpnp_led_masked_write(led,
                        RGB_LED_EN_CTL(led->base),
                        led->rgb_cfg->enable, led->rgb_cfg->enable);
                if (rc) {
                        dev_err(&led->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }

                rc = pwm_enable(led->rgb_cfg->pwm_cfg->pwm_dev);
                if (rc < 0) {
                        dev_err(&led->spmi_dev->dev, "pwm enable failed\n");
                        return rc;
                }
        } else {
                led->rgb_cfg->pwm_cfg->mode =
                        led->rgb_cfg->pwm_cfg->default_mode;
                pwm_disable(led->rgb_cfg->pwm_cfg->pwm_dev);
                rc = qpnp_led_masked_write(led,
                        RGB_LED_EN_CTL(led->base),
                        led->rgb_cfg->enable, RGB_LED_DISABLE);
                if (rc) {
                        dev_err(&led->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
        }

        led->rgb_cfg->pwm_cfg->blinking = false;
        qpnp_dump_regs(led, rgb_pwm_debug_regs, ARRAY_SIZE(rgb_pwm_debug_regs));

        return 0;
}
#endif

static void qpnp_led_set(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	struct qpnp_led_data *led;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);
	if (value < LED_OFF) {
		dev_err(&led->spmi_dev->dev, "Invalid brightness value\n");
		return;
	}

	if (value > led->cdev.max_brightness)
		value = led->cdev.max_brightness;

	led->cdev.brightness = value;
	if (led->in_order_command_processing)
		queue_work(led->workqueue, &led->work);
	else
		schedule_work(&led->work);
}

static void __qpnp_led_work(struct qpnp_led_data *led,
				enum led_brightness value)
{
	int rc;

	if (led->id == QPNP_ID_FLASH1_LED0 || led->id == QPNP_ID_FLASH1_LED1)
		mutex_lock(&flash_lock);
	else
		mutex_lock(&led->lock);

	switch (led->id) {
	case QPNP_ID_WLED:
		rc = qpnp_wled_set(led);
		if (rc < 0)
			dev_err(&led->spmi_dev->dev,
				"WLED set brightness failed (%d)\n", rc);
		break;
	case QPNP_ID_FLASH1_LED0:
	case QPNP_ID_FLASH1_LED1:
		rc = qpnp_flash_set(led);
		if (rc < 0)
			dev_err(&led->spmi_dev->dev,
				"FLASH set brightness failed (%d)\n", rc);
		break;
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		rc = qpnp_rgb_set(led);
		if (rc < 0)
			dev_err(&led->spmi_dev->dev,
				"RGB set brightness failed (%d)\n", rc);
		break;
	case QPNP_ID_LED_MPP:
		rc = qpnp_mpp_set(led);
		if (rc < 0)
			dev_err(&led->spmi_dev->dev,
					"MPP set brightness failed (%d)\n", rc);
		break;
	case QPNP_ID_KPDBL:
		rc = qpnp_kpdbl_set(led);
		if (rc < 0)
			dev_err(&led->spmi_dev->dev,
				"KPDBL set brightness failed (%d)\n", rc);
		break;
	default:
		dev_err(&led->spmi_dev->dev, "Invalid LED(%d)\n", led->id);
		break;
	}
	if (led->id == QPNP_ID_FLASH1_LED0 || led->id == QPNP_ID_FLASH1_LED1)
		mutex_unlock(&flash_lock);
	else
		mutex_unlock(&led->lock);

}

static void qpnp_led_work(struct work_struct *work)
{
	struct qpnp_led_data *led = container_of(work,
					struct qpnp_led_data, work);

	__qpnp_led_work(led, led->cdev.brightness);

	return;
}

static int __devinit qpnp_led_set_max_brightness(struct qpnp_led_data *led)
{
	switch (led->id) {
	case QPNP_ID_WLED:
		led->cdev.max_brightness = WLED_MAX_LEVEL;
		break;
	case QPNP_ID_FLASH1_LED0:
	case QPNP_ID_FLASH1_LED1:
		led->cdev.max_brightness = led->max_current;
		break;
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		led->cdev.max_brightness = RGB_MAX_LEVEL;
		break;
	case QPNP_ID_LED_MPP:
		if (led->mpp_cfg->pwm_mode == MANUAL_MODE)
			led->cdev.max_brightness = led->max_current;
		else
			led->cdev.max_brightness = MPP_MAX_LEVEL;
		break;
	case QPNP_ID_KPDBL:
		led->cdev.max_brightness = KPDBL_MAX_LEVEL;
		break;
	default:
		dev_err(&led->spmi_dev->dev, "Invalid LED(%d)\n", led->id);
		return -EINVAL;
	}

	return 0;
}

static enum led_brightness qpnp_led_get(struct led_classdev *led_cdev)
{
	struct qpnp_led_data *led;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	return led->cdev.brightness;
}

static void qpnp_led_turn_off_delayed(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct qpnp_led_data *led
		= container_of(dwork, struct qpnp_led_data, dwork);

	led->cdev.brightness = LED_OFF;
	qpnp_led_set(&led->cdev, led->cdev.brightness);
}

static void qpnp_led_turn_off(struct qpnp_led_data *led)
{
	INIT_DELAYED_WORK(&led->dwork, qpnp_led_turn_off_delayed);
	schedule_delayed_work(&led->dwork,
		msecs_to_jiffies(led->turn_off_delay_ms));
}

static int __devinit qpnp_wled_init(struct qpnp_led_data *led)
{
	int rc, i;
	u8 num_wled_strings;

	num_wled_strings = led->wled_cfg->num_strings;

	/* verify ranges */
	if (led->wled_cfg->ovp_val > WLED_OVP_27V) {
		dev_err(&led->spmi_dev->dev, "Invalid ovp value\n");
		return -EINVAL;
	}

	if (led->wled_cfg->boost_curr_lim > WLED_CURR_LIMIT_1680mA) {
		dev_err(&led->spmi_dev->dev, "Invalid boost current limit\n");
		return -EINVAL;
	}

	if (led->wled_cfg->cp_select > WLED_CP_SELECT_MAX) {
		dev_err(&led->spmi_dev->dev, "Invalid pole capacitance\n");
		return -EINVAL;
	}

	if ((led->max_current > WLED_MAX_CURR)) {
		dev_err(&led->spmi_dev->dev, "Invalid max current\n");
		return -EINVAL;
	}

	if ((led->wled_cfg->ctrl_delay_us % WLED_CTL_DLY_STEP) ||
		(led->wled_cfg->ctrl_delay_us > WLED_CTL_DLY_MAX)) {
		dev_err(&led->spmi_dev->dev, "Invalid control delay\n");
		return -EINVAL;
	}

	/* program over voltage protection threshold */
	rc = qpnp_led_masked_write(led, WLED_OVP_CFG_REG(led->base),
		WLED_OVP_VAL_MASK,
		(led->wled_cfg->ovp_val << WLED_OVP_VAL_BIT_SHFT));
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED OVP reg write failed(%d)\n", rc);
		return rc;
	}

	/* program current boost limit */
	rc = qpnp_led_masked_write(led, WLED_BOOST_LIMIT_REG(led->base),
		WLED_BOOST_LIMIT_MASK, led->wled_cfg->boost_curr_lim);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED boost limit reg write failed(%d)\n", rc);
		return rc;
	}

	/* program output feedback */
	rc = qpnp_led_masked_write(led, WLED_FDBCK_CTRL_REG(led->base),
		WLED_OP_FDBCK_MASK,
		(led->wled_cfg->op_fdbck << WLED_OP_FDBCK_BIT_SHFT));
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED fdbck ctrl reg write failed(%d)\n", rc);
		return rc;
	}

	/* program switch frequency */
	rc = qpnp_led_masked_write(led,
		WLED_SWITCHING_FREQ_REG(led->base),
		WLED_SWITCH_FREQ_MASK, led->wled_cfg->switch_freq);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"WLED switch freq reg write failed(%d)\n", rc);
		return rc;
	}

	/* program current sink */
	if (led->wled_cfg->cs_out_en) {
		rc = qpnp_led_masked_write(led, WLED_CURR_SINK_REG(led->base),
			WLED_CURR_SINK_MASK,
			(((1 << led->wled_cfg->num_strings) - 1)
			<< WLED_CURR_SINK_SHFT));
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED curr sink reg write failed(%d)\n", rc);
			return rc;
		}
	}

	/* program high pole capacitance */
	rc = qpnp_led_masked_write(led, WLED_HIGH_POLE_CAP_REG(led->base),
		WLED_CP_SELECT_MASK, led->wled_cfg->cp_select);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
				"WLED pole cap reg write failed(%d)\n", rc);
		return rc;
	}

	/* program modulator, current mod src and cabc */
	for (i = 0; i < num_wled_strings; i++) {
		rc = qpnp_led_masked_write(led, WLED_MOD_EN_REG(led->base, i),
			WLED_NO_MASK, WLED_EN_MASK);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED mod enable reg write failed(%d)\n", rc);
			return rc;
		}

		if (led->wled_cfg->dig_mod_gen_en) {
			rc = qpnp_led_masked_write(led,
				WLED_MOD_SRC_SEL_REG(led->base, i),
				WLED_NO_MASK, WLED_USE_EXT_GEN_MOD_SRC);
			if (rc) {
				dev_err(&led->spmi_dev->dev,
				"WLED dig mod en reg write failed(%d)\n", rc);
			}
		}

		rc = qpnp_led_masked_write(led,
			WLED_FULL_SCALE_REG(led->base, i), WLED_MAX_CURR_MASK,
			(u8)led->max_current);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"WLED max current reg write failed(%d)\n", rc);
			return rc;
		}

	}

	/* Reset WLED enable register */
	rc = qpnp_led_masked_write(led, WLED_MOD_CTRL_REG(led->base),
		WLED_8_BIT_MASK, WLED_BOOST_OFF);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"WLED write ctrl reg failed(%d)\n", rc);
		return rc;
	}

	/* dump wled registers */
	qpnp_dump_regs(led, wled_debug_regs, ARRAY_SIZE(wled_debug_regs));

	return 0;
}

static ssize_t led_mode_store(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	unsigned long state;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL;

	ret = kstrtoul(buf, 10, &state);
	if (ret)
		return ret;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	/* '1' to enable torch mode; '0' to switch to flash mode */
	if (state == 1)
		led->flash_cfg->torch_enable = true;
	else
		led->flash_cfg->torch_enable = false;

	return count;
}

static ssize_t led_strobe_type_store(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	unsigned long state;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL;

	ret = kstrtoul(buf, 10, &state);
	if (ret)
		return ret;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	/* '0' for sw strobe; '1' for hw strobe */
	if (state == 1)
		led->flash_cfg->strobe_type = 1;
	else
		led->flash_cfg->strobe_type = 0;

	return count;
}

static int qpnp_pwm_init(struct pwm_config_data *pwm_cfg,
					struct spmi_device *spmi_dev,
					const char *name)
{
	int rc, start_idx, idx_len, lut_max_size;

	if (pwm_cfg->pwm_channel != -1) {
		pwm_cfg->pwm_dev =
			pwm_request(pwm_cfg->pwm_channel, name);

		if (IS_ERR_OR_NULL(pwm_cfg->pwm_dev)) {
			dev_err(&spmi_dev->dev,
				"could not acquire PWM Channel %d, " \
				"error %ld\n",
				pwm_cfg->pwm_channel,
				PTR_ERR(pwm_cfg->pwm_dev));
			pwm_cfg->pwm_dev = NULL;
			return -ENODEV;
		}
#if SHENQI_KPD
if(!strcmp(name,"button-backlight"))
{printk("%s,button-backlight",__func__);
        pwm_dev_button1 = pwm_cfg->pwm_dev;
}

if(!strcmp(name,"button-backlight2"))
{printk("%s,button-backlight2",__func__);
        pwm_dev_button2 = pwm_cfg->pwm_dev;
}
#endif

		if (pwm_cfg->mode == LPG_MODE) {
			start_idx =
			pwm_cfg->duty_cycles->start_idx;
			idx_len =
			pwm_cfg->duty_cycles->num_duty_pcts;

			if (strnstr(name, "kpdbl", sizeof("kpdbl")))
				lut_max_size = PWM_GPLED_LUT_MAX_SIZE;
			else
				lut_max_size = PWM_LUT_MAX_SIZE;

			if (idx_len >= lut_max_size && start_idx) {
				dev_err(&spmi_dev->dev,
					"Wrong LUT size or index\n");
				return -EINVAL;
			}

			if ((start_idx + idx_len) > lut_max_size) {
				dev_err(&spmi_dev->dev,
					"Exceed LUT limit\n");
				return -EINVAL;
			}
			rc = pwm_lut_config(pwm_cfg->pwm_dev,
				pwm_cfg->pwm_period_us,
				pwm_cfg->duty_cycles->duty_pcts,
				pwm_cfg->lut_params);
			if (rc < 0) {
				dev_err(&spmi_dev->dev, "Failed to " \
					"configure pwm LUT\n");
				return rc;
			}
		}
	} else {
		dev_err(&spmi_dev->dev,
			"Invalid PWM channel\n");
		return -EINVAL;
	}

	return 0;
}

static ssize_t pwm_us_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 pwm_us;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_pwm_us;
	struct pwm_config_data *pwm_cfg;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	ret = kstrtou32(buf, 10, &pwm_us);
	if (ret)
		return ret;

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for pwm_us\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_pwm_us = pwm_cfg->pwm_period_us;

	pwm_cfg->pwm_period_us = pwm_us;
	pwm_free(pwm_cfg->pwm_dev);
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->pwm_period_us = previous_pwm_us;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new pwm_us value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t pause_lo_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 pause_lo;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_pause_lo;
	struct pwm_config_data *pwm_cfg;

	ret = kstrtou32(buf, 10, &pause_lo);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for pause lo\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_pause_lo = pwm_cfg->lut_params.lut_pause_lo;

	pwm_free(pwm_cfg->pwm_dev);
	pwm_cfg->lut_params.lut_pause_lo = pause_lo;
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->lut_params.lut_pause_lo = previous_pause_lo;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new pause lo value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t pause_hi_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 pause_hi;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_pause_hi;
	struct pwm_config_data *pwm_cfg;

	ret = kstrtou32(buf, 10, &pause_hi);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for pause hi\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_pause_hi = pwm_cfg->lut_params.lut_pause_hi;

	pwm_free(pwm_cfg->pwm_dev);
	pwm_cfg->lut_params.lut_pause_hi = pause_hi;
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->lut_params.lut_pause_hi = previous_pause_hi;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new pause hi value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t start_idx_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 start_idx;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_start_idx;
	struct pwm_config_data *pwm_cfg;

	ret = kstrtou32(buf, 10, &start_idx);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for start idx\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_start_idx = pwm_cfg->duty_cycles->start_idx;
	pwm_cfg->duty_cycles->start_idx = start_idx;
	pwm_cfg->lut_params.start_idx = pwm_cfg->duty_cycles->start_idx;
	pwm_free(pwm_cfg->pwm_dev);
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->duty_cycles->start_idx = previous_start_idx;
		pwm_cfg->lut_params.start_idx = pwm_cfg->duty_cycles->start_idx;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new start idx value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t ramp_step_ms_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 ramp_step_ms;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_ramp_step_ms;
	struct pwm_config_data *pwm_cfg;

	ret = kstrtou32(buf, 10, &ramp_step_ms);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for ramp step\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_ramp_step_ms = pwm_cfg->lut_params.ramp_step_ms;

	pwm_free(pwm_cfg->pwm_dev);
	pwm_cfg->lut_params.ramp_step_ms = ramp_step_ms;
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->lut_params.ramp_step_ms = previous_ramp_step_ms;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new ramp step value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t lut_flags_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	u32 lut_flags;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret;
	u32 previous_lut_flags;
	struct pwm_config_data *pwm_cfg;

	ret = kstrtou32(buf, 10, &lut_flags);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for lut flags\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	previous_lut_flags = pwm_cfg->lut_params.flags;

	pwm_free(pwm_cfg->pwm_dev);
	pwm_cfg->lut_params.flags = lut_flags;
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret) {
		pwm_cfg->lut_params.flags = previous_lut_flags;
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		qpnp_led_set(&led->cdev, led->cdev.brightness);
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm with new lut flags value\n");
		return ret;
	}
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;
}

static ssize_t duty_pcts_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	int num_duty_pcts = 0;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	char *buffer;
	ssize_t ret;
	int i = 0;
	int max_duty_pcts;
	struct pwm_config_data *pwm_cfg;
	u32 previous_num_duty_pcts;
	int value;
	int *previous_duty_pcts;

	led = container_of(led_cdev, struct qpnp_led_data, cdev);

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		pwm_cfg = led->mpp_cfg->pwm_cfg;
		max_duty_pcts = PWM_LUT_MAX_SIZE;
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		pwm_cfg = led->rgb_cfg->pwm_cfg;
		max_duty_pcts = PWM_LUT_MAX_SIZE;
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev,
			"Invalid LED id type for duty pcts\n");
		return -EINVAL;
	}

	if (pwm_cfg->mode == LPG_MODE)
		pwm_cfg->blinking = true;

	buffer = (char *)buf;

	for (i = 0; i < max_duty_pcts; i++) {
		if (buffer == NULL)
			break;
		ret = sscanf((const char *)buffer, "%u,%s", &value, buffer);
		pwm_cfg->old_duty_pcts[i] = value;
		num_duty_pcts++;
		if (ret <= 1)
			break;
	}

	if (num_duty_pcts >= max_duty_pcts) {
		dev_err(&led->spmi_dev->dev,
			"Number of duty pcts given exceeds max (%d)\n",
			max_duty_pcts);
		return -EINVAL;
	}

	previous_num_duty_pcts = pwm_cfg->duty_cycles->num_duty_pcts;
	previous_duty_pcts = pwm_cfg->duty_cycles->duty_pcts;

	pwm_cfg->duty_cycles->num_duty_pcts = num_duty_pcts;
	pwm_cfg->duty_cycles->duty_pcts = pwm_cfg->old_duty_pcts;
	pwm_cfg->old_duty_pcts = previous_duty_pcts;
	pwm_cfg->lut_params.idx_len = pwm_cfg->duty_cycles->num_duty_pcts;

	pwm_free(pwm_cfg->pwm_dev);
	ret = qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	if (ret)
		goto restore;

	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return count;

restore:
	dev_err(&led->spmi_dev->dev,
		"Failed to initialize pwm with new duty pcts value\n");
	pwm_cfg->duty_cycles->num_duty_pcts = previous_num_duty_pcts;
	pwm_cfg->old_duty_pcts = pwm_cfg->duty_cycles->duty_pcts;
	pwm_cfg->duty_cycles->duty_pcts = previous_duty_pcts;
	pwm_cfg->lut_params.idx_len = pwm_cfg->duty_cycles->num_duty_pcts;
	pwm_free(pwm_cfg->pwm_dev);
	qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
	qpnp_led_set(&led->cdev, led->cdev.brightness);
	return ret;
}

static void led_blink(struct qpnp_led_data *led,
			struct pwm_config_data *pwm_cfg)
{
	int rc;

	flush_work(&led->work);
	mutex_lock(&led->lock);
	if (pwm_cfg->use_blink) {
		if (led->cdev.brightness) {
			pwm_cfg->blinking = true;
			if (led->id == QPNP_ID_LED_MPP)
				led->mpp_cfg->pwm_mode = LPG_MODE;
			else if (led->id == QPNP_ID_KPDBL)
				led->kpdbl_cfg->pwm_mode = LPG_MODE;
			pwm_cfg->mode = LPG_MODE;
		} else {
			pwm_cfg->blinking = false;
			pwm_cfg->mode = pwm_cfg->default_mode;
			if (led->id == QPNP_ID_LED_MPP)
				led->mpp_cfg->pwm_mode = pwm_cfg->default_mode;
			else if (led->id == QPNP_ID_KPDBL)
				led->kpdbl_cfg->pwm_mode =
						pwm_cfg->default_mode;
		}
		pwm_free(pwm_cfg->pwm_dev);
		qpnp_pwm_init(pwm_cfg, led->spmi_dev, led->cdev.name);
		if (led->id == QPNP_ID_RGB_RED || led->id == QPNP_ID_RGB_GREEN
				|| led->id == QPNP_ID_RGB_BLUE) {
			rc = qpnp_rgb_set(led);
			if (rc < 0)
				dev_err(&led->spmi_dev->dev,
				"RGB set brightness failed (%d)\n", rc);
		} else if (led->id == QPNP_ID_LED_MPP) {
			rc = qpnp_mpp_set(led);
			if (rc < 0)
				dev_err(&led->spmi_dev->dev,
				"MPP set brightness failed (%d)\n", rc);
		} else if (led->id == QPNP_ID_KPDBL) {
			rc = qpnp_kpdbl_set(led);
			if (rc < 0)
				dev_err(&led->spmi_dev->dev,
				"KPDBL set brightness failed (%d)\n", rc);
		}
	}
	mutex_unlock(&led->lock);
}

static ssize_t blink_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct qpnp_led_data *led;
	unsigned long blinking;
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL;

	ret = kstrtoul(buf, 10, &blinking);
	if (ret)
		return ret;
	led = container_of(led_cdev, struct qpnp_led_data, cdev);
	led->cdev.brightness = blinking ? led->cdev.max_brightness : 0;

	switch (led->id) {
	case QPNP_ID_LED_MPP:
		led_blink(led, led->mpp_cfg->pwm_cfg);
		break;
#if !SHENQI_RGB
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		led_blink(led, led->rgb_cfg->pwm_cfg);
		break;
#endif 
	default:
		dev_err(&led->spmi_dev->dev, "Invalid LED id type for blink\n");
		return -EINVAL;
	}
	return count;
}

static DEVICE_ATTR(led_mode, 0664, NULL, led_mode_store);
static DEVICE_ATTR(strobe, 0664, NULL, led_strobe_type_store);
static DEVICE_ATTR(pwm_us, 0664, NULL, pwm_us_store);
static DEVICE_ATTR(pause_lo, 0664, NULL, pause_lo_store);
static DEVICE_ATTR(pause_hi, 0664, NULL, pause_hi_store);
static DEVICE_ATTR(start_idx, 0664, NULL, start_idx_store);
static DEVICE_ATTR(ramp_step_ms, 0664, NULL, ramp_step_ms_store);
static DEVICE_ATTR(lut_flags, 0664, NULL, lut_flags_store);
static DEVICE_ATTR(duty_pcts, 0664, NULL, duty_pcts_store);
static DEVICE_ATTR(blink, 0664, NULL, blink_store);

static struct attribute *led_attrs[] = {
	&dev_attr_led_mode.attr,
	&dev_attr_strobe.attr,
	NULL
};

static const struct attribute_group led_attr_group = {
	.attrs = led_attrs,
};

static struct attribute *pwm_attrs[] = {
	&dev_attr_pwm_us.attr,
	NULL
};

static struct attribute *lpg_attrs[] = {
	&dev_attr_pause_lo.attr,
	&dev_attr_pause_hi.attr,
	&dev_attr_start_idx.attr,
	&dev_attr_ramp_step_ms.attr,
	&dev_attr_lut_flags.attr,
	&dev_attr_duty_pcts.attr,
	NULL
};

static struct attribute *blink_attrs[] = {
	&dev_attr_blink.attr,
	NULL
};

static const struct attribute_group pwm_attr_group = {
	.attrs = pwm_attrs,
};

static const struct attribute_group lpg_attr_group = {
	.attrs = lpg_attrs,
};

static const struct attribute_group blink_attr_group = {
	.attrs = blink_attrs,
};

static int __devinit qpnp_flash_init(struct qpnp_led_data *led)
{
	int rc;

	led->flash_cfg->flash_on = false;

	rc = qpnp_led_masked_write(led,
		FLASH_LED_STROBE_CTRL(led->base),
		FLASH_STROBE_MASK, FLASH_DISABLE_ALL);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"LED %d flash write failed(%d)\n", led->id, rc);
		return rc;
	}

	/* Disable flash LED module */
	rc = qpnp_led_masked_write(led, FLASH_ENABLE_CONTROL(led->base),
		FLASH_ENABLE_MASK, FLASH_DISABLE_ALL);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Enable reg write failed(%d)\n", rc);
		return rc;
	}

	if (led->flash_cfg->torch_enable)
		return 0;

	/* Set headroom */
	rc = qpnp_led_masked_write(led, FLASH_HEADROOM(led->base),
		FLASH_HEADROOM_MASK, led->flash_cfg->headroom);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Headroom reg write failed(%d)\n", rc);
		return rc;
	}

	/* Set startup delay */
	rc = qpnp_led_masked_write(led,
		FLASH_STARTUP_DELAY(led->base), FLASH_STARTUP_DLY_MASK,
		led->flash_cfg->startup_dly);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Startup delay reg write failed(%d)\n", rc);
		return rc;
	}

	/* Set timer control - safety or watchdog */
	if (led->flash_cfg->safety_timer) {
		rc = qpnp_led_masked_write(led,
			FLASH_LED_TMR_CTRL(led->base),
			FLASH_TMR_MASK, FLASH_TMR_SAFETY);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"LED timer ctrl reg write failed(%d)\n",
				rc);
			return rc;
		}
	}

	/* Set Vreg force */
	rc = qpnp_led_masked_write(led,	FLASH_VREG_OK_FORCE(led->base),
		FLASH_VREG_MASK, FLASH_HW_VREG_OK);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Vreg OK reg write failed(%d)\n", rc);
		return rc;
	}

	/* Set self fault check */
	rc = qpnp_led_masked_write(led, FLASH_FAULT_DETECT(led->base),
		FLASH_FAULT_DETECT_MASK, FLASH_SELFCHECK_ENABLE);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Fault detect reg write failed(%d)\n", rc);
		return rc;
	}

	/* Set mask enable */
	rc = qpnp_led_masked_write(led, FLASH_MASK_ENABLE(led->base),
		FLASH_MASK_REG_MASK, FLASH_MASK_1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Mask enable reg write failed(%d)\n", rc);
		return rc;
	}

	/* Set current ramp */
	rc = qpnp_led_masked_write(led, FLASH_CURRENT_RAMP(led->base),
		FLASH_CURRENT_RAMP_MASK, FLASH_RAMP_STEP_27US);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Current ramp reg write failed(%d)\n", rc);
		return rc;
	}

	led->flash_cfg->strobe_type = 0;

	/* dump flash registers */
	qpnp_dump_regs(led, flash_debug_regs, ARRAY_SIZE(flash_debug_regs));

	return 0;
}

static int __devinit qpnp_kpdbl_init(struct qpnp_led_data *led)
{
	int rc;
	u8 val;

	/* select row source - vbst or vph */
	rc = spmi_ext_register_readl(led->spmi_dev->ctrl, led->spmi_dev->sid,
				KPDBL_ROW_SRC_SEL(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read from addr=%x, rc(%d)\n",
			KPDBL_ROW_SRC_SEL(led->base), rc);
		return rc;
	}

	if (led->kpdbl_cfg->row_src_vbst)
		val |= 1 << led->kpdbl_cfg->row_id;
	else
		val &= ~(1 << led->kpdbl_cfg->row_id);

	rc = spmi_ext_register_writel(led->spmi_dev->ctrl, led->spmi_dev->sid,
				KPDBL_ROW_SRC_SEL(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read from addr=%x, rc(%d)\n",
			KPDBL_ROW_SRC_SEL(led->base), rc);
		return rc;
	}

	/* row source enable */
	rc = spmi_ext_register_readl(led->spmi_dev->ctrl, led->spmi_dev->sid,
				KPDBL_ROW_SRC(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read from addr=%x, rc(%d)\n",
			KPDBL_ROW_SRC(led->base), rc);
		return rc;
	}

	if (led->kpdbl_cfg->row_src_en)
		val |= KPDBL_ROW_SCAN_EN_MASK | (1 << led->kpdbl_cfg->row_id);
	else
		val &= ~(1 << led->kpdbl_cfg->row_id);

	rc = spmi_ext_register_writel(led->spmi_dev->ctrl, led->spmi_dev->sid,
		KPDBL_ROW_SRC(led->base), &val, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to write to addr=%x, rc(%d)\n",
			KPDBL_ROW_SRC(led->base), rc);
		return rc;
	}

	/* enable module */
	rc = qpnp_led_masked_write(led, KPDBL_ENABLE(led->base),
		KPDBL_MODULE_EN_MASK, KPDBL_MODULE_EN);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Enable module write failed(%d)\n", rc);
		return rc;
	}

	rc = qpnp_pwm_init(led->kpdbl_cfg->pwm_cfg, led->spmi_dev,
				led->cdev.name);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Failed to initialize pwm\n");
		return rc;
	}

	if (led->kpdbl_cfg->always_on) {
		kpdbl_master = led->kpdbl_cfg->pwm_cfg->pwm_dev;
		kpdbl_master_period_us = led->kpdbl_cfg->pwm_cfg->pwm_period_us;
	}

	/* dump kpdbl registers */
	qpnp_dump_regs(led, kpdbl_debug_regs, ARRAY_SIZE(kpdbl_debug_regs));

	return 0;
}

#if SHENQI_RGB
static int __devinit qpnp_rgb_init(struct qpnp_led_data *led)
{
	int rc, start_idx, idx_len;

	rc = qpnp_led_masked_write(led, RGB_LED_SRC_SEL(led->base),
		RGB_LED_SRC_MASK, RGB_LED_SOURCE_VPH_PWR);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Failed to write led source select register\n");
		return rc;
	}

        if (led->rgb_cfg->pwm_channel != -1) {
                led->rgb_cfg->pwm_dev =
                        pwm_request(led->rgb_cfg->pwm_channel,
                                                led->cdev.name);

                if (IS_ERR_OR_NULL(led->rgb_cfg->pwm_dev)) {
                        dev_err(&led->spmi_dev->dev,
                                "could not acquire PWM Channel %d, " \
                                "error %ld\n",
                                led->rgb_cfg->pwm_channel,
                                PTR_ERR(led->rgb_cfg->pwm_dev));
                        led->rgb_cfg->pwm_dev = NULL;
                        return -ENODEV;
                }

                if (led->rgb_cfg->mode == LPG_MODE) {
                        start_idx =
                        led->rgb_cfg->duty_cycles->start_idx;
                        idx_len =
                        led->rgb_cfg->duty_cycles->num_duty_pcts;

			if (idx_len >= PWM_LUT_MAX_SIZE &&
					start_idx) {
				dev_err(&led->spmi_dev->dev,
					"Wrong LUT size or index\n");
				return -EINVAL;
			}
			if ((start_idx + idx_len) >
					PWM_LUT_MAX_SIZE) {
				dev_err(&led->spmi_dev->dev,
					"Exceed LUT limit\n");
				return -EINVAL;
			}
#if 0
			rc = pwm_lut_config(led->rgb_cfg->pwm_dev,
				PM_PWM_PERIOD_MIN, /* ignored by hardware */
				led->rgb_cfg->duty_cycles->duty_pcts,
				led->rgb_cfg->lut_params);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev, "Failed to " \
					"configure pwm LUT\n");
				return rc;
			
			}
#endif
		}
	} else {
		dev_err(&led->spmi_dev->dev,
			"Invalid PWM channel\n");
		return -EINVAL;
	}

        /* Initialize led for use in auto trickle charging mode */
        rc = qpnp_led_masked_write(led, RGB_LED_ATC_CTL(led->base),
                led->rgb_cfg->enable, led->rgb_cfg->enable);

        return 0;

}
#else
static int __devinit qpnp_rgb_init(struct qpnp_led_data *led)
{
        int rc;

        rc = qpnp_led_masked_write(led, RGB_LED_SRC_SEL(led->base),
                RGB_LED_SRC_MASK, RGB_LED_SOURCE_VPH_PWR);
        if (rc) {
                dev_err(&led->spmi_dev->dev,
                        "Failed to write led source select register\n");
                return rc;
        }

        rc = qpnp_pwm_init(led->rgb_cfg->pwm_cfg, led->spmi_dev,
                                led->cdev.name);
        if (rc) {
                dev_err(&led->spmi_dev->dev,
                        "Failed to initialize pwm\n");
                return rc;
        }
        /* Initialize led for use in auto trickle charging mode */
        rc = qpnp_led_masked_write(led, RGB_LED_ATC_CTL(led->base),
                led->rgb_cfg->enable, led->rgb_cfg->enable);

        return 0;
}
#endif

static int __devinit qpnp_mpp_init(struct qpnp_led_data *led)
{
	int rc;
	u8 val;

	if (led->max_current < LED_MPP_CURRENT_MIN ||
		led->max_current > LED_MPP_CURRENT_MAX) {
		dev_err(&led->spmi_dev->dev,
			"max current for mpp is not valid\n");
		return -EINVAL;
	}

	val = (led->mpp_cfg->current_setting / LED_MPP_CURRENT_PER_SETTING) - 1;

	if (val < 0)
		val = 0;

	rc = qpnp_led_masked_write(led, LED_MPP_VIN_CTRL(led->base),
		LED_MPP_VIN_MASK, led->mpp_cfg->vin_ctrl);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Failed to write led vin control reg\n");
		return rc;
	}

	rc = qpnp_led_masked_write(led, LED_MPP_SINK_CTRL(led->base),
		LED_MPP_SINK_MASK, val);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Failed to write sink control reg\n");
		return rc;
	}

	if (led->mpp_cfg->pwm_mode != MANUAL_MODE) {
		rc = qpnp_pwm_init(led->mpp_cfg->pwm_cfg, led->spmi_dev,
					led->cdev.name);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"Failed to initialize pwm\n");
			return rc;
		}
	}

	return 0;
}

static int __devinit qpnp_led_initialize(struct qpnp_led_data *led)
{
	int rc = 0;

	switch (led->id) {
	case QPNP_ID_WLED:
		rc = qpnp_wled_init(led);
		if (rc)
			dev_err(&led->spmi_dev->dev,
				"WLED initialize failed(%d)\n", rc);
		break;
	case QPNP_ID_FLASH1_LED0:
	case QPNP_ID_FLASH1_LED1:
		rc = qpnp_flash_init(led);
		if (rc)
			dev_err(&led->spmi_dev->dev,
				"FLASH initialize failed(%d)\n", rc);
		break;
	case QPNP_ID_RGB_RED:
	case QPNP_ID_RGB_GREEN:
	case QPNP_ID_RGB_BLUE:
		rc = qpnp_rgb_init(led);
		if (rc)
			dev_err(&led->spmi_dev->dev,
				"RGB initialize failed(%d)\n", rc);
		break;
	case QPNP_ID_LED_MPP:
		rc = qpnp_mpp_init(led);
		if (rc)
			dev_err(&led->spmi_dev->dev,
				"MPP initialize failed(%d)\n", rc);
		break;
	case QPNP_ID_KPDBL:
		rc = qpnp_kpdbl_init(led);
		if (rc)
			dev_err(&led->spmi_dev->dev,
				"KPDBL initialize failed(%d)\n", rc);
		break;
	default:
		dev_err(&led->spmi_dev->dev, "Invalid LED(%d)\n", led->id);
		return -EINVAL;
	}

	return rc;
}

static int __devinit qpnp_get_common_configs(struct qpnp_led_data *led,
				struct device_node *node)
{
	int rc;
	u32 val;
	const char *temp_string;

	led->cdev.default_trigger = LED_TRIGGER_DEFAULT;
	rc = of_property_read_string(node, "linux,default-trigger",
		&temp_string);
	if (!rc)
		led->cdev.default_trigger = temp_string;
	else if (rc != -EINVAL)
		return rc;

	led->default_on = false;
	rc = of_property_read_string(node, "qcom,default-state",
		&temp_string);
	if (!rc) {
		if (strncmp(temp_string, "on", sizeof("on")) == 0)
			led->default_on = true;
	} else if (rc != -EINVAL)
		return rc;

	led->turn_off_delay_ms = 0;
	rc = of_property_read_u32(node, "qcom,turn-off-delay-ms", &val);
	if (!rc)
		led->turn_off_delay_ms = val;
	else if (rc != -EINVAL)
		return rc;

	return 0;
}

/*
 * Handlers for alternative sources of platform_data
 */
static int __devinit qpnp_get_config_wled(struct qpnp_led_data *led,
				struct device_node *node)
{
	u32 val;
	int rc;

	led->wled_cfg = devm_kzalloc(&led->spmi_dev->dev,
				sizeof(struct wled_config_data), GFP_KERNEL);
	if (!led->wled_cfg) {
		dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	rc = spmi_ext_register_readl(led->spmi_dev->ctrl, led->spmi_dev->sid,
		PMIC_VERSION_REG, &led->wled_cfg->pmic_version, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read pmic ver, rc(%d)\n", rc);
	}

	led->wled_cfg->num_strings = WLED_DEFAULT_STRINGS;
	rc = of_property_read_u32(node, "qcom,num-strings", &val);
	if (!rc)
		led->wled_cfg->num_strings = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->ovp_val = WLED_DEFAULT_OVP_VAL;
	rc = of_property_read_u32(node, "qcom,ovp-val", &val);
	if (!rc)
		led->wled_cfg->ovp_val = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->boost_curr_lim = WLED_BOOST_LIM_DEFAULT;
	rc = of_property_read_u32(node, "qcom,boost-curr-lim", &val);
	if (!rc)
		led->wled_cfg->boost_curr_lim = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->cp_select = WLED_CP_SEL_DEFAULT;
	rc = of_property_read_u32(node, "qcom,cp-sel", &val);
	if (!rc)
		led->wled_cfg->cp_select = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->ctrl_delay_us = WLED_CTRL_DLY_DEFAULT;
	rc = of_property_read_u32(node, "qcom,ctrl-delay-us", &val);
	if (!rc)
		led->wled_cfg->ctrl_delay_us = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->op_fdbck = WLED_OP_FDBCK_DEFAULT;
	rc = of_property_read_u32(node, "qcom,op-fdbck", &val);
	if (!rc)
		led->wled_cfg->op_fdbck = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->switch_freq = WLED_SWITCH_FREQ_DEFAULT;
	rc = of_property_read_u32(node, "qcom,switch-freq", &val);
	if (!rc)
		led->wled_cfg->switch_freq = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->wled_cfg->dig_mod_gen_en =
		of_property_read_bool(node, "qcom,dig-mod-gen-en");

	led->wled_cfg->cs_out_en =
		of_property_read_bool(node, "qcom,cs-out-en");

	return 0;
}

static int __devinit qpnp_get_config_flash(struct qpnp_led_data *led,
				struct device_node *node, bool *reg_set)
{
	int rc;
	u32 val;

	led->flash_cfg = devm_kzalloc(&led->spmi_dev->dev,
				sizeof(struct flash_config_data), GFP_KERNEL);
	if (!led->flash_cfg) {
		dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	rc = spmi_ext_register_readl(led->spmi_dev->ctrl, led->spmi_dev->sid,
			FLASH_PERIPHERAL_SUBTYPE(led->base),
			&led->flash_cfg->peripheral_subtype, 1);
	if (rc) {
		dev_err(&led->spmi_dev->dev,
			"Unable to read from addr=%x, rc(%d)\n",
			FLASH_PERIPHERAL_SUBTYPE(led->base), rc);
	}

	led->flash_cfg->torch_enable =
		of_property_read_bool(node, "qcom,torch-enable");

	if (of_find_property(of_get_parent(node), "flash-wa-supply",
					NULL) && (!*reg_set)) {
		led->flash_cfg->flash_wa_reg =
			devm_regulator_get(&led->spmi_dev->dev, "flash-wa");
		if (IS_ERR_OR_NULL(led->flash_cfg->flash_wa_reg)) {
			rc = PTR_ERR(led->flash_cfg->flash_wa_reg);
			if (rc != EPROBE_DEFER) {
				dev_err(&led->spmi_dev->dev,
					"Flash wa regulator get failed(%d)\n",
					rc);
			}
		} else
			led->flash_cfg->flash_wa_reg_get = true;
	}
//dev_err(&led->spmi_dev->dev,
					//"qpnp_get_config_flash S led->id:%d ,*reg_se:%d, flash_reg_get:%d\n",
					//led->id,*reg_set,led->flash_cfg->flash_reg_get);
	if (led->id == QPNP_ID_FLASH1_LED0) {
		led->flash_cfg->enable_module = FLASH_ENABLE_LED_0;
		led->flash_cfg->current_addr = FLASH_LED_0_CURR(led->base);
		led->flash_cfg->trigger_flash = FLASH_LED_0_OUTPUT;
		if (!*reg_set) {
			led->flash_cfg->flash_boost_reg =
				regulator_get(&led->spmi_dev->dev,
							"flash-boost");
			if (IS_ERR(led->flash_cfg->flash_boost_reg)) {
				rc = PTR_ERR(led->flash_cfg->flash_boost_reg);
				dev_err(&led->spmi_dev->dev,
					"Regulator get failed(%d)\n", rc);
				goto error_get_flash_reg;
			}
			led->flash_cfg->flash_reg_get = true;
			*reg_set = true;
		} else
			led->flash_cfg->flash_reg_get = false;
#if 0
		if (led->flash_cfg->torch_enable) {
			led->flash_cfg->second_addr =
						FLASH_LED_1_CURR(led->base);
		}
#endif
	} else if (led->id == QPNP_ID_FLASH1_LED1) {
		led->flash_cfg->enable_module = FLASH_ENABLE_LED_1;
		led->flash_cfg->current_addr = FLASH_LED_1_CURR(led->base);
		led->flash_cfg->trigger_flash = FLASH_LED_1_OUTPUT;
		if (!*reg_set) {
			led->flash_cfg->flash_boost_reg =
					regulator_get(&led->spmi_dev->dev,
								"flash-boost");
			if (IS_ERR(led->flash_cfg->flash_boost_reg)) {
				rc = PTR_ERR(led->flash_cfg->flash_boost_reg);
				dev_err(&led->spmi_dev->dev,
					"Regulator get failed(%d)\n", rc);
				goto error_get_flash_reg;
			}
			led->flash_cfg->flash_reg_get = true;
			*reg_set = true;
		} else
			led->flash_cfg->flash_reg_get = false;
#if 0
		if (led->flash_cfg->torch_enable) {
			led->flash_cfg->second_addr =
						FLASH_LED_0_CURR(led->base);
		}
#endif
	} else {
		dev_err(&led->spmi_dev->dev, "Unknown flash LED name given\n");
		return -EINVAL;
	}

//dev_err(&led->spmi_dev->dev,
					//"qpnp_get_config_flash M led->id:%d ,*reg_se:%d, flash_reg_get:%d\n",
					//led->id,*reg_set,led->flash_cfg->flash_reg_get);
	if (led->flash_cfg->torch_enable) {
		if (led->id == QPNP_ID_FLASH1_LED0) {
			*reg_set = false;
		}
		if (of_find_property(of_get_parent(node), "torch-boost-supply",
									NULL)) {
			if(!*reg_set) {
				led->flash_cfg->torch_boost_reg =
					regulator_get(&led->spmi_dev->dev,
									"torch-boost");
				if (IS_ERR(led->flash_cfg->torch_boost_reg)) {
					rc = PTR_ERR(led->flash_cfg->torch_boost_reg);
					dev_err(&led->spmi_dev->dev,
						"Torch regulator get failed(%d)\n", rc);
					goto error_get_torch_reg;
				}
				led->flash_cfg->torch_reg_get = true;
				*reg_set = true;
			} else
				led->flash_cfg->torch_reg_get = false;
			led->flash_cfg->enable_module = FLASH_ENABLE_MODULE;
		} else
			led->flash_cfg->enable_module = FLASH_ENABLE_ALL;
		//led->flash_cfg->trigger_flash = FLASH_TORCH_OUTPUT;
	}

	rc = of_property_read_u32(node, "qcom,current", &val);
	if (!rc) {
		if (led->flash_cfg->torch_enable) {
			led->flash_cfg->current_prgm = (val *
				TORCH_MAX_LEVEL / led->max_current);
			return 0;
		}
		else
			led->flash_cfg->current_prgm = (val *
				FLASH_MAX_LEVEL / led->max_current);
	} else
		if (led->flash_cfg->torch_enable)
			goto error_get_torch_reg;
		else
			goto error_get_flash_reg;

	rc = of_property_read_u32(node, "qcom,headroom", &val);
	if (!rc)
		led->flash_cfg->headroom = (u8) val;
	else if (rc == -EINVAL)
		led->flash_cfg->headroom = HEADROOM_500mV;
	else
		goto error_get_flash_reg;

	rc = of_property_read_u32(node, "qcom,duration", &val);
	if (!rc)
		led->flash_cfg->duration = (u8)((val - 10) / 10);
	else if (rc == -EINVAL)
		led->flash_cfg->duration = FLASH_DURATION_200ms;
	else
		goto error_get_flash_reg;

	rc = of_property_read_u32(node, "qcom,clamp-curr", &val);
	if (!rc)
		led->flash_cfg->clamp_curr = (val *
				FLASH_MAX_LEVEL / led->max_current);
	else if (rc == -EINVAL)
		led->flash_cfg->clamp_curr = FLASH_CLAMP_200mA;
	else
		goto error_get_flash_reg;

	rc = of_property_read_u32(node, "qcom,startup-dly", &val);
	if (!rc)
		led->flash_cfg->startup_dly = (u8) val;
	else if (rc == -EINVAL)
		led->flash_cfg->startup_dly = DELAY_128us;
	else
		goto error_get_flash_reg;

	led->flash_cfg->safety_timer =
		of_property_read_bool(node, "qcom,safety-timer");

	return 0;

error_get_torch_reg:
	regulator_put(led->flash_cfg->torch_boost_reg);

error_get_flash_reg:
	regulator_put(led->flash_cfg->flash_boost_reg);
	return rc;

}

static int __devinit qpnp_get_config_pwm(struct pwm_config_data *pwm_cfg,
				struct spmi_device *spmi_dev,
				struct device_node *node)
{
	struct property *prop;
	int rc, i, lut_max_size;
	u32 val;
	u8 *temp_cfg;
	const char *led_label;

	rc = of_property_read_u32(node, "qcom,pwm-channel", &val);
	if (!rc)
		pwm_cfg->pwm_channel = val;
	else
		return rc;

	if (pwm_cfg->mode != MANUAL_MODE) {
		rc = of_property_read_u32(node, "qcom,pwm-us", &val);
		if (!rc)
			pwm_cfg->pwm_period_us = val;
		else
			return rc;
	}

	pwm_cfg->use_blink =
		of_property_read_bool(node, "qcom,use-blink");

	if (pwm_cfg->mode == LPG_MODE || pwm_cfg->use_blink) {
		pwm_cfg->duty_cycles =
			devm_kzalloc(&spmi_dev->dev,
			sizeof(struct pwm_duty_cycles), GFP_KERNEL);
		if (!pwm_cfg->duty_cycles) {
			dev_err(&spmi_dev->dev,
				"Unable to allocate memory\n");
			rc = -ENOMEM;
			goto bad_lpg_params;
		}

		prop = of_find_property(node, "qcom,duty-pcts",
			&pwm_cfg->duty_cycles->num_duty_pcts);
		if (!prop) {
			dev_err(&spmi_dev->dev, "Looking up property " \
				"node qcom,duty-pcts failed\n");
			rc =  -ENODEV;
			goto bad_lpg_params;
		} else if (!pwm_cfg->duty_cycles->num_duty_pcts) {
			dev_err(&spmi_dev->dev, "Invalid length of " \
				"duty pcts\n");
			rc =  -EINVAL;
			goto bad_lpg_params;
		}

		rc = of_property_read_string(node, "label", &led_label);

		if (rc < 0) {
			dev_err(&spmi_dev->dev,
				"Failure reading label, rc = %d\n", rc);
			return rc;
		}

		if (strcmp(led_label, "kpdbl") == 0)
			lut_max_size = PWM_GPLED_LUT_MAX_SIZE;
		else
			lut_max_size = PWM_LUT_MAX_SIZE;

		pwm_cfg->duty_cycles->duty_pcts =
			devm_kzalloc(&spmi_dev->dev,
			sizeof(int) * lut_max_size,
			GFP_KERNEL);
		if (!pwm_cfg->duty_cycles->duty_pcts) {
			dev_err(&spmi_dev->dev,
				"Unable to allocate memory\n");
			rc = -ENOMEM;
			goto bad_lpg_params;
		}

		pwm_cfg->old_duty_pcts =
			devm_kzalloc(&spmi_dev->dev,
			sizeof(int) * lut_max_size,
			GFP_KERNEL);
		if (!pwm_cfg->old_duty_pcts) {
			dev_err(&spmi_dev->dev,
				"Unable to allocate memory\n");
			rc = -ENOMEM;
			goto bad_lpg_params;
		}

		temp_cfg = devm_kzalloc(&spmi_dev->dev,
				pwm_cfg->duty_cycles->num_duty_pcts *
				sizeof(u8), GFP_KERNEL);
		if (!temp_cfg) {
			dev_err(&spmi_dev->dev, "Failed to allocate " \
				"memory for duty pcts\n");
			rc = -ENOMEM;
			goto bad_lpg_params;
		}

		memcpy(temp_cfg, prop->value,
			pwm_cfg->duty_cycles->num_duty_pcts);

		for (i = 0; i < pwm_cfg->duty_cycles->num_duty_pcts; i++)
			pwm_cfg->duty_cycles->duty_pcts[i] =
				(int) temp_cfg[i];

		rc = of_property_read_u32(node, "qcom,start-idx", &val);
		if (!rc) {
			pwm_cfg->lut_params.start_idx = val;
			pwm_cfg->duty_cycles->start_idx = val;
		} else
			goto bad_lpg_params;

		pwm_cfg->lut_params.lut_pause_hi = 0;
		rc = of_property_read_u32(node, "qcom,pause-hi", &val);
		if (!rc)
			pwm_cfg->lut_params.lut_pause_hi = val;
		else if (rc != -EINVAL)
			goto bad_lpg_params;

		pwm_cfg->lut_params.lut_pause_lo = 0;
		rc = of_property_read_u32(node, "qcom,pause-lo", &val);
		if (!rc)
			pwm_cfg->lut_params.lut_pause_lo = val;
		else if (rc != -EINVAL)
			goto bad_lpg_params;

		pwm_cfg->lut_params.ramp_step_ms =
				QPNP_LUT_RAMP_STEP_DEFAULT;
		rc = of_property_read_u32(node, "qcom,ramp-step-ms", &val);
		if (!rc)
			pwm_cfg->lut_params.ramp_step_ms = val;
		else if (rc != -EINVAL)
			goto bad_lpg_params;

		pwm_cfg->lut_params.flags = QPNP_LED_PWM_FLAGS;
		rc = of_property_read_u32(node, "qcom,lut-flags", &val);
		if (!rc)
			pwm_cfg->lut_params.flags = (u8) val;
		else if (rc != -EINVAL)
			goto bad_lpg_params;

		pwm_cfg->lut_params.idx_len =
			pwm_cfg->duty_cycles->num_duty_pcts;
	}
	return 0;

bad_lpg_params:
	pwm_cfg->use_blink = false;
	if (pwm_cfg->mode == PWM_MODE) {
		dev_err(&spmi_dev->dev, "LPG parameters not set for" \
			" blink mode, defaulting to PWM mode\n");
		return 0;
	}
	return rc;
};

static int qpnp_led_get_mode(const char *mode)
{
	if (strncmp(mode, "manual", strlen(mode)) == 0)
		return MANUAL_MODE;
	else if (strncmp(mode, "pwm", strlen(mode)) == 0)
		return PWM_MODE;
	else if (strncmp(mode, "lpg", strlen(mode)) == 0)
		return LPG_MODE;
	else
		return -EINVAL;
};

static int __devinit qpnp_get_config_kpdbl(struct qpnp_led_data *led,
				struct device_node *node)
{
	int rc;
	u32 val;
	u8 led_mode;
	const char *mode;

	led->kpdbl_cfg = devm_kzalloc(&led->spmi_dev->dev,
				sizeof(struct kpdbl_config_data), GFP_KERNEL);
	if (!led->kpdbl_cfg) {
		dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	rc = of_property_read_string(node, "qcom,mode", &mode);
	if (!rc) {
		led_mode = qpnp_led_get_mode(mode);
		if ((led_mode == MANUAL_MODE) || (led_mode == -EINVAL)) {
			dev_err(&led->spmi_dev->dev, "Selected mode not " \
				"supported for kpdbl.\n");
			return -EINVAL;
		}
		led->kpdbl_cfg->pwm_cfg = devm_kzalloc(&led->spmi_dev->dev,
					sizeof(struct pwm_config_data),
					GFP_KERNEL);
		if (!led->kpdbl_cfg->pwm_cfg) {
			dev_err(&led->spmi_dev->dev,
				"Unable to allocate memory\n");
			return -ENOMEM;
		}
		led->kpdbl_cfg->pwm_cfg->mode = led_mode;
		led->kpdbl_cfg->pwm_cfg->default_mode = led_mode;
	} else
		return rc;

	rc = qpnp_get_config_pwm(led->kpdbl_cfg->pwm_cfg, led->spmi_dev,  node);
	if (rc < 0)
		return rc;

	rc = of_property_read_u32(node, "qcom,row-id", &val);
	if (!rc)
		led->kpdbl_cfg->row_id = val;
	else
		return rc;

	led->kpdbl_cfg->row_src_vbst =
			of_property_read_bool(node, "qcom,row-src-vbst");

	led->kpdbl_cfg->row_src_en =
			of_property_read_bool(node, "qcom,row-src-en");

	led->kpdbl_cfg->always_on =
			of_property_read_bool(node, "qcom,always-on");

	return 0;
}

#if SHENQI_RGB
static int __devinit qpnp_get_config_rgb(struct qpnp_led_data *led,
				struct device_node *node)
{
        struct property *prop;
	int rc, i;
        u32 val;
        u8 *temp_cfg;
#if 1
        u8 *temp_cfg1;
#endif

	led->rgb_cfg = devm_kzalloc(&led->spmi_dev->dev,
				sizeof(struct rgb_config_data), GFP_KERNEL);
	if (!led->rgb_cfg) {
		dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	if (led->id == QPNP_ID_RGB_RED)
		led->rgb_cfg->enable = RGB_LED_ENABLE_RED;
	else if (led->id == QPNP_ID_RGB_GREEN)
		led->rgb_cfg->enable = RGB_LED_ENABLE_GREEN;
	else if (led->id == QPNP_ID_RGB_BLUE)
		led->rgb_cfg->enable = RGB_LED_ENABLE_BLUE;
	else
		return -EINVAL;

        rc = of_property_read_u32(node, "qcom,mode", &val);
        if (!rc)
                led->rgb_cfg->mode = (u8) val;
        else
                return rc;

        rc = of_property_read_u32(node, "qcom,pwm-channel", &val);
        if (!rc)
                led->rgb_cfg->pwm_channel = val;
        else
                return rc;
#if 1
        //if (led->rgb_cfg->mode == PWM_MODE) {
        if (1) {
#endif
                rc = of_property_read_u32(node, "qcom,pwm-us", &val);
                if (!rc)
                        led->rgb_cfg->pwm_period_us = val;
                else
                        return rc;
        }

#if 1
        //if (led->rgb_cfg->mode == LPG_MODE) {
        if (1) {
#endif
                led->rgb_cfg->duty_cycles =
                        devm_kzalloc(&led->spmi_dev->dev,
                        sizeof(struct pwm_duty_cycles), GFP_KERNEL);
                if (!led->rgb_cfg->duty_cycles) {
                        dev_err(&led->spmi_dev->dev,
                                "Unable to allocate memory\n");
                        return -ENOMEM;
                }

                prop = of_find_property(node, "qcom,duty-pcts",
                        &led->rgb_cfg->duty_cycles->num_duty_pcts);
                if (!prop) {
                        dev_err(&led->spmi_dev->dev, "Looking up property " \
                                "node qcom,duty-pcts failed\n");
                        return -ENODEV;
                } else if (!led->rgb_cfg->duty_cycles->num_duty_pcts) {
                        dev_err(&led->spmi_dev->dev, "Invalid length of " \
                                "duty pcts\n");
                        return -EINVAL;
                }

                led->rgb_cfg->duty_cycles->duty_pcts =
                        devm_kzalloc(&led->spmi_dev->dev,
                        sizeof(int) * led->rgb_cfg->duty_cycles->num_duty_pcts,
                        GFP_KERNEL);
                if (!led->rgb_cfg->duty_cycles->duty_pcts) {
                        dev_err(&led->spmi_dev->dev,
                                "Unable to allocate memory\n");
                        return -ENOMEM;
                }
                temp_cfg = devm_kzalloc(&led->spmi_dev->dev,
                                led->rgb_cfg->duty_cycles->num_duty_pcts *
                                sizeof(u8), GFP_KERNEL);
                if (!temp_cfg) {
                        dev_err(&led->spmi_dev->dev, "Failed to allocate " \
                                "memory for duty pcts\n");
                        return -ENOMEM;
                }

                memcpy(temp_cfg, prop->value,
                        led->rgb_cfg->duty_cycles->num_duty_pcts);

                for (i = 0; i < led->rgb_cfg->duty_cycles->num_duty_pcts; i++)
                        led->rgb_cfg->duty_cycles->duty_pcts[i] =
                                (int) temp_cfg[i];



                led->rgb_cfg->duty_cycles1 =
                        devm_kzalloc(&led->spmi_dev->dev,
                        sizeof(struct pwm_duty_cycles), GFP_KERNEL);
                if (!led->rgb_cfg->duty_cycles1) {
                        dev_err(&led->spmi_dev->dev,
                                "Unable to allocate memory\n");
                        return -ENOMEM;
                }

                prop = of_find_property(node, "qcom,duty-pcts1",
                        &led->rgb_cfg->duty_cycles1->num_duty_pcts);
                if (!prop) {
                        dev_err(&led->spmi_dev->dev, "Looking up property " \
                                "node qcom,duty-pcts failed\n");
                        return -ENODEV;
                } else if (!led->rgb_cfg->duty_cycles1->num_duty_pcts) {
                        dev_err(&led->spmi_dev->dev, "Invalid length of " \
                                "duty pcts\n");
                        return -EINVAL;
                }

                led->rgb_cfg->duty_cycles1->duty_pcts =
                        devm_kzalloc(&led->spmi_dev->dev,
                        sizeof(int) * led->rgb_cfg->duty_cycles1->num_duty_pcts,
                        GFP_KERNEL);
                if (!led->rgb_cfg->duty_cycles1->duty_pcts) {
                        dev_err(&led->spmi_dev->dev,
                                "Unable to allocate memory\n");
                        return -ENOMEM;
                }

                temp_cfg1 = devm_kzalloc(&led->spmi_dev->dev,
                                led->rgb_cfg->duty_cycles1->num_duty_pcts *
                                sizeof(u8), GFP_KERNEL);
                if (!temp_cfg1) {
                        dev_err(&led->spmi_dev->dev, "Failed to allocate " \
                                "memory for duty pcts\n");
                        return -ENOMEM;
                }

                memcpy(temp_cfg1, prop->value,
                        led->rgb_cfg->duty_cycles1->num_duty_pcts);

                for (i = 0; i < led->rgb_cfg->duty_cycles1->num_duty_pcts; i++)
                        led->rgb_cfg->duty_cycles1->duty_pcts[i] =
                                (int) temp_cfg1[i];
                rc = of_property_read_u32(node, "qcom,start-idx", &val);
                if (!rc) {
                        led->rgb_cfg->lut_params1.start_idx = (u8) val;
                        led->rgb_cfg->duty_cycles1->start_idx = (u8) val;
                } else
                        return rc;

                led->rgb_cfg->lut_params1.lut_pause_hi = 0;
                rc = of_property_read_u32(node, "qcom,pause-hi", &val);
                if (!rc)
                        led->rgb_cfg->lut_params1.lut_pause_hi = (u8) val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params1.lut_pause_lo = 0;
                rc = of_property_read_u32(node, "qcom,pause-lo", &val);
                if (!rc)
                        led->rgb_cfg->lut_params1.lut_pause_lo = (u8) val;
                else if (rc != -EINVAL)
                        return rc;
 
                led->rgb_cfg->lut_params1.ramp_step_ms =
                                QPNP_LUT_RAMP_STEP_DEFAULT1;
                rc = of_property_read_u32(node, "qcom,ramp-step-ms", &val);
                if (!rc)
                        led->rgb_cfg->lut_params1.ramp_step_ms = (u8) val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params1.flags = QPNP_LED_PWM_FLAGS;
                rc = of_property_read_u32(node, "qcom,lut-flags", &val);
                if (!rc)
                        led->rgb_cfg->lut_params1.flags = (u8) val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params1.idx_len =
                        led->rgb_cfg->duty_cycles1->num_duty_pcts;
                rc = of_property_read_u32(node, "qcom,start-idx", &val);
                if (!rc) {
                        led->rgb_cfg->lut_params.start_idx = val;
                        led->rgb_cfg->duty_cycles->start_idx = val;
                } else
                        return rc;

                led->rgb_cfg->lut_params.lut_pause_hi = 0;
                rc = of_property_read_u32(node, "qcom,pause-hi", &val);
                if (!rc)
                        led->rgb_cfg->lut_params.lut_pause_hi = val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params.lut_pause_lo = 0;
                rc = of_property_read_u32(node, "qcom,pause-lo", &val);
                if (!rc)
                        led->rgb_cfg->lut_params.lut_pause_lo = val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params.ramp_step_ms =
                                QPNP_LUT_RAMP_STEP_DEFAULT;
                rc = of_property_read_u32(node, "qcom,ramp-step-ms", &val);
                if (!rc)
                        led->rgb_cfg->lut_params.ramp_step_ms = val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params.flags = QPNP_LED_PWM_FLAGS;
                rc = of_property_read_u32(node, "qcom,lut-flags", &val);
                if (!rc)
                        led->rgb_cfg->lut_params.flags = val;
                else if (rc != -EINVAL)
                        return rc;

                led->rgb_cfg->lut_params.idx_len =
                        led->rgb_cfg->duty_cycles->num_duty_pcts;
        }

        return 0;
}
#else
static int __devinit qpnp_get_config_rgb(struct qpnp_led_data *led,
                                struct device_node *node)
{
        int rc;
        u8 led_mode;
        const char *mode;

        led->rgb_cfg = devm_kzalloc(&led->spmi_dev->dev,
                                sizeof(struct rgb_config_data), GFP_KERNEL);
        if (!led->rgb_cfg) {
                dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
                return -ENOMEM;
        }

        if (led->id == QPNP_ID_RGB_RED)
                led->rgb_cfg->enable = RGB_LED_ENABLE_RED;
        else if (led->id == QPNP_ID_RGB_GREEN)
                led->rgb_cfg->enable = RGB_LED_ENABLE_GREEN;
        else if (led->id == QPNP_ID_RGB_BLUE)
                led->rgb_cfg->enable = RGB_LED_ENABLE_BLUE;
        else
                return -EINVAL;

        rc = of_property_read_string(node, "qcom,mode", &mode);
        if (!rc) {
                led_mode = qpnp_led_get_mode(mode);
                if ((led_mode == MANUAL_MODE) || (led_mode == -EINVAL)) {
                        dev_err(&led->spmi_dev->dev, "Selected mode not " \
                                "supported for rgb.\n");
                        return -EINVAL;
                }
                led->rgb_cfg->pwm_cfg = devm_kzalloc(&led->spmi_dev->dev,
                                        sizeof(struct pwm_config_data),
                                        GFP_KERNEL);
                if (!led->rgb_cfg->pwm_cfg) {
                        dev_err(&led->spmi_dev->dev,
                                "Unable to allocate memory\n");
                        return -ENOMEM;
                }
                led->rgb_cfg->pwm_cfg->mode = led_mode;
                led->rgb_cfg->pwm_cfg->default_mode = led_mode;
        } else
                return rc;

        rc = qpnp_get_config_pwm(led->rgb_cfg->pwm_cfg, led->spmi_dev, node);
        if (rc < 0)
                return rc;

        return 0;
}
#endif
#if SHENQI_RGB
static ssize_t led_blink_show(struct device *dev,
                struct device_attribute *attr, char *buf)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);

        struct qpnp_led_data *led_dat =
                container_of(led_cdev, struct qpnp_led_data,cdev);
        return sprintf(buf, "%d\n", led_dat->led_blink);
}

static ssize_t led_blink_store(struct device *dev,
                struct device_attribute *attr, const char *buf, size_t count)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);
        unsigned long state;
        int ret = -EINVAL;
        int rc;
        struct qpnp_led_data *led_dat =
                container_of(led_cdev, struct qpnp_led_data,cdev);
        ret = kstrtoul(buf, 10, &state);
        if (ret)
                return ret;
        led_dat->led_blink = state;
        if(led_dat->led_blink == 0)
        {
        //      led_dat->is_blinking = false;
                pwm_disable(led_dat->rgb_cfg->pwm_dev);
                rc = qpnp_led_masked_write(led_dat,
                        RGB_LED_EN_CTL(led_dat->base),
                        led_dat->rgb_cfg->enable, RGB_LED_DISABLE);
                if (rc) {
                        dev_err(&led_dat->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
        }else if(led_dat->led_blink!=0)
        {
                printk("%s,led_dat is %d\n",__func__,led_dat->led_blink);
        //      led_dat->is_blinking = true;
        //              printk("%s,rgb mode %d\n",__func__,led_dat->rgb_cfg->mode);
                        rc = pwm_lut_config(led_dat->rgb_cfg->pwm_dev,
                                PM_PWM_PERIOD_MIN, /* ignored by hardware */
                                led_dat->rgb_cfg->duty_cycles1->duty_pcts,
                                led_dat->rgb_cfg->lut_params1);
                        if (rc < 0) {
                                dev_err(&led_dat->spmi_dev->dev, "Failed to " \
                                        "configure pwm LUT\n");
                                return rc;
                        }
                rc = qpnp_led_masked_write(led_dat,
                        RGB_LED_EN_CTL(led_dat->base),
                        led_dat->rgb_cfg->enable, led_dat->rgb_cfg->enable);
                if (rc) {
                        dev_err(&led_dat->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
                rc = pwm_enable(led_dat->rgb_cfg->pwm_dev);
}
        return count;
}

static ssize_t rgbled_mode_show(struct device *dev,
                struct device_attribute *attr, char *buf)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);

        struct qpnp_led_data *led_dat =
                container_of(led_cdev, struct qpnp_led_data,cdev);
        return sprintf(buf, "%d\n", led_dat->rgb_cfg->mode);
}
static ssize_t rgbled_mode_store(struct device *dev,
                        struct device_attribute *attr,
                        const char *buf, size_t count)
{
        struct qpnp_led_data *led;
        unsigned long state;
        struct led_classdev *led_cdev = dev_get_drvdata(dev);
        ssize_t ret = -EINVAL;
        ret = kstrtoul(buf, 10, &state);
        if (ret)
                return ret;

        led = container_of(led_cdev, struct qpnp_led_data, cdev);

        /* '1' to enable lpg mode; '0' to switch to pwm mode */
        if (state == 1)
                led->rgb_cfg->mode = 1;
        else
                led->rgb_cfg->mode = 0;
        pwm_change_mode(led->rgb_cfg->pwm_dev,led->rgb_cfg->mode);

        return count;
}
static ssize_t led_breath_show(struct device *dev,
                struct device_attribute *attr, char *buf)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);

        struct qpnp_led_data *led_dat =
                container_of(led_cdev, struct qpnp_led_data,cdev);
        return sprintf(buf, "%d\n", led_dat->led_breath);
}
static ssize_t led_breath_store(struct device *dev,
                        struct device_attribute *attr,
                        const char *buf, size_t count)
{
        struct qpnp_led_data *led_dat;
        unsigned long state;
        struct led_classdev *led_cdev = dev_get_drvdata(dev);
        ssize_t ret = -EINVAL;
        int rc;
        ret = kstrtoul(buf, 10, &state);
        if (ret)
                return ret;

        led_dat = container_of(led_cdev, struct qpnp_led_data, cdev);
        led_dat->led_breath = state;
        if(led_dat->led_breath==0)
        {
                pwm_disable(led_dat->rgb_cfg->pwm_dev);
                rc = qpnp_led_masked_write(led_dat,
                        RGB_LED_EN_CTL(led_dat->base),
                        led_dat->rgb_cfg->enable, RGB_LED_DISABLE);
                if (rc) {
                        dev_err(&led_dat->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
        }else
        {
                        ret = pwm_lut_config(led_dat->rgb_cfg->pwm_dev,
                                PM_PWM_PERIOD_MIN,
                                led_dat->rgb_cfg->duty_cycles->duty_pcts,
                                led_dat->rgb_cfg->lut_params);
                        if (ret < 0) {
                                dev_err(&led_dat->spmi_dev->dev, "Failed to " \
                                        "configure pwm LUT\n");
                                return ret;
                        }
                rc = qpnp_led_masked_write(led_dat,
                        RGB_LED_EN_CTL(led_dat->base),
                        led_dat->rgb_cfg->enable, led_dat->rgb_cfg->enable);
                if (rc) {
                        dev_err(&led_dat->spmi_dev->dev,
                                "Failed to write led enable reg\n");
                        return rc;
                }
                rc = pwm_enable(led_dat->rgb_cfg->pwm_dev);
        }
        return count;
}
static DEVICE_ATTR(rgbblink, 0644, led_blink_show, led_blink_store);
static DEVICE_ATTR(rgbled_mode, 0664, rgbled_mode_show, rgbled_mode_store);
static DEVICE_ATTR(rgbbreath, 0664, led_breath_show, led_breath_store);
static struct attribute *ledblink_attrs[] = {
        &dev_attr_rgbblink.attr,
        &dev_attr_rgbled_mode.attr,
        &dev_attr_rgbbreath.attr,
        NULL
};

static const struct attribute_group ledblink_attr_group = {
        .attrs = ledblink_attrs,
};
#endif

static int __devinit qpnp_get_config_mpp(struct qpnp_led_data *led,
		struct device_node *node)
{
	int rc;
	u32 val;
	u8 led_mode;
	const char *mode;

	led->mpp_cfg = devm_kzalloc(&led->spmi_dev->dev,
			sizeof(struct mpp_config_data), GFP_KERNEL);
	if (!led->mpp_cfg) {
		dev_err(&led->spmi_dev->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	led->mpp_cfg->current_setting = LED_MPP_CURRENT_MIN;
	rc = of_property_read_u32(node, "qcom,current-setting", &val);
	if (!rc) {
		if (led->mpp_cfg->current_setting < LED_MPP_CURRENT_MIN)
			led->mpp_cfg->current_setting = LED_MPP_CURRENT_MIN;
		else if (led->mpp_cfg->current_setting > LED_MPP_CURRENT_MAX)
			led->mpp_cfg->current_setting = LED_MPP_CURRENT_MAX;
		else
			led->mpp_cfg->current_setting = (u8) val;
	} else if (rc != -EINVAL)
		return rc;

	led->mpp_cfg->source_sel = LED_MPP_SOURCE_SEL_DEFAULT;
	rc = of_property_read_u32(node, "qcom,source-sel", &val);
	if (!rc)
		led->mpp_cfg->source_sel = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->mpp_cfg->mode_ctrl = LED_MPP_MODE_SINK;
	rc = of_property_read_u32(node, "qcom,mode-ctrl", &val);
	if (!rc)
		led->mpp_cfg->mode_ctrl = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->mpp_cfg->vin_ctrl = LED_MPP_VIN_CTRL_DEFAULT;
	rc = of_property_read_u32(node, "qcom,vin-ctrl", &val);
	if (!rc)
		led->mpp_cfg->vin_ctrl = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	led->mpp_cfg->min_brightness = 0;
	rc = of_property_read_u32(node, "qcom,min-brightness", &val);
	if (!rc)
		led->mpp_cfg->min_brightness = (u8) val;
	else if (rc != -EINVAL)
		return rc;

	rc = of_property_read_string(node, "qcom,mode", &mode);
	if (!rc) {
		led_mode = qpnp_led_get_mode(mode);
		led->mpp_cfg->pwm_mode = led_mode;
		if (led_mode == MANUAL_MODE)
			return MANUAL_MODE;
		else if (led_mode == -EINVAL) {
			dev_err(&led->spmi_dev->dev, "Selected mode not " \
				"supported for mpp.\n");
			return -EINVAL;
		}
		led->mpp_cfg->pwm_cfg = devm_kzalloc(&led->spmi_dev->dev,
					sizeof(struct pwm_config_data),
					GFP_KERNEL);
		if (!led->mpp_cfg->pwm_cfg) {
			dev_err(&led->spmi_dev->dev,
				"Unable to allocate memory\n");
			return -ENOMEM;
		}
		led->mpp_cfg->pwm_cfg->mode = led_mode;
		led->mpp_cfg->pwm_cfg->default_mode = led_mode;
	} else
		return rc;

	rc = qpnp_get_config_pwm(led->mpp_cfg->pwm_cfg, led->spmi_dev, node);
	if (rc < 0)
		return rc;

	return 0;
}

static int __devinit qpnp_leds_probe(struct spmi_device *spmi)
{
	struct qpnp_led_data *led, *led_array;
	struct resource *led_resource;
	struct device_node *node, *temp;
	int rc, i, num_leds = 0, parsed_leds = 0;
	const char *led_label;
	bool regulator_probe = false;

	node = spmi->dev.of_node;
	if (node == NULL)
		return -ENODEV;

	temp = NULL;
	while ((temp = of_get_next_child(node, temp)))
		num_leds++;

	if (!num_leds)
		return -ECHILD;

	led_array = devm_kzalloc(&spmi->dev,
		(sizeof(struct qpnp_led_data) * num_leds), GFP_KERNEL);
	if (!led_array) {
		dev_err(&spmi->dev, "Unable to allocate memory\n");
		return -ENOMEM;
	}

	for_each_child_of_node(node, temp) {
		led = &led_array[parsed_leds];
		led->num_leds = num_leds;
		led->spmi_dev = spmi;

		led_resource = spmi_get_resource(spmi, NULL, IORESOURCE_MEM, 0);
		if (!led_resource) {
			dev_err(&spmi->dev, "Unable to get LED base address\n");
			rc = -ENXIO;
			goto fail_id_check;
		}
		led->base = led_resource->start;

		rc = of_property_read_string(temp, "label", &led_label);
		if (rc < 0) {
			dev_err(&led->spmi_dev->dev,
				"Failure reading label, rc = %d\n", rc);
			goto fail_id_check;
		}

		rc = of_property_read_string(temp, "linux,name",
			&led->cdev.name);
		if (rc < 0) {
			dev_err(&led->spmi_dev->dev,
				"Failure reading led name, rc = %d\n", rc);
			goto fail_id_check;
		}

		rc = of_property_read_u32(temp, "qcom,max-current",
			&led->max_current);
		if (rc < 0) {
			dev_err(&led->spmi_dev->dev,
				"Failure reading max_current, rc =  %d\n", rc);
			goto fail_id_check;
		}

		rc = of_property_read_u32(temp, "qcom,id", &led->id);
		if (rc < 0) {
			dev_err(&led->spmi_dev->dev,
				"Failure reading led id, rc =  %d\n", rc);
			goto fail_id_check;
		}

		rc = qpnp_get_common_configs(led, temp);
		if (rc) {
			dev_err(&led->spmi_dev->dev,
				"Failure reading common led configuration," \
				" rc = %d\n", rc);
			goto fail_id_check;
		}

		led->cdev.brightness_set    = qpnp_led_set;
		led->cdev.brightness_get    = qpnp_led_get;

		if (strncmp(led_label, "wled", sizeof("wled")) == 0) {
			rc = qpnp_get_config_wled(led, temp);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
					"Unable to read wled config data\n");
				goto fail_id_check;
			}
		} else if (strncmp(led_label, "flash", sizeof("flash"))
				== 0) {
			if (!of_find_property(node, "flash-boost-supply", NULL))
				regulator_probe = true;
			rc = qpnp_get_config_flash(led, temp, &regulator_probe);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
					"Unable to read flash config data\n");
				goto fail_id_check;
			}
		} else if (strncmp(led_label, "rgb", sizeof("rgb")) == 0) {
			rc = qpnp_get_config_rgb(led, temp);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
					"Unable to read rgb config data\n");
				goto fail_id_check;
			}
		} else if (strncmp(led_label, "mpp", sizeof("mpp")) == 0) {
			rc = qpnp_get_config_mpp(led, temp);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
						"Unable to read mpp config data\n");
				goto fail_id_check;
			}
		} else if (strncmp(led_label, "kpdbl", sizeof("kpdbl")) == 0) {
			bitmap_zero(kpdbl_leds_in_use, NUM_KPDBL_LEDS);
			is_kpdbl_master_turn_on = false;
			rc = qpnp_get_config_kpdbl(led, temp);
			if (rc < 0) {
				dev_err(&led->spmi_dev->dev,
					"Unable to read kpdbl config data\n");
				goto fail_id_check;
			}
		} else {
			dev_err(&led->spmi_dev->dev, "No LED matching label\n");
			rc = -EINVAL;
			goto fail_id_check;
		}

		if (led->id != QPNP_ID_FLASH1_LED0 &&
					led->id != QPNP_ID_FLASH1_LED1)
			mutex_init(&led->lock);

		led->in_order_command_processing = of_property_read_bool
				(temp, "qcom,in-order-command-processing");

		if (led->in_order_command_processing) {
			/*
			 * the command order from user space needs to be
			 * maintained use ordered workqueue to prevent
			 * concurrency
			 */
			led->workqueue = alloc_ordered_workqueue
							("led_workqueue", 0);
			if (!led->workqueue) {
				rc = -ENOMEM;
				goto fail_id_check;
			}
		}

		INIT_WORK(&led->work, qpnp_led_work);

		rc =  qpnp_led_initialize(led);
		if (rc < 0)
			goto fail_id_check;

		rc = qpnp_led_set_max_brightness(led);
		if (rc < 0)
			goto fail_id_check;

		rc = led_classdev_register(&spmi->dev, &led->cdev);
		if (rc) {
			dev_err(&spmi->dev, "unable to register led %d,rc=%d\n",
						 led->id, rc);
			goto fail_id_check;
		}

		if (led->id == QPNP_ID_FLASH1_LED0 ||
			led->id == QPNP_ID_FLASH1_LED1) {
			rc = sysfs_create_group(&led->cdev.dev->kobj,
							&led_attr_group);
			if (rc)
				goto fail_id_check;

		}

		if (led->id == QPNP_ID_LED_MPP) {
			if (!led->mpp_cfg->pwm_cfg)
				break;
			if (led->mpp_cfg->pwm_cfg->mode == PWM_MODE) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&pwm_attr_group);
				if (rc)
					goto fail_id_check;
			}
			if (led->mpp_cfg->pwm_cfg->use_blink) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&blink_attr_group);
				if (rc)
					goto fail_id_check;

				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&lpg_attr_group);
				if (rc)
					goto fail_id_check;
			} else if (led->mpp_cfg->pwm_cfg->mode == LPG_MODE) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&lpg_attr_group);
				if (rc)
					goto fail_id_check;
			}
		} else if ((led->id == QPNP_ID_RGB_RED) ||
			(led->id == QPNP_ID_RGB_GREEN) ||
			(led->id == QPNP_ID_RGB_BLUE)) {
#if SHENQI_RGB
                        rc = sysfs_create_group(&led->cdev.dev->kobj,
                                                        &ledblink_attr_group);
                        if (rc)
                                goto fail_id_check;

#else

			if (led->rgb_cfg->pwm_cfg->mode == PWM_MODE) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&pwm_attr_group);
				if (rc)
					goto fail_id_check;
			}
			if (led->rgb_cfg->pwm_cfg->use_blink) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&blink_attr_group);
				if (rc)
					goto fail_id_check;

				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&lpg_attr_group);
				if (rc)
					goto fail_id_check;
			} else if (led->rgb_cfg->pwm_cfg->mode == LPG_MODE) {
				rc = sysfs_create_group(&led->cdev.dev->kobj,
					&lpg_attr_group);
				if (rc)
					goto fail_id_check;
			}
#endif 
		}

		/* configure default state */
		if (led->default_on) {
			led->cdev.brightness = led->cdev.max_brightness;
			__qpnp_led_work(led, led->cdev.brightness);
			if (led->turn_off_delay_ms > 0)
				qpnp_led_turn_off(led);
		} else
			led->cdev.brightness = LED_OFF;

		parsed_leds++;
	}
	dev_set_drvdata(&spmi->dev, led_array);
	return 0;

fail_id_check:
	for (i = 0; i < parsed_leds; i++) {
		if (led_array[i].id != QPNP_ID_FLASH1_LED0 &&
				led_array[i].id != QPNP_ID_FLASH1_LED1)
			mutex_destroy(&led_array[i].lock);
		if (led_array[i].in_order_command_processing)
			destroy_workqueue(led_array[i].workqueue);
		led_classdev_unregister(&led_array[i].cdev);
	}

	return rc;
}

static int __devexit qpnp_leds_remove(struct spmi_device *spmi)
{
	struct qpnp_led_data *led_array  = dev_get_drvdata(&spmi->dev);
	int i, parsed_leds = led_array->num_leds;

	for (i = 0; i < parsed_leds; i++) {
		cancel_work_sync(&led_array[i].work);
		if (led_array[i].id != QPNP_ID_FLASH1_LED0 &&
				led_array[i].id != QPNP_ID_FLASH1_LED1)
			mutex_destroy(&led_array[i].lock);

		if (led_array[i].in_order_command_processing)
			destroy_workqueue(led_array[i].workqueue);
		led_classdev_unregister(&led_array[i].cdev);
		switch (led_array[i].id) {
		case QPNP_ID_WLED:
			break;
		case QPNP_ID_FLASH1_LED0:
		case QPNP_ID_FLASH1_LED1:
			if (led_array[i].flash_cfg->flash_reg_get)
				regulator_put(led_array[i].flash_cfg-> \
							flash_boost_reg);
			if (led_array[i].flash_cfg->torch_enable)
				if (led_array[i].flash_cfg->torch_reg_get)
					regulator_put(led_array[i].flash_cfg->\
								torch_boost_reg);
			sysfs_remove_group(&led_array[i].cdev.dev->kobj,
							&led_attr_group);
			break;
		case QPNP_ID_RGB_RED:
		case QPNP_ID_RGB_GREEN:
		case QPNP_ID_RGB_BLUE:
#if SHENQI_RGB
                        sysfs_remove_group(&led_array[i].cdev.dev->kobj,
                                                        &ledblink_attr_group);
#else

			if (led_array[i].rgb_cfg->pwm_cfg->mode == PWM_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &pwm_attr_group);
			if (led_array[i].rgb_cfg->pwm_cfg->use_blink) {
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &blink_attr_group);
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &lpg_attr_group);
			} else if (led_array[i].rgb_cfg->pwm_cfg->mode\
					== LPG_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &lpg_attr_group);
#endif 
			break;
		case QPNP_ID_LED_MPP:
			if (!led_array[i].mpp_cfg->pwm_cfg)
				break;
			if (led_array[i].mpp_cfg->pwm_cfg->mode == PWM_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &pwm_attr_group);
			if (led_array[i].mpp_cfg->pwm_cfg->use_blink) {
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &blink_attr_group);
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &lpg_attr_group);
			} else if (led_array[i].mpp_cfg->pwm_cfg->mode\
					== LPG_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->\
					kobj, &lpg_attr_group);
			break;
		case QPNP_ID_KPDBL:
			if (led_array[i].kpdbl_cfg->pwm_cfg->mode == PWM_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->
					kobj, &pwm_attr_group);
			if (led_array[i].kpdbl_cfg->pwm_cfg->use_blink) {
				sysfs_remove_group(&led_array[i].cdev.dev->
					kobj, &blink_attr_group);
				sysfs_remove_group(&led_array[i].cdev.dev->
					kobj, &lpg_attr_group);
			} else if (led_array[i].kpdbl_cfg->pwm_cfg->mode
					== LPG_MODE)
				sysfs_remove_group(&led_array[i].cdev.dev->
					kobj, &lpg_attr_group);
			break;
		default:
			dev_err(&led_array[i].spmi_dev->dev,
					"Invalid LED(%d)\n",
					led_array[i].id);
			return -EINVAL;
		}
	}

	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id spmi_match_table[] = {
	{ .compatible = "qcom,leds-qpnp",},
	{ },
};
#else
#define spmi_match_table NULL
#endif

static struct spmi_driver qpnp_leds_driver = {
	.driver		= {
		.name	= "qcom,leds-qpnp",
		.of_match_table = spmi_match_table,
	},
	.probe		= qpnp_leds_probe,
	.remove		= __devexit_p(qpnp_leds_remove),
};

static int __init qpnp_led_init(void)
{
	return spmi_driver_register(&qpnp_leds_driver);
}
module_init(qpnp_led_init);

static void __exit qpnp_led_exit(void)
{
	spmi_driver_unregister(&qpnp_leds_driver);
}
module_exit(qpnp_led_exit);

MODULE_DESCRIPTION("QPNP LEDs driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("leds:leds-qpnp");

