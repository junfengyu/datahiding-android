#include <jni.h>
#include "com_ethan_datahidingdemo_receiver_MainActivity.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cctype>

#include <stdio.h>

#include <string>

#include <android/log.h>


#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))


struct Messageheader{
	unsigned int messagelength;
	char messagefiletype[4];
} messageheader;



JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_SteganographyDecode
  (JNIEnv* pEnv, jobject pObj, jstring imagePathName){
	const char  *aInputImage=pEnv->GetStringUTFChars(imagePathName,0);
	int i,j,k,l,t;
	IplImage* stegoimg = cvLoadImage(aInputImage);
	CvScalar pix;
	int h=stegoimg->height;
	int w=stegoimg->width;
	int nchannel = 3;
	int nplane = 3;
	int charsize = 8; //a character has 8 bits

	memset(&messageheader, 0, sizeof(messageheader));


	for(t=0;t<sizeof(messageheader.messagelength)*charsize;t++){//extract messagelength
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels

		messageheader.messagelength += (int(pix.val[k]) & (1u<<l))<<(t);

	}
	for(t=sizeof(messageheader.messagelength)*charsize;t<sizeof(messageheader)*charsize;t++){//embed message filetype
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels

		int pos = t - sizeof(messageheader.messagelength)*charsize;
		messageheader.messagefiletype[pos/charsize] += (int(pix.val[k]) & (1u<<l))<<(pos%charsize);
	}

	unsigned char *extractedmessage = new unsigned char [messageheader.messagelength+1];
	for(t=0;t<messageheader.messagelength;t++){
		extractedmessage[t] = '\0';
	}


		//data extraction start
	for(t=sizeof(messageheader)*charsize;t<(sizeof(messageheader)+messageheader.messagelength)*charsize;t++){
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels
		int pos = t - sizeof(messageheader)*charsize;
	    extractedmessage[pos/charsize] += (unsigned char)(((int(pix.val[k]) >> l)&1)<<(pos%charsize));
	}


	    FILE *fp;
	    char outputMsgFilePath[100]="/sdcard/receiver/ReceivedMsg.";
		strcat(outputMsgFilePath,messageheader.messagefiletype);
	    fp = fopen(outputMsgFilePath,"wb+");
		if(fp!=NULL){
		  fwrite(extractedmessage, 1 , messageheader.messagelength , fp );
		  fclose(fp);
		  delete[] extractedmessage;
	  	  return 0;
		}
		else{
		  delete[] extractedmessage;
		  return -1;
		}

}



JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_SteganographyFileDecode
  (JNIEnv* pEnv, jobject pObj, jstring imagePathName){
	const char  *aInputImage=pEnv->GetStringUTFChars(imagePathName,0);
	int i,j,k,l,t;
	IplImage* stegoimg = cvLoadImage(aInputImage);
	CvScalar pix;
	int h=stegoimg->height;
	int w=stegoimg->width;
	int nchannel = 3;
	int nplane = 3;
	int charsize = 8; //a character has 8 bits

	memset(&messageheader, 0, sizeof(messageheader));


	for(t=0;t<sizeof(messageheader.messagelength)*charsize;t++){//extract messagelength
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels

		messageheader.messagelength += (int(pix.val[k]) & (1u<<l))<<(t);

	}
	for(t=sizeof(messageheader.messagelength)*charsize;t<sizeof(messageheader)*charsize;t++){//embed message filetype
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels

		int pos = t - sizeof(messageheader.messagelength)*charsize;
		messageheader.messagefiletype[pos/charsize] += (int(pix.val[k]) & (1u<<l))<<(pos%charsize);
	}

	unsigned char *extractedmessage = new unsigned char [messageheader.messagelength+1];
	for(t=0;t<messageheader.messagelength;t++){
		extractedmessage[t] = '\0';
	}


		//data extraction start
	for(t=sizeof(messageheader)*charsize;t<(sizeof(messageheader)+messageheader.messagelength)*charsize;t++){
		j=t%w;//which column
		i=(t/w)%h;//which row
		k=(t/(h*w))%nchannel;//which channel
		l=(t/(h*w*nchannel))%nplane; //which LSB plane
		pix=cvGet2D(stegoimg,i,j); // has 3 channels
		int pos = t - sizeof(messageheader)*charsize;
	    extractedmessage[pos/charsize] += (unsigned char)(((int(pix.val[k]) >> l)&1)<<(pos%charsize));
	}


	    FILE *fp;
	    char outputMsgFilePath[100]="/sdcard/receiver/ReceiveEncryptedFile.";
		strcat(outputMsgFilePath,messageheader.messagefiletype);
	    fp = fopen(outputMsgFilePath,"wb+");
		if(fp!=NULL){
		  fwrite(extractedmessage, 1 , messageheader.messagelength , fp );
		  fclose(fp);
		  delete[] extractedmessage;
	  	  return 0;
		}
		else{
		  delete[] extractedmessage;
		  return -1;
		}

}
