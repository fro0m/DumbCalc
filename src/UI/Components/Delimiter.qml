import QtQuick 2.0

Item {
    id: root
    property alias color: delimiter._color
    anchors.right: parent.right
    height: parent.height
    width: 1
    Rectangle {
        id: delimiter
        property color _color: "black"
        width: parent.width
        height: parent.height
        border.color: _color
        border.width: 1
        color: "transparent"
    }
}
