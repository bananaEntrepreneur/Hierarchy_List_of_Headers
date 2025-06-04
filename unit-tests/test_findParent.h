#ifndef TEST_FINDPARENT_H
#define TEST_FINDPARENT_H

#include "../main.h"
#include "../functions.h"
#include "../paragraph.h"

class test_findParent : public QObject {
    Q_OBJECT
public:
    explicit test_findParent(QObject *parent = nullptr);
private slots:
    void currentLVLbiggerThenPrevious();
    void currentLVLequalPrevious();
    void currentLVLlessThenPrevious();
    void currentLVLlessThenPreviousANDmanySameParagraphs();
};

#endif // TEST_FINDPARENT_H
