TEMPLATE    = app
QT         += opengl 

INCLUDEPATH += /usr/include/glm

INCLUDEPATH += /home2/users/alumnes/1227286/dades/linux/IDI/Model

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \  
        MyGLWidget.cpp 
SOURCES += /home2/users/alumnes/1227286/dades/linux/IDI/Model/model.cpp
