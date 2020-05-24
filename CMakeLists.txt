cmake_minimum_required(VERSION 3.14)
project(Homework)

# Using -Wall is required:
add_compile_options(-Wall)

# These compile flags are highly recommended, but not required:
add_compile_options(-Wextra -Wpedantic)

# Optional super-strict mode:
add_compile_options(-fmessage-length=80 -fno-diagnostics-show-option)
add_compile_options(-fstack-protector-all -g -O3 -std=c++14 -Walloc-zero)
add_compile_options(-Walloca -Wctor-dtor-privacy -Wduplicated-cond)
add_compile_options(-Wduplicated-branches -Werror -Wfatal-errors -Winit-self)
add_compile_options(-Wlogical-op -Wold-style-cast -Wshadow)
add_compile_options(-Wunused-const-variable=1 -Wzero-as-null-pointer-constant)

# add_compile_options must be BEFORE add_executable or add_library.

add_library(binomial_heap binomial_heap.cc)
add_executable(method_tests method_tests.cc)
add_executable(time_tests time_tests.cc)
target_link_libraries(method_tests binomial_heap)
target_link_libraries(time_tests binomial_heap)

# Create a tar file every time:
add_custom_target(binomial_heap.tar ALL COMMAND tar cf binomial_heap.tar binomial_heap.cc binomial_heap.h method_tests.cc time_tests.cc CMakeLists.txt)
