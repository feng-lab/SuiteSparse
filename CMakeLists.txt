cmake_minimum_required(VERSION 3.14)
project(suitesparse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# set_target_properties(MyTarget PROPERTIES CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

if (UNIX AND NOT APPLE)
  # excludes symbols in all archive libraries from automatic export.
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--exclude-libs,ALL")
  # Prevent symbol relocations internal to our wrapper library to be
  # overwritten by the application.  And fail if there are missing
  # symbols.
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bsymbolic -Wl,-Bsymbolic-functions")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-Bsymbolic -Wl,-Bsymbolic-functions")

  # Fail if there are missing symbols, except when using Address Sanitizer
  # since libasan symbols are supposed to be preloaded.
  if (NOT ENABLE_ASAN)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,defs")
  endif ()
endif ()

if (UNIX)
  # Do not put non-global symbols in the output file's symbol table.
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-x")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-x")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-x")
endif ()

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/static-cmake)

message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

include(BuildType)
include(PrintCMakeTargetInfo)
include(libs)

if (NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif ()
message(STATUS "CMAKE_DEBUG_POSTFIX: " ${CMAKE_DEBUG_POSTFIX})
message(STATUS "CMAKE_STATIC_LIBRARY_PREFIX: " ${CMAKE_STATIC_LIBRARY_PREFIX})

include(GNUInstallDirs)

# subprojects
add_subdirectory(static-cmake/metis-cmake)
add_subdirectory(static-cmake/SuiteSparse_config-cmake)
# add_subdirectory(Mongoose)
add_subdirectory(static-cmake/AMD-cmake)
add_subdirectory(static-cmake/BTF-cmake)
add_subdirectory(static-cmake/CAMD-cmake)
add_subdirectory(static-cmake/CCOLAMD-cmake)
add_subdirectory(static-cmake/COLAMD-cmake)
add_subdirectory(static-cmake/CHOLMOD-cmake)
add_subdirectory(static-cmake/KLU-cmake)
add_subdirectory(static-cmake/LDL-cmake)
add_subdirectory(static-cmake/UMFPACK-cmake)
# add_subdirectory(static-cmake/CSparse-cmake)
add_subdirectory(static-cmake/CXSparse-cmake)
add_subdirectory(static-cmake/RBio-cmake)
add_subdirectory(static-cmake/SPQR-cmake)
set(USER_OPENMP OFF CACHE BOOL "No openmp as we are using tbb")
set(USER_POSIX ON CACHE BOOL "")
# set(BUILD_GRB_STATIC_LIBRARY ON CACHE BOOL "")
# add_subdirectory(GraphBLAS)
