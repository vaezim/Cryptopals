
# Iterate over each Set's directory
file(GLOB SET_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/Set*")
foreach(SET_DIR ${SET_DIRS})

    # Current set name (e.g. Set1, Set2, ...)
    get_filename_component(CURRENT_SET "${SET_DIR}" NAME)

    # Get a list of all *.cpp challenge files
    file(GLOB CPP_FILES "${SET_DIR}/*.cpp")

    # Strip the file extension
    set(CHALLENGES)
    foreach(FILE ${CPP_FILES})
        get_filename_component(STRIPPED_FILE ${FILE} NAME_WE)
        list(APPEND CHALLENGES ${STRIPPED_FILE})
    endforeach()

    # Add executable for each challenge file
    # Output directory: ${root_dir}/output/exe/Set*/challenge*
    foreach(CHALLENGE ${CHALLENGES})
        add_executable(${CHALLENGE} "${SET_DIR}/${CHALLENGE}.cpp")
        set_target_properties(${CHALLENGE} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CURRENT_SET}
        )
        # Link each challenge executable with Crypto lib
        target_link_libraries(
            ${CHALLENGE}
            ${CRYPTO_LIB}
        )
    endforeach()

    # Copy text/ directory to executables path
    if(EXISTS "${SET_DIR}/text/")
        file(COPY "${SET_DIR}/text/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CURRENT_SET}/text")
    endif()

endforeach()