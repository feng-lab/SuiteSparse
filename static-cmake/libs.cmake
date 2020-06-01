if (BUILD_WITH_CONDA)
  # tbb
  set(TBB_DIR $ENV{PREFIX}/lib/cmake/tbb)
endif ()

find_package(TBB REQUIRED tbb)
print_target_properties(TBB::tbb)

if (BUILD_WITH_CONDA)
  set(MKL_INCLUDE_DIRS ${MKL_INCLUDE_DIRS} $ENV{PREFIX}/include $ENV{PREFIX}/include/fftw)
  find_library(MKL_INTEL_LP64 NAMES mkl_intel_lp64
               PATHS $ENV{PREFIX}/lib NO_DEFAULT_PATH)
  find_library(MKL_TBB_THREAD NAMES mkl_tbb_thread
               PATHS $ENV{PREFIX}/lib NO_DEFAULT_PATH)
  find_library(MKL_CORE NAMES mkl_core
               PATHS $ENV{PREFIX}/lib NO_DEFAULT_PATH)
  set(MKL_LIBRARIES ${MKL_INTEL_LP64} ${MKL_TBB_THREAD} ${MKL_CORE})
else ()
  if (WIN32)
    set(INTEL_PATH "C:\\Program Files (x86)\\IntelSWTools\\compilers_and_libraries\\windows\\compiler")
    set(MKL_PATH "C:\\Program Files (x86)\\IntelSWTools\\compilers_and_libraries\\windows\\mkl")
  else (WIN32)
    set(INTEL_PATH /opt/intel)
    set(MKL_PATH ${INTEL_PATH}/mkl)
  endif (WIN32)
  set(MKL_INCLUDE_DIRS ${MKL_INCLUDE_DIRS} ${MKL_PATH}/include ${MKL_PATH}/include/fftw)
  if (WIN32)
    # todo: fix, mkl_tbb_thread links to static version of msvc runtime so we can not use it now
    set(MKL_LIBRARIES ${MKL_LIBRARIES}
        ${MKL_PATH}/lib/intel64/mkl_intel_lp64.lib
        ${MKL_PATH}/lib/intel64/mkl_sequential.lib
        ${MKL_PATH}/lib/intel64/mkl_core.lib)
  elseif (APPLE)
    set(MKL_LIBRARIES ${MKL_LIBRARIES}
        ${MKL_PATH}/lib/libmkl_intel_lp64.a
        ${MKL_PATH}/lib/libmkl_tbb_thread.a
        ${MKL_PATH}/lib/libmkl_core.a)
  else ()
    set(MKL_LIBRARIES ${MKL_LIBRARIES}
        ${MKL_PATH}/lib/intel64/libmkl_intel_lp64.a
        ${MKL_PATH}/lib/intel64/libmkl_tbb_thread.a
        ${MKL_PATH}/lib/intel64/libmkl_core.a)
  endif ()
endif ()
message(STATUS "MKL_INCLUDE_DIRS: ${MKL_INCLUDE_DIRS}")
message(STATUS "MKL_LIBRARIES: ${MKL_LIBRARIES}")
