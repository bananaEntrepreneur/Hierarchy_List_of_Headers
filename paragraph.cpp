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

QString Paragraph::getText() const {
    return this->text;
}

Paragraph* Paragraph::getParent() const {
    return this->parent;
}

QList<Paragraph*>* Paragraph::getChildHierarchy() {
    return &this->childHierarchy;
}

int Paragraph::getLevel() const {
    return this->level;
}

void Paragraph::getString(QTextStream& stream, const QString& separator, QVector<int>& currentNumeration) {
    // 1. Собрать префикс нумерации для текущего узла
    QStringList numerationStrings;
    for (int num : currentNumeration) {
        numerationStrings << QString::number(num);
    }

    // 2. Сформировать и записать полную строку для текущего узла в поток
    stream << numerationStrings.join(separator)
           << " "
           << this->text
           << "\n";

    // 3. Рекурсивно обработать всех детей
    for (int i = 0; i < childHierarchy.size(); ++i) {
        Paragraph* child = childHierarchy.at(i);
        currentNumeration.append(i + 1); // Добавляем номер ребенка к пути
        child->getString(stream, separator, currentNumeration);
        currentNumeration.removeLast(); // Убираем нумерацию ребенка для обработки следующего соседа
    }
}

QString Paragraph::toString(QString separator) {
    QString resultString;
    QTextStream stream(&resultString); // Связываем поток со строкой результата

    if (this->level == 0) { // Для корневого пункта иерархии
        // Проходим по всем прямым потомкам корневого узла
        for (int i = 0; i < childHierarchy.size(); ++i) {
            Paragraph* child = childHierarchy.at(i);
            // Для каждого ребенка верхнего уровня создается свой вектор нумерации.
            QVector<int> numerationForChild;
            numerationForChild.append(i + 1);

            // Запускаем рекурсивный процесс для дочернего узла.
            child->getString(stream, separator, numerationForChild);
        }
    } else { // Для остальных пунктов иерархии
        QVector<int> localNumeration;
        localNumeration.append(1);
        this->getString(stream, separator, localNumeration);
    }

    return resultString;
}
