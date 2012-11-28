
set (arduino-android_SRCS
    arduino-android.cpp
    USB_Host_Shield/Max3421e.cpp
    USB_Host_Shield/Usb.cpp
)

include_directories(USB_Host_Shield)

set(arduino-android_BOARD mega2560)
set(arduino-android_SERIAL screen @SERIAL_PORT@)
set(arduino-android_PORT /dev/ttyACM0)

generate_arduino_firmware(arduino-android)
