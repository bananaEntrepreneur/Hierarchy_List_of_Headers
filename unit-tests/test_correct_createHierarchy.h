#ifndef TEST_CORRECT_CREATEHIERARCHY_H
#define TEST_CORRECT_CREATEHIERARCHY_H

#include "../main.h"
#include "../paragraph.h"
#include "../functions.h"
#include "compareTrees.h"

/*!
 * \class test_correct_createHierarchy
 * \brief Класс для модульного тестирования функции createHierarchyListOfHeaderTags.
 *
 * Содержит набор тестовых случаев для проверки корректного построения
 * иерархии заголовочных тегов в различных ситуациях, когда не ожидается ошибок.
 */
class test_correct_createHierarchy : public QObject {
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса тестов.
     * \param parent Родительский QObject (обычно nullptr).
     */
    explicit test_correct_createHierarchy(QObject *parent = nullptr);

    /*!
     * \brief Обертка для QVERIFY для сравнения двух деревьев Paragraph.
     * \param actual Указатель на корень фактически построенного дерева.
     * \param expected Указатель на корень ожидаемого дерева.
     * \param message Сообщение для вывода в случае провала теста.
     */
    inline void QVERIFY_TREES_EQUAL(Paragraph* actual, Paragraph* expected, const char* message = "Paragraph trees are not equal.");

private slots:
    /*! \brief Тест базовой функциональности с простой иерархией. */
    void basicTest();

    /*! \brief Тест с несколькими дочерними элементами одного уровня под одним родителем. */
    void manyChildsWithSameLVL();

    /*! \brief Тест с полным набором тегов H1-H6. */
    void manyTagsWithVariousLVL();

    /*! \brief Тест обработки заголовков внутри тегов <section> и <article>. */
    void manyTagsInsideSectionAndArticle();

    /*! \brief Тест на игнорирование тегов, похожих на заголовки, но не являющихся ими (<hr>). */
    void headerLikeTags();

    /*! \brief Тест на игнорирование обычного текста (<p>) между заголовками. */
    void plaintTextBetweenHeaders();

    /*! \brief Тест на игнорирование текста, похожего на тег, внутри атрибута другого тега. */
    void textLikeHeaderInTagAttribute();

    /*! \brief Тест на игнорирование текста, который выглядит как заголовочный тег, но является просто текстом. */
    void textLikeHeader();

    /*! \brief Тест: Секции и статьи как прямые соседи с заголовками разного уровня. */
    void siblingSectionsAndArticlesWithMixedHeaders();

    /*! \brief Тест: Несколько секций подряд, каждая из которых начинается с H1. */
    void multipleSequentialSectionsStartingWithH1();

    /*! \brief Тест: Заголовки содержат сущности HTML (&amp;). */
    void headersWithHtmlEntities();

    /*! \brief Тест: Заголовки разных уровней после секции/статьи, относящиеся к предыдущему контексту. */
    void headersAfterSectionRelatingToOuterContext();
};

#endif // TEST_CORRECT_CREATEHIERARCHY_H
