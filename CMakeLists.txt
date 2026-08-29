cmake_minimum_required(VERSION 3.16)
project(pong)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(Python3 REQUIRED COMPONENTS Interpreter)

execute_process(
		COMMAND ${Python3_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_config_var('LIBPL')); print(sysconfig.get_config_var('LDLIBRARY'))"
		OUTPUT_VARIABLE PYTHON_LIBRARY_INFO
		OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" ";" PYTHON_LIBRARY_INFO_LINES "${PYTHON_LIBRARY_INFO}")
list(GET PYTHON_LIBRARY_INFO_LINES 0 PYTHON_LIBDIR)
list(GET PYTHON_LIBRARY_INFO_LINES 1 PYTHON_LDLIBRARY)
set(PYTHON_LIBRARY_PATH "${PYTHON_LIBDIR}/${PYTHON_LDLIBRARY}")

add_library(pong_core src/game.cpp)
target_include_directories(pong_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(pong src/main.cpp)
target_link_libraries(pong PRIVATE pong_core)

add_executable(pong_tests tests/game_collision_tests.cpp)
target_link_libraries(pong_tests PRIVATE pong_core)

add_test(NAME pong_tests COMMAND pong_tests)

add_library(pong_py MODULE bindings/python_bindings.cpp)
target_include_directories(pong_py PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(pong_py PRIVATE pong_core "${PYTHON_LIBRARY_PATH}")
set_target_properties(pong_py PROPERTIES OUTPUT_NAME pong PREFIX "")

add_test(NAME pong_python_smoke COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/python_smoke.py)
set_tests_properties(pong_python_smoke PROPERTIES ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:pong_py>")

