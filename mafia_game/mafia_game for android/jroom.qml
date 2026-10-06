import QtQuick
import QtQuick.Controls

Page {
    id: jroomui
    background: Rectangle { color: "#000000" }
    Text {
        id: title1
        color: "#ffffff"
        text: qsTr("join room")
        font.family: "Stencil"
        font.pointSize: 30
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }
    Text {
        id: title2
        color: "#ffffff"
        text: qsTr("name of room")
        font.family: "Stencil"
        font.pointSize: 15
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height*0.25

    }
    TextField{
                id:room
                width: parent.width *0.7
                height: parent.height*0.1
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height*0.35
                font.family: "Impact"
                font.pointSize: 15
                background: Rectangle {
                        radius: 20
                        color: "white"
                        border.color: "#999999"
                    }
            }

    Text {
        id: title3
        color: "#ffffff"
        text: qsTr("your name")
        font.family: "Stencil"
        font.pointSize: 15
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height*0.55
    }

    TextField{
                id:name
                width: parent.width *0.7
                height: parent.height*0.1
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height*0.65
                font.family: "Impact"
                font.pointSize: 15
                background: Rectangle {
                        radius: 20
                        color: "white"
                        border.color: "#999999"
                    }
            }



    Rectangle{
        id:myBox
        width: parent.width *0.20
        height: parent.height*0.1
        color: "black"
        radius:10
        clip: true
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        Text {
            id: text3
            text: qsTr("start")
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }
        gradient: Gradient {
            GradientStop {
                position: 0.69;
                color: backend.color[3];
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }
        MouseArea {
                anchors.fill: parent
                hoverEnabled: true // هادي ضروري باش يخدم onEntered و onExited

                onEntered: {
                    backend.changeColor(3,"#2d2d2d")

                }
                onExited: {
                    backend.changeColor(3,"#999999")

                }

                onPressed: {
                    backend.changeColor(3,"#314928")

                }
                onReleased:{
                    backend.lougin(room.text,name.text)
                    jroomui.StackView.view.push("gameui.qml")
                }
            }

    }

    Button {
            id:btn0
            width: parent.width *0.1
            height: parent.height*0.1
            x:parent.width*0.01
            //y:parent.height*0.25
            text: "back"


            onClicked: jroomui.StackView.view.pop()
            background: Rectangle {
                    color: "red" // هذا هو لون الزر
                    radius: 10
                    border.color: "red"
                }

                contentItem: Text {
                    text: parent.text
                    color: "black" // هذا لون الكتابة
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
        }

}
