// tp_dpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <deque>



struct Point
{
    int x;
    int y;

    Point()
    {
    }
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    ~Point()
    {}

};

void printDeque(std::deque<std::deque<Point>> *d)
{
    for (auto ligne : *d)
    {
        for (auto val : ligne)
        {
            std::cout << val.x << "/" << val.y << " ";
        }
        std::cout << std::endl;
    }
}

std::deque<std::deque<Point>> tdd;


void initDeque(int n, std::deque<std::deque<Point>> * ptdd)
{
    std::deque<Point> td;
    Point p;

    for (int i = 0; i < n; i++)
    {
         td.clear();
         for (int j = 0; j < n; j++)
         {
             p.x = i;
             p.y = j;
             td.push_back(p);
         }
         ptdd->push_back(td);
    }
}

void addNorth(std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    int val = ptdd->at(0).at(0).x;

    for (int i = 0; i < ptdd->size(); i++)
    {
      
        p.x = val-1;
        p.y = i;
        td.push_back(p);
    }
    ptdd->push_front(td);

}
void addEast(std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    int valY;
    for (int i = 0; i < ptdd->size(); i++)
    {
        valY = ptdd->at(i).at(ptdd->at(i).size()-1).y; // On lui donne la valeur Y de son voisin direct
        p.x = ptdd->at(i).at(0).x; // On lui donne la valeur X de son voisin en debut de ligne
        p.y = valY + 1;
        ptdd->at(i).push_back(p);
    }
}

void addWest(std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    for (int i = 0; i < ptdd->size(); i++)
    {
        p.x = ptdd->at(i).at(0).x; // Il prend la valeur X du premier de la ligne
        p.y = ptdd->at(i).at(0).y - 1; // Il prend la valeur Y - 1 du premier de la ligne
        ptdd->at(i).push_front(p);
    }
}

void addSouth(std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    for (int i = 0; i < ptdd->at(0).size(); i++)
    {
        p.x = ptdd->at(ptdd->size()-1).at(0).x +1; // Il prend la valeur X + 1 du dernier element de la ligne i
        p.y = ptdd->at(ptdd->size() - 1).at(i).y ; // Il prend la valeur en Y du dernier element  de la ligne i
        td.push_back(p);
    }
    ptdd->push_back(td);
}

int main()
{
    std::deque<std::deque<Point>> tdd;
    std::deque<std::deque<Point>> * ptdd;
    ptdd = &tdd;
    initDeque(9, ptdd);
    addNorth(ptdd);
    addEast(ptdd);
    addWest(ptdd);
    addSouth(ptdd);
    printDeque(ptdd);







}