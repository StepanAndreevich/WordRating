#include <QFile>
#include <QSet>
#include <QMap>
#include "filereader.h"

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

    QStringList words = QString(newStr).split(" ");
    QSet<QString> uniqueWords;
    QMap<QString, int> wordCounter;
    for(const auto& word : words)
    {
        if(uniqueWords.contains(word))
        {
            auto count = wordCounter.value(word);
            wordCounter.insert(word, ++count);
        }
        else
        {
            if(word.contains(" ") || word.contains("\n"))
                continue;
            wordCounter.insert(word, 1);
        }
        uniqueWords.insert(word);
    }

    QMultiMap<int, QString> reversWordCount; //Получаем отсортированные слова по количеству вхождений
    for(const auto& word : wordCounter.keys())
    {
        auto val = wordCounter.value(word);
        reversWordCount.insert(val, word);
    }

    //auto wordCountSize = reversWordCount.size();


    QString outText;
    for(const auto& word: wordCounter.keys())
    {
        auto count = wordCounter.value(word);
        QString text = QString("%1 : %2 \n").arg(word).arg(count);
        outText.append(text);
    }
    emit outTextReady(outText);
}

