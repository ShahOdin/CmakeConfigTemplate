CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
##A template for a package containing multiple projects, in this case: Hello and Bye.
PROJECT(Words)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
############################################################
## Versioning/installation information
set(PROJECT_VERSION         "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_DIRNAME         "${PROJECT_NAME}-${PROJECT_VERSION}")

set(PROJECT_DIRNAME_lib     "lib/${PROJECT_DIRNAME}")
set(PROJECT_DIRNAME_include "include/${PROJECT_DIRNAME}")

############################################################

add_library(Hello   SHARED  Hello/Hello.cpp )
add_library(Bye     STATIC  Bye/Bye.cpp )

##List of libraries in the project
set(PROJECT_LIBRARIES
        Hello
        Bye)

##Installation target for Headers for the libraries.
install(
        FILES
        Hello/Hello.h
        DESTINATION
        ${PROJECT_DIRNAME_include}/Hello
)
install(
        FILES
        Bye/Bye.h
        DESTINATION
        ${PROJECT_DIRNAME_include}/Bye
)
##Installation target for the Libraries exported from this package.
install(
        TARGETS
        Bye
        Hello
        DESTINATION
        ${PROJECT_DIRNAME_lib}
        EXPORT
        ${PROJECT_NAME}Exports
)

install(
        EXPORT
        ${PROJECT_NAME}Exports
        DESTINATION
        ${PROJECT_DIRNAME_lib}
)

############################################################
##Config file configurations. PROJECT_DIRNAME_include will be made relocatable.

include(CMakePackageConfigHelpers)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION
        ${PROJECT_DIRNAME_lib}
        PATH_VARS
        PROJECT_DIRNAME_include
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

############################################################
##Installation target for the COnfig files configured in the previous step.

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION
        ${PROJECT_DIRNAME_lib}
)
############################################################
