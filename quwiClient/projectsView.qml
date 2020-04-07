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
            modelId.append({"projectName":name,"time_this_week": spentTimeWeek,"time_this_month": spentTimeMonth,"time_total": spentTimeAll})
        }
    }

    ListModel {
        id: modelId
    }

        Component {
            id: contactDelegate

            Rectangle {
                width: applicationWindow.width - 30; height: 50
                id: it
                border.color: "gray"


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
                    Row{
                        Text {
                            id: timeThisWeekLabel
                            text: qsTr("time this week:")
                        }

                        Text {
                            id: timeThisWeekLabeValue
                            text: time_this_week

                            anchors.leftMargin: 10
                        }
                    }

                    Row{

                        Text {

                            id: timeThisMonth
                            text: qsTr("this month:")
                        }

                        Text {
                            id: timeThisMonthValue
                            text: time_this_month
                        }

                    }

                    Row
                    {
                        Text {
                            id: timeAll
                            text: qsTr("total:")
                        }

                        Text {
                            id: timeAllValue
                            text: time_total
                            anchors.top: timeThisMonthValue.bottom
                            anchors.left: timeThisMonthValue.left
                        }

                    }


                    Text{
                        id:projectName
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked:
                    {
                        newProjectHandler.openProjectSetting(modelId.get(index).projectName)
                        console.log(modelId.get(index).projectName);
                    }
                }
            }
        }


        ListView {
            anchors.fill: parent

        model: modelId
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
        anchors.margins: 20
        spacing: 20
    }
}

/*##^##
Designer {
    D{i:13;anchors_height:200;anchors_width:370;anchors_x:29;anchors_y:128}D{i:19;anchors_height:200;anchors_width:370;anchors_x:29;anchors_y:128}
}
##^##*/
