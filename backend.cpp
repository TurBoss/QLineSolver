#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

QString BackEnd::fileName()
{
    return m_fileName;
}

void BackEnd::setFileName(const QString &fileName)
{
    if (fileName == m_fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged();
}
