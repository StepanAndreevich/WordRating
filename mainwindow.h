#pragma once
#include <QObject>
#include <QThread>
#include <QVariant>
#include <QVariantList>
#include "filereader.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);
    ~MainWindow();

    Q_INVOKABLE void setFilePath(QString filePath);
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE QString fixFilePath(QString filePath);

signals:
    void fileError(QString errorText);
    void outTextReady(QString outText);
    void processinfFile(QString filePath);
    void resultReady(QStringList wordList, QVariantList entriesList);
    void changeProgress(double value);

private:
    bool checkFilePath(QString& filePath);
    QString m_filePath = "";
    QThread* m_thread = nullptr;
    FileReader* m_fileReader = nullptr;
};

