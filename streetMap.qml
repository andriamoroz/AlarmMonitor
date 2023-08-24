import QtQuick 2.2
import QtQuick.Controls 2.15
import QtLocation 5.15

Item {
    visible: true
    width: 800
    height: 480

    Plugin{
        id: mapPlugin
        name: "osm"
    }

    Map{
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 10
    }
}
