QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    correct_tst_createHierarchy.cpp \
    incorrect_tst_createHierarchy.cpp \
    tst_findParentForParagraph.cpp \
    tst_getString.cpp
