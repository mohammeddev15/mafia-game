#include "backend.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>

Backend::Backend(QObject *parent) : QObject(parent) {
    net = new QNetworkAccessManager(this);
    refreshTimer = new QTimer(this);
    refreshTimer->setInterval(5000);
    connect(refreshTimer, &QTimer::timeout, this, [this](){ refreshPlayers(); });

    refreshTimer1 = new QTimer(this);
    refreshTimer1->setInterval(1000);
    connect(refreshTimer1, &QTimer::timeout, this, [this](){ night(); });

}


QVector<QString>  Backend::color() const {
    return m_color;
}

QVector<QString>Backend::image()const{
    return m_image;
}

QString Backend::players() const{
    return m_players;
}
QString Backend::room1() const{
    return m_room1;
}
QString Backend::msg() const{
    return m_msg;
}
QString Backend::my_role() const{
    return m_my_role;
}
int Backend::count() const{
    return m_count;
}
int Backend::mycount() const{
    return m_mycount;
}
int Backend::time() const{
    return m_time;
}

QString Backend::count_image() const{
    return m_count_image;
}

QString Backend::dayornight () const{
    return m_dayornight;
}
QString Backend::myBox2txt () const{
    return m_myBox2txt;
}
QString Backend::myBox2ui () const{
    return m_myBox2ui;
}
QString Backend::startBoxtxt () const{
    return m_startBoxtxt;
}
QString Backend::background_image () const{
    return m_background_image;
}
QString Backend::startBox1txt () const{
    return m_startBox1txt;
}
QString Backend::role_of_another () const{
    return m_role_of_another;
}
QString Backend::note()const{
    return m_note;
}
QString Backend::your_mafia_team ()const{
    return m_your_mafia_team;
}
int Backend::started()const{
    return m_started;
}





void Backend::changeColor(int index,QString new_color){
    m_color[index]= new_color;
    emit colorChanged();
}







void Backend::lougin(QString room, QString name){
    auto *r1 = net->get(QNetworkRequest(QUrl(base + room + "/started.json")));
    connect(r1, &QNetworkReply::finished, this, [=](){
        if(r1->error() == QNetworkReply::NoError){
            m_started = r1->readAll().toInt();
            emit startedChanged();

            if(m_started == 1){
                m_note = "Game already started! You can't join.";
                emit noteChanged();
                r1->deleteLater();
                return; // منع الدخول
            }




            room2 = room;
            name2 = name;
            if(refreshTimer->isActive()) refreshTimer->stop();
            refreshTimer->start(); // بدا التايمر هنا مباشرة
            qDebug() << "Timer STARTED for room:" << room2;

            auto *reply = net->get(QNetworkRequest(QUrl(base + room + "/count.json")));
            connect(reply, &QNetworkReply::finished, this, [=](){

                if(reply->error() == QNetworkReply::NoError){
                    int data = reply->readAll().toInt();
                    int myorder = data + 1;
                    m_count=myorder;
                    m_mycount=myorder;
                    emit mycountChanged();
                    emit countChanged();

                    QJsonObject o{{"name", name},{"count", myorder}};
                    QJsonDocument doc(o);

                    // 1 - إرسال اللاعب
                    QNetworkRequest req1(QUrl(base + room + "/players/" + QUrl::toPercentEncoding(name) + ".json"));
                    req1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                    auto *putPlayer = net->put(req1, doc.toJson());

                    connect(putPlayer, &QNetworkReply::finished, this, [=](){
                        if(putPlayer->error() != QNetworkReply::NoError){
                            qDebug() << "PUT player error:" << putPlayer->errorString() << putPlayer->readAll();
                        } else {
                            qDebug() << "Player added OK";

                            // 2 - من بعد ما تزاد اللاعب، عاد زيد الـ count
                            QNetworkRequest req2(QUrl(base + room + "/count.json"));
                            req2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                            auto *putCount = net->put(req2, QByteArray::number(myorder));
                            connect(putCount, &QNetworkReply::finished, this, [=](){
                                if(putCount->error() != QNetworkReply::NoError){
                                    qDebug() << "PUT count error:" << putCount->errorString();
                                }
                                putCount->deleteLater();
                            });
                        }
                        putPlayer->deleteLater();

                        // 3 - قراءة اللاعبين
                        auto *reply1 = net->get(QNetworkRequest(QUrl(base + room + "/players.json?shallow=true")));
                        connect(reply1, &QNetworkReply::finished, this, [=](){
                            if(reply1->error() == QNetworkReply::NoError){
                                QJsonDocument doc = QJsonDocument::fromJson(reply1->readAll());
                                if(doc.isObject()){
                                    // الى درتي shallow=true المفاتيح هوما السميات نيشان
                                    QStringList names = doc.object().keys();
                                    m_players = names.join("\n"); // دابا غتولي "amin, sara"
                                    emit playersChanged();
                                }






                            }
                            reply1->deleteLater();
                        });
                    });

                } else {
                    qDebug() << "GET count error:" << reply->errorString();
                }

                reply->deleteLater();
            });







        }
        r1->deleteLater();
    });

}







