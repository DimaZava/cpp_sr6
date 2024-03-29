cmake_minimum_required(VERSION 3.5)

project(sr_6)

add_executable(main main.cpp)
add_library(custom_allocator_lib custom_allocator.h custom_allocator.cpp)

set_target_properties(main custom_allocator_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )


target_link_libraries(main
    PRIVATE
    custom_allocator_lib
    )

if (MSVC)
    target_compile_options(main PRIVATE
        /W4
    )
    target_compile_options(custom_allocator_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(main PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(custom_allocator_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if(APPLE)
    set(CPACK_GENERATOR "7Z")
else()
    set(CPACK_GENERATOR DEB)
endif()

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimazava@hotmail.com)

include(CPack)

# enable_testing()
# add_test(unit_tests unit_tests)