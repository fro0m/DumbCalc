import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    //    width: 600
    //    height: 400
    title: qsTr("DumbCalc - STC")

    header: ToolBar {
        id: toolBar
        contentHeight: toolButton.implicitHeight
        contentWidth: window.width
        Row {
            anchors.fill: parent
            spacing: 6
            ToolButton {
                id: toolButton
                text: /*stackView.depth > 1 ? "\u25C0" :*/ "\u2630"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                enabled: false
            }
            Label {
                id: calcLabelId
                width: window.width / 2 - toolButton.width
                height: toolBar.height
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                text: "Обычный"//stackView.currentItem.title
            }
            Label {
                id: journaLabellId
                width: window.width  / 2
                height: toolBar.height
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                text: "Журнал"//stackView.currentItem.title

            }
        }


    }

    Row {
        id: mainContentItem
        anchors.fill: parent
        Column {
            id: calc
            height: parent.height
            width: parent.width / 2
        }
        Column {
            id: journal
            height: parent.height
            width: parent.width / 2
            ListView {
                id: journalList
                model: journalModel
                delegate: JournalItem {
                    txt: text
                    clr: color
                }
            }
        }
    }

    Component.onCompleted: {
        var windowGeometry = settingsManager.windowRect
        if (windowGeometry.x !== 0 && windowGeometry.y !== 0) {
            window.x = windowGeometry.x
            window.y = windowGeometry.y
        }
        window.width = windowGeometry.width
        window.height = windowGeometry.height

        journalModel.submitToNumber("545.33")
        journalModel.pressMinus()
        journalModel.submitToNumber("222")
        journalModel.pressCalculate()
    }
    Component.onDestruction: {
        settingsManager.setWindowRect(Qt.rect(window.x, window.y, window.width, window.height))
    }
}
