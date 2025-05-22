#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "main.h"

class Paragraph {
public:
    Paragraph();
    Paragraph(QString iText, Paragraph* iParent, int iLevel);
    Paragraph(QString iText, Paragraph* iParent, QList<Paragraph*> iChildHierarchy, int iLevel);

    void setText(QString value);
    void setParent(Paragraph* value);
    void appendChild(Paragraph* value);
    void setLevel(int value);

    QString getText();
    Paragraph* getParent();
    QList<Paragraph*>* getChildHierarchy();
    int getLevel();

    //QString toString(QString separator);

private:
    QString text;
    int level;
    Paragraph* parent;
    QList<Paragraph*> childHierarchy;

    //QString getString(QString separator, QVector<int> numeration);
};

#endif // PARAGRAPH_H
