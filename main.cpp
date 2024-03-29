#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "../Lib/supportfunctions.h"

int main(int argc, char *argv[])
{
    if (argc>1 && argv[1][0]=='-' && argv[1][1]!='\0') {

        switch (argv[1][1]) {
        case 'v':
            std::cout << appHash().replace("v","").toLatin1().data() << "\n" ;
            break ;
        case 'l':
            std::cout << libVersion().replace("v","").toLatin1().data() << "\n" ;
            break ;
        case 'd':
            std::cout << buildDate().toLatin1().data() << "\n" ;
            break ;
        case 'a':
            std::cout << appHash().replace("v","").toLatin1().data() << "\n" ;
            std::cout << libVersion().replace("v","").toLatin1().data() << "\n" ;
            std::cout << buildDate().toLatin1().data() << "\n" ;
            break ;
        default:
            std::cout << "EncPad -adlv\n -a - Show all\n -d - Build date\n -l - Library version\n -v - Application version\n" ;
            break ;
        }
        return 1 ;

    } else {

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }
}
