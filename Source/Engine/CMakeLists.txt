## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Copyright (C) 2017-2020 by Agustin Alvarez. All rights reserved.
##
## This work is licensed under the terms of the Apache License, Version 2.0.
##
## See <https://opensource.org/licenses/Apache-2.0>.
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

PROJECT(Engine)

## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Dependencies
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

ExternalProject_Add(EASTL
        SOURCE_DIR "${ROOT_LIB_DIR}/EASTL"
        CMAKE_ARGS
            -DEASTL_BUILD_TESTS=OFF
            -DEASTL_BUILD_BENCHMARK=OFF
        INSTALL_COMMAND "")
ExternalProject_Get_Property(EASTL SOURCE_DIR)
ExternalProject_Get_Property(EASTL BINARY_DIR)
INCLUDE_DIRECTORIES(
    ${SOURCE_DIR}/include
    ${SOURCE_DIR}/test/packages/EAAssert/include
    ${SOURCE_DIR}/test/packages/EABase/include
    ${SOURCE_DIR}/test/packages/EABase/include/Common
    ${SOURCE_DIR}/test/packages/EAMain/include
    ${SOURCE_DIR}/test/packages/EAStdC/include)
LIST(APPEND PROJECT_LIB ${BINARY_DIR}${CONFIGURATION_SUFFIX}/EASTL.lib)
LIST(APPEND PROJECT_LIB d3d11)

## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Include
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Code
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

FILE(GLOB_RECURSE PROJECT_SRC "*.cpp")

## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Library
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

ADD_LIBRARY(Engine STATIC ${PROJECT_SRC})

## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
## Link
## -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

TARGET_LINK_LIBRARIES(Engine ${PROJECT_LIB})