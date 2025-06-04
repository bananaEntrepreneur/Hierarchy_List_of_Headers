#ifndef TEST_CREATEDOMTREEFROMFILE_H
#define TEST_CREATEDOMTREEFROMFILE_H

#include "../main.h"
#include "../functions.h"

class test_createDomTreeFromFile : public QObject {
    Q_OBJECT
public:
    explicit test_createDomTreeFromFile(QObject *parent = nullptr);
private:
    QString tempDirPath;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void validFile();
    void nonExistentFile();
    void emptyFile();
    void badXmlParsing();
    void scriptTag();
};

#endif // TEST_CREATEDOMTREEFROMFILE_H
