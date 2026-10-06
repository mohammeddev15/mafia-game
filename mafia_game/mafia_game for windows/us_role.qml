import QtQuick
import QtQuick.Controls

Page {

    id: us_role1
    background: Rectangle { color: "#000000" }

    Text {
        id: title
        color: "#ffffff"
        text: backend.my_role
        font.family: "Elephant"
        font.pointSize: 20
        x:parent.width *0.1
        y:parent.height*0.01
    }

    Text {
        id: note1
        color: "#ffffff"
        text: backend.note
        font.family: "Elephant"
        font.pointSize: 15
        x:parent.width *0.01
        y:parent.height*0.05
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
                    if(checked) backend.savevote(modelData) // هادي هي اللي خاصك
                }
            }
        }
    }
}


    Rectangle{
        id:myBox2
        width: parent.width *0.5
        height: parent.height*0.05
        color: backend.color[5]
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
                    backend.start_fonction_of_your_role()
                    us_role1.StackView.view.pop()
                }
            }

    }



    Image {
        id: role_image
        source:backend.count_image
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 0
        width: parent.width *0.5
        height: parent.height*1
    }

}
