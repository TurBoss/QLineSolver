// This file is part of QLineSolver
// Copyright 2019 Metal and TurBoss

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <iostream>
#include <iomanip>

#include <QFile>
#include <QUrl>

#include "handlesignals.h"
#include "linesolver.h"
#include "parser.h"

using namespace std;
using namespace gpr;

void HandleSignals::runSlot(QString in) {


    cout << fixed;
    cout << setprecision(3);

    QUrl url(in);
    QFile file(url.path());

    LineSolver line_solver;

    if(!file.exists()) {
        qDebug() << url.path() << " not found ...";
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        string file_content = stream.readAll().toUtf8().constData();
        gcode_program p = parse_gcode(file_content);


        if (p.get_block(0).get_chunk(0) == make_percent_chunk()) {
            qDebug() << "ISO FADAL" << endl;
        }

        // cout << p << endl;

        const chunk g0 = make_word_int('G', 0);
        const chunk g1 = make_word_int('G', 1);

        const chunk x_word = make_isolated_word('X');
        const chunk y_word = make_isolated_word('Y');
        const chunk z_word = make_isolated_word('Z');

        chunk x_point_1 = make_word_double('X', 0.0);
        chunk y_point_1 = make_word_double('Y', 0.0);
        chunk z_point_1 = make_word_double('Z', 0.0);

        chunk x_point_2 = make_word_double('X', 0.0);
        chunk y_point_2 = make_word_double('Y', 0.0);
        chunk z_point_2 = make_word_double('Z', 0.0);

        chunk x_point_c = make_word_double('X', 0.0);
        chunk y_point_c = make_word_double('Y', 0.0);
        chunk z_point_c = make_word_double('Z', 0.0);

        double p1[3] = {
            x_point_1.get_address().double_value(),
            y_point_1.get_address().double_value(),
            z_point_1.get_address().double_value()
        };
        double p2[3] = {
            x_point_2.get_address().double_value(),
            y_point_2.get_address().double_value(),
            z_point_2.get_address().double_value()
        };
        double cp[3] = {
            x_point_c.get_address().double_value(),
            y_point_c.get_address().double_value(),
            z_point_c.get_address().double_value()
        };


        for (auto j: p) {

            bool check_line = false;

            for (auto k: j) {
                switch(k.tp()) {

                case CHUNK_TYPE_WORD_ADDRESS:
                    // cout << "WORD ADDRESS ";
                    // cout << k.get_word() << endl;

                    if (k.get_word() == 'X')
                    {
                        if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE)
                        {
                            // cout << "X " << k.get_address().double_value() << endl;
                            cp[0] = k.get_address().double_value();
                        } else {
                            // cout << "X " << k.get_address().int_value() << endl;
                            cp[0] = k.get_address().int_value();
                        }
                        check_line = true;
                    }
                    else if (k.get_word() == 'Y')
                    {
                        if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE)
                        {
                            // cout << "Y " << k.get_address().double_value() << endl;
                            cp[1] = k.get_address().double_value();
                        } else {
                            // cout << "Y " << k.get_address().int_value() << endl;
                            cp[1] = k.get_address().int_value();
                        }
                        check_line = true;

                    }
                    else if (k.get_word() == 'Z')
                    {
                        if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE)
                        {
                            // cout << "Z " << k.get_address().double_value() << endl;
                            cp[2] = k.get_address().double_value();
                        } else {
                            // cout << "Z " << k.get_address().int_value() << endl;
                            cp[2] = k.get_address().int_value();
                        }
                        check_line = true;
                    }
                    break;

                case CHUNK_TYPE_WORD:
                    // cout << "WORD" << endl;
                    // cout << k.get_word() << endl;
                    break;

                default:
                    cout << k << endl;
                }
            }
            if (check_line){

                // cout << "CHECK POINT" << endl;

                cout << "X" << p1[0] << 'Y' << p1[1] << 'Z' << p1[2] << endl;
                cout << "X" << p2[0] << 'Y' << p2[1] << 'Z' << p2[2] << endl;
                cout << "X" << cp[0] << 'Y' << cp[1] << 'Z' << cp[2] << endl;

                // bool result = line_solver.checkPoint(p1, p2, cp);

                // cout << "result = " << result << endl;

                p1[0] = p2[0];
                p1[1] = p2[1];
                p1[2] = p2[2];

                p2[0] = cp[0];
                p2[1] = cp[1];
                p2[2] = cp[2];

            }
        }
    }

    else {
        qDebug() << url.path() << " read error ...";
    }

    file.close();

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
