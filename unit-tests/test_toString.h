#ifndef TEST_TOSTRING_H
#define TEST_TOSTRING_H

#include "../main.h"
#include "../paragraph.h"

class test_toString : public QObject {
    Q_OBJECT
public:
    explicit test_toString(QObject *parent = nullptr);
private slots:
    void basicTest();
    void emptyHierarchy();
    void onlyDifferentLVL();
    void oneParagraphHierarchy();
    void dotIsNotSeparator();
    void manyChilds();
};

#endif // TEST_TOSTRING_H
