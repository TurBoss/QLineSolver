#include "linesolver.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

LineSolver::LineSolver()
{

}

bool LineSolver::checkPoint(double *p1, double *p2, double *cp) {

    std::vector<double> point1 {p1[0], p1[1], p1[2]};
    std::vector<double> point2 {p2[0], p2[1], p2[2]};
    std::vector<double> d;

    std::set_difference(
        point2.begin(), point2.end(),
        point1.begin(), point1.end(),
        std::back_inserter(d)
    );

    double l = d[0];
    double m = d[1];
    double n = d[2];

    double x1 = p1[0];
    double y1 = p1[1];
    double z1 = p1[2];

    std::vector<double> cpoint {cp[0], cp[1], cp[2]};

    double x = cpoint[0];
    double y = cpoint[1];
    double z = cpoint[2];

    if (l == 0){
        if (x != x1){
            return false;
        }
        else if (n * y - n * y1 == m * z - m * z1){
            return true;
        }
        else{
            return false;
        }
    }

    if (m == 0) {
        if (y != y1) {
            return false;
        }
        else if(n * x - n * x1 == l * z - l * z1){
            return true;
        }
        else{
            return false;
        }
    }

    if (n == 0) {
        if (z != z1){
            return false;
        }
        else if (m * x - m * x1 == l * y - l * y1){
            return true;
        }
        else{
            return false;
        }
    }

    if ((n * y - m * z + (m * z1 - n * y1)) == 0 and (m * x - l * y + (l * y1 - m * x1)) == 0){
        return true;
    }
    else{
        return false;
    }
}
