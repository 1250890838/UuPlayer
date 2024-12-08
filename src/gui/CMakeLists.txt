qt_add_library(gui STATIC)

set(plain_qml_files
    qml/Main.qml
    qml/leftNavigationPanel/LeftNavigationPanel.qml
    qml/leftNavigationPanel/NavigationPanelItem.qml
    qml/stackPages/CloudMusicSelectedPage.qml
    qml/stackPages/CommunityPage.qml
    qml/stackPages/DownloadManagePage.qml
    qml/stackPages/FavorMusicPage.qml
    qml/stackPages/LocalMusicPage.qml
    qml/stackPages/PodcastPage.qml
    qml/stackPages/RecentPlayPage.qml
)

set(singletons_qml_files qml/assets/Icons.qml)

set(custom_shared_qml_files 
    qml/components/button/IconButton.qml
    qml/components/button/IconLabel.qml
)

set(js_files
    qml/leftNavigationPanel/NavigateLogic.js
)
#[[ set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
]]

qt_add_qml_module(gui
    URI "gui"
    VERSION 1.0
    QML_FILES
    ${plain_qml_files}
    ${singletons_qml_files}
    ${custom_shared_qml_files}
    ${js_files}
    RESOURCE_PREFIX /
    RESOURCES
        images/demo.png
        qml/components/qmldir
    IMPORT_PATH
        qml/
)

