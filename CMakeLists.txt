#
#  CMake file for the thread-sync-app
#

cmake_minimum_required (VERSION 3.8)
project (thread-sync-app C)

set (PROJECT_NAME thread-sync-app)
set (SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INCDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories (${INCDIR})

set (SRC_FILES
        ${SRCDIR}/main.c
        )

add_executable (${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} pthread)


install (TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        PERMISSIONS OWNER_EXECUTE OWNER_READ)