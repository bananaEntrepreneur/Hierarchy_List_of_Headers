#include "error.h"

Error::Error()
    : type(noError),
      errorTagName(" "),
      errorAttrName(" "),
      errorInputPath(" "),
      errorOutputPath(" ") {}


bool Error::operator>(const Error& other) const {
    return std::tie(type, errorTagName, errorAttrName, errorInputPath, errorInputPath)
           > std::tie(other.type, other.errorTagName, other.errorAttrName, other.errorInputPath, other.errorInputPath);
}

bool Error::operator<(const Error& other) const {
    return std::tie(type, errorTagName, errorAttrName, errorInputPath, errorInputPath)
           < std::tie(other.type, other.errorTagName, other.errorAttrName, other.errorInputPath, other.errorInputPath);
}

bool Error::operator==(const Error& other) const {
    return type == other.type &&
           errorTagName == other.errorTagName &&
           errorAttrName == other.errorAttrName &&
           errorInputPath == other.errorInputPath &&
           errorOutputPath == other.errorOutputPath;
}

void Error::setType(ErrorType value) {
    type = value;
}

void Error::setErrorTagName(QString value) {
    errorTagName = value;
}

void Error::setErrorAttrName(QString value) {
    errorAttrName = value;
}

void Error::setErrorInputPath(QString value) {
    errorInputPath = value;
}

void Error::setErrorOutputPath(QString value) {
    errorOutputPath = value;
}

ErrorType Error::getErrorType() const {
    return this->type;
}

int Error::getIntErrorType() const {
    if (type == ErrorType::noError) return 1;
    if (type == ErrorType::tagError) return 2;
    if (type == ErrorType::tagAttributeError) return 3;
    if (type == ErrorType::fileError) return 4;
    if (type == ErrorType::htmlStructureError) return 5;
    if (type == ErrorType::headerTagsHierarchyError) return 6;
    if (type == ErrorType::sectionNestingError) return 7;
    if (type == ErrorType::articleNestingError) return 8;
    if (type == ErrorType::tooManyTagsError) return 9;
    if (type == ErrorType::noTagError) return 10;
    if (type == ErrorType::noHeaderTagsError) return 11;
    if (type == ErrorType::XMLerror) return 12;
    return 0;
}

QString Error::getErrorTagName() const {
    return this->errorTagName;
}

QString Error::getErrorAttrName() const {
    return this->errorAttrName;
}

QString Error::getErrorInputPath() const {
    return this->errorInputPath;
}

QString Error::getErrorOutputPath() const {
    return this->errorOutputPath;
}

