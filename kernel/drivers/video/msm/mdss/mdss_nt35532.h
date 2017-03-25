#ifndef MDSS_NT35532_H
#define MDSS_NT35532_H
#include "lcd_effect.h"
#include "mdss_panel.h"

/*********************************** head cmd *************************************/
//static char nt35532_addr_mode[] = {0x36,0x00};

static struct dsi_cmd_desc nt35532_packet_head_cmds[] = {
//	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35532_addr_mode)}, nt35532_addr_mode},
};
/*********************************** ce head cmd *************************************/
//struct dsi_ctrl_hdr cmd_head={0x29,1,0,0,0,2};
static char nt35532_normal_mode_cmd[] = {0xFF,0x00};

static char nt35532_ct_cold_cmd1[]=  {0xFF, 0x01};	//Gamma setting  R+
static char nt35532_ct_cold_cmd2[]=  {0xFB, 0x01};
static char nt35532_ct_cold_cmd3[]=  {0x75, 0x01};
static char nt35532_ct_cold_cmd4[]=  {0x76, 0x38};
static char nt35532_ct_cold_cmd5[]=  {0x77, 0x01};
static char nt35532_ct_cold_cmd6[]=  {0x78, 0x47};
static char nt35532_ct_cold_cmd7[]=  {0x79, 0x01};
static char nt35532_ct_cold_cmd8[]=  {0x7A, 0x50};
static char nt35532_ct_cold_cmd9[]=  {0x7B, 0x01};
static char nt35532_ct_cold_cmd10[]= {0x7C, 0x59};
static char nt35532_ct_cold_cmd11[]= {0x7D, 0x01};
static char nt35532_ct_cold_cmd12[]= {0x7E, 0x62};
static char nt35532_ct_cold_cmd13[]= {0x7F, 0x01};
static char nt35532_ct_cold_cmd14[]= {0x80, 0x6A};
static char nt35532_ct_cold_cmd15[]= {0x81, 0x01};
static char nt35532_ct_cold_cmd16[]= {0x82, 0x73};
static char nt35532_ct_cold_cmd17[]= {0x83, 0x01};
static char nt35532_ct_cold_cmd18[]= {0x84, 0x79};
static char nt35532_ct_cold_cmd19[]= {0x85, 0x01};
static char nt35532_ct_cold_cmd20[]= {0x86, 0x82};
static char nt35532_ct_cold_cmd21[]= {0x87, 0x01};
static char nt35532_ct_cold_cmd22[]= {0x88, 0x9B};
static char nt35532_ct_cold_cmd23[]= {0x89, 0x01};
static char nt35532_ct_cold_cmd24[]= {0x8A, 0xB1};
static char nt35532_ct_cold_cmd25[]= {0x8B, 0x01};
static char nt35532_ct_cold_cmd26[]= {0x8C, 0xD6};
static char nt35532_ct_cold_cmd27[]= {0x8D, 0x01};
static char nt35532_ct_cold_cmd28[]= {0x8E, 0xF5};
static char nt35532_ct_cold_cmd29[]= {0x8F, 0x02};
static char nt35532_ct_cold_cmd30[]= {0x90, 0x25};
static char nt35532_ct_cold_cmd31[]= {0x91, 0x02};
static char nt35532_ct_cold_cmd32[]= {0x92, 0x4F};
static char nt35532_ct_cold_cmd33[]= {0x93, 0x02};
static char nt35532_ct_cold_cmd34[]= {0x94, 0x51};
static char nt35532_ct_cold_cmd35[]= {0x95, 0x02};
static char nt35532_ct_cold_cmd36[]= {0x96, 0x7B};
static char nt35532_ct_cold_cmd37[]= {0x97, 0x02};
static char nt35532_ct_cold_cmd38[]= {0x98, 0xB1};
static char nt35532_ct_cold_cmd39[]= {0x99, 0x02};
static char nt35532_ct_cold_cmd40[]= {0x9A, 0xD4};
static char nt35532_ct_cold_cmd41[]= {0x9B, 0x03};
static char nt35532_ct_cold_cmd42[]= {0x9C, 0x05};
static char nt35532_ct_cold_cmd43[]= {0x9D, 0x03};
static char nt35532_ct_cold_cmd44[]= {0x9E, 0x25};
static char nt35532_ct_cold_cmd45[]= {0x9F, 0x03};
static char nt35532_ct_cold_cmd46[]= {0xA0, 0x4E};
static char nt35532_ct_cold_cmd47[]= {0xA2, 0x03};
static char nt35532_ct_cold_cmd48[]= {0xA3, 0x5B};
static char nt35532_ct_cold_cmd49[]= {0xA4, 0x03};
static char nt35532_ct_cold_cmd50[]= {0xA5, 0x69};
static char nt35532_ct_cold_cmd51[]= {0xA6, 0x03};
static char nt35532_ct_cold_cmd52[]= {0xA7, 0x78};
static char nt35532_ct_cold_cmd53[]= {0xA9, 0x03};
static char nt35532_ct_cold_cmd54[]= {0xAA, 0x89};
static char nt35532_ct_cold_cmd55[]= {0xAB, 0x03};
static char nt35532_ct_cold_cmd56[]= {0xAC, 0x9E};
static char nt35532_ct_cold_cmd57[]= {0xAD, 0x03};
static char nt35532_ct_cold_cmd58[]= {0xAE, 0xBA};
static char nt35532_ct_cold_cmd59[]= {0xAF, 0x03};
static char nt35532_ct_cold_cmd60[]= {0xB0, 0xDE};
static char nt35532_ct_cold_cmd61[]= {0xB1, 0x03};
static char nt35532_ct_cold_cmd62[]= {0xB2, 0xFF};
static char nt35532_ct_cold_cmd63[]= {0xB3, 0x01};//R-
static char nt35532_ct_cold_cmd64[]= {0xB4, 0x38};
static char nt35532_ct_cold_cmd65[]= {0xB5, 0x01};
static char nt35532_ct_cold_cmd66[]= {0xB6, 0x47};
static char nt35532_ct_cold_cmd67[]= {0xB7, 0x01};
static char nt35532_ct_cold_cmd68[]= {0xB8, 0x50};
static char nt35532_ct_cold_cmd69[]= {0xB9, 0x01};
static char nt35532_ct_cold_cmd70[]= {0xBA, 0x59};
static char nt35532_ct_cold_cmd71[]= {0xBB, 0x01};
static char nt35532_ct_cold_cmd72[]= {0xBC, 0x62};
static char nt35532_ct_cold_cmd73[]= {0xBD, 0x01};
static char nt35532_ct_cold_cmd74[]= {0xBE, 0x6A};
static char nt35532_ct_cold_cmd75[]= {0xBF, 0x01};
static char nt35532_ct_cold_cmd76[]= {0xC0, 0x73};
static char nt35532_ct_cold_cmd77[]= {0xC1, 0x01};
static char nt35532_ct_cold_cmd78[]= {0xC2, 0x79};
static char nt35532_ct_cold_cmd79[]= {0xC3, 0x01};
static char nt35532_ct_cold_cmd80[]= {0xC4, 0x82};
static char nt35532_ct_cold_cmd81[]= {0xC5, 0x01};
static char nt35532_ct_cold_cmd82[]= {0xC6, 0x9B};
static char nt35532_ct_cold_cmd83[]= {0xC7, 0x01};
static char nt35532_ct_cold_cmd84[]= {0xC8, 0xB1};
static char nt35532_ct_cold_cmd85[]= {0xC9, 0x01};
static char nt35532_ct_cold_cmd86[]= {0xCA, 0xD6};
static char nt35532_ct_cold_cmd87[]= {0xCB, 0x01};
static char nt35532_ct_cold_cmd88[]= {0xCC, 0xF5};
static char nt35532_ct_cold_cmd89[]= {0xCD, 0x02};
static char nt35532_ct_cold_cmd90[]= {0xCE, 0x25};
static char nt35532_ct_cold_cmd91[]= {0xCF, 0x02};
static char nt35532_ct_cold_cmd92[]= {0xD0, 0x4F};
static char nt35532_ct_cold_cmd93[]= {0xD1, 0x02};
static char nt35532_ct_cold_cmd94[]= {0xD2, 0x51};
static char nt35532_ct_cold_cmd95[]= {0xD3, 0x02};
static char nt35532_ct_cold_cmd96[]= {0xD4, 0x7B};
static char nt35532_ct_cold_cmd97[]= {0xD5, 0x02};
static char nt35532_ct_cold_cmd98[]= {0xD6, 0xB1};
static char nt35532_ct_cold_cmd99[]= {0xD7, 0x02};
static char nt35532_ct_cold_cmd100[]={0xD8, 0xD4};
static char nt35532_ct_cold_cmd101[]={0xD9, 0x03};
static char nt35532_ct_cold_cmd102[]={0xDA, 0x05};
static char nt35532_ct_cold_cmd103[]={0xDB, 0x03};
static char nt35532_ct_cold_cmd104[]={0xDC, 0x25};
static char nt35532_ct_cold_cmd105[]={0xDD, 0x03};
static char nt35532_ct_cold_cmd106[]={0xDE, 0x4E};
static char nt35532_ct_cold_cmd107[]={0xDF, 0x03};
static char nt35532_ct_cold_cmd108[]={0xE0, 0x5B};
static char nt35532_ct_cold_cmd109[]={0xE1, 0x03};
static char nt35532_ct_cold_cmd110[]={0xE2, 0x69};
static char nt35532_ct_cold_cmd111[]={0xE3, 0x03};
static char nt35532_ct_cold_cmd112[]={0xE4, 0x78};
static char nt35532_ct_cold_cmd113[]={0xE5, 0x03};
static char nt35532_ct_cold_cmd114[]={0xE6, 0x89};
static char nt35532_ct_cold_cmd115[]={0xE7, 0x03};
static char nt35532_ct_cold_cmd116[]={0xE8, 0x9E};
static char nt35532_ct_cold_cmd117[]={0xE9, 0x03};
static char nt35532_ct_cold_cmd118[]={0xEA, 0xBA};
static char nt35532_ct_cold_cmd119[]={0xEB, 0x03};
static char nt35532_ct_cold_cmd120[]={0xEC, 0xDE};
static char nt35532_ct_cold_cmd121[]={0xED, 0x03};
static char nt35532_ct_cold_cmd122[]={0xEE, 0xFF};
static char nt35532_ct_cold_cmd123[]={0xEF, 0x00};//G+
static char nt35532_ct_cold_cmd124[]={0xF0, 0x01};
static char nt35532_ct_cold_cmd125[]={0xF1, 0x00};
static char nt35532_ct_cold_cmd126[]={0xF2, 0x1F};
static char nt35532_ct_cold_cmd127[]={0xF3, 0x00};
static char nt35532_ct_cold_cmd128[]={0xF4, 0x67};
static char nt35532_ct_cold_cmd129[]={0xF5, 0x00};
static char nt35532_ct_cold_cmd130[]={0xF6, 0x93};
static char nt35532_ct_cold_cmd131[]={0xF7, 0x00};
static char nt35532_ct_cold_cmd132[]={0xF8, 0xB4};
static char nt35532_ct_cold_cmd133[]={0xF9, 0x00};
static char nt35532_ct_cold_cmd134[]={0xFA, 0xCF};
static char nt35532_ct_cold_cmd135[]={0xFF, 0x02};
static char nt35532_ct_cold_cmd136[]={0xFB, 0x01};
static char nt35532_ct_cold_cmd137[]={0x00, 0x00};
static char nt35532_ct_cold_cmd138[]={0x01, 0xE6};
static char nt35532_ct_cold_cmd139[]={0x02, 0x00};
static char nt35532_ct_cold_cmd140[]={0x03, 0xFA};
static char nt35532_ct_cold_cmd141[]={0x04, 0x01};
static char nt35532_ct_cold_cmd142[]={0x05, 0x0B};
static char nt35532_ct_cold_cmd143[]={0x06, 0x01};
static char nt35532_ct_cold_cmd144[]={0x07, 0x43};
static char nt35532_ct_cold_cmd145[]={0x08, 0x01};
static char nt35532_ct_cold_cmd146[]={0x09, 0x6B};
static char nt35532_ct_cold_cmd147[]={0x0A, 0x01};
static char nt35532_ct_cold_cmd148[]={0x0B, 0xA6};
static char nt35532_ct_cold_cmd149[]={0x0C, 0x01};
static char nt35532_ct_cold_cmd150[]={0x0D, 0xD0};
static char nt35532_ct_cold_cmd151[]={0x0E, 0x02};
static char nt35532_ct_cold_cmd152[]={0x0F, 0x0E};
static char nt35532_ct_cold_cmd153[]={0x10, 0x02};
static char nt35532_ct_cold_cmd154[]={0x11, 0x3F};
static char nt35532_ct_cold_cmd155[]={0x12, 0x02};
static char nt35532_ct_cold_cmd156[]={0x13, 0x40};
static char nt35532_ct_cold_cmd157[]={0x14, 0x02};
static char nt35532_ct_cold_cmd158[]={0x15, 0x6E};
static char nt35532_ct_cold_cmd159[]={0x16, 0x02};
static char nt35532_ct_cold_cmd160[]={0x17, 0xA5};
static char nt35532_ct_cold_cmd161[]={0x18, 0x02};
static char nt35532_ct_cold_cmd162[]={0x19, 0xC9};
static char nt35532_ct_cold_cmd163[]={0x1A, 0x02};
static char nt35532_ct_cold_cmd164[]={0x1B, 0xFA};
static char nt35532_ct_cold_cmd165[]={0x1C, 0x03};
static char nt35532_ct_cold_cmd166[]={0x1D, 0x1B};
static char nt35532_ct_cold_cmd167[]={0x1E, 0x03};
static char nt35532_ct_cold_cmd168[]={0x1F, 0x45};
static char nt35532_ct_cold_cmd169[]={0x20, 0x03};
static char nt35532_ct_cold_cmd170[]={0x21, 0x52};
static char nt35532_ct_cold_cmd171[]={0x22, 0x03};
static char nt35532_ct_cold_cmd172[]={0x23, 0x5F};
static char nt35532_ct_cold_cmd173[]={0x24, 0x03};
static char nt35532_ct_cold_cmd174[]={0x25, 0x6E};
static char nt35532_ct_cold_cmd175[]={0x26, 0x03};
static char nt35532_ct_cold_cmd176[]={0x27, 0x80};
static char nt35532_ct_cold_cmd177[]={0x28, 0x03};
static char nt35532_ct_cold_cmd178[]={0x29, 0x96};
static char nt35532_ct_cold_cmd179[]={0x2A, 0x03};
static char nt35532_ct_cold_cmd180[]={0x2B, 0xB0};
static char nt35532_ct_cold_cmd181[]={0x2D, 0x03};
static char nt35532_ct_cold_cmd182[]={0x2F, 0xD3};
static char nt35532_ct_cold_cmd183[]={0x30, 0x03};
static char nt35532_ct_cold_cmd184[]={0x31, 0xFF};
static char nt35532_ct_cold_cmd185[]={0x32, 0x00};
static char nt35532_ct_cold_cmd186[]={0x33, 0x01};//G-
static char nt35532_ct_cold_cmd187[]={0x34, 0x00};
static char nt35532_ct_cold_cmd188[]={0x35, 0x1F};
static char nt35532_ct_cold_cmd189[]={0x36, 0x00};
static char nt35532_ct_cold_cmd190[]={0x37, 0x67};
static char nt35532_ct_cold_cmd191[]={0x38, 0x00};
static char nt35532_ct_cold_cmd192[]={0x39, 0x93};
static char nt35532_ct_cold_cmd193[]={0x3A, 0x00};
static char nt35532_ct_cold_cmd194[]={0x3B, 0xB4};
static char nt35532_ct_cold_cmd195[]={0x3D, 0x00};
static char nt35532_ct_cold_cmd196[]={0x3F, 0xCF};
static char nt35532_ct_cold_cmd197[]={0x40, 0x00};
static char nt35532_ct_cold_cmd198[]={0x41, 0xE6};
static char nt35532_ct_cold_cmd199[]={0x42, 0x00};
static char nt35532_ct_cold_cmd200[]={0x43, 0xFA};
static char nt35532_ct_cold_cmd201[]={0x44, 0x01};
static char nt35532_ct_cold_cmd202[]={0x45, 0x0B};
static char nt35532_ct_cold_cmd203[]={0x46, 0x01};
static char nt35532_ct_cold_cmd204[]={0x47, 0x43};
static char nt35532_ct_cold_cmd205[]={0x48, 0x01};
static char nt35532_ct_cold_cmd206[]={0x49, 0x6B};
static char nt35532_ct_cold_cmd207[]={0x4A, 0x01};
static char nt35532_ct_cold_cmd208[]={0x4B, 0xA6};
static char nt35532_ct_cold_cmd209[]={0x4C, 0x01};
static char nt35532_ct_cold_cmd210[]={0x4D, 0xD0};
static char nt35532_ct_cold_cmd211[]={0x4E, 0x02};
static char nt35532_ct_cold_cmd212[]={0x4F, 0x0E};
static char nt35532_ct_cold_cmd213[]={0x50, 0x02};
static char nt35532_ct_cold_cmd214[]={0x51, 0x3F};
static char nt35532_ct_cold_cmd215[]={0x52, 0x02};
static char nt35532_ct_cold_cmd216[]={0x53, 0x40};
static char nt35532_ct_cold_cmd217[]={0x54, 0x02};
static char nt35532_ct_cold_cmd218[]={0x55, 0x6E};
static char nt35532_ct_cold_cmd219[]={0x56, 0x02};
static char nt35532_ct_cold_cmd220[]={0x58, 0xA5};
static char nt35532_ct_cold_cmd221[]={0x59, 0x02};
static char nt35532_ct_cold_cmd222[]={0x5A, 0xC9};
static char nt35532_ct_cold_cmd223[]={0x5B, 0x02};
static char nt35532_ct_cold_cmd224[]={0x5C, 0xFA};
static char nt35532_ct_cold_cmd225[]={0x5D, 0x03};
static char nt35532_ct_cold_cmd226[]={0x5E, 0x1B};
static char nt35532_ct_cold_cmd227[]={0x5F, 0x03};
static char nt35532_ct_cold_cmd228[]={0x60, 0x45};
static char nt35532_ct_cold_cmd229[]={0x61, 0x03};
static char nt35532_ct_cold_cmd230[]={0x62, 0x52};
static char nt35532_ct_cold_cmd231[]={0x63, 0x03};
static char nt35532_ct_cold_cmd232[]={0x64, 0x5F};
static char nt35532_ct_cold_cmd233[]={0x65, 0x03};
static char nt35532_ct_cold_cmd234[]={0x66, 0x6E};
static char nt35532_ct_cold_cmd235[]={0x67, 0x03};
static char nt35532_ct_cold_cmd236[]={0x68, 0x80};
static char nt35532_ct_cold_cmd237[]={0x69, 0x03};
static char nt35532_ct_cold_cmd238[]={0x6A, 0x96};
static char nt35532_ct_cold_cmd239[]={0x6B, 0x03};
static char nt35532_ct_cold_cmd240[]={0x6C, 0xB0};
static char nt35532_ct_cold_cmd241[]={0x6D, 0x03};
static char nt35532_ct_cold_cmd242[]={0x6E, 0xD3};
static char nt35532_ct_cold_cmd243[]={0x6F, 0x03};
static char nt35532_ct_cold_cmd244[]={0x70, 0xFF};
static char nt35532_ct_cold_cmd245[]={0x71, 0x01};
static char nt35532_ct_cold_cmd246[]={0x72, 0x48};	//B+
static char nt35532_ct_cold_cmd247[]={0x73, 0x01};
static char nt35532_ct_cold_cmd248[]={0x74, 0x4E};
static char nt35532_ct_cold_cmd249[]={0x75, 0x01};
static char nt35532_ct_cold_cmd250[]={0x76, 0x58};
static char nt35532_ct_cold_cmd251[]={0x77, 0x01};
static char nt35532_ct_cold_cmd252[]={0x78, 0x62};
static char nt35532_ct_cold_cmd253[]={0x79, 0x01};
static char nt35532_ct_cold_cmd254[]={0x7A, 0x6A};
static char nt35532_ct_cold_cmd255[]={0x7B, 0x01};
static char nt35532_ct_cold_cmd256[]={0x7C, 0x73};
static char nt35532_ct_cold_cmd257[]={0x7D, 0x01};
static char nt35532_ct_cold_cmd258[]={0x7E, 0x7A};
static char nt35532_ct_cold_cmd259[]={0x7F, 0x01};
static char nt35532_ct_cold_cmd260[]={0x80, 0x82};
static char nt35532_ct_cold_cmd261[]={0x81, 0x01};
static char nt35532_ct_cold_cmd262[]={0x82, 0x88};
static char nt35532_ct_cold_cmd263[]={0x83, 0x01};
static char nt35532_ct_cold_cmd264[]={0x84, 0xA2};
static char nt35532_ct_cold_cmd265[]={0x85, 0x01};
static char nt35532_ct_cold_cmd266[]={0x86, 0xB7};
static char nt35532_ct_cold_cmd267[]={0x87, 0x01};
static char nt35532_ct_cold_cmd268[]={0x88, 0xDB};
static char nt35532_ct_cold_cmd269[]={0x89, 0x01};
static char nt35532_ct_cold_cmd270[]={0x8A, 0xF9};
static char nt35532_ct_cold_cmd271[]={0x8B, 0x02};
static char nt35532_ct_cold_cmd272[]={0x8C, 0x28};
static char nt35532_ct_cold_cmd273[]={0x8D, 0x02};
static char nt35532_ct_cold_cmd274[]={0x8E, 0x53};
static char nt35532_ct_cold_cmd275[]={0x8F, 0x02};
static char nt35532_ct_cold_cmd276[]={0x90, 0x54};
static char nt35532_ct_cold_cmd277[]={0x91, 0x02};
static char nt35532_ct_cold_cmd278[]={0x92, 0x7E};
static char nt35532_ct_cold_cmd279[]={0x93, 0x02};
static char nt35532_ct_cold_cmd280[]={0x94, 0xB3};
static char nt35532_ct_cold_cmd281[]={0x95, 0x02};
static char nt35532_ct_cold_cmd282[]={0x96, 0xD7};
static char nt35532_ct_cold_cmd283[]={0x97, 0x03};
static char nt35532_ct_cold_cmd284[]={0x98, 0x08};
static char nt35532_ct_cold_cmd285[]={0x99, 0x03};
static char nt35532_ct_cold_cmd286[]={0x9A, 0x2A};
static char nt35532_ct_cold_cmd287[]={0x9B, 0x03};
static char nt35532_ct_cold_cmd288[]={0x9C, 0x59};
static char nt35532_ct_cold_cmd289[]={0x9D, 0x03};
static char nt35532_ct_cold_cmd290[]={0x9E, 0x6A};
static char nt35532_ct_cold_cmd291[]={0x9F, 0x03};
static char nt35532_ct_cold_cmd292[]={0xA0, 0x7F};
static char nt35532_ct_cold_cmd293[]={0xA2, 0x03};
static char nt35532_ct_cold_cmd294[]={0xA3, 0x9F};
static char nt35532_ct_cold_cmd295[]={0xA4, 0x03};
static char nt35532_ct_cold_cmd296[]={0xA5, 0xAE};
static char nt35532_ct_cold_cmd297[]={0xA6, 0x03};
static char nt35532_ct_cold_cmd298[]={0xA7, 0xBB};
static char nt35532_ct_cold_cmd299[]={0xA9, 0x03};
static char nt35532_ct_cold_cmd300[]={0xAA, 0xC8};
static char nt35532_ct_cold_cmd301[]={0xAB, 0x03};
static char nt35532_ct_cold_cmd302[]={0xAC, 0xDE};
static char nt35532_ct_cold_cmd303[]={0xAD, 0x03};
static char nt35532_ct_cold_cmd304[]={0xAE, 0xFF};
static char nt35532_ct_cold_cmd305[]={0xAF, 0x01};
static char nt35532_ct_cold_cmd306[]={0xB0, 0x48};//B-
static char nt35532_ct_cold_cmd307[]={0xB1, 0x01};
static char nt35532_ct_cold_cmd308[]={0xB2, 0x4E};
static char nt35532_ct_cold_cmd309[]={0xB3, 0x01};
static char nt35532_ct_cold_cmd310[]={0xB4, 0x58};
static char nt35532_ct_cold_cmd311[]={0xB5, 0x01};
static char nt35532_ct_cold_cmd312[]={0xB6, 0x62};
static char nt35532_ct_cold_cmd313[]={0xB7, 0x01};
static char nt35532_ct_cold_cmd314[]={0xB8, 0x6A};
static char nt35532_ct_cold_cmd315[]={0xB9, 0x01};
static char nt35532_ct_cold_cmd316[]={0xBA, 0x73};
static char nt35532_ct_cold_cmd317[]={0xBB, 0x01};
static char nt35532_ct_cold_cmd318[]={0xBC, 0x7A};
static char nt35532_ct_cold_cmd319[]={0xBD, 0x01};
static char nt35532_ct_cold_cmd320[]={0xBE, 0x82};
static char nt35532_ct_cold_cmd321[]={0xBF, 0x01};
static char nt35532_ct_cold_cmd322[]={0xC0, 0x88};
static char nt35532_ct_cold_cmd323[]={0xC1, 0x01};
static char nt35532_ct_cold_cmd324[]={0xC2, 0xA2};
static char nt35532_ct_cold_cmd325[]={0xC3, 0x01};
static char nt35532_ct_cold_cmd326[]={0xC4, 0xB7};
static char nt35532_ct_cold_cmd327[]={0xC5, 0x01};
static char nt35532_ct_cold_cmd328[]={0xC6, 0xDB};
static char nt35532_ct_cold_cmd329[]={0xC7, 0x01};
static char nt35532_ct_cold_cmd330[]={0xC8, 0xF9};
static char nt35532_ct_cold_cmd331[]={0xC9, 0x02};
static char nt35532_ct_cold_cmd332[]={0xCA, 0x28};
static char nt35532_ct_cold_cmd333[]={0xCB, 0x02};
static char nt35532_ct_cold_cmd334[]={0xCC, 0x53};
static char nt35532_ct_cold_cmd335[]={0xCD, 0x02};
static char nt35532_ct_cold_cmd336[]={0xCE, 0x54};
static char nt35532_ct_cold_cmd337[]={0xCF, 0x02};
static char nt35532_ct_cold_cmd338[]={0xD0, 0x7E};
static char nt35532_ct_cold_cmd339[]={0xD1, 0x02};
static char nt35532_ct_cold_cmd340[]={0xD2, 0xB3};
static char nt35532_ct_cold_cmd341[]={0xD3, 0x02};
static char nt35532_ct_cold_cmd342[]={0xD4, 0xD7};
static char nt35532_ct_cold_cmd343[]={0xD5, 0x03};
static char nt35532_ct_cold_cmd344[]={0xD6, 0x08};
static char nt35532_ct_cold_cmd345[]={0xD7, 0x03};
static char nt35532_ct_cold_cmd346[]={0xD8, 0x2A};
static char nt35532_ct_cold_cmd347[]={0xD9, 0x03};
static char nt35532_ct_cold_cmd348[]={0xDA, 0x59};
static char nt35532_ct_cold_cmd349[]={0xDB, 0x03};
static char nt35532_ct_cold_cmd350[]={0xDC, 0x6A};
static char nt35532_ct_cold_cmd351[]={0xDD, 0x03};
static char nt35532_ct_cold_cmd352[]={0xDE, 0x7F};
static char nt35532_ct_cold_cmd353[]={0xDF, 0x03};
static char nt35532_ct_cold_cmd354[]={0xE0, 0x9F};
static char nt35532_ct_cold_cmd355[]={0xE1, 0x03};
static char nt35532_ct_cold_cmd356[]={0xE2, 0xAE};
static char nt35532_ct_cold_cmd357[]={0xE3, 0x03};
static char nt35532_ct_cold_cmd358[]={0xE4, 0xBB};
static char nt35532_ct_cold_cmd359[]={0xE5, 0x03};
static char nt35532_ct_cold_cmd360[]={0xE6, 0xC8};
static char nt35532_ct_cold_cmd361[]={0xE7, 0x03};
static char nt35532_ct_cold_cmd362[]={0xE8, 0xDE};
static char nt35532_ct_cold_cmd363[]={0xE9, 0x03};
static char nt35532_ct_cold_cmd364[]={0xEA, 0xFF};

