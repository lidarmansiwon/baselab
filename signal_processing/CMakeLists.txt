cmake_minimum_required(VERSION 3.8)
project(signal_processing)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(INCLUDE_DIRECTORIES 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
include_directories(include)
install(
  DIRECTORY include/
  DESTINATION include
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(Python3 COMPONENTS Development NumPy REQUIRED)

# Add your test executable
add_executable(dft_example src/signal_processing/dft_example.cpp)

# Set include directories
# target_include_directories(dft_example PUBLIC ${INCLUDE_DIRECTORIES})
target_include_directories(dft_example PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${Python3_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/signal_processing/signal_processing   # 헤더 위치
)

target_link_libraries(dft_example PRIVATE Python3::Python Python3::NumPy)

install(TARGETS
  dft_example

  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
