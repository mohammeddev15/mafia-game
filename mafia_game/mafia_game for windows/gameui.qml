import QtQuick
import QtQuick.Controls

Page {
    id: gameui1
    //background: Rectangle { color: "#1f216d" }



    Rectangle {
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: backend.background_image // الصورة ديالك
            fillMode: Image.PreserveAspectCrop
            cache: true
            asynchronous: true
        }

        Rectangle {
            anchors.fill: parent
            color: "#0a0a0a"
            opacity: 0.75
        }

        //this is the players
    Text {
        y:parent.height*0.15
        color: "#ffffff"
        x:parent.width *0.01
        id: titleplayers
        text: qsTr("players:")
        font.family: "Arial Rounded MT"
        font.bold: true
        font.pointSize: 20
    }
    Rectangle {
        color: "#cc0F122E"
        radius: 5
        width: parent.width * 0.15
        height: parent.height * 0.8
        y:parent.height*0.19
        x:parent.width *0.01
        clip: true // ضروري

        Flickable {
            id: flick
            anchors.fill: parent
            anchors.margins: 10
            contentWidth: width // هادي كتمنع السكرول الأفقي
            contentHeight: mytxt.implicitHeight
            ScrollBar.vertical: ScrollBar {}

            Text {
                id: mytxt
                width: flick.width*0.90 // عرض النص هو عرض المنطقة
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#ffffff"
                text: {
                    if(backend.my_role === "mafia" || backend.my_role === "boss" || backend.my_role === "silencer"){
                        return backend.players + "\n_____________\n you are from mafia\n" + backend.your_mafia_team
                    } else {
                        return backend.players
                    }
                }

                font.pointSize: 11
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
    }


    //this for notes

    Text {
        id: note1
        color: "#ffffff"
        text: backend.note
        font.family: "Elephant"
        font.pointSize: 15
        x:parent.width *0.25
        y:parent.height*0.1
    }


 // this is chat

    Text {
        y:parent.height*0.20
        x:parent.width *0.2
        id: titlechat
        text: qsTr("chat:")
        font.family: "Arial Rounded MT"
        font.bold: true
        font.pointSize: 20
        color: "#ffffff"
    }
    Rectangle {

            radius: 5
            width: parent.width * 0.7
            height: parent.height * 0.6
            color: "#99000000"
            y:parent.height*0.25
            x:parent.width *0.2
            clip: true // ضروري

            Flickable {
                id: flick1
                anchors.fill: parent
                anchors.margins: 10
                contentWidth: width // هادي كتمنع السكرول الأفقي
                contentHeight: mytxt1.implicitHeight
                ScrollBar.vertical: ScrollBar {}

                Text {
                    id: mytxt1
                    width: flick1.width*0.90 // عرض النص هو عرض المنطقة
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#ffffff"
                    text: backend.msg

                    font.pointSize: 11
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }
        }



//this for write a message


    Rectangle{
        color: "#0d1f216d"
        width: parent.width *0.9
        height: parent.height*0.035
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height*0.025
    TextField{
                id:message
                width: parent.width *0.7
                height: parent.height*1
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: parent.width *0.05
                font.family: "Bahnschrift"
                font.pointSize: 15
                background: Rectangle {
                        radius: 20
                        color: "white"
                        border.color: "#999999"
                    }
                placeholderText: qsTr("send message")
            }
    Rectangle{
        id:myBox1
        width: parent.width *0.15
        height: parent.height*1
        gradient: Gradient {
            GradientStop {
                position: 1;
                color: backend.color[6];
            }}
        radius:10
        clip: true
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: parent.width *0.05
        Text {
            id: text1
            text: qsTr("send")
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }

        MouseArea {
                anchors.fill: parent
                hoverEnabled: true


                onPressed: {
                    backend.changeColor(6,"#073f09")

                }
                onReleased:{
                    backend.changeColor(6,"green")
                    backend.sendmsg(message.text)
                    message.text=""
                }
            }

    }

}

//this for count :number of players

    Text {
        id: count
        color: "#ffffff"
        text: backend.count
        font.family: "Elephant"
        font.pointSize: 30
        y:parent.height*0.04
        x:parent.width *0.95

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
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20

        Text {
            id: text2
            text:backend.myBox2txt
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
                    gameui1.StackView.view.push(backend.myBox2ui)
                }
            }

    }

    Rectangle{
        id: startBox

        visible: backend.mycount === 1 && backend.count >= 8
        width: parent.width *0.5
        height: parent.height*0.05
        color: backend.color[7]
        radius:10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 80

        Text {
            text:backend.startBoxtxt
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                backend.changeColor(7,"#a05a08")

            }
            onReleased:{
                backend.changeColor(7,"orange")
                backend.distributeRoles()
            }


        }
    }


    Rectangle{
        id: startBox1

        visible: backend.mycount === 1 && backend.count >= 8 && backend.dayornight === "day"
        width: parent.width *0.15
        height: parent.height*0.05
        color: backend.color[8]
        radius:10
        x:parent.width *0.8
        y: parent.height*0.9

        Text {
            text:backend.startBox1txt
            font.family: "Stencil"
            font.pointSize: 15
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                backend.changeColor(8,"#a05a08")

            }
            onReleased:{
                backend.changeColor(8,"orange")
                backend.changisnight()
            }


        }
    }




    Text {
        y:parent.height*0.07
        x:parent.width *0.01
        id: status
        text: qsTr("status:"+backend.dayornight)
        font.family: "Arial Rounded MT"
        font.bold: true
        font.pointSize: 20
        color: "#ffffff"
    }
    Text {
        y:parent.height*0.11
        x:parent.width *0.01
        id: role
        text: qsTr("role:"+backend.my_role)
        font.family: "Arial Rounded MT"
        font.bold: true
        font.pointSize: 20
        color: "#ffffff"
    }
}
}

















