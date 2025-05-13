#pragma once
#include "main.h"

/*! ���������� �������� ������� ��������� (H1=1, H2=2, ...)
* \param [in] - element ������ �� ������� DOM ������
* return �������� ������� ���������. 0 ���� ������� �� �������� �������� ����� ��������� H1-H6
*/
int getHeaderLevel(const QDomElement& element);

/*!
*/
Paragraph* findParentForParagraph(Paragraph* previous, int currentLevel);


/*! ����������� ������� ���������� �������� ������������ �����
* \param [in] domTreeRoot - ������ DOM ������  
* \param [in,out] root - ������ �������� ������������ �����
*/
void createHierarchyListOfHeaderTags(QDomElement& domTreeRoot, Paragraph* root, QSet<Error> errors);