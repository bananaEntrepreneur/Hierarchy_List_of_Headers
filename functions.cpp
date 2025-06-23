#include "functions.h"

void createHierarchyListOfHeaderTags(QDomElement& bodyElement, Paragraph* root, QSet<Error>& errors) {
    // 1. Проверка заголовков вне body
    QDomElement htmlElement = bodyElement.parentNode().toElement();
    if (!htmlElement.isNull() && htmlElement.tagName().toLower() == "html") {
        QDomElement headElement = htmlElement.firstChildElement("head");
        if (!headElement.isNull()) {
            for (int i = 1; i <= 6; ++i) {
                QString tagName = "h" + QString::number(i);
                if (headElement.elementsByTagName(tagName).count() > 0) {
                    Error outsideError;
                    outsideError.setType(ErrorType::htmlStructureError);
                    outsideError.setErrorTagName(tagName);
                    outsideError.setErrorAttrName("outside_body");
                    errors.insert(outsideError);
                }
            }
        }
    }

    // 2. Рекурсивное построение иерархии заголовочных тегов начиная с <body>
    createHierarchyRecursive(bodyElement, root, errors);

    // 3. Были ли найдены заголовки во всем документе.
    if (root->getChildHierarchy()->isEmpty()) {
        bool noHeaderErrorExists = false;
        for (const Error& err : qAsConst(errors)) {
            if (err.getErrorType() == ErrorType::noHeaderTagsError) {
                noHeaderErrorExists = true;
            }
        }
        // Добавляем ошибку, только если она еще не была добавлена
        if (!noHeaderErrorExists) {
            Error noHeader;
            noHeader.setType(ErrorType::noHeaderTagsError);
            errors.insert(noHeader);
        }
    }
}

Paragraph* handleHeader(
    QDomElement& headerElement,
    Paragraph* contextNode,
    QSet<Error>& errors,
    int& previousHeaderLevel,
    bool& h1FoundInScope,
    bool& firstHeaderProcessed)
{
    QString tagName = headerElement.tagName().toLower();
    QString parentScopeName = headerElement.parentNode().toElement().tagName().toLower();
    int headerLevel = getHeaderLevel(headerElement);

    // Ошибка: Первый заголовок в body/section/article не h1
    if (!firstHeaderProcessed) {
        if (headerLevel != 1) {
            Error firstHeaderError;
            firstHeaderError.setType(ErrorType::noTagError);
            firstHeaderError.setErrorTagName(tagName);
            firstHeaderError.setErrorAttrName(parentScopeName + "_first_not_h1");
            errors.insert(firstHeaderError);
        }
        firstHeaderProcessed = true;
    }

    // Ошибка: Больше одного h1 в текущем контексте
    if (headerLevel == 1) {
        if (h1FoundInScope) {
            Error tooManyH1Error;
            tooManyH1Error.setType(ErrorType::tooManyTagsError);
            tooManyH1Error.setErrorTagName(tagName);
            tooManyH1Error.setErrorAttrName(parentScopeName);
            errors.insert(tooManyH1Error);
        }
        h1FoundInScope = true;
    }

    // Ошибка: Нарушение иерархии (например, h1 -> h3)
    if (previousHeaderLevel != 0 && headerLevel > previousHeaderLevel + 1) {
        Error hierarchyError;
        hierarchyError.setType(ErrorType::headerTagsHierarchyError);
        hierarchyError.setErrorTagName(tagName);
        errors.insert(hierarchyError);
    }

    QString paragraphText = headerElement.text().trimmed();

    // Ошибка: Пустой заголовочный тег
    if (paragraphText.isEmpty()) {
        Error emptyHeader;
        emptyHeader.setType(ErrorType::tagError);
        emptyHeader.setErrorTagName(tagName);
        emptyHeader.setErrorAttrName("empty");
        errors.insert(emptyHeader);
        previousHeaderLevel = headerLevel;
        return nullptr;
    }

    // Ошибка: Содержимое заголовочного тега не текст
    if (hasChildElements(headerElement)) {
        Error contentError;
        contentError.setType(ErrorType::tagError);
        contentError.setErrorTagName(tagName);
        contentError.setErrorAttrName("content_not_text");
        errors.insert(contentError);
        previousHeaderLevel = headerLevel;
        return nullptr;
    }

    // --- Создание пункта иерархии ---
    // Поиск родителя в иерархии
    Paragraph* newParentNode = findParentForParagraph(contextNode, headerLevel);
    if (!newParentNode)
        return nullptr;

    Paragraph* newParagraph = new Paragraph(paragraphText, newParentNode, headerLevel);
    newParentNode->appendChild(newParagraph);

    previousHeaderLevel = headerLevel;

    return newParagraph;
}

