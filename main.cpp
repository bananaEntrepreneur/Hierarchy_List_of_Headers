#include "functions.h"
#include "unit-tests/test_correct_createHierarchy.h"
#include "unit-tests/test_incorrect_createHierarchy.h"
#include "unit-tests/test_findParent.h"
#include "unit-tests/test_toString.h"
#include "unit-tests/test_createDomTreeFromFile.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSet<Error> errors;

    QDomDocument domTree = createDomTreeFromFile(argv[1], errors);

    if (errors.isEmpty() && !domTree.isNull()) {
        QDomElement docElem = domTree.documentElement();
        QDomElement bodyElement;

        QDomElement scriptElement = bodyElement.firstChildElement("script");

        if (!docElem.isNull())
            bodyElement = docElem.firstChildElement("body");

        Paragraph root;

        if (!bodyElement.isNull()) {
            createHierarchyListOfHeaderTags(bodyElement, &root, errors);
        }

        if (errors.isEmpty())
            printHierarchyListOfHeaderTagsToFile(argv[2], &root, errors);
    }

    // --- Тесты ---
    //QTest::qExec(new test_correct_createHierarchy);
    //QTest::qExec(new test_incorrect_createHierarchy);
    //QTest::qExec(new test_toString);
    //QTest::qExec(new test_findParent);
    //QTest::qExec(new test_createDomTreeFromFile);

    if (!errors.isEmpty()) {
        for(const Error& err : qAsConst(errors)) {
            QString msg = err.generateErrorMessage();
            qDebug().noquote() << msg;
        }
        return 1;
    }
    else {
        qInfo() << QString("Иерархия успешно сформирована и записана в файл: %1").arg(argv[1]) << Qt::endl;
        return 0;
    }
}
