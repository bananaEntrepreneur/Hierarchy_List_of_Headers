#ifndef TEST_CORRECT_CREATEHIERARCHY_H
#define TEST_CORRECT_CREATEHIERARCHY_H

#include "../main.h"
#include "../paragraph.h"
#include "../functions.h"

class test_correct_createHierarchy : public QObject {
    Q_OBJECT
public:
    explicit test_correct_createHierarchy(QObject *parent = nullptr);
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

#endif // TEST_CORRECT_CREATEHIERARCHY_H
