cmake_minimum_required(VERSION 3.16)

project(MiscTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MiscTool
    src/Apps/MiscExporterApp.hpp
    src/Apps/MiscImporterApp.hpp
    src/Apps/MiscToolApp.hpp

    src/MiscCompilator/MiscCompilator.hpp

    src/MiscCompilator/MiscCompilatorStrings.hpp



    src/MiscFile/KsTerrainDat.cpp
    src/MiscFile/KsTerrainDat.hpp


    src/main.cpp
    src/MiscGlobals.hpp
    src/MiscFile/IMisc.hpp
    src/MiscFile/MiscFile.hpp
    src/MiscFile/MiscFactory.hpp)

target_include_directories(MiscTool PRIVATE
    ../KsUtils
    ../KsUtils/src
)

target_link_libraries(MiscTool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../KsUtils/build/Desktop_Qt_6_9_3_MinGW_64_bit-Release/libKsUtils.a
)

include(GNUInstallDirs)
install(TARGETS MiscTool
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
