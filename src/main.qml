import QtQuick 2.9
import QtQuick.Controls 2.2
import "qrc:/UI/Components"
import "UI"

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("DumbCalc - STC")
    header: ToolBar {
        id: toolBar
        height: 40
        //        contentHeight: toolButton.implicitHeight
        //        contentWidth: window.width
        Row {
            id: toolBarLayout
            anchors.fill: parent
            spacing: 6
            Label {
                id: calcLabelId
                width: toolBarLayout.width / 2
                height: toolBar.height
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                text: "Обычный"
                Delimiter {color: "black"}
            }
            Label {
                id: journaLabellId
                width: toolBarLayout.width / 2
                height: toolBar.height
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                text: "Журнал"
            }
        }
    }
    Row {
        id: mainContentItem
        anchors.fill: parent

        Column {
            id: calcColumn
            height: parent.height
            width: parent.width / 2
            Calculator {
                height: parent.height
                width: parent.width
            }
        }
        Column {
            id: journalColumn
            height: parent.height
            width: parent.width / 2
            ListView {
                id: journalList
                height: parent.height * 0.8
                width: parent.width
                verticalLayoutDirection: ListView.BottomToTop
                model: journalModel
                clip: true
                delegate: JournalItem {
                    height: journalList.height * 0.15
                    width: journalList.width
                    txt: index + 1 + ". " + text
                    clr: color
                }
                Connections {
                    target: journalModel
                    onRowsInserted: {
                        //journalList.contentY = 0
                        journalList.positionViewAtEnd()
                        //journalList.positionViewAtIndex(journalList.count - 1, ListView.End);
                    }
                }
                Rectangle {
                    anchors.top: parent.bottom
                    width: parent.width
                    height: 1
                    color: "transparent"
                    border.color: "black"
                }
            }
            Row {
                id: queueSizes
                height: parent.height * 0.2
                width: parent.width
                Label {
                    height: parent.height
                    width: parent.width / 2
                    font.pixelSize: 9
                    horizontalAlignment: Label.AlignHCenter
                    text: "Размер\nочереди запросов\n" + journalModel.requestsSize
                }
                Label {
                    height: parent.height
                    width: parent.width / 2
                    font.pixelSize: 9
                    horizontalAlignment: Label.AlignHCenter
                    text: "Размер\nочереди результатов\n" + journalModel.resultsSize
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
    }
    Component.onDestruction: {
        settingsManager.setWindowRect(Qt.rect(window.x, window.y, window.width, window.height))
    }
}
