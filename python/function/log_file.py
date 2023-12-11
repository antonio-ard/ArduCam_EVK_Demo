from ArducamEvkSDK import *


def main():
    camera = Camera()
    param = Param()
    log_file = "log.txt"
    if not camera.open(param):  # open camera, return True if success, otherwise return False
        raise Exception("open camera error! {}".format(get_error_name(camera.last_error)))  # get the last error message
    print("Disable Console Log")
    print("Save Log to {}".format(log_file))
    camera.enable_console_log(False)  # disable console log
    camera.log_level = LoggerLevel.Trace  # set log level to info
    camera.add_log_file(log_file)  # add log file

    # set camera config
    camera_config = CameraConfig()
    camera_config.height = 1080  # set height (required)
    camera_config.width = 1920  # set width (required)
    camera.config = camera_config  # set config to camera

    # init camera
    camera.init()
    camera.close()

    print("Log File Content:")
    with open(log_file, "r") as f:
        print(f.read())


if __name__ == '__main__':
    main()