void Backend::refreshPlayers(){
    qDebug() << "tick" << room2;
    if(room2.isEmpty()) return;

    auto *r = net->get(QNetworkRequest(QUrl(base + room2 + "/players.json?shallow=true")));
    connect(r, &QNetworkReply::finished, this, [=](){
        if(r->error() == QNetworkReply::NoError){
            QJsonDocument doc = QJsonDocument::fromJson(r->readAll());
            if(doc.isObject()){

                QStringList names = doc.object().keys();
                m_players = names.join("\n");
                emit playersChanged();
            }

        }
        r->deleteLater();
    });


    auto *r1 = net->get(QNetworkRequest(QUrl(base + room2 + "/count.json")));
    connect(r1, &QNetworkReply::finished, this, [=](){
        if(r1->error() == QNetworkReply::NoError){
            m_count = r1->readAll().toInt();
            emit countChanged();

        }
        r1->deleteLater();
    });



    auto *r2 = net->get(QNetworkRequest(QUrl(base + room2 + "/chat.json")));
    connect(r2, &QNetworkReply::finished, this, [=](){
        if(r2->error() == QNetworkReply::NoError){
            QJsonDocument doc = QJsonDocument::fromJson(r2->readAll());
            QJsonObject obj = doc.object();
            QStringList chatList;
            for(auto key : obj.keys()){
                QJsonObject m = obj[key].toObject();
                chatList << m["name"].toString() + ": " + m["message"].toString();
            }
            m_msg = chatList.join("\n"); // "amin: سلام \n sara: ماشي انا"
            emit msgChanged();

        }
        r2->deleteLater();
    });


    auto *r3 = net->get(QNetworkRequest(QUrl(base + room2 + "/roles/"+name2+".json")));
    connect(r3, &QNetworkReply::finished, this, [=](){
        if(r3->error() == QNetworkReply::NoError){
            m_my_role = QString::fromUtf8(r3->readAll()).replace("\"","");
            emit my_roleChanged();
            if(m_my_role=="silencer"){
                m_count_image=m_image[9];
                emit count_imageChanged();
            }else if(m_my_role=="boss"){
                m_count_image=m_image[1];
                emit count_imageChanged();
            }else if(m_my_role=="mayor"){
                m_count_image=m_image[6];
                emit count_imageChanged();
            }else if(m_my_role=="sniper"){
                m_count_image=m_image[3];
                emit count_imageChanged();
            }else if(m_my_role=="medic"){
                m_count_image=m_image[0];
                emit count_imageChanged();
            }else if(m_my_role=="kid"){
                m_count_image=m_image[4];
                emit count_imageChanged();
            }else if(m_my_role=="mafia"){
                m_count_image=m_image[7];
                emit count_imageChanged();
            }else if(m_my_role=="citizen"){
                m_count_image=m_image[2];
                emit count_imageChanged();
            }

        }
        r3->deleteLater();
    });



    auto *r4 = net->get(QNetworkRequest(QUrl(base + room2 + "/isNight.json")));
    connect(r4, &QNetworkReply::finished, this, [=](){
        if(r4->error() == QNetworkReply::NoError){
            isNight = r4->readAll().toInt();

            if(isNight==1){
                changetonight();
                mafia_team();
            }else{
                changetoday();
            }

        }
        r4->deleteLater();
    });





    auto *r5 = net->get(QNetworkRequest(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(name2) + ".json")));
    connect(r5, &QNetworkReply::finished, this, [=](){
        if(r5->error() == QNetworkReply::NoError){
            QString killed = QString::fromUtf8(r5->readAll()).replace("\"","");

            if(killed=="true"){
                m_note="you are died now , you can't do anything just watching";
                emit noteChanged();
                lougout();
            }
        }
        r5->deleteLater();
    });





    auto *r6 = net->get(QNetworkRequest(QUrl(base + room2 +"/players/"+QUrl::toPercentEncoding(name2)+ "/count.json")));
    connect(r6, &QNetworkReply::finished, this, [=](){
        if(r6->error() == QNetworkReply::NoError){
            m_mycount = r6->readAll().toInt();
            emit mycountChanged();

        }
        r6->deleteLater();
    });
}









