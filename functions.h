#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"

/*! Определить числовой уровень заголовка (H1=1, H2=2, ...)
* \param [in] element - ссылка на элемент DOM дерева
* return числовой уровень заголовка. 0 если элемент не является валидным тегом заголовка H1-H6
*/
int getHeaderLevel(const QDomElement& element);

/*! Поиск родителя для нового пункта
 * \param [in] previous - последний добавленный пункт в иерархию
 * \param [in] currentLevel - уровень текущего пункта
 * return указатель на родителя
*/
Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel);


/*! Построить иерархию заголовочных тегов
* \param [in] domTreeRoot - корень DOM дерева
* \param [in,out] root - корень иерархии заголовочных тегов
*/
void createHierarchyListOfHeaderTags(QDomElement& domTreeRoot, Paragraph* root, QSet<Error>& errors);

#endif // FUNCTIONS_H
