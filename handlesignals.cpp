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

#include <iomanip>
#include <iostream>
#include <fstream>

#include <QFile>
#include <QUrl>

#include "handlesignals.h"
#include "linesolver.h"
#include "gpr/parser.h"

using namespace std;
using namespace gpr;

void HandleSignals::runSlot(QString in) {

    LineSolver line_solver;


    QUrl url(in);
    QFile input_file(url.toLocalFile());

    if(!input_file.exists()) {
        qDebug() << url.path() << " not found ...";
        return;
    }

    if (input_file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QString filename = "output.tap";
        QFile output_file(filename);

        if (output_file.open(QIODevice::ReadWrite | QIODevice::Text) ) {

            QTextStream output_stream( &output_file );

            output_stream << "(TurBo test)" << endl;

            QTextStream input_stream(&input_file);
            string file_content = input_stream.readAll().toUtf8().constData();

            gcode_program p = parse_gcode(file_content);

            if (p.get_block(0).get_chunk(0) == make_percent_chunk()) {
                qDebug() << "ISO FADAL" << endl;
            }

            // cout << p << endl;

            chunk active_modal;

            const chunk g0 = make_word_int('G', 0);
            const chunk g1 = make_word_int('G', 1);
            const chunk g2 = make_word_int('G', 2);
            const chunk g3 = make_word_int('G', 3);

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

            for (block &j: p) {

                bool check_line = false;
                bool requires_newline = false;


                // block gcode_block(false, {g0, x_point_c, y_point_c, z_point_c});

                for (chunk &k: j) {
                    switch(k.tp()) {

                    case CHUNK_TYPE_WORD_ADDRESS:

                        if (k.get_word() == 'G') {
                            if (k.get_address().tp() == ADDRESS_TYPE_INTEGER) {
                                if ((k.get_address().int_value() == 0)
                                        or (k.get_address().int_value() == 2)
                                        or (k.get_address().int_value() == 3)) {
                                    output_stream << k.get_word() << k.get_address().int_value();
                                    active_modal = k;
                                    requires_newline = true;
                                }
                                else if (k.get_address().int_value() == 1) {
                                    active_modal = k;
                                    check_line = true;

                                }
                                else {
                                    output_stream << k.get_word() << k.get_address().int_value();
                                    requires_newline = true;
                                }
                            }
                            else if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                output_stream << k.get_word() << k.get_address().double_value();
                            }
                        }

                        else if (k.get_word() == 'X') {
                            cout << active_modal;
                            if (active_modal == g1){
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    cp[0] = k.get_address().double_value();
                                } else {
                                    cp[0] = k.get_address().int_value();
                                }
                                check_line = true;
                            }
                            else {
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    output_stream << k.get_word() << k.get_address().double_value();
                                }
                                else if (k.get_address().tp() == ADDRESS_TYPE_INTEGER) {
                                    output_stream << k.get_word() << k.get_address().int_value();
                                }
                            }
                        }

                        else if (k.get_word() == 'Y') {
                            if (active_modal == g1){
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    cp[1] = k.get_address().double_value();
                                } else {
                                    cp[1] = k.get_address().int_value();
                                }
                                check_line = true;
                            }
                            else {
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    output_stream << k.get_word() << k.get_address().double_value();
                                }
                                else if (k.get_address().tp() == ADDRESS_TYPE_INTEGER) {
                                    output_stream << k.get_word() << k.get_address().int_value();
                                }
                            }
                        }

                        else if (k.get_word() == 'Z') {
                            if (active_modal == g1){
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    cp[2] = k.get_address().double_value();
                                } else {
                                    cp[2] = k.get_address().int_value();
                                }
                                check_line = true;
                            }
                            else {
                                if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                    output_stream << k.get_word() << k.get_address().double_value();
                                }
                                else if (k.get_address().tp() == ADDRESS_TYPE_INTEGER) {
                                    output_stream << k.get_word() << k.get_address().int_value();
                                }
                            }
                        }

                        else {
                            output_stream << k.get_word();

                            if (k.get_address().tp() == ADDRESS_TYPE_DOUBLE) {
                                output_stream << k.get_address().double_value();
                            }
                            else if (k.get_address().tp() == ADDRESS_TYPE_INTEGER) {
                                output_stream << k.get_address().int_value();
                            }
                            requires_newline = true;
                        }
                        break;

                    case CHUNK_TYPE_WORD:

                        printf("WORD %d\n", k.get_word());

                        break;
                    case CHUNK_TYPE_COMMENT:
                        output_stream << "(" << k.get_comment_text().c_str() << ")";
                        requires_newline = true;
                        break;

                    default:
                        cout << k << " ";
                    }
                }


                if (check_line){
                    check_line = false;

                    if (active_modal == g1) {
                        //cout << "FOUND G1" << endl;

                        printf("\nP1 X %f Y %f Z %f\n", p1[0], p1[1], p1[2]);
                        printf("P2 X %f Y %f Z %f\n", p2[0], p2[1], p2[2]);
                        printf("CP X %f Y %f Z %f\n", cp[0], cp[1], cp[2]);


                        bool result = line_solver.checkPoint(p1, p2, cp);

                        if (!result) {
                            chunk x_result = make_word_double('X', cp[0]);
                            chunk y_result = make_word_double('Y', cp[1]);
                            chunk z_result = make_word_double('Z', cp[2]);

                            cout  << x_result << y_result << z_result << endl;

                            output_stream << active_modal.get_word() << active_modal.get_address().int_value();

                            output_stream << x_result.get_word() << x_result.get_address().double_value();
                            output_stream << y_result.get_word() << y_result.get_address().double_value();
                            output_stream << z_result.get_word() << z_result.get_address().double_value();
                            requires_newline = true;

                            // block result_block = make
                        }
                        printf("result = %d\n", result);
                        printf("------------------------\n");
                    }
                }

                if (requires_newline) {
                    requires_newline = false;

                    output_stream << endl;
                }

                p1[0] = p2[0];
                p1[1] = p2[1];
                p1[2] = p2[2];

                p2[0] = cp[0];
                p2[1] = cp[1];
                p2[2] = cp[2];
            }
            output_file.close();
        }
        input_file.close();
    }

    else {
        qDebug() << url.path() << " read error ...";
    }

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
