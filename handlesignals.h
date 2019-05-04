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

#ifndef HANDLESIGNALS_H
#define HANDLESIGNALS_H

#include <QObject>
#include <QDebug>

class HandleSignals : public QObject
{
    Q_OBJECT

signals:
    void setViewer(QVariant cpx, QVariant cpy, QVariant cpz);
    void setViewer2(QVariant text);

public slots:
    void runSlot(QString in);

};

#endif // HANDLESIGNALS_H
