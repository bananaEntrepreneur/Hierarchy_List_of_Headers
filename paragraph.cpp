#include "paragraph.h"

Paragraph::Paragraph() {
    text = "root";
    parent = nullptr;
    level = 0;
}

Paragraph::Paragraph(QString iText, Paragraph* iParent, int iLevel) {
    text = iText;
    parent = iParent;
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
    QString result;
    QVector<int> numeration;

    if (this->level == 0) { // Если вызывается от root
        for (int i = 0; i < childHierarchy.size(); ++i) {
            numeration.clear();
            numeration.append(i + 1); // верхний уровень
            result += childHierarchy[i]->getString(separator, numeration);
        }
    } else { // Если вызывается от любого другого параграфа
        numeration.append(1);
        result = this->getString(separator, numeration);
    }

    return result;
}

QString Paragraph::getString(QString separator, QVector<int>& currentNumeration) {
    QString resultString;

    // Формируем строку с текущей нумерацией
    QStringList numerationStrings;
    for (int num : currentNumeration) {
        numerationStrings << QString::number(num);
    }

    if (!numerationStrings.isEmpty()) {
        resultString += numerationStrings.join(separator) + " " + this->text + "\n";
    }

    for (int i = 0; i < childHierarchy.size(); ++i) {
        currentNumeration.append(i + 1); // Переход к дочернему уровню
        resultString += childHierarchy[i]->getString(separator, currentNumeration);
        currentNumeration.removeLast(); // Откат к текущему уровню
    }

    return resultString;
}
