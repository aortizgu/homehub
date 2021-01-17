# Locate libcURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

include_directories(${homehub_SOURCE_DIR}/spdlog)
include_directories(${homehub_SOURCE_DIR}/drogon)

file(GLOB SCP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/views/*.csp)
foreach(cspFile ${SCP_LIST})
    message(STATUS "cspFile:" ${cspFile})
    get_filename_component(classname ${cspFile} NAME_WE)
    message(STATUS "view classname:" ${classname})
    add_custom_command(OUTPUT ${classname}.h ${classname}.cc
                    COMMAND drogon_ctl
                            ARGS
                            create
                            view
                            ${cspFile}
                    DEPENDS ${cspFile}
                    VERBATIM)
    set(VIEWSRC ${VIEWSRC} ${classname}.cc)
endforeach()

execute_process(COMMAND "drogon_ctl" 
                        "create" 
                        "model" 
                        "-f" 
                        "." 
                WORKING_DIRECTORY ${homehub_SOURCE_DIR}/src/model/
                RESULT_VARIABLE rv)

file(GLOB SOURCES "*.cc" "filters/*.cc" "mail/*.cc" "model/*.cc")
add_executable(homehub ${SOURCES} ${VIEWSRC})
target_link_libraries(homehub spdlog drogon curl)