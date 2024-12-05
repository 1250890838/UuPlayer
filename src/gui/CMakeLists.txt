qt_add_library(gui STATIC)

set(plain_qml_files
    qml/Main.qml
    qml/components/button/IconButton.qml
    qml/components/button/Test.qml
)

set(qml_singletons qml/assets/Icons.qml)

#[[ set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
]]

qt_add_qml_module(gui
    URI "gui"
    VERSION 1.0
    QML_FILES
    ${plain_qml_files}
    ${qml_singletons}
    RESOURCE_PREFIX /
    RESOURCES
        images/demo.png
    IMPORT_PATH
        qml/
)