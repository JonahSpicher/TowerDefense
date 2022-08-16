cmake_minimum_required(VERSION 3.10)

# set the project name
project(TOWERDEFENSE)
find_package(SFML 2.5.1 COMPONENTS system window graphics)

# add the executable
add_executable(game TowerDefense.cpp Tower.cpp Enemy.cpp)
#link libraries
target_link_libraries(game sfml-graphics)
