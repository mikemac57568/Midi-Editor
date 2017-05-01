#include "parsetrack.h"
#include "MidiFile.h"
#include <iostream>
#include <QString>
#include <string>
#include <QtAlgorithms>

QList<int> noteList;
MidiFile midifile;

parseTrack::parseTrack(QString filename)
{
    string file = filename.toStdString().c_str();
    midifile.read(file);

    tracks = midifile.getTrackCount();
    tpq = midifile.getTicksPerQuarterNote();


}

int parseTrack::getTrackCount() {
    return tracks;
}

int parseTrack::getTPQ() {
    return tpq;
}

QList<int> parseTrack::getNoteList(int track) {
    noteList.clear();
    for (int event=0; event < midifile[track].size(); event++) {
        if (midifile[track][event].isNoteOn()) {
            if(!noteList.contains(midifile[track][event].getKeyNumber())) {
                noteList.append(midifile[track][event].getKeyNumber());
            }
        }
    }

    std::stable_sort(noteList.begin(), noteList.end());

    return noteList;
}




