#option(CPP_STARTER_USE_QT "Enable compilation of QT sample" OFF)

# qt
#if(CPP_STARTER_USE_QT)
#  message("Using Qt")
#  add_subdirectory(qt)
#endif()

# Generic test that uses conan libs
add_executable(journey main.cpp)
target_link_libraries(
  journey
  PRIVATE project_options
          project_warnings)
