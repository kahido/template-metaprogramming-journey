set(source_files 00_basic_function_templates.cpp)

# Loop through each source file
foreach(source_file IN LISTS source_files)
  # Get the name of the file without the extension
  get_filename_component(target_name ${source_file} NAME_WE)

  # Create an executable with the above name, building the above source
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE project_options project_warnings)
endforeach()
