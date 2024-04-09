add_library(metamodule-rack-interface INTERFACE)

target_compile_options(metamodule-rack-interface INTERFACE
	-shared
	-fPIC
	-nostartfiles
	-nostdlib
)

target_include_directories(metamodule-rack-interface INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/dep/include
)

set_property(TARGET metamodule-rack-interface PROPERTY CXX_STANDARD 20)
