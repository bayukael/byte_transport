cmake_minimum_required(VERSION 3.13)
project(pendarlab_lib_comm_byte_transport)

set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(NAMESPACE pendarlab)
set(PACKAGE_FILENAME byte_transport)

find_package(GTest CONFIG REQUIRED)

add_library(ByteTransport SHARED
    src/Registry.cpp
    src/RegistryUser.cpp
)
target_include_directories(ByteTransport PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_library(${NAMESPACE}::ByteTransport ALIAS ByteTransport)


##############################################################################
######################     Define Files to Install     #######################
##############################################################################

set(TARGET_EXPORT_NAME ByteTransportTargets)
set(TARGET_EXPORT_FILENAME byte_transport_targets)
set(PACKAGE_DIRECTORY_DESTINATION lib/cmake/byte_transport)

install(
	TARGETS ByteTransport
	EXPORT ${TARGET_EXPORT_NAME}
)
install(
	DIRECTORY include/
	DESTINATION include
)
install(
	EXPORT ${TARGET_EXPORT_NAME}
	FILE ${TARGET_EXPORT_FILENAME}.cmake
	NAMESPACE pendarlab::
	DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)

##############################################################################
##########################     CMake Packaging     ###########################
##############################################################################

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PACKAGE_FILENAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_FILENAME}-config.cmake
    INSTALL_DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_FILENAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# -------------------------------------------------
# 5. Install Config + Version files
# -------------------------------------------------
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_FILENAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_FILENAME}-config-version.cmake
    DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)