#include "functions.h"

int getHeaderLevel(const QDomElement& element) {
    QString tagName = element.tagName().toLower();
    if (tagName.startsWith('h') && tagName.length() == 2) {
        bool ok;
        int level = tagName.mid(1).toInt(&ok);
        if (ok && level >= 1 && level <= 6) {
            return level;
        }
    }
    if (tagName == "section" || tagName == "article") {
        return 1;
    }
    return 0; // �� �������� ����� ��������� H1-H6
}


Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel)
{
    int previousLevel = previous->getLevel();

    Paragraph* root = previous;
    while (root->getLevel() > 0) {
        root = root->getParent();
    }

    if (currentLevel == 1 || !previous || previous == root) {
        return root;
    }
    else if (currentLevel == previousLevel) {
        // ��� �� �������: �������� ��� ��, ��� � � �����������
        return previous->getParent();
    }
    else if (currentLevel > previousLevel) {
        // ������� ������: ������� ���������� �������� �����������
        return previous;
    }
    else { // currentLevel < previousLevel
        Paragraph* ancestor = previous->getParent();
        while (ancestor != root && ancestor->getLevel() >= currentLevel) {
            ancestor = ancestor->getParent();
        }

        return ancestor;
    }
}


void createHierarchyListOfHeaderTags(QDomElement& domTreeRoot, Paragraph* root, QSet<Error> errors) {
    QDomNode childNode = domTreeRoot.firstChild();
    while (!childNode.isNull()) {
        Paragraph* lastAddedParagraph = nullptr;

        if (childNode.isElement()) {

            QDomElement childElement = childNode.toElement();

            int headerLevel = getHeaderLevel(childElement);

            Paragraph* newParagraph = nullptr;

            if (headerLevel > 0) { // ��� ������������ ���
                Paragraph* newParent = findParentForParagraph(root, headerLevel);

                QString headerText = childElement.text();
                newParagraph = new Paragraph(headerText.trimmed(), newParent, headerLevel);

                newParent->appendChild(newParagraph);

                lastAddedParagraph = newParagraph;

                createHierarchyListOfHeaderTags(childElement, newParagraph, errors);
            }
            else {
            createHierarchyListOfHeaderTags(childElement, lastAddedParagraph, errors);
            }
        }
        // ��������� � ���������� �������� � DOM
        childNode = childNode.nextSibling();
    }
}