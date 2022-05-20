cmake_minimum_required (VERSION 3.14)

project (IncredibleMachine)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()


if(APPLE)

	add_executable (IncredibleMachine MACOSX_BUNDLE "")

	add_subdirectory (Box2D/include)
	add_subdirectory (Box2D/src)
	add_subdirectory (include)
	add_subdirectory (src)
	add_subdirectory (resources)


	set (SFML_STATIC_LIBRARIES FALSE)
	set (SFML_DIR "/usr/local/Cellar/sfml/2.5.1")

	find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)

	set_target_properties ( PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

	target_link_libraries (IncredibleMachine sfml-graphics sfml-audio)
	target_link_libraries (IncredibleMachine box2d)

 endif()



 if(WIN32)

	add_executable (IncredibleMachine  "")

	add_subdirectory (Box2D/include)
	add_subdirectory (Box2D/src)
	add_subdirectory (include)
	add_subdirectory (src)
	add_subdirectory (resources)

	set (SFML_STATIC_LIBRARIES TRUE)
	set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

	find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)

	set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

	target_link_libraries (IncredibleMachine sfml-audio sfml-graphics sfml-main)
	target_link_libraries (IncredibleMachine box2d)

 endif()

 #ifdef __APPLE__