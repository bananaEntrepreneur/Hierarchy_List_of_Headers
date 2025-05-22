#include <QtTest>
#include <QCoreApplication>

#include "../main.h"

class correct_tst_createHierarchy : public QObject
{
    Q_OBJECT

public:
    correct_tst_createHierarchy();
    ~correct_tst_createHierarchy();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void basicTest();
};

correct_tst_createHierarchy::correct_tst_createHierarchy()
{

}

correct_tst_createHierarchy::~correct_tst_createHierarchy()
{

}

void correct_tst_createHierarchy::initTestCase()
{

}

void correct_tst_createHierarchy::cleanupTestCase()
{

}

void correct_tst_createHierarchy::basicTest()
{
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
    QDomElement rootElement = doc.documentElement();

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootElement, &root, errors);

    // Проверка корня
    const auto& topHeaders = root.getChild();
    QCOMPARE(topHeaders.size(), 1);
    QCOMPARE(topHeaders[0]->getText(), QString("Lorem ispsum")); // <h1>

    const auto& h1Children = topHeaders[0]->getChildren();
    QCOMPARE(h1Children.size(), 3);

    QCOMPARE(h1Children[0]->getText(), QString("Dolor sit amet"));          // <h2>
    QCOMPARE(h1Children[1]->getText(), QString("Consectetur adipiscing elit")); // <h2>
    QCOMPARE(h1Children[2]->getText(), QString("Ut labore et dolore"));     // <h2>

    const auto& h2_1 = h1Children[1]->getChildren(); // <h3> под "Consectetur..."
    QCOMPARE(h2_1.size(), 1);
    QCOMPARE(h2_1[0]->getText(), QString("Tempor incididunt")); // <h3>

    const auto& h2_2 = h1Children[2]->getChildren(); // <h3> под "Ut labore..."
    QCOMPARE(h2_2.size(), 1);
    QCOMPARE(h2_2[0]->getText(), QString("Et dolore magna")); // <h3>

    const auto& h3_2 = h2_2[0]->getChildren(); // <h4> под "Et dolore magna"
    QCOMPARE(h3_2.size(), 1);
    QCOMPARE(h3_2[0]->getText(), QString("Ut enim ad minim")); // <h4>

    QVERIFY(errors.isEmpty());
}


QTEST_MAIN(correct_tst_createHierarchy)

//#include "tst_findParentForParagraph.moc"
