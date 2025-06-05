#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "main.h"

/*!
 * \file paragraph.h
 * \class Paragraph
 * \brief Представляет собой пункт в иерархии заголовочных тегов. *
 *
 * Каждый объект этого класса соответствует одному заголовочному тегу (H1-H6)
 * или структурному элементу (section, article), обнаруженному в HTML-документе.
 * Хранит текст заголовка, его уровень вложенности, ссылку на родительский
 * элемент и список дочерних элементов.
 */
class Paragraph {
public:
    /*!
     * \brief Конструктор по умолчанию.
     * Создает корневой элемент иерархии с текстом "root", уровнем 0 и без родителя.
     */
    Paragraph();
    /*!
     * \brief Конструктор для создания элемента иерархии.
     * \param iText Текст заголовка.
     * \param iParent Указатель на родительский элемент Paragraph.
     * \param iLevel Уровень вложенности заголовка (1 для H1, 2 для H2 и т.д.).
     */
    Paragraph(QString iText, Paragraph* iParent, int iLevel);
    /*!
     * \brief Конструктор для создания элемента иерархии с предопределенным списком дочерних элементов.
     * \param iText Текст заголовка.
     * \param iParent Указатель на родительский элемент Paragraph.
     * \param iChildHierarchy Список дочерних элементов Paragraph.
     * \param iLevel Уровень вложенности заголовка.
     */
    Paragraph(QString iText, Paragraph* iParent, QList<Paragraph*> iChildHierarchy, int iLevel);

    //! SET-теры
    /*!
     * \brief Устанавливает текст заголовка.
     * \param value Новый текст заголовка.
     */
    void setText(QString value);
    /*!
     * \brief Устанавливает родительский элемент.
     * \param value Указатель на родительский Paragraph.
     */
    void setParent(Paragraph* value);
    /*!
     * \brief Добавляет дочерний элемент.
     * \param value Указатель на дочерний Paragraph для добавления.
     */
    void appendChild(Paragraph* value);
    /*!
     * \brief Устанавливает уровень вложенности.
     * \param value Новый уровень вложенности.
     */
    void setLevel(int value);

    //! GET-теры
    /*!
     * \brief Возвращает текст заголовка.
     * \return Текст заголовка.
     */
    QString getText() const;
    /*!
     * \brief Возвращает указатель на родительский элемент.
     * \return Указатель на родительский Paragraph.
     */
    Paragraph* getParent() const;
    /*!
     * \brief Возвращает указатель на список дочерних элементов.
     * \return Указатель на QList<Paragraph*>, содержащий дочерние элементы.
     */
    QList<Paragraph*>* getChildHierarchy();

    /*!
     * \brief Возвращает уровень вложенности.
     * \return Уровень вложенности.
     */
    int getLevel() const;

    /*!
     * \brief Возвращает строковое представление иерархии, начиная с текущего узла.
     * Если текущий узел - корневой (level 0), то выводятся его дочерние элементы.
     * Если текущий узел - не корневой, то выводится он сам и его дочерние элементы с корректной нумерацией.
     * \param[in] separator Разделитель между цифрами в нумерации (например, ".").
     * \return Строковое представление пункта иерархии заголовочных тегов.
     */
    QString toString(QString separator);

private:
    QString text;                       //!< Текст заголовка.
    int level;                          //!< Уровень вложенности (0 для корня, 1 для H1, и т.д.).
    Paragraph* parent;                  //!< Указатель на родительский элемент.
    QList<Paragraph*> childHierarchy;   //!< Список указателей на дочерние элементы.

    /*!
     * \brief Рекурсивный приватный метод для формирования строки с нумерацией.
     * Вызывается методом toString() для построения строкового представления
     * текущего узла и его дочерних элементов.
     * \param separator Разделитель между цифрами в нумерации.
     * \param currentNumeration Текущий путь нумерации (например, [1, 2] для "1.2").
     * \return Строковое представление текущего узла и его поддерева.
     */
    QString getString(QString separator, QVector<int>& currentNumeration);

};

#endif // PARAGRAPH_H