void Backend::lougout (){
    auto *reply2 = net->get(QNetworkRequest(QUrl(base + room2 +  "/count.json")));
    refreshTimer->stop();
    connect(reply2, &QNetworkReply::finished, this, [=](){
        int data = reply2->readAll().toInt();
        int myorder = data-1;
        m_count=myorder;
        emit countChanged();


        auto *pc = net->put(QNetworkRequest(QUrl(base + room2 + "/count.json")), QByteArray::number(myorder));
        connect(pc, &QNetworkReply::finished, this, [=](){ pc->deleteLater(); });

        auto *del = net->deleteResource(QNetworkRequest(QUrl(base + room2 + "/players/"+ QUrl::toPercentEncoding(name2) +".json")));
        connect(del, &QNetworkReply::finished, this, [=](){ del->deleteLater(); });

        m_count=0;
        emit countChanged();


        reply2->deleteLater();

    });

}






// INTENTIONAL DESIGN - NOT A BUG: Single-Message Chat System
// Each player is limited to ONE active message. Sending a new message
// overwrites the previous one at /chat/{playerName}.json
// Purpose: To increase mystery and prevent players from reviewing history
// to identify the Mafia by speech patterns. Real-time discussion only.
void Backend::sendmsg(QString my_msg){

    auto *r3 = net->get(QNetworkRequest(QUrl(base + room2 + "/nightState/silenced/"+QUrl::toPercentEncoding(name2)+".json")));
    connect(r3, &QNetworkReply::finished, this, [=](){
        if(r3->error() == QNetworkReply::NoError){
            QString silenced;
            silenced  = QString::fromUtf8(r3->readAll()).replace("\"","");

            if(silenced=="true"){
                m_note="you can't send anymessage , you are silenced .";
                emit noteChanged();
            }

            if(silenced!="true"){
                auto *r5 = net->get(QNetworkRequest(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(name2) + ".json")));
                connect(r5, &QNetworkReply::finished, this, [=](){
                    if(r5->error() == QNetworkReply::NoError){
                        QString killed = QString::fromUtf8(r5->readAll()).replace("\"","");

                        if(killed!="true"){
                            QJsonObject o{{"name", name2},{"message", my_msg}};
                            QJsonDocument doc(o);

                            // 1 - إرسال اللاعب
                            QNetworkRequest req1(QUrl(base + room2 + "/chat/" + QUrl::toPercentEncoding(name2) + ".json"));
                            req1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                            auto *putmsg = net->put(req1, doc.toJson());

                            connect(putmsg, &QNetworkReply::finished, this, [=](){
                                if(putmsg->error() != QNetworkReply::NoError){
                                    qDebug() << "PUT player error:" << putmsg->errorString() << putmsg->readAll();
                                };
                                putmsg->deleteLater();
                            });
                        }
                    }
                    r5->deleteLater();
                });


            }

        }
        r3->deleteLater();
    });


}









