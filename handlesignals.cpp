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
#include "parser.h"

using namespace std;
using namespace gpr;

void HandleSignals::runSlot(QString in) {

    QUrl url(in);
    QFile file(url.path());

    if(!file.exists()) {
        qDebug() << url.path() << " no encontrado ...";
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        string file_content = stream.readAll().toUtf8().constData();
        gcode_program p = parse_gcode(file_content);

        // cout << p << endl;

        if (p.get_block(0).get_chunk(0) == make_percent_chunk()) {
            qDebug() << "ISO FADAL" << endl;
        }

        vector<block>::iterator block_it;

        chunk g0 = make_word_int('G', 0);
        chunk g1 = make_word_int('G', 1);

        chunk x_word = make_word_double('X', 0.0);
        chunk y_word = make_word_double('Y', 0.0);
        chunk z_word = make_word_double('Z', 0.0);


        for (block_it = p.begin(); block_it != p.end(); ++block_it){

            // cout << *block_it << endl;

            // double x, y, z;

            vector<chunk>::iterator chunk_it;

            for (chunk_it = block_it->begin(); chunk_it != block_it->end(); ++chunk_it) {
                cout << *chunk_it << endl;
                if ((*chunk_it == g0) or (*chunk_it == g1)){
                    cout << "Linear movement" << endl;
                }
            }

            cout << endl;
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
