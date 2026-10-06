import QtQuick

import QtQuick.Controls
Page{
    id: about1
    background: Rectangle { color: "black" }

    title: qsTr("ٌRules")

    Text {
        id: title

        color: "#a37afb"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
        text: qsTr("About")
        font.family: "Arial Rounded MT"
        font.pointSize: 40

    }


    Rectangle {
        //width: myText.width + 20
        //height: myText.height + 10
        color: "#0f2d2a" // هذا هو لون الخلفية
        radius: 5
        width: parent.width * 0.9
        height: parent.height * 0.8
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        clip: true // ضروري

        Flickable {
            id: flick
            anchors.fill: parent
            anchors.margins: 10
            contentWidth: width // هادي كتمنع السكرول الأفقي
            contentHeight: myText.implicitHeight
            ScrollBar.vertical: ScrollBar {}

            Text {
                id: myText
                width: flick.width*0.90 // عرض النص هو عرض المنطقة
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Mafia Night - لعبة الذكاء والخداع الاجتماعي\n\nما هي لعبة المافيا؟\nالمافيا هي لعبة حفلات عالمية مشهورة، تلعب مع أصدقائك، فكرتها بسيطة: هناك مدينة هادئة دخلتها عصابة مافيا في الليل، وفي النهار يحاول الجميع كشف من هو القاتل بالكلام والذكاء فقط.\nهذه اللعبة تجمع بين الضحك والشك والتفكير.\n\nلماذا صنعت هذه النسخة؟\nصنعت هذه النسخة الرقمية لكي تستطيع لعبها مع أصدقائك من أي مكان في العالم بدون الحاجة للتجمع في غرفة واحدة، ولكي تكون سهلة وسريعة وغامضة، بنفس جو المافيا الحقيقي.\nتم تطويرها باستخدام Qt و QML و Firebase لتكون سريعة وتعمل على الويندوز والهاتف.\n\nعن المطور:\nأنا محمد أمين، مطور برمجيات من أكادير - المغرب.\nشغوف بالبرمجة وصناعة الألعاب البسيطة التي تجمع الناس.\nهذه أول نسخة من اللعبة (Version 1.0 - 2025)، أعمل حاليا على نسخة الهاتف بوضع أفقي.\nأتمنى أن تستمتعوا باللعبة، واذا واجهتم أي مشكل أو عندكم فكرة جديدة راسلوني.\n\nشكرا لكم للعب Mafia Night!"
                color: "#ffffff"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
    }

    Button {
            id:btn0
            width: parent.width *0.05
            height: parent.height*0.05
            x:parent.width*0.01
            //y:parent.height*0.25
            text: "back"


            onClicked: about1.StackView.view.pop()
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
