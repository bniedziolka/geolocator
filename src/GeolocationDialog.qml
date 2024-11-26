import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Dialog {
    property var geolocationRef

    signal remove(string ip)

    anchors.centerIn: Overlay.overlay
    modal: true
    closePolicy: Popup.NoAutoClose

    height: 400
    width: 600

    title: geolocationRef?.ip ?? ""

    standardButtons: Dialog.Ok

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        ColumnLayout {
            GeolocationTable {
                geolocation: geolocationRef
            }
            Item {
                Layout.fillHeight: true
            }
            Button {
                text: qsTr("Remove")
                onClicked: {
                    confirmDialog.open()
                }
                MessageDialog {
                    id: confirmDialog
                    text: qsTr("Delete this entry?")
                    buttons: MessageDialog.Yes | MessageDialog.No
                    onAccepted: {
                        remove(geolocationRef.ip)
                        geolodationDialog.close()
                    }
                }
            }

            Layout.fillWidth: true
        }

        GeolocationMap {
            geolocation: geolocationRef
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
