#pragma once
#include <QObject>
#include <QThread>
#include <QVariant>
#include <QVariantList>
#include "filereader.h"

/*!
 * \brief The MainWindow class класс взаимодействия с графическим интерфейсом
 */
class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);
    ~MainWindow();

    /*!
     * \brief setFilePath Задать путь к файлу
     * \param filePath
     */
    Q_INVOKABLE void setFilePath(QString filePath);
    /*!
     * \brief start запуск обработки файла
     */
    Q_INVOKABLE void start();
    /*!
     * \brief stop остановка обработки файла
     */
    Q_INVOKABLE void stop();
    /*!
     * \brief fixFilePath очистить строку от лишних символов
     * \param filePath путь к выбранному файлу
     * \return
     */
    Q_INVOKABLE QString fixFilePath(QString filePath);

signals:
    /*!
     * \brief fileError
     * \param errorText текст ошибки
     */
    void fileError(QString errorText);
    /*!
     * \brief processinfFile начало обработки файла
     * \param filePath путь к файлу
     */
    void processinfFile(QString filePath);
    /*!
     * \brief resultReady подготовленные данные отправляемые в qml
     * \param wordList список слов
     * \param entriesList количество вхождений
     */
    void resultReady(QStringList wordList, QVariantList entriesList);
    /*!
     * \brief changeProgress сигнал изменения прогресс бара
     * \param value процент заполнения прогресс бара
     */
    void changeProgress(double value);
    /*!
     * \brief finished сигнал о завершении обработки файла
     */
    void finished();

private:
    /*!
     * \brief checkFilePath проверка файла
     * \param filePath путь к файлу
     * \return true - с файлом все хорошо / false - с файлом проблемы
     */
    bool checkFilePath(QString& filePath);
    QString m_filePath = "";
    QThread* m_thread = nullptr;
    FileReader* m_fileReader = nullptr;
};

