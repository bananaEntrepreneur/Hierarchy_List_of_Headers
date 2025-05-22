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
    QDomElement rootDocElement = doc.documentElement();

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    Paragraph* LoremIpsumHeader = root.getChildHierarchy()->takeFirst(); // <h1>Lorem ispsum</h1>
    QCOMPARE(LoremIpsumHeader->getLevel(), 1);
    QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");
    QVERIFY(root.getChildHierarchy()->isEmpty());

    QList<Paragraph*>* LoremIpsumChildHierarchy = LoremIpsumHeader->getChildHierarchy();

    Paragraph* DolorSitHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Dolor sit amet</h2>
    QCOMPARE(DolorSitHeader->getLevel(), 2);
    QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");

    Paragraph* Consectetur = LoremIpsumChildHierarchy->takeFirst(); // <h2>Consectetur adipiscing elit</h2>
    QCOMPARE(Consectetur->getLevel(), 2);
    QCOMPARE(Consectetur->getText(), "Consectetur adipiscing elit");

    Paragraph* Tempor = Consectetur->getChildHierarchy()->takeFirst(); // <h3>Tempor incididunt</h3>
    QCOMPARE(Tempor->getLevel(), 3);
    QCOMPARE(Tempor->getText(), "Tempor incididunt");
    QVERIFY(Consectetur->getChildHierarchy()->isEmpty());

    Paragraph* Utlabore = LoremIpsumChildHierarchy->takeFirst(); // <h2>Ut labore et dolore</h2>
    QCOMPARE(Utlabore->getLevel(), 2);
    QCOMPARE(Utlabore->getText(), "Ut labore et dolore");
    QVERIFY(LoremIpsumChildHierarchy->isEmpty());

    Paragraph* Etdolore = Utlabore->getChildHierarchy()->takeFirst(); // <h3>Et dolore magna</h3>
    QCOMPARE(Etdolore->getLevel(), 3);
    QCOMPARE(Etdolore->getText(), "Et dolore magna");
    QVERIFY(Utlabore->getChildHierarchy()->isEmpty());

    Paragraph* Utenim = Etdolore->getChildHierarchy()->takeFirst(); // <h4>Ut enim ad minim</h4>
    QCOMPARE(Utenim->getLevel(), 4);
    QCOMPARE(Utenim->getText(), "Ut enim ad minim");
    QVERIFY(Etdolore->getChildHierarchy()->isEmpty());
    QVERIFY(Utenim->getChildHierarchy()->isEmpty());

    QVERIFY(errors.isEmpty());
}

QTEST_MAIN(correct_tst_createHierarchy)

//#include "correct_tst_createHierarchy.moc"
