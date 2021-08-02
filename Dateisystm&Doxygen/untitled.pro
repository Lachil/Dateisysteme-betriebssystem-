TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BsFatEmulator.c \
        BsInodes.c \
        CDroomEmulator.c \
        DisckEmu.c \
        main.c

HEADERS += \
    BsFatEmulator.h \
    BsInodes.h \
    CDroomEmulator.h \
    DisckEmu.h
