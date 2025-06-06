#include "test_correct_createHierarchy.h"

// Конструктор остается прежним
test_correct_createHierarchy::test_correct_createHierarchy(QObject *parent)
    : QObject{parent}
{}

inline void test_correct_createHierarchy::QVERIFY_TREES_EQUAL(Paragraph* actual, Paragraph* expected, const char* message) {
    QVERIFY2(compareParagraphTreesRecursive(actual, expected), message);
}

void test_correct_createHierarchy::basicTest() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Lorem ispsum</h1>"
        "<h2>Dolor sit amet</h2>"
        "<h2>Consectetur adipiscing elit</h2>"
        "<h3>Tempor incididunt</h3>"
        "<h2>Ut labore et dolore</h2>"
        "<h3>Et dolore magna</h3>"
        "<h4>Ut enim ad minim</h4>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), qPrintable("basicTest: Errors found during hierarchy creation: " + (errors.isEmpty() ? "None" : errors.values().first().generateErrorMessage() ) ));

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    Paragraph* h2_1_e = new Paragraph("Dolor sit amet", h1_e, 2);
    h1_e->appendChild(h2_1_e);
    Paragraph* h2_2_e = new Paragraph("Consectetur adipiscing elit", h1_e, 2);
    h1_e->appendChild(h2_2_e);
    Paragraph* h3_1_e = new Paragraph("Tempor incididunt", h2_2_e, 3);
    h2_2_e->appendChild(h3_1_e);
    Paragraph* h2_3_e = new Paragraph("Ut labore et dolore", h1_e, 2);
    h1_e->appendChild(h2_3_e);
    Paragraph* h3_2_e = new Paragraph("Et dolore magna", h2_3_e, 3);
    h2_3_e->appendChild(h3_2_e);
    Paragraph* h4_1_e = new Paragraph("Ut enim ad minim", h3_2_e, 4);
    h3_2_e->appendChild(h4_1_e);

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "basicTest: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::manyChildsWithSameLVL() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Lorem ispsum</h1>"
        "<h2>Dolor sit amet</h2>"
        "<h2>Consectetur adipiscing elit</h2>"
        "<h2>Tempor incididunt</h2>"
        "<h2>Ut labore et dolore</h2>"
        "<h3>Et dolore magna</h3>"
        "<h4>Ut enim ad minim</h4>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "manyChildsWithSameLVL: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Dolor sit amet", h1_e, 2));
    h1_e->appendChild(new Paragraph("Consectetur adipiscing elit", h1_e, 2));
    h1_e->appendChild(new Paragraph("Tempor incididunt", h1_e, 2));
    Paragraph* h2_4_e = new Paragraph("Ut labore et dolore", h1_e, 2);
    h1_e->appendChild(h2_4_e);
    Paragraph* h3_1_e = new Paragraph("Et dolore magna", h2_4_e, 3);
    h2_4_e->appendChild(h3_1_e);
    h3_1_e->appendChild(new Paragraph("Ut enim ad minim", h3_1_e, 4));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "manyChildsWithSameLVL: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::manyTagsWithVariousLVL() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Lorem ispsum</h1>"
        "<h2>Dolor sit amet</h2>"
        "<h3>Consectetur adipiscing elit</h3>"
        "<h4>Tempor incididunt</h4>"
        "<h5>Ut labore et dolore</h5>"
        "<h6>Et dolore magna</h6>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "manyTagsWithVariousLVL: Errors found.");

    Paragraph expectedRoot;
    Paragraph* p1 = new Paragraph("Lorem ispsum", &expectedRoot, 1); expectedRoot.appendChild(p1);
    Paragraph* p2 = new Paragraph("Dolor sit amet", p1, 2); p1->appendChild(p2);
    Paragraph* p3 = new Paragraph("Consectetur adipiscing elit", p2, 3); p2->appendChild(p3);
    Paragraph* p4 = new Paragraph("Tempor incididunt", p3, 4); p3->appendChild(p4);
    Paragraph* p5 = new Paragraph("Ut labore et dolore", p4, 5); p4->appendChild(p5);
    p5->appendChild(new Paragraph("Et dolore magna", p5, 6));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "manyTagsWithVariousLVL: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::manyTagsInsideSectionAndArticle() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Lorem ispsum 1</h1>"
        "<section>"
        "<h1>Lorem ispsum 2</h1>"
        "<h2>Dolor sit amet 1</h2>"
        "</section>"
        "<article>"
        "<h1>Lorem ispsum 3</h1>"
        "<h2>Consectetur adipiscing elit</h2>"
        "</article>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY(errors.isEmpty());

    Paragraph expectedRoot;
    Paragraph* h1_0_e = new Paragraph("Lorem ispsum 1", &expectedRoot, 1);
    expectedRoot.appendChild(h1_0_e);

    Paragraph* h1_1_e = new Paragraph("Lorem ispsum 2", &expectedRoot, 1);
    expectedRoot.appendChild(h1_1_e);
    h1_1_e->appendChild(new Paragraph("Dolor sit amet 1", h1_1_e, 2));

    Paragraph* h1_3_e = new Paragraph("Lorem ispsum 3", &expectedRoot, 1);
    expectedRoot.appendChild(h1_3_e);
    h1_3_e->appendChild(new Paragraph("Consectetur adipiscing elit", h1_3_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "manyTagsInsideSectionAndArticle: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::headerLikeTags() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<hr/>"
            "<br/>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "headerLikeTags: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Dolor sit amet", h1_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "headerLikeTags: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::plaintTextBetweenHeaders() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "Some plain text here."
            "<p>Paragraph text.</p>"
            "<div>Div text.</div>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "plaintTextBetweenHeaders: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Dolor sit amet", h1_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "plaintTextBetweenHeaders: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::textLikeHeaderInTagAttribute() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<div title = 'h1This is not a real header'>"
            "</div>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "textLikeHeaderInTagAttribute: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Dolor sit amet", h1_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "textLikeHeaderInTagAttribute: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::textLikeHeader() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<p>This text contains &lt;h2&gt; but it's not a tag.</p>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "textLikeHeader: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Lorem ispsum", &expectedRoot, 1);
    expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Dolor sit amet", h1_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "textLikeHeader: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::siblingSectionsAndArticlesWithMixedHeaders() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Main Title</h1>"
        "<h2>Subtitle One</h2>"
        "<section>"
        "<h1>Section 1 Title (H1)</h1>"
        "<h2>Section 1 Subtitle (H2)</h2>"
        "</section>"
        "<article>"
        "<h1>Article 1 Title (H1)</h1>"
        "</article>"
        "<h2>Subtitle Two (sibling of Subtitle One)</h2>"
        "<h3>Detail under Subtitle Two</h3>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "siblingSectionsAndArticlesWithMixedHeaders: Errors found.");

    Paragraph expectedRoot;
    Paragraph* mainH1_e = new Paragraph("Main Title", &expectedRoot, 1);
    expectedRoot.appendChild(mainH1_e);
    Paragraph* sub1_e = new Paragraph("Subtitle One", mainH1_e, 2);
    mainH1_e->appendChild(sub1_e);

    Paragraph* sec1H1_e = new Paragraph("Section 1 Title (H1)", &expectedRoot, 1); expectedRoot.appendChild(sec1H1_e);
    sec1H1_e->appendChild(new Paragraph("Section 1 Subtitle (H2)", sec1H1_e, 2));

    Paragraph* art1H1_e = new Paragraph("Article 1 Title (H1)", &expectedRoot, 1); expectedRoot.appendChild(art1H1_e);

    Paragraph* sub2_e = new Paragraph("Subtitle Two (sibling of Subtitle One)", mainH1_e, 2);
    mainH1_e->appendChild(sub2_e);
    sub2_e->appendChild(new Paragraph("Detail under Subtitle Two", sub2_e, 3));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "siblingSectionsAndArticlesWithMixedHeaders: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::multipleSequentialSectionsStartingWithH1() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Main H1 After Sections</h1>"
        "<section>"
        "<h1>Section 1 H1</h1>"
        "<h2>Section 1 H2</h2>"
        "</section>"
        "<section>"
        "<h1>Section 2 H1</h1>"
        "</section>"
        "<section>"
        "<h1>Section 3 H1</h1>"
        "</section>"
        "</body>"
        "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "multipleSequentialSectionsStartingWithH1: Errors found.");

    Paragraph expectedRoot;

    expectedRoot.appendChild(new Paragraph("Main H1 After Sections", &expectedRoot, 1));

    Paragraph* s1h1_e = new Paragraph("Section 1 H1", &expectedRoot, 1); expectedRoot.appendChild(s1h1_e);
    s1h1_e->appendChild(new Paragraph("Section 1 H2", s1h1_e, 2));

    expectedRoot.appendChild(new Paragraph("Section 2 H1", &expectedRoot, 1));

    expectedRoot.appendChild(new Paragraph("Section 3 H1", &expectedRoot, 1));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "multipleSequentialSectionsStartingWithH1: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::headersWithHtmlEntities() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Title with &amp; &lt; &gt; &quot; &apos;</h1>"
        "<h2>Section with &nbsp; spaces</h2>"
        "</body>"
        "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), "headersWithHtmlEntities: Errors found.");

    Paragraph expectedRoot;
    Paragraph* h1_e = new Paragraph("Title with & < > \" '", &expectedRoot, 1); expectedRoot.appendChild(h1_e);
    h1_e->appendChild(new Paragraph("Section with  spaces", h1_e, 2));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "headersWithHtmlEntities: Paragraph trees are not equal.");
}

