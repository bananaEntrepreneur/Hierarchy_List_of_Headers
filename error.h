#ifndef ERROR_H
#define ERROR_H

#include "main.h"

enum ErrorType { noError, tagError, tagAttributeError, fileError, htmlStructureError, headerTagsHierarchyError, sectionNestingError , articleNestingError, tooManyTagsError, noTagError, noHeaderTagsError };

class Error {
public:
    Error();
    ~Error();

private:
    ErrorType type;
    QString errorTagName;
    QString errorAttrName;
    QString errorInputPath;
    QString errorOutputPath;
};

#endif // ERROR_H
