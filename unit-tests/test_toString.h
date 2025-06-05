#ifndef TEST_TOSTRING_H
#define TEST_TOSTRING_H

#include "../main.h"
#include "../paragraph.h"

/*!
 * \class test_toString
 * \brief Класс для модульного тестирования метода Paragraph::toString().
 *
 * Содержит тесты для проверки корректности строкового представления
 * иерархии Paragraph, включая нумерацию и обработку различных
 * структур иерархии.
 */
class test_toString : public QObject {
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса тестов.
     * \param parent Родительский QObject (обычно nullptr).
     */
    explicit test_toString(QObject *parent = nullptr);

private slots:
    /*! \brief Тест базовой функциональности toString с простой иерархией. */
    void basicTest();
    /*! \brief Тест toString для пустой иерархии (только корневой узел). */
    void emptyHierarchy();
    /*! \brief Тест toString, когда метод вызывается для узла, не имеющего одноуровневых соседей, но имеющего детей. */
    void onlyDifferentLVL();
    /*! \brief Тест toString для иерархии, состоящей из одного параграфа (помимо root). */
    void oneParagraphHierarchy();
    /*! \brief Тест toString с использованием разделителя, отличного от точки. */
    void dotIsNotSeparator();
    /*! \brief Тест toString для иерархии с множеством дочерних элементов на разных уровнях. */
    void manyChilds();
};

#endif // TEST_TOSTRING_H
