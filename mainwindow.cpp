#include <QFile>
#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    m_fileReader = new FileReader();
    m_fileReader->setTopBorder(15);
    connect(m_fileReader, &FileReader::outTextReady, this, &MainWindow::outTextReady);
    connect(m_fileReader, &FileReader::resultReady, this, &MainWindow::resultReady);
    connect(m_fileReader, &FileReader::changeProgress, this, &MainWindow::changeProgress);
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
    if(!m_thread->isRunning())
        m_thread->start();
    if(!checkFilePath(m_filePath))
    {
        emit fileError("Не задан файл.");
        return;
    }
    emit processinfFile(m_filePath);
}

void MainWindow::stop()
{
    m_thread->terminate();
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

