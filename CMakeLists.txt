cmake_minimum_required(VERSION 3.5)

project(AstroDb VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(Qt6_DIR "C:/Qt6.7.1/lib/cmake/Qt6")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt6.7.1")
    set(Qt6Widgets_DIR "C:/Qt6.7.1/lib/cmake/Qt6Widgets")
elseif(UNIX)
    set(Qt6_DIR /opt/Qt6.7.1/lib/cmake/Qt6)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /opt/Qt6.7.1)
    set(Qt6Widgets_DIR /opt/Qt6.7.1/lib/cmake/Qt6Widgets)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/about.cpp
        src/analysis.cpp
        src/calculations.cpp
        src/canvas.cpp
        src/combobox.cpp
        src/comparison.cpp
        src/consts.cpp
        src/frame.cpp
        src/main.cpp
        src/msgbox.cpp
        src/optional.cpp
        src/progress.cpp
        src/select.cpp
        src/spinbox.cpp
        src/spreadsheet.cpp
        src/toplevel.cpp
        src/utils.cpp
        src/widget.cpp
        src/worker_analysis.cpp
        src/worker_calculations.cpp
        src/worker_file_loader.cpp
        src/zodiac.cpp
        include/about.hpp
        include/analysis.hpp
        include/calculations.hpp
        include/canvas.hpp
        include/combobox.hpp
        include/comparison.hpp
        include/consts.hpp
        include/frame.hpp
        include/libs.hpp
        include/msgbox.hpp
        include/optional.hpp
        include/progress.hpp
        include/select.hpp
        include/spinbox.hpp
        include/spreadsheet.hpp
        include/toplevel.hpp
        include/utils.hpp
        include/widget.hpp
        include/worker_analysis.hpp
        include/worker_calculations.hpp
        include/worker_file_loader.hpp
        include/zodiac.hpp
        lib/rapidxml/rapidxml.hpp
        lib/rapidxml/rapidxml_iterators.hpp
        lib/rapidxml/rapidxml_print.hpp
        lib/rapidxml/rapidxml_utils.hpp
        lib/swe/swedate.h
        lib/swe/swedll.h
        lib/swe/sweephe4.h
        lib/swe/swehouse.h
        lib/swe/swejpl.h
        lib/swe/swemptab.h
        lib/swe/swenut2000a.h
        lib/swe/sweodef.h
        lib/swe/sweph.h
        lib/swe/swephexp.h
        lib/swe/swephlib.h
        lib/swe/swevents.h
        qss/resources.qrc
)

if(WIN32)
    list(APPEND PROJECT_SOURCES
        lib/swe/swecl.obj
        lib/swe/swedate.obj
        lib/swe/swehel.obj
        lib/swe/swehouse.obj
        lib/swe/swejpl.obj
        lib/swe/swemmoon.obj
        lib/swe/swemplan.obj
        lib/swe/sweph.obj
        lib/swe/swephlib.obj
    )
elseif(UNIX)
    list(APPEND PROJECT_SOURCES
        lib/swe/swecl.o
        lib/swe/swedate.o
        lib/swe/swehel.o
        lib/swe/swehouse.o
        lib/swe/swejpl.o
        lib/swe/swemmoon.o
        lib/swe/swemplan.o
        lib/swe/sweph.o
        lib/swe/swephlib.o
    )
endif()

qt_add_executable(AstroDb
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

set_target_properties(AstroDb PROPERTIES
    LINK_FLAGS "-static-libgcc -static-libstdc++"
)

target_link_libraries(AstroDb PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(AstroDb PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS AstroDb
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AstroDb)
endif()

