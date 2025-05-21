#include "paragraph.h"

Paragraph::Paragraph() {
    QString text = " ";
    Paragraph* parent = nullptr;
    QList<Paragraph*> childHierarchy;
    int level = 0;
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

QList<Paragraph*> Paragraph::getChildHierarchy() {
    return this->childHierarchy;
}

int Paragraph::getLevel() {
    return this->level;
}
