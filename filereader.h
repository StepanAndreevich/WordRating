#pragma once
#include <QObject>
#include <QVariant>
#include <QVariantList>

/*!
 * \brief The FileReader class класс работы с файлом(чтение и подсчет слов)
 */
class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);

public slots:
    void wordEntry(const QString& filePath);

signals:
    void outTextReady(QString outText);
    void resultReady(QStringList wordList, QVariantList entriesList);

private:
    /*!
     * \brief readFile Чтение файла
     * \param filePath путь к файлу
     * \return
     */
    QString readFile(const QString& filePath);
    /*!
     * \brief countEntries Определение частоты встречаемости слова в тексте
     * \param words список все слов в файле
     * \return QMap слово на его количество в тексте
     */
    QMap<QString, int> countEntries(QStringList words);
    /*!
     * \brief sortByEntriesCounting Сортировка слов по количеству входжений
     * \param wordCounter
     * \return
     */
    QMultiMap<int, QString> sortByEntriesCounting(QMap<QString, int> wordCounter);
    /*!
     * \brief topOfWords Находжение топ-15 слов по количеству вхождений
     * \param wordCounter отсортированный, по кол-ву вхождений, QMap слов
     * \return топ-15 слов
     */
    QMultiMap<QString, int> topOfWords(QMultiMap<int, QString> wordCounter);
    /*!
     * \brief m_filePath абсольтный путь к открытому файлу
     */
    QString m_filePath = "";
};
