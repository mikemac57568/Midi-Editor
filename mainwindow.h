#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_functionSelectBox_currentIndexChanged(int index);

    void on_radioButton_toggled(bool checked);

    void on_trackSelectBox_currentIndexChanged(int index);

    void on_magnitudeSlider_sliderMoved(int position);

    void on_lowRangeSlider_sliderMoved(int position);


    void on_measuresBox_clicked(bool checked);

    void on_noteCheckBox_clicked(bool checked);


    void on_overwriteButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
