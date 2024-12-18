import QtQuick
import QtQuick.Controls

Dialog {
    id: dialog
    title: "Title"
    modal:true
    visible:true
    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked")
}
