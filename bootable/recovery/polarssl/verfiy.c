/*
 * =====================================================================================
 *
 *       Filename:  verfiy.c
 *
 *    Description:  verfiy update.zip
 *
 *        Version:  1.0
 *        Created:  12/03/2015 04:39:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *      Author:  wngwq14@zuk.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cutils/properties.h"
#include "rsa.h"
#include "md5.h"

static int macStrToMacNum(unsigned char *macstr, unsigned char *macAddrNum)
{
	int i = 0, j = 0, value;
	unsigned char str_tmp[3] = "\0";
	int len = 0;
    
	if(macstr == NULL || macAddrNum == NULL)
	{
		printf("Param is null!\n");
		return -1; 
	}

    len = strlen((char*)macstr);
    //ALOGD("macstr = %s\n", macstr);
    //ALOGD("macstr length = %d  (%d)\n", len, len/2);
    
	for(i = 0; i < len/2; i++)
	{
		memset(str_tmp, 0, sizeof(str_tmp));
		memcpy(str_tmp, macstr, 2*sizeof(char)); 
		macstr += 2;
		macAddrNum[i] = '\0';
		
		for(j = strlen((char *)str_tmp)-1; j >= 0; j--)
		{
            //ALOGD("str_tmp[%d] = %c\n", j, str_tmp[j]);
			switch(str_tmp[j])
			{
				case '0' : value = 0x0; break;
				case '1' : value = 0x1; break; 
				case '2' : value = 0x2; break;
				case '3' : value = 0x3; break;
				case '4' : value = 0x4; break;
				case '5' : value = 0x5; break; 
				case '6' : value = 0x6; break;
				case '7' : value = 0x7; break;
				case '8' : value = 0x8; break;
				case '9' : value = 0x9; break; 
				case 'a' : value = 0xa; break;
				case 'A' : value = 0xA; break;
				case 'b' : value = 0xb; break;
				case 'B' : value = 0xB; break;
				case 'c' : value = 0xc; break;
				case 'C' : value = 0xC; break;
				case 'd' : value = 0xd; break;
				case 'D' : value = 0xD; break;
				case 'e' : value = 0xe; break;
				case 'E' : value = 0xE; break;
				case 'f' : value = 0xf; break;
				case 'F' : value = 0xF; break;
				
				default :
					printf("error str_tmp[j] = %c \n!", str_tmp[j]);
					return -1;
			} 
			
			macAddrNum[i] |= (unsigned char )(value << ((strlen((char *)str_tmp)-1-j)*4));
		}
	} 
	
	return 0;
}

int signData(unsigned char* addr, unsigned int length)
{
    char serialno[256];
    unsigned char md5_buffer[16];
    unsigned char outBuffer[256];
    unsigned int  uiFileLen = 0;
    unsigned char SerMac[4] = {0};
    unsigned char Md5Mac[16] = {0};
    int ret = 0;
    int i = 0;
    
    memset(serialno, 0, 256);
    memset(md5_buffer, 0, 16);

    property_get("ro.boot.serialno", serialno, "");
    printf("[%s:%d] device serialno = %s\n", __func__, __LINE__, serialno);
    if(strlen(serialno) == 0){
        printf("[%s:%d] Get Serialno failed!\n", __func__, __LINE__);
        return 0;
    }

    macStrToMacNum((unsigned char*)serialno, SerMac);
    printf("[%s:%d] SerialNo[%2.2x-%2.2x-%2.2x-%2.2x]\n", 
                    __func__, __LINE__, SerMac[0], SerMac[1], SerMac[2], SerMac[3]);

    MD5_File((unsigned char*)addr, length, md5_buffer);
    printf("update.zip md5: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n", 
            md5_buffer[0], md5_buffer[1], md5_buffer[2], md5_buffer[3],
            md5_buffer[4], md5_buffer[5], md5_buffer[6], md5_buffer[7],
            md5_buffer[8], md5_buffer[9], md5_buffer[10], md5_buffer[11],
            md5_buffer[12], md5_buffer[13], md5_buffer[14], md5_buffer[15]);

    for(i = 0; i < 16; i++){
        //ALOGD("SerMac index = %d\n", i%4);
        Md5Mac[i] = md5_buffer[i] | SerMac[i%4];
    }
    
    printf("[%s:%d] md5 to sign [%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x]\n", 
            __func__, __LINE__, 
            Md5Mac[0], Md5Mac[1], Md5Mac[2], Md5Mac[3], Md5Mac[4], Md5Mac[5],
            Md5Mac[6], Md5Mac[7], Md5Mac[8], Md5Mac[9], Md5Mac[10], Md5Mac[11],
            Md5Mac[12], Md5Mac[13], Md5Mac[14], Md5Mac[15]);

    memset(outBuffer, 0, 256);
    ret = ras_sign(SIG_RSA_MD5, (unsigned char*)Md5Mac, 16, outBuffer, 256);
    if(0 != ret){
        printf("[%s:%d] ras_sign failed! ret = %d\n", __func__, __LINE__, ret);
        return 0;
    }
    printf("[%s:%d] ras_sign ok.\n", __func__, __LINE__);

    FILE* rsafd = fopen("/cache/ota/RsaData", "w+");
    if(rsafd == NULL){
        printf("[%s:%d] fail to open RsaData file, error info: %s \n", 
            __func__, __LINE__, strerror(errno));
        return 0;
    }

    ret = fwrite(outBuffer, 1, 256, rsafd);
    if(ret != 256)
    {
        printf("[%s:%d] fail to fwrite RsaData file, error info: %s \n", 
            __func__, __LINE__, strerror(errno));
        return 0;
    }
    fclose(rsafd);

    printf("[%s:%d] ok!\n", __func__, __LINE__);
	return 1;
}

int verfiyData(unsigned char* addr, unsigned int length)
{
    char serialno[256];
    unsigned char md5_buffer[16];
    unsigned char *pSignBuffer = NULL;
    unsigned int  uiFileLen = 0;
    unsigned char SerMac[4] = {0};
    unsigned char Md5Mac[16] = {0};
    int ret = 0;
    int i = 0;
    
    memset(serialno, 0, 256);
    memset(md5_buffer, 0, 16);

    property_get("ro.boot.serialno", serialno, "");
    printf("[%s:%d] device serialno = %s\n", __func__, __LINE__, serialno);
    if(strlen(serialno) == 0){
        printf("[%s:%d] Get Serialno failed!\n", __func__, __LINE__);
        return 0;
    }

    macStrToMacNum((unsigned char*)serialno, SerMac);
    printf("[%s:%d] SerialNo[%2.2x-%2.2x-%2.2x-%2.2x]\n", 
                __func__, __LINE__, SerMac[0], SerMac[1], SerMac[2], SerMac[3]);

    MD5_File((unsigned char*)addr, length, md5_buffer);
    printf("update.zip md5: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n", 
            md5_buffer[0], md5_buffer[1], md5_buffer[2], md5_buffer[3],
            md5_buffer[4], md5_buffer[5], md5_buffer[6], md5_buffer[7],
            md5_buffer[8], md5_buffer[9], md5_buffer[10], md5_buffer[11],
            md5_buffer[12], md5_buffer[13], md5_buffer[14], md5_buffer[15]);

    for(i = 0; i < 16; i++){
        //ALOGD("SerMac index = %d\n", i%4);
        Md5Mac[i] = md5_buffer[i] | SerMac[i%4];
    }
    printf("md5 to verfiy: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n", 
            Md5Mac[0], Md5Mac[1], Md5Mac[2], Md5Mac[3],
            Md5Mac[4], Md5Mac[5], Md5Mac[6], Md5Mac[7],
            Md5Mac[8], Md5Mac[9], Md5Mac[10], Md5Mac[11],
            Md5Mac[12], Md5Mac[13], Md5Mac[14], Md5Mac[15]);

    FILE* rsafd = fopen("/cache/ota/RsaData", "r");
    if(rsafd == NULL){
        printf("[%s:%d] fail to open RsaData file, error info: %s \n", 
            __func__, __LINE__, strerror(errno));
        return 0;
    }

    fseek(rsafd, 0, SEEK_END);
    uiFileLen = ftell(rsafd);
    printf("[%s:%d] RsaData file len is %d. \n", __func__, __LINE__, uiFileLen);
    rewind(rsafd);

    pSignBuffer = (unsigned char*)malloc(uiFileLen);
    if(NULL == pSignBuffer){
        printf("[%s:%d] malloc failed!! size = %d. \n", __func__, __LINE__, uiFileLen);
        fclose(rsafd);
        return 0;
    }

    ret = fread(pSignBuffer, 1, uiFileLen, rsafd);
    if(ret != (int)uiFileLen){
        printf("[%s:%d] fread failed!! read data length = %d. \n", __func__, __LINE__, ret);
        fclose(rsafd);
        free(pSignBuffer);
        pSignBuffer = NULL;
        return 0;
    }

    ret = ras_verify(SIG_RSA_MD5, Md5Mac, 16, pSignBuffer, uiFileLen);
    if(0 != ret){
        printf("[%s:%d] ras_verify failed! ret = %d. \n", __func__, __LINE__, ret);
        fclose(rsafd);
        free(pSignBuffer);
        pSignBuffer = NULL;
        return 0;
    }
    printf("[%s:%d] ras_verify ok.\n", __func__, __LINE__);

    fclose(rsafd);
    free(pSignBuffer);
    pSignBuffer = NULL;
    printf("[%s:%d] ok!\n", __func__, __LINE__);
    return 1;
}

