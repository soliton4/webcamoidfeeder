#include "feeder.h"


#include "VirtualCamera/src/dshow/VirtualCameraFilter/ipc/src/ipcbridge.h"
#include "VirtualCamera/src/dshow/VirtualCameraFilter/ipc/src/filtercommons.h"

#include <uuids.h>

IpcBridge* gBridge = 0;
bool gBridgeopen = false;

unsigned char* gData = 0;

Feeder::Feeder()
{

}

void Feeder::feed(bool white){
    int width = 640;
    int height = 480;

    if (!gBridge){
        gBridge = new IpcBridge(IPC_FILE_NAME);
        gBridgeopen = gBridge->open(IpcBridge::Write);
        gData = (unsigned char*)malloc(3 * width * height);
    };

    if (gBridgeopen) {


        for (int h = 0; h < height; ++h){
            for (int w = 0; w < width; ++w){
                int pos = (h * width * 3) + (w * 3);
                BYTE fill = 0;
                if (white){
                    fill = 255;
                };
                gData[pos] = fill;
                gData[pos + 1] = fill;
                gData[pos + 2] = fill;
            };
        };

        // Fill data.

        gBridge->write(MEDIASUBTYPE_RGB24, width, height, gData);

        //gBridge->close();
    }


};
