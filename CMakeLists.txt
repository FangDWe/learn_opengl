
cmake_minimum_required (VERSION 3.15)

project (learn_opengl)

add_definitions(-Dcurrent_path="${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
                        
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src_list)

add_executable (learn_opengl main.cpp ${src_list})

target_link_libraries(learn_opengl glfw3 opengl32 assimp-vc143-mt)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})