static struct dsi_cmd_desc nt35532_ct_cold_cmd[] = {
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd1},//Gamma setting  R+
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd2},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd3},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd4},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd5},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd6},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd7},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd8},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd9},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd10},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd11},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd12},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd13},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd14},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd15},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd16},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd17},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd18},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd19},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd20},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd21},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd22},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd23},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd24},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd25},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd26},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd27},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd28},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd29},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd30},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd31},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd32},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd33},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd34},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd35},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd36},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd37},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd38},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd39},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd40},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd41},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd42},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd43},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd44},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd45},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd46},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd47},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd48},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd49},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd50},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd51},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd52},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd53},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd54},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd55},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd56},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd57},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd58},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd59},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd60},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd61},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd62},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd63},//R-
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd64},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd65},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd66},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd67},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd68},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd69},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd70},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd71},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd72},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd73},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd74},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd75},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd76},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd77},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd78},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd79},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd80},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd81},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd82},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd83},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd84},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd85},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd86},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd87},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd88},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd89},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd90},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd91},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd92},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd93},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd94},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd95},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd96},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd97},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd98},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd99},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd100},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd101},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd102},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd103},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd104},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd105},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd106},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd107},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd108},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd109},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd110},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd111},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd112},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd113},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd114},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd115},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd116},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd117},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd118},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd119},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd120},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd121},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd122},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd123},//G+
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd124},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd125},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd126},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd127},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd128},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd129},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd130},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd131},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd132},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd133},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd134},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd135},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd136},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd137},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd138},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd139},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd140},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd141},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd142},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd143},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd144},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd145},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd146},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd147},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd148},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd149},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd150},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd151},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd152},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd153},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd154},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd155},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd156},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd157},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd158},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd159},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd160},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd161},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd162},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd163},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd164},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd165},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd166},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd167},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd168},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd169},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd170},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd171},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd172},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd173},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd174},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd175},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd176},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd177},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd178},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd179},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd180},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd181},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd182},
  {{0x29,1,0,0,0,2},nt35532_ct_cold_cmd183},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd184},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd185},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd186},//G-
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd187},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd188},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd189},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd190},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd191},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd192},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd193},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd194},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd195},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd196},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd197},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd198},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd199},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd200},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd201},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd202},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd203},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd204},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd205},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd206},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd207},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd208},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd209},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd210},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd211},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd212},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd213},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd214},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd215},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd216},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd217},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd218},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd219},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd220},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd221},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd222},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd223},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd224},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd225},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd226},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd227},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd228},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd229},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd230},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd231},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd232},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd233},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd234},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd235},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd236},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd237},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd238},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd239},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd240},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd241},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd242},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd243},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd244},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd245},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd246},	//B+
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd247},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd248},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd249},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd250},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd251},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd252},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd253},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd254},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd255},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd256},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd257},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd258},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd259},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd260},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd261},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd262},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd263},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd264},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd265},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd266},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd267},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd268},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd269},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd270},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd271},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd272},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd273},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd274},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd275},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd276},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd277},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd278},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd279},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd280},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd281},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd282},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd283},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd284},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd285},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd286},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd287},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd288},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd289},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd290},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd291},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd292},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd293},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd294},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd295},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd296},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd297},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd298},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd299},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd300},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd301},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd302},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd303},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd304},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd305},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd306},//B-
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd307},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd308},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd309},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd310},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd311},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd312},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd313},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd314},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd315},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd316},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd317},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd318},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd319},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd320},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd321},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd322},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd323},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd324},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd325},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd326},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd327},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd328},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd329},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd330},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd331},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd332},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd333},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd334},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd335},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd336},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd337},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd338},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd339},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd340},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd341},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd342},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd343},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd344},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd345},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd346},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd347},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd348},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd349},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd350},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd351},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd352},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd353},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd354},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd355},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd356},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd357},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd358},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd359},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd360},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd361},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd362},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd363},
  {{0x29,0,0,0,0,2},nt35532_ct_cold_cmd364},
  {{0x29,1,0,0,0,2},nt35532_normal_mode_cmd},
};

