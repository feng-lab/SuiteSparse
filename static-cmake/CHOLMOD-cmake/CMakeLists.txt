cmake_minimum_required(VERSION 3.14)
project(cholmod)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../CHOLMOD)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME cholmod)
# Find sources. GPU sources not included for now
set(CORE_SOURCES
    cholmod_aat.c cholmod_add.c cholmod_band.c
  cholmod_change_factor.c cholmod_common.c cholmod_complex.c
  cholmod_copy.c cholmod_dense.c cholmod_error.c cholmod_factor.c
  cholmod_memory.c cholmod_sparse.c
  cholmod_transpose.c cholmod_triplet.c
        cholmod_version.c
    # t_cholmod_change_factor.c t_cholmod_dense.c t_cholmod_transpose.c t_cholmod_triplet.c
    )

set(CHECK_SOURCES
    cholmod_check.c cholmod_read.c cholmod_write.c
    )

set(CHOLESKY_SOURCES
    cholmod_amd.c cholmod_analyze.c cholmod_colamd.c
  cholmod_etree.c cholmod_factorize.c cholmod_postorder.c
  cholmod_rcond.c cholmod_resymbol.c cholmod_rowcolcounts.c
  cholmod_rowfac.c cholmod_solve.c cholmod_spsolve.c
    # t_cholmod_lsolve.c t_cholmod_ltsolve.c t_cholmod_rowfac.c t_cholmod_solve.c
    )

set(MATRIXOPS_SOURCES
    cholmod_drop.c cholmod_horzcat.c cholmod_norm.c
  cholmod_scale.c cholmod_sdmult.c cholmod_ssmult.c
  cholmod_submatrix.c cholmod_vertcat.c cholmod_symmetry.c
    # t_cholmod_sdmult.c
    )

set(PARTITION_SOURCES
    cholmod_ccolamd.c cholmod_csymamd.c
  cholmod_metis.c cholmod_nesdis.c cholmod_camd.c
    )

set(MODIFY_SOURCES
    cholmod_rowadd.c cholmod_rowdel.c cholmod_updown.c
    # t_cholmod_updown_numkr.c t_cholmod_updown.c
    )

set(SUPERNODAL_SOURCES
    cholmod_super_numeric.c cholmod_super_solve.c
  cholmod_super_symbolic.c
    # t_cholmod_super_numeric.c t_cholmod_super_solve.c
    )

set(SOURCES)
foreach(_file ${CORE_SOURCES})
  list(APPEND SOURCES Core/${_file})
endforeach()
foreach(_file ${CHECK_SOURCES})
  list(APPEND SOURCES Check/${_file})
endforeach()
foreach(_file ${CHOLESKY_SOURCES})
  list(APPEND SOURCESCholesky/${_file})
endforeach()
foreach(_file ${MATRIXOPS_SOURCES})
  list(APPEND SOURCES MatrixOps/${_file})
endforeach()
foreach(_file ${PARTITION_SOURCES})
  list(APPEND SOURCES Partition/${_file})
endforeach()
foreach(_file ${MODIFY_SOURCES})
  list(APPEND SOURCES Modify/${_file})
endforeach()
foreach(_file ${SUPERNODAL_SOURCES})
  list(APPEND SOURCES Supernodal/${_file})
endforeach()

set(O_SOURCES)
set(L_SOURCES)
foreach(_file ${SOURCES})
  string(REPLACE "cholmod_" "cholmod_l_" file_out ${_file})
  set(file_orig ${SRCDIR}/${_file})
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out})
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND L_SOURCES ${file_output})
  list(APPEND O_SOURCES ${file_orig})
endforeach()
set_source_files_properties(${L_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${L_SOURCES} PROPERTIES COMPILE_FLAGS -DDLONG)

add_library(${LIBRARY_NAME} STATIC ${O_SOURCES} ${L_SOURCES})

target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/Core)
target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/Cholesky)
target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/MatrixOps)
target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/Modify)
target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/Supernodal)
target_include_directories(${LIBRARY_NAME} PUBLIC ${SRCDIR}/Include)

# compile options
if (WIN32)
  target_compile_definitions(${LIBRARY_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN UNICODE _UNICODE _WIN32_WINNT=0x0601 _USE_MATH_DEFINES _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

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

target_link_libraries(${LIBRARY_NAME} PUBLIC suitesparseconfig amd camd colamd ccolamd metis)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(${LIBRARY_NAME} PUBLIC -Wl,--start-group ${MKL_LIBRARIES} -Wl,--end-group)
else ()
  target_link_libraries(${LIBRARY_NAME} PUBLIC ${MKL_LIBRARIES})
endif ()

file(GLOB PUBLIC_HEADERS ${SRCDIR}/Include/*.h)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")
install(TARGETS ${LIBRARY_NAME}
  EXPORT  SuiteSparseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
