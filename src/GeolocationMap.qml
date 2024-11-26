import QtQuick
import QtQuick.Layouts

import QtLocation
import QtPositioning

Map {
    property var geolocation

    plugin: osmPlugin
    zoomLevel: 10
    minimumZoomLevel: 5
    copyrightsVisible: false

    center: QtPositioning.coordinate(geolocation?.latitude ?? 0.0, geolocation?.longitude ?? 0.0)

    WheelHandler {
        id: wheel
        acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                         ? PointerDevice.Mouse | PointerDevice.TouchPad
                         : PointerDevice.Mouse
        rotationScale: 1/120
        property: "zoomLevel"
    }

    DragHandler {
       id: drag
       target: null
       onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
    }

    MapCircle {
        center {
            latitude: geolocation?.latitude ?? 0.0
            longitude: geolocation?.longitude ?? 0.0
        }
        radius: 1500.0
        color: "blue"
        opacity: 0.5
    }

    Plugin {
        id: osmPlugin
        name: "osm"
        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
        PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }
    }
}
