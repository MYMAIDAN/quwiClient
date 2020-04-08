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
        target: projectSetting

        onSetImageSource:
            logoImage.source = "file:/" + source;
    }

    Column{
        x: 62
        y: 116
        id: nameActiveColumn
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
            objectName: "activeSwithObject"
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
           anchors.verticalCenterOffset: 0
           anchors.left: parent.left
           anchors.leftMargin: 100
           anchors.verticalCenter: projectNameLabel.verticalCenter
           objectName: "projectNameEdit"
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
         onClicked: {
             projectSetting.changeProjectName(projectNameEdit.text)
             console.log(projectNameEdit.text)
         }
     }
    }
  }
    Image
    {


        id:logoImage
        width: 152
        height: 113
        visible: true
        anchors.bottom: nameActiveColumn.bottom
        anchors.bottomMargin: 0
        anchors.left: nameActiveColumn.right
        anchors.leftMargin: 20
        objectName: "logoImage"
    }

    Row
    {
        id: row
        width: 401
        height: 42
        anchors.left: nameActiveColumn.left
        anchors.leftMargin: 0
        anchors.top: nameActiveColumn.bottom
        anchors.topMargin: 10
        Switch {
            id: addMeWatcherSwitch
            text: qsTr("Switch")
            anchors.left: parent.left
            anchors.leftMargin: 0
            objectName: "ownerWatchedSwitch"
         }

        Text {
            id: element1
            text: qsTr("Add me as watcher to tickets created by others")
            anchors.left: addMeWatcherSwitch.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }
    }

}

/*##^##
Designer {
    D{i:4;anchors_x:57;anchors_y:159}
}
##^##*/
