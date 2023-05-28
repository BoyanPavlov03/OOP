project(Tables_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(Tables_tests_run
        DoubleCellTests.cpp
        FormulaCellTests.cpp
        StringCellTests.cpp
        TableTests.cpp
        IntegerCellTests.cpp)

target_link_libraries(Tables_tests_run Tables_lib)
target_link_libraries(Tables_tests_run gtest gtest_main)