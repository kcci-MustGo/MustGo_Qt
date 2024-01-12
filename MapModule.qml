import QtQuick 2.0
import QtPositioning 5.12
import QtLocation 5.12
Item{
    visible: true
    width:600
    height:500
    //property double latitude:BotSpecification.currentPos[0]
    //property double longitude:BotSpecification.currentPos[1]

    Map{
        id: mapview
        anchors.fill: parent
        plugin: Plugin{
            id: osmPlugin
            name: "osm"
        }

        center: QtPositioning.coordinate(37.5573094, 126.835679)
        zoomLevel: 16

        MapPolyline {
            id: line
            line.color: "blue"
            line.width: 8
            path: beautiful.path
        }
    }
}
