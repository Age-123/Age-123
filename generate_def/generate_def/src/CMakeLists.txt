include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB_RECURSE ALL_SRC "*.cpp")
set(LIB_SOURCES
${ALL_SRC}
)
add_compile_options(-g)
add_library(def_verilog STATIC
  ${LIB_SOURCES}
)
