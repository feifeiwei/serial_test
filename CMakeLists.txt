cmake_minimum_required(VERSION 2.8)

project(bsnn-apps)

set(COREIP_SAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs -O3 -s -DNDEBUG")


# mf add
#link_directories(/home/official_code/lib)
find_package(OpenCV REQUIRED)

find_package(Protobuf REQUIRED)

message(STATUS "OpenCV libaray information:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    header file: ${OpenCV_INCLUDE_DIRS}")

if (PROTOBUF_FOUND)
    message("protobuf found")
else ()
    message(FATAL_ERROR "Cannot find Protobuf")
endif ()

include_directories(
    /home/official_code/include/bsnn
    /home/official_code/bsnn/3rdparty/bst_isp/include
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    /home/tools/serial-main/include
    )


find_library(
    BSNN_LIB
    NAMES bsnn
    /home/official_code/usr/lib64
    # CMAKE_FIND_ROOT_PATH is set to ONLY which limits the search path of find_library
    # refer to /opt/bstos/a1000/2.1.1.4/sysroots/x86_64-bstsdk-linux/usr/share/cmake/OEToolchainConfig.cmake
    # avoid it to make search path in HINTS work
    # NO_CMAKE_FIND_ROOT_PATH
)
if (NOT BSNN_LIB)
    message(FATAL_ERROR "libbsnn.so Not Found!")
else()
    message (STATUS "BSNN_LIB library found in ${BSNN_LIB}")
endif()

find_library(
    ISP_LIB
    NAMES bstisp
    HINTS /home/test_infer_yolo/3rdparty/bst_isp/lib
    # CMAKE_FIND_ROOT_PATH is set to ONLY which limits the search path of find_library
    # refer to /opt/bstos/a1000/2.1.1.4/sysroots/x86_64-bstsdk-linux/usr/share/cmake/OEToolchainConfig.cmake
    # avoid it to make search path in HINTS work
    NO_CMAKE_FIND_ROOT_PATH
)
if (NOT ISP_LIB)
    message(FATAL_ERROR "libbstisp.so Not Found!")
else()
    message (STATUS "ISP_LIB library found in ${ISP_LIB}")
endif()



find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)
find_library(AVUTIL_LIBRARY avutil)
find_library(SWSCALE_LIBRARY swscale)
find_library(AVFILTER_LIBRARY avfilter)
message (STATUS "AVCODEC_LIBRARY library found in ${AVCODEC_LIBRARY}")

# serial lib ``````````````````````````````````````````````````````
find_library(lib_serial 
            NAMES serial 
            HINTS /home/tools/serial-main/build
            NO_CMAKE_FIND_ROOT_PATH)

if (NOT lib_serial)
    message (FATAL_ERROR "required serial library but not found!")
else()
    message (STATUS "serial library found in ${lib_serial}")
endif()


# cyber lib ```````````````````````````````````````````````````````````````
find_library(LIBcyber_proto
            NAMES libcyber_proto.so 
            HINTS /opt/bstos/2.2.5.3/sysroots/aarch64-bst-linux/usr/lib64
            NO_CMAKE_FIND_ROOT_PATH)

if (NOT LIBcyber_proto)
    message (FATAL_ERROR "required LIBcyber_proto library but not found!")
else()
    message (STATUS "LIBcyber_proto library found in ${LIBcyber_proto}")
endif()


find_library(LIBads_log
            NAMES libads_log.so  
            HINTS /opt/bstos/2.2.5.3/sysroots/aarch64-bst-linux/usr/lib64
            NO_CMAKE_FIND_ROOT_PATH)

if (NOT LIBads_log)
    message (FATAL_ERROR "required LIBads_log library but not found!")
else()
    message (STATUS "LIBads_log library found in ${LIBads_log}")
endif()

find_library(lib_fastrtps
            NAMES fastrtps  
            HINTS /opt/bstos/2.2.5.3/sysroots/aarch64-bst-linux/usr/lib
            NO_CMAKE_FIND_ROOT_PATH)

find_library(lib_cyber 
            NAMES cyber  
            HINTS /opt/bstos/2.2.5.3/sysroots/aarch64-bst-linux/usr/lib
            NO_CMAKE_FIND_ROOT_PATH)

if (NOT lib_cyber OR NOT lib_fastrtps)
    message (FATAL_ERROR "required lib_cyber library but not found!")
    message (FATAL_ERROR "required lib_fastrtps library but not found!")
else()
    message (STATUS "lib_cyber library found in ${lib_cyber}")
    message (STATUS "lib_fastrtps library found in ${lib_fastrtps}")
endif()

########``````````````````````````````````````````````````````````````````````````


# --- protobuf --------
set(PROTO_FILES 
                /home/serial_test/proto/control_base.proto
                /home/serial_test/proto/config.proto
                )
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")


message(">>>---------------------------------------------------------------------")
get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${dirs}") #打印一下目录情况
message(">>>---------------------------------------------------------------------")

add_executable(serial_port
                src/main.cpp
                ${PROTO_SRCS}
                ${PROTO_HDRS}
                )

add_executable(listener 
                src/listener.cpp
                ${PROTO_SRCS}
                ${PROTO_HDRS}
                )

add_executable(publisher 
                src/publisher.cpp
                ${PROTO_SRCS}
                ${PROTO_HDRS}
                )
target_link_libraries(serial_port ${LIBcyber_proto} ${lib_serial} ${LIBads_log} ${lib_fastrtps} ${lib_cyber} ${PROTOBUF_LIBRARIES})
target_link_libraries(listener ${LIBcyber_proto} ${lib_serial} ${LIBads_log} ${lib_fastrtps} ${lib_cyber} ${PROTOBUF_LIBRARIES})
target_link_libraries(publisher ${LIBcyber_proto} ${lib_serial} ${LIBads_log} ${lib_fastrtps} ${lib_cyber} ${PROTOBUF_LIBRARIES})
