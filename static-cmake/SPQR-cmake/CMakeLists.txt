cmake_minimum_required(VERSION 3.14)
project(spqr)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../SPQR)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME spqr)
# Find sources. GPU sources not included for now
set(SOURCES
    spqr_rmap
    SuiteSparseQR_C
    SuiteSparseQR_expert
    spqr_parallel
    spqr_kernel
    spqr_analyze
    spqr_assemble
    spqr_cpack
    spqr_csize
    spqr_fcsize
    spqr_debug
    spqr_front
    spqr_factorize
    spqr_freenum
    spqr_freesym
    spqr_freefac
    spqr_fsize
    spqr_maxcolnorm
    spqr_rconvert
    spqr_rcount
    spqr_rhpack
    spqr_rsolve
    spqr_stranspose1
    spqr_stranspose2
    spqr_hpinv
    spqr_1fixed
    spqr_1colamd
    SuiteSparseQR
    spqr_1factor
    spqr_cumsum
    spqr_shift
    spqr_happly
    spqr_panel
    spqr_happly_work
    SuiteSparseQR_qmult
    spqr_trapezoidal
    spqr_larftb
    spqr_append
    spqr_type
    spqr_tol
    )

set(O_SOURCES)
foreach(_file ${SOURCES})
  set(file_orig ${SRCDIR}/Source/${_file}.cpp)
  list(APPEND O_SOURCES ${file_orig})
endforeach()

add_library(${LIBRARY_NAME} STATIC ${O_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${SRCDIR}/Include)

# target_compile_definitions(${LIBRARY_NAME} PUBLIC -DHAVE_TBB)

# compile options
if (WIN32)
  target_compile_definitions(${LIBRARY_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN UNICODE _UNICODE WINVER=0x0601 _WIN32_WINNT=0x0601 _USE_MATH_DEFINES _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

  target_compile_options(${LIBRARY_NAME} PUBLIC /GR) # Enable Run-Time Type Information
  target_compile_options(${LIBRARY_NAME} PUBLIC /EHsc) # exception handling model, https://msdn.microsoft.com/en-us/library/1deeycx5.aspx
  # target_compile_options(${LIBRARY_NAME} PUBLIC /Wall)
  target_compile_options(${LIBRARY_NAME} PUBLIC /bigobj) # increases the number of sections that an object file can contain.
  target_compile_options(${LIBRARY_NAME} PUBLIC /utf-8)  # https://blogs.msdn.microsoft.com/vcblog/2016/02/22/new-options-for-managing-character-sets-in-the-microsoft-cc-compiler/
  target_compile_options(${LIBRARY_NAME} PUBLIC /wd5105) # macro expansion producing 'defined' has undefined behavior, from windows sdk
  if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${LIBRARY_NAME} PUBLIC /analyze) # The C/C++ Code Analysis tool provides information to developers about possible defects in their C/C++ source code
    target_compile_options(${LIBRARY_NAME} PUBLIC /MP) # Build with Multiple Processes
    target_compile_options(${LIBRARY_NAME} PUBLIC /GL) # Enables whole program optimization.
  else()
    target_compile_options(${LIBRARY_NAME} PUBLIC /MD)
  endif()
  target_compile_options(${LIBRARY_NAME} PUBLIC /Zc:inline) #
  target_compile_options(${LIBRARY_NAME} PUBLIC /permissive-)
  target_compile_options(${LIBRARY_NAME} PUBLIC /Zc:preprocessor)
  target_compile_options(${LIBRARY_NAME} PUBLIC /arch:AVX)
else (WIN32)
  target_compile_options(${LIBRARY_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-frtti>)
  target_compile_options(${LIBRARY_NAME} PUBLIC -fexceptions)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wextra)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Waddress -Wdeprecated)
  target_compile_options(${LIBRARY_NAME} PUBLIC -mavx)
endif (WIN32)

target_link_libraries(${LIBRARY_NAME} PUBLIC suitesparseconfig amd colamd cholmod)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(${LIBRARY_NAME} PUBLIC -Wl,--start-group ${MKL_LIBRARIES} -Wl,--end-group)
else ()
  target_link_libraries(${LIBRARY_NAME} PUBLIC ${MKL_LIBRARIES})
endif ()
# target_link_libraries(${LIBRARY_NAME} PUBLIC TBB::tbb)

file(GLOB PUBLIC_HEADERS ${SRCDIR}/Include/*.*)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")
install(TARGETS ${LIBRARY_NAME}
  EXPORT  SuiteSparseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
