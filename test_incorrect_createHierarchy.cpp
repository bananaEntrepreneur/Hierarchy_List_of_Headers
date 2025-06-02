#include "test_incorrect_createHierarchy.h"

test_incorrect_createHierarchy::test_incorrect_createHierarchy(QObject *parent)
    : QObject{parent}
{}

void test_incorrect_createHierarchy::noBodyChilds() {
    // Тест №1: "Тег <body> не содержит дочерних элементов"
    // Ожидаемая ошибка: noHeaderTagsError
    QString html =
            "<html>"
            "<body>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Ошибка пустого <body> не найдена!");
    if (errors.isEmpty()) return;

    Error generatedError = errors.values().first();
    QCOMPARE(generatedError.getErrorType(), ErrorType::noHeaderTagsError);
    // getErrorTagName() и getErrorAttrName() нерелевантны для noHeaderTagsError
}

void test_incorrect_createHierarchy::noHeaders() {
    // Тест №2: "Тег <body> не содержит заголовочных тегов"
    // Ожидаемая ошибка: noHeaderTagsError
    QString html =
            "<html>"
            "<body>"
            "<p>Lorem ipsum</p>"
            "<div><img src = 'URL' /></div>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Ошибка <body> без заголовочных тегов не найдена!");
    if (errors.isEmpty()) return;

    Error generatedError = errors.values().first();
    QCOMPARE(generatedError.getErrorType(), ErrorType::noHeaderTagsError);
}

void test_incorrect_createHierarchy::headerOutsideBody() {
    // Тест №3: "Заголовочный тег располагается вне <body>"
    // (Например, в <head>. Функция createHierarchy обычно вызывается для body,
    // но если бы она обрабатывала весь документ или <head>, эта ошибка была бы актуальна)
    // Для имитации ситуации, будем передавать <head> в createHierarchyListOfHeaderTags
    QString html =
            "<html>"
            "<head>"
            "<h1>Header in head</h1>"
            "</head>"
            "<body>"
            "<h2>Header in body</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement headElement = doc.documentElement().firstChildElement("head");

    Paragraph root; // Используем временный root для вызова
    QSet<Error> errors;

    QDomElement bodyElement = doc.documentElement().firstChildElement("body");
    Paragraph mainRoot; // Главный root для иерархии из body
    QSet<Error> bodyErrors;

    // Обрабатываем head, где ожидаем ошибку
    if (!headElement.isNull()) {
         createHierarchyListOfHeaderTags(headElement, &mainRoot, bodyErrors);
    }
    // Затем обрабатываем body (хотя ошибка из head уже должна быть)
    //createHierarchyListOfHeaderTags(bodyElement, &mainRoot, bodyErrors);

    QVERIFY2(!bodyErrors.isEmpty(), "Ошибка заголовочного тега вне <body> не найдена!");
    if (bodyErrors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : bodyErrors) {
        if (err.getErrorType() == ErrorType::htmlStructureError &&
            err.getErrorTagName().toLower() == "h1" &&
            err.getErrorAttrName() == "outside_body") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "htmlStructureError (header_outside_body) for h1 in head was not found.");
}

void test_incorrect_createHierarchy::firstHeaderNotH1() {
    // Тест №4: "Первый заголовочный тег не <h1>" (в <body>)
    // Ожидаемая ошибка: noTagError (согласно документации) или htmlStructureError
    // ErrorType::noTagError, errorTagName="h2" (или какой был найден), errorAttrName="body_first_not_h1"
    QString html =
            "<html>"
            "<body>"
            "<h2>First header is H2</h2>"
            "<h1>Then H1</h1>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Ошибка неправильной последовательности тегов не найдена!");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        // В generateErrorMessage "Ошибка: первым тегом в body должен быть <h1>."
        // В тестах noTagError, tagName "hl", attrName "body".
        // В новой реализации createHierarchyListOfHeaderTags это может быть htmlStructureError или noTagError
        if ((err.getErrorType() == ErrorType::noTagError || err.getErrorType() == ErrorType::htmlStructureError) &&
             err.getErrorAttrName() == "body_first_not_h1" && // Наш флаг
             err.getErrorTagName().toLower() == "h2") { // Тег, который был найден вместо H1
            foundError = true;
        }
    }
    QVERIFY2(foundError, "Specific error for 'first header in body not H1' not found or attributes mismatch.");
}


void test_incorrect_createHierarchy::emptyHeaderTag() {
    // Тест №5: "Пустой заголовочный тег"
    // Ожидаемая ошибка: tagError, errorTagName="h1", errorAttrName="empty"
    QString html =
            "<html>"
            "<body>"
            "<h1></h1>"
            "<h2>Second header</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for empty H1 tag should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::tagError &&
            err.getErrorTagName().toLower() == "h1" &&
            err.getErrorAttrName() == "empty") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "tagError (empty) for H1 not found.");
}