void createHierarchyRecursive(QDomElement& domNode, Paragraph* currentParagraph, QSet<Error>& errors) {
    QString currentDomTagName = domNode.tagName().toLower();

    int previousHeaderLevel = 0;
    bool h1FoundInScope = false;
    bool firstHeaderProcessed = false;

    QDomNode childNode = domNode.firstChild();
    Paragraph* lastAddedParagraph = currentParagraph;

    while (!childNode.isNull()) {
        if (childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString childTagName = childElement.tagName().toLower();

            // Ошибка: некорректная вложенность <section> или <article>
            if ((currentDomTagName == "section" || currentDomTagName == "article") &&
                (childTagName == "section" || childTagName == "article")) {
                Error nestingError;
                nestingError.setType(currentDomTagName == "section" ? ErrorType::sectionNestingError : ErrorType::articleNestingError);
                nestingError.setErrorTagName(childTagName);
                nestingError.setErrorAttrName(currentDomTagName);
                errors.insert(nestingError);
            }

            int headerLevel = getHeaderLevel(childElement);

            if (headerLevel > 0) { // Это тег h1-h6
                Paragraph* newParagraph = handleHeader(childElement, lastAddedParagraph, errors, previousHeaderLevel, h1FoundInScope, firstHeaderProcessed);
                if (newParagraph) {
                    lastAddedParagraph = newParagraph;
                }
            } else { // Это не заголовочный узел (div, p, и т.д.)
                // Продолжаем обход вглубь, сохраняя текущий контекст
                createHierarchyRecursive(childElement, lastAddedParagraph, errors);
            }
        }
        childNode = childNode.nextSibling();
    }
}

Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel) {
    if (!previous)
        return nullptr;

    int previousLevel = previous->getLevel();
    Paragraph* root = previous;

    // Поднимаемся до корня иерархии
    while (root->getLevel() > 0) {
        root = root->getParent();
    }

    // Определяем родителя в зависимости от уровня
    if (currentLevel == 1 || !previous || previous == root) {
        return root;
    }
    else if (currentLevel == previousLevel) { // Тот же уровень
        return previous->getParent();
    }
    else if (currentLevel > previousLevel) { // Уровень выше → дочерний
        return previous;
    }
    else { // currentLevel < previousLevel → ищем подходящего предка
        Paragraph* ancestor = previous->getParent();
        while (ancestor != root && ancestor->getLevel() >= currentLevel) {
            ancestor = ancestor->getParent();
        }
        return ancestor;
    }
}