static char nt35532_ct_default_cmd1[]=  {0xFF, 0x01};		//Gamma setting  R+
static char nt35532_ct_default_cmd2[]=  {0xFB, 0x01};
static char nt35532_ct_default_cmd3[]=  {0x75, 0x01};
static char nt35532_ct_default_cmd4[]=  {0x76, 0x1C};
static char nt35532_ct_default_cmd5[]=  {0x77, 0x01};
static char nt35532_ct_default_cmd6[]=  {0x78, 0x24};
static char nt35532_ct_default_cmd7[]=  {0x79, 0x01};
static char nt35532_ct_default_cmd8[]=  {0x7A, 0x30};
static char nt35532_ct_default_cmd9[]=  {0x7B, 0x01};
static char nt35532_ct_default_cmd10[]= {0x7C, 0x3B};
static char nt35532_ct_default_cmd11[]= {0x7D, 0x01};
static char nt35532_ct_default_cmd12[]= {0x7E, 0x47};
static char nt35532_ct_default_cmd13[]= {0x7F, 0x01};
static char nt35532_ct_default_cmd14[]= {0x80, 0x50};
static char nt35532_ct_default_cmd15[]= {0x81, 0x01};
static char nt35532_ct_default_cmd16[]= {0x82, 0x5A};
static char nt35532_ct_default_cmd17[]= {0x83, 0x01};
static char nt35532_ct_default_cmd18[]= {0x84, 0x63};
static char nt35532_ct_default_cmd19[]= {0x85, 0x01};
static char nt35532_ct_default_cmd20[]= {0x86, 0x6B};
static char nt35532_ct_default_cmd21[]= {0x87, 0x01};
static char nt35532_ct_default_cmd22[]= {0x88, 0x89};
static char nt35532_ct_default_cmd23[]= {0x89, 0x01};
static char nt35532_ct_default_cmd24[]= {0x8A, 0xA3};
static char nt35532_ct_default_cmd25[]= {0x8B, 0x01};
static char nt35532_ct_default_cmd26[]= {0x8C, 0xCB};
static char nt35532_ct_default_cmd27[]= {0x8D, 0x01};
static char nt35532_ct_default_cmd28[]= {0x8E, 0xEC};
static char nt35532_ct_default_cmd29[]= {0x8F, 0x02};
static char nt35532_ct_default_cmd30[]= {0x90, 0x20};
static char nt35532_ct_default_cmd31[]= {0x91, 0x02};
static char nt35532_ct_default_cmd32[]= {0x92, 0x4B};
static char nt35532_ct_default_cmd33[]= {0x93, 0x02};
static char nt35532_ct_default_cmd34[]= {0x94, 0x4C};
static char nt35532_ct_default_cmd35[]= {0x95, 0x02};
static char nt35532_ct_default_cmd36[]= {0x96, 0x78};
static char nt35532_ct_default_cmd37[]= {0x97, 0x02};
static char nt35532_ct_default_cmd38[]= {0x98, 0xAF};
static char nt35532_ct_default_cmd39[]= {0x99, 0x02};
static char nt35532_ct_default_cmd40[]= {0x9A, 0xD2};
static char nt35532_ct_default_cmd41[]= {0x9B, 0x03};
static char nt35532_ct_default_cmd42[]= {0x9C, 0x03};
static char nt35532_ct_default_cmd43[]= {0x9D, 0x03};
static char nt35532_ct_default_cmd44[]= {0x9E, 0x23};
static char nt35532_ct_default_cmd45[]= {0x9F, 0x03};
static char nt35532_ct_default_cmd46[]= {0xA0, 0x4C};
static char nt35532_ct_default_cmd47[]= {0xA2, 0x03};
static char nt35532_ct_default_cmd48[]= {0xA3, 0x59};
static char nt35532_ct_default_cmd49[]= {0xA4, 0x03};
static char nt35532_ct_default_cmd50[]= {0xA5, 0x67};
static char nt35532_ct_default_cmd51[]= {0xA6, 0x03};
static char nt35532_ct_default_cmd52[]= {0xA7, 0x77};
static char nt35532_ct_default_cmd53[]= {0xA9, 0x03};
static char nt35532_ct_default_cmd54[]= {0xAA, 0x88};
static char nt35532_ct_default_cmd55[]= {0xAB, 0x03};
static char nt35532_ct_default_cmd56[]= {0xAC, 0x9D};
static char nt35532_ct_default_cmd57[]= {0xAD, 0x03};
static char nt35532_ct_default_cmd58[]= {0xAE, 0xB8};
static char nt35532_ct_default_cmd59[]= {0xAF, 0x03};
static char nt35532_ct_default_cmd60[]= {0xB0, 0xDE};
static char nt35532_ct_default_cmd61[]= {0xB1, 0x03};
static char nt35532_ct_default_cmd62[]= {0xB2, 0xFF};
static char nt35532_ct_default_cmd63[]= {0xB3, 0x01}; //R-
static char nt35532_ct_default_cmd64[]= {0xB4, 0x1C};
static char nt35532_ct_default_cmd65[]= {0xB5, 0x01};
static char nt35532_ct_default_cmd66[]= {0xB6, 0x24};
static char nt35532_ct_default_cmd67[]= {0xB7, 0x01};
static char nt35532_ct_default_cmd68[]= {0xB8, 0x30};
static char nt35532_ct_default_cmd69[]= {0xB9, 0x01};
static char nt35532_ct_default_cmd70[]= {0xBA, 0x3B};
static char nt35532_ct_default_cmd71[]= {0xBB, 0x01};
static char nt35532_ct_default_cmd72[]= {0xBC, 0x47};
static char nt35532_ct_default_cmd73[]= {0xBD, 0x01};
static char nt35532_ct_default_cmd74[]= {0xBE, 0x50};
static char nt35532_ct_default_cmd75[]= {0xBF, 0x01};
static char nt35532_ct_default_cmd76[]= {0xC0, 0x5A};
static char nt35532_ct_default_cmd77[]= {0xC1, 0x01};
static char nt35532_ct_default_cmd78[]= {0xC2, 0x63};
static char nt35532_ct_default_cmd79[]= {0xC3, 0x01};
static char nt35532_ct_default_cmd80[]= {0xC4, 0x6B};
static char nt35532_ct_default_cmd81[]= {0xC5, 0x01};
static char nt35532_ct_default_cmd82[]= {0xC6, 0x89};
static char nt35532_ct_default_cmd83[]= {0xC7, 0x01};
static char nt35532_ct_default_cmd84[]= {0xC8, 0xA3};
static char nt35532_ct_default_cmd85[]= {0xC9, 0x01};
static char nt35532_ct_default_cmd86[]= {0xCA, 0xCB};
static char nt35532_ct_default_cmd87[]= {0xCB, 0x01};
static char nt35532_ct_default_cmd88[]= {0xCC, 0xEC};
static char nt35532_ct_default_cmd89[]= {0xCD, 0x02};
static char nt35532_ct_default_cmd90[]= {0xCE, 0x20};
static char nt35532_ct_default_cmd91[]= {0xCF, 0x02};
static char nt35532_ct_default_cmd92[]= {0xD0, 0x4B};
static char nt35532_ct_default_cmd93[]= {0xD1, 0x02};
static char nt35532_ct_default_cmd94[]= {0xD2, 0x4C};
static char nt35532_ct_default_cmd95[]= {0xD3, 0x02};
static char nt35532_ct_default_cmd96[]= {0xD4, 0x78};
static char nt35532_ct_default_cmd97[]= {0xD5, 0x02};
static char nt35532_ct_default_cmd98[]= {0xD6, 0xAF};
static char nt35532_ct_default_cmd99[]= {0xD7, 0x02};
static char nt35532_ct_default_cmd100[]={0xD8, 0xD2};
static char nt35532_ct_default_cmd101[]={0xD9, 0x03};
static char nt35532_ct_default_cmd102[]={0xDA, 0x03};
static char nt35532_ct_default_cmd103[]={0xDB, 0x03};
static char nt35532_ct_default_cmd104[]={0xDC, 0x23};
static char nt35532_ct_default_cmd105[]={0xDD, 0x03};
static char nt35532_ct_default_cmd106[]={0xDE, 0x4C};
static char nt35532_ct_default_cmd107[]={0xDF, 0x03};
static char nt35532_ct_default_cmd108[]={0xE0, 0x59};
static char nt35532_ct_default_cmd109[]={0xE1, 0x03};
static char nt35532_ct_default_cmd110[]={0xE2, 0x67};
static char nt35532_ct_default_cmd111[]={0xE3, 0x03};
static char nt35532_ct_default_cmd112[]={0xE4, 0x77};
static char nt35532_ct_default_cmd113[]={0xE5, 0x03};
static char nt35532_ct_default_cmd114[]={0xE6, 0x88};
static char nt35532_ct_default_cmd115[]={0xE7, 0x03};
static char nt35532_ct_default_cmd116[]={0xE8, 0x9D};
static char nt35532_ct_default_cmd117[]={0xE9, 0x03};
static char nt35532_ct_default_cmd118[]={0xEA, 0xB8};
static char nt35532_ct_default_cmd119[]={0xEB, 0x03};
static char nt35532_ct_default_cmd120[]={0xEC, 0xDE};
static char nt35532_ct_default_cmd121[]={0xED, 0x03};
static char nt35532_ct_default_cmd122[]={0xEE, 0xFF};
static char nt35532_ct_default_cmd123[]={0xEF, 0x00};//G+
static char nt35532_ct_default_cmd124[]={0xF0, 0x24};
static char nt35532_ct_default_cmd125[]={0xF1, 0x00};
static char nt35532_ct_default_cmd126[]={0xF2, 0x4B};
static char nt35532_ct_default_cmd127[]={0xF3, 0x00};
static char nt35532_ct_default_cmd128[]={0xF4, 0x80};
static char nt35532_ct_default_cmd129[]={0xF5, 0x00};
static char nt35532_ct_default_cmd130[]={0xF6, 0xA5};
static char nt35532_ct_default_cmd131[]={0xF7, 0x00};
static char nt35532_ct_default_cmd132[]={0xF8, 0xC3};
static char nt35532_ct_default_cmd133[]={0xF9, 0x00};
static char nt35532_ct_default_cmd134[]={0xFA, 0xDA};
static char nt35532_ct_default_cmd135[]={0xFF, 0x02};
static char nt35532_ct_default_cmd136[]={0xFB, 0x01};
static char nt35532_ct_default_cmd137[]={0x00, 0x00};
static char nt35532_ct_default_cmd138[]={0x01, 0xEF};
static char nt35532_ct_default_cmd139[]={0x02, 0x01};
static char nt35532_ct_default_cmd140[]={0x03, 0x02};
static char nt35532_ct_default_cmd141[]={0x04, 0x01};
static char nt35532_ct_default_cmd142[]={0x05, 0x14};
static char nt35532_ct_default_cmd143[]={0x06, 0x01};
static char nt35532_ct_default_cmd144[]={0x07, 0x47};
static char nt35532_ct_default_cmd145[]={0x08, 0x01};
static char nt35532_ct_default_cmd146[]={0x09, 0x6E};
static char nt35532_ct_default_cmd147[]={0x0A, 0x01};
static char nt35532_ct_default_cmd148[]={0x0B, 0xA7};
static char nt35532_ct_default_cmd149[]={0x0C, 0x01};
static char nt35532_ct_default_cmd150[]={0x0D, 0xD2};
static char nt35532_ct_default_cmd151[]={0x0E, 0x02};
static char nt35532_ct_default_cmd152[]={0x0F, 0x0E};
static char nt35532_ct_default_cmd153[]={0x10, 0x02};
static char nt35532_ct_default_cmd154[]={0x11, 0x3F};
static char nt35532_ct_default_cmd155[]={0x12, 0x02};
static char nt35532_ct_default_cmd156[]={0x13, 0x40};
static char nt35532_ct_default_cmd157[]={0x14, 0x02};
static char nt35532_ct_default_cmd158[]={0x15, 0x6D};
static char nt35532_ct_default_cmd159[]={0x16, 0x02};
static char nt35532_ct_default_cmd160[]={0x17, 0xA5};
static char nt35532_ct_default_cmd161[]={0x18, 0x02};
static char nt35532_ct_default_cmd162[]={0x19, 0xC9};
static char nt35532_ct_default_cmd163[]={0x1A, 0x02};
static char nt35532_ct_default_cmd164[]={0x1B, 0xFA};
static char nt35532_ct_default_cmd165[]={0x1C, 0x03};
static char nt35532_ct_default_cmd166[]={0x1D, 0x1A};
static char nt35532_ct_default_cmd167[]={0x1E, 0x03};
static char nt35532_ct_default_cmd168[]={0x1F, 0x46};
static char nt35532_ct_default_cmd169[]={0x20, 0x03};
static char nt35532_ct_default_cmd170[]={0x21, 0x53};
static char nt35532_ct_default_cmd171[]={0x22, 0x03};
static char nt35532_ct_default_cmd172[]={0x23, 0x61};
static char nt35532_ct_default_cmd173[]={0x24, 0x03};
static char nt35532_ct_default_cmd174[]={0x25, 0x71};
static char nt35532_ct_default_cmd175[]={0x26, 0x03};
static char nt35532_ct_default_cmd176[]={0x27, 0x83};
static char nt35532_ct_default_cmd177[]={0x28, 0x03};
static char nt35532_ct_default_cmd178[]={0x29, 0x98};
static char nt35532_ct_default_cmd179[]={0x2A, 0x03};
static char nt35532_ct_default_cmd180[]={0x2B, 0xB3};
static char nt35532_ct_default_cmd181[]={0x2D, 0x03};
static char nt35532_ct_default_cmd182[]={0x2F, 0xD9};
static char nt35532_ct_default_cmd183[]={0x30, 0x03};
static char nt35532_ct_default_cmd184[]={0x31, 0xFF};
static char nt35532_ct_default_cmd185[]={0x32, 0x00};
static char nt35532_ct_default_cmd186[]={0x33, 0x24};//G-
static char nt35532_ct_default_cmd187[]={0x34, 0x00};
static char nt35532_ct_default_cmd188[]={0x35, 0x4B};
static char nt35532_ct_default_cmd189[]={0x36, 0x00};
static char nt35532_ct_default_cmd190[]={0x37, 0x80};
static char nt35532_ct_default_cmd191[]={0x38, 0x00};
static char nt35532_ct_default_cmd192[]={0x39, 0xA5};
static char nt35532_ct_default_cmd193[]={0x3A, 0x00};
static char nt35532_ct_default_cmd194[]={0x3B, 0xC3};
static char nt35532_ct_default_cmd195[]={0x3D, 0x00};
static char nt35532_ct_default_cmd196[]={0x3F, 0xDA};
static char nt35532_ct_default_cmd197[]={0x40, 0x00};
static char nt35532_ct_default_cmd198[]={0x41, 0xEF};
static char nt35532_ct_default_cmd199[]={0x42, 0x01};
static char nt35532_ct_default_cmd200[]={0x43, 0x02};
static char nt35532_ct_default_cmd201[]={0x44, 0x01};
static char nt35532_ct_default_cmd202[]={0x45, 0x14};
static char nt35532_ct_default_cmd203[]={0x46, 0x01};
static char nt35532_ct_default_cmd204[]={0x47, 0x47};
static char nt35532_ct_default_cmd205[]={0x48, 0x01};
static char nt35532_ct_default_cmd206[]={0x49, 0x6E};
static char nt35532_ct_default_cmd207[]={0x4A, 0x01};
static char nt35532_ct_default_cmd208[]={0x4B, 0xA7};
static char nt35532_ct_default_cmd209[]={0x4C, 0x01};
static char nt35532_ct_default_cmd210[]={0x4D, 0xD2};
static char nt35532_ct_default_cmd211[]={0x4E, 0x02};
static char nt35532_ct_default_cmd212[]={0x4F, 0x0E};
static char nt35532_ct_default_cmd213[]={0x50, 0x02};
static char nt35532_ct_default_cmd214[]={0x51, 0x3F};
static char nt35532_ct_default_cmd215[]={0x52, 0x02};
static char nt35532_ct_default_cmd216[]={0x53, 0x40};
static char nt35532_ct_default_cmd217[]={0x54, 0x02};
static char nt35532_ct_default_cmd218[]={0x55, 0x6D};
static char nt35532_ct_default_cmd219[]={0x56, 0x02};
static char nt35532_ct_default_cmd220[]={0x58, 0xA5};
static char nt35532_ct_default_cmd221[]={0x59, 0x02};
static char nt35532_ct_default_cmd222[]={0x5A, 0xC9};
static char nt35532_ct_default_cmd223[]={0x5B, 0x02};
static char nt35532_ct_default_cmd224[]={0x5C, 0xFA};
static char nt35532_ct_default_cmd225[]={0x5D, 0x03};
static char nt35532_ct_default_cmd226[]={0x5E, 0x1A};
static char nt35532_ct_default_cmd227[]={0x5F, 0x03};
static char nt35532_ct_default_cmd228[]={0x60, 0x46};
static char nt35532_ct_default_cmd229[]={0x61, 0x03};
static char nt35532_ct_default_cmd230[]={0x62, 0x53};
static char nt35532_ct_default_cmd231[]={0x63, 0x03};
static char nt35532_ct_default_cmd232[]={0x64, 0x61};
static char nt35532_ct_default_cmd233[]={0x65, 0x03};
static char nt35532_ct_default_cmd234[]={0x66, 0x71};
static char nt35532_ct_default_cmd235[]={0x67, 0x03};
static char nt35532_ct_default_cmd236[]={0x68, 0x83};
static char nt35532_ct_default_cmd237[]={0x69, 0x03};
static char nt35532_ct_default_cmd238[]={0x6A, 0x98};
static char nt35532_ct_default_cmd239[]={0x6B, 0x03};
static char nt35532_ct_default_cmd240[]={0x6C, 0xB3};
static char nt35532_ct_default_cmd241[]={0x6D, 0x03};
static char nt35532_ct_default_cmd242[]={0x6E, 0xD9};
static char nt35532_ct_default_cmd243[]={0x6F, 0x03};
static char nt35532_ct_default_cmd244[]={0x70, 0xFF};
static char nt35532_ct_default_cmd245[]={0x71, 0x01};
static char nt35532_ct_default_cmd246[]={0x72, 0x92};		//B+
static char nt35532_ct_default_cmd247[]={0x73, 0x01};
static char nt35532_ct_default_cmd248[]={0x74, 0x95};
static char nt35532_ct_default_cmd249[]={0x75, 0x01};
static char nt35532_ct_default_cmd250[]={0x76, 0x9A};
static char nt35532_ct_default_cmd251[]={0x77, 0x01};
static char nt35532_ct_default_cmd252[]={0x78, 0xA0};
static char nt35532_ct_default_cmd253[]={0x79, 0x01};
static char nt35532_ct_default_cmd254[]={0x7A, 0xA6};
static char nt35532_ct_default_cmd255[]={0x7B, 0x01};
static char nt35532_ct_default_cmd256[]={0x7C, 0xAA};
static char nt35532_ct_default_cmd257[]={0x7D, 0x01};
static char nt35532_ct_default_cmd258[]={0x7E, 0xAF};
static char nt35532_ct_default_cmd259[]={0x7F, 0x01};
static char nt35532_ct_default_cmd260[]={0x80, 0xB4};
static char nt35532_ct_default_cmd261[]={0x81, 0x01};
static char nt35532_ct_default_cmd262[]={0x82, 0xB9};
static char nt35532_ct_default_cmd263[]={0x83, 0x01};
static char nt35532_ct_default_cmd264[]={0x84, 0xCA};
static char nt35532_ct_default_cmd265[]={0x85, 0x01};
static char nt35532_ct_default_cmd266[]={0x86, 0xDA};
static char nt35532_ct_default_cmd267[]={0x87, 0x01};
static char nt35532_ct_default_cmd268[]={0x88, 0xF6};
static char nt35532_ct_default_cmd269[]={0x89, 0x02};
static char nt35532_ct_default_cmd270[]={0x8A, 0x0D};
static char nt35532_ct_default_cmd271[]={0x8B, 0x02};
static char nt35532_ct_default_cmd272[]={0x8C, 0x37};
static char nt35532_ct_default_cmd273[]={0x8D, 0x02};
static char nt35532_ct_default_cmd274[]={0x8E, 0x5D};
static char nt35532_ct_default_cmd275[]={0x8F, 0x02};
static char nt35532_ct_default_cmd276[]={0x90, 0x5E};
static char nt35532_ct_default_cmd277[]={0x91, 0x02};
static char nt35532_ct_default_cmd278[]={0x92, 0x87};
static char nt35532_ct_default_cmd279[]={0x93, 0x02};
static char nt35532_ct_default_cmd280[]={0x94, 0xBB};
static char nt35532_ct_default_cmd281[]={0x95, 0x02};
static char nt35532_ct_default_cmd282[]={0x96, 0xE0};
static char nt35532_ct_default_cmd283[]={0x97, 0x03};
static char nt35532_ct_default_cmd284[]={0x98, 0x11};
static char nt35532_ct_default_cmd285[]={0x99, 0x03};
static char nt35532_ct_default_cmd286[]={0x9A, 0x33};
static char nt35532_ct_default_cmd287[]={0x9B, 0x03};
static char nt35532_ct_default_cmd288[]={0x9C, 0x65};
static char nt35532_ct_default_cmd289[]={0x9D, 0x03};
static char nt35532_ct_default_cmd290[]={0x9E, 0x78};
static char nt35532_ct_default_cmd291[]={0x9F, 0x03};
static char nt35532_ct_default_cmd292[]={0xA0, 0x93};
static char nt35532_ct_default_cmd293[]={0xA2, 0x03};
static char nt35532_ct_default_cmd294[]={0xA3, 0xA4};
static char nt35532_ct_default_cmd295[]={0xA4, 0x03};
static char nt35532_ct_default_cmd296[]={0xA5, 0xA8};
static char nt35532_ct_default_cmd297[]={0xA6, 0x03};
static char nt35532_ct_default_cmd298[]={0xA7, 0xAA};
static char nt35532_ct_default_cmd299[]={0xA9, 0x03};
static char nt35532_ct_default_cmd300[]={0xAA, 0xBA};
static char nt35532_ct_default_cmd301[]={0xAB, 0x03};
static char nt35532_ct_default_cmd302[]={0xAC, 0xF7};
static char nt35532_ct_default_cmd303[]={0xAD, 0x03};
static char nt35532_ct_default_cmd304[]={0xAE, 0xFF};
static char nt35532_ct_default_cmd305[]={0xAF, 0x01};
static char nt35532_ct_default_cmd306[]={0xB0, 0x92};	//B-
static char nt35532_ct_default_cmd307[]={0xB1, 0x01};
static char nt35532_ct_default_cmd308[]={0xB2, 0x95};
static char nt35532_ct_default_cmd309[]={0xB3, 0x01};
static char nt35532_ct_default_cmd310[]={0xB4, 0x9A};
static char nt35532_ct_default_cmd311[]={0xB5, 0x01};
static char nt35532_ct_default_cmd312[]={0xB6, 0xA0};
static char nt35532_ct_default_cmd313[]={0xB7, 0x01};
static char nt35532_ct_default_cmd314[]={0xB8, 0xA6};
static char nt35532_ct_default_cmd315[]={0xB9, 0x01};
static char nt35532_ct_default_cmd316[]={0xBA, 0xAA};
static char nt35532_ct_default_cmd317[]={0xBB, 0x01};
static char nt35532_ct_default_cmd318[]={0xBC, 0xAF};
static char nt35532_ct_default_cmd319[]={0xBD, 0x01};
static char nt35532_ct_default_cmd320[]={0xBE, 0xB4};
static char nt35532_ct_default_cmd321[]={0xBF, 0x01};
static char nt35532_ct_default_cmd322[]={0xC0, 0xB9};
static char nt35532_ct_default_cmd323[]={0xC1, 0x01};
static char nt35532_ct_default_cmd324[]={0xC2, 0xCA};
static char nt35532_ct_default_cmd325[]={0xC3, 0x01};
static char nt35532_ct_default_cmd326[]={0xC4, 0xDA};
static char nt35532_ct_default_cmd327[]={0xC5, 0x01};
static char nt35532_ct_default_cmd328[]={0xC6, 0xF6};
static char nt35532_ct_default_cmd329[]={0xC7, 0x02};
static char nt35532_ct_default_cmd330[]={0xC8, 0x0D};
static char nt35532_ct_default_cmd331[]={0xC9, 0x02};
static char nt35532_ct_default_cmd332[]={0xCA, 0x37};
static char nt35532_ct_default_cmd333[]={0xCB, 0x02};
static char nt35532_ct_default_cmd334[]={0xCC, 0x5D};
static char nt35532_ct_default_cmd335[]={0xCD, 0x02};
static char nt35532_ct_default_cmd336[]={0xCE, 0x5E};
static char nt35532_ct_default_cmd337[]={0xCF, 0x02};
static char nt35532_ct_default_cmd338[]={0xD0, 0x87};
static char nt35532_ct_default_cmd339[]={0xD1, 0x02};
static char nt35532_ct_default_cmd340[]={0xD2, 0xBB};
static char nt35532_ct_default_cmd341[]={0xD3, 0x02};
static char nt35532_ct_default_cmd342[]={0xD4, 0xE0};
static char nt35532_ct_default_cmd343[]={0xD5, 0x03};
static char nt35532_ct_default_cmd344[]={0xD6, 0x11};
static char nt35532_ct_default_cmd345[]={0xD7, 0x03};
static char nt35532_ct_default_cmd346[]={0xD8, 0x33};
static char nt35532_ct_default_cmd347[]={0xD9, 0x03};
static char nt35532_ct_default_cmd348[]={0xDA, 0x65};
static char nt35532_ct_default_cmd349[]={0xDB, 0x03};
static char nt35532_ct_default_cmd350[]={0xDC, 0x78};
static char nt35532_ct_default_cmd351[]={0xDD, 0x03};
static char nt35532_ct_default_cmd352[]={0xDE, 0x93};
static char nt35532_ct_default_cmd353[]={0xDF, 0x03};
static char nt35532_ct_default_cmd354[]={0xE0, 0xA4};
static char nt35532_ct_default_cmd355[]={0xE1, 0x03};
static char nt35532_ct_default_cmd356[]={0xE2, 0xA8};
static char nt35532_ct_default_cmd357[]={0xE3, 0x03};
static char nt35532_ct_default_cmd358[]={0xE4, 0xAA};
static char nt35532_ct_default_cmd359[]={0xE5, 0x03};
static char nt35532_ct_default_cmd360[]={0xE6, 0xBA};
static char nt35532_ct_default_cmd361[]={0xE7, 0x03};
static char nt35532_ct_default_cmd362[]={0xE8, 0xF7};
static char nt35532_ct_default_cmd363[]={0xE9, 0x03};
static char nt35532_ct_default_cmd364[]={0xEA, 0xFF};

