#ifndef CHANGEVOLUME_H
#define CHANGEVOLUME_H
#include <QString>


class ChangeVolume
{
public:
    ChangeVolume(QString filename, int selectedNote, int highChange, int lowChange, int selectedTrack,
                 int lowRange,int highRange, int sigA, int sigB, bool note, bool randb);
};

#endif // CHANGEVOLUME_H
