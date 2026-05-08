cmake_minimum_required(VERSION 3.16)
project(biblioteca_distribuida LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)

include_directories(${ZeroMQ_INCLUDE_DIRS} src)
link_directories(${ZeroMQ_LIBRARY_DIRS})
add_definitions(${ZeroMQ_CFLAGS_OTHER})

add_executable(requester_ps src/requester_ps.cpp)
add_executable(load_manager src/load_manager.cpp)
add_executable(actor_devolucion src/actor_devolucion.cpp)
add_executable(actor_renovacion src/actor_renovacion.cpp)
add_executable(actor_prestamo src/actor_prestamo.cpp)

target_link_libraries(requester_ps PRIVATE ${ZeroMQ_LIBRARIES})
target_link_libraries(load_manager PRIVATE ${ZeroMQ_LIBRARIES})
target_link_libraries(actor_devolucion PRIVATE ${ZeroMQ_LIBRARIES})
target_link_libraries(actor_renovacion PRIVATE ${ZeroMQ_LIBRARIES})
target_link_libraries(actor_prestamo PRIVATE ${ZeroMQ_LIBRARIES})
