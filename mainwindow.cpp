/*
 * mainwindow.cpp
 *
 *  Created on: 29.10.2018
 *		Author: Rudenko Roman (aka Rem Norton)
 *
 */


#include "mainwindow.h"
#include "ssd1306emu.h"
#include "transport.h"
#include "ssd1306.h"
#include "lcdlib.h"
#include "bitmaps.h"



SSD1306EMU_Init_t ssd1306_init =
{
    SSD1306_CM_BlueYellow,
    SSD1306_RES_128x64,
    0x78,
    3,
    0,
    Q_NULLPTR,
};

SSD1306_INIT_t drvInit = {0, 0x78, 64, 16};

DSPInitStruct_t initStruct = {
    &ssd1306_driver,
    &drvInit
};

uint8_t dsp_handle = 0;
uint8_t enters = 0;

static MainWindow* mw = 0;

//
//callback
//
void onEmuClosse()
{
    if (mw)
    {
        dsp_handle = 0;
        mw->close();
    }
}

//
//
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    drawer.setInterval(100);
    connect(&drawer, SIGNAL(timeout()), SLOT(drawScene()));

    mw = this;
    ssd1306_init.onCloseCallback = onEmuClosse;
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    mw = 0;
    if (dsp_handle) ssd1306emu_stop();
}

void MainWindow::drawScene()
{
    drawer.stop();

    dspClearScreen(dsp_handle);

//    dspDrawString(dsp_handle, 64, 30, &font_Courier_New_10pt, (uint8_t*)QString("УРА !!!").toLocal8Bit().data(),DSP_TextAllignCenter, DSP_TextDir_BottomTop);


//    dspDrawBitmap(dsp_handle, 10,20, &sattelite_bmp, DSP_Rotate_0);
//    dspDrawBitmap(dsp_handle, 30,20, &sattelite_bmp, DSP_Rotate_90);
//    dspDrawBitmap(dsp_handle, 10,40, &sattelite_bmp, DSP_Rotate_180);
//    dspDrawBitmap(dsp_handle, 30,40, &sattelite_bmp, DSP_Rotate_270);

//    dspDrawBitmap(dsp_handle, 0,20, &ok24_bmp, DSP_Rotate_0);
//    dspDrawBitmap(dsp_handle, 26,20, &ok24_bmp, DSP_Rotate_MirrorY);
//    dspDrawBitmap(dsp_handle, 26,20, &ok24_bmp, DSP_Rotate_90);
//    dspDrawBitmap(dsp_handle, 50,20, &ok24_bmp, DSP_Rotate_180);
//    dspDrawBitmap(dsp_handle, 76,20, &ok24_bmp, DSP_Rotate_270);


    //draw battery

    dspDrawRectangle(dsp_handle, 104, 2, 18, 12);
    dspFillRectangle(dsp_handle, 102, 6, 2, 4);

    if (enters > 24) dspFillRectangle(dsp_handle, 118,4, 2, 8);
    if (enters > 49) dspFillRectangle(dsp_handle, 114,4, 2, 8);
    if (enters > 74) dspFillRectangle(dsp_handle, 110,4, 2, 8);
    if (enters > 99) dspFillRectangle(dsp_handle, 106,4, 2, 8);

    dspDrawString(dsp_handle, 64, 30, &font_Courier_New_10pt, (uint8_t*)"Hell yes!!!",DSP_TextAllignCenter, DSP_TextDir_LeftRight);
    dspDrawString(dsp_handle, 64, 48, &font_Courier_New_10pt, (uint8_t*)"It's working!", DSP_TextAllignCenter, DSP_TextDir_LeftRight);

    dspDrawRectangle(dsp_handle, 0, 16, 127, 47);
    dspDrawRectangle(dsp_handle, 2, 18, 123, 43);

    dspDrawBitmap(dsp_handle, 0,1, &sattelite_bmp, DSP_Rotate_0);

    dspDrawString(dsp_handle, 60, 7, &font_Courier_New_8pt, (uint8_t*)"SSD1306",DSP_TextAllignCenter, DSP_TextDir_LeftRight);

    dspPushScreen(dsp_handle);

    enters++;
    if (enters > 150) enters = 0;

    drawer.start();
}

void MainWindow::on_chkEnabled_toggled(bool checked)
{
    dspSwitchOn(dsp_handle, checked);
}

void MainWindow::on_slContrast_valueChanged(int value)
{
    dspSetBrightnes(dsp_handle, value);
}

void MainWindow::on_cbInverse_toggled(bool checked)
{
    dspSetInverse(dsp_handle, checked);
}

void MainWindow::on_cbColors_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
        {
            ssd1306_init.color = SSD1306_CM_White;
            break;
        }
        case 1:
        {
            ssd1306_init.color = SSD1306_CM_Blue;
            break;
        }
        case 2:
        {
            ssd1306_init.color = SSD1306_CM_BlueYellow;
            break;
        }
    }
}

void MainWindow::on_btStart_clicked()
{
    if (dsp_handle) return;
    gbEmu->setEnabled(true);
    on_cbColors_currentIndexChanged(cbColors->currentIndex());
    ssd1306_init.resolution = cbResolution->currentIndex();
    ssd1306emu_init(&ssd1306_init);
    dspInit();
    dsp_handle = dspOpen(&initStruct);

    on_slContrast_valueChanged(slContrast->value());

    drawScene();
}

void MainWindow::on_sbOffset_valueChanged(int arg1)
{
    uint8_t cmd[2] = {0xd3,(uint8_t)arg1};
    dspSendCommands(dsp_handle, cmd, sizeof(cmd));
}

void MainWindow::on_cbFlipY_toggled(bool checked)
{
    uint8_t cmd = checked?0xc0:0xc8;
    dspSendCommands(dsp_handle, &cmd, sizeof(cmd));
}

void MainWindow::on_cbFlipX_toggled(bool checked)
{
    uint8_t cmd = 0xa1-(checked?1:0);
    dspSendCommands(dsp_handle, &cmd, sizeof(cmd));
}

void MainWindow::on_chkRotate_toggled(bool checked)
{
    dspRotate(dsp_handle, checked?DSP_Rotate_180:DSP_Rotate_0);
}
