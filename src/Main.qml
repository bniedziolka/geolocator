import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQml.Models

import geolocator

ApplicationWindow {
    id: root
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("geolocator")

    Component.onCompleted: {
        geolocationModel.init()
    }

    MessageDialog {
        id: messageDialog
        buttons: MessageDialog.Ok
        text: "Application initialization error."
        onAccepted: root.close()
    }

    GeolocationListModel {
        id: geolocationModel
        onRepositoyError: {
            messageDialog.text = "Database initialization error"
            messageDialog.open()
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.margins: 10

            TextField {
                id: textField
                placeholderText: "IP or domain"
                focus: true
                Layout.fillWidth: true
            }
            Button {
                text: "GO"
                onClicked: {
                    searchDialog.phrase = textField.text
                    searchDialog.open()
                    textField.clear()
                }
                SearchDialog {
                    id: searchDialog
                    model: geolocationModel
                }
                enabled: textField.length > 0
            }
        }

        ListView {
            id: listView
            model: geolocationModel
            Layout.fillHeight: true
            delegate: ItemDelegate {
                text: modelData.ip
                onClicked: {
                    geolodationDialog.geolocationRef = modelData
                    geolodationDialog.open()
                }
            }
            GeolocationDialog {
                id: geolodationDialog
                onRemove: {
                    var result = geolocationModel.remove(ip)
                    if (!result) {
                        errorDialog.open()
                    }
                }
            }
        }

        MessageDialog {
            id: errorDialog
            text: qsTr("Data remove error")
            buttons: MessageDialog.Ok
        }

        Button {
            text: "Settings"
            onClicked: {
                settingsDialog.open()
            }

            SettingsDialog {
                id: settingsDialog
            }
        }
    }
}
