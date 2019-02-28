
macro(enable_automatic_reference_counting TARGET SCOPE)
    if (BDN_USES_FK)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Apple")
            target_compile_options(${TARGET} ${SCOPE} "-fobjc-arc")
        endif()
    endif()
endmacro()

macro(enable_warnings_as_errors TARGET SCOPE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(${TARGET} ${SCOPE} "-Werror")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${TARGET} ${SCOPE} "-Werror")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} ${SCOPE} "/WX")
    else()
        message(WARNING "I Don't know how to enable warnings as errors on this platform! (${CMAKE_CXX_COMPILER_ID})")
    endif()
endmacro()

macro(enable_big_object_files TARGET SCOPE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${TARGET} ${SCOPE} "/bigobj")
    endif()
endmacro()

macro(enable_unicode TARGET SCOPE)
    target_compile_definitions(${TARGET} ${SCOPE} "UNICODE" "_UNICODE")
endmacro()

macro(enable_multicore_build TARGET SCOPE)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${TARGET} ${SCOPE} "/MP")
	endif()
endmacro()

macro(enable_ffast_math TARGET SCOPE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(${TARGET} ${SCOPE} "-ffast-math")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} ${SCOPE} "/fp:fast")
    else()
        message(WARNING "I Don't know how to enable fast math on this platform! (${CMAKE_CXX_COMPILER_ID})")
    endif()
endmacro()

macro(cmake_variable_to_define TARGET SCOPE CMAKE_VARIABLE)
    set(truelist "Yes" "On" "True")

    if(${CMAKE_VARIABLE})
        if(${CMAKE_VARIABLE} IN_LIST truelist)
            target_compile_definitions(${TARGET} ${SCOPE} "${CMAKE_VARIABLE}")
        else()
            target_compile_definitions(${TARGET} ${SCOPE} "${CMAKE_VARIABLE}=${${CMAKE_VARIABLE}}")
        endif()
    endif()

endmacro()
