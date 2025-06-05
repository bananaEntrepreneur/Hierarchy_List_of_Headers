#ifndef ERROR_H
#define ERROR_H

#include "main.h"

/*!
 * \file error.h
*/

/*!
 * \brief Перечисление типов возможных ошибок.
 *
 * Определяет различные категории ошибок, которые могут возникнуть
 * в процессе работы приложения.
 */
enum ErrorType {
    noError,                  /*!< Ошибка отсутствует. */
    tagError,                 /*!< Ошибка, связанная с тегом (например, пустой заголовочный тег или некорректное содержимое). */
    tagAttributeError,        /*!< Ошибка, связанная с атрибутом тега. */
    fileError,                /*!< Ошибка при работе с файлом (например, не удалось открыть или записать). */
    htmlStructureError,       /*!< Ошибка в структуре HTML-документа (например, заголовок вне body). */
    headerTagsHierarchyError, /*!< Ошибка в иерархии заголовочных тегов (например, пропуск уровня). */
    sectionNestingError,      /*!< Ошибка вложенности тега <section>. */
    articleNestingError,      /*!< Ошибка вложенности тега <article>. */
    tooManyTagsError,         /*!< Обнаружено слишком много тегов определенного типа (например, несколько <h1> в одной секции). */
    noTagError,               /*!< Отсутствует необходимый тег (например, первый тег в body не <h1>). */
    noHeaderTagsError,        /*!< В документе не найдено ни одного заголовочного тега. */
    XMLerror                  /*!< Ошибка при парсинге XML документа. */
};

/*!
 * \class Error
 * \brief Класс для представления и хранения информации об ошибке.
 *
 * Содержит тип ошибки и дополнительную информацию, такую как
 * имя тега, имя атрибута или пути к файлам, связанные с ошибкой.
 */
class Error {
public:
    /*!
     * \brief Конструктор по умолчанию.
     * Инициализирует ошибку типом noError и пустыми строками для дополнительной информации.
     */
    Error();

    //! Перегрузки операторов сравнения для корректной работы с QSet и для возможной сортировки.
    /*!
     * \brief Оператор сравнения "больше".
     * \param other Другой объект Error для сравнения.
     * \return true, если текущий объект "больше" other, иначе false.
     */
    bool operator>(const Error& other) const;
    /*!
     * \brief Оператор сравнения "меньше".
     * \param other Другой объект Error для сравнения.
     * \return true, если текущий объект "меньше" other, иначе false.
     */
    bool operator<(const Error& other) const;
    /*!
     * \brief Оператор сравнения "равно".
     * \param other Другой объект Error для сравнения.
     * \return true, если текущий объект равен other, иначе false.
     */
    bool operator==(const Error& other) const;

    //! SET-теры
    /*!
     * \brief Устанавливает тип ошибки.
     * \param value Тип ошибки из перечисления ErrorType.
     */
    void setType(ErrorType value);
    /*!
     * \brief Устанавливает имя тега, связанного с ошибкой.
     * \param value Имя тега.
     */
    void setErrorTagName(QString value);
    /*!
     * \brief Устанавливает имя атрибута, связанного с ошибкой.
     * \param value Имя атрибута.
     */
    void setErrorAttrName(QString value);
    /*!
     * \brief Устанавливает путь к входному файлу, связанному с ошибкой.
     * \param value Путь к файлу.
     */
    void setErrorInputPath(QString value);
    /*!
     * \brief Устанавливает путь к выходному файлу, связанному с ошибкой.
     * \param value Путь к файлу.
     */
    void setErrorOutputPath(QString value);

    //! GET-теры
    /*!
     * \brief Возвращает тип ошибки.
     * \return Тип ошибки ErrorType.
     */
    ErrorType getErrorType() const;
    /*!
     * \brief Возвращает целочисленное представление типа ошибки.
     * Используется для qHash.
     * \return Целое число, соответствующее типу ошибки.
     */
    int getIntErrorType() const;
    /*!
     * \brief Возвращает имя тега, связанного с ошибкой.
     * \return Имя тега.
     */
    QString getErrorTagName() const;
    /*!
     * \brief Возвращает имя атрибута, связанного с ошибкой.
     * \return Имя атрибута.
     */
    QString getErrorAttrName() const;
    /*!
     * \brief Возвращает путь к входному файлу, связанному с ошибкой.
     * \return Путь к файлу.
     */
    QString getErrorInputPath() const;
    /*!
     * \brief Возвращает путь к выходному файлу, связанному с ошибкой.
     * \return Путь к файлу.
     */
    QString getErrorOutputPath() const;

    /*!
     * \brief Генерирует текстовое сообщение об ошибке.
     * Формирует сообщение на основе типа ошибки и сохраненных данных (имя тега, атрибута, пути).
     * \return Строковое представление ошибки.
     */
    QString generateErrorMessage() const;

private:
    ErrorType type;             //!< Тип ошибки.
    QString errorTagName;       //!< Имя тега, связанного с ошибкой.
    QString errorAttrName;      //!< Имя атрибута, связанного с ошибкой, или дополнительный контекст.
    QString errorInputPath;     //!< Путь к входному файлу.
    QString errorOutputPath;    //!< Путь к выходному файлу.
};

/*!
 * \brief Функция хеширования для объектов класса Error.
 * Необходима для использования объектов Error в QSet.
 * \param value Объект Error для хеширования.
 * \param seed Начальное значение для хеш-функции.
 * \return Хеш-значение.
 */
inline uint qHash(const Error& value, uint seed) {
    seed = qHash(value.getIntErrorType(), seed);
    seed = qHash(value.getErrorTagName(), seed);
    seed = qHash(value.getErrorAttrName(), seed);
    seed = qHash(value.getErrorInputPath(), seed);
    seed = qHash(value.getErrorOutputPath(), seed);
    return seed;
}

#endif // ERROR_H
