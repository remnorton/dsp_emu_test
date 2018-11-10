/*
 * mainwindow.h
 *
 *  Created on: 29.10.2018
 *		Author: Rudenko Roman (aka Rem Norton)
 *
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QCloseEvent>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent* e);

private slots:
    void drawScene();
    void on_chkEnabled_toggled(bool checked);
    void on_slContrast_valueChanged(int value);
    void on_cbInverse_toggled(bool checked);

    void on_cbColors_currentIndexChanged(int index);

    void on_btStart_clicked();

    void on_sbOffset_valueChanged(int arg1);

    void on_cbFlipY_toggled(bool checked);

    void on_cbFlipX_toggled(bool checked);

    void on_chkRotate_toggled(bool checked);

private:
    QTimer drawer;
};

#endif // MAINWINDOW_H
