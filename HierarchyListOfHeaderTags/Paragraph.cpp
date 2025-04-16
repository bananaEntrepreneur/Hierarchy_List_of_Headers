#include "Paragraph.h"

Paragraph::Paragraph() {
	QString text = " ";
	Paragraph* parent = nullptr;
	QList<Paragraph*> childHierarchy;
	int level = 0;
}

Paragraph::Paragraph(QString iText, Paragraph* iParent, int iLevel) {
	text = iText;
	parent = iParent;
	level = iLevel;
	QList<Paragraph*> childHierarchy;
}

Paragraph::Paragraph(QString iText, Paragraph* iParent, QList<Paragraph*> iChildHierarchy, int iLevel) {
	text = iText;
	parent = iParent;
	childHierarchy = iChildHierarchy;
	level = iLevel;
}

// SET-методы

void Paragraph::setText(QString value) {
	text = value;
}

void Paragraph::setParent(Paragraph* value) {
	parent = value;
}

void Paragraph::appendChild(Paragraph* value) {
	childHierarchy.append(value);
}

void Paragraph::setLevel(int value) {
	level = value;
}

// GET-методы

QString Paragraph::getText() {
	return this->text;
}

Paragraph* Paragraph::getParent() {
	return this->parent;
}

int Paragraph::getCountOfChilds() {
	return this->getChildHierarchy()->count();
}

QList<Paragraph*> Paragraph::getChildHierarchy() {
	return this->childHierarchy;
}

int Paragraph::getLevel() {
	return this->level;
}

// Метод, возвращающий строковое представление иерархии заголовочных тегов
QString Paragraph::toString(QString separator) {
	return;
}