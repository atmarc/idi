#include <QApplication>
#include "DemoForm.h"

int main (int argc, char **argv) {
        QApplication app(argc, argv);
        
        DemoForm myform;
        myform.show();
        return app.exec();
        
}
