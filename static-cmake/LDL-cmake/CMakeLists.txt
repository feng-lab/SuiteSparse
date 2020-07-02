cmake_minimum_required(VERSION 3.14)
project(ldl)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../LDL)

# main stuff

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

# our target
set(LIBRARY_NAME ldl)
# Find sources.
set(SOURCES
    ldl.c
    )

set(O_SOURCES)
set(L_SOURCES)
foreach(_file ${SOURCES})
  string(REPLACE "ldl" "ldll" file_out ${_file})
  set(file_orig ${SRCDIR}/Source/${_file})
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
set_source_files_properties(${L_SOURCES} PROPERTIES COMPILE_FLAGS -DLDL_LONG)

add_library(${LIBRARY_NAME} STATIC ${O_SOURCES} ${L_SOURCES})

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
else (WIN32)
  target_compile_options(${LIBRARY_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-frtti>)
  target_compile_options(${LIBRARY_NAME} PUBLIC -fexceptions)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Wall -Wextra)
  target_compile_options(${LIBRARY_NAME} PUBLIC -Waddress -Wdeprecated)
endif (WIN32)

target_link_libraries(${LIBRARY_NAME} PUBLIC suitesparseconfig)

# file(GLOB PUBLIC_HEADERS ${SRCDIR}/Include/*.h)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${SRCDIR}/Include/ldl.h)
install(TARGETS ${LIBRARY_NAME}
  EXPORT  SuiteSparseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
