add_library(metamodule-rack-interface STATIC ${CMAKE_CURRENT_LIST_DIR}/libc_stub.c)

target_compile_options(metamodule-rack-interface PUBLIC
	-shared
	-fPIC
	-nostartfiles
	-nostdlib
)

target_include_directories(metamodule-rack-interface PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/dep/include
    ${CMAKE_CURRENT_LIST_DIR}/dep/include/cpputil
)

set_property(TARGET metamodule-rack-interface PROPERTY CXX_STANDARD 20)
