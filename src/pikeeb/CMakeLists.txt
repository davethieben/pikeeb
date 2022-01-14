# CMakeList.txt : CMake project for pikeeb, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pikeeb "main.cpp" "PiMatrix.h" "PiMatrix.cpp" "HidKeyboard.h" "HidKeyboard.cpp" "UsbHidKeys.h" "Event.cpp")

target_link_libraries(pikeeb wiringPi)

