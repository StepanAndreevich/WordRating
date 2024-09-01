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
    /*!
     * \brief setTopBorder установить границу топа слов
     * \param border
     */
    void setTopBorder(int border);
    int topBorder();

public slots:
    void wordEntry(const QString& filePath);

signals:
    void outTextReady(QString outText);
    void resultReady(QStringList wordList, QVariantList entriesList);
    void changeProgress(double value);

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
    void topOfWords(QMultiMap<int, QString> wordCounter);
    //QMultiMap<QString, int> topOfWords(QMultiMap<int, QString> wordCounter);

    /*!
     * \brief sendData отправляем доанные в qml
     * \param data
     */
    void sendData(QMultiMap<QString, int> data);
    /*!
     * \brief m_filePath абсольтный путь к открытому файлу
     */
    QString m_filePath = "";
    int m_topBorder = 0;
    bool m_pause = false;
};
