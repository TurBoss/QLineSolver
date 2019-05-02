#include <iostream>

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "linesolver.h"
#include "handlesignals.h"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlEngine engine;
    QQmlComponent component(&engine, url);

    QObject *object = component.create();


    HandleSignals handleSignals;

    QObject::connect(object, SIGNAL(runSignal(QString)),
                     &handleSignals, SLOT(runSlot(QString)));
    return app.exec();

}
