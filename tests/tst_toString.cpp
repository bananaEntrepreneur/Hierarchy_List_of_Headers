#include <QtTest>
#include <QCoreApplication>

#include "../main.h"

class testToString : public QObject {
    Q_OBJECT

private slots:
    void basicTest();
    void emptyHierarchy();
    void onlyDifferentLVL();
    void oneParagraphHierarchy();
    void dotIsNotSeparator();
    void manyChilds();
};

void testToString::basicTest() {
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

    QVector<int> numeration;
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

void testToString::manyChilds() {
    Paragraph root;

    Paragraph* h1_1 = new Paragraph("Excepteur sint", &root, 1);
    root.appendChild(h1_1);
    Paragraph* h2_1 = new Paragraph("Nulla pariatur", h1_1, 2);
    h1_1->appendChild(h2_1);

    Paragraph* h1_2 = new Paragraph("Lorem ipsum", &root, 1);
    Paragraph* h2_2 = new Paragraph("Dolor sit amet", h1_2, 2);
    Paragraph* h2_3 = new Paragraph("Consectetur adipiscing elit", h1_2, 2);
    Paragraph* h3_1 = new Paragraph("Tempor incididunt", h2_3, 3);
    Paragraph* h2_4 = new Paragraph("Ut labore et dolore", h1_2, 2);
    Paragraph* h3_2 = new Paragraph("Et dolore magna", h2_4, 3);
    Paragraph* h4_1 = new Paragraph("Ut enim ad minim", h3_2, 4);

    h1_2->appendChild(h2_2);
    h1_2->appendChild(h2_3);
    h1_2->appendChild(h2_4);
    h2_3->appendChild(h3_1);
    h2_4->appendChild(h3_2);
    h3_2->appendChild(h4_1);

    Paragraph* h1_3 = new Paragraph("Quis autem", &root, 1);
    root.appendChild(h1_3);

    QVector<int> numeration;
    QString result = root.toString(".");

    QString expected =
            "1 Excepteur sint"
            "1.1 Nulla pariatur"
            "2 Lorem ipsum"
            "2.1 Dolor sit amet"
            "2.2 Consectetur adipiscing elit"
            "2.2.1 Tempor incididunt"
            "2.3 Ut labore et dolore"
            "2.3.1 Et dolore magna"
            "2.3.1.1 Ut enim ad minim"
            "3 Quis autem";

    QCOMPARE(result, expected);
}

void testToString::emptyHierarchy() {
    Paragraph root;

    QVector<int> numeration;
    QString result = root.toString(".");

    QString expected = " ";

    QCOMPARE(result, expected);
}

void testToString::onlyDifferentLVL() {
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

    QVector<int> numeration;
    QString result = h2_3->toString(".");

    QString expected =
        "1 Ut labore et dolore\n"
        "1.1 Et dolore magna\n"
        "1.1.1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}

void testToString::oneParagraphHierarchy() {
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

    QVector<int> numeration;
    QString result = h4_1->toString(".");

    QString expected = "1 Ut enim ad minim\n";

    QCOMPARE(result, expected);
}

void testToString::dotIsNotSeparator() {
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

    QVector<int> numeration;
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

QTEST_MAIN(testToString)

//#include "tst_toString.moc"
