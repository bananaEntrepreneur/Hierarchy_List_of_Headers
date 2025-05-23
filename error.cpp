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

ErrorType Error::getErrorType() {
    return this->type;
}

QString Error::getErrorTagName() {
    return this->errorTagName;
}

QString Error::getErrorAttrName() {
    return this->errorAttrName;
}

QString Error::getErrorInputPath() {
    return this->errorInputPath;
}

QString Error::getErrorOutputPath() {
    return this->errorOutputPath;
}
