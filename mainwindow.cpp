#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <strummify.h>
#include <QFileDialog>
#include <qmessagebox.h>
#include <string>
#include <parsetrack.h>
#include <qdesktopservices.h>
#include <MidiFile.h>
#include <changenote.h>
#include <changedelta.h>
#include <changevolume.h>
#include <overwritemid.h>

QString filename = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int selection = ui->functionSelectBox->currentIndex();
    if (!filename.isEmpty()) {
        if (selection == 0) {

           int value = ui->magnitudeSlider->value();
           int track = ui->trackSelectBox->currentIndex() + 1;
           int start;
           int stop;
           if (ui->measuresBox->isChecked()){
                start = ui->startSpinBox->value()-1;
                stop = ui->stopSpinBox->value()-1;
            }
           else {
               start = 0;
               stop = 1000;
           }
           int sigA;
           int sigB;

            sigA = ui->sigABox->value();
            sigB = ui->sigBBox->value();


           Strummify s(filename, value, track, start, stop, sigA, sigB);
        }
        else if (selection == 1) {
            //cout << "Change Delta" << endl;
            int highChange = ui->magnitudeSlider->value();
            int lowChange = ui->lowRangeSlider->value();
            int selectedNote;
            if (ui->noteCheckBox->isChecked()) {
                selectedNote = ui->noteComboBox->currentText().toInt();
            }
            else {
                selectedNote = 0;
            }
            int track = ui->trackSelectBox->currentIndex() + 1;
            int start;
            int stop;
            if (ui->measuresBox->isChecked()){
                 start = ui->startSpinBox->value()-1;
                 stop = ui->stopSpinBox->value()-1;
            }
            else {
                start = 0;
                stop = 1000;
            }
            int sigA;
            int sigB;

            sigA = ui->sigABox->value();
            sigB = ui->sigBBox->value();

            ChangeDelta d(filename, selectedNote, highChange, lowChange, track, start, stop, sigA, sigB, ui->noteCheckBox->isChecked(), ui->radioButton->isChecked());
        }

        else if (selection == 2) {

            int change = ui->magnitudeSlider->value();
            int selectedNote = ui->noteComboBox->currentText().toInt();
            int track = ui->trackSelectBox->currentIndex() + 1;
            int start;
            int stop;
            if (ui->measuresBox->isChecked()){
                 start = ui->startSpinBox->value()-1;
                 stop = ui->stopSpinBox->value()-1;
            }
            else {
                start = 0;
                stop = 1000;
            }
            int sigA;
            int sigB;

            sigA = ui->sigABox->value();
            sigB = ui->sigBBox->value();

            ChangeNote c(filename, selectedNote, change, track, start, stop, sigA, sigB);
        }
        else if (selection == 3) {
            //cout << "Change Delta" << endl;
            int highChange = ui->magnitudeSlider->value();
            int lowChange = ui->lowRangeSlider->value();
            int selectedNote;
            if (ui->noteCheckBox->isChecked()) {
                selectedNote = ui->noteComboBox->currentText().toInt();
            }
            else {
                selectedNote = 0;
            }
            int track = ui->trackSelectBox->currentIndex() + 1;
            int start;
            int stop;
            if (ui->measuresBox->isChecked()){
                 start = ui->startSpinBox->value()-1;
                 stop = ui->stopSpinBox->value()-1;
            }
            else {
                start = 0;
                stop = 1000;
            }
            int sigA;
            int sigB;

             sigA = ui->sigABox->value();
             sigB = ui->sigBBox->value();

            ChangeVolume v(filename, selectedNote, highChange, lowChange, track, start, stop, sigA, sigB, ui->noteCheckBox->isChecked(), ui->radioButton->isChecked());

        }
        ui->saveLabel->setText("Unsaved Changes!");
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "Home", "Midi files (*.mid)");
    ui->label->setText(filename.right(30));

    parseTrack parser = parseTrack(filename);
    int tracks = parser.getTrackCount();
    QString s = QString::number(tracks);
    //parseTrack();

    QStringList list;
    for (int a = 1; a < tracks; a = a+1) {
        list << QString::number(a);
    }
    ui->trackSelectBox->clear();
    ui->trackSelectBox->addItems(list);


}


void MainWindow::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("output.mid"));
}

