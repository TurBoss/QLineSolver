#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>




bool check_point(float *p1, float *p2, float *cp) {

    std::vector<float> point1 {p1[0], p1[1], p1[2]};
    std::vector<float> point2 {p2[0], p2[1], p2[2]};
    std::vector<float> d;

    std::set_difference(
        point2.begin(), point2.end(),
        point1.begin(), point1.end(),
        std::back_inserter(d)
    );

    float l = d[0];
    float m = d[1];
    float n = d[2];

    float x1 = p1[0];
    float y1 = p1[1];
    float z1 = p1[2];

    std::vector<float> cpoint {cp[0], cp[1], cp[2]};

    float x = cpoint[0];
    float y = cpoint[1];
    float z = cpoint[2];

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

int main() {

    float p1[3] = {0.0, 0.0, 4.0};
    float p2[3] = {0.0, 0.0, 2.0};
    float cp[3] = {0.0, 0.0, 3.0};

    printf("Result = %d", check_point(p1, p2, cp));

    return 0;
}

extern "C" {
    extern bool cffi_check_point(float *p1, float *p2, float *cp) {
        return check_point(p1, p2, cp);
    }
}
