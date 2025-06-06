#ifndef COMPARETREES_H
#define COMPARETREES_H

#include "../main.h"
#include "../paragraph.h"

/*!
 * \brief Рекурсивно сравнивает два узла Paragraph и их дочерние иерархии.
 * \param actual Указатель на текущий узел в фактически построенном дереве.
 * \param expected Указатель на текущий узел в ожидаемом дереве.
 * \param path Строковый путь к текущему узлу для информативного вывода ошибок (например, "root->child[0]->child[1]").
 * \return true, если поддеревья, начиная с этих узлов, идентичны, иначе false.
 */
bool compareParagraphTreesRecursive(Paragraph* actual, Paragraph* expected, QString path = "root");

#endif // COMPARETREES_H
