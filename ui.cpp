#include "mainwindow.h"

void MainWindow::on_modeButton0_toggled(bool checked) {
    if (checked) {
        setMode(0);
    }
}

void MainWindow::on_modeButton1_toggled(bool checked) {
    if (checked) {
        setMode (1);
    }
}
