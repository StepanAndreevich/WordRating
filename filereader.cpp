#include "filereader.h"
#include <QFile>
#include <QSet>
#include <QMap>
#include <QThread>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

void FileReader::setTopBorder(int border)
{
    m_topBorder = border;
}

int FileReader::topBorder()
{
    return m_topBorder;
}

QString FileReader::readFile(const QString& filePath)
{
    if(filePath.isEmpty())
        return QString();

    QFile file(filePath);
    if(!file.exists())
        return QString();

    if(!file.open(QIODevice::ReadOnly))
        return QString();

    auto fileData = file.readAll();
    return QString(fileData);
}

void FileReader::wordEntry(const QString& filePath)
{
    auto fileData = readFile(filePath);
    QRegExp val("[,.:;!-+=/*@#&$?]"); //Убираем знаки припинания из строки
    QString newStr = fileData.replace(val, QString(""));
    QRegExp tabs("\r\n");
    newStr = newStr.replace(tabs, QString(" "));
    newStr = newStr.trimmed();

    QStringList words = QString(newStr).split(" ");
    auto wordCounter = countEntries(words);
    if(wordCounter.isEmpty())
        return emit outTextReady("Error");
}

QMap<QString, int> FileReader::countEntries(QStringList words)
{
    QMap<QString, int> wordCounter = {};
    double progress = 0;
    double count = 0;
    double allWords = words.count();
    for(const auto& word : words)
    {
        if(!wordCounter.contains(word))
        {
            wordCounter.insert(word, 1);
            auto sortWordCounter = sortByEntriesCounting(wordCounter);
            topOfWords(sortWordCounter);
        }
        else
        {
            auto count = wordCounter.value(word);
            wordCounter.insert(word, ++count);
            auto sortWordCounter = sortByEntriesCounting(wordCounter);
            topOfWords(sortWordCounter);
        }
        ++count;
        progress = count / allWords * 100;
        emit changeProgress(progress);
    }

    return wordCounter;
}

QMultiMap<int, QString> FileReader::sortByEntriesCounting(QMap<QString, int> wordCounter)
{
    QMultiMap<int, QString> reversWordCount = {};
    for(const auto& word : wordCounter.keys())
    {
        auto val = wordCounter.value(word);
        reversWordCount.insert(val, word);
    }
    return reversWordCount;
}

void FileReader::topOfWords(QMultiMap<int, QString> wordCounter)
{
    QMap<int, QString>::iterator begin = 0;
    QMap<int, QString>::iterator end = 0;
    if(topBorder() == 0)
        return;

    if(wordCounter.size() <= topBorder())
    {
        begin = wordCounter.end() - 1;
        end = wordCounter.begin();
    }
    else
    {
        begin = wordCounter.end() - 1;
        end = wordCounter.end() - topBorder() - 1;
    }

    QMultiMap<QString, int> resultWords = {};
    for(auto it = begin; it != end; it--)
    {
        auto val = it.key();
        auto key = it.value();
        resultWords.insert(key, val);
    }
    sendData(resultWords);
}

void FileReader::sendData(QMultiMap<QString, int> data)
{
    auto wordsList = data.keys();
    QVariantList entries = {};
    for(const auto& val : data.values())
        entries.append(val);
    emit resultReady(wordsList, entries);
    QThread::msleep(100);
}

