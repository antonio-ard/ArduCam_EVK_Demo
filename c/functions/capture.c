#include <arducam/arducam_evk_sdk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "options.h"

void capture(const char* config_path, bool bin_config, int num) {
    ArducamCameraHandle camera;
    ArducamCameraOpenParam param;
    ArducamDefaultParam(&param);           // init camera open parameters with the default values
    param.config_file_name = config_path;  // a path of config file
    param.bin_config = bin_config;         // if the config file is a bin file
    int ret =
        ArducamOpenCamera(&camera, &param);  // open camera, return Success if success, otherwise return error code
    if (ret != Success) {
        // get the last error message
        printf("open error! %s\n", ArducamErrorName(ret));
        exit(-1);
    }
    ArducamInitCamera(camera);  // init camera
    ArducamStartCamera(camera);
    for (int i = 0; i < num; i++) {
        ArducamImageFrame image;
        // the ArducamCaptureImage return Success if success, otherwise return error code
        if (ArducamCaptureImage(camera, &image, 1000) == Success) {
            printf("get frame(%dx%d) from camera.\n", image.format.width, image.format.height);
            ArducamFreeImage(camera, image);
        }
    }
    ArducamStopCamera(camera);
    ArducamCloseCamera(camera);
}

int main(int argc, char** argv) {
    // clang-format off
    ARGPARSE_DEFINE(parse,
        (file, c, config, "Path to config file."),
        (int, n, take, "Number of frames to take.")
    );
    // clang-format on
    const char* info = "Capture images synchronously.";
    ARGPARSE_PARSE(parse, argc, argv, info, return 1, return 0);
    CHECK_REQUIRED(config, return 1);

    GET_CONFIG(config, path, bin);
    int take_val = GET_OR_DEFAULT(int, take, 1);

    capture(path, bin, take_val);

    ARGPARSE_FREE(parse);
    return 0;
}
