import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.0

Window {

    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    Connections {
        target: newProjectHandler

        onAppendNewProject: {
            modelId.append({"time_this_week": spentTimeWeek,"time_this_month": spentTimeMonth,"time_total": spentTimeAll})
        }
    }

    ListModel {
        id: modelId
    }

    Rectangle {
        width: parent.width; height: 200
        id: rec

        Component {
            id: contactDelegate
            Item {
                width:  rec.width; height: 50
                id: it
                Image {
                    id: image
                    width: 64
                    height: 29
                    fillMode: Image.PreserveAspectFit
                    source: "photo-1503023345310-bd7c1de61c7d.jpg"

                }
                Text {
                    id: status
                    anchors.horizontalCenter: it.horizontalCenter
                    anchors.leftMargin: 40
                    text: qsTr("Active")
                }
                Column {
                    id: col
                    anchors.leftMargin: 30
                    anchors.right: it.right

                    Text {
                        id: timeThisWeekLabe
                        text: qsTr("time this week:" + time_this_week)
                    }
                    Text {
                        id: timeThisMonth
                        text: qsTr("this month:" + time_this_month)
                    }
                    Text {
                        id: timeAll
                        text: qsTr("total:" + time_total)
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked:
                    {
                        console.log("Hello")
                    }
                }
            }
        }
    }

    ListView {
        width: 370; height: 200

        model: modelId
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}
