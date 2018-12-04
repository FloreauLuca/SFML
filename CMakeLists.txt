cmake_minimum_required(VERSION 3.3)
project(SAE918)

include(cmake/IntelCompileFeatures.cmake)

include(cmake/EnumeratedOption.cmake)
include(cmake/CheckCXXFeature.cmake)
include(cmake/CheckCXXStandardLibrary.cmake)

message(STATUS "CXX compiler ID: '${CMAKE_CXX_COMPILER_ID}'")
message(STATUS "CXX compiler Version: '${CMAKE_CXX_COMPILER_VERSION}'")

enum_option(BUILD_CXX_STANDARD
  DOC "C++ Standard to compile against"
  VALUES 11 14 17
  CASE_INSENSITIVE
  )
message(STATUS "List of CXX features known to CMake")
	get_property(_cxx_known_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
	message(STATUS "List of supported CXX11 features")
	foreach(_f ${CMAKE_CXX11_COMPILE_FEATURES})
	  message("  ${_f}")
	endforeach()
	message(STATUS "List of supported CXX14 features")
	foreach(_f ${CMAKE_CXX14_COMPILE_FEATURES})
	  message("  ${_f}")
	endforeach()
	message(STATUS "List of supported CXX17 features")
	foreach(_f ${CMAKE_CXX17_COMPILE_FEATURES})
		message("  ${_f}")
endforeach()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

include_directories(include ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SAE918_SRC src/*.cpp include/*.h)

set_property(GLOBAL PROPERTY USE_FOLDERS On)
SET_SOURCE_FILES_PROPERTIES( ${SAE918_SRC} PROPERTIES
                FOLDER "${CMAKE_SOURCE_DIR}/src" )
#SFML
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
#set(SFML_BUILD_EXAMPLES FALSE)
SET(BUILD_SHARED_LIBS FALSE CACHE INTERNAL "")
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include ${SFML_DIR}/src)
LIST(APPEND SAE918_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network)



#BOX2D
set(BOX2D_DIR ${EXTERNAL_DIR}/Box2D)

SET(BOX2D_INSTALL ON CACHE INTERNAL "")
SET(BOX2D_BUILD_STATIC ON  CACHE INTERNAL "")

add_subdirectory(${BOX2D_DIR})
include_directories(${BOX2D_DIR}/Box2D/)
LIST(APPEND SAE918_LIBRARIES
	Box2D)


if(APPLE)
	set(boost_min_ver 1.50.0)
	set(boost_libs system filesystem)
	find_package(Boost ${boost_min_ver})

	if(Boost_FOUND)
		find_package(Boost ${boost_min_ver} COMPONENTS ${boost_libs})
	endif()
	include_directories(${Boost_INCLUDE_DIRS})
	LIST(APPEND SAE918_LIBRARIES
	  ${Boost_LIBRARIES})
endif(APPLE)

#MISCELLANEOUS UTILITIES
set(UTILITIES_DIR ${EXTERNAL_DIR}/utilities/)
include_directories(${UTILITIES_DIR})


#SAE918_COMMON
if(NOT APPLE AND UNIX)
	LIST(APPEND SAE918_LIBRARIES
		stdc++fs)
ENDIF()
add_library(SAE918_COMMON STATIC ${SAE918_SRC})
include_directories(include/)
target_link_libraries(SAE918_COMMON PUBLIC ${SAE918_LIBRARIES})
set_property(TARGET SAE918_COMMON PROPERTY CXX_STANDARD 17)
if(APPLE)
set_target_properties(SAE918_COMMON PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
ENDIF(APPLE)

#SAE918_main
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}" )
elseif()
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -masm=intel" )
endif()
SET(SAE918_MAIN_DIR ${CMAKE_SOURCE_DIR}/main/)
file(GLOB MAIN_FILES ${SAE918_MAIN_DIR}/*.cpp )
foreach(main_file ${MAIN_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH main_relative_path ${SAE918_MAIN_DIR} ${main_file})
    string( REPLACE ".cpp" "" main_name ${main_relative_path} )
    
	set(FILE ${main_name})
	if (EXISTS include/${main_name})
	else ()
	file (MAKE_DIRECTORY include/${main_name})
	endif()
	file(GLOB HEADERCONTENT include/${main_name}/*.h)
	
	if (EXISTS src/${main_name})
	else ()
	file (MAKE_DIRECTORY src/${main_name})
	endif()
	file(GLOB SOURCECONTENT src/${main_name}/*.cpp)
	
	if (EXISTS data/${main_name})
	else ()
	file (MAKE_DIRECTORY data/${main_name})
	endif()
	file(GLOB DATACONTENT data/${main_name}/*)
	
	add_executable(${main_name} ${SAE918_MAIN_DIR}/${main_relative_path} ${SAE918_COMMON} ${HEADERCONTENT} ${SOURCECONTENT} ${DATACONTENT})
    # Make sure YourLib is linked to each app
    target_link_libraries(${main_name} PUBLIC SAE918_COMMON)
	set_property(TARGET ${main_name} PROPERTY CXX_STANDARD 17)
	IF(UNIX)
		set_target_properties(${main_name} PROPERTIES COMPILE_FLAGS "-save-temps")
	ENDIF(UNIX)
  IF(APPLE)
    set_target_properties(${main_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
  ENDIF(APPLE)
endforeach()


#SAE918
file(COPY data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)

