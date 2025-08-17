cmake_minimum_required(VERSION 3.8)
project(data_structure)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# === 실행 파일 추가 ===
add_executable(binary_search_tree src/binary_search_tree.cpp)
target_include_directories(binary_search_tree PUBLIC include)
ament_target_dependencies(binary_search_tree)

# 테스트 옵션
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  binary_search_tree
  DESTINATION lib/${PROJECT_NAME})

ament_package()
