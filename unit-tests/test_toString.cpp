#include "test_toString.h"

test_toString::test_toString(QObject *parent)
    : QObject{parent}
{}

void test_toString::basicTest() {
    Paragraph root;
    Paragraph* h1 = new Paragraph("Lorem ipsum", &root, 1);
    root.appendChild(h1);

    Paragraph* h2_1 = new Paragraph("Dolor sit amet", h1, 2);
    Paragraph* h2_2 = new Paragraph("Consectetur adipiscing elit", h1, 2);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_2, 3);
    Paragraph* h2_3 = new Paragraph("Ut labore et dolore", h1, 2);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_3, 3);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);

    h1->appendChild(h2_1);
    h1->appendChild(h2_2);
    h2_2->appendChild(h3_1);
    h1->appendChild(h2_3);
    h2_3->appendChild(h3_2);
    h3_2->appendChild(h4_1);

    QString result = root.toString(".");

    QString expected =
        "1 Lorem ipsum\n"
        "1.1 Dolor sit amet\n"
        "1.2 Consectetur adipiscing elit\n"
        "1.2.1 Tempor incididunt\n"
        "1.3 Ut labore et dolore\n"
        "1.3.1 Et dolore magna\n"
        "1.3.1.1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}

void test_toString::manyChilds() {
    Paragraph root;

    Paragraph* h1_1 = new Paragraph("Excepteur sint", &root, 1);
    root.appendChild(h1_1);
    Paragraph* h2_1 = new Paragraph("Nulla pariatur", h1_1, 2);
    h1_1->appendChild(h2_1);

    Paragraph* h1_2 = new Paragraph("Lorem ipsum", &root, 1);
    root.appendChild(h1_2);
    Paragraph* h2_2 = new Paragraph("Dolor sit amet", h1_2, 2);
    h1_2->appendChild(h2_2);
    Paragraph* h2_3 = new Paragraph("Consectetur adipiscing elit", h1_2, 2);
    h1_2->appendChild(h2_3);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_3, 3);
    h2_3->appendChild(h3_1);
    Paragraph* h2_4 = new Paragraph("Ut labore et dolore", h1_2, 2);
    h1_2->appendChild(h2_4);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_4, 3);
    h2_4->appendChild(h3_2);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);
    h3_2->appendChild(h4_1);

    Paragraph* h1_3 = new Paragraph("Quis autem", &root, 1);
    root.appendChild(h1_3);

    QString result = root.toString(".");

    QString expected =
            "1 Excepteur sint\n"
            "1.1 Nulla pariatur\n"
            "2 Lorem ipsum\n"
            "2.1 Dolor sit amet\n"
            "2.2 Consectetur adipiscing elit\n"
            "2.2.1 Tempor incididunt\n"
            "2.3 Ut labore et dolore\n"
            "2.3.1 Et dolore magna\n"
            "2.3.1.1 Ut enim ad minim\n"
            "3 Quis autem\n";

    QCOMPARE(result, expected);
}

void test_toString::emptyHierarchy() {
    Paragraph root;

    QVector<int> numeration;
    QString result = root.toString(".");

    QString expected = "";

    QCOMPARE(result, expected);
}

void test_toString::onlyDifferentLVL() {
    Paragraph root;
    Paragraph* h1 = new Paragraph("Lorem ipsum", &root, 1);
    root.appendChild(h1);

    Paragraph* h2_1 = new Paragraph("Dolor sit amet", h1, 2);
    Paragraph* h2_2 = new Paragraph("Consectetur adipiscing elit", h1, 2);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_2, 3);
    Paragraph* h2_3 = new Paragraph("Ut labore et dolore", h1, 2);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_3, 3);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);

    h1->appendChild(h2_1);
    h1->appendChild(h2_2);
    h2_2->appendChild(h3_1);
    h1->appendChild(h2_3);
    h2_3->appendChild(h3_2);
    h3_2->appendChild(h4_1);

    QString result = h2_3->toString(".");

    QString expected =
        "1 Ut labore et dolore\n"
        "1.1 Et dolore magna\n"
        "1.1.1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}

void test_toString::oneParagraphHierarchy() {
    Paragraph root;
    Paragraph* h1 = new Paragraph("Lorem ipsum", &root, 1);
    root.appendChild(h1);

    Paragraph* h2_1 = new Paragraph("Dolor sit amet", h1, 2);
    Paragraph* h2_2 = new Paragraph("Consectetur adipiscing elit", h1, 2);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_2, 3);
    Paragraph* h2_3 = new Paragraph("Ut labore et dolore", h1, 2);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_3, 3);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);

    h1->appendChild(h2_1);
    h1->appendChild(h2_2);
    h2_2->appendChild(h3_1);
    h1->appendChild(h2_3);
    h2_3->appendChild(h3_2);
    h3_2->appendChild(h4_1);

    QString result = h4_1->toString(".");

    QString expected = "1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}

void test_toString::dotIsNotSeparator() {
    Paragraph root;
    Paragraph* h1 = new Paragraph("Lorem ipsum", &root, 1);
    root.appendChild(h1);

    Paragraph* h2_1 = new Paragraph("Dolor sit amet", h1, 2);
    Paragraph* h2_2 = new Paragraph("Consectetur adipiscing elit", h1, 2);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_2, 3);
    Paragraph* h2_3 = new Paragraph("Ut labore et dolore", h1, 2);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_3, 3);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);

    h1->appendChild(h2_1);
    h1->appendChild(h2_2);
    h2_2->appendChild(h3_1);
    h1->appendChild(h2_3);
    h2_3->appendChild(h3_2);
    h3_2->appendChild(h4_1);

    QString result = root.toString(",");

    QString expected =
        "1 Lorem ipsum\n"
        "1,1 Dolor sit amet\n"
        "1,2 Consectetur adipiscing elit\n"
        "1,2,1 Tempor incididunt\n"
        "1,3 Ut labore et dolore\n"
        "1,3,1 Et dolore magna\n"
        "1,3,1,1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}
