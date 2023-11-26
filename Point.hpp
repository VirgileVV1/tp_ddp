

#ifndef POINT_H
#define POINT_H

// Structure representant un point sur la carte 
// Chaque Point a des coordonnees entiers X et Y
// Et un type passable / non passable
struct Point
{
    int x;
    int y;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
    bool passable;

    Point()
    {
        x = 0;
        y = 0;
        passable = true;
        parentX = 0;
        parentY = 0;
        gCost = 0;
        hCost = 0;
        fCost = 0;
    }

    Point(int _x, int _y, bool _passable)
    {
        x = _x;
        y = _y;
        passable = _passable;
        parentX = 0;
        parentY = 0;
        gCost = 0;
        hCost = 0;
        fCost = 0;
    }

    ~Point() {}
};

#endif // POINT_H
