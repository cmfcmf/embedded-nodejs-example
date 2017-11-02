cmake_minimum_required (VERSION 2.6)
project (embedded-nodejs-example)

# Replace $ENV{VENDOR}/nodejs/.." with the path to
# your Node.js includes
include_directories(SYSTEM $ENV{VENDOR}/nodejs/include )
include_directories(SYSTEM $ENV{VENDOR}/nodejs/include/v8_include )

add_library( nodejs-lib SHARED IMPORTED)

# Replace "$ENV{VENDOR}/nodejs/lib/${ANDROID_ABI}/libnode.so" with
# the path to your libnode.so shared lib
set_target_properties( nodejs-lib
                      PROPERTIES IMPORTED_LOCATION
                      $ENV{VENDOR}/nodejs/lib/${ANDROID_ABI}/libnode.so )


add_executable(embedded-nodejs-example main.cc)