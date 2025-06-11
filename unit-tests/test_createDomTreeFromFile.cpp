#include "test_createDomTreeFromFile.h"

test_createDomTreeFromFile::test_createDomTreeFromFile(QObject *parent)
    : QObject{parent}
{}

void test_createDomTreeFromFile::initTestCase()
{
    QTemporaryDir tempDir;
    if (tempDir.isValid()) {
        tempDirPath = tempDir.path();
        qDebug() << "Временная директория для тестов:" << tempDirPath;
    } else {
        qWarning() << "Не удалось создать временную директорию для тестов.";
    }
    tempDirPath = QDir::currentPath() + "/test_temp_dir_file_ops";
    QDir dir(tempDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    qDebug() << "Используется временная директория для тестов:" << tempDirPath;
}

void test_createDomTreeFromFile::cleanupTestCase()
{
    QDir dir(tempDirPath);
    if (dir.exists()) {
        dir.removeRecursively();
        qDebug() << "Очищена временная директория:" << tempDirPath;
    }
}

void test_createDomTreeFromFile::validFile()
{
    QString filePath = tempDirPath + "/valid.html";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "<html><body><h1>Title</h1></body></html>";
        file.close();
    } else {
        QFAIL("Не удалось создать временный файл для теста validFile");
    }

    QSet<Error> errors;
    QDomDocument doc = createDomTreeFromFile(filePath, errors);

    QVERIFY2(errors.isEmpty(), qPrintable("Ошибки для валидного файла не должны были быть найдены. Ошибки: " + (errors.isEmpty() ? "Нет" : errors.values().first().generateErrorMessage())));
    QVERIFY2(!doc.isNull(), "DOM document не должне быть нулевым для валидного файла.");
    QVERIFY2(doc.documentElement().tagName().toLower() == "html", "Корневой элемент должен быть <html>.");
    QVERIFY2(doc.documentElement().firstChildElement("body").firstChildElement("h1").text() == "Title", "Контент тега H1 потерян.");

    QFile::remove(filePath);
}

void test_createDomTreeFromFile::nonExistentFile()
{
    QString filePath = tempDirPath + "/non_existent_file.html";
    if (QFile::exists(filePath)) {
        QFile::remove(filePath);
    }

    QSet<Error> errors;
    QDomDocument doc = createDomTreeFromFile(filePath, errors);

    QVERIFY2(!errors.isEmpty(), "Ошибка должна быть обнаружена");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for(const Error& err : errors){
        if(err.getErrorType() == ErrorType::fileError &&
           (err.getErrorAttrName() == "input_cannot_open")  ){
            foundError = true;
        }
    }
    QVERIFY2(foundError, "Ошибки fileError (input_non_existent) не найдена.");
    QVERIFY2(doc.isNull(), "DOM документ должен быть нулевым для несуществующего файла.");
}

void test_createDomTreeFromFile::emptyFile()
{
    QString filePath = tempDirPath + "/empty.html";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.close();
    } else {
        QFAIL("Не удаётся создать пустой файл для теста");
    }

    QSet<Error> errors;
    QDomDocument doc = createDomTreeFromFile(filePath, errors);

    QVERIFY2(!errors.isEmpty(), "Должна быть найдена ошибка парсинга XML.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for(const Error& err : errors){
        if(err.getErrorType() == ErrorType::XMLerror ) {
            foundError = true;
        }
    }
    QVERIFY2(foundError, "Ошибка XML для теста с пустым файлом не была обнаружена.");

    QFile::remove(filePath);
}

void test_createDomTreeFromFile::badXmlParsing()
{
    QString filePath = tempDirPath + "/badXmlParsing.html";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "<html><body><h1>Title</h1</body></html>"; // Незакрытый h1, нет закрывающего </html>
        file.close();
    } else {
        QFAIL("Не удалось создать временный файл для теста badXmlParsing");
    }

    QSet<Error> errors;
    QDomDocument doc = createDomTreeFromFile(filePath, errors);

    QVERIFY2(!errors.isEmpty(), "Должна быть найдена ошибка плохого парсинга XML.");
    if (errors.isEmpty()) return;

    bool foundError = false;
    for(const Error& err : errors){
        if(err.getErrorType() == ErrorType::XMLerror){
            QVERIFY2(err.getErrorAttrName().contains("xml_parse_error"), "Поле AttrName должно показывать ошибку парсера.");
            foundError = true;
        }
    }
    QVERIFY2(foundError, "Не найдена ошибка плохого парсинга XML.");
    QVERIFY2(doc.isNull() || !doc.documentElement().isNull(), "doc может быть не null, но содержать только часть до ошибки или быть невалидным.");

    QFile::remove(filePath);
}

void test_createDomTreeFromFile::scriptTag()
{
    QString filePath = tempDirPath + "/with_script.html";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "<html><body><script>var x=1;</script><h1>Title</h1></body></html>";
        file.close();
    } else {
        QFAIL("Не удалось создать временный файл для теста scriptTag");
    }

    QSet<Error> errors;
    QDomDocument doc = createDomTreeFromFile(filePath, errors);

    bool foundScriptError = false;
    for(const Error& err : errors){
        if(err.getErrorType() == ErrorType::htmlStructureError && err.getErrorTagName() == "script"){
            foundScriptError = true;
        }
    }
    QVERIFY2(foundScriptError, "Ошибка для тега <script> не была найдена.");

    QVERIFY2(!doc.isNull(), "В любом случае, DOM должен быть построен корректно");

    QFile::remove(filePath);
}
