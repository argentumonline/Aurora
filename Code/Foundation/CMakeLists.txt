####################################################################################################
### Copyright (C) 2019 Agustin L. Alvarez. All rights reserved.
###
### This work is licensed under the terms of the Apache License, Version 2.0.
###
### See <https://opensource.org/licenses/Apache-2.0>.
####################################################################################################

PROJECT(Aurora CXX)

# TODO: Move to script folder and make it global
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WINDLL -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0601")

####################################################################################################
# [PROJECT:INCLUDE]
####################################################################################################

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

####################################################################################################
# [PROJECT:SOURCE]
####################################################################################################

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/**.cpp")

####################################################################################################
# [PROJECT:EXECUTABLE]
####################################################################################################

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCES})