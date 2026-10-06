import QtQuick
import QtQuick.Controls

Page {

    id: voteing
    background: Rectangle { color: "#000000" }

    Text {
        id: title
        color: "#ffffff"
        text: qsTr("voteing")
        font.family: "Elephant"
        font.pointSize: 20
        x:parent.width *0.15
        y:parent.height*0.01
    }
    Rectangle{
        width: parent.width *0.5
        height: parent.height*0.7
        color: "#2a6929"
        x:parent.width *0.0
        y:parent.height*0.2
        radius: 20
    Column {
        spacing: 10
        anchors.centerIn: parent
        width: parent.width *0.9
        height: parent.height*0.9


        Repeater {
            model: backend.players.split("\n") // كيدير لوب قد عدد اللاعبين

            delegate: RadioButton {
                // ما تخليش الواحد يصوت على راسو
                visible: modelData!== backend.myName && modelData.trim()!== ""
                text: modelData
                onCheckedChanged: {
                    backend.savevote(modelData)
                }
            }
        }
    }
}


    Rectangle{
        id:myBox2
        width: parent.width *0.5
        height: parent.height*0.05
        gradient: Gradient {
            GradientStop {
                position: 1;
                color: backend.color[5];
            }}
        radius:10
        clip: true
        x:parent.width *0.0
        y:parent.height*0.93

        Text {
            id: text2
            text:"send"
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }

        MouseArea {
                anchors.fill: parent
                hoverEnabled: true


                onPressed: {
                    backend.changeColor(5,"#073f09")

                }
                onReleased:{
                    backend.changeColor(5,"green")
                    backend.sendvote()
                    voteing.StackView.view.pop()
                }
            }

    }

    Image {
        id: role_image
        source:backend.image[5]
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 0
        width: parent.width *0.5
        height: parent.height*1
    }


    Button {
                id:btn0
                width: parent.width *0.1
                height: parent.height*0.1
                x:parent.width*0.01
                //y:parent.height*0.25
                text: "back"


                onClicked: voteing.StackView.view.pop()
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
