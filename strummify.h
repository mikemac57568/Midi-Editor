#ifndef STRUMMIFY_H
#define STRUMMIFY_H
#include <QString>



class Strummify
{
public:
    Strummify(QString filename, int amount, int selectedTrack,
              int lowRange,int highRange, int sigA, int sigB);
};

#endif // STRUMMIFY_H
