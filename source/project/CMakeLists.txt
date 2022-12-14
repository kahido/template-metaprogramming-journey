# Generic test that uses conan libs
add_executable(${PROJECT_NAME} project.cpp)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE project_options
          project_warnings)
