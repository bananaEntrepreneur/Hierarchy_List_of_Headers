#include <QtTest>
#include <QCoreApplication>

#include "../main.h"

class incorrect_tst_createHierarchy : public QObject {
    Q_OBJECT

private slots:
    void noBodyChilds();
    void noHeaders();
};

void incorrect_tst_createHierarchy::noBodyChilds() {
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

    QCOMPARE(false, errors.isEmpty());

    QList<Error> errorsList = errors.values();

    Error noBodyChildsError = errorsList.takeFirst();

    QCOMPARE(noBodyChildsError.getErrorType(), ErrorType::noTagError);

    QCOMPARE(noBodyChildsError.getErrorType(), "any");
}

void incorrect_tst_createHierarchy::noHeaders() {
    QString html =
            "<html>"
            "<body>"
            "<img src=URL />"
            "<p>Lorem ipsum</p>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    QCOMPARE(false, errors.isEmpty());

    QList<Error> errorsList = errors.values();

    Error noHeadersError = errorsList.takeFirst();

    QCOMPARE(noHeadersError.getErrorType(), ErrorType::noHeaderTagsError);
    QCOMPARE(noHeadersError.getErrorTagName(), " ");
}
