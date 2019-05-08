QT += quick
QT += multimedia

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.cpp \
        gpr/gcode_program.cpp \
        gpr/parser.cpp \
        handlesignals.cpp \
        linesolver.cpp \
        main.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    backend.h \
    gpr/gcode_program.h \
    gpr/parser.h \
    handlesignals.h \
    linesolver.h \

DISTFILES += \
    LICENSE/LICENSE.md \
    LICENSE/gpl-3.0.md \
    README.md \
    example/sample.ngc \
    images/bg.svg \
    main.qml \
    music/CT_BOSS.MOD \
    music/CT_BOSS.ogg \
    music/Cv_boss.mod \
    music/Cv_boss.ogg \
    music/FINALBAT.ogg \
    music/FINALBAT.s3m \
    music/Fr_boss.mod \
    music/Fr_boss.ogg \
    music/ICEFRONT.S3M \
    music/ICEFRONT.ogg \
    music/Wood.ogg \
    music/Wood.s3m \
    music/amblight.ogg \
    music/cave.ogg \
    music/cave.xm \
    music/cave06.ogg \
    music/cave06.s3m \
    music/cavern.ogg \
    music/cavern.xm \
    music/fear2.mod \
    music/fear2.ogg \
    music/iller_knarkloader_final.ogg \
    music/iller_knarkloader_final.xm \
    music/rpg_bat1.ogg \
    music/rpg_bat1.xm