static struct dsi_cmd_desc nt35532_ct_default_cmd[] = {
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd1},//Gamma setting  R+
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd2},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd3},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd4},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd5},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd6},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd7},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd8},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd9},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd10},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd11},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd12},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd13},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd14},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd15},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd16},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd17},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd18},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd19},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd20},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd21},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd22},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd23},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd24},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd25},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd26},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd27},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd28},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd29},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd30},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd31},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd32},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd33},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd34},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd35},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd36},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd37},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd38},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd39},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd40},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd41},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd42},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd43},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd44},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd45},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd46},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd47},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd48},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd49},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd50},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd51},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd52},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd53},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd54},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd55},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd56},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd57},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd58},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd59},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd60},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd61},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd62},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd63},//R-
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd64},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd65},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd66},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd67},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd68},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd69},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd70},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd71},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd72},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd73},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd74},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd75},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd76},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd77},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd78},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd79},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd80},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd81},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd82},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd83},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd84},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd85},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd86},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd87},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd88},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd89},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd90},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd91},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd92},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd93},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd94},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd95},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd96},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd97},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd98},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd99},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd100},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd101},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd102},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd103},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd104},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd105},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd106},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd107},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd108},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd109},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd110},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd111},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd112},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd113},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd114},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd115},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd116},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd117},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd118},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd119},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd120},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd121},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd122},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd123},//G+
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd124},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd125},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd126},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd127},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd128},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd129},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd130},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd131},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd132},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd133},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd134},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd135},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd136},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd137},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd138},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd139},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd140},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd141},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd142},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd143},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd144},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd145},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd146},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd147},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd148},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd149},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd150},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd151},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd152},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd153},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd154},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd155},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd156},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd157},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd158},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd159},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd160},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd161},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd162},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd163},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd164},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd165},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd166},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd167},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd168},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd169},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd170},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd171},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd172},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd173},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd174},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd175},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd176},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd177},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd178},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd179},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd180},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd181},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd182},
  {{0x29,1,0,0,0,2},nt35532_ct_default_cmd183},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd184},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd185},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd186},//G-
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd187},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd188},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd189},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd190},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd191},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd192},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd193},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd194},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd195},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd196},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd197},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd198},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd199},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd200},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd201},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd202},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd203},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd204},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd205},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd206},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd207},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd208},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd209},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd210},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd211},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd212},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd213},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd214},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd215},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd216},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd217},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd218},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd219},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd220},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd221},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd222},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd223},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd224},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd225},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd226},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd227},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd228},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd229},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd230},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd231},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd232},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd233},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd234},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd235},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd236},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd237},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd238},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd239},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd240},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd241},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd242},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd243},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd244},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd245},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd246},	//B+
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd247},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd248},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd249},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd250},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd251},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd252},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd253},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd254},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd255},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd256},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd257},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd258},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd259},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd260},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd261},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd262},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd263},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd264},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd265},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd266},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd267},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd268},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd269},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd270},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd271},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd272},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd273},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd274},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd275},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd276},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd277},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd278},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd279},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd280},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd281},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd282},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd283},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd284},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd285},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd286},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd287},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd288},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd289},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd290},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd291},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd292},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd293},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd294},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd295},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd296},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd297},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd298},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd299},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd300},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd301},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd302},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd303},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd304},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd305},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd306},//B-
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd307},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd308},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd309},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd310},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd311},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd312},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd313},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd314},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd315},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd316},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd317},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd318},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd319},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd320},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd321},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd322},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd323},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd324},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd325},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd326},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd327},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd328},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd329},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd330},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd331},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd332},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd333},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd334},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd335},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd336},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd337},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd338},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd339},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd340},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd341},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd342},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd343},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd344},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd345},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd346},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd347},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd348},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd349},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd350},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd351},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd352},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd353},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd354},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd355},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd356},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd357},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd358},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd359},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd360},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd361},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd362},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd363},
  {{0x29,0,0,0,0,2},nt35532_ct_default_cmd364},
  {{0x29,1,0,0,0,2},nt35532_normal_mode_cmd},
};
static char nt35532_ct_warm_cmd1[]=  {0xFF, 0x01};
static char nt35532_ct_warm_cmd2[]=  {0xFB, 0x01};
static char nt35532_ct_warm_cmd3[]=  {0x75, 0x00};
static char nt35532_ct_warm_cmd4[]=  {0x76, 0x01};
static char nt35532_ct_warm_cmd5[]=  {0x77, 0x00};
static char nt35532_ct_warm_cmd6[]=  {0x78, 0x04};
static char nt35532_ct_warm_cmd7[]=  {0x79, 0x00};
static char nt35532_ct_warm_cmd8[]=  {0x7A, 0x37};
static char nt35532_ct_warm_cmd9[]=  {0x7B, 0x00};
static char nt35532_ct_warm_cmd10[]= {0x7C, 0x72};
static char nt35532_ct_warm_cmd11[]= {0x7D, 0x00};
static char nt35532_ct_warm_cmd12[]= {0x7E, 0x98};
static char nt35532_ct_warm_cmd13[]= {0x7F, 0x00};
static char nt35532_ct_warm_cmd14[]= {0x80, 0xB6};
static char nt35532_ct_warm_cmd15[]= {0x81, 0x00};
static char nt35532_ct_warm_cmd16[]= {0x82, 0xD1};
static char nt35532_ct_warm_cmd17[]= {0x83, 0x00};
static char nt35532_ct_warm_cmd18[]= {0x84, 0xE5};
static char nt35532_ct_warm_cmd19[]= {0x85, 0x00};
static char nt35532_ct_warm_cmd20[]= {0x86, 0xFB};
static char nt35532_ct_warm_cmd21[]= {0x87, 0x01};
static char nt35532_ct_warm_cmd22[]= {0x88, 0x36};
static char nt35532_ct_warm_cmd23[]= {0x89, 0x01};
static char nt35532_ct_warm_cmd24[]= {0x8A, 0x61};
static char nt35532_ct_warm_cmd25[]= {0x8B, 0x01};
static char nt35532_ct_warm_cmd26[]= {0x8C, 0xA1};
static char nt35532_ct_warm_cmd27[]= {0x8D, 0x01};
static char nt35532_ct_warm_cmd28[]= {0x8E, 0xCB};
static char nt35532_ct_warm_cmd29[]= {0x8F, 0x02};
static char nt35532_ct_warm_cmd30[]= {0x90, 0x0C};
static char nt35532_ct_warm_cmd31[]= {0x91, 0x02};
static char nt35532_ct_warm_cmd32[]= {0x92, 0x3D};
static char nt35532_ct_warm_cmd33[]= {0x93, 0x02};
static char nt35532_ct_warm_cmd34[]= {0x94, 0x3F};
static char nt35532_ct_warm_cmd35[]= {0x95, 0x02};
static char nt35532_ct_warm_cmd36[]= {0x96, 0x6D};
static char nt35532_ct_warm_cmd37[]= {0x97, 0x02};
static char nt35532_ct_warm_cmd38[]= {0x98, 0xA4};
static char nt35532_ct_warm_cmd39[]= {0x99, 0x02};
static char nt35532_ct_warm_cmd40[]= {0x9A, 0xC7};
static char nt35532_ct_warm_cmd41[]= {0x9B, 0x02};
static char nt35532_ct_warm_cmd42[]= {0x9C, 0xF8};
static char nt35532_ct_warm_cmd43[]= {0x9D, 0x03};
static char nt35532_ct_warm_cmd44[]= {0x9E, 0x19};
static char nt35532_ct_warm_cmd45[]= {0x9F, 0x03};
static char nt35532_ct_warm_cmd46[]= {0xA0, 0x34};
static char nt35532_ct_warm_cmd47[]= {0xA2, 0x03};
static char nt35532_ct_warm_cmd48[]= {0xA3, 0x50};
static char nt35532_ct_warm_cmd49[]= {0xA4, 0x03};
static char nt35532_ct_warm_cmd50[]= {0xA5, 0x60};
static char nt35532_ct_warm_cmd51[]= {0xA6, 0x03};
static char nt35532_ct_warm_cmd52[]= {0xA7, 0x70};
static char nt35532_ct_warm_cmd53[]= {0xA9, 0x03};
static char nt35532_ct_warm_cmd54[]= {0xAA, 0x82};
static char nt35532_ct_warm_cmd55[]= {0xAB, 0x03};
static char nt35532_ct_warm_cmd56[]= {0xAC, 0x98};
static char nt35532_ct_warm_cmd57[]= {0xAD, 0x03};
static char nt35532_ct_warm_cmd58[]= {0xAE, 0xB3};
static char nt35532_ct_warm_cmd59[]= {0xAF, 0x03};
static char nt35532_ct_warm_cmd60[]= {0xB0, 0xD9};
static char nt35532_ct_warm_cmd61[]= {0xB1, 0x03};
static char nt35532_ct_warm_cmd62[]= {0xB2, 0xFF};
static char nt35532_ct_warm_cmd63[]= {0xB3, 0x00};
static char nt35532_ct_warm_cmd64[]= {0xB4, 0x01};
static char nt35532_ct_warm_cmd65[]= {0xB5, 0x00};
static char nt35532_ct_warm_cmd66[]= {0xB6, 0x04};
static char nt35532_ct_warm_cmd67[]= {0xB7, 0x00};
static char nt35532_ct_warm_cmd68[]= {0xB8, 0x37};
static char nt35532_ct_warm_cmd69[]= {0xB9, 0x00};
static char nt35532_ct_warm_cmd70[]= {0xBA, 0x72};
static char nt35532_ct_warm_cmd71[]= {0xBB, 0x00};
static char nt35532_ct_warm_cmd72[]= {0xBC, 0x98};
static char nt35532_ct_warm_cmd73[]= {0xBD, 0x00};
static char nt35532_ct_warm_cmd74[]= {0xBE, 0xB6};
static char nt35532_ct_warm_cmd75[]= {0xBF, 0x00};
static char nt35532_ct_warm_cmd76[]= {0xC0, 0xD1};
static char nt35532_ct_warm_cmd77[]= {0xC1, 0x00};
static char nt35532_ct_warm_cmd78[]= {0xC2, 0xE5};
static char nt35532_ct_warm_cmd79[]= {0xC3, 0x00};
static char nt35532_ct_warm_cmd80[]= {0xC4, 0xFB};
static char nt35532_ct_warm_cmd81[]= {0xC5, 0x01};
static char nt35532_ct_warm_cmd82[]= {0xC6, 0x36};
static char nt35532_ct_warm_cmd83[]= {0xC7, 0x01};
static char nt35532_ct_warm_cmd84[]= {0xC8, 0x61};
static char nt35532_ct_warm_cmd85[]= {0xC9, 0x01};
static char nt35532_ct_warm_cmd86[]= {0xCA, 0xA1};
static char nt35532_ct_warm_cmd87[]= {0xCB, 0x01};
static char nt35532_ct_warm_cmd88[]= {0xCC, 0xCB};
static char nt35532_ct_warm_cmd89[]= {0xCD, 0x02};
static char nt35532_ct_warm_cmd90[]= {0xCE, 0x0C};
static char nt35532_ct_warm_cmd91[]= {0xCF, 0x02};
static char nt35532_ct_warm_cmd92[]= {0xD0, 0x3D};
static char nt35532_ct_warm_cmd93[]= {0xD1, 0x02};
static char nt35532_ct_warm_cmd94[]= {0xD2, 0x3F};
static char nt35532_ct_warm_cmd95[]= {0xD3, 0x02};
static char nt35532_ct_warm_cmd96[]= {0xD4, 0x6D};
static char nt35532_ct_warm_cmd97[]= {0xD5, 0x02};
static char nt35532_ct_warm_cmd98[]= {0xD6, 0xA4};
static char nt35532_ct_warm_cmd99[]= {0xD7, 0x02};
static char nt35532_ct_warm_cmd100[]={0xD8, 0xC7};
static char nt35532_ct_warm_cmd101[]={0xD9, 0x02};
static char nt35532_ct_warm_cmd102[]={0xDA, 0xF8};
static char nt35532_ct_warm_cmd103[]={0xDB, 0x03};
static char nt35532_ct_warm_cmd104[]={0xDC, 0x19};
static char nt35532_ct_warm_cmd105[]={0xDD, 0x03};
static char nt35532_ct_warm_cmd106[]={0xDE, 0x34};
static char nt35532_ct_warm_cmd107[]={0xDF, 0x03};
static char nt35532_ct_warm_cmd108[]={0xE0, 0x50};
static char nt35532_ct_warm_cmd109[]={0xE1, 0x03};
static char nt35532_ct_warm_cmd110[]={0xE2, 0x60};
static char nt35532_ct_warm_cmd111[]={0xE3, 0x03};
static char nt35532_ct_warm_cmd112[]={0xE4, 0x70};
static char nt35532_ct_warm_cmd113[]={0xE5, 0x03};
static char nt35532_ct_warm_cmd114[]={0xE6, 0x82};
static char nt35532_ct_warm_cmd115[]={0xE7, 0x03};
static char nt35532_ct_warm_cmd116[]={0xE8, 0x98};
static char nt35532_ct_warm_cmd117[]={0xE9, 0x03};
static char nt35532_ct_warm_cmd118[]={0xEA, 0xB3};
static char nt35532_ct_warm_cmd119[]={0xEB, 0x03};
static char nt35532_ct_warm_cmd120[]={0xEC, 0xD9};
static char nt35532_ct_warm_cmd121[]={0xED, 0x03};
static char nt35532_ct_warm_cmd122[]={0xEE, 0xFF};
static char nt35532_ct_warm_cmd123[]={0xEF, 0x00};
static char nt35532_ct_warm_cmd124[]={0xF0, 0x5D};
static char nt35532_ct_warm_cmd125[]={0xF1, 0x00};
static char nt35532_ct_warm_cmd126[]={0xF2, 0x79};
static char nt35532_ct_warm_cmd127[]={0xF3, 0x00};
static char nt35532_ct_warm_cmd128[]={0xF4, 0xA4};
static char nt35532_ct_warm_cmd129[]={0xF5, 0x00};
static char nt35532_ct_warm_cmd130[]={0xF6, 0xC1};
static char nt35532_ct_warm_cmd131[]={0xF7, 0x00};
static char nt35532_ct_warm_cmd132[]={0xF8, 0xD9};
static char nt35532_ct_warm_cmd133[]={0xF9, 0x00};
static char nt35532_ct_warm_cmd134[]={0xFA, 0xEF};
static char nt35532_ct_warm_cmd135[]={0xFF, 0x02};
static char nt35532_ct_warm_cmd136[]={0xFB, 0x01};
static char nt35532_ct_warm_cmd137[]={0x00, 0x01};
static char nt35532_ct_warm_cmd138[]={0x01, 0x02};
static char nt35532_ct_warm_cmd139[]={0x02, 0x01};
static char nt35532_ct_warm_cmd140[]={0x03, 0x13};
static char nt35532_ct_warm_cmd141[]={0x04, 0x01};
static char nt35532_ct_warm_cmd142[]={0x05, 0x21};
static char nt35532_ct_warm_cmd143[]={0x06, 0x01};
static char nt35532_ct_warm_cmd144[]={0x07, 0x52};
static char nt35532_ct_warm_cmd145[]={0x08, 0x01};
static char nt35532_ct_warm_cmd146[]={0x09, 0x77};
static char nt35532_ct_warm_cmd147[]={0x0A, 0x01};
static char nt35532_ct_warm_cmd148[]={0x0B, 0xAC};
static char nt35532_ct_warm_cmd149[]={0x0C, 0x01};
static char nt35532_ct_warm_cmd150[]={0x0D, 0xD6};
static char nt35532_ct_warm_cmd151[]={0x0E, 0x02};
static char nt35532_ct_warm_cmd152[]={0x0F, 0x11};
static char nt35532_ct_warm_cmd153[]={0x10, 0x02};
static char nt35532_ct_warm_cmd154[]={0x11, 0x41};
static char nt35532_ct_warm_cmd155[]={0x12, 0x02};
static char nt35532_ct_warm_cmd156[]={0x13, 0x42};
static char nt35532_ct_warm_cmd157[]={0x14, 0x02};
static char nt35532_ct_warm_cmd158[]={0x15, 0x70};
static char nt35532_ct_warm_cmd159[]={0x16, 0x02};
static char nt35532_ct_warm_cmd160[]={0x17, 0xA6};
static char nt35532_ct_warm_cmd161[]={0x18, 0x02};
static char nt35532_ct_warm_cmd162[]={0x19, 0xCA};
static char nt35532_ct_warm_cmd163[]={0x1A, 0x02};
static char nt35532_ct_warm_cmd164[]={0x1B, 0xFB};
static char nt35532_ct_warm_cmd165[]={0x1C, 0x03};
static char nt35532_ct_warm_cmd166[]={0x1D, 0x1C};
static char nt35532_ct_warm_cmd167[]={0x1E, 0x03};
static char nt35532_ct_warm_cmd168[]={0x1F, 0x37};
static char nt35532_ct_warm_cmd169[]={0x20, 0x03};
static char nt35532_ct_warm_cmd170[]={0x21, 0x53};
static char nt35532_ct_warm_cmd171[]={0x22, 0x03};
static char nt35532_ct_warm_cmd172[]={0x23, 0x62};
static char nt35532_ct_warm_cmd173[]={0x24, 0x03};
static char nt35532_ct_warm_cmd174[]={0x25, 0x72};
static char nt35532_ct_warm_cmd175[]={0x26, 0x03};
static char nt35532_ct_warm_cmd176[]={0x27, 0x83};
static char nt35532_ct_warm_cmd177[]={0x28, 0x03};
static char nt35532_ct_warm_cmd178[]={0x29, 0x98};
static char nt35532_ct_warm_cmd179[]={0x2A, 0x03};
static char nt35532_ct_warm_cmd180[]={0x2B, 0xB3};
static char nt35532_ct_warm_cmd181[]={0x2D, 0x03};
static char nt35532_ct_warm_cmd182[]={0x2F, 0xD9};
static char nt35532_ct_warm_cmd183[]={0x30, 0x03};
static char nt35532_ct_warm_cmd184[]={0x31, 0xFF};
static char nt35532_ct_warm_cmd185[]={0x32, 0x00};
static char nt35532_ct_warm_cmd186[]={0x33, 0x5D};
static char nt35532_ct_warm_cmd187[]={0x34, 0x00};
static char nt35532_ct_warm_cmd188[]={0x35, 0x79};
static char nt35532_ct_warm_cmd189[]={0x36, 0x00};
static char nt35532_ct_warm_cmd190[]={0x37, 0xA4};
static char nt35532_ct_warm_cmd191[]={0x38, 0x00};
static char nt35532_ct_warm_cmd192[]={0x39, 0xC1};
static char nt35532_ct_warm_cmd193[]={0x3A, 0x00};
static char nt35532_ct_warm_cmd194[]={0x3B, 0xD9};
static char nt35532_ct_warm_cmd195[]={0x3D, 0x00};
static char nt35532_ct_warm_cmd196[]={0x3F, 0xEF};
static char nt35532_ct_warm_cmd197[]={0x40, 0x01};
static char nt35532_ct_warm_cmd198[]={0x41, 0x02};
static char nt35532_ct_warm_cmd199[]={0x42, 0x01};
static char nt35532_ct_warm_cmd200[]={0x43, 0x13};
static char nt35532_ct_warm_cmd201[]={0x44, 0x01};
static char nt35532_ct_warm_cmd202[]={0x45, 0x21};
static char nt35532_ct_warm_cmd203[]={0x46, 0x01};
static char nt35532_ct_warm_cmd204[]={0x47, 0x52};
static char nt35532_ct_warm_cmd205[]={0x48, 0x01};
static char nt35532_ct_warm_cmd206[]={0x49, 0x77};
static char nt35532_ct_warm_cmd207[]={0x4A, 0x01};
static char nt35532_ct_warm_cmd208[]={0x4B, 0xAC};
static char nt35532_ct_warm_cmd209[]={0x4C, 0x01};
static char nt35532_ct_warm_cmd210[]={0x4D, 0xD6};
static char nt35532_ct_warm_cmd211[]={0x4E, 0x02};
static char nt35532_ct_warm_cmd212[]={0x4F, 0x11};
static char nt35532_ct_warm_cmd213[]={0x50, 0x02};
static char nt35532_ct_warm_cmd214[]={0x51, 0x41};
static char nt35532_ct_warm_cmd215[]={0x52, 0x02};
static char nt35532_ct_warm_cmd216[]={0x53, 0x42};
static char nt35532_ct_warm_cmd217[]={0x54, 0x02};
static char nt35532_ct_warm_cmd218[]={0x55, 0x70};
static char nt35532_ct_warm_cmd219[]={0x56, 0x02};
static char nt35532_ct_warm_cmd220[]={0x58, 0xA6};
static char nt35532_ct_warm_cmd221[]={0x59, 0x02};
static char nt35532_ct_warm_cmd222[]={0x5A, 0xCA};
static char nt35532_ct_warm_cmd223[]={0x5B, 0x02};
static char nt35532_ct_warm_cmd224[]={0x5C, 0xFB};
static char nt35532_ct_warm_cmd225[]={0x5D, 0x03};
static char nt35532_ct_warm_cmd226[]={0x5E, 0x1C};
static char nt35532_ct_warm_cmd227[]={0x5F, 0x03};
static char nt35532_ct_warm_cmd228[]={0x60, 0x37};
static char nt35532_ct_warm_cmd229[]={0x61, 0x03};
static char nt35532_ct_warm_cmd230[]={0x62, 0x53};
static char nt35532_ct_warm_cmd231[]={0x63, 0x03};
static char nt35532_ct_warm_cmd232[]={0x64, 0x62};
static char nt35532_ct_warm_cmd233[]={0x65, 0x03};
static char nt35532_ct_warm_cmd234[]={0x66, 0x72};
static char nt35532_ct_warm_cmd235[]={0x67, 0x03};
static char nt35532_ct_warm_cmd236[]={0x68, 0x83};
static char nt35532_ct_warm_cmd237[]={0x69, 0x03};
static char nt35532_ct_warm_cmd238[]={0x6A, 0x98};
static char nt35532_ct_warm_cmd239[]={0x6B, 0x03};
static char nt35532_ct_warm_cmd240[]={0x6C, 0xB3};
static char nt35532_ct_warm_cmd241[]={0x6D, 0x03};
static char nt35532_ct_warm_cmd242[]={0x6E, 0xD9};
static char nt35532_ct_warm_cmd243[]={0x6F, 0x03};
static char nt35532_ct_warm_cmd244[]={0x70, 0xFF};
static char nt35532_ct_warm_cmd245[]={0x71, 0x01};
static char nt35532_ct_warm_cmd246[]={0x72, 0xA7};
static char nt35532_ct_warm_cmd247[]={0x73, 0x01};
static char nt35532_ct_warm_cmd248[]={0x74, 0xA8};
static char nt35532_ct_warm_cmd249[]={0x75, 0x01};
static char nt35532_ct_warm_cmd250[]={0x76, 0xAC};
static char nt35532_ct_warm_cmd251[]={0x77, 0x01};
static char nt35532_ct_warm_cmd252[]={0x78, 0xB2};
static char nt35532_ct_warm_cmd253[]={0x79, 0x01};
static char nt35532_ct_warm_cmd254[]={0x7A, 0xB7};
static char nt35532_ct_warm_cmd255[]={0x7B, 0x01};
static char nt35532_ct_warm_cmd256[]={0x7C, 0xBB};
static char nt35532_ct_warm_cmd257[]={0x7D, 0x01};
static char nt35532_ct_warm_cmd258[]={0x7E, 0xBF};
static char nt35532_ct_warm_cmd259[]={0x7F, 0x01};
static char nt35532_ct_warm_cmd260[]={0x80, 0xC4};
static char nt35532_ct_warm_cmd261[]={0x81, 0x01};
static char nt35532_ct_warm_cmd262[]={0x82, 0xC8};
static char nt35532_ct_warm_cmd263[]={0x83, 0x01};
static char nt35532_ct_warm_cmd264[]={0x84, 0xD8};
static char nt35532_ct_warm_cmd265[]={0x85, 0x01};
static char nt35532_ct_warm_cmd266[]={0x86, 0xE6};
static char nt35532_ct_warm_cmd267[]={0x87, 0x01};
static char nt35532_ct_warm_cmd268[]={0x88, 0xFF};
static char nt35532_ct_warm_cmd269[]={0x89, 0x02};
static char nt35532_ct_warm_cmd270[]={0x8A, 0x15};
static char nt35532_ct_warm_cmd271[]={0x8B, 0x02};
static char nt35532_ct_warm_cmd272[]={0x8C, 0x3C};
static char nt35532_ct_warm_cmd273[]={0x8D, 0x02};
static char nt35532_ct_warm_cmd274[]={0x8E, 0x62};
static char nt35532_ct_warm_cmd275[]={0x8F, 0x02};
static char nt35532_ct_warm_cmd276[]={0x90, 0x63};
static char nt35532_ct_warm_cmd277[]={0x91, 0x02};
static char nt35532_ct_warm_cmd278[]={0x92, 0x8B};
static char nt35532_ct_warm_cmd279[]={0x93, 0x02};
static char nt35532_ct_warm_cmd280[]={0x94, 0xBF};
static char nt35532_ct_warm_cmd281[]={0x95, 0x02};
static char nt35532_ct_warm_cmd282[]={0x96, 0xE3};
static char nt35532_ct_warm_cmd283[]={0x97, 0x03};
static char nt35532_ct_warm_cmd284[]={0x98, 0x14};
static char nt35532_ct_warm_cmd285[]={0x99, 0x03};
static char nt35532_ct_warm_cmd286[]={0x9A, 0x37};
static char nt35532_ct_warm_cmd287[]={0x9B, 0x03};
static char nt35532_ct_warm_cmd288[]={0x9C, 0x4F};
static char nt35532_ct_warm_cmd289[]={0x9D, 0x03};
static char nt35532_ct_warm_cmd290[]={0x9E, 0x68};
static char nt35532_ct_warm_cmd291[]={0x9F, 0x03};
static char nt35532_ct_warm_cmd292[]={0xA0, 0x76};
static char nt35532_ct_warm_cmd293[]={0xA2, 0x03};
static char nt35532_ct_warm_cmd294[]={0xA3, 0x86};
static char nt35532_ct_warm_cmd295[]={0xA4, 0x03};
static char nt35532_ct_warm_cmd296[]={0xA5, 0x96};
static char nt35532_ct_warm_cmd297[]={0xA6, 0x03};
static char nt35532_ct_warm_cmd298[]={0xA7, 0xA8};
static char nt35532_ct_warm_cmd299[]={0xA9, 0x03};
static char nt35532_ct_warm_cmd300[]={0xAA, 0xBD};
static char nt35532_ct_warm_cmd301[]={0xAB, 0x03};
static char nt35532_ct_warm_cmd302[]={0xAC, 0xF1};
static char nt35532_ct_warm_cmd303[]={0xAD, 0x03};
static char nt35532_ct_warm_cmd304[]={0xAE, 0xFF};
static char nt35532_ct_warm_cmd305[]={0xAF, 0x01};
static char nt35532_ct_warm_cmd306[]={0xB0, 0xA7};
static char nt35532_ct_warm_cmd307[]={0xB1, 0x01};
static char nt35532_ct_warm_cmd308[]={0xB2, 0xA8};
static char nt35532_ct_warm_cmd309[]={0xB3, 0x01};
static char nt35532_ct_warm_cmd310[]={0xB4, 0xAC};
static char nt35532_ct_warm_cmd311[]={0xB5, 0x01};
static char nt35532_ct_warm_cmd312[]={0xB6, 0xB2};
static char nt35532_ct_warm_cmd313[]={0xB7, 0x01};
static char nt35532_ct_warm_cmd314[]={0xB8, 0xB7};
static char nt35532_ct_warm_cmd315[]={0xB9, 0x01};
static char nt35532_ct_warm_cmd316[]={0xBA, 0xBB};
static char nt35532_ct_warm_cmd317[]={0xBB, 0x01};
static char nt35532_ct_warm_cmd318[]={0xBC, 0xBF};
static char nt35532_ct_warm_cmd319[]={0xBD, 0x01};
static char nt35532_ct_warm_cmd320[]={0xBE, 0xC4};
static char nt35532_ct_warm_cmd321[]={0xBF, 0x01};
static char nt35532_ct_warm_cmd322[]={0xC0, 0xC8};
static char nt35532_ct_warm_cmd323[]={0xC1, 0x01};
static char nt35532_ct_warm_cmd324[]={0xC2, 0xD8};
static char nt35532_ct_warm_cmd325[]={0xC3, 0x01};
static char nt35532_ct_warm_cmd326[]={0xC4, 0xE6};
static char nt35532_ct_warm_cmd327[]={0xC5, 0x01};
static char nt35532_ct_warm_cmd328[]={0xC6, 0xFF};
static char nt35532_ct_warm_cmd329[]={0xC7, 0x02};
static char nt35532_ct_warm_cmd330[]={0xC8, 0x15};
static char nt35532_ct_warm_cmd331[]={0xC9, 0x02};
static char nt35532_ct_warm_cmd332[]={0xCA, 0x3C};
static char nt35532_ct_warm_cmd333[]={0xCB, 0x02};
static char nt35532_ct_warm_cmd334[]={0xCC, 0x62};
static char nt35532_ct_warm_cmd335[]={0xCD, 0x02};
static char nt35532_ct_warm_cmd336[]={0xCE, 0x63};
static char nt35532_ct_warm_cmd337[]={0xCF, 0x02};
static char nt35532_ct_warm_cmd338[]={0xD0, 0x8B};
static char nt35532_ct_warm_cmd339[]={0xD1, 0x02};
static char nt35532_ct_warm_cmd340[]={0xD2, 0xBF};
static char nt35532_ct_warm_cmd341[]={0xD3, 0x02};
static char nt35532_ct_warm_cmd342[]={0xD4, 0xE3};
static char nt35532_ct_warm_cmd343[]={0xD5, 0x03};
static char nt35532_ct_warm_cmd344[]={0xD6, 0x14};
static char nt35532_ct_warm_cmd345[]={0xD7, 0x03};
static char nt35532_ct_warm_cmd346[]={0xD8, 0x37};
static char nt35532_ct_warm_cmd347[]={0xD9, 0x03};
static char nt35532_ct_warm_cmd348[]={0xDA, 0x4F};
static char nt35532_ct_warm_cmd349[]={0xDB, 0x03};
static char nt35532_ct_warm_cmd350[]={0xDC, 0x68};
static char nt35532_ct_warm_cmd351[]={0xDD, 0x03};
static char nt35532_ct_warm_cmd352[]={0xDE, 0x76};
static char nt35532_ct_warm_cmd353[]={0xDF, 0x03};
static char nt35532_ct_warm_cmd354[]={0xE0, 0x86};
static char nt35532_ct_warm_cmd355[]={0xE1, 0x03};
static char nt35532_ct_warm_cmd356[]={0xE2, 0x96};
static char nt35532_ct_warm_cmd357[]={0xE3, 0x03};
static char nt35532_ct_warm_cmd358[]={0xE4, 0xA8};
static char nt35532_ct_warm_cmd359[]={0xE5, 0x03};
static char nt35532_ct_warm_cmd360[]={0xE6, 0xBD};
static char nt35532_ct_warm_cmd361[]={0xE7, 0x03};
static char nt35532_ct_warm_cmd362[]={0xE8, 0xF1};
static char nt35532_ct_warm_cmd363[]={0xE9, 0x03};
static char nt35532_ct_warm_cmd364[]={0xEA, 0xFF};