void test_correct_createHierarchy::headersAfterSectionRelatingToOuterContext() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Main H1</h1>"
        "<h2>First Subtitle (under Main H1)</h2>"
        "<section>"
        "<h1>Section H1</h1>"
        "<h2>Section Subtitle</h2>"
        "</section>"
        "<h3>Second Subtitle (child of First Subtitle)</h3>"
        "<h4>Detail for H3 (child of H3)</h4>"
        "</body>"
        "</html>";
    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph actualRoot;
    QSet<Error> errors;
    createHierarchyListOfHeaderTags(rootDocElement, &actualRoot, errors);
    QVERIFY2(errors.isEmpty(), qPrintable("headersAfterSectionRelatingToOuterContext: Errors found: " + (errors.isEmpty() ? "None" : errors.values().first().generateErrorMessage() ) ));


    Paragraph expectedRoot;
    Paragraph* mainH1_e = new Paragraph("Main H1", &expectedRoot, 1); expectedRoot.appendChild(mainH1_e);
    Paragraph* firstH2_e = new Paragraph("First Subtitle (under Main H1)", mainH1_e, 2); mainH1_e->appendChild(firstH2_e);

    Paragraph* secH1_e = new Paragraph("Section H1", &expectedRoot, 1); expectedRoot.appendChild(secH1_e);
    secH1_e->appendChild(new Paragraph("Section Subtitle", secH1_e, 2));

    Paragraph* secondH3_e = new Paragraph("Second Subtitle (child of First Subtitle)", firstH2_e, 3);
    firstH2_e->appendChild(secondH3_e);
    secondH3_e->appendChild(new Paragraph("Detail for H3 (child of H3)", secondH3_e, 4));

    QVERIFY_TREES_EQUAL(&actualRoot, &expectedRoot, "headersAfterSectionRelatingToOuterContext: Paragraph trees are not equal.");
}
