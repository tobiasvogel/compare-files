#include <QtGui>
#include <mainwindow.h>


int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

        compareWindow window;

        window.show();

        window.setWindowState(Qt::WindowActive);        

        return app.exec();

}
