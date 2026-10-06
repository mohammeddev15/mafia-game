import QtQuick
import QtQuick.Controls

Window {
    width: 1500; height: 900; visible: true
    minimumWidth: 1000
    minimumHeight: 500
    StackView {
        id: myStack
        anchors.fill: parent
        initialItem: StartUI{}
    }
}
