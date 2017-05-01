#ifndef PARSETRACK_H
#define PARSETRACK_H
#include <QString>
#include <QList>


class parseTrack
{
    int tracks, tpq;
 public:
    parseTrack(QString filename);
    int getTrackCount();
    int getTPQ();
    QList<int> getNoteList(int track);
    int getNoteListLength();
};

#endif // PARSETRACK_H
