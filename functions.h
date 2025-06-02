#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"
#include "error.h"
#include "paragraph.h"

/*! Определить числовой уровень заголовка (H1=1, H2=2, ...)
* \param [in] element - ссылка на элемент DOM дерева
* return числовой уровень заголовка. 0 если элемент не является валидным тегом заголовка H1-H6
*/
int getHeaderLevel(const QDomElement& element);

/*! Определяет родительский параграф для текущего параграфа в зависимости от уровня заголовка
 * \param [in] previous - последний добавленный пункт в иерархию
 * \param [in] currentLevel - уровень текущего пункта
 * return указатель на найденного родителя
*/
Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel);

/*! Проверяет наличие не-текстовых (теговых) дочерних элементов
 * \param [in] element - элемент DOM дерева
*/
bool hasNonTextChildElements(const QDomElement& element);

/*! Построить иерархию заголовочных тегов
* \param [in] domTreeRoot - корень DOM дерева
* \param [in,out] currentParagraph - пункт иерархии заголовочных тегов
* \param [in,out] errors - список ошибок
*/
void createHierarchyListOfHeaderTags(QDomElement& domNode, Paragraph* currentParagraph, QSet<Error>& errors);

#endif // FUNCTIONS_H
