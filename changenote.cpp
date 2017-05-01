#include "changenote.h"
#include <QString>
#include "MidiFile.h"
#include <iostream>
#include <string>

ChangeNote::ChangeNote(QString filename, int selectedNote, int change, int selectedTrack,
                       int lowRange,int highRange, int sigA, int sigB)
{
    cout << "Changing note " << selectedNote << " to " <<
            change << endl;
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

    for (int event=0; event < midifile[track].size(); event++) {
        cout << "low " << lowRange << endl;
        cout << "Real " << midifile[track][event].tick << endl;
        cout << "high " << highRange << endl;

        if (midifile[track][event].tick >= lowRange && midifile[track][event].tick < highRange){
            if (midifile[track][event][1] == selectedNote){

                midifile[track][event][1] = change;

            }

        }

    }

    midifile.write("output.mid");
}
