# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/software/Espressif/frameworks/esp-idf-v5.3.1/components/bootloader/subproject"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/tmp"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/src/bootloader-stamp"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/src"
  "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/github/esp32_learn/test_demo/blink_led_blue/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
