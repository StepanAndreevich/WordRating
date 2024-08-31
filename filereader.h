#pragma once
#include <QObject>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);

public slots:
    void wordEntry(const QString& filePath);

signals:
    void outTextReady(QString outText);

private:
    QString readFile(const QString& filePath);
    QString m_filePath = "";

};
