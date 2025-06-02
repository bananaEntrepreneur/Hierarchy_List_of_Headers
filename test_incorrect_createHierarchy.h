#ifndef TEST_INCORRECT_CREATEHIERARCHY_H
#define TEST_INCORRECT_CREATEHIERARCHY_H

#include "main.h"
#include "paragraph.h"
#include "functions.h"

class test_incorrect_createHierarchy : public QObject {
    Q_OBJECT
public:
    explicit test_incorrect_createHierarchy(QObject *parent = nullptr);
private slots:
    void noBodyChilds();
    void noHeaders();
    void headerOutsideBody();
    void firstHeaderNotH1();
    void emptyHeaderTag();
    void tooManyH1InBody();
    void tooManyH1InSection();
    void sectionInSection();
    void articleInArticle();
    void sectionInArticle();
    void articleInSection();
    void headerHierarchySkipLevel();
    void headerContainsOtherTags();
    void firstHeaderInSectionNotH1();
    //void scriptTagContent();
};

#endif // TEST_INCORRECT_CREATEHIERARCHY_H
