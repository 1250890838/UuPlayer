qt_add_library(gui STATIC)

set(plain_qml_files
    qml/Main.qml
    qml/leftNavigationPanel/LeftNavigationPanel.qml
)

set(singletons_qml_files qml/assets/Icons.qml)

set(custom_shared_qml_files 
    qml/components/button/IconButton.qml
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
    RESOURCE_PREFIX /
    RESOURCES
        images/demo.png
        qml/components/qmldir
    IMPORT_PATH
        qml/
)
