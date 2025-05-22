#ifndef ERROR_H
#define ERROR_H

#include "main.h"

enum ErrorType { noError, tagError, tagAttributeError, fileError, htmlStructureError, headerTagsHierarchyError, sectionNestingError , articleNestingError, tooManyTagsError, noTagError, noHeaderTagsError };

class Error {
public:
    Error();

    void setType(ErrorType value);
    void setErrorTagName(QString value);
    void setErrorAttrName(QString value);
    void setErrorInputPath(QString value);
    void setErrorOutputPath(QString value);

    ErrorType getErrorType();
    QString getErrorTagName();
    QString getErrorAttrName();
    QString getErrorInputPath();
    QString getErrorOutputPath();

private:
    ErrorType type;
    QString errorTagName;
    QString errorAttrName;
    QString errorInputPath;
    QString errorOutputPath;
};

#endif // ERROR_H