void Backend::distributeRoles(){

    if(m_mycount!= 1) return;

    if(m_count < 8) return;

    if(rolesDistributed) return;



    QVector<QString> rare = {
        "silencer", "boss", "mayor",
        "sniper", "medic", "kid"
    };
    QVector<QString> roles = rare;
    roles << "mafia" << "citizen";

    int extra = m_count - 8;
    for(int i=0; i<extra; i++){
        int r = QRandomGenerator::global()->bounded(100);
        roles << (r < 40? "mafia" : "citizen");
    }

    std::shuffle(roles.begin(), roles.end(), std::mt19937(QRandomGenerator::global()->generate()));


    QStringList names = m_players.split("\n");
    std::shuffle(names.begin(), names.end(), std::mt19937(QRandomGenerator::global()->generate()));


    QJsonObject obj;
    for(int i=0; i<names.size() && i<roles.size(); i++){
        obj[names[i]] = roles[i];
    }

    QNetworkRequest req(QUrl(base + room2 + "/roles.json"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto *putrules = net->put(req, QJsonDocument(obj).toJson());

    connect(putrules, &QNetworkReply::finished, this, [=](){
        if(putrules->error() != QNetworkReply::NoError){
            qDebug() << "PUT player error:" << putrules->errorString() << putrules->readAll();
        } else {
            qDebug() << "distributeroles is good";
            rolesDistributed = true;
            if(refreshTimer1->isActive()) refreshTimer1->stop();
            refreshTimer1->start();
            m_time=60;
            emit timeChanged();
            m_started=1;
            emit startedChanged();
            QNetworkRequest req2(QUrl(base + room2 + "/started.json"));
            req2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            auto *putCount = net->put(req2, QByteArray::number(m_started));
            connect(putCount, &QNetworkReply::finished, this, [=](){
                if(putCount->error() != QNetworkReply::NoError){
                    qDebug() << "PUT count error:" << putCount->errorString();
                }
                putCount->deleteLater();
            });

        };
        putrules->deleteLater();

    });

}








void Backend::savevote(QString vote_from_ui){

    the_vote=vote_from_ui;

}


void Backend ::sendvote(){
    auto *r5 = net->get(QNetworkRequest(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(name2) + ".json")));
    connect(r5, &QNetworkReply::finished, this, [=](){
        if(r5->error() == QNetworkReply::NoError){
            QString killed = QString::fromUtf8(r5->readAll()).replace("\"","");

            if(killed!="true"){
                auto *reply = net->get(QNetworkRequest(QUrl(base + room2 + "/votes/"+QUrl::toPercentEncoding(the_vote) + ".json")));
                connect(reply, &QNetworkReply::finished, this, [=](){

                    if(reply->error() == QNetworkReply::NoError){
                        QByteArray raw = reply->readAll();
                        int data = 0;
                        if(raw != "null") data = raw.toInt();
                        int myvote;
                        if(m_my_role=="mayor"){
                            myvote = data + 2;
                        }else{
                            myvote = data + 1;
                        }





                        QNetworkRequest req2(QUrl(base + room2 + "/votes/"+QUrl::toPercentEncoding(the_vote) + ".json"));
                        req2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                        auto *putCount = net->put(req2, QByteArray::number(myvote));
                        connect(putCount, &QNetworkReply::finished, this, [=](){
                            if(putCount->error() != QNetworkReply::NoError){
                                qDebug() << "PUT count error:" << putCount->errorString();
                            }
                            putCount->deleteLater();
                        });
                    }
                    reply->deleteLater();
                });
            }
        }
        r5->deleteLater();
    });




}



void Backend::calcule_votes(){

    QStringList names = m_players.split("\n");

    auto maxVotes = QSharedPointer<int>::create(-1);

    auto indexToKill = QSharedPointer<int>::create(0);

    auto end_get = QSharedPointer<int>::create(names.size());

    for(int i=0; i<names.size(); i++){
        auto *r1 = net->get(QNetworkRequest(QUrl(base + room2 + "/votes/"+QUrl::toPercentEncoding(names[i])+".json")));
        connect(r1, &QNetworkReply::finished, this, [=](){
            if(r1->error() == QNetworkReply::NoError){
                int vote = r1->readAll().toInt();

                if (vote>*maxVotes){
                    (*maxVotes)=vote;
                    (*indexToKill)=i;
                }
            }
            (*end_get)--;
            if(*end_get==0){
                QNetworkRequest req(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(names[*indexToKill]) + ".json"));
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                auto *putPlayer = net->put(req, QByteArray("true"));

                connect(putPlayer, &QNetworkReply::finished, this, [=](){
                    if(putPlayer->error() != QNetworkReply::NoError){
                        qDebug() << "error" << putPlayer->errorString() << putPlayer->readAll();
                    }
                    checkWin();
                    auto *del = net->deleteResource(QNetworkRequest(QUrl(base + room2 + "/votes.json")));
                    connect(del, &QNetworkReply::finished, this, [=](){ del->deleteLater(); });

                    putPlayer->deleteLater();
                });
            }


            r1->deleteLater();

        });

    }




}






