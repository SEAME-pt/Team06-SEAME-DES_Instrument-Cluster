import QtQuick
import QtQuick.Layouts
//import QtQuick.Effects

/*Rectangle {
    color: "black"
    ColumnLayout {
        anchors.fill: parent
        //Progress Bar
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            containmentMask: Rectangle {
                color: "white"
                //anchors.fill: parent
                width: 100//parent.width * speedometerObj.speed / 25
                height: parent.height
            }

            RowLayout {

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "green"
                }
            }

        }
        //Display of the value
        Text {
            color: "white"
            id: speedPlaceholder
            font.family: fontAwesome.name
            font.pointSize: 20
            text: speedometerObj.speed + " Km/h"
        }
    }
    FontLoader { id: fontAwesome; source: "qrc:/airstrike3d.ttf"}
}*/

ColumnLayout {
Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "white"
    border.width: 1
    border.color: "black"
    Rectangle {
        anchors.fill: parent
        anchors.margins: 3
        color: "transparent"
        Rectangle {
            color: "green"
            width: parent.width * speedometerObj.speed / 25
            height: parent.height
        }
        RowLayout {
            anchors.fill: parent
            spacing: 0
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
        }
    }
}
Text {
    color: "black"
    id: speedPlaceholder
    Layout.fillWidth: true
    horizontalAlignment: Text.AlignHCenter
    font.family: fontAwesome.name
    font.pointSize: 20
    text: speedometerObj.speed + " Km/h"
}
FontLoader { id: fontAwesome; source: "qrc:/airstrike3d.ttf"}
}
