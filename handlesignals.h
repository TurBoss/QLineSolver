#ifndef HANDLESIGNALS_H
#define HANDLESIGNALS_H

#include <QObject>
#include <QDebug>

class HandleSignals : public QObject
{
    Q_OBJECT

public slots:
    void runSlot(QString in);

};

#endif // HANDLESIGNALS_H
