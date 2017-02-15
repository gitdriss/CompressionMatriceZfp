cmake_minimum_required(VERSION 2.4)

project(exe)

# Under Windows, un-comment the following line and set the `VTK_DIR' variable 
# to the path where the file `VTKConfig.cmake' is located (in your installed 
# VTK source tree).

#set(VTK_DIR "C:\\Program Files\\VTK\\lib\\vtk-6.0")

# specify the path to the custom vtk extensions
find_path(VTKCODE_DIR vtk.cmake
  PATHS
    vtkBase/
    ../vtkBase/
    ../../vtkBase/
)
include(${VTKCODE_DIR}/vtk.cmake)

# add the different filters required by the application

include_directories(".")

add_executable(exe
  ${PROJECT_SRC}
  matrix.cc)

set_target_properties(exe
  PROPERTIES 
  COMPILE_FLAGS
  "${PROJECT_FLAGS}"
)
  
target_link_libraries(exe
  ${VTK_LIBRARIES})

install(TARGETS exe RUNTIME DESTINATION bin)
