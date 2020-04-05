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

    Column{
        x: 47
        y: 64

        width: 386
        height: 113

     Row
    {
        id:activeRow
        width: 182
        height: 50
        Text {
            id: activeLable
            text: qsTr("Active")
            anchors.verticalCenter: parent.verticalCenter
        }

        Switch {
            id: activeSwith
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: activeLable.verticalCenter
            anchors.left: activeLable.right
            anchors.leftMargin: 56
            checked: false
        }
    }

    Row
    {
        id:projectNameRow
        width: 393
        height: 68
        anchors.left: activeRow.right
        anchors.leftMargin: -182
        anchors.top: activeRow.bottom
        anchors.topMargin: -6
        Text {
            id: projectNameLabel
            text: qsTr("Name")
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField
        {
           id: projectNameEdit
           text: qsTr("Name")
           anchors.verticalCenterOffset: 0
           anchors.left: parent.left
           anchors.leftMargin: 100
           anchors.verticalCenter: projectNameLabel.verticalCenter
        }

     Button
     {
         id: changeNameButton
         width: 40
         height: 40
         text: "OK"
         display: AbstractButton.TextBesideIcon
         font.bold: true
         autoExclusive: true
         autoRepeat: false
         checkable: true
         highlighted: true
         visible: true
         anchors.verticalCenter: parent.verticalCenter
         anchors.left: projectNameEdit.right
         anchors.leftMargin: 20
     }
    }
  }
}

/*##^##
Designer {
    D{i:4;anchors_x:57;anchors_y:159}
}
##^##*/
