if(NOT VTKCODE_PKG)

  # specify the path to the custom vtk extensions
  find_path(BASECODE_DIR baseCode.cmake
    PATHS
      ${VTKCODE_DIR}/baseCode/
      baseCode/
      ../baseCode/
      ../../baseCode/
  )

  # add the common package
  find_path(COMMON_PATH common.cmake
    PATHS
    ${BASECODE_DIR}/common/)

  if(COMMON_PATH)
    include(${COMMON_PATH}/common.cmake)
  elseif(NOT COMMON_PATH)
    message(FATAL_ERROR "Could not find the common package! (common.cmake)")
  endif(COMMON_PATH)

  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
  
# issues with VTK 6.0....
#   if(CMAKE_COMPILER_IS_GNUCXX)
#     add_definitions(-std=gnu++0x)
#   endif()
  
  set(VTKCODE_PKG true)

endif(NOT VTKCODE_PKG)
