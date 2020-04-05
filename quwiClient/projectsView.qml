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

    ListModel {
        id: modelId
        ListElement {
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
        }
    }

    Rectangle {
        width: 500; height: 200

        Component {
            id: contactDelegate
            Item {
                width: 500; height: 40
                Image {
                    id: image
                    width: 64
                    height: 29
                    fillMode: Image.PreserveAspectFit
                    source: "photo-1503023345310-bd7c1de61c7d.jpg"
                }
                Text {
                    id: status
                    anchors.left: image.right
                    anchors.leftMargin: 40
                    text: qsTr("Active")
                }
                Column {
                    id: col
                    anchors.left: status.right
                    anchors.leftMargin: 30
                    Text { text: '<b>Name:</b> ' + name }
                    Text { text: '<b>Number:</b> ' + number }
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
