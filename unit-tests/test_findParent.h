#ifndef TEST_FINDPARENT_H
#define TEST_FINDPARENT_H

#include "../main.h"
#include "../functions.h"
#include "../paragraph.h"

/*!
 * \class test_findParent
 * \brief Класс для модульного тестирования функции findParentForParagraph.
 *
 * Содержит тесты для проверки логики определения родительского элемента
 * при добавлении нового заголовка в иерархию в зависимости от уровней
 * текущего и предыдущего заголовков.
 */
class test_findParent : public QObject {
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса тестов.
     * \param parent Родительский QObject (обычно nullptr).
     */
    explicit test_findParent(QObject *parent = nullptr);

private slots:
    /*! \brief Тест: текущий уровень заголовка больше предыдущего (вложенный заголовок). */
    void currentLVLbiggerThenPrevious();
    /*! \brief Тест: текущий уровень заголовка равен предыдущему (соседний заголовок). */
    void currentLVLequalPrevious();
    /*! \brief Тест: текущий уровень заголовка меньше предыдущего (выход на более высокий уровень). */
    void currentLVLlessThenPrevious();
    /*! \brief Тест: текущий уровень меньше предыдущего, при этом есть несколько одноуровневых соседей у предыдущего. */
    void currentLVLlessThenPreviousANDmanySameParagraphs();
};

#endif // TEST_FINDPARENT_H
