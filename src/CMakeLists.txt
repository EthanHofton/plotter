set(SOURCES
    line.cpp
    plotter.cpp
)

set(LIBRARY_NAME plotter)

find_package(Boost REQUIRED COMPONENTS
    iostreams system filesystem
)

add_library(${LIBRARY_NAME}, ${SOURCES})

target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(plotter PUBLIC ${Boost_LIBRARIES})