void MainWindow::on_functionSelectBox_currentIndexChanged(int index)
{
    if(index == 0) { //strummify
        ui->magnitudeSlider->setEnabled(true);
        ui->magnitudeLabel->setEnabled(true);
        ui->radioButton->setEnabled(false);
        ui->noteComboBox->setEnabled(false);
        ui->noteCheckBox->setEnabled(false);
        ui->lowRangeSlider->setEnabled(false);
        ui->magnitudeSlider->setMinimum(0);

    } else if (index == 1) { //change delta
        ui->magnitudeSlider->setEnabled(true);
        ui->magnitudeLabel->setEnabled(true);
        ui->radioButton->setEnabled(true);
        ui->magnitudeSlider->setMaximum(100);
        ui->magnitudeSlider->setMinimum(-100);
        ui->lowRangeSlider->setMaximum(0);
        ui->lowRangeSlider->setMinimum(-100);
        ui->magnitudeSlider->setSliderPosition(50);
        ui->lowRangeSlider->setSliderPosition(-50);
        ui->magnitudeLabel->setText("Magnitude 50");
        ui->lowRangeLabel->setText("Low Magnitude -50");
        ui->noteComboBox->setEnabled(true);
        ui->noteCheckBox->setEnabled(true);
        ui->radioButton->setChecked(false);
        ui->lowRangeSlider->setEnabled(false);



    } else if (index == 2) { //change note
        ui->magnitudeSlider->setEnabled(true);
        ui->magnitudeLabel->setEnabled(true);
        ui->radioButton->setEnabled(false);
        ui->radioButton->setChecked(false);
        ui->lowRangeSlider->setEnabled(false);
        ui->lowRangeLabel->setEnabled(false);
        ui->magnitudeSlider->setMaximum(127);
        ui->magnitudeSlider->setMinimum(0);
        ui->magnitudeSlider->setSliderPosition(63);
        ui->magnitudeLabel->setText("Magnitude 75");
        ui->noteComboBox->setEnabled(true);
        ui->noteCheckBox->setEnabled(false);


    } else if (index == 3) { //change volume
        ui->magnitudeSlider->setEnabled(true);
        ui->magnitudeLabel->setEnabled(true);
        ui->radioButton->setEnabled(true);
        ui->magnitudeSlider->setMaximum(100);
        ui->magnitudeSlider->setMinimum(-100);
        ui->lowRangeSlider->setMaximum(0);
        ui->lowRangeSlider->setMinimum(-100);
        ui->magnitudeSlider->setSliderPosition(50);
        ui->lowRangeSlider->setSliderPosition(-50);
        ui->magnitudeLabel->setText("Magnitude 50");
        ui->lowRangeLabel->setText("Low Magnitude -50");
        ui->noteComboBox->setEnabled(true);
        ui->noteCheckBox->setEnabled(true);
        ui->radioButton->setChecked(false);
        ui->lowRangeSlider->setEnabled(false);

    }
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked) {

        ui->lowRangeSlider->setEnabled(true);
        ui->lowRangeLabel->setEnabled(true);
        ui->magnitudeSlider->setMinimum(0);
        //ui->magnitudeSlider->setSliderPosition(20);
        //ui->magnitudeSlider->setMaximum(20);
        //ui->lowRangeSlider->setMinimum(-20);
        //ui->magnitudeLabel->setText("Magnitude 20");

    } else {

        ui->lowRangeSlider->setEnabled(false);
        ui->lowRangeLabel->setEnabled(false);
        ui->magnitudeSlider->setMinimum(-100);
        //ui->magnitudeSlider->setSliderPosition(20);
        //ui->magnitudeSlider->setMaximum(100);
        //ui->lowRangeSlider->setMinimum(-100);
        //ui->magnitudeLabel->setText("Magnitude 20");

    }
}

void MainWindow::on_trackSelectBox_currentIndexChanged(int index)
{
    parseTrack parser = parseTrack(filename);
    QList<int> noteList = parser.getNoteList(index+1);
    QStringList noteStringList;
    for (int b = 0; b < noteList.length(); b=b+1) {
        noteStringList << QString::number(noteList[b]);
    }

    ui->noteComboBox->clear();
    ui->noteComboBox->addItems(noteStringList);
}

void MainWindow::on_magnitudeSlider_sliderMoved(int position)
{
    ui->magnitudeLabel->setText("Magnitude " + QString::number(position));
}

void MainWindow::on_lowRangeSlider_sliderMoved(int position)
{
    ui->lowRangeLabel->setText("Low Magnitude " + QString::number(position));
}

void MainWindow::on_measuresBox_clicked(bool checked)
{
    if(checked) {

        ui->startSpinBox->setEnabled(true);
        ui->stopSpinBox->setEnabled(true);
    }
    else {

        ui->startSpinBox->setEnabled(false);
        ui->stopSpinBox->setEnabled(false);
    }
}

void MainWindow::on_noteCheckBox_clicked(bool checked)
{
    if (checked) {

        ui->noteComboBox->setEnabled(true);
    }
    else {

        ui->noteComboBox->setEnabled(false);
    }
}

void MainWindow::on_overwriteButton_clicked()
{
    OverWriteMID o(filename);

    string file = filename.toStdString().c_str();
    string ext = file.substr(file.find_last_of("."), file.length());
    int pos = file.length() - ext.length();
    file = file.substr(0, pos);
    if (file.find("MIDIEDITOR") == std::string::npos) {
        file.append("MIDIEDITOR");
    }
    file.append(".mid");
    filename = QString::fromStdString(file);

    ui->label->setText(filename.right(30));

    ui->saveLabel->setText("Changes Saved!");
}
