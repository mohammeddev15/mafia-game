#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QString> color READ color NOTIFY colorChanged)
    Q_PROPERTY(QVector<QString> image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString players READ players NOTIFY playersChanged)
    Q_PROPERTY(QString room1 READ room1 NOTIFY room1Changed)
    Q_PROPERTY(QString msg READ msg NOTIFY msgChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int mycount READ mycount NOTIFY mycountChanged)
    Q_PROPERTY(int time READ time NOTIFY timeChanged)
    Q_PROPERTY(QString count_image READ count_image NOTIFY count_imageChanged)
    Q_PROPERTY(QString my_role READ my_role NOTIFY my_roleChanged)
    Q_PROPERTY(QString dayornight READ dayornight NOTIFY dayornightChanged)
    Q_PROPERTY(QString myBox2txt READ myBox2txt NOTIFY myBox2txtChanged)
    Q_PROPERTY(QString myBox2ui READ myBox2ui NOTIFY myBox2uiChanged)
    Q_PROPERTY(QString startBoxtxt READ startBoxtxt NOTIFY startBoxtxtChanged)
    Q_PROPERTY(QString background_image READ background_image NOTIFY background_imageChanged)
    Q_PROPERTY(QString startBox1txt READ startBox1txt NOTIFY startBox1txtChanged)
    Q_PROPERTY(QString role_of_another READ role_of_another NOTIFY role_of_anotherChanged)
    Q_PROPERTY(QString note READ note NOTIFY noteChanged)
    Q_PROPERTY(QString your_mafia_team READ your_mafia_team NOTIFY your_mafia_teamChanged)
    Q_PROPERTY(int started READ started NOTIFY startedChanged)




public:
    explicit Backend(QObject *parent = nullptr);
    QVector<QString>color()const;
    QVector<QString>image()const;
    QString  players  () const;
    QString  room1  () const;
    QString  msg  () const;
    QString  my_role  () const;
    QString dayornight () const;
    QString myBox2txt () const;
    QString myBox2ui () const;
    QString startBoxtxt () const;
    QString background_image () const;
    QString startBox1txt () const;
    QString role_of_another () const;
    QString note ()const;
    QString your_mafia_team()const;

    int  time  () const;
    int  count  () const;
    int  mycount  () const;
    int started()const;
    QString  count_image  () const;
    int isNight=0;
    QString base = "https://YOUR-PROJECT.firebaseio.com/";
    QString room2;
    QString name2;
    QString the_vote;
    int us_your_role_one=1;
    bool rolesDistributed = false;
    Q_INVOKABLE void changeColor(int index,QString new_color);
    Q_INVOKABLE void lougin (QString room, QString name);
    Q_INVOKABLE void lougout ();
    Q_INVOKABLE void sendmsg (QString my_msg);
    Q_INVOKABLE void distributeRoles();
    void refreshPlayers();
    void night ();
    void calcule_votes();
    void mafia_team();
    Q_INVOKABLE void savevote(QString vote_from_ui);
    Q_INVOKABLE void sendvote ();
    Q_INVOKABLE void changisnight();
    Q_INVOKABLE void changetonight();
    Q_INVOKABLE void changetoday();
    Q_INVOKABLE void start_fonction_of_your_role( );
    Q_INVOKABLE void checkWin();

signals:
    void colorChanged();
    void imageChanged();
    void playersChanged();
    void room1Changed();
    void msgChanged();
    void countChanged();
    void mycountChanged();
    void timeChanged();
    void my_roleChanged();
    void dayornightChanged ();
    void myBox2txtChanged ();
    void myBox2uiChanged ();
    void startBoxtxtChanged ();
    void background_imageChanged ();
    void startBox1txtChanged ();
    void role_of_anotherChanged ();
    void count_imageChanged ();
    void noteChanged();
    void your_mafia_teamChanged();
    void startedChanged();
private:
    QVector<QString> m_color = {
        "#999999", "#999999", "#999999",
        "#999999", "#999999", "green",
        "green","orange","orange","#272ccfa6"
    };
    QVector<QString> m_image= {"images/735128856_122118382736776700_2754096892861324660_n.jpg",
                                "images/735577286_122118382532776700_2883574024477408815_n.jpg",
                                "images/736053905_122118382844776700_1637321274866886842_n.jpg",
                                "images/736858136_122118382628776700_4273887804627270561_n.jpg",
                                "images/737774558_122118382526776700_1474392633146894410_n.jpg",
                                "images/737819474_122118382802776700_1838107492342197626_n.jpg",
                                "images/738937662_122118382742776700_1428208817051282161_n.jpg",
                                "images/739762701_122118382634776700_629602115043394480_n.jpg",
                                "images/740070516_122118382604776700_9212383590004908530_n.jpg"};
    QString m_players;
    QString m_room1;
    QString m_msg;
    QString m_my_role="wait...";
    int m_count=0;
    int m_mycount;
    int m_time;
    QString m_count_image=m_image[5];
    QNetworkAccessManager *net;
    QTimer *refreshTimer = nullptr;
    QTimer *refreshTimer1 = nullptr;
    QString m_dayornight="wait...";
    QString m_myBox2txt="wait to start game...";
    QString m_myBox2ui="";
    QString m_startBoxtxt="start";
    QString m_background_image="images/day.jpg";
    QString m_startBox1txt="start night";
    QString m_role_of_another;
    QString m_note;
    QString m_your_mafia_team="";
    int m_started=0;


};

#endif // BACKEND_H