void test_incorrect_createHierarchy::tooManyH1InBody() {
    // Тест №6: "Два <h1> в одной секции" (здесь секция - это <body>, без <section> или <article>)
    // Ожидаемая ошибка: tooManyTagsError, errorTagName="h1", errorAttrName="body"
    QString html =
            "<html>"
            "<body>"
            "<h1>First H1</h1>"
            "<h2>Subtitle</h2>"
            "<h1>Second H1</h1>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for multiple H1 in body should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::tooManyTagsError &&
            err.getErrorTagName().toLower() == "h1" &&
            err.getErrorAttrName().toLower() == "body") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "tooManyTagsError for H1 in body not found.");
}

void test_incorrect_createHierarchy::tooManyH1InSection() {
    // Тест №7: "Два <h1> в <section>"
    QString html =
            "<html>"
            "<body>"
            "<section>"
            "<h1>First H1 in section</h1>"
            "<h2>Subtitle</h2>"
            "<h1>Second H1 in section</h1>"
            "</section>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for multiple H1 in section should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::tooManyTagsError &&
            err.getErrorTagName().toLower() == "h1" &&
            err.getErrorAttrName().toLower() == "section") { // Контекст section
            foundError = true;
        }
    }
    QVERIFY2(foundError, "tooManyTagsError for H1 in section not found.");
}


void test_incorrect_createHierarchy::sectionInSection() {
    // Тест №8: "<section> вложен в <section>"
    // Ожидаемая ошибка: sectionNestingError, errorTagName="section" (внутренний), errorAttrName="section" (внешний)
    QString html =
            "<html>"
            "<body>"
            "<section>"
            "<h1>Outer section</h1>"
            "<section>"
            "<h2>Inner section header</h2>"
            "</section>"
            "</section>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for section in section should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::sectionNestingError &&
            err.getErrorTagName().toLower() == "section" && // Внутренний (ошибочный) тег
            err.getErrorAttrName().toLower() == "section") { // Внешний (родительский) тег
            foundError = true;
        }
    }
    QVERIFY2(foundError, "sectionNestingError for section in section not found.");
}

void test_incorrect_createHierarchy::articleInArticle() {
    // Тест №9: "<article> вложен в <article>"
    // Ожидаемая ошибка: articleNestingError, errorTagName="article", errorAttrName="article"
    QString html =
            "<html>"
            "<body>"
            "<article>"
            "<h1>Outer article</h1>"
            "<article>"
            "<h2>Inner article header</h2>"
            "</article>"
            "</article>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");
    Paragraph root;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);
    QVERIFY2(!errors.isEmpty(), "Error for article in article should be reported.");
    if (errors.isEmpty()) return;
    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::articleNestingError &&
            err.getErrorTagName().toLower() == "article" &&
            err.getErrorAttrName().toLower() == "article") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "articleNestingError for article in article not found.");
}

void test_incorrect_createHierarchy::sectionInArticle() {
    // Тест №10: "<section> вложен в <article>"
    // Ожидаемая ошибка: articleNestingError, errorTagName="section", errorAttrName="article"
    QString html =
            "<html>"
            "<body>"
            "<article>"
            "<h1>Outer article</h1>"
            "<section>"
            "<h2>Inner section header</h2>"
            "</section>"
            "</article>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");
    Paragraph root;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);
    QVERIFY2(!errors.isEmpty(), "Error for section in article should be reported.");
    if (errors.isEmpty()) return;
    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::articleNestingError && // Родитель article, поэтому тип ошибки articleNestingError
            err.getErrorTagName().toLower() == "section" &&      // Вложенный тег section
            err.getErrorAttrName().toLower() == "article") {     // Родительский тег article
            foundError = true;
        }
    }
    QVERIFY2(foundError, "articleNestingError for section in article not found.");
}

void test_incorrect_createHierarchy::articleInSection() {
    // Тест №11: "<article> вложен в <section>"
    // Ожидаемая ошибка: sectionNestingError, errorTagName="article", errorAttrName="section"
    QString html =
            "<html>"
            "<body>"
            "<section>"
            "<h1>Outer section</h1>"
            "<article>"
            "<h2>Inner article header</h2>"
            "</article>"
            "</section>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");
    Paragraph root;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);
    QVERIFY2(!errors.isEmpty(), "Error for article in section should be reported.");
    if (errors.isEmpty()) return;
    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::sectionNestingError && // Родитель section
            err.getErrorTagName().toLower() == "article" &&      // Вложенный тег article
            err.getErrorAttrName().toLower() == "section") {     // Родительский тег section
            foundError = true;
        }
    }
    QVERIFY2(foundError, "sectionNestingError for article in section not found.");
}

