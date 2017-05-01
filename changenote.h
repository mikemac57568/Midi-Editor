#ifndef CHANGENOTE_H
#define CHANGENOTE_H
#include <QString>


class ChangeNote
{
public:
    ChangeNote(QString filename, int selectedNote, int change, int selectedTrack,
               int lowRange,int highRange, int sigA, int sigB);
};

#endif // CHANGENOTE_H
