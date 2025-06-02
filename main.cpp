#include "functions.h"
#include "test_correct_createHierarchy.h"
#include "test_incorrect_createHierarchy.h"
#include "test_findParent.h"
#include "test_toString.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSet<Error> errors;

    QFile inputFile(argv[1]);

    if (!inputFile.open(QIODevice::ReadOnly)) {
        Error fileError;
        fileError.setType(ErrorType::fileError);
        fileError.setErrorInputPath(argv[1]);
        fileError.setErrorAttrName("input_non_existent");
        errors.insert(fileError);
    }

    QDomDocument domTree;
    QString errorMessage;
    int errorLine, errorColumn;

    if (inputFile.isOpen()) {
        if (!domTree.setContent(&inputFile, true, &errorMessage, &errorLine, &errorColumn)) {
            Error parseError;
            parseError.setType(ErrorType::XMLerror);
            parseError.setErrorInputPath(argv[1]);
            parseError.setErrorAttrName("xml_parse_error: " + errorMessage);
            errors.insert(parseError);
        }
        inputFile.close();
    }

    if (errors.isEmpty() || !errors.contains(Error())) {
        QDomElement docElem = domTree.documentElement();
        QDomElement bodyElement;

        if (!docElem.isNull()) {
            bodyElement = docElem.firstChildElement("body");
            if (bodyElement.isNull() && docElem.tagName().toLower() == "body") {
                bodyElement = docElem;
            }
            else if (bodyElement.isNull()) {
                 QDomNodeList bodyList = docElem.elementsByTagName("body");
                 if (bodyList.count() > 0) {
                     bodyElement = bodyList.at(0).toElement();
                 }
            }
        }

        Paragraph root;

        if (!bodyElement.isNull()) {
            createHierarchyListOfHeaderTags(bodyElement, &root, errors);
        }
        else if (errors.count() == 0) {
            bool noHeaderErrorExists = false;
            for(const Error& err : errors) {
                if(err.getErrorType() == ErrorType::noHeaderTagsError) {
                    noHeaderErrorExists = true;
                }
            }
            if (!noHeaderErrorExists) {
                Error noBodyError;
                noBodyError.setType(ErrorType::noTagError);
                noBodyError.setErrorTagName("body");
                noBodyError.setErrorAttrName("not_found");
                errors.insert(noBodyError);
            }
        }

        if (errors.isEmpty()) {
            QFile outputFile(argv[2]);
            if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QString textImplementationOfHierarchy = root.toString(".");
                QTextStream out(&outputFile);
                out.setCodec("UTF-8");
                out << textImplementationOfHierarchy;
                outputFile.close();
            } else {
                Error outputError;
                outputError.setType(ErrorType::fileError);
                outputError.setErrorOutputPath(argv[2]);
                outputError.setErrorAttrName("output_cannot_create");
                errors.insert(outputError);
            }
        }
    }

    // --- Тесты ---
    //QTest::qExec(new test_correct_createHierarchy);
    //QTest::qExec(new test_incorrect_createHierarchy);
    //QTest::qExec(new test_toString);
    //QTest::qExec(new test_findParent);

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