static struct dsi_cmd_desc nt35532_ct_warm_cmd[] = {
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd1},//Gamma setting  R+
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd2},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd3},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd4},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd5},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd6},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd7},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd8},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd9},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd10},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd11},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd12},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd13},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd14},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd15},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd16},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd17},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd18},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd19},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd20},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd21},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd22},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd23},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd24},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd25},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd26},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd27},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd28},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd29},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd30},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd31},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd32},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd33},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd34},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd35},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd36},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd37},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd38},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd39},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd40},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd41},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd42},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd43},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd44},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd45},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd46},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd47},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd48},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd49},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd50},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd51},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd52},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd53},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd54},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd55},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd56},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd57},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd58},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd59},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd60},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd61},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd62},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd63},//R-
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd64},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd65},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd66},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd67},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd68},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd69},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd70},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd71},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd72},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd73},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd74},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd75},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd76},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd77},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd78},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd79},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd80},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd81},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd82},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd83},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd84},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd85},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd86},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd87},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd88},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd89},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd90},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd91},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd92},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd93},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd94},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd95},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd96},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd97},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd98},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd99},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd100},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd101},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd102},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd103},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd104},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd105},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd106},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd107},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd108},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd109},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd110},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd111},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd112},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd113},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd114},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd115},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd116},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd117},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd118},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd119},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd120},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd121},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd122},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd123},//G+
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd124},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd125},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd126},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd127},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd128},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd129},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd130},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd131},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd132},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd133},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd134},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd135},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd136},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd137},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd138},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd139},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd140},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd141},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd142},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd143},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd144},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd145},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd146},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd147},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd148},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd149},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd150},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd151},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd152},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd153},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd154},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd155},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd156},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd157},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd158},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd159},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd160},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd161},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd162},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd163},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd164},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd165},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd166},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd167},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd168},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd169},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd170},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd171},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd172},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd173},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd174},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd175},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd176},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd177},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd178},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd179},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd180},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd181},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd182},
  {{0x29,1,0,0,0,2},nt35532_ct_warm_cmd183},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd184},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd185},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd186},//G-
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd187},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd188},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd189},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd190},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd191},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd192},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd193},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd194},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd195},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd196},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd197},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd198},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd199},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd200},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd201},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd202},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd203},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd204},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd205},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd206},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd207},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd208},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd209},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd210},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd211},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd212},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd213},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd214},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd215},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd216},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd217},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd218},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd219},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd220},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd221},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd222},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd223},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd224},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd225},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd226},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd227},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd228},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd229},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd230},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd231},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd232},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd233},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd234},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd235},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd236},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd237},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd238},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd239},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd240},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd241},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd242},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd243},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd244},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd245},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd246},	//B+
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd247},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd248},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd249},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd250},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd251},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd252},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd253},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd254},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd255},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd256},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd257},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd258},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd259},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd260},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd261},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd262},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd263},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd264},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd265},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd266},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd267},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd268},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd269},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd270},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd271},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd272},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd273},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd274},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd275},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd276},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd277},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd278},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd279},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd280},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd281},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd282},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd283},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd284},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd285},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd286},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd287},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd288},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd289},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd290},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd291},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd292},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd293},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd294},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd295},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd296},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd297},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd298},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd299},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd300},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd301},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd302},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd303},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd304},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd305},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd306},//B-
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd307},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd308},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd309},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd310},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd311},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd312},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd313},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd314},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd315},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd316},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd317},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd318},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd319},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd320},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd321},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd322},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd323},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd324},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd325},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd326},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd327},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd328},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd329},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd330},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd331},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd332},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd333},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd334},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd335},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd336},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd337},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd338},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd339},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd340},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd341},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd342},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd343},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd344},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd345},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd346},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd347},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd348},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd349},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd350},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd351},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd352},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd353},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd354},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd355},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd356},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd357},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd358},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd359},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd360},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd361},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd362},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd363},
  {{0x29,0,0,0,0,2},nt35532_ct_warm_cmd364},
  {{0x29,1,0,0,0,2},nt35532_normal_mode_cmd},
};

