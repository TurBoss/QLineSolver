// This file is part of QLineSolver
// Copyright 2019 Metal and TurBoss

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>

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
                     &handleSignals, SLOT(runSlot(QString))
                     );

    QObject::connect(&engine, &QQmlApplicationEngine::quit,
                     &app, &QGuiApplication::quit
                     );

    return app.exec();
}
