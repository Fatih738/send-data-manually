#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQuickItem>
#include <QQuickView>

#include <QTimer>
#include "wiringPi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>


QObject *itemTemp = NULL;

QObject *itemH = NULL;

double val=0;
int update(){
    val++;
    if(itemH)
        itemH->setProperty("text",QString().setNum(val,'f',1));
    //QString::number((m_Speed/40),'g',3));
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    itemTemp = engine.rootObjects().at(0)->findChild<QQuickItem*>("temp");
    itemH = engine.rootObjects().at(0)->findChild<QQuickItem*>("hum");//hum qml dosyasında kullandığımız obje ismi


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout,update);
    timer.start(2000);//iki saniyede bir update çalışır

    return app.exec();
}
