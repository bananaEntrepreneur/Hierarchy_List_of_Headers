#ifndef TEST_INCORRECT_CREATEHIERARCHY_H
#define TEST_INCORRECT_CREATEHIERARCHY_H

#include "../main.h"
#include "../paragraph.h"
#include "../functions.h"

/*!
 * \class test_incorrect_createHierarchy
 * \brief Класс для модульного тестирования функции createHierarchyListOfHeaderTags на некорректных данных.
 *
 * Содержит тестовые случаи для проверки генерации ошибок функцией
 * createHierarchyListOfHeaderTags при обработке HTML-структур
 * с различными нарушениями (например, пустой body, некорректная вложенность секций,
 * нарушение иерархии заголовков и т.д.).
 */
class test_incorrect_createHierarchy : public QObject {
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса тестов.
     * \param parent Родительский QObject (обычно nullptr).
     */
    explicit test_incorrect_createHierarchy(QObject *parent = nullptr);

private slots:
    /*! \brief Тест: тег <body> не содержит дочерних элементов. */
    void noBodyChilds();
    /*! \brief Тест: тег <body> не содержит заголовочных тегов. */
    void noHeaders();
    /*! \brief Тест: заголовочный тег располагается вне тега <body> (в <head>). */
    void headerOutsideBody();
    /*! \brief Тест: первый заголовочный тег в <body> не является <h1>. */
    void firstHeaderNotH1();
    /*! \brief Тест: пустой заголовочный тег (<h1></h1>). */
    void emptyHeaderTag();
    /*! \brief Тест: несколько тегов <h1> в теге <body> (без секций). */
    void tooManyH1InBody();
    /*! \brief Тест: несколько тегов <h1> в одной <section>. */
    void tooManyH1InSection();
    /*! \brief Тест: некорректное вложение <section> в <section>. */
    void sectionInSection();
    /*! \brief Тест: некорректное вложение <article> в <article>. */
    void articleInArticle();
    /*! \brief Тест: некорректное вложение <section> в <article>. */
    void sectionInArticle();
    /*! \brief Тест: некорректное вложение <article> в <section>. */
    void articleInSection();
    /*! \brief Тест: нарушение иерархии заголовков (H1 за которым следует H3). */
    void headerHierarchySkipLevel();
    /*! \brief Тест: заголовочный тег содержит другие HTML-теги вместо текста. */
    void headerContainsOtherTags();
    /*! \brief Тест: первый заголовочный тег в <section> не является <h1>. */
    void firstHeaderInSectionNotH1();
};

#endif // TEST_INCORRECT_CREATEHIERARCHY_H
