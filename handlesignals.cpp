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

#include <QFile>
#include <QUrl>

#include "handlesignals.h"
#include "linesolver.h"
#include "parser.h"

using namespace std;
using namespace gpr;

void HandleSignals::runSlot(QString in) {

    QUrl url(in);
    QFile file(url.path());

    LineSolver line_solver;

    if(!file.exists()) {
        qDebug() << url.path() << " no encontrado ...";
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

        chunk g0 = make_word_int('G', 0);
        chunk g1 = make_word_int('G', 1);

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

        vector<block>::iterator block_it;
        for (block_it = p.begin(); block_it != p.end(); ++block_it){
//            cout << *block_it << endl;

            vector<chunk>::iterator chunk_it;
            for (chunk_it = block_it->begin(); chunk_it != block_it->end(); ++chunk_it) {

                chunk x_word = make_isolated_word('X');
                chunk y_word = make_isolated_word('Y');
                chunk z_word = make_isolated_word('Z');

                if (*chunk_it == x_word){
                    double temp_x = chunk_it->get_address().double_value();
                    cp[0] = temp_x;
                }

                if (*chunk_it == y_word){
                    double temp_y = chunk_it->get_address().double_value();
                    cp[1] = temp_y;
                }

                if (*chunk_it == z_word){
                    double temp_z = chunk_it->get_address().double_value();
                    cp[2] = temp_z;
                }


//                bool result = line_solver.checkPoint(p1, p2, cp);
//                cout << "TEST Point = " << result << "\n";


            }

            emit setViewer(cp[0], cp[1], cp[2]);
            emit setViewer2("pedo");
            qDebug() << "emitSignal";
        }
    }

    else {
        qDebug() << url.path() << " error de lectura ...";
        return;
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
