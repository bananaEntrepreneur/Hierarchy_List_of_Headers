#include "error.h"

Error::Error() {
    type = noError;
    errorTagName = " ";
    errorAttrName = " ";
    errorInputPath = " ";
    errorOutputPath = " ";
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


