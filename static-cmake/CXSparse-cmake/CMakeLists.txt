cmake_minimum_required(VERSION 3.14)
project(cxsparse)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../CXSparse)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME cxsparse)
# Find sources.
set(CS_SOURCE
    cs_add.c cs_amd.c cs_chol.c cs_cholsol.c cs_counts.c cs_cumsum.c
  cs_droptol.c cs_dropzeros.c cs_dupl.c cs_entry.c
  cs_etree.c cs_fkeep.c cs_gaxpy.c cs_happly.c cs_house.c cs_ipvec.c
  cs_lsolve.c cs_ltsolve.c cs_lu.c cs_lusol.c cs_util.c cs_multiply.c
  cs_permute.c cs_pinv.c cs_post.c cs_pvec.c cs_qr.c cs_qrsol.c
  cs_scatter.c cs_schol.c cs_sqr.c cs_symperm.c cs_tdfs.c cs_malloc.c
  cs_transpose.c cs_compress.c cs_usolve.c cs_utsolve.c cs_scc.c
  cs_maxtrans.c cs_dmperm.c cs_updown.c cs_print.c cs_norm.c cs_load.c
  cs_dfs.c cs_reach.c cs_spsolve.c cs_leaf.c cs_ereach.c cs_randperm.c
    )

set(CSC_SOURCE
    ${SRCDIR}/Source/cs_convert.c
    )

set(DI_SOURCES)
foreach(_file ${CS_SOURCE})
  string(REGEX REPLACE "^(.*).c$" "\\1_di.c" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file})
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out})
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND DI_SOURCES ${file_output})
endforeach()
set_source_files_properties(${DI_SOURCES} PROPERTIES GENERATED TRUE)

set(DL_SOURCES)
foreach(_file ${CS_SOURCE})
  string(REGEX REPLACE "^(.*).c$" "\\1_dl.c" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file})
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out})
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND DL_SOURCES ${file_output})
endforeach()
set_source_files_properties(${DL_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${DL_SOURCES} PROPERTIES COMPILE_FLAGS -DCS_LONG)

set(CI_SOURCES)
foreach(_file ${CS_SOURCE})
  string(REGEX REPLACE "^(.*).c$" "\\1_ci.c" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file})
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out})
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND CI_SOURCES ${file_output})
endforeach()
set_source_files_properties(${CI_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${CI_SOURCES} PROPERTIES COMPILE_FLAGS -DCS_COMPLEX)

set(CL_SOURCES)
foreach(_file ${CS_SOURCE})
  string(REGEX REPLACE "^(.*).c$" "\\1_cl.c" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file})
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out})
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND CL_SOURCES ${file_output})
endforeach()
set_source_files_properties(${CL_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${CL_SOURCES} PROPERTIES COMPILE_FLAGS "-DCS_LONG -DCS_COMPLEX")

add_library(${LIBRARY_NAME} STATIC 
  ${CSC_SOURCE} ${DI_SOURCES} ${DL_SOURCES} ${CI_SOURCES} ${CL_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${SRCDIR}/Include)

# compile options
if (WIN32)
  target_compile_definitions(${LIBRARY_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN UNICODE _UNICODE _WIN32_WINNT=0x0601 _USE_MATH_DEFINES _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

  target_compile_options(${LIBRARY_NAME} PUBLIC /TP) # treat all files as c++ file as msvc does not support the complex struct used in this lib
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
else (WIN32)
  target_compile_options(${LIBRARY_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-frtti>)
  target_compile_options(${LIBRARY_NAME} PUBLIC -fexceptions)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wextra)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Waddress -Wdeprecated)
endif (WIN32)

target_link_libraries(${LIBRARY_NAME} PUBLIC suitesparseconfig)

set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${SRCDIR}/Include/cs.h)
install(TARGETS ${LIBRARY_NAME}
  EXPORT  SuiteSparseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
