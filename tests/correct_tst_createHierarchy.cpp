#include <QtTest>
#include <QCoreApplication>

#include "../main.h"
#include "../functions.h"

class correct_tst_createHierarchy : public QObject {
    Q_OBJECT

private slots:
    void basicTest();
    void manyChildsWithSameLVL();
    void manyTagsWithVariousLVL();
    void manyTagsInsideSectionAndArticle();
    void headerLikeTags();
    void plaintTextBetweenHeaders();
    void textLikeHeaderInTagAttribute();
    void textLikeHeader();
};

void correct_tst_createHierarchy::basicTest() {
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
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");

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

void correct_tst_createHierarchy::manyChildsWithSameLVL() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<h2>Dolor sit amet</h2>"
            "<h2>Consectetur adipiscing elit</h2>"
            "<h2>Sed do eiusmod tempor</h2>"
            "<h2>Ut labore et dolore</h2>"
            "<h2>Ut enim ad minim veniam</h2>"
            "<h2>Quis nostrud exercitation</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

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
    QCOMPARE(LoremIpsumHeader->getText(), "DolorSitHeader");

    Paragraph* ConsecteturHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Consectetur adipiscing elit</h2>
    QCOMPARE(ConsecteturHeader->getLevel(), 2);
    QCOMPARE(ConsecteturHeader->getText(), "Consectetur adipiscing elit");

    Paragraph* SeddoHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Sed do eiusmod tempor</h2>
    QCOMPARE(SeddoHeader->getLevel(), 2);
    QCOMPARE(SeddoHeader->getText(), "Sed do eiusmod tempor");

    Paragraph* UtlaboreHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Ut labore et dolore</h2>
    QCOMPARE(UtlaboreHeader->getLevel(), 2);
    QCOMPARE(UtlaboreHeader->getText(), "Ut labore et dolore");

    Paragraph* UtenimHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Ut enim ad minim veniam</h2>
    QCOMPARE(UtenimHeader->getLevel(), 2);
    QCOMPARE(UtenimHeader->getText(), "Ut enim ad minim veniam");

    Paragraph* QuisnostrudHeader = LoremIpsumChildHierarchy->takeFirst(); // <h2>Quis nostrud exercitation</h2>
    QCOMPARE(QuisnostrudHeader->getLevel(), 2);
    QCOMPARE(QuisnostrudHeader->getText(), "Quis nostrud exercitation");
    QVERIFY(LoremIpsumChildHierarchy->isEmpty());

    QVERIFY(errors.isEmpty());
}

void correct_tst_createHierarchy::manyTagsWithVariousLVL() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<h2>Dolor sit amet</h2>"
            "<h3>Consectetur adipiscing elit</h3>"
            "<h4>Sed do eiusmod tempor</h4>"
            "<h5>Ut labore et dolore</h5>"
            "<h6>Ut enim ad minim veniam</h6>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");

    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    Paragraph* LoremIpsumHeader = root.getChildHierarchy()->takeFirst(); // <h1>Lorem ispsum</h1>
    QVERIFY(root.getChildHierarchy()->isEmpty());
    QCOMPARE(LoremIpsumHeader->getLevel(), 1);
    QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");

    Paragraph* DolorSitHeader = LoremIpsumHeader->getChildHierarchy()->takeFirst(); // <h2>Dolor sit amet</h2>
    QVERIFY(LoremIpsumHeader->getChildHierarchy()->isEmpty());
    QCOMPARE(DolorSitHeader->getLevel(), 2);
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");

    Paragraph* Consectetur = DolorSitHeader->getChildHierarchy()->takeFirst(); // <h3>Consectetur adipiscing elit</h3>
    QVERIFY(DolorSitHeader->getChildHierarchy()->isEmpty());
    QCOMPARE(Consectetur->getLevel(), 3);
    QCOMPARE(Consectetur->getText(), "Consectetur adipiscing elit");

    Paragraph* Seddo = Consectetur->getChildHierarchy()->takeFirst(); // <h4>Sed do eiusmod tempor</h4>
    QVERIFY(Consectetur->getChildHierarchy()->isEmpty());
    QCOMPARE(Seddo->getLevel(), 4);
    QCOMPARE(Seddo->getText(), "Sed do eiusmod tempor");

    Paragraph* Utlabore = Seddo->getChildHierarchy()->takeFirst(); // <h5>Ut labore et dolore</h5>
    QVERIFY(Seddo->getChildHierarchy()->isEmpty());
    QCOMPARE(Utlabore->getLevel(), 5);
    QCOMPARE(Utlabore->getText(), "Ut labore et dolore");

    Paragraph* Etdolore = Utlabore->getChildHierarchy()->takeFirst(); // <h6>Ut enim ad minim veniam</h6>
    QVERIFY(Utlabore->getChildHierarchy()->isEmpty());
    QCOMPARE(Etdolore->getLevel(), 6);
    QCOMPARE(Etdolore->getText(), "Ut enim ad minim veniam");
    QVERIFY(Etdolore->getChildHierarchy()->isEmpty());

    QVERIFY(errors.isEmpty());
}

