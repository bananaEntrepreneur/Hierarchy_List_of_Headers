#include "test_findParent.h"

test_findParent::test_findParent(QObject *parent)
    : QObject{parent}
{}

void test_findParent::currentLVLbiggerThenPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 3);

    QCOMPARE(result, &B);
}

void test_findParent::currentLVLequalPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 2);

    QCOMPARE(result, &A);
}

void test_findParent::currentLVLlessThenPrevious() {
    Paragraph root;
    Paragraph A("A", &root, 1);
    root.appendChild(&A);
    Paragraph B("B", &A, 2);
    A.appendChild(&B);

    Paragraph* result = findParentForParagraph(&B, 1);

    QCOMPARE(result, &root);
}

void test_findParent::currentLVLlessThenPreviousANDmanySameParagraphs() {
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

    Paragraph* result = findParentForParagraph(&H, 1);

    QCOMPARE(result, &root);
}
