INCLUDEPATH += $$PWD\
				$$PWD/fonts

DISTFILES += \
    $$PWD/lcdlib.pri

HEADERS += \
    $$PWD/intmath.h \
    $$PWD/lcdlib.h \
    $$PWD/ssd1306.h \
    $$PWD/fonts/fonts_lib.h \
    $$PWD/dsp_driver.h \
    $$PWD/hal_includes.h

SOURCES += \
    $$PWD/intmath.cpp \
    $$PWD/lcdlib.cpp \
    $$PWD/ssd1306.cpp \
    $$PWD/fonts/fonts_lib.cpp \
    $$PWD/fonts/courier8.cpp \
    $$PWD/fonts/courier10.cpp