static char nt35532_ce_soft_cmd1[] = {0x55,0x03};
static char nt35532_ce_default_cmd1[] = {0x55,0x83};
static char nt35532_ce_bright_cmd1[] = {0x55,0xB3};

static struct dsi_cmd_desc nt35532_ce_soft_cmd[] = {
	{{0x29,0,0,0,0,2},nt35532_normal_mode_cmd},
	{{0x29,1,0,0,0,2},nt35532_ce_soft_cmd1},
};
static struct dsi_cmd_desc nt35532_ce_default_cmd[] = {
	{{0x29,0,0,0,0,2},nt35532_normal_mode_cmd},
	{{0x29,1,0,0,0,2},nt35532_ce_default_cmd1},
};
static struct dsi_cmd_desc nt35532_ce_bright_cmd[] = {
	{{0x29,0,0,0,0,2},nt35532_normal_mode_cmd},
	{{0x29,1,0,0,0,2},nt35532_ce_bright_cmd1},
};

/*********************************** ce *************************************/
static char nt35532_ce0[] = {0x55,0x80};
static char nt35532_ce1[] = {0x55,0x90};
static char nt35532_ce2[] = {0x55,0xB0};

char *nt35532_ce[] = {
	nt35532_ce0,
	nt35532_ce1,
	nt35532_ce2,
};

