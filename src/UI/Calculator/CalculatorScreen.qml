import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: root
    width: 100
    property var text: "0"
    function clear() {
        text = "0"
    }
    function addChar(ch) {
        if (text === "0" ) {
            text = ch;
        } else {
            text += ch;
        }
    }
    clip: true
    Label {
        id: calcText
        height: parent.height
        width: parent.width
        padding: root.height * 0.15
        text: root.text
        font.pixelSize: text.length > 8  ? root.width * 0.06 : root.width * 0.18
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignRight
        maximumLineCount: 1
        wrapMode: Label.NoWrap
//        onContentWidthChanged: {
//            if(contentWidth > calcText.width ) {
//                print(calcText.x, contentWidth, calcText.width, root.width)
//                calcText.x -= 35
//                calcText.width -+ 35
//            }
//        }
    }
}
