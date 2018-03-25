set(bilinear_mainapp_source_files
    Main.cpp
)

add_library(mainapp STATIC ${bilinear_mainapp_source_files})
target_link_libraries(mainapp PUBLIC xassert xutils)
target_include_directories(mainapp PRIVATE ../include)
