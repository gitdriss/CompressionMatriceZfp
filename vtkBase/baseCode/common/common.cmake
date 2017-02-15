if(NOT COMMON_PKG)

  option(withKamikaze "Enable Kamikaze compilation mode" false)

  if(withKamikaze)

    set(PROJECT_FLAGS "${PROJECT_FLAGS} -D withKamikaze")

  endif(withKamikaze)

  include_directories("${BASECODE_DIR}/common/")

  if(MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#    set_target_properties(${PROJECT}
#      PROPERTIES
#      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})
#    set_target_properties(${PROJECT}
#      PROPERTIES
#      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
    set(PROJECT_FLAGS ${PROJECT_FLAGS} "/MP")
  else(MSVC)
    set(PROJECT_FLAGS
      "${PROJECT_FLAGS} -Wall -march=native")
    if(CMAKE_BUILD_TYPE MATCHES Release)
      set (PROJECT_FLAGS
        "${PROJECT_FLAGS} -O3")
    endif(CMAKE_BUILD_TYPE MATCHES Release)
  endif()


  option(withOpenMP "Enable OpenMP support" false)

  if(withOpenMP)
    find_package(OpenMP)
    if(OPENMP_FOUND)
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
      set(PROJECT_FLAGS "${PROJECT_FLAGS} -DwithOpenMP")
    endif(OPENMP_FOUND)
  endif(withOpenMP)

  message(STATUS
"common ----------------------------------------------------------------------")
  message(STATUS "Kamikaze compilation mode: ${withKamikaze} (-DwithKamikaze=)")
  message(STATUS "OpenMP: ${withOpenMP} (-DwithOpenMP=)")
  message(STATUS
"-----------------------------------------------------------------------------")

  # avoid some issues under windows
  if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
  endif(COMMAND cmake_policy)
  if(COMMAND cmake_policy)
    cmake_policy(SET CMP0011 NEW)
  endif(COMMAND cmake_policy)

  set(COMMON_PKG true)
endif(NOT COMMON_PKG)
