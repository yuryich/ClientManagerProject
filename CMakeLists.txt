cmake_minimum_required(VERSION 3.20)
project(ClientManagerProject)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажите пути к исходным и заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Подключение библиотеки libpqxx
add_subdirectory(C:\Users\Долгова Елена\libpqxx-7.9.2)

# Укажите главный исполняемый файл
add_executable(ClientManagerProject main.cpp ${SOURCES})
target_link_libraries(ClientManagerProject pqxx)