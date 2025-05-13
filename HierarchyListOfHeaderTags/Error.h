#pragma once
#include "main.h"

enum ErrorType { noError, tagError, tagAttributeError, fileError, htmlStructureError };

class Error {
public:

private:
	ErrorType type;
	QString errorTagName;
	QString errorAttrName;
	QString errorInputPath;
	QString errorOutputPath;
};