QString Error::generateErrorMessage() const {
    switch (type) {
        case ErrorType::noError:
            return "Нет ошибки.";

        case ErrorType::fileError:
            if (errorAttrName == "input_non_existent") {
                return QString("Неверно указан файл с входными данными. Возможно, файл '%1' не существует.").arg(errorInputPath);
            }
            if (!errorInputPath.isEmpty() && errorAttrName == "input_no_access") {
                 return QString("Неверно указан файл с входными данными. Нет доступа к указанному файлу '%1'.").arg(errorInputPath);
            }
            if (!errorOutputPath.isEmpty() && errorAttrName == "output_cannot_create") {
                 return QString("Неверно указан файл для выходных данных. Возможно указанного расположения '%1' не существует или нет прав на запись.").arg(errorOutputPath);
            }
            if (errorTagName.toLower() == "script" && errorAttrName == "ignored_content") {
                return "Ошибка. Содержимое тега <script> не учитывается.";
            }
            return QString("Ошибка файла: Input='%1', Output='%2', Tag='%3', Attr='%4'")
                   .arg(errorInputPath.isEmpty() ? "N/A" : errorInputPath)
                   .arg(errorOutputPath.isEmpty() ? "N/A" : errorOutputPath)
                   .arg(errorTagName.trimmed().isEmpty() ? "N/A" : errorTagName)
                   .arg(errorAttrName.trimmed().isEmpty() ? "N/A" : errorAttrName);

        case ErrorType::XMLerror:
            {
                QString specificMessage = errorAttrName;
                if (specificMessage.startsWith("xml_parse_error: ", Qt::CaseInsensitive)) {
                    specificMessage = specificMessage.mid(QString("xml_parse_error: ").length());
                }
                if (!errorInputPath.isEmpty()) {
                    return QString("Ошибка разбора XML файла '%1': %2").arg(errorInputPath).arg(specificMessage);
                } else {
                    return QString("Ошибка разбора XML: %1").arg(specificMessage);
                }
            }

        case ErrorType::noTagError:
            if (!errorTagName.trimmed().isEmpty()) {
                return QString("Ошибка: отсутствует необходимый тег <%1>.").arg(errorTagName);
            }
            return "Ошибка: отсутствует необходимый тег.";


        case ErrorType::sectionNestingError:
            if (errorTagName.toLower() == "section" && (errorAttrName.toLower() == "section" || errorAttrName.isEmpty())) {
                return "Ошибка: <section> не должен быть вложен в <section>.";
            }
            if (errorTagName.toLower() == "article" && errorAttrName.toLower() == "section") {
                return "Ошибка: <article> не должен быть вложен в <section>.";
            }
            return QString("Ошибка вложенности: тег <%1> некорректно вложен в <section>.").arg(errorTagName);

        case ErrorType::articleNestingError:
             if (errorTagName.toLower() == "article" && (errorAttrName.toLower() == "article" || errorAttrName.isEmpty())) {
                return "Ошибка: <article> не должен быть вложен в <article>.";
            }
            if (errorTagName.toLower() == "section" && errorAttrName.toLower() == "article") {
                return "Ошибка: <section> не должен быть вложен в <article>.";
            }
            return QString("Ошибка вложенности: тег <%1> некорректно вложен в <article>.").arg(errorTagName);

        case ErrorType::tagError:
            if (errorAttrName == "empty") {
                return QString("Ошибка: содержимое тега <%1> не может быть пустым.").arg(errorTagName);
            }
            if (errorAttrName == "content_not_text") {
                 return QString("Ошибка: содержимым тега <%1> может быть только текст.").arg(errorTagName);
            }
            return QString("Ошибка тега <%1>: %2.").arg(errorTagName).arg(errorAttrName);

        case ErrorType::htmlStructureError:
            if (errorAttrName == "header_outside_body" || errorAttrName == "outside_body") {
                 return QString("Ошибка: заголовочный тег <%1> может располагаться только в <body>.").arg(errorTagName);
            }
            if (errorAttrName == "body_first_not_h1") {
                return QString("Ошибка: первым тегом в <body> может быть только <h1>.");
            }
            if (errorAttrName == "section_first_not_h1") {
                return QString("Ошибка: первым заголовочным тегом в <section> может быть только <h1>.");
            }
            if (errorAttrName == "article_first_not_h1") {
                // Аналогично секциям, для <article>
                return QString("Ошибка: первым заголовочным тегом в <article> может быть только <h1>.");
            }
            if (errorTagName == "script") {
                return QString("Ошибка: Содержимое тега <script> не учитывается.");
            }
            return QString("Ошибка структуры HTML: Тег <%1>, Атрибут/Контекст '%2'.").arg(errorTagName).arg(errorAttrName);

        case ErrorType::headerTagsHierarchyError:
             if (!errorTagName.trimmed().isEmpty()) {
                return QString("Ошибка: тег <%1> нарушает правило последовательности уровней (отличается от предыдущего больше, чем на один уровень).").arg(errorTagName);
             }
             return "Ошибка иерархии заголовочных тегов.";

        case ErrorType::tooManyTagsError:
            if (errorTagName.toLower() == "h1") {
                return QString("Ошибка: не должно быть больше одного <%1> в <%2>.").arg(errorTagName).arg(errorAttrName);
            }
            return QString("Ошибка: слишком много тегов <%1> в указанном контексте ('%2').").arg(errorTagName).arg(errorAttrName);

        case ErrorType::noHeaderTagsError:
            return "Ошибка: нет заголовочных тегов.";

        case ErrorType::tagAttributeError:
             return QString("Ошибка в атрибуте '%1' тега <%2>.").arg(errorAttrName).arg(errorTagName);

        default:
            return QString("Неизвестная ошибка (Тип: %1, Тег: <%2>, Атрибут/Контекст: '%3').")
                   .arg(QString::number(static_cast<int>(type)))
                   .arg(errorTagName.trimmed().isEmpty() ? "N/A" : errorTagName)
                   .arg(errorAttrName.trimmed().isEmpty() ? "N/A" : errorAttrName);
    }
}
