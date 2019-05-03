#include <iostream>

#include <QFile>
#include <QUrl>

#include "handlesignals.h"
#include "parser.h"

using namespace std;

void HandleSignals::runSlot(QString in){

    QUrl url(in);
    QFile file(url.path());

    if(!file.exists()){
        qDebug() << url.path() << " no encontrado ...";
        return;
    }else{
        qDebug() << url.path() << " encontrado  ...";
    }

    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);

        std::string file_content = stream.readAll().toUtf8().constData();
        gpr::gcode_program p = gpr::parse_gcode(file_content);

        cout << p << endl;
    }

    file.close();

//    std::string file_contents((std::istreambuf_iterator<char>(t)),
//                              std::istreambuf_iterator<char>());

    //    LineSolver line_solver;

    //    double p1[3] = {0.0, 0.0, 0.0};
    //    double p2[3] = {1.0, 0.0, 0.0};
    //    double cp[3] = {2.0, 0.0, 0.0};

    //    bool result = line_solver.checkPoint(p1, p2, cp);

    //    cout << "TEST TRUE = " << result << "\n";

    //    cp[1] = 1.0;
    //    result = line_solver.checkPoint(p1, p2, cp);

    //    cout << "TEST FALSE = " << result << "\n";


}
