add_library(ui_base STATIC)

qt_add_qml_module(
    ui_base
    URI "ui_base"
    VERSION 1.0
    QML_FILES
    CatlistItem.qml
    CScrollBar.qml
    CTab.qml
    IconButton.qml
    IconLabel.qml
    PlaylistItem.qml
    RoundedImage.qml
    RoundedRectangle.qml
    SearchBar.qml
    TextIconButton.qml
    UScrollBar.qml
    UTextEdit.qml
    Utils.js
)
