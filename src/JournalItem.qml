import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: listDelegate
    property alias txt: label1.text
    property alias clr: label1.color
    Label {
        id: label1
        height: 80
        width: journalList.width
    }
}
