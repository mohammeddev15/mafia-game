import QtQuick

import QtQuick.Controls
Page{
    id: rules1
    background: Rectangle { color: "black" }

    title: qsTr("ٌRules")

    Text {
        id: title

        color: "#a37afb"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        text: qsTr("Rules")
        font.family: "Arial Rounded MT"
        font.pointSize: 35

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
                text: "مرحبا بك في لعبة المافيا! هذه لعبة ذكاء وخداع.\n\nكيف تبدأ اللعبة:\n1- تدخل اسم الغرفة واسمك وتضغط دخول.\n2- يجب أن نكون 8 لاعبين على الأقل.\n3- أول واحد دخل للغرفة هو الزعيم، هو اللي يوزع الأدوار ويبدأ الليل.\n\nماذا يحدث عندما يأتي الليل:\nعندما تتغير خلفية اللعبة إلى صورة الليل المظلمة وتتغير كلمة day إلى night فوق، هذا يعني أننا في الليل. في هذا الوقت ستظهر لك واجهة us role.\nهنا يمكنك استعمال قدرتك مرة واحدة فقط في كل ليلة، اختر اسم واحد واضغط استعمل:\n\n- اذا كنت silencer: يمكنك اختيار شخص واحد، هذا الشخص في النهار القادم لن يستطيع كتابة أي رسالة.\n- اذا كنت boss: أنت الرئيس، اختر شخصا لتقتله في الليل، سيموت الا اذا حماه الطبيب.\n- اذا كنت medic: أنت الطبيب، اختر شخصا لتحميه، اذا اختاره الـ boss للقتل فلن يموت وستظهر لك رسالة this one is saved.\n- اذا كنت mafia: أنت فرد من المافيا، اختر شخصا لتمنعه من استعمال قدرته هذه الليلة، ستظهر له رسالة you are blocked.\n- اذا كنت sniper: أنت القناص، اختر شخصا تظنه من المافيا. اذا كان فعلا من المافيا (boss أو silencer أو mafia) سيموت هو، واذا كان مواطنا عاديا ستموت أنت بدلا منه.\n- اذا كنت kid: أنت الطفل الفضولي، اختر شخصا واحدا لتعرف ما هو دوره، سيظهر لك دوره.\n- اذا كنت mayor: أنت العمدة، ليس لديك قدرة في الليل، انتظر النهار.\n- اذا كنت citizen: أنت مواطن عادي، ليس لديك قدرة، انتظر النهار وصوت بذكاء.\n\nالليل يدوم 60 ثانية فقط، بعدها يأتي النهار تلقائيا.\n\nماذا يحدث في النهار:\nعندما تتغير الخلفية إلى صورة النهار المشرقة وتتغير الكلمة إلى day، نحن في النهار.\n1- الدردشة: يمكنك كتابة رسالة واحدة فقط! اذا كتبت رسالة جديدة ستمسح القديمة. هذا مقصود لزيادة الغموض. اذا كنت silenced لن تستطيع الكتابة.\n2- التصويت: اختر الشخص الذي تشك أنه من المافيا واضغط تصويت. انتبه: صوت الـ mayor يحسب بصوتين لأنه العمدة.\n3- بعد انتهاء وقت التصويت، الشخص الذي حصل على أكثر الأصوات يموت ويخرج من اللعبة.\n\nماذا يحدث اذا مت:\nاذا تم قتلك ستظهر لك رسالة you are died now you can't do anything just watching وستخرج من الغرفة، يمكنك فقط المشاهدة بعدها.\n\nكيف نفوز:\n- فريق المدينة (mayor و medic و sniper و kid و citizen) يفوز اذا قتل كل أفراد المافيا (boss و mafia و silencer).\n- فريق المافيا يفوز اذا أصبح عددهم مثل أو أكثر من عدد المدينة.\n\nملاحظة مهمة: لا تثق بأحد، حتى صديقك قد يكون هو الـ boss!"
                color: "#ffffff"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
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


            onClicked: rules1.StackView.view.pop()
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
