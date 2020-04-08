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
            modelId.append({"logoPath":logo,"projectName":name,"time_this_week": spentTimeWeek,"time_this_month": spentTimeMonth,"time_total": spentTimeAll})
        }
    }

    ListModel {
        id: modelId
    }

        Component {
            id: contactDelegate

            Rectangle {
                width: applicationWindow.width - 30; height: 100
                id: it
                border.color: "gray"


                Image {
                    id: image
                    width: 80
                    height: 80
                    anchors.top: it.top
                    anchors.topMargin: 20
                    anchors.bottom: it.bottom
                    anchors.bottomMargin: 20
                    anchors.left: it.left
                    anchors.leftMargin: 20
                    fillMode: Image.PreserveAspectFit
                    source: "file:/"+ logoPath

                }
                Text {
                    id: status
                    anchors.centerIn: it
                    anchors.leftMargin: 40
                    text: qsTr("Active")
                }
                Column {
                    id: col
                    width: 180
                    height: 30;
                    anchors.right: it.right
                    anchors.rightMargin: 20
                    anchors.top: it.top
                    anchors.topMargin: 20


                        Text {
                            id: timeThisWeekLabel
                            text: qsTr("time this week:")
                        }

                        Text {
                            id: timeThisWeekLabeValue
                            text: time_this_week
                            anchors.left: timeThisWeekLabel.right

                            anchors.leftMargin: 5
                        }


                        Text {

                            id: timeThisMonth
                            text: qsTr("this month:")
                            anchors.top: timeThisWeekLabel.bottom
                            anchors.topMargin: 2.5
                        }

                        Text {
                            id: timeThisMonthValue
                            text: time_this_month
                            anchors.left: timeThisWeekLabeValue.left
                            anchors.leftMargin: 0
                            anchors.top: timeThisWeekLabeValue.bottom
                            anchors.topMargin: 2.5
                        }

                        Text {
                            id: timeAll
                            text: qsTr("total:")
                            anchors.top: timeThisMonth.bottom
                            anchors.topMargin: 2.5
                        }
                        Text {
                            id: timeAllValue
                            text: time_total
                            anchors.top: timeThisMonthValue.bottom
                            anchors.topMargin: 2.5
                            anchors.left: timeThisMonthValue.left
                            anchors.leftMargin: 0
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
    D{i:15;anchors_height:200;anchors_width:370;anchors_x:29;anchors_y:128}
}
##^##*/
