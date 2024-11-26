import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

import geolocator

Item {
    property string phrase: ""
    property GeolocationListModel model
    signal open()

    property string errorText: ""

    onOpen: {
        dialog.open()
        searchBackend.search(phrase)
    }

    SearchBackend {
        id: searchBackend

        onProcessing: {
            state = "loading"
            errorText = ""
        }
        onError: function(text) {
            state = "error"
            errorText = text
        }
        onDone: {
            state = "done"
            errorText = ""
        }
    }

    Dialog {
        id: dialog
        anchors.centerIn: Overlay.overlay
        modal: true
        closePolicy: Popup.NoAutoClose

        height: 400
        width: 600

        title: qsTr("Search results")

        onAccepted: {
            var result = model.store(searchBackend.geolocation)
            if (!result) {
                errorDialog.open()
            }
        }

        MessageDialog {
            id: errorDialog
            text: qsTr("Data store error")
            buttons: MessageDialog.Ok
        }

        Label {
            id: loadingLabel
            anchors.centerIn: parent
            visible: false
            elide: Text.ElideRight
        }

        RowLayout {
            id: resultsLayout
            anchors.fill: parent
            anchors.margins: 10

            visible: false

            spacing: 10

            ColumnLayout {
                GeolocationTable {
                    geolocation: searchBackend.geolocation
                }
                Item {
                    Layout.fillHeight: true
                }
                Layout.fillWidth: true
            }

            GeolocationMap {
                geolocation: searchBackend.geolocation
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

    states: [
        State {
            name: "loading"
            PropertyChanges {
                target: loadingLabel
                visible: true
                text: "Loading..."
            }
            PropertyChanges {
                target: resultsLayout
                visible: false
            }
            PropertyChanges {
                target: dialog
                standardButtons: Dialog.Cancel
            }
        },
        State {
            name: "error"
            PropertyChanges {
                target: loadingLabel
                visible: true
                text: qsTr("Error:") + " " + errorText
            }
            PropertyChanges {
                target: resultsLayout
                visible: false
            }
            PropertyChanges {
                target: dialog
                standardButtons: Dialog.Cancel
            }
        },
        State {
            name: "done"
            PropertyChanges {
                target: loadingLabel
                visible: false
            }
            PropertyChanges {
                target: resultsLayout
                visible: true
            }
            PropertyChanges {
                target: dialog
                standardButtons: Dialog.Cancel | Dialog.Save
            }
        }
    ]
}
