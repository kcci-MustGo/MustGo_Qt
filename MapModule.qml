import QtQuick
import QtLocation
import QtPositioning
//import QtQuick 2.0
//import QtPositioning 5.12
//import QtLocation 5.12
Item{
    visible: true
    width:300
    height:500


    function loadPath() {
        var lines = []
        for(var i=0; i < routeProvider.geopath.size(); i++){
            lines[i] = routeProvider.geopath.coordinateAt(i)
        }
        return lines;
    }

    Map{
        id: mapview
        anchors.fill: parent

        plugin: Plugin{
            id: osmPlugin
            name: "osm"
        }

        center: routeProvider.path && routeProvider.path.size > 0 ? routeProvider.path[0] : QtPositioning.coordinate(37.5579000, 126.835679)
        zoomLevel: 16

        MapPolyline {
            id: polylines
            line.color: "blue"
            line.width: 6
        }

        Connections{
            target: routeProvider
            onPathUpdated: {
                polylines.path = loadPath()
                if ( polylines.pathLength() > 0)
                    mapview.center = polylines.path[0];

            }
        }

        Component.onCompleted: polylines.path = loadPath()
    }
}
