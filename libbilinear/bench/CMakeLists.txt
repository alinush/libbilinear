set(bilinear_bench_sources
  RelicMicroBench.cpp
  FastMultExpBench.cpp
)

foreach(appSrc ${bilinear_bench_sources})
    get_filename_component(appName ${appSrc} NAME_WE)
    set(appDir ../bin/bench)

    add_executable(${appName} ${appSrc})
    target_link_libraries(${appName} PRIVATE bilinear_mainapp bilinear)

    set_target_properties(${appName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${appDir})
endforeach()
