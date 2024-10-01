add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Arguments)
target_link_libraries(${PROJECT_NAME} PRIVATE Tsv)
target_link_libraries(${PROJECT_NAME} PRIVATE Queue)
target_link_libraries(${PROJECT_NAME} PRIVATE Image)
target_link_libraries(${PROJECT_NAME} PRIVATE Table)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})