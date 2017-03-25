

#ifndef _MD5_H_ 
#define _MD5_H_ 

/*
 * Calculate and store in 'buff' the MD5 digest of 'uiFileLength' bytes at
 * 'ucFileData'. 'buff' must have enough space to hold 16 bytes.
 */
void MD5_File(unsigned char * ucFileData, unsigned int uiFileLength, unsigned char buff[16]);

#endif //_MD5_H_ 

