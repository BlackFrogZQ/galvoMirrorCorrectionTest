add_subdirectory(setParaWindow)
add_subdirectory(messageBox)
add_subdirectory(controlWindow)
add_subdirectory(multipointCorrectWindow)
add_subdirectory(logTextBrowser)

aux_source_directory(. DIR_SYSTEM_SRCS)
add_library(uiLib ${DIR_SYSTEM_SRCS})

target_link_libraries(uiLib
    setParaWindowLib
    messageBoxLib
    controlLib
    multipointCorrectLib
    logTextBrowserLib)