#include "strummify.h"
#include "MidiFile.h"
#include <iostream>
#include <QString>
#include <string>



Strummify::Strummify(QString filename, int amount, int selectedTrack,
                     int lowRange, int highRange, int sigA, int sigB)
{
    //cout << "Something is working" << endl;
    //cout << filename.toStdString().c_str() << endl;
    cout << "this track " << selectedTrack << endl;

    string file = filename.toStdString().c_str();
    MidiFile midifile;
    midifile.read(file);
    midifile.linkNotePairs();
    cout << midifile.status() << endl;
    int tracks = midifile.getTrackCount();
    int tpq = midifile.getTicksPerQuarterNote();

    lowRange = tpq*lowRange*sigA;
    highRange = tpq*highRange*sigA + (tpq*sigA);

    cout << "Tracks: " << tracks << endl;
    cout << "TPQ: " << tpq << endl;


    double value = amount*.001;
    //.001

    int track = selectedTrack;
    bool stroke = true;
    for (int event=0; event < midifile[track].size(); event++) {
        //cout << "low " << lowRange << endl;
        //cout << "Real " << midifile[track][event].tick << endl;
        //cout << "high " << highRange << endl;

        if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){

            if (midifile[track][event].isNoteOn()) {
                int numChordNotes = 1;
                int thisChord = event;
                while (midifile[track][thisChord].tick == midifile[track][thisChord + 1].tick) {
                    numChordNotes++;
                    thisChord++;
                }

                if (numChordNotes > 1) {
                    //we found a chord
                    if (stroke) {
                        cout << "DownStroke" << endl;
                        for (int n = 0; n < numChordNotes; n++) {
                            //cout << midifile[track][event + n].tick << endl;

                            midifile[track][event + n].tick += (tpq*value)*n;
                            //if (midifile[track][event + n].isLinked()) {
                            //    midifile[track][event + n].getLinkedEvent()->tick += (tpq*value)*n;
                            //}
                            cout << midifile[track][event + n].tick << endl;
                            //I think it should be (tpq*.020)
                            //cout << dec << (event + n) << " = " << midifile[track][event + n].tick << endl;
                            //cout << (int)midifile[track][event + n][0] << endl;


                        }
                        if ((midifile[track][event +numChordNotes].tick - midifile[track][event].tick) <= tpq/2) {
                            stroke = false;
                        }
                    } else {
                        cout << "UpStroke" << endl;
                        int z = numChordNotes - 1;
                        for (int n = 0; n < numChordNotes; n++) {
                            //cout << "Added Value " << midifile[track][event + n].tick + (tpq*value)*z << endl;
                            //cout << "z" << z << endl;
                            midifile[track][event + n].tick += (tpq*value)*z;
                            //if (midifile[track][event + n].isLinked()) {
                            //    midifile[track][event + n].getLinkedEvent()->tick += (tpq*value)*z;
                            //}
                            z--;
                            cout << midifile[track][event + n].tick << endl;
                            //cout << dec << (event + n) << " = " << midifile[track][event + n].tick << endl;

                            //cout << (int)midifile[track][event + n][1] << endl;
                            //cout << (int)midifile[track][event + n][2] << endl;
                            //cout << (int)midifile[track][event + n][3] << endl;

                        }
                        if ((midifile[track][event +numChordNotes].tick - midifile[track][event].tick) <= tpq/2) {
                            stroke = true;
                        }
                    }
                }
            //cout << "We found a chord" << endl;
                event += (numChordNotes - 1);
                cout << "\n" << endl;
            }

        }

    }
    midifile.sortTrack(midifile[track]);
    midifile.write("output.mid");

}
