#include <stdio.h>
#include <stdbool.h>
#include "ImageProc.h"

int main() {

    bool cameraExists = false;
	bool shouldStop;
	
	// /dev/videox (x=cameraId+cameraBase) is used.
	// In some omap devices, system uses /dev/video[0-3],
	// so users must use /dev/video[4-].
	// In such a case, try cameraId=0 and cameraBase=4
	int cameraId = 0;
	//int cameraBase=0;
	
	// This definition also exists in ImageProc.h.
	// Webcam must support the resolution 640x480 with YUYV format. 
	// int IMG_WIDTH=640;
	// int IMG_HEIGHT=480;

	// The following variables are used to draw camera images.
    int winWidth = 0;
    int winHeight = 0;
    // private Rect rect;
    int dw, dh;
    float rate;

    int ret2;

	printf("started!");

    ret2 = preparecamera(cameraId);

    if(ret2!=-1) cameraExists = true;

	printf("ret : %d", ret2);

    while(1 && cameraExists) {
        readframeonce();
    }
    return 0;
}
