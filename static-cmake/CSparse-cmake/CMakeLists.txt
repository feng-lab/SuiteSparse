cmake_minimum_required(VERSION 3.14)
project(csparse)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../CSparse)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME csparse)
# Find sources.
set(SOURCES
    cs_add cs_amd cs_chol cs_cholsol cs_counts cs_cumsum
  cs_droptol cs_dropzeros cs_dupl cs_entry
  cs_etree cs_fkeep cs_gaxpy cs_happly cs_house cs_ipvec
  cs_lsolve cs_ltsolve cs_lu cs_lusol cs_util cs_multiply
  cs_permute cs_pinv cs_post cs_pvec cs_qr cs_qrsol
  cs_scatter cs_schol cs_sqr cs_symperm cs_tdfs cs_malloc
  cs_transpose cs_compress cs_usolve cs_utsolve cs_scc
  cs_maxtrans cs_dmperm cs_updown cs_print cs_norm cs_load
  cs_dfs cs_reach cs_spsolve cs_ereach cs_leaf cs_randperm
    )

set(O_SOURCES)
foreach(_file ${SOURCES})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  list(APPEND O_SOURCES ${file_orig})
endforeach()

add_library(${LIBRARY_NAME} STATIC ${O_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${SRCDIR}/Include)

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

# file(GLOB PUBLIC_HEADERS ${SRCDIR}/Include/*.h)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${SRCDIR}/Include/cs.h)
install(TARGETS ${LIBRARY_NAME}
  EXPORT  SuiteSparseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