void correct_tst_createHierarchy::manyTagsInsideSectionAndArticle() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<h2>Dolor sit amet</h2>"
            "<h3>Consectetur adipiscing elit</h3>"
            "<h4>Sed do eiusmod tempor</h4>"
            "<h5>Ut labore et dolore</h5>"
            "<h6>Ut enim ad minim veniam</h6>"
            "<section>"
            "<h1>Lorem ispsum</h1>"
            "<h2>Dolor sit amet</h2>"
            "<h3>Consectetur adipiscing elit</h3>"
            "<h4>Sed do eiusmod tempor</h4>"
            "<h5>Ut labore et dolore</h5>"
            "<h6>Ut enim ad minim veniam</h6>"
            "</section>"
            "<article>"
            "<h1>Lorem ispsum</h1>"
            "<h2>Dolor sit amet</h2>"
            "<h3>Consectetur adipiscing elit</h3>"
            "<h4>Sed do eiusmod tempor</h4>"
            "<h5>Ut labore et dolore</h5>"
            "<h6>Ut enim ad minim veniam</h6>"
            "</article>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");


    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    for (int i = 0; i < 3; i++)
    {
        Paragraph* LoremIpsumHeader = root.getChildHierarchy()->takeFirst(); // <h1>Lorem ispsum</h1>
        if (i == 2)
            QVERIFY(root.getChildHierarchy()->isEmpty());
        QCOMPARE(LoremIpsumHeader->getLevel(), 1);
        QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");

        Paragraph* DolorSitHeader = LoremIpsumHeader->getChildHierarchy()->takeFirst(); // <h2>Dolor sit amet</h2>
        QVERIFY(LoremIpsumHeader->getChildHierarchy()->isEmpty());
        QCOMPARE(DolorSitHeader->getLevel(), 2);
        QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");

        Paragraph* Consectetur = DolorSitHeader->getChildHierarchy()->takeFirst(); // <h3>Consectetur adipiscing elit</h3>
        QVERIFY(DolorSitHeader->getChildHierarchy()->isEmpty());
        QCOMPARE(Consectetur->getLevel(), 3);
        QCOMPARE(Consectetur->getText(), "Consectetur adipiscing elit");

        Paragraph* Seddo = Consectetur->getChildHierarchy()->takeFirst(); // <h4>Sed do eiusmod tempor</h4>
        QVERIFY(Consectetur->getChildHierarchy()->isEmpty());
        QCOMPARE(Seddo->getLevel(), 4);
        QCOMPARE(Seddo->getText(), "Sed do eiusmod tempor");

        Paragraph* Utlabore = Seddo->getChildHierarchy()->takeFirst(); // <h5>Ut labore et dolore</h5>
        QVERIFY(Seddo->getChildHierarchy()->isEmpty());
        QCOMPARE(Utlabore->getLevel(), 5);
        QCOMPARE(Utlabore->getText(), "Ut labore et dolore");

        Paragraph* Etdolore = Utlabore->getChildHierarchy()->takeFirst(); // <h6>Ut enim ad minim veniam</h6>
        QVERIFY(Utlabore->getChildHierarchy()->isEmpty());
        QCOMPARE(Etdolore->getLevel(), 6);
        QCOMPARE(Etdolore->getText(), "Ut enim ad minim veniam");
        QVERIFY(Etdolore->getChildHierarchy()->isEmpty());

        QVERIFY(errors.isEmpty());
    }
}

