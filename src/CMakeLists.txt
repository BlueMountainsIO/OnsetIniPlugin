set(PLUGIN_CONFIG_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/config_headers")

configure_file(
	"version.hpp.in"
	"${PLUGIN_CONFIG_INCLUDE_DIR}/version.hpp"
	@ONLY
)

add_library(ini-plugin MODULE
	HandleManager.cpp
	HandleManager.hpp
	Plugin.cpp
	Plugin.hpp
	PluginInterface.cpp
	Singleton.hpp
	ini.hpp
)

target_include_directories(ini-plugin PRIVATE 
	${PLUGIN_CONFIG_INCLUDE_DIR}
	${HORIZONSDK_INCLUDE_DIR}
)

set_property(TARGET ini-plugin PROPERTY PREFIX "")

set_property(TARGET ini-plugin PROPERTY CXX_STANDARD 11)
set_property(TARGET ini-plugin PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	target_compile_definitions(ini-plugin PRIVATE
		_CRT_SECURE_NO_WARNINGS
		NOMINMAX
	)
endif()

# increase warning levels
if (MSVC)
	target_compile_options(ini-plugin PRIVATE
		/W4
		/WX
		/permissive-
		/wd4505
	)
elseif(UNIX)
	target_compile_options(ini-plugin PRIVATE
		-Wall
		-Wextra
		-pedantic
		-Werror
		-Wno-unused-function
	)
endif()

target_link_libraries(ini-plugin ${HORIZONSDK_LIBRARY} ini-lib)

if(UNIX)
	if(NOT APPLE)
		target_link_libraries(ini-plugin rt)
	endif()
	
	set_target_properties(ini-plugin PROPERTIES
		INSTALL_RPATH "$ORIGIN/..:$ORIGIN/")
endif()

install(TARGETS ini-plugin DESTINATION "plugins/")

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
if(WIN32)
	set(CPACK_GENERATOR ZIP)
else()
	set(CPACK_GENERATOR TGZ)
endif()

include(CPack)
