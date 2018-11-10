/*
 * emuscreen.h
 *
 *  Created on: 29.10.2018
 *		Author: Rudenko Roman (aka Rem Norton)
 *
 */


#ifndef EMUSCREEN_H
#define EMUSCREEN_H

#include <QtCore>
#include <QWidget>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include "ssd1306_types.h"

//
//
//
#define _X_SPACING  1
#define _Y_SPACING  1

#define _X_SCALE    3
#define _Y_SCALE    4

#define _WIDTH_     128
#define _HIGHT_     64

//
//
//


class EmuScreen : public QOpenGLWidget
{
public:
    explicit EmuScreen(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void setGRAM(uint8_t* gramPtr);
    void setLedMatrixData(SSD1306EMU_Init_t* ledMatData);

private:
    QRgb getColor(int x, int y);

protected:
    void paintEvent(QPaintEvent* e);

private:
    uint8_t* GRAM = 0;
    uint8_t  colorMode = SSD1306_CM_Blue;
    SSD1306EMU_Init_t* instance;
};

#endif // EMUSCREEN_H
