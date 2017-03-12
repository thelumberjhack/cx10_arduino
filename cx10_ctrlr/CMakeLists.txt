cmake_minimum_required(VERSION 3.6)
project(cx10_ctrlr)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cx10.h
        cx10_ctrlr.ino
        iface_nrf24l01.h
        interface.h
        nrf24l01.c
        XN297_nRF24L01.cpp)

add_executable(cx10_ctrlr ${SOURCE_FILES})