##
## Configuration
##
cmake_minimum_required(VERSION 3.14.5)
project(bllsht)

# Configure C++ version
set(CMAKE_CXX_STANDARD 14)

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
## Binary
##

# Create executable
file(GLOB BLLSHT_SOURCES src/bllsht/*.cpp)
set(BLLSHT bllsht)
add_executable(${BLLSHT} ${BLLSHT_SOURCES})
target_include_directories(${BLLSHT} PUBLIC "./src")
# target_link_libraries(${SPIDER_CLIENT} PUBLIC ${LIBNETWORK} ${LIBLOGGER} ${LIBLOADER} ${LIBMT} ${LIBMACADDR} ${OPENSSL_LIBRARIES})
# if(UNIX AND NOT APPLE)
# target_link_libraries(${SPIDER_CLIENT} PUBLIC -lpthread -ldl)
# endif()

##
## Installation
##

if(WIN32)
# Install to %AppData% on Windows
install(TARGETS ${BLLSHT} DESTINATION $ENV{APPDATA}/bllsht/)
else()
install(TARGETS ${BLLSHT} DESTINATION /usr/local/bin/bllsht/)
endif()