void test_incorrect_createHierarchy::headerHierarchySkipLevel() {
    // Тест №12: "Неправильная последовательность тегов (уровень следующего тега отличается больше, чем на 1)"
    // Например, H1 -> H3
    // Ожидаемая ошибка: headerTagsHierarchyError, errorTagName="h3"
    QString html =
            "<html>"
            "<body>"
            "<h1>Level 1</h1>"
            "<h3>Level 3 (skip H2)</h3>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for H1 -> H3 hierarchy skip should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::headerTagsHierarchyError &&
            err.getErrorTagName().toLower() == "h3") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "headerTagsHierarchyError for H1->H3 skip not found.");
}

void test_incorrect_createHierarchy::headerContainsOtherTags() {
    // Тест №13: "Заголовочный тег может содержать только текст."
    // Ожидаемая ошибка: tagError, errorTagName="h1", errorAttrName="content_not_text"
    QString html =
            "<html>"
            "<body>"
            "<h1>Title with <b>bold</b> text</h1>"
            "<h2>Another header</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QVERIFY2(!errors.isEmpty(), "Error for H1 containing <b> tag should be reported.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for (const Error& err : errors) {
        if (err.getErrorType() == ErrorType::tagError &&
            err.getErrorTagName().toLower() == "h1" &&
            err.getErrorAttrName() == "content_not_text") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "tagError (content_not_text) for H1 containing <b> not found.");
}

void test_incorrect_createHierarchy::firstHeaderInSectionNotH1() {
    // Тест №14: "Первый заголовочный тег в секции не <h1>"
    QString html =
            "<html>"
            "<body>"
            "<section>"
            "<h2>H2 is first in section</h2>"
            "<h1>H1 later</h1>"
            "</section>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");
    Paragraph root;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);
    QVERIFY2(!errors.isEmpty(), "Error for first header in section not H1 should be reported.");
    if (errors.isEmpty()) return;
    bool foundError = false;
    for (const Error& err : errors) {
        if ((err.getErrorType() == ErrorType::noTagError || err.getErrorType() == ErrorType::htmlStructureError) &&
            err.getErrorAttrName() == "section_first_not_h1" &&
            err.getErrorTagName().toLower() == "h2") {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "Error for first header in section not H1 not found or attributes mismatch.");
}

// Тест для проверки игнорирования содержимого <script>
// Это не ошибка иерархии, а скорее предупреждение/информационная ошибка при парсинге.
// В createHierarchyListOfHeaderTags оно не генерируется, но может быть добавлено при необходимости
// на более раннем этапе обработки DOM или если getHeaderLevel/текст будет извлекаться для <script>.
/*
void test_incorrect_createHierarchy::scriptTagContent() {
    // Тест №12: "Содержимое тега <script> не учитывается"
    // Ожидаемая ошибка: fileError (согласно generateErrorMessage), errorTagName="script", errorAttrName="ignored_content" (мой флаг)
    QString html =
            "<html>"
            "<body>"
            "<h1>Title</h1>"
            "<script>var x = '<h1>Not a real header</h1>';</script>"
            "<h2>Subtitle</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    // Ожидается, что текст из <script> не попадет в иерархию.
    // Ошибка об игнорировании <script> должна генерироваться, если это предусмотрено.
    // В текущей createHierarchyListOfHeaderTags эта ошибка не генерируется.
    // Если бы она генерировалась:
    // QVERIFY(!errors.isEmpty());
    // bool foundError = false;
    // for (const Error& err : errors) {
    //     if (err.getErrorType() == ErrorType::fileError && // или другой подходящий тип
    //         err.getErrorTagName().toLower() == "script" &&
    //         err.getErrorAttrName() == "ignored_content") {
    //         foundError = true;
    //     }
    // }
    // QVERIFY(foundError);

    // Проверяем, что иерархия построена без учета содержимого script
    QVERIFY(root.getChildHierarchy()->size() == 1); // Только <h1>
    if (root.getChildHierarchy()->size() == 1) {
        Paragraph* h1 = root.getChildHierarchy()->first();
        QCOMPARE(h1->getText(), "Title");
        QVERIFY(h1->getChildHierarchy()->size() == 1); // Только <h2>
        if (h1->getChildHierarchy()->size() == 1) {
            Paragraph* h2 = h1->getChildHierarchy()->first();
            QCOMPARE(h2->getText(), "Subtitle");
        }
    }
}
*/
