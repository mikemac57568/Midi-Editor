#include "changevolume.h"
#include <QString>
#include "MidiFile.h"
#include <string>
#include <iostream>

ChangeVolume::ChangeVolume(QString filename, int selectedNote, int highChange, int lowChange, int selectedTrack,
                           int lowRange,int highRange, int sigA, int sigB, bool note, bool randb)
{
    cout << "Changing note " << selectedNote << " by " <<
            highChange << endl;
    string file = filename.toStdString().c_str();
    MidiFile midifile;
    midifile.read(file);
    cout << midifile.status() << endl;
    int tracks = midifile.getTrackCount();
    int tpq = midifile.getTicksPerQuarterNote();

    lowRange = tpq*lowRange*sigA;
    highRange = tpq*highRange*sigA + (tpq*sigA);

    cout << "Tracks: " << tracks << endl;
    cout << "TPQ: " << tpq << endl;

    int track = selectedTrack;
    int randChange;

    for (int event=0; event < midifile[track].size(); event++) {
        //cout << "low " << lowRange << endl;
        //cout << "Real " << midifile[track][event].tick << endl;
        //cout << "high " << highRange << endl;
        if (midifile[track][event].isNoteOn()) {
            if (randb) {
                cout << "Rand" << endl;
                if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){
                    if (note) {
                        cout << "note" << endl;
                        if (midifile[track][event][1] == selectedNote){
                            randChange = rand() % (highChange - lowChange) + (lowChange);
                            cout << randChange << endl;
                            midifile[track][event][2] += randChange; ///random here

                        }
                    }
                    else {
                        cout << "no note" << endl;
                        randChange = rand() % (highChange - lowChange) + (lowChange);
                        cout << randChange << endl;
                        midifile[track][event][2] += randChange; ///random here
                    }

                }
            } else {
                if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){
                    if (note) {
                        if (midifile[track][event][1] == selectedNote){

                            midifile[track][event][2] += highChange;

                        }
                    }
                    else {
                        midifile[track][event][2] += highChange;
                    }
                }

            }
        }
    }

    //midifile.sortTrack(midifile[track]);
    midifile.write("output.mid");
}
