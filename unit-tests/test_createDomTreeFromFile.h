#ifndef TEST_CREATEDOMTREEFROMFILE_H
#define TEST_CREATEDOMTREEFROMFILE_H

#include "../main.h"
#include "../functions.h"

/*!
 * \class test_createDomTreeFromFile
 * \brief Класс для модульного тестирования функции createDomTreeFromFile.
 *
 * Содержит тесты для проверки корректного создания DOM-дерева из файла
 * и обработки различных ошибочных ситуаций (файл не найден, пустой файл, некорректный XML).
 */
class test_createDomTreeFromFile : public QObject {
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса тестов.
     * \param parent Родительский QObject (обычно nullptr).
     */
    explicit test_createDomTreeFromFile(QObject *parent = nullptr);

private:
    QString tempDirPath; //!< Путь к временной директории для тестовых файлов.

private slots:
    /*! \brief Инициализация тестового набора (создание временной директории). */
    void initTestCase();
    /*! \brief Очистка после выполнения всех тестов (удаление временной директории). */
    void cleanupTestCase();
    /*! \brief Тест чтения корректного HTML-файла. */
    void validFile();
    /*! \brief Тест попытки чтения несуществующего файла. */
    void nonExistentFile();
    /*! \brief Тест чтения пустого файла. */
    void emptyFile();
    /*! \brief Тест чтения файла с некорректной XML/HTML разметкой. */
    void badXmlParsing();
    /*! \brief Тест обработки файла, содержащего тег <script>. */
    void scriptTag();
};

#endif // TEST_CREATEDOMTREEFROMFILE_H
