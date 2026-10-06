cmake_minimum_required(VERSION 3.16)

project(mafia VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appmafia
    main.cpp
)

qt_add_qml_module(appmafia
    URI mafia
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES backend.h backend.cpp
        QML_FILES StartUI.qml
        RESOURCES images/735128856_122118382736776700_2754096892861324660_n.jpg images/735577286_122118382532776700_2883574024477408815_n.jpg images/736053905_122118382844776700_1637321274866886842_n.jpg images/736858136_122118382628776700_4273887804627270561_n.jpg images/737774558_122118382526776700_1474392633146894410_n.jpg images/737819474_122118382802776700_1838107492342197626_n.jpg images/738937662_122118382742776700_1428208817051282161_n.jpg images/739762701_122118382634776700_629602115043394480_n.jpg images/740070516_122118382604776700_9212383590004908530_n.jpg images/logo.png
        QML_FILES Rules.qml
        QML_FILES jroom.qml
        QML_FILES gameui.qml
        QML_FILES vote.qml
        QML_FILES us_role.qml
        RESOURCES images/image_20261001_081748.jpg
        QML_FILES
        RESOURCES
        QML_FILES about.qml
        RESOURCES images/day.jpg



)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appmafia PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmafia
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmafia
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appmafia
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
