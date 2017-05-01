#include "changedelta.h"
#include <QString>
#include "MidiFile.h"
#include <string>
#include <iostream>

ChangeDelta::ChangeDelta(QString filename, int selectedNote, int highChange, int lowChange, int selectedTrack,
                         int lowRange,int highRange, int sigA, int sigB, bool note, bool randb)
{
    cout << "Changing note " << selectedNote << " by " <<
            highChange << endl;
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
    cout << "Note " << note << endl;
    cout << "Rand" << randb << endl;

    int track = selectedTrack;
    int randChange;
    //int offChange;

    for (int event=0; event < midifile[track].size(); event++) {
        //cout << "low " << lowRange << endl;
        //cout << "Real " << midifile[track][event].tick << endl;
        //cout << "high " << highRange << endl;
        if (midifile[track][event].isNoteOn()) {
            //if user requested random value
            if (randb) {
                //if value is in requested range (range passed in. doesn't matter if user selected)
                if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){
                    //if user requested only change one note
                    if (note) {
                        //if it is the selected note
                        if (midifile[track][event][1] == selectedNote){
                            //create the random value
                            randChange = (rand() % (highChange - lowChange)) + (lowChange);
                            //apply value to event
                            if (midifile[track][event].tick + randChange >= 0 &&
                                    midifile[track][event].tick + randChange < 0x0FFFffff) {
                                cout << "Before: " << midifile[track][event].tick << endl;
                                midifile[track][event].tick += randChange; ///random here
                                cout << "After: " << midifile[track][event].tick << endl;
                                //apply value to off-note
                                if (midifile[track][event].isLinked()) {
                                    midifile[track][event].getLinkedEvent()->tick += randChange;
                                }
                            }
                        }
                     //user wants to apply to all notes, so we need to keep chords together
                     } else {

                        randChange = (rand() % (highChange - lowChange)) + (lowChange);
                        if (midifile[track][event].tick + randChange >= 0 &&
                                midifile[track][event].tick + randChange < 0x0FFFffff) {
                            cout << "Before: " << midifile[track][event].tick << endl;
                            midifile[track][event].tick += randChange; ///random here
                            cout << "After: " << midifile[track][event].tick << endl;
                            //apply value to off-note
                            if (midifile[track][event].isLinked()) {
                                midifile[track][event].getLinkedEvent()->tick += randChange;
                            }
                        }
                        //apply value to event
                        //if (midifile[track][event].tick + randChange >= 0 &&
                        //        midifile[track][event].tick + randChange < 0x0FFFffff) {
                        //    int numChordNotes = 1;
                        //    int thisChord = event;
                        //    while (midifile[track][thisChord].tick == midifile[track][thisChord + 1].tick) {
                        //        numChordNotes++;
                        //        thisChord++;
                        //    }
                        //    randChange = rand() % (highChange - lowChange) + (lowChange);

                        //    for (int n = 0; n < numChordNotes; n++) {
                        //        cout << randChange << endl;
                        //        cout << "Before: " << midifile[track][event + n].tick << endl;
                        //        midifile[track][event + n].tick += randChange;
                        //        cout << "After: " << midifile[track][event + n].tick << endl;
                        //        if (midifile[track][event + n].isLinked()) {
                        //            midifile[track][event + n].getLinkedEvent()->tick += randChange;
                        //        }
                        //    }
                            //skip ahead past the chord
                        //    event += (numChordNotes - 1);
                        //}
                     }
                  }
              //user didn't want a random value
              } else {
                if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){
                    if (note) {
                        if (midifile[track][event][1] == selectedNote){
                            cout << "Before: " << midifile[track][event].tick << endl;
                            if (midifile[track][event].tick + highChange >= 0 &&
                                    midifile[track][event].tick + highChange < 0x0FFFffff) {
                                midifile[track][event].tick += highChange;
                                cout << "After: " << midifile[track][event].tick << endl;
                                if (midifile[track][event].isLinked()) {
                                    midifile[track][event].getLinkedEvent()->tick += highChange;
                                }
                            }

                        }
                    } else {
                        cout << "Before: " << midifile[track][event].tick << endl;
                        if (midifile[track][event].tick + highChange >= 0 &&
                                midifile[track][event].tick + highChange < 0x0FFFffff) {
                            midifile[track][event].tick += highChange;
                            cout << "After: " << midifile[track][event].tick << endl;
                            if (midifile[track][event].isLinked()) {
                                midifile[track][event].getLinkedEvent()->tick += highChange;
                            }
                        }
                    }
                }
            }
        }
    }
    try {
        midifile.sortTrack(midifile[track]);
        midifile.write("output.mid");
    } catch (...) {
        cout << "we did it" << endl;
    }

    cout << midifile.status() << endl;
    cout << "Hello" << endl;
}
