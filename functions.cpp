#include "functions.h"

// Глобальный флаг: найден ли заголовочный тег (h1-h6) в документе?
static bool isAnyHeaderTagFoundInCurrentDocumentGlobal = false;

void createHierarchyListOfHeaderTags(QDomElement& domTreeRoot, Paragraph* currentHierarchyNode, QSet<Error>& errors) {
    QString currentDomRootTagName = domTreeRoot.tagName().toLower();

    // Переменные для отслеживания состояния в текущем блоке (body, section, article)
    bool h1FoundInThisScope = false;
    int previousHeaderLevelForThisParent = 0;

    // Обработка начального вызова или вложенного раздела
    if (currentDomRootTagName == "body") {
        isAnyHeaderTagFoundInCurrentDocumentGlobal = false;
        h1FoundInThisScope = false;
        previousHeaderLevelForThisParent = 0;
    }
    else if (currentDomRootTagName == "section" || currentDomRootTagName == "article") {
        h1FoundInThisScope = false;
        previousHeaderLevelForThisParent = 0;
    }

    QDomNode childNode = domTreeRoot.firstChild();
    Paragraph* contextForNextSibling = currentHierarchyNode;
    bool firstHeaderInThisScopeProcessed = false;

    while (!childNode.isNull()) {
        if (childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString tagName = childElement.tagName().toLower();

            // Проверка ошибки: section внутри section / article
            if ((currentDomRootTagName == "section" || currentDomRootTagName == "article") &&
                (tagName == "section" || tagName == "article")) {
                Error nestingError;
                nestingError.setType(currentDomRootTagName == "section" ? ErrorType::sectionNestingError : ErrorType::articleNestingError);
                nestingError.setErrorTagName(tagName);
                nestingError.setErrorAttrName(currentDomRootTagName);
                errors.insert(nestingError);
            }

            int headerLevel = getHeaderLevel(childElement);

            if (headerLevel > 0) { // Элемент — заголовок h1-h6
                isAnyHeaderTagFoundInCurrentDocumentGlobal = true;

                // Ошибка: заголовок вне <body> (например, в <head>)
                if (tagName.startsWith('h')) {
                    QDomNode parentOfChildElement = childElement.parentNode();
                    if (parentOfChildElement.isElement()) {
                        QString parentTag = parentOfChildElement.toElement().tagName().toLower();
                        if (parentTag == "head") {
                            Error structureError;
                            structureError.setType(ErrorType::htmlStructureError);
                            structureError.setErrorTagName(tagName);
                            structureError.setErrorAttrName("outside_body");
                            errors.insert(structureError);
                        }
                    }
                }

                // Ошибка: первый заголовок в области — не H1
                if (tagName.startsWith('h') && !firstHeaderInThisScopeProcessed && headerLevel != 1) {
                    Error firstHeaderError;
                    firstHeaderError.setType(ErrorType::htmlStructureError);
                    firstHeaderError.setErrorTagName(tagName);
                    firstHeaderError.setErrorAttrName(currentDomRootTagName + "_first_not_h1");
                    errors.insert(firstHeaderError);
                }
                if (tagName.startsWith('h')) {
                    firstHeaderInThisScopeProcessed = true;
                }

                // Ошибка: несколько H1 в одной области
                if (headerLevel == 1 && tagName == "h1") {
                    if (h1FoundInThisScope) {
                        Error tooManyH1Error;
                        tooManyH1Error.setType(ErrorType::tooManyTagsError);
                        tooManyH1Error.setErrorTagName("h1");
                        tooManyH1Error.setErrorAttrName(currentDomRootTagName);
                        errors.insert(tooManyH1Error);
                    }
                    h1FoundInThisScope = true;
                }

                // Ошибка иерархии заголовков (например, H1 → H3 без H2)
                if (tagName.startsWith('h') && previousHeaderLevelForThisParent != 0 &&
                    headerLevel > previousHeaderLevelForThisParent + 1) {
                    Error hierarchyError;
                    hierarchyError.setType(ErrorType::headerTagsHierarchyError);
                    hierarchyError.setErrorTagName(tagName);
                    errors.insert(hierarchyError);
                }

                // Проверка пустого заголовка
                QString paragraphText = childElement.text().trimmed();
                if (tagName.startsWith('h') && paragraphText.isEmpty()) {
                    Error emptyHeader;
                    emptyHeader.setType(ErrorType::tagError);
                    emptyHeader.setErrorTagName(tagName);
                    emptyHeader.setErrorAttrName("empty");
                    errors.insert(emptyHeader);
                    previousHeaderLevelForThisParent = headerLevel;
                    childNode = childNode.nextSibling();
                    continue;
                }

                // Проверка наличия тегов внутри заголовка (должен содержать только текст)
                if (tagName.startsWith('h') && hasNonTextChildElements(childElement)) {
                    Error contentError;
                    contentError.setType(ErrorType::tagError);
                    contentError.setErrorTagName(tagName);
                    contentError.setErrorAttrName("content_not_text");
                    errors.insert(contentError);
                    previousHeaderLevelForThisParent = headerLevel;
                    childNode = childNode.nextSibling();
                    continue;
                }

                // Добавление параграфа в иерархию
                Paragraph* newParentNode = findParentForParagraph(contextForNextSibling, headerLevel);
                if (!newParentNode) {
                    previousHeaderLevelForThisParent = headerLevel;
                    childNode = childNode.nextSibling();
                    continue;
                }
                Paragraph* newParagraph = new Paragraph(paragraphText, newParentNode, headerLevel);
                newParentNode->appendChild(newParagraph);

                // Рекурсивный вызов для вложенного содержимого заголовка
                createHierarchyListOfHeaderTags(childElement, newParagraph, errors);

                contextForNextSibling = newParagraph;
                previousHeaderLevelForThisParent = headerLevel;
            }
            else {
                // Рекурсивный обход не-заголовков (div, p и т.п.)
                createHierarchyListOfHeaderTags(childElement, contextForNextSibling, errors);
            }
        }
        childNode = childNode.nextSibling();
    }

    // Проверка: нет ни одного заголовка в <body>
    if (currentDomRootTagName == "body" && !isAnyHeaderTagFoundInCurrentDocumentGlobal) {
        bool errorExists = false;
        for (const Error& err : errors) {
            if (err.getErrorType() == ErrorType::noHeaderTagsError) {
                errorExists = true;
                break;
            }
        }
        if (!errorExists) {
            Error noHeader;
            noHeader.setType(ErrorType::noHeaderTagsError);
            errors.insert(noHeader);
        }
    }
}

Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel)
{
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
    QFile inputFile(path);

    if (!inputFile.open(QIODevice::ReadOnly)) {
        Error fileError;
        fileError.setType(ErrorType::fileError);
        fileError.setErrorInputPath(path);
        fileError.setErrorAttrName("input_non_existent");
        errors.insert(fileError);
    }

    QDomDocument domTree;
    QString errorMessage;
    int errorLine, errorColumn;

    if (inputFile.isOpen()) {
        if (!domTree.setContent(&inputFile, &errorMessage, &errorLine, &errorColumn)) {
            Error parseError;
            parseError.setType(ErrorType::XMLerror);
            parseError.setErrorInputPath(path);
            parseError.setErrorAttrName("xml_parse_error: " + errorMessage);
            errors.insert(parseError);
        }
        inputFile.close();

        QDomElement docElem = domTree.documentElement();
        QDomElement bodyElement;

        if (!docElem.isNull())
            bodyElement = docElem.firstChildElement("body");

        QDomElement scriptElement = bodyElement.firstChildElement("script");

        if (bodyElement.isNull()) {
            Error noBodyError;
            noBodyError.setType(ErrorType::noTagError);
            noBodyError.setErrorTagName("body");
            noBodyError.setErrorAttrName("not_found");
            errors.insert(noBodyError);
        }
        if (!scriptElement.isNull()) {
            Error scriptError;
            scriptError.setType(ErrorType::htmlStructureError);
            scriptError.setErrorTagName("script");
            errors.insert(scriptError);
        }
    }

    return domTree;
}

void printHierarchyListOfHeaderTagsToFile(QString path, Paragraph* root, QSet<Error>& errors) {
    QFile outputFile(path);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString textImplementationOfHierarchy = root->toString(".");
        QTextStream out(&outputFile);
        out.setCodec("UTF-8");
        out << textImplementationOfHierarchy;
        outputFile.close();
    } else {
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

bool hasNonTextChildElements(const QDomElement& element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.isElement()) {
            return true; // Есть вложенный тег
        }
        child = child.nextSibling();
    }
    return false;
}