QDomDocument createDomTreeFromFile(QString path, QSet<Error>& errors) {
    // Создаем объект для работы с файлом
    QFile file(path);
    // Создаем пустой DOM-документ
    QDomDocument domTree;

    // Пытаемся открыть файл только для чтения в текстовом режиме
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Если файл не удалось открыть, создаем и добавляем ошибку
        Error fileOpenError;
        fileOpenError.setType(ErrorType::fileError);
        fileOpenError.setErrorInputPath(path);
        fileOpenError.setErrorAttrName("input_cannot_open");
        errors.insert(fileOpenError);
        return domTree; // Возвращаем пустой документ
    }

    // Читаем все содержимое файла
    QString fileContent = file.readAll();
    file.close(); // Закрываем файл после чтения

    // Проверяем наличие <script> тегов.
    if (fileContent.contains("</script>", Qt::CaseInsensitive)) {
        Error scriptError;
        scriptError.setType(ErrorType::htmlStructureError);
        scriptError.setErrorTagName("script");
        scriptError.setErrorAttrName("ignored_content"); // Указываем, что контент игнорируется
        errors.insert(scriptError);
    }

    // Строим DOM-дерево
    QString errorMsg;
    int errorLine, errorColumn;
    if (!domTree.setContent(fileContent, &errorMsg, &errorLine, &errorColumn)) {
        // Если парсинг не удался, создаем и добавляем ошибку парсинга
        Error xmlError;
        xmlError.setType(ErrorType::XMLerror);
        xmlError.setErrorTagName("XML/HTML");
        // В атрибут записываем детальное сообщение об ошибке от парсера
        xmlError.setErrorAttrName(QString("xml_parse_error: %1 at line %2, column %3")
                                      .arg(errorMsg)
                                      .arg(errorLine)
                                      .arg(errorColumn));
        errors.insert(xmlError);
    }

    // Возвращаем созданный DOM-документ (может быть пустым в случае ошибки)
    return domTree;
}

void printHierarchyListOfHeaderTagsToFile(QString path, Paragraph* root, QSet<Error>& errors) {
    QFile outputFile(path); // Создаем объект файла

    // Открываем файл для записи в текстовом режиме
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Получаем строковое представление иерархии с разделителем "."
        QString textImplementationOfHierarchy = root->toString(".");

        // Поток для записи в файл с указанием кодировки UTF-8
        QTextStream out(&outputFile);
        out.setCodec("UTF-8");

        // Записываем результат и закрываем файл
        out << textImplementationOfHierarchy;
        outputFile.close();
    } else {
        // Если файл не открылся — добавляем ошибку
        Error outputError;
        outputError.setType(ErrorType::fileError);
        outputError.setErrorOutputPath(path);
        outputError.setErrorAttrName("output_cannot_create");
        errors.insert(outputError);
    }
}

int getHeaderLevel(const QDomElement& element) {
    QString tagName = element.tagName().toLower();
    if (tagName.startsWith('h') && tagName.length() == 2) {
        bool ok;
        int level = tagName.mid(1).toInt(&ok);
        if (ok && level >= 1 && level <= 6) {
            return level;
        }
    }
    return 0; // Не заголовок h1-h6
}

bool hasChildElements(const QDomElement& element) {
    QDomNode child = element.firstChild(); // Получаем первый дочерний узел

    while (!child.isNull()) { // Пока есть дочерние узлы
        if (child.isElement()) { // Если это DOM-элемент (а не текст или комментарий)
            return true; // Есть вложенный тег
        }
        child = child.nextSibling(); // Переход к следующему дочернему узлу
    }
    return false;
}

void printErrors (QString path, QSet<Error>& errors) {
    QFile outputFile(path); // Создаём объект файла

    // Открываем файл для записи
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outputFile); // Поток для записи текста в файл
        out.setCodec("UTF-8"); // Устанавливаем кодировку UTF-8 для корректного вывода

        // Для каждой ошибки
        for(const Error& err : qAsConst(errors)) {
            QString msg = err.generateErrorMessage(); // Формируем текст сообщения об ошибке
            qDebug().noquote() << msg; // Выводим в консоль
            out << msg; // Выводим в файл
        }

        outputFile.close(); // Закрываем файл после записи
    } else {
        // Если файл не открылся, выводим ошибки только в консоль
        for(const Error& err : qAsConst(errors)) {
            QString msg = err.generateErrorMessage();
            qDebug().noquote() << msg;
        }
    }
}
