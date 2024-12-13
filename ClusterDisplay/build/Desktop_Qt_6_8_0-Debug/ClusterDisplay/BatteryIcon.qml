import QtQuick
import QtQuick.Layouts

Rectangle {
    color: "white"
    border.width: 3
    border.color: "black"
    Rectangle {
        anchors.fill: parent
        anchors.margins: 3
        color: "transparent"
        Rectangle {
            color: "green"
            width: parent.width * batteryIconObj.percentage / 100
            height: parent.height
        }
        RowLayout {
            anchors.fill: parent
            spacing: 0
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
            SimpleBar {}
        }
    }
}
