#include <QtTest>
#include <QCoreApplication>

#include "../main.h"

class testGetString : public QObject {
    Q_OBJECT

private slots:
    void basicTest();
};

void testGetString::basicTest() {
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
    QString result = root.getString(".", numeration);

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

QTEST_MAIN(testGetString)

#include "tst_getString.moc"
