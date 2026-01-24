cmake_minimum_required(VERSION 3.14)
project(Kalkulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)


if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/heads/main.zip
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
else()
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
endif()


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(KalkulatorLib
    src/Calculator.cpp
    src/Systems.cpp
)

target_include_directories(KalkulatorLib PUBLIC include)


add_executable(Kalkulator
    src/main.cpp
    src/Interface.cpp
)

target_link_libraries(Kalkulator PRIVATE KalkulatorLib)


enable_testing()

add_executable(TestyKalkulatora
    tests/Testy.cpp
)

target_link_libraries(TestyKalkulatora
    PRIVATE
    KalkulatorLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestyKalkulatora)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Kalkulator)