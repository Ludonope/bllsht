##
## Configuration
##
cmake_minimum_required(VERSION 3.14.5)
project(bllsht)

# Configure C++ version
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_COMPILER clang++)

# Configure build directory
set(OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# Configure serialization
if(UNIX AND NOT APPLE)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Weffc++ -Wno-deprecated-declarations")
elseif(APPLE)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-c++1z-extensions -Wno-deprecated-declarations")
endif()
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}")

##
## Libraries
##

# Get modbus library files
file(GLOB LIBMODBUSPP_SOURCES lib/modbuspp/*.cpp)
set(LIBMODBUSPP libmodbuspp)
add_library(${LIBMODBUSPP} STATIC ${LIBMODBUSPP_SOURCES})
target_include_directories(${LIBMODBUSPP} PUBLIC "./lib/modbuspp")

# Get Paho Mqtt library
find_package(OpenSSL REQUIRED)
find_library(paho-mqttpp3 NAMES libpaho-mqttpp3.so REQUIRED)
find_library(paho-mqtt3a NAMES libpaho-mqtt3a.so REQUIRED)

add_library(pahottpp SHARED IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

##
## Internal Libraries
##

# Get egse library files
file(GLOB LIBEGSE_SOURCES src/egse/*.cpp)
set(LIBEGSE libegse)
add_library(${LIBEGSE} STATIC ${LIBEGSE_SOURCES})
target_include_directories(${LIBEGSE} PUBLIC "./src" "./lib" "./src/egse")
target_link_libraries(${LIBEGSE} PRIVATE ${LIBMODBUSPP})

# Get broadcast library files
file(GLOB LIBBROADCAST_SOURCES src/broadcast/*.cpp)
set(LIBBROADCAST libbroadcast)
add_library(${LIBBROADCAST} STATIC ${LIBBROADCAST_SOURCES})
target_include_directories(${LIBBROADCAST} PUBLIC "./src" "./lib" "./src/broadcast" ${PAHOMQTTCPP_INCLUDES})
target_link_libraries(${LIBBROADCAST} PRIVATE pahottpp pahomqtt3a)

##
## Binary
##

# Create executable
file(GLOB BLLSHT_SOURCES src/bllsht/*.cpp)
set(BLLSHT bllsht)
add_executable(${BLLSHT} ${BLLSHT_SOURCES})
target_include_directories(${BLLSHT} PUBLIC "./src" "./lib")
target_link_libraries(${BLLSHT} PUBLIC ${LIBBROADCAST} ${LIBEGSE})

##
## Installation
##

if(WIN32)
# Install to %AppData% on Windows
install(TARGETS ${BLLSHT} DESTINATION $ENV{APPDATA}/bllsht/)
else()
install(TARGETS ${BLLSHT} DESTINATION /usr/local/bin/bllsht/)
endif()