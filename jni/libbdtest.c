#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "bd.h"
#include "mylog.h"
#include "com_ethan_datahidingdemo_receiver_MainActivity.h"
ulonglong* ciphertextbuf=NULL;
int thetextlength=0;
ulonglong* ksp=NULL;

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

int equal_ulonglong_arrays(ulonglong a1 [], ulonglong a2 [], int n)
{
    int i, result;
        for (i=0; i<n; ++i)
            if (a1[i] != a2[i])
                                return 0;
    return (1);
}

void XOR(uchar* source,uchar* target,uchar* key, int length)
{

    int count=0;
    for(count;count<length;count++)
    {
        target[count]=source[count]^key[count];
     }
    return;
}

ulong*  ucharbuf2ulongbuf(const uchar* _uchar){
	int ucharLength=strlen(_uchar);
	if (ucharLength==0)
		return NULL;
	ulong* ulongbuf= (ulong*)malloc(ucharLength*sizeof(ulong));
	
	int i=0;
	for(i;i<ucharLength;i++)
	{
		ulongbuf[i]=(ulong)_uchar[i];
	}
	return ulongbuf;
	}

ulonglong*  ucharbuf2ulonglongbuf(const uchar* _uchar){

	int ucharLength=strlen(_uchar);
	if (ucharLength==0)
		return NULL;
	ulonglong* ulonglongbuf= (ulonglong*)malloc(ucharLength*sizeof(ulonglong));
	int i=0;
	for(i;i<ucharLength;i++)
	{
		ulonglongbuf[i]=(ulonglong)_uchar[i];
	}
	return ulonglongbuf;
	}

uchar*  ulonglongbuf2uchar(const ulonglong* ulonglongbuf, int length){

	if (length==0)
		return NULL;
	uchar* charbuf = (uchar*)malloc((length+1)*sizeof(uchar));
    int i=0;
	for (i;i<length;i++)
	{
		charbuf[i]=(uchar)ulonglongbuf[i];
	}
	charbuf[length]='\0';
	return charbuf;
}




JNIEXPORT jbyteArray JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeEncrypt
  (JNIEnv* pEnv, jobject pObj, jstring aplaintext, jstring amasterkey){
	 /*Get the native string from javaString*/

}




JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeDecrypt
  (JNIEnv* pEnv, jobject pObj, jstring filepath, jstring amasterkey){
	 /*Get the native string from javaString*/
			char *native_filepath = (*pEnv)->GetStringUTFChars(pEnv,filepath,0);
		    char *nativemasterkey = (*pEnv)->GetStringUTFChars(pEnv,amasterkey,0);

		    LOGD("check point 1");
		    FILE *fl = fopen(native_filepath, "r");
		    fseek(fl, 0, SEEK_END);
		    int dataLength;
		    int msgLength = ftell(fl);
		    if(msgLength%8)
		    	dataLength = msgLength/8 + 1;
		    else dataLength = msgLength/8;
		    fseek(fl, 0, SEEK_SET);
		    uchar*  ucharBuf=(uchar*)malloc(msgLength*sizeof(uchar));
		    memset (ucharBuf,'\0',msgLength);
		    fread(ucharBuf, 1, msgLength, fl);
		    fclose(fl);

		    LOGD("check point 2");
		    int kslength = dataLength/2;
		    uchar* target = (uchar*)malloc(msgLength*sizeof(uchar));
		    uchar* source= ucharBuf;
		    //allocate and initiate
		    ulong iv[] = { 0, 0, 0, 0 };
		    //ulong* masterkey_ulong=ucharbuf2ulongbuf(nativemasterkey);
		    ulong masterkey_ulong[]={0,0,0,0};
	      	ulonglong* ks = (ulonglong*)malloc((dataLength)*sizeof(ulonglong));
	        //generate keystream

	        Dragon2_Ctx ctx;
	        BD_initkey(&ctx, masterkey_ulong);
	        BD_initiv(&ctx, iv);
	    	BD_keystream(&ctx, ks, kslength);
	    	uchar *ksArray = (unsigned char*)ks;

		    LOGD("check point 3");
	    	// encrypt
	        XOR(source, target, ksArray, msgLength);
	        uchar *ciphertextbuf=target;

		    LOGD("check point 4");
	        FILE *fp;
	        fp=fopen("/sdcard/receiver/decrypted.dat","wb");
	        fwrite(target,sizeof(uchar),msgLength,fp);
	        fclose(fp);

	        free(target);
	        free(ucharBuf);

	        (*pEnv)->ReleaseStringUTFChars(pEnv, filepath, native_filepath);

		    (*pEnv)->ReleaseStringUTFChars(pEnv, amasterkey, nativemasterkey);
		    return 0;

}


JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeBinaryDecrypt
  (JNIEnv* pEnv, jobject pObj, jstring binaryFilePath, jstring amasterkey){
	 /*Get the native string from javaString*/
		    uchar *nativeBinrayFilePath = (*pEnv)->GetStringUTFChars(pEnv, binaryFilePath, 0);
		    uchar *nativemasterkey= (*pEnv)->GetStringUTFChars(pEnv,amasterkey,0);

		    /*Do something with the nativeString*/
		    ulong iv[] = { 0, 0, 0, 0 };
		    LOGD("check point 1\n");
		    char encryptedFilePath[] = "/sdcard/receiver/received.dat";
		    int fileLength;
		    LOGD("check point 2\n");
		    FILE *fl = fopen(encryptedFilePath, "r");
		    fseek(fl, 0, SEEK_END);
		    int len = ftell(fl);
		    fseek(fl, 0, SEEK_SET);
		    LOGD("check point 3\n");
		    uchar*  ucharBuf=(uchar*)malloc(len*sizeof(uchar));
		    LOGD("check point 4\n");
		    fread(ucharBuf, 1, len, fl);
		    fclose(fl);
		    LOGD("File Length is %d\n",len);
		    fileLength=len;

		    int cryptoLength=fileLength/8;

		    int ksLength= cryptoLength/2;

		    ulonglong* target = (ulonglong*)malloc(cryptoLength*sizeof(ulonglong));
		    ulonglong* encrypted_ulonglong_buf=(ulonglong*)ucharBuf;
		    //ulong* masterkey_ulong=ucharbuf2ulongbuf(nativemasterkey);
		    ulong masterkey_ulong[]={0,0,0,0};
		    ulonglong* ks = (ulonglong*)malloc((cryptoLength)*sizeof(ulonglong));


		    Dragon2_Ctx ctx;
		    BD_initkey(&ctx, masterkey_ulong);
		    BD_initiv(&ctx, iv);
		    BD_keystream(&ctx, ks, ksLength);

		    XOR(encrypted_ulonglong_buf,target, ks, cryptoLength);

		    uchar* decrptedBuf = (uchar*)target;

		    FILE *f;
		    f=fopen("/sdcard/receiver/Receiveddecrypted.txt","wb");
		    fwrite(decrptedBuf,1,fileLength,f);
		    fclose(f);

		    (*pEnv)->ReleaseStringUTFChars(pEnv, binaryFilePath, nativeBinrayFilePath);
		    (*pEnv)->ReleaseStringUTFChars(pEnv, amasterkey, nativemasterkey);
		    //return (*pEnv)->NewStringUTF(pEnv,(char*)plaintextbuf);
		     return 0;
}


