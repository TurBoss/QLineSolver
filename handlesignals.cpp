#include <iostream>
#include "handlesignals.h"

using namespace std;

void HandleSignals::runSlot(QString in){

   qDebug() << in;

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