static struct dsi_cmd_desc nt35532_effect_ce[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_ce0)}, nt35532_ce0},
};

struct lcd_effect_cmds nt35532_effect_ce_cmd[] = {
	{{nt35532_ce, ARRAY_SIZE(nt35532_ce)}, {nt35532_effect_ce, ARRAY_SIZE(nt35532_effect_ce)}},
};
/*********************************** cta *************************************/
static char nt35532_cta0[] = {0xC8,0x01,0x00,0x06,0xfd,0x05,0xFC,0x00,0x00,0x08,0xfc,0xfc,0x9e,0x00,0x00,0xfd,0xfe,0xf9,0x37,0x00};
static char nt35532_cta1[] = {0xC8,0x01,0x00,0x06,0xfd,0x05,0xFC,0x00,0x00,0x08,0xfc,0xfc,0x9e,0x00,0x00,0xfd,0xfe,0xf9,0x37,0x00};
static char nt35532_cta2[] = {0xC8,0x01,0x00,0x05,0xfd,0x05,0xFC,0x00,0x00,0x06,0xfd,0xff,0xa6,0x00,0x00,0xfd,0xfe,0xfa,0x54,0x00};

char *nt35532_cta[] = {
	nt35532_cta0,
	nt35532_cta1,
	nt35532_cta2,
};

static struct dsi_cmd_desc nt35532_effect_cta[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_cta0)}, nt35532_cta0},
};
struct lcd_effect_cmds nt35532_effect_cta_cmd[] = {
	{{nt35532_cta, ARRAY_SIZE(nt35532_cta)}, {nt35532_effect_cta, ARRAY_SIZE(nt35532_effect_cta)}},
};

/************************************* sre ***********************************/
static char nt35532_sre_cmd0[]={0xFF,0x03};
static char nt35532_sre_cmd1[]={0xFB,0x01};
static char nt35532_sre0[]={0x56,0x77};
static char nt35532_sre1[]={0x56,0x00};

char *nt35532_sre00[] = {
	nt35532_sre_cmd0,
	nt35532_sre_cmd0,
	nt35532_sre_cmd0,
	nt35532_sre_cmd0,
};

char *nt35532_sre01[] = {
	nt35532_sre_cmd1,
	nt35532_sre_cmd1,
	nt35532_sre_cmd1,
	nt35532_sre_cmd1,
};

char *nt35532_sre[] = {
	nt35532_sre0,
	nt35532_sre1,
	nt35532_sre0,
	nt35532_sre1,
};

static char nt35532_sre_cabc0[] = {0x00, 0x00};
static char *nt35532_sre_cabc[] = {
	nt35532_sre_cabc0,
};
static struct dsi_cmd_desc nt35532_effect_sre0[] = {
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(nt35532_sre_cmd0)}, nt35532_sre_cmd0},
};
static struct dsi_cmd_desc nt35532_effect_sre1[] = {
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(nt35532_sre_cmd1)}, nt35532_sre_cmd1},
};
static struct dsi_cmd_desc nt35532_effect_sre[] = {
	{{DTYPE_GEN_LWRITE, 0, 0, 0, 0, sizeof(nt35532_sre0)}, nt35532_sre0},
};
static struct dsi_cmd_desc nt35532_effect_sre_cabc[] = {
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(nt35532_sre_cabc0)}, nt35532_sre_cabc0},
};

