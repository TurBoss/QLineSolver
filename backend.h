#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString fileName();

    void setFileName(const QString &fileName);

signals:
    void fileNameChanged();

private:
    QString m_fileName;
};

#endif // BACKEND_H