void Backend ::changisnight(){
    isNight=1;
    m_time=60;

    QNetworkRequest req2(QUrl(base + room2 + "/isNight.json"));
    req2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto *putCount = net->put(req2, QByteArray::number(isNight));
    connect(putCount, &QNetworkReply::finished, this, [=](){
        if(putCount->error() != QNetworkReply::NoError){
            qDebug() << "PUT count error:" << putCount->errorString();
        }
        calcule_votes();
        putCount->deleteLater();
    });
}






void Backend ::night(){
    if(isNight == 0) return;
    m_time-=1;
    emit timeChanged();
    if(m_time==0){
        m_time=60;
        if(isNight==1){
            isNight=0;
            us_your_role_one=1;
            m_note="";
            emit noteChanged();
            QNetworkRequest req2(QUrl(base + room2 + "/isNight.json"));
            req2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            auto *putCount = net->put(req2, QByteArray::number(isNight));
            connect(putCount, &QNetworkReply::finished, this, [=](){
                if(putCount->error() != QNetworkReply::NoError){
                    qDebug() << "PUT count error:" << putCount->errorString();

                }
                checkWin();
                auto *del = net->deleteResource(QNetworkRequest(QUrl(base + room2 + "/nightState.json")));
                connect(del, &QNetworkReply::finished, this, [=](){ del->deleteLater(); });
                putCount->deleteLater();

            });

        }
    };
}






void Backend :: changetonight(){

    //here we have change ui to night
    m_dayornight="night";
    emit dayornightChanged();
    //m_color[9]="#0d0f57eb";
    //emit colorChanged();
    m_myBox2txt="us role";
    emit myBox2txtChanged();
    m_myBox2ui="us_role.qml";
    emit myBox2uiChanged();
    m_background_image="images/image_20261001_081748.jpg";
    emit background_imageChanged();

}



void Backend ::changetoday(){
    //here change ui to day

    m_dayornight="day";
    emit dayornightChanged();
    //m_color[9]="#1c20b7eb";
    //emit colorChanged();
    m_myBox2txt="vote";
    emit myBox2txtChanged();
    m_myBox2ui="vote.qml";
    emit myBox2uiChanged();
    m_background_image="images/day.jpg";
    emit background_imageChanged();

}






