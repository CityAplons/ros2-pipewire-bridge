cmake_minimum_required(VERSION 3.8)
project(pw_client)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pw_interfaces REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PIPEWIRE REQUIRED libpipewire-0.3)

add_library(pw_client SHARED
  src/pw_client.cpp
  src/client.cpp)
target_link_libraries(pw_client
  ${PIPEWIRE_LIBRARIES})
target_include_directories(pw_client PUBLIC
  ${PIPEWIRE_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(pw_client PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17
target_compile_options(pw_client PUBLIC ${PIPEWIRE_CFLAGS_OTHER})

ament_target_dependencies(pw_client
  rclcpp
  pw_interfaces
)

ament_export_targets(pw_client HAS_LIBRARY_TARGET)
install(
  TARGETS pw_client
  EXPORT pw_client
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(DIRECTORY
  include/pw_client
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}_test_client test/test_client.cpp)

  target_link_libraries(${PROJECT_NAME}_test_client pw_client)
  target_include_directories(${PROJECT_NAME}_test_client PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
  )
endif()

ament_export_include_directories(include)
ament_export_libraries(pw_client)
ament_export_dependencies(${DEPENDENCIES})
ament_package()