void correct_tst_createHierarchy::headerLikeTags() {
    QString html =
        "<html>"
        "<body>"
        "<hr/>"
        "<h1>Lorem ispsum</h1>"
        "<h2>Dolor sit amet</h2>"
        "<h2>Consectetur adipiscing elit</h2>"
        "<h3>Tempor incididunt</h3>"
        "<h2>Ut labore et dolore</h2>"
        "<h3>Et dolore magna</h3>"
        "<h4>Ut enim ad minim</h4>"
        "<hr/>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");


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
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");

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

void correct_tst_createHierarchy::plaintTextBetweenHeaders() {
    QString html =
        "<html>"
        "<body>"
        "<h1>Lorem ispsum</h1>"
        "<p>С другой стороны укрепление и развитие структуры обеспечивает широкому кругу (специалистов) участие в формировании системы обучения кадров, соответствует насущным потребностям.</p>"
        "<h2>Dolor sit amet</h2>"
        "<p> Товарищи! консультация с широким активом требуют от нас анализа систем массового участия.</p>"
        "<h2>Consectetur adipiscing elit</h2>"
        "<p> Товарищи! постоянное информационно-пропагандистское обеспечение нашей деятельности обеспечивает широкому кругу (специалистов) участие в формировании новых предложений.</p>"
        "<h3>Tempor incididunt</h3>"
        "<p> Не следует, однако забывать, что консультация с широким активом требуют определения и уточнения соответствующий условий активизации.</p>"
        "<h2>Ut labore et dolore</h2>"
        "<p>С другой стороны начало повседневной работы по формированию позиции в значительной степени обуславливает создание систем массового участия</p>"
        "<h3>Et dolore magna</h3>"
        "<p> Разнообразный и богатый опыт постоянный количественный рост и сфера нашей активности играет важную роль в формировании дальнейших направлений развития.</p>"
        "<h4>Ut enim ad minim</h4>"
        "</body>"
        "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");


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
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");

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

void correct_tst_createHierarchy::textLikeHeaderInTagAttribute() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<img src= “h1.png”/>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");


    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    Paragraph* LoremIpsumHeader = root.getChildHierarchy()->takeFirst(); // <h1>Lorem ispsum</h1>
    QCOMPARE(LoremIpsumHeader->getLevel(), 1);
    QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");
    QVERIFY(root.getChildHierarchy()->isEmpty());

    Paragraph* DolorSitHeader = LoremIpsumHeader->getChildHierarchy()->takeFirst(); // <h2>Dolor sit amet</h2>
    QVERIFY(LoremIpsumHeader->getChildHierarchy()->isEmpty());
    QCOMPARE(DolorSitHeader->getLevel(), 2);
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");
    QVERIFY(DolorSitHeader->getChildHierarchy()->isEmpty());

    QVERIFY(errors.isEmpty());
}

void correct_tst_createHierarchy::textLikeHeader() {
    QString html =
            "<html>"
            "<body>"
            "<h1>Lorem ispsum</h1>"
            "<p> a <h1 </p>"
            "<h2>Dolor sit amet</h2>"
            "</body>"
            "</html>";

    QDomDocument doc;
    QVERIFY(doc.setContent(html));
    QDomElement rootDocElement = doc.documentElement().firstChildElement("body");


    Paragraph root;
    QSet<Error> errors;

    createHierarchyListOfHeaderTags(rootDocElement, &root, errors);

    Paragraph* LoremIpsumHeader = root.getChildHierarchy()->takeFirst(); // <h1>Lorem ispsum</h1>
    QCOMPARE(LoremIpsumHeader->getLevel(), 1);
    QCOMPARE(LoremIpsumHeader->getText(), "Lorem ispsum");
    QVERIFY(root.getChildHierarchy()->isEmpty());

    Paragraph* DolorSitHeader = LoremIpsumHeader->getChildHierarchy()->takeFirst(); // <h2>Dolor sit amet</h2>
    QVERIFY(LoremIpsumHeader->getChildHierarchy()->isEmpty());
    QCOMPARE(DolorSitHeader->getLevel(), 2);
    QCOMPARE(DolorSitHeader->getText(), "Dolor sit amet");
    QVERIFY(DolorSitHeader->getChildHierarchy()->isEmpty());

    QVERIFY(errors.isEmpty());
}

QTEST_MAIN(correct_tst_createHierarchy)

//#include "correct_tst_createHierarchy.moc"
