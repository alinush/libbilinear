#
# Targets
#

add_library(bilinear 
    Groups.cpp
    Library.cpp
    FastMultExp.cpp
    PublicParameters.cpp
)

message("binary include dir: ${CMAKE_CURRENT_BINARY_DIR}")

target_include_directories(bilinear PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>"
    "$<INSTALL_INTERFACE:${INSTALL_CMAKE_DIR}/include>"
)

target_link_libraries(bilinear PUBLIC relic)
target_link_libraries(bilinear PUBLIC xutils)
target_link_libraries(bilinear PUBLIC xassert)

#include(FindOpenMP)
#if(OPENMP_FOUND)
#    target_link_libraries(bilinear PUBLIC gomp)
#endif()
#target_link_libraries(bilinear PUBLIC Threads::Threads)

#
# Installation
# TODO: Add <Package>Config[Version].cmake files so this package can be easily imported?
# (See https://cmake.org/cmake/help/git-master/manual/cmake-packages.7.html#creating-packages)
#

# This creates the <Package>Config.cmake file and installs it
install(TARGETS bilinear EXPORT bilinearConfig 
   ARCHIVE DESTINATION lib)
install(EXPORT bilinearConfig DESTINATION lib/cmake/bilinear)

# This installs the static or (/and?) dynamic library
install(TARGETS bilinear 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# This installs the headers
# WARNING: Don't add / at the end. No slash means bilinear/ directory is created in the destination path
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/bilinear DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../include/bilinear DESTINATION include)
