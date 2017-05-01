#ifndef CHANGEDELTA_H
#define CHANGEDELTA_H
#include <QString>


class ChangeDelta
{
public:
    ChangeDelta(QString filename, int selectedNote, int highChange, int lowChange, int selectedTrack,
                int lowRange,int highRange, int sigA, int sigB, bool note, bool randb);
};

#endif // CHANGEDELTA_H
