#include "functions.h"
#include "unit-tests/test_correct_createHierarchy.h"
#include "unit-tests/test_incorrect_createHierarchy.h"
#include "unit-tests/test_findParent.h"
#include "unit-tests/test_toString.h"
#include "unit-tests/test_createDomTreeFromFile.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // --- Запуск Unit-тестов ---
    // Проверяем, есть ли достаточное количество аргументов (имя_программы, "test", файл_вывода)
    if (argc > 2 && strcmp(argv[1], "test") == 0) {
        // Переменная для хранения общего результата тестов
        int overallResult = 0;

        // Выполняем все наборы тестов и объединяем их результаты с помощью побитового ИЛИ.
        // QTest::qExec возвращает 0 при успехе и ненулевое значение при провале.
        overallResult |= QTest::qExec(new test_correct_createHierarchy);
        overallResult |= QTest::qExec(new test_incorrect_createHierarchy);
        overallResult |= QTest::qExec(new test_toString);
        overallResult |= QTest::qExec(new test_findParent);
        overallResult |= QTest::qExec(new test_createDomTreeFromFile);

        // Завершаем программу с кодом, отражающим результат тестов.
        return overallResult;
    }

    // Множество для хранения ошибок
    QSet<Error> errors;

    // Создание DOM-дерева из входного HTML файла
    QDomDocument domTree = createDomTreeFromFile(argv[1], errors);

    // Если не обнаружено ошибок и удалось создать DOM-дерево
    if (errors.isEmpty() && !domTree.isNull()) {
        // Получаем корневой элемент документа (<html>)
        QDomElement docElem = domTree.documentElement();
        QDomElement bodyElement;

        // Находим элемент <body>
        if (!docElem.isNull())
            bodyElement = docElem.firstChildElement("body");

        // Создаем корневой узел для нашей иерархии Paragraph
        Paragraph root;

        // Если элемент <body> найден, строим иерархию заголовков
        if (!bodyElement.isNull())
            createHierarchyListOfHeaderTags(bodyElement, &root, errors);

        // Если и на этом этапе не возникло ошибок
        if (errors.isEmpty())
            // Записываем полученную иерархию в выходной файл
            printHierarchyListOfHeaderTagsToFile(argv[2], &root, errors);
    }

    // Если в процессе работы были обнаружены какие-либо ошибки
    if (!errors.isEmpty()) {
        // Выводим все собранные ошибки в выходной файл
        printErrors(argv[2], errors);
        // Завершаем программу с ошибкой
        return 1;
    }
    else {
        qInfo() << QString("Иерархия успешно сформирована и записана в файл: %1").arg(argv[2]);
        return 0;
    }
}
