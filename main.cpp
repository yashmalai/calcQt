#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTime>

static const int LOAD_TIME_MSEC = 2 * 1000;


int main( int argc, char *argv[] )
{
    QApplication a(argc, argv);

    QPixmap pix( ":/imgScreen/imgScreen/logoza.ru.png" );
    QSplashScreen splashScreen( pix );
    splashScreen.show();

    QTime time;
    time.start();
    while( time.elapsed() < LOAD_TIME_MSEC ) {
        const int progress = static_cast< double >( time.elapsed() ) / LOAD_TIME_MSEC * 100.0;
    }

    MainWindow w;


    w.show();
    splashScreen.finish( &w );


    return a.exec();
}
