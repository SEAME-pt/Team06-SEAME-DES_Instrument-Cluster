import QtQuick
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    ColumnLayout {
        anchors.fill: parent
        Speedometer {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth: 500
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
        }
        BatteryIcon {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth: 100
            Layout.maximumHeight: 50
            Layout.alignment: Qt.AlignHCenter
            Text {
                anchors.centerIn: parent
                //font.family: fontAwesome.name
                text: batteryIconObj.percentage + "%"
                color: "black"
            }

        }
    }


}
