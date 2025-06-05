# Программа для автоматической генерации иерархического оглавления HTML-страницы на основе заголовочных тегов и секций.

---

## 📌 Функциональность
- Парсинг HTML/XML файлов с построением DOM-дерева
- Автоматическое определение иерархии заголовков
- Валидация структуры документа согласно спецификации HTML5
- Генерация нумерованного оглавления в текстовый файл
- Обработка ошибок (некорректная вложенность, пустые теги и др.)

---

## ⚙️ Требования
- **Qt 5.13+** (модули: Core, Xml, Test)
- **C++11** или новее
- **Сборка**: qmake или CMake

---

## 🚀 Запуск

$: Hierarchy_List_of_Headers.exe input.html result.txt
- P.S. может потребоваться указать абсолютный путь до файлов (например: D:\...\input.html D:\...\result.txt)
- P.S.2 для работы требуются dll-файлы qt библиотек

---

## 📝 Пример

### Входной HTML-файл
- `<html>`
- `<body>`
- `<h1>`Lorem ispsum`</h1>`
- `<h2>`Dolor sit amet`</h2>`
- `<h2>`Consectetur adipiscing elit`</h2>`
- `<h3>`Tempor incididunt`</h3>`
- `<h2>`Ut labore et dolore`</h2>`
- `<h3>`Et dolore magna`</h3>`
- `<h4>`Ut enim ad minim`</h4>`
- `</body>`
- `</html>`

### Иерархия заголовочных тегов
- 1 Lorem ipsum
- 1.1 Dolor sit amet
- 1.2 Consectetur adipiscing elit
- 1.2.1 Tempor incididunt
- 1.3 Ut labore et dolore
- 1.3.1 Et dolore magna
- 1.3.1.1 Ut enim ad minim