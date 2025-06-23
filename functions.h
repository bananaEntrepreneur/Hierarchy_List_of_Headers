#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"
#include "error.h"
#include "paragraph.h"

/*!
 * \file functions.h
*/

/*!
 * \brief Рекурсивно строит иерархию заголовочных тегов из DOM-дерева.
 * Обходит DOM-дерево, начиная с `domNode`, идентифицирует заголовочные теги (H1-H6, section, article)
 * и строит соответствующую иерархическую структуру объектов Paragraph.
 * Также функция обнаруживает и записывает ошибки, связанные со структурой и иерархией заголовков.
 * \param[in] domNode Ссылка на текущий узел DOM-дерева (обычно элемент <body> или его дочерний элемент).
 * \param[in,out] currentParagraph Указатель на текущий узел в строящейся иерархии Paragraph,
 * к которому будут добавляться новые найденные заголовки или который служит контекстом.
 * \param[in,out] errors Ссылка на QSet, в который добавляются обнаруженные ошибки типа Error.
 */
void createHierarchyListOfHeaderTags(QDomElement& domNode, Paragraph* currentParagraph, QSet<Error>& errors);


/*!
    \brief Обрабатывает заголовочный тег (h1–h6) и создает соответствующий пункт иерархии.

    Выполняет проверку структуры документа, включая:
    - правильность первого заголовка (h1),
    - отсутствие дублирующихся заголовков h1,
    - корректную иерархию уровней (например, запрет h1 → h3),
    - отсутствие вложенного HTML в заголовке,
    - непустое текстовое содержимое.

    При необходимости добавляет соответствующие ошибки в набор errors.

    \param headerElement DOM-элемент заголовочного тега (например, h2).
    \param contextNode Последний успешно добавленный параграф — используется для поиска родителя.
    \param errors Контейнер для накопления обнаруженных ошибок структуры.
    \param previousHeaderLevel Уровень предыдущего заголовка (для проверки иерархии).
    \param h1FoundInScope Флаг, указывающий, был ли уже найден заголовок h1 в текущем контексте (body/section/article).
    \param firstHeaderProcessed Флаг, был ли уже обработан первый заголовок в текущем контексте.

    \return Указатель на созданный объект Paragraph, либо nullptr, если добавление не выполнено из-за ошибки.
*/
Paragraph* handleHeader(
    QDomElement& headerElement,
    Paragraph* contextNode,
    QSet<Error>& errors,
    int& previousHeaderLevel,
    bool& h1FoundInScope,
    bool& firstHeaderProcessed);

/*!
    \brief Рекурсивно обходит DOM-дерево и создает иерархию заголовков.

    Функция обрабатывает заголовки h1–h6, а также структуры section и article,
    создавая иерархию узлов Paragraph на основе их уровней вложенности.
    Также фиксирует структурные ошибки, включая:
    - неправильную вложенность разделов,
    - пропуски уровней заголовков,
    - повторные h1 внутри одной области.

    \param domNode Узел DOM-дерева, откуда начинается обход (например, body или section).
    \param currentParagraph Указатель на текущий пункт иерархии Paragraph, к которому будут добавлены найденные заголовки.
    \param errors Контейнер, в который будут записаны найденные ошибки.
*/
void createHierarchyRecursive(QDomElement& domNode, Paragraph* currentParagraph, QSet<Error>& errors);


/*!
 * \brief Поиск родительского пункта для нового пункта в иерархии.
 * Определяет, куда встроить новый заголовок на основе уровня предыдущего добавленного пункта и уровня текущего пункта.
 * \param[in] previous Указатель на последний добавленный пункт в иерархию Paragraph.
 * \param[in] currentLevel Уровень текущего пункта (заголовка), для которого ищется родитель.
 * \return Указатель на найденный родительский Paragraph. Может вернуть nullptr, если родитель не может быть определен.
 */
Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel);

/*!
 * \brief Создает DOM-дерево из HTML-файла.
 * Читает HTML-содержимое из файла по указанному пути и пытается построить из него DOM-структуру.
 * Обнаруженные ошибки (например, отсутствие файла, ошибки парсинга) добавляются в errors.
 * \param[in] path Путь к HTML-файлу.
 * \param[in,out] errors Ссылка на QSet для добавления ошибок, возникших при чтении или парсинге файла.
 * \return QDomDocument, представляющий DOM-дерево. Если произошла ошибка, документ может быть пустым или невалидным.
 */
QDomDocument createDomTreeFromFile(QString path, QSet<Error>& errors);

/*!
 * \brief Записывает строковое представление иерархии заголовочных тегов в файл.
 * Преобразует иерархию, начиная с `root`, в строку и записывает ее в файл по указанному пути.
 * Обнаруженные ошибки (например, невозможность записи файла) добавляются в errors.
 * \param[in] path Путь к выходному файлу.
 * \param[in] root Указатель на корневой узел иерархии Paragraph для вывода.
 * \param[in,out] errors Ссылка на QSet для добавления ошибок, возникших при записи файла.
 */
void printHierarchyListOfHeaderTagsToFile(QString path, Paragraph* root, QSet<Error>& errors);

/*!
 * \brief Определяет числовой уровень заголовочного тега (H1=1, H2=2, ...).
 * Также обрабатывает теги section и article как уровень 1 для контекста иерархии.
 * \param[in] element Ссылка на элемент DOM-дерева.
 * \return Числовой уровень заголовка. 0, если элемент не является валидным тегом заголовка (H1-H6) или структурным элементом section/article.
 */
int getHeaderLevel(const QDomElement& element);

/*!
 * \brief Проверяет, содержит ли элемент нетекстовые дочерние элементы (другие теги).
 * Используется для проверки того, что заголовочные теги содержат только текст.
 * \param[in] element Элемент DOM для проверки.
 * \return true, если элемент содержит хотя бы один дочерний элемент-тег, иначе false.
 */
bool hasChildElements(const QDomElement& element);

/*!
 * \brief Распечатывает ошибки в файл. Если файла не удаётся открыть, то выводит ошибки в консоль.
 * \param [in] path Путь до файла
 * \param [in] errors Список с ошибками
 */
void printErrors (QString path, QSet<Error>& errors);

#endif // FUNCTIONS_H
