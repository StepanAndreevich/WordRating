#include <QFile>
#include <QSet>
#include <QMap>
#include "filereader.h"
#include <QVariant>
#include <QVariantList>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

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

    auto reversWordCount = sortByEntriesCounting(wordCounter);
    if(reversWordCount.isEmpty())
        return emit outTextReady("Error");

    auto resultWords = topOfWords(reversWordCount);
    if(resultWords.isEmpty())
        return emit outTextReady("Error");

    auto wordsList = resultWords.keys();
    //auto entries = resultWords.values();
    QVariantList entries = {};
    for(const auto& val : resultWords.values())
        entries.append(val);
    emit resultReady(wordsList, entries);

//    QString outText;
//    for(const auto& word: resultWords.keys())
//    {
//        auto count = resultWords.value(word);
//        QString text = QString("%1(%2) \n").arg(word).arg(count);
//        outText.append(text);
//    }
//    emit outTextReady(outText);
}

QMap<QString, int> FileReader::countEntries(QStringList words)
{
    QMap<QString, int> wordCounter = {};
    for(const auto& word : words)
    {
        if(!wordCounter.contains(word))
        {
            wordCounter.insert(word, 1);
        }
        else
        {
            auto count = wordCounter.value(word);
            wordCounter.insert(word, ++count);
        }
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

QMultiMap<QString, int> FileReader::topOfWords(QMultiMap<int, QString> wordCounter)
{
    QMap<int, QString>::iterator begin = 0;
    QMap<int, QString>::iterator end = 0;
    if(wordCounter.size() <= 15)
    {
        begin = wordCounter.end() - 1;
        end = wordCounter.begin();
    }
    else
    {
        begin = wordCounter.end() - 1;
        end = wordCounter.end() - 16;
    }

    QMultiMap<QString, int> resultWords = {};
    for(auto it = begin; it != end; it--)
    {
        auto val = it.key();
        auto key = it.value();
        resultWords.insert(key, val);
    }

    return resultWords;
}

