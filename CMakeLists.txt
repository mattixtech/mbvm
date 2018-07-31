cmake_minimum_required(VERSION 3.10)
project(mbvm C)

set(CMAKE_C_STANDARD 11)

# Create an exec directory to store the build products in
set(EXEC_DIRECTORY ../exec)
file(MAKE_DIRECTORY ${EXEC_DIRECTORY})
add_custom_target(create-exec-dir ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${EXEC_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXEC_DIRECTORY})

set(SOURCES_MAIN
        src/instructions/instruction_exec.c
        src/instructions/instruction_exec.h
        src/instructions/instruction_utils.c
        src/instructions/instruction_utils.h
        src/instructions/instructions.c
        src/instructions/instructions.h
        src/io/load.c
        src/io/load.h
        src/system/system.c
        src/system/system.h
        src/util/util.c
        src/util/util.h
        src/vm/vm.c
        src/vm/vm.h)
set(SOURCES_MAIN_MBVM src/mbvm.c)

set(SOURCES_TEST
        tests/instructions/test_instructions.c
        tests/instructions/test_instructions.h
        tests/system/test_system.c
        tests/system/test_system.h
        tests/vm/test_vm.c
        tests/vm/test_vm.h
        tests/test_registry.c)
set(SOURCES_TEST_REGISTRY)

# Main executable
add_executable(mbvm ${SOURCES_MAIN} ${SOURCES_MAIN_MBVM})
add_dependencies(mbvm create-exec-dir)

# Test executable
enable_testing()
add_executable(mbvm_test EXCLUDE_FROM_ALL ${SOURCES_MAIN} ${SOURCES_TEST}
        ${SOURCES_TEST_REGISTRY})
add_dependencies(mbvm_test create-exec-dir)
# We need to link CUnit to the test exe
target_link_libraries(mbvm_test PRIVATE "-lcunit")
add_test(mbvm_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mbvm_test)

