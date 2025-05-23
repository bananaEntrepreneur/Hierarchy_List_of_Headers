#include "main.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile inputFile(argv[1]);

    inputFile.open(QIODevice::ReadOnly);

    QDomDocument domTree;
    QString errorMesaage;
    int errorLine, errorColumn;

    domTree.setContent(&inputFile, &errorMesaage, &errorLine, &errorColumn);

    inputFile.close();

    QDomElement bodyElement = domTree.firstChildElement("body");

    Paragraph root;

    QSet<Error> errors;

    createHierarchyListOfHeaderTags(bodyElement, &root, errors);

    QFile outputFile(argv[2]);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    return a.exec();
}
