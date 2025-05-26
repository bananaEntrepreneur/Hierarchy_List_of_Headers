#include "main.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSet<Error> errors;

    QFile inputFile(argv[1]);

    if (!inputFile.open(QIODevice::ReadOnly)) {
        Error fileError;
        fileError.setType(ErrorType::fileError);
        fileError.setErrorInputPath(argv[1]);
        errors.insert(fileError);
    }

    QDomDocument domTree;
    QString errorMesaage;
    int errorLine, errorColumn;

    domTree.setContent(&inputFile, &errorMesaage, &errorLine, &errorColumn);

    inputFile.close();

    QDomElement bodyElement = domTree.firstChildElement("body");

    Paragraph root;

    createHierarchyListOfHeaderTags(bodyElement, &root, errors);

    QFile outputFile(argv[2]);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return 1;

    return a.exec();
}
