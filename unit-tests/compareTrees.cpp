#include "compareTrees.h"

bool compareParagraphTreesRecursive(Paragraph* actual, Paragraph* expected, QString path) {
    // 1. Проверка на null
    if (!actual && !expected) return true; // Оба null, считаем их равными в этом контексте
    if (!actual || !expected) {
        qWarning() << "Tree Mismatch at" << path << ":"
                   << "One node is null, the other is not."
                   << "Actual:" << (actual ? actual->getText() : "null")
                   << "Expected:" << (expected ? expected->getText() : "null");
        return false;
    }

    // 2. Сравнение данных текущего узла (текст и уровень)
    // Не сравниваем корневой узел "root" по тексту, только его детей
    if (actual->getLevel() != 0 || expected->getLevel() != 0) { // Не для самого главного "root"
        if (actual->getLevel() != expected->getLevel()) {
            qWarning() << "Tree Mismatch at" << path << ":"
                       << "Different levels."
                       << "Actual Level:" << actual->getLevel() << "(Text:" << actual->getText() << ")"
                       << "Expected Level:" << expected->getLevel() << "(Text:" << expected->getText() << ")";
            return false;
        }
        // Текст для section/article может быть пустым, это нормально, если уровни совпадают
        // Если это не section/article (уровень > 0, но текст не пустой ИЛИ это Hx), то сравниваем текст
        bool isStructuralTagActual = (actual->getText().isEmpty() && (actual->getLevel() == 1)); /* Простой эвристический подход */
        bool isStructuralTagExpected = (expected->getText().isEmpty() && (expected->getLevel() == 1));

        if (!(isStructuralTagActual && isStructuralTagExpected) && actual->getText() != expected->getText()) {
             // Не сравниваем текст, если оба узла - это структурные теги (section/article) с пустым текстом
            if (!((actual->getText().isEmpty() && expected->getText().isEmpty()) && (actual->getLevel() == 1 && expected->getLevel() == 1))) {
                qWarning() << "Tree Mismatch at" << path << ":"
                        << "Different text."
                        << "Actual Text:" << actual->getText() << "(Level:" << actual->getLevel() << ")"
                        << "Expected Text:" << expected->getText() << "(Level:" << expected->getLevel() << ")";
                return false;
            }
        }
    }

    // 3. Сравнение количества дочерних элементов
    QList<Paragraph*>* actualChildren = actual->getChildHierarchy();
    QList<Paragraph*>* expectedChildren = expected->getChildHierarchy();

    if (actualChildren->size() != expectedChildren->size()) {
        qWarning() << "Tree Mismatch at" << path << ":"
                   << "Different number of children."
                   << "Actual children count:" << actualChildren->size()
                   << "Expected children count:" << expectedChildren->size();
        // Для наглядности выводится список детей
        QStringList actualChildTexts, expectedChildTexts;
        for(Paragraph* child : *actualChildren) actualChildTexts << child->getText();
        for(Paragraph* child : *expectedChildren) expectedChildTexts << child->getText();
        qDebug() << "Actual children:" << actualChildTexts;
        qDebug() << "Expected children:" << expectedChildTexts;
        return false;
    }

    // 4. Рекурсивное сравнение каждого дочернего элемента
    for (int i = 0; i < actualChildren->size(); ++i) {
        QString childPath = path + QString("->child[%1]").arg(i);
        if (!compareParagraphTreesRecursive(actualChildren->at(i), expectedChildren->at(i), childPath)) {
            return false; // Если хоть один дочерний элемент не совпадает, деревья разные
        }
    }

    return true; // Все проверки пройдены для этого узла и его поддерева
}
