#include <QtTest>
#include <QCoreApplication>

#include "../main.h"
#include "../functions.h"

class tst_findParentTest : public QObject {
    Q_OBJECT

private slots:
    void currentLVLbiggerThenPrevious();
    void currentLVLequalPrevious();
    void currentLVLlessThenPrevious();
    void currentLVLlessThenPreviousANDmanySameParagraphs();
};

void tst_findParentTest::currentLVLbiggerThenPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 3);

    QCOMPARE(result, &B);
}

void tst_findParentTest::currentLVLequalPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 2);

    QCOMPARE(result, &A);
}

void tst_findParentTest::currentLVLlessThenPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 1);

    QCOMPARE(result, root);
}

void tst_findParentTest::currentLVLlessThenPreviousANDmanySameParagraphs() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);
    Paragraph C("C", &A, 2);
    A.appendChild(&C);
    Paragraph D("D", &C, 3);
    C.appendChild(&D);
    Paragraph E("E", &root, 1);
    root.appendChild(&E);
    Paragraph F("F", &E, 2);
    E.appendChild(&F);
    Paragraph G("G", &E, 2);
    E.appendChild(&G);
    Paragraph H("H", &G, 3);
    G.appendChild(&H);

    Paragraph* result = findParentForParagraph(&B, 2);

    QCOMPARE(result, &root);
}

QTEST_MAIN(tst_findParentTest)

//#include "tst_findParentForParagraph.moc"
