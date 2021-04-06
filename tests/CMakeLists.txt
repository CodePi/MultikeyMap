cmake_minimum_required(VERSION 2.8)
project(MultikeyMap)

add_executable(MultikeyMap_test MultikeyMap_test.cpp)
add_executable(MultikeyMap_test2 MultikeyMap_test2.cpp)

add_test(MultikeyMap_test MultikeyMap_test)
add_test(MultikeyMap_test2 MultikeyMap_test2)