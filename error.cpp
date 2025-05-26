#include "error.h"

Error::Error() {
    type = noError;
    errorTagName = " ";
    errorAttrName = " ";
    errorInputPath = " ";
    errorOutputPath = " ";
}

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
