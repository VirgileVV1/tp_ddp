

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cmath>

#include <stack>
#include <deque>
#include <vector>
#include "Point.hpp"


class Map
{

private:

    // L'objet map est un pointeur vers un deque a 2 dimension contenant des Point

public:
    std::shared_ptr<std::deque<std::deque<Point>>> pMap;

    Map();
    Map(unsigned int mapSize, int initType);
    ~Map();
    void destroyMap();
    unsigned int getNbRow();
    unsigned int getNbCol();
    void print();
    void printXY();
    void add(Point p);
    Point getPointByIndexes(unsigned int row, unsigned int col);
    int* getPointIndexes(Point p);
    void setPassable(int i, int j, bool _passable);
    void addSouth(unsigned int n);
    void addNorth(unsigned int n);
    void addEast(unsigned int n);
    void addWest(unsigned int n);

    // METHODES CONCERNANT LA RECHERCHE DE CHEMIN :
    bool isValid(int x, int y);
    bool isDestination(int x, int y, Point dest);
    double calculateH(int x, int y, Point dest);
    std::vector<Point> aStar(Point origin, Point dest);
    std::vector<Point> makePath(std::vector<std::vector<Point>> map, Point dest);

};

#endif // MAP_H