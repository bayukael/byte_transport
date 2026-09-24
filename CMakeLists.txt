cmake_minimum_required(VERSION 3.13)
project(pendarlab_lib_comm_byte_transport VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(NAMESPACE pendarlab)
set(PACKAGE_FILENAME byte_transport)
set(PACKAGE_NAME PendarlabByteTransport)

# Append the version to the install prefix so each release installs into its own
# subdirectory (<prefix>/<version>/), letting multiple versions coexist and be
# switched via CMAKE_PREFIX_PATH without the user typing the version.
string(REGEX REPLACE "/+$" "" _bt_base "${CMAKE_INSTALL_PREFIX}")
if(NOT _bt_base MATCHES "/${PROJECT_VERSION}$")
    set(CMAKE_INSTALL_PREFIX "${_bt_base}/${PROJECT_VERSION}" CACHE PATH "" FORCE)
endif()

find_package(GTest CONFIG REQUIRED)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/byte_transport/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/byte_transport/Version.h
    @ONLY
)

add_library(ByteTransport SHARED
    src/Registry.cpp
    src/RegistryUser.cpp
)
target_include_directories(ByteTransport PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_library(${NAMESPACE}::ByteTransport ALIAS ByteTransport)
set_target_properties(ByteTransport PROPERTIES
    OUTPUT_NAME pendarlab-byte_transport
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

##############################################################################
######################     MockTransportDefinition     #######################
##############################################################################
add_library(ByteTransportMockTransport SHARED
    test/mock_transport/MockTransportDefinition.cpp
    test/mock_transport/MockTransport.cpp
)
target_include_directories(ByteTransportMockTransport PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>
)


##############################################################################
#########################     ByteTransport Test     #########################
##############################################################################
add_executable(ByteTransportTest
    test/byte_transport_test.cpp
)
target_include_directories(ByteTransportTest PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>
)
target_link_libraries(ByteTransportTest
    PRIVATE ByteTransport
    PRIVATE ByteTransportMockTransport
    PRIVATE gtest
)


##############################################################################
######################     Define Files to Install     #######################
##############################################################################

set(TARGET_EXPORT_NAME ByteTransportTargets)
set(TARGET_EXPORT_FILENAME byte_transport_targets)
set(PACKAGE_DIRECTORY_DESTINATION lib/cmake/${PACKAGE_NAME})

install(
	TARGETS ByteTransport
	EXPORT ${TARGET_EXPORT_NAME}
)
install(
	DIRECTORY include/
	DESTINATION include
	PATTERN "*.in" EXCLUDE
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/include/byte_transport/Version.h
	DESTINATION include/byte_transport
)
install(
	EXPORT ${TARGET_EXPORT_NAME}
	FILE ${TARGET_EXPORT_FILENAME}.cmake
	NAMESPACE ${NAMESPACE}::
	DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)

##############################################################################
##########################     CMake Packaging     ###########################
##############################################################################

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PACKAGE_FILENAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
    INSTALL_DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# -------------------------------------------------
# 5. Install Config + Version files
# -------------------------------------------------
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake
    DESTINATION ${PACKAGE_DIRECTORY_DESTINATION}
)