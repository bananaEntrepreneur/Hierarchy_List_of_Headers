#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "main.h"

class Paragraph {
public:
    // Конструкторы
    Paragraph();
    Paragraph(QString iText, Paragraph* iParent, int iLevel);
    Paragraph(QString iText, Paragraph* iParent, QList<Paragraph*> iChildHierarchy, int iLevel);
    // SET-теры
    void setText(QString value);
    void setParent(Paragraph* value);
    void appendChild(Paragraph* value);
    void setLevel(int value);
    // GET-теры
    QString getText();
    Paragraph* getParent();
    QList<Paragraph*>* getChildHierarchy();
    int getLevel();
    /*! Возвращает строковое представление иерархии заголовочных тегов с нумерацией
    \param [in] separator - разделитель между цифрами в нумерации
    */
    QString toString(QString separator);
private:
    QString text;
    int level;
    Paragraph* parent;
    QList<Paragraph*> childHierarchy;

    QString getString(QString separator, QVector<int>& currentNumeration);
};

#endif // PARAGRAPH_H
