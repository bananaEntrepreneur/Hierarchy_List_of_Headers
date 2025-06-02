#ifndef ERROR_H
#define ERROR_H

#include "main.h"

enum ErrorType { noError,
                 tagError,
                 tagAttributeError,
                 fileError,
                 htmlStructureError,
                 headerTagsHierarchyError,
                 sectionNestingError,
                 articleNestingError,
                 tooManyTagsError,
                 noTagError,
                 noHeaderTagsError,
                 XMLerror };

class Error {
public:
    Error();
    // Перегрузки сравнения для QSet
    bool operator>(const Error& other) const;
    bool operator<(const Error& other) const;
    bool operator==(const Error& other) const;
    // SET-теры
    void setType(ErrorType value);
    void setErrorTagName(QString value);
    void setErrorAttrName(QString value);
    void setErrorInputPath(QString value);
    void setErrorOutputPath(QString value);
    // GET-теры
    ErrorType getErrorType()const;
    int getIntErrorType()const;
    QString getErrorTagName()const;
    QString getErrorAttrName()const;
    QString getErrorInputPath()const;
    QString getErrorOutputPath()const;
    /*! Возвращает строковое представление ошибки */
    QString generateErrorMessage()const;
private:
    ErrorType type;
    QString errorTagName;
    QString errorAttrName;
    QString errorInputPath;
    QString errorOutputPath;
};

inline uint qHash(const Error& value, uint seed) {
    seed = qHash(value.getIntErrorType(), seed);
    seed = qHash(value.getErrorTagName(), seed);
    seed = qHash(value.getErrorAttrName(), seed);
    seed = qHash(value.getErrorInputPath(), seed);
    seed = qHash(value.getErrorOutputPath(), seed);
    return seed;
}

#endif // ERROR_H