void Backend:: start_fonction_of_your_role(){
    if(us_your_role_one == 0) return;
    us_your_role_one--;
    auto *r5 = net->get(QNetworkRequest(QUrl(base + room2 + "/nightState/blocked/"+QUrl::toPercentEncoding(name2)+".json")));
    connect(r5, &QNetworkReply::finished, this, [=](){
        if(r5->error() == QNetworkReply::NoError){
            QString blocked;
            blocked  = QString::fromUtf8(r5->readAll()).replace("\"","");

            if (blocked=="true"){
                m_note="you can't us your role because you are blocked by mafia this night";
                emit noteChanged();
            }

            if(blocked == "true") return;

            if(m_my_role=="silencer"){
                //here you can find code of role in the combition
                QNetworkRequest req(QUrl(base + room2 + "/nightState/silenced/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                auto *putPlayer = net->put(req, QByteArray("true"));

                connect(putPlayer, &QNetworkReply::finished, this, [=](){
                    if(putPlayer->error() != QNetworkReply::NoError){
                        qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                    }
                    putPlayer->deleteLater();
                });
            }else if(m_my_role=="boss"){
                //here you can find code of role in the combition
                auto *r3 = net->get(QNetworkRequest(QUrl(base + room2 + "/nightState/saved/"+QUrl::toPercentEncoding(the_vote)+".json")));
                connect(r3, &QNetworkReply::finished, this, [=](){
                    if(r3->error() == QNetworkReply::NoError){
                        QString saved;
                        saved  = QString::fromUtf8(r3->readAll()).replace("\"","");

                        if (saved=="true"){
                            m_note="this one is saved";
                            emit noteChanged();
                        }

                        if(saved!="true"){

                            QNetworkRequest req(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                            req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                            auto *putPlayer = net->put(req, QByteArray("true"));

                            connect(putPlayer, &QNetworkReply::finished, this, [=](){
                                if(putPlayer->error() != QNetworkReply::NoError){
                                    qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                                }
                                putPlayer->deleteLater();

                            });
                        }

                    }
                    r3->deleteLater();
                });

            }else if(m_my_role=="mayor"){
                //here you can find code of role in the combition
            }else if(m_my_role=="sniper"){

                auto *r3 = net->get(QNetworkRequest(QUrl(base + room2 + "/roles/"+QUrl::toPercentEncoding(the_vote)+".json")));
                connect(r3, &QNetworkReply::finished, this, [=](){
                    if(r3->error() == QNetworkReply::NoError){
                        m_role_of_another= QString::fromUtf8(r3->readAll()).replace("\"","");
                        emit role_of_anotherChanged();


                        if(m_role_of_another!="boss"&&m_role_of_another!="silencer"&&m_role_of_another!="mafia"){
                            QNetworkRequest req(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                            req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                            auto *putPlayer = net->put(req, QByteArray("true"));

                            connect(putPlayer, &QNetworkReply::finished, this, [=](){
                                if(putPlayer->error() == QNetworkReply::NoError){
                                    QNetworkRequest req1(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(name2)+ ".json"));
                                    req1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                                    auto *putPlayer = net->put(req1, QByteArray("true"));

                                    connect(putPlayer, &QNetworkReply::finished, this, [=](){
                                        if(putPlayer->error() != QNetworkReply::NoError){
                                            qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                                        }
                                        putPlayer->deleteLater();
                                    });

                                }
                                putPlayer->deleteLater();
                            });
                            m_note="he dont was from the mafia now you are die";
                            emit noteChanged();
                        }else {
                            QNetworkRequest req(QUrl(base + room2 + "/killed/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                            req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                            auto *putPlayer = net->put(req, QByteArray("true"));

                            connect(putPlayer, &QNetworkReply::finished, this, [=](){
                                if(putPlayer->error() != QNetworkReply::NoError){
                                    qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                                }
                                putPlayer->deleteLater();
                            });
                        }

                    }
                    r3->deleteLater();
                });

                //here you can find code of role in the combition
            }else if(m_my_role=="medic"){
                //here you can find code of role in the combition
                QNetworkRequest req(QUrl(base + room2 + "/nightState/saved/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                auto *putPlayer = net->put(req, QByteArray("true"));

                connect(putPlayer, &QNetworkReply::finished, this, [=](){
                    if(putPlayer->error() != QNetworkReply::NoError){
                        qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                    }
                    putPlayer->deleteLater();
                });
            }else if(m_my_role=="kid"){
                //here you can find code of role in the combition
                auto *r3 = net->get(QNetworkRequest(QUrl(base + room2 + "/roles/"+QUrl::toPercentEncoding(the_vote)+".json")));
                connect(r3, &QNetworkReply::finished, this, [=](){
                    if(r3->error() == QNetworkReply::NoError){
                        m_role_of_another = QString::fromUtf8(r3->readAll()).replace("\"","");
                        emit role_of_anotherChanged();
                        m_note="this is a "+m_role_of_another;
                        emit noteChanged();

                    }
                    r3->deleteLater();
                });
            }else if(m_my_role=="mafia"){
                //here you can find code of role in the combition
                QNetworkRequest req(QUrl(base + room2 + "/nightState/blocked/" + QUrl::toPercentEncoding(the_vote) + ".json"));
                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                auto *putPlayer = net->put(req, QByteArray("true"));

                connect(putPlayer, &QNetworkReply::finished, this, [=](){
                    if(putPlayer->error() != QNetworkReply::NoError){
                        qDebug() << "PUT silenced error:" << putPlayer->errorString() << putPlayer->readAll();
                    }
                    putPlayer->deleteLater();
                });
            }else if(m_my_role=="citizen"){
                //here you can find code of role in the combition
                m_note="hey you dont have anyrole here wait to the voteing";
                emit noteChanged();
            }

        }
        r5->deleteLater();
    });



}






void Backend::checkWin(){
    if(room2.isEmpty()) return;

    auto *rRoles = net->get(QNetworkRequest(QUrl(base + room2 + "/roles.json")));
    connect(rRoles, &QNetworkReply::finished, this, [=](){
        if(rRoles->error() != QNetworkReply::NoError){ rRoles->deleteLater(); return; }

        QJsonObject rolesObj = QJsonDocument::fromJson(rRoles->readAll()).object();
        rRoles->deleteLater();

        auto *rKilled = net->get(QNetworkRequest(QUrl(base + room2 + "/killed.json")));
        connect(rKilled, &QNetworkReply::finished, this, [=](){
            if(rKilled->error() != QNetworkReply::NoError){ rKilled->deleteLater(); return; }

            QJsonObject killedObj = QJsonDocument::fromJson(rKilled->readAll()).object();
            rKilled->deleteLater();

            int aliveMafia = 0;
            int aliveCity = 0;

            for(auto it = rolesObj.begin(); it != rolesObj.end(); ++it){
                QString playerName = it.key();
                QString role = it.value().toString();
                QJsonValue v = killedObj.value(playerName);
                bool isDead = (v.isString() && v.toString()=="true") || (v.isBool() && v.toBool());
                if(isDead) continue;

                if(role=="boss" || role=="mafia" || role=="silencer"){
                    aliveMafia++;
                }else{
                    aliveCity++;
                }
            }

            if(aliveMafia == 0 && aliveCity > 0){
                m_note = "the city team wins!";
                emit noteChanged();
                refreshTimer->stop();
                refreshTimer1->stop();
                m_myBox2txt = "City Wins!";
                emit myBox2txtChanged();
                m_myBox2ui="";
                emit myBox2uiChanged();
            }
            else if(aliveMafia >= aliveCity && aliveMafia > 0){
                m_note = "the mafia team wins!";
                emit noteChanged();
                refreshTimer->stop();
                refreshTimer1->stop();
                m_myBox2txt = "Mafia Wins!";
                emit myBox2txtChanged();
                m_myBox2ui="";
                emit myBox2uiChanged();
            }
        });
    });
}






void Backend::mafia_team(){
    if(m_my_role=="boss" || m_my_role=="mafia" || m_my_role=="silencer"){
        m_your_mafia_team="";
        emit your_mafia_teamChanged();
        auto *rRoles = net->get(QNetworkRequest(QUrl(base + room2 + "/roles.json")));
        connect(rRoles, &QNetworkReply::finished, this, [=](){
            if(rRoles->error() != QNetworkReply::NoError){ rRoles->deleteLater(); return; }

            QJsonObject rolesObj = QJsonDocument::fromJson(rRoles->readAll()).object();
            rRoles->deleteLater();
            for(auto it = rolesObj.begin(); it != rolesObj.end(); ++it){
                QString playerName = it.key();
                QString role = it.value().toString();

                if(role=="boss" || role=="mafia" || role=="silencer"){
                    m_your_mafia_team=m_your_mafia_team+playerName+",";

                }


            }

            m_your_mafia_team=m_your_mafia_team+"are your team!";
            emit your_mafia_teamChanged();
        });




    }


}
