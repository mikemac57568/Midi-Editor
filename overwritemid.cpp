#include "overwritemid.h"
#include "MidiFile.h"
#include "iostream"
#include <string.h>

string file = "";
OverWriteMID::OverWriteMID(QString filename)
{
    //cout << "Hello" << endl;
    MidiFile midifile;
    midifile.read("output.mid");
    //cout << midifile.status() << endl;

    file = filename.toStdString().c_str();
    //Delete this shit to make overwrite
    string ext = file.substr(file.find_last_of("."), file.length());
    int pos = file.length() - ext.length();

    //cout << file << endl;
    //cout << ext << endl;

    file = file.substr(0, pos);
    //cout << file << endl;
    if (file.find("MIDIEDITOR") == std::string::npos) {
        file.append("MIDIEDITOR");
    }
    file.append(".mid");
    /////////////////////////////////////
    midifile.write(file);

    //cout << midifile.status() << endl;
}