struct lcd_effect_cmds nt35532_effect_sre_cmd[] = {
	{{nt35532_sre_cabc, ARRAY_SIZE(nt35532_sre_cabc)}, {nt35532_effect_sre_cabc, ARRAY_SIZE(nt35532_effect_sre_cabc)}},
	{{nt35532_sre, ARRAY_SIZE(nt35532_sre)}, {nt35532_effect_sre, ARRAY_SIZE(nt35532_effect_sre)}},
};

/************************************ cabc ***********************************/
//level0 and level3 outside light mode, cabc off, sre on
//level1 and level2 inside normal mode, cabc on, sre off 
static char nt35532_cabc0[] = {0x55, 0xB0};
static char nt35532_cabc1[] = {0x55, 0xB3};
static char nt35532_cabc2[] = {0x55, 0x80};
static char nt35532_cabc3[] = {0x55, 0x83};

char *nt35532_cabc00[] = {
	nt35532_normal_mode_cmd,
	nt35532_normal_mode_cmd,
	nt35532_normal_mode_cmd,
	nt35532_normal_mode_cmd,
};

char *nt35532_cabc[] = {
	nt35532_cabc0,
	nt35532_cabc1,
	nt35532_cabc2,
	nt35532_cabc3,
};
/*
static struct dsi_cmd_desc nt35532_effect_blc[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_blc0)}, nt35532_blc0},
};*/
static struct dsi_cmd_desc nt35532_effect_cabc0[] = {
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(nt35532_normal_mode_cmd)}, nt35532_normal_mode_cmd},
};
static struct dsi_cmd_desc nt35532_effect_cabc[] = {
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(nt35532_cabc0)}, nt35532_cabc0},
};
struct lcd_effect_cmds nt35532_effect_cabc_cmd[] = {
	{{nt35532_sre00, ARRAY_SIZE(nt35532_sre00)}, {nt35532_effect_sre0, ARRAY_SIZE(nt35532_effect_sre0)}},
	{{nt35532_sre01, ARRAY_SIZE(nt35532_sre01)}, {nt35532_effect_sre1, ARRAY_SIZE(nt35532_effect_sre1)}},
	{{nt35532_sre, ARRAY_SIZE(nt35532_sre)}, {nt35532_effect_sre, ARRAY_SIZE(nt35532_effect_sre)}},	
	{{nt35532_cabc00, ARRAY_SIZE(nt35532_cabc00)}, {nt35532_effect_cabc0, ARRAY_SIZE(nt35532_effect_cabc0)}},	
	{{nt35532_cabc, ARRAY_SIZE(nt35532_cabc)}, {nt35532_effect_cabc, ARRAY_SIZE(nt35532_effect_cabc)}},
};
/*************************************  aco ***********************************/
static char nt35532_aco0[] = {0xba,0x07,0xb0,0x00,0x00,0x00,0x87};
static char nt35532_aco1[] = {0xba,0x07,0xb0,0x00,0x00,0x00,0x87};


static char *nt35532_aco[] = {
	nt35532_aco0,
	nt35532_aco1,
};
#if 0
static char *nt35532_aco_blc[] = {
	nt35532_blc1,
};
#endif
static char nt35532_aco_cabc0[] = {0x55,0x03};
static char *nt35532_aco_cabc[] = {
	nt35532_aco_cabc0,
};
#if 0
static struct dsi_cmd_desc nt35532_effect_aco_blc[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_blc1)}, nt35532_blc1},
};
#endif

static struct dsi_cmd_desc nt35532_effect_aco_cabc[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35532_aco_cabc0)}, nt35532_aco_cabc0},
};

static struct dsi_cmd_desc nt35532_effect_aco[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_aco0)}, nt35532_aco0},
};

struct lcd_effect_cmds nt35532_effect_aco_cmd[] = {
	//{{nt35532_aco_blc, ARRAY_SIZE(nt35532_aco_blc)}, {nt35532_effect_aco_blc, ARRAY_SIZE(nt35532_effect_aco_blc)}},
	{{nt35532_aco_cabc, ARRAY_SIZE(nt35532_aco_cabc)}, {nt35532_effect_aco_cabc, ARRAY_SIZE(nt35532_effect_aco_cabc)}},
	{{nt35532_aco, ARRAY_SIZE(nt35532_aco)}, {nt35532_effect_aco, ARRAY_SIZE(nt35532_effect_aco)}},
};

/************************************* cr ***********************************/
#if 1
static char nt35532_cr0[] = {0x00,0x00,0x00,0x00};
static char nt35532_cr1[] = {0xbb,0x00,0x00,0x00};
static char nt35532_cr2[] = {0xbb,0x00,0x00,0x08};
static char nt35532_cr3[] = {0xbb,0x00,0x00,0x10};
static char nt35532_cr4[] = {0xbb,0x00,0x00,0x18};
static char nt35532_cr5[] = {0xbb,0x00,0x00,0x20};
static char nt35532_cr6[] = {0xbb,0x00,0x00,0x28};
static char nt35532_cr7[] = {0xbb,0x00,0x00,0x30};
static char nt35532_cr8[] = {0xbb,0x00,0x00,0x38};
static char nt35532_cr9[] = {0xbb,0x00,0x00,0x40};
static char nt35532_cr10[] = {0xbb,0x00,0x00,0x48};
static char nt35532_cr11[] = {0xbb,0x00,0x00,0x50};
static char nt35532_cr12[] = {0xbb,0x00,0x00,0x58};
static char nt35532_cr13[] = {0xbb,0x00,0x00,0x60};
static char nt35532_cr14[] = {0xbb,0x00,0x00,0x68};
static char nt35532_cr15[] = {0xbb,0x00,0x00,0x70};

char *nt35532_cr[] = {
	nt35532_cr0,
	nt35532_cr1,
	nt35532_cr2,
	nt35532_cr3,
	nt35532_cr4,
	nt35532_cr5,
	nt35532_cr6,
	nt35532_cr7,
	nt35532_cr8,
	nt35532_cr9,
	nt35532_cr10,
	nt35532_cr11,
	nt35532_cr12,
	nt35532_cr13,
	nt35532_cr14,
	nt35532_cr15,
};
static char nt35532_cr_cabc0[] = {0x55, 0x00};
static char *nt35532_cr_cabc[] = {
	nt35532_cr_cabc0,
};
static struct dsi_cmd_desc nt35532_effect_cr[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_cr0)}, nt35532_cr0},
};
static struct dsi_cmd_desc nt35532_effect_cr_cabc[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35532_cr_cabc0)}, nt35532_cr_cabc0},
};


struct lcd_effect_cmds nt35532_effect_cr_cmd[] = {
	{{nt35532_cr, ARRAY_SIZE(nt35532_cr)}, {nt35532_effect_cr, ARRAY_SIZE(nt35532_effect_cr)}},
	{{nt35532_cr_cabc, ARRAY_SIZE(nt35532_cr_cabc)}, {nt35532_effect_cr_cabc, ARRAY_SIZE(nt35532_effect_cr_cabc)}},
};
#endif

/************************************** normal mode **************************************/
static struct dsi_cmd_desc nt35532_normal_mode[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(nt35532_normal_mode_cmd)}, nt35532_normal_mode_cmd},
};
#if 0
/************************************** video mode **************************************/
static char video_mode_cmd0[] = {0x55,0x00};
static char video_mode_cmd1[] = {0xba,0x07,0x75,0x61,0x20,0x16,0x87};
static char video_mode_cmd2[] = {0xca,0x00,0xC8,0x80,0x80,0x80,0x80,0x80,0x80,0x12,0x29,0xAC,0x80,0x00,0x4A,0x37,0x80,0x55,0xF8,0x08,0x08,0x08,0x08,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10};
static char video_mode_cmd3[] = {0xc8,0x01,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00};
static struct dsi_cmd_desc video_mode_cmds[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(video_mode_cmd0)}, video_mode_cmd0},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(video_mode_cmd1)}, video_mode_cmd1},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(video_mode_cmd2)}, video_mode_cmd2},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(video_mode_cmd3)}, video_mode_cmd3},
};
/************************************** comfort mode **************************************/
static char comfort_mode_cmd0[] = {0xca,0x00,0x80,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0x20,0x20,0x20,0x80,0x00,0x42,0x44,0x80,0x69,0xda,0x08,0x08,0x08,0x08,0x08,0x04,0x00,0x00,0x10,0x10,0x3F,0x3F,0x3F,0x3F};
static char comfort_mode_cmd1[] = {0x55,0x03};
static char comfort_mode_cmd2[] = {0xba,0x07,0x75,0x61,0x20,0x16,0x87};
static char comfort_mode_cmd3[] = {0xc8,0x01,0x8c,0x06,0xfd,0x05,0xfc,0x00,0x8c,0x08,0xfc,0xfc,0x9e,0x00,0x8c,0xfd,0xfe,0xf9,0x37,0x00};

/************************************** outside mode **************************************/
static char outside_mode_cmd0[] = {0x55,0x73};
static char outside_mode_cmd1[] = {0xc8,0x01,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00};
static char outside_mode_cmd2[] = {0xca,0x01,0xC8,0x80,0x80,0x80,0x80,0x80,0x80,0x12,0x29,0xAC,0x80,0x00,0x4A,0x37,0x80,0x55,0xF8,0x08,0x08,0x08,0x08,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10};
static char outside_mode_cmd3[] = {0xba,0x05,0x3c,0xff,0x00,0x00,0x00};
static char outside_mode_cmd4[] = {0xbd,0x01,0x1e,0x14};
static struct dsi_cmd_desc outside_mode_cmds[] = {
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(outside_mode_cmd0)}, outside_mode_cmd0},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(outside_mode_cmd1)}, outside_mode_cmd1},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(outside_mode_cmd2)}, outside_mode_cmd2},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(outside_mode_cmd3)}, outside_mode_cmd3},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(outside_mode_cmd4)}, outside_mode_cmd4},
};

/************************************** ultra bright mode **************************************/
static char ultra_mode_cmd0[] = {0x55,0x03};
static char ultra_mode_cmd1[] = {0xba,0x07,0x75,0x61,0x20,0x16,0x87};
static char ultra_mode_cmd2[] = {0xca,0x01,0xC8,0x80,0x80,0x80,0x80,0x80,0x80,0x12,0x29,0xAC,0x80,0x00,0x4A,0x37,0x80,0x55,0xF8,0x08,0x08,0x08,0x08,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10};
static char ultra_mode_cmd3[] = {0xc8,0x01,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0x00};

static struct dsi_cmd_desc ultra_mode_cmds[] = {
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(nt35532_aco0)}, nt35532_aco0},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ultra_mode_cmd2)}, ultra_mode_cmd2},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ultra_mode_cmd3)}, ultra_mode_cmd3},
	{{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ultra_mode_cmd1)}, ultra_mode_cmd1},
	{{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(ultra_mode_cmd0)}, ultra_mode_cmd0},
};
#endif
/*********************************** all effect ************************************/
struct lcd_effect nt35532_effect[] = {
	{"cabc", ARRAY_SIZE(nt35532_cabc), 0, {nt35532_effect_cabc_cmd, ARRAY_SIZE(nt35532_effect_cabc_cmd)}},
	{"ce", ARRAY_SIZE(nt35532_ce), 0, {nt35532_effect_ce_cmd, ARRAY_SIZE(nt35532_effect_ce_cmd)}},
	{"cta", ARRAY_SIZE(nt35532_cta), 0, {nt35532_effect_cta_cmd, ARRAY_SIZE(nt35532_effect_cta_cmd)}},
	{"aco", ARRAY_SIZE(nt35532_aco), 0, {nt35532_effect_aco_cmd, ARRAY_SIZE(nt35532_effect_aco_cmd)}},
	{"gamma", ARRAY_SIZE(nt35532_sre), 0, {nt35532_effect_sre_cmd, ARRAY_SIZE(nt35532_effect_sre_cmd)}},
};
/**************************************************************************************/

/************************************** all mode **************************************/
struct lcd_mode nt35532_mode[] = {
	{"custom_mode", 0, {nt35532_normal_mode, ARRAY_SIZE(nt35532_normal_mode)}},
	{"ct_warm_mode", 0, {nt35532_ct_warm_cmd, ARRAY_SIZE(nt35532_ct_warm_cmd)}},
	{"ct_default_mode", 0, {nt35532_ct_default_cmd, ARRAY_SIZE(nt35532_ct_default_cmd)}},
	{"ct_cold_mode", 0, {nt35532_ct_cold_cmd, ARRAY_SIZE(nt35532_ct_cold_cmd)}},
	{"ce_soft_mode", 0, {nt35532_ce_soft_cmd, ARRAY_SIZE(nt35532_ce_soft_cmd)}},
	{"ce_default_mode", 0, {nt35532_ce_default_cmd, ARRAY_SIZE(nt35532_ce_default_cmd)}},
	{"ce_bright_mode", 0, {nt35532_ce_bright_cmd, ARRAY_SIZE(nt35532_ce_bright_cmd)}},
/*	{"auto_mode", 0, {nt35532_normal_mode, ARRAY_SIZE(nt35532_normal_mode)}},
	{"normal_mode", 0, {nt35532_normal_mode, ARRAY_SIZE(nt35532_normal_mode)}},
	{"comfort_mode", 0, {comfort_mode_cmds, ARRAY_SIZE(comfort_mode_cmds)}},
	{"outside_mode", 0, {outside_mode_cmds, ARRAY_SIZE(outside_mode_cmds)}},
	{"ultra_mode", 1, {ultra_mode_cmds, ARRAY_SIZE(ultra_mode_cmds)}},
	{"camera_mode", 0, {video_mode_cmds, ARRAY_SIZE(video_mode_cmds)}},*/
};
/**************************************************************************************/
static struct lcd_cmds nt35532_head_cmds =
	{nt35532_packet_head_cmds, ARRAY_SIZE(nt35532_packet_head_cmds)};

static struct lcd_effect_data nt35532_effect_data =
	{nt35532_effect, &nt35532_head_cmds, ARRAY_SIZE(nt35532_effect)};

static struct lcd_mode_data nt35532_mode_data =
	{nt35532_mode, &nt35532_head_cmds, ARRAY_SIZE(nt35532_mode), 0};

/**************************************************************************************/
struct panel_effect_data lcd_35532_data = {
	&nt35532_effect_data,
	&nt35532_mode_data,
};

#endif
