#include <QFile>
#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    m_fileReader = new FileReader();
    connect(m_fileReader, &FileReader::outTextReady, this, &MainWindow::outTextReady);
    connect(this, &MainWindow::processinfFile, m_fileReader, &FileReader::wordEntry);
    m_thread = new QThread(this);
    connect(this, SIGNAL(destroyed()), m_thread, SLOT(quit()));
    m_fileReader->moveToThread(m_thread);
    m_thread->start();
}

MainWindow::~MainWindow()
{
    delete m_fileReader;
    delete m_thread;
}

void MainWindow::setFilePath(QString filePath)
{
    m_filePath = filePath;
}

void MainWindow::start()
{
    emit clearHistogram();
    if(!checkFilePath(m_filePath))
    {
        emit fileError("Не задан файл.");
        return;
    }
    emit processinfFile(m_filePath);
}

QString MainWindow::fixFilePath(QString filePath)
{
    QRegExp val("file:///");
    QString newStr = filePath.replace(val, QString(""));
    return newStr;
}

bool MainWindow::checkFilePath(QString& filePath)
{
    if(filePath.isEmpty())
        return false;

    QFile file(filePath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return false;

    return true;
}

