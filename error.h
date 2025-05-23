#ifndef ERROR_H
#define ERROR_H

#include <QHash>
#include "main.h"

enum ErrorType { noError,
                 tagError,
                 tagAttributeError,
                 fileError,
                 htmlStructureError,
                 headerTagsHierarchyError,
                 sectionNestingError ,
                 articleNestingError,
                 tooManyTagsError,
                 noTagError,
                 noHeaderTagsError };

class Error {
public:
    Error();

    // Сравнения для QSet и сортировки
    bool operator>(const Error& other) const;
    bool operator<(const Error& other) const;
    bool operator==(const Error& other) const;
    inline uint qHash(const Error& value, uint seed) const;

    void setType(ErrorType value);
    void setErrorTagName(QString value);
    void setErrorAttrName(QString value);
    void setErrorInputPath(QString value);
    void setErrorOutputPath(QString value);

    ErrorType getErrorType()const;
    int getIntErrorType() const;
    QString getErrorTagName()const;
    QString getErrorAttrName()const;
    QString getErrorInputPath()const;
    QString getErrorOutputPath()const;

private:
    ErrorType type;
    QString errorTagName;
    QString errorAttrName;
    QString errorInputPath;
    QString errorOutputPath;
};

#endif // ERROR_H
