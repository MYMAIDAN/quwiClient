import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    Connections {
        target: loginHandler

        onSendError: {
            errorLable.text = error
        }
        onCloseWindow:
        {
            applicationWindow.close()
        }
    }

    Text
    {
        id: loginLabel
        anchors.bottom: loginEdit.top
        anchors.bottomMargin: 20
        anchors.left: loginEdit.left
        text: "LOGIN"
    }

    TextField
    {
        id: loginEdit
        anchors.centerIn: parent
        placeholderText: "Email"
    }

    TextField
    {
        id: passwordEdit
        anchors.top: loginEdit.bottom
        anchors.horizontalCenter: loginEdit.horizontalCenter
        anchors.topMargin: 10
        echoMode: "Password"
        placeholderText: "Password"
    }

    Button
    {
        id: loginButton
        anchors.top: passwordEdit.bottom
        anchors.topMargin: 10
        anchors.left: passwordEdit.left
        text: "Login"
        layer.enabled: false
        spacing: 10
        layer.format: ShaderEffectSource.RGB
        layer.mipmap: true
        font.family: "Tahoma"
        autoExclusive: true
        checkable: false
        display: AbstractButton.TextBesideIcon
        onClicked:
        {
            loginHandler.recieveData(loginEdit.text,passwordEdit.text)
        }
    }

    Text {
        id: errorLable
        anchors.top: loginButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: loginEdit.horizontalCenter
        color: "#FF0000"
    }


}

/*##^##
Designer {
    D{i:2;anchors_x:220}
}
##^##*/
