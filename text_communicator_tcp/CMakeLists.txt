cmake_minimum_required(VERSION 3.10)

project(ChatProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)


add_executable(server server.c)
target_link_libraries(server PRIVATE Threads::Threads)

add_executable(client client.c)
target_link_libraries(client PRIVATE Threads::Threads)

configure_file(users.txt users.txt COPYONLY)
