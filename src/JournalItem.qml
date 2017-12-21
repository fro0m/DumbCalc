import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: listDelegate
    property alias txt: label1.text
    property alias clr: label1.color
    Label {
        id: label1
        height: parent.height
        width: journalList.width
        padding: width * 0.04
        horizontalAlignment: Label.AlignRight
        verticalAlignment: Label.AlignVCenter
        wrapMode: Label.WordWrap
        font.pixelSize: width * 0.04
    }
//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "red"
//    }
}
