#include <stdio.h>
#include <stdbool.h>
#include "ImageProc.h"

int preparecamera(int videoid, int camerabase) {
    int ret;

	if(camerabase<0){
		camerabase = checkCamerabase();
	}

	ret = opendevice(camerabase + videoid);

	if(ret != ERROR_LOCAL){
		ret = initdevice();
	}
	if(ret != ERROR_LOCAL){
		ret = startcapturing();

		if(ret != SUCCESS_LOCAL){
			stopcapturing();
			uninitdevice ();
			closedevice ();
			printf("device resetted");	
		}

	}

	if(ret != ERROR_LOCAL){
		rgb = (int *)malloc(sizeof(int) * (IMG_WIDTH*IMG_HEIGHT));
		ybuf = (int *)malloc(sizeof(int) * (IMG_WIDTH*IMG_HEIGHT));
	}
	return ret;
}

int main() {
    bool cameraExists=false;
	bool shouldStop=false;
	
	// /dev/videox (x=cameraId+cameraBase) is used.
	// In some omap devices, system uses /dev/video[0-3],
	// so users must use /dev/video[4-].
	// In such a case, try cameraId=0 and cameraBase=4
	int cameraId=0;
	int cameraBase=0;
	
	// This definition also exists in ImageProc.h.
	// Webcam must support the resolution 640x480 with YUYV format. 
	// int IMG_WIDTH=640;
	// int IMG_HEIGHT=480;

	// The following variables are used to draw camera images.
    int winWidth=0;
    int winHeight=0;
    // private Rect rect;
    int dw, dh;
    float rate;

    int ret = preparecamera(cameraId, cameraBase);

    if(ret!=-1) cameraExists = true;

    while(1 && cameraExists) {
        readframeonce();
    }
    return 0;
}