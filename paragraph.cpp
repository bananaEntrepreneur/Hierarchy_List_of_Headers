#include "paragraph.h"

Paragraph::Paragraph() {
    text = "root";
    parent = nullptr;
    QList<Paragraph*> childHierarchy;
    level = 0;
}

Paragraph::Paragraph(QString iText, Paragraph* iParent, int iLevel) {
    text = iText;
    parent = iParent;
    QList<Paragraph*> childHierarchy;
    level = iLevel;
}

Paragraph::Paragraph(QString iText, Paragraph* iParent, QList<Paragraph*> iChildHierarchy, int iLevel) {
    text = iText;
    parent = iParent;
    childHierarchy = iChildHierarchy;
    level = iLevel;
}

// SET-методы

void Paragraph::setText(QString value) {
    text = value;
}

void Paragraph::setParent(Paragraph* value) {
    parent = value;
}

void Paragraph::appendChild(Paragraph* value) {
    childHierarchy.append(value);
}

void Paragraph::setLevel(int value) {
    level = value;
}

// GET-методы

QString Paragraph::getText() {
    return this->text;
}

Paragraph* Paragraph::getParent() {
    return this->parent;
}

QList<Paragraph*>* Paragraph::getChildHierarchy() {
    return &this->childHierarchy;
}

int Paragraph::getLevel() {
    return this->level;
}

QString Paragraph::toString(QString separator) {
    QVector<int> numeration;
    return this->getString(separator, numeration);
}

QString Paragraph::getString(QString separator, QVector<int> numeration) {
    QString result;

    if (this->getLevel() > 0) {
        QStringList numList;
        for (int num : numeration) {
            numList << QString::number(num);
        }
        result += numList.join(separator) + " " + this->text + "\n";
    }

    int index = 1;
    for (Paragraph* child : childHierarchy) {
        QVector<int> childNumeration = numeration;
        childNumeration.append(index);
        result += child->getString(separator, childNumeration);
        ++index;
    }

    return result;
}
