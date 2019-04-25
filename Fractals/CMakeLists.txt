cmake_minimum_required(VERSION 3.9)
project(Lab_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


set(SFML_ROOT "D:/Archive/Programming projects/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics network audio window system)

add_executable(${PROJECT_NAME} main.cpp
        Fluctlight/Fluctlight.cpp Fluctlight/Fluctlight.hpp
        Fractals/Base/Fractal.cpp Fractals/Base/Fractal.hpp
        Fractals/B/B.cpp Fractals/B/B.hpp
        Fractals/A/A.cpp Fractals/A/A.hpp
        TimeCounter/TimeCounter.hpp
        FrameCounter/FrameCounter.hpp
        TexturePrinter/TexturePrinter.cpp TexturePrinter/TexturePrinter.hpp
        Utilites/CycleIterator.hpp
        Utilites/Misc.hpp Utilites/Misc.cpp Fractals/C/C.cpp Fractals/C/C.hpp Utilites/WindowForTests/WindowForTests.cpp Utilites/WindowForTests/WindowForTests.hpp)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
