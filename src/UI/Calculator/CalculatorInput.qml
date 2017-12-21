import QtQuick 2.0

Item {
    id: root
    signal digitPressed(string digit)
    signal signChPressed()
    signal dotPressed()
    signal plusPressed()
    signal minusPressed()
    signal multiplyPressed()
    signal dividePressed()
    signal calculatePressed()
    GridView {
        id: mainView
        height: parent.height * 0.8
        width: parent.width
        cellWidth: root.width / 4; cellHeight: root.height / 5
        interactive: false
        property var modelData: [
            {"sym" : "7", "fun" : function() {digitPressed(7)}},
            {"sym" : "8", "fun" : function() {digitPressed(8)}},
            {"sym" : "9", "fun" : function() {digitPressed(9)}},
            {"sym" : "+", "fun" : function() {plusPressed()}},
            {"sym" : "4", "fun" : function() {digitPressed(4)}},
            {"sym" : "5", "fun" : function() {digitPressed(5)}},
            {"sym" : "6", "fun" : function() {digitPressed(6)}},
            {"sym" : "-", "fun" : function() {minusPressed()}},
            {"sym" : "1", "fun" : function() {digitPressed(1)}},
            {"sym" : "2", "fun" : function() {digitPressed(2)}},
            {"sym" : "3", "fun" : function() {digitPressed(3)}},
            {"sym" : "\u00D7", "fun" : function() {multiplyPressed()}},
            {"sym" : "\u00B1", "fun" : function() {signChPressed()}},
            {"sym" : "0", "fun" : function() {digitPressed(0)}},
            {"sym" : ".", "fun" : function() {dotPressed()}},
            {"sym" : "\u00F7", "fun" : function() {dividePressed()}}
        ]
        model: 16
        delegate: CalcButton {
            height: root.height / 5
            width: root.width / 4
            text: mainView.modelData[index].sym
            onClicked: mainView.modelData[index].fun()
        }
    }
    CalcButton {
        id: deriveButton
        anchors.top: mainView.bottom
        height: root.height / 5
        width: root.width
        text: "="
        onClicked: calculatePressed()
    }
}
