import QtQuick
import QtQuick.Controls

Page {
    id: startui
    background: Rectangle { color: "#000000" }
    Rectangle{
        width: parent.width *0.9
        height: parent.height*0.7
        radius: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        clip: true

        Image {
                id: logo1
                source: "images/logo.png"
                anchors.fill: parent
            }
    }

    Rectangle{
        id:myBox1
        width: parent.width *0.10
        height: parent.height*0.1
        color: "black"
        radius:10
        clip: true

        Text {
            id: text1
            text: qsTr("about")
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }
        gradient: Gradient {
            GradientStop {
                position: 0.69;
                color: backend.color[0];
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }
        x:parent.width*0.20
        y:parent.height*0.8
        MouseArea {
                anchors.fill: parent
                hoverEnabled: true // هادي ضروري باش يخدم onEntered و onExited

                onEntered: {
                    backend.changeColor(0,"#2d2d2d")

                }
                onExited: {
                    backend.changeColor(0,"#999999")

                }

                onPressed: {
                    backend.changeColor(0,"#314928")

                }
                onReleased:{
                    startui.StackView.view.push("about.qml")
                }
            }

    }



    Rectangle{
        id:myBox2
        width: parent.width *0.10
        height: parent.height*0.1
        color: "black"
        radius:10
        clip: true

        Text {
            id: text2
            text: qsTr("the Rules")
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }
        gradient: Gradient {
            GradientStop {
                position: 0.69;
                color: backend.color[1];
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }
        x:parent.width*0.45
        y:parent.height*0.8
        MouseArea {
                anchors.fill: parent
                hoverEnabled: true // هادي ضروري باش يخدم onEntered و onExited

                onEntered: {
                    backend.changeColor(1,"#2d2d2d")

                }
                onExited: {
                    backend.changeColor(1,"#999999")

                }

                onPressed: {
                    backend.changeColor(1,"#314928")

                }
                onReleased:{
                    startui.StackView.view.push("Rules.qml")
                }
            }

    }




    Rectangle{
        id:myBox3
        width: parent.width *0.10
        height: parent.height*0.1
        color: "black"
        radius:10
        clip: true

        Text {
            id: text3
            text: qsTr("join room")
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }
        gradient: Gradient {
            GradientStop {
                position: 0.69;
                color: backend.color[2];
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }
        x:parent.width*0.70
        y:parent.height*0.8
        MouseArea {
                anchors.fill: parent
                hoverEnabled: true // هادي ضروري باش يخدم onEntered و onExited

                onEntered: {
                    backend.changeColor(2,"#2d2d2d")

                }
                onExited: {
                    backend.changeColor(2,"#999999")

                }

                onPressed: {
                    backend.changeColor(2,"#314928")

                }
                onReleased:{
                    startui.StackView.view.push("jroom.qml")
                }
            }

    }
}
