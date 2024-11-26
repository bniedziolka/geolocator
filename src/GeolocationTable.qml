import QtQuick
import QtQuick.Controls

import geolocator

Grid {
    property var geolocation

    columns: 2
    spacing: 10

    Label {
        text: "Ip:"
    }
    Label {
        text: geolocation?.ip ?? ""
    }

    Label {
        text: "Continent:"
    }
    Label {
        text: geolocation?.continent ?? ""
    }

    Label {
        text: "Country:"
    }
    Label {
        text: geolocation?.country ?? ""
    }

    Label {
        text: "Region:"
    }
    Label {
        text: geolocation?.region ?? ""
    }

    Label {
        text: "City:"
    }
    Label {
        text: geolocation?.city ?? ""
    }

    Label {
        text: "Zip:"
    }
    Label {
        text: geolocation?.zip ?? ""
    }

    Label {
        text: "Latitude:"
    }
    Label {
        text: geolocation?.latitude.toFixed(4) ?? ""
    }

    Label {
        text: "Longitude:"
    }
    Label {
        text: geolocation?.longitude.toFixed(4) ?? ""
    }
}
