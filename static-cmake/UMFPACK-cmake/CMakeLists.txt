cmake_minimum_required(VERSION 3.14)
project(umfpack)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../UMFPACK)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME umfpack)
# Find sources.
set(UMFCH
    umf_assemble umf_blas3_update umf_build_tuples umf_create_element
  umf_dump umf_extend_front umf_garbage_collection umf_get_memory
  umf_init_front umf_kernel umf_kernel_init umf_kernel_wrapup
  umf_local_search umf_lsolve umf_ltsolve umf_mem_alloc_element
  umf_mem_alloc_head_block umf_mem_alloc_tail_block
  umf_mem_free_tail_block umf_mem_init_memoryspace
  umf_report_vector umf_row_search umf_scale_column
  umf_set_stats umf_solve umf_symbolic_usage umf_transpose
  umf_tuple_lengths umf_usolve umf_utsolve umf_valid_numeric
  umf_valid_symbolic umf_grow_front umf_start_front
  umf_store_lu umf_scale
    )

set(UMFINT
    umf_analyze umf_apply_order umf_colamd umf_free umf_fsize
  umf_is_permutation umf_malloc umf_realloc umf_report_perm
  umf_singletons umf_cholmod
    )

set(UMF_CREATED
    umf_lhsolve umf_uhsolve umf_triplet_map_nox
  umf_triplet_nomap_x umf_triplet_nomap_nox umf_triplet_map_x
  umf_assemble_fixq umf_store_lu_drop
    )

set(UMFPACK
    umfpack_col_to_triplet umfpack_defaults umfpack_free_numeric
  umfpack_free_symbolic umfpack_get_numeric umfpack_get_lunz
  umfpack_get_symbolic umfpack_get_determinant umfpack_numeric
  umfpack_qsymbolic umfpack_report_control umfpack_report_info
  umfpack_report_matrix umfpack_report_numeric umfpack_report_perm
  umfpack_report_status umfpack_report_symbolic umfpack_report_triplet
  umfpack_report_vector umfpack_solve umfpack_symbolic
  umfpack_transpose umfpack_triplet_to_col umfpack_scale
  umfpack_load_numeric umfpack_save_numeric
  umfpack_load_symbolic umfpack_save_symbolic
    )

set(UMFPACKW
    umfpack_wsolve
    )

set(GENERIC
    umfpack_timer umfpack_tictoc
    )

set(I_SOURCES)
foreach(_file ${UMFINT})
  string(REPLACE "umf_" "umf_i_" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND I_SOURCES ${file_output})
endforeach()
set_source_files_properties(${I_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${I_SOURCES} PROPERTIES COMPILE_FLAGS -DDINT)

set(L_SOURCES)
foreach(_file ${UMFINT})
  string(REPLACE "umf_" "umf_l_" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND L_SOURCES ${file_output})
endforeach()
set_source_files_properties(${L_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${L_SOURCES} PROPERTIES COMPILE_FLAGS -DDLONG)

set(DI_SOURCES)
foreach(_file IN LISTS UMFCH UMFPACK)
  string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_di_\\2" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND DI_SOURCES ${file_output})
endforeach()
set_source_files_properties(${DI_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${DI_SOURCES} PROPERTIES COMPILE_FLAGS -DDINT)

set(DL_SOURCES)
foreach(_file IN LISTS UMFCH UMFPACK)
  string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_dl_\\2" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND DL_SOURCES ${file_output})
endforeach()
set_source_files_properties(${DL_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${DL_SOURCES} PROPERTIES COMPILE_FLAGS -DDLONG)

set(ZI_SOURCES)
foreach(_file IN LISTS UMFCH UMFPACK)
  string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_zi_\\2" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND ZI_SOURCES ${file_output})
endforeach()
set_source_files_properties(${ZI_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${ZI_SOURCES} PROPERTIES COMPILE_FLAGS -DZINT)

set(ZL_SOURCES)
foreach(_file IN LISTS UMFCH UMFPACK)
  string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_zl_\\2" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND ZL_SOURCES ${file_output})
endforeach()
set_source_files_properties(${ZL_SOURCES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${ZL_SOURCES} PROPERTIES COMPILE_FLAGS -DZLONG)
# message(STATUS "ZL_SOURCES: " ${ZL_SOURCES})

set(GN_SOURCES)
foreach(_file ${GENERIC})
  string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_gn_\\2" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file}.c)
  set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
  add_custom_command(
    OUTPUT ${file_output}
    COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
    DEPENDS ${file_orig}
  ) 
  list(APPEND GN_SOURCES ${file_output})
endforeach()
set_source_files_properties(${GN_SOURCES} PROPERTIES GENERATED TRUE)

set(CREATED_SOURCES)
set(SG_PREFIX di dl zi zl)
set(SG_PREFIX_COMPILE_FLAG -DDINT -DDLONG -DZINT -DZLONG)
set(SG_SOURCES umf_ltsolve umf_utsolve umf_triplet umf_triplet umf_triplet umf_triplet
  umf_assemble umf_store_lu umfpack_solve)
set(SG_TARGETS umf_lhsolve umf_uhsolve umf_triplet_map_x umf_triplet_map_nox
  umf_triplet_nomap_x umf_triplet_nomap_nox umf_assemble_fixq umf_store_lu_drop 
  umfpack_wsolve)
set(SG_TARGETS_COMPILE_FLAG -DCONJUGATE_SOLVE -DCONJUGATE_SOLVE "-DDO_MAP -DDO_VALUES"
  -DDO_MAP -DDO_VALUES "" -DFIXQ -DDROP -DWSOLVE)
foreach(sgp sgpcf IN ZIP_LISTS SG_PREFIX SG_PREFIX_COMPILE_FLAG)
  foreach(sgs sgt sgtcf IN ZIP_LISTS SG_SOURCES SG_TARGETS SG_TARGETS_COMPILE_FLAG)
    string(REGEX REPLACE "^([umfpack]+)_(.*)" "\\1_${sgp}_\\2" file_out ${sgt})
    set(file_orig ${SRCDIR}/Source/${sgs}.c)
    set(file_output ${CMAKE_CURRENT_BINARY_DIR}/${file_out}.c)
    add_custom_command(
      OUTPUT ${file_output}
      COMMAND ${CMAKE_COMMAND} -E copy ${file_orig} ${file_output}
      DEPENDS ${file_orig}
    )
    list(APPEND CREATED_SOURCES ${file_output})
    set_source_files_properties(${file_output} PROPERTIES GENERATED TRUE)
    set_source_files_properties(${file_output} PROPERTIES COMPILE_FLAGS "${sgpcf} ${sgtcf}")
  endforeach()
endforeach()

add_library(${LIBRARY_NAME} STATIC 
  ${I_SOURCES} ${L_SOURCES} ${ZI_SOURCES} ${ZL_SOURCES}
  ${DI_SOURCES} ${DL_SOURCES} ${GN_SOURCES} ${CREATED_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${SRCDIR}/Include)
target_include_directories(${LIBRARY_NAME} PRIVATE ${SRCDIR}/Source)

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

target_link_libraries(${LIBRARY_NAME} PUBLIC suitesparseconfig cholmod amd)
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
