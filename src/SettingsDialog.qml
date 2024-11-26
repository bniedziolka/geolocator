import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

import geolocator

Dialog {

    anchors.centerIn: Overlay.overlay
    modal: true
    closePolicy: Popup.NoAutoClose

    height: 400
    width: 600

    title: qsTr("Settings")

    standardButtons: Dialog.Ok | Dialog.Cancel

    SettingsBackend {
        id: settingsBackend
    }

    RowLayout {

        anchors.fill: parent
        anchors.centerIn: parent

        Label {
            text: "ApiKey"
        }

        TextField {
            id: apiKeyField
            text: settingsBackend.apiKey
            Layout.fillWidth: true
        }

    }

    onAccepted: {
        settingsBackend.apiKey = apiKeyField.text
    }
}
