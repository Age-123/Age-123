cmake_minimum_required (VERSION 3.9)

#must put it here , or don't work
set(CMAKE_C_COMPILER /opt/rh/devtoolset-9/root/bin/gcc CACHE PATH "")
set(CMAKE_CXX_COMPILER /opt/rh/devtoolset-9/root/bin/g++ CACHE PATH "")
# Default c++ standard used unless otherwise specified in target_compile_features.
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable compiler specific extensions like gnu++11.

project(DefGenerator VERSION 1
  LANGUAGES CXX
)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(INCLUDE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)
add_subdirectory(src)
add_compile_options(-g)
set(BIN "defgenerator")
add_executable(${BIN}
  main.cpp
)
target_include_directories(${BIN}
PUBLIC
   ${PROJECT_SOURCE_DIR}/include
)
 
link_directories(
  {PROJECT_SOURCE_DIR}/build_release/lib/
)
target_link_libraries(${BIN}
def_verilog)
target_link_libraries(${BIN}
${PROJECT_SOURCE_DIR}/build_release/lib/libdef_verilog.a
)



