set(bilinear_mainapp_source_files
    Main.cpp
)

add_library(bilinear_mainapp STATIC ${bilinear_mainapp_source_files})
target_link_libraries(bilinear_mainapp PUBLIC xassert xutils)
target_include_directories(bilinear_mainapp PUBLIC ../include)

install(TARGETS bilinear_mainapp 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
