// tp_dpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <deque>

struct Point
{
    int x;
    int y;
    bool passable;

    Point() 
    {
        x = 0; 
        y = 0; 
        passable = true;
    }

    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
        passable = true;
    }

    ~Point(){}
};


// Classe representant la carte
class Map 
{
private:
    // l'objet map est un pointeur vers un deque a 2 dimension contenant des Point
    std::shared_ptr<std::deque<std::deque<Point>>> pMap;

public:  

    Map(unsigned int n)
    {
        init(n);
    }

    Map()
    {
    }

    ~Map()
    {}

    void init(unsigned int n)
    {
        pMap = std::make_shared<std::deque<std::deque<Point>>>();

        std::deque<Point> td;
        Point p;

        for (unsigned int i = 0; i < n; i++)
        {
            td.clear();
            for (unsigned int j = 0; j < n; j++)
            {
                p.x = i;
                p.y = j;
                td.push_back(p);
            }
            tableau->push_back(td);
        }
    }

    void destroyMap()
    {
        // detruir la map
        
    }

    void print()
    {
        for (auto ligne : *pMap)
        {
            for (auto val : ligne)
            {
                std::cout << val.x << "/" << val.y << " ";
            }
            std::cout << std::endl;
        }
    }

    int* getPointCoord(Point p)
    {
        int* coord = new int[2];

        for (int i = 0; i < pMap->size(); i++)
        {
            for (int j = 0; j < pMap->at(i).size(); j++)
            {
                if ((p.x == pMap->at(i).at(j).x) && (p.y == pMap->at(i).at(j).y))
                {
                    coord[0] = i;
                    coord[1] = j;
                    return coord;
                }
            }
        }

        coord = nullptr;
        return coord;
    }

    // p1 point de depart, p2 point d'arrivee
    void searchingPath(Point p1, Point p2, std::deque<std::deque<Point>>* ptdd)
    {
        Point test;
        test = p1;
        float distance = 0;
        int memoire = 0;

        while (test.x != p2.x && test.y != p2.y)
        {
            if (test.x > p2.x && test.y > p2.y)
            {
                test.x -= 1;
                test.y -= 1;
                if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false) 
                {
                   // cas où la diagonale est non passable
                    test.x += 1;
                    // check si le point du bas est passable
                    if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                    {
                        test.x -= 1;
                        test.y += 1;
                        // check si le point de gauche est passable
                        if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                        {
                            memoire += 1;
                        }
                        else
                        {
                            distance += 1;
                        }
                    }
                    else
                    {
                        distance += 1;
                    }
                }
                // si la diagonale est passable, on enchaîne
                distance += sqrt(2);
                // go vers bas gauche
            }
            else if (test.x < p2.x && test.y > p2.y)
            {
                test.x += 1;
                test.y -= 1;
                if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false) {
                    // cas où la diagonale est non passable
                    test.x -= 1;
                    // check si le point du bas est passable
                    if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                    {
                        test.x += 1;
                        test.y += 1;
                        // check si le point de droite est passable
                        if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                        {
                            memoire += 1;
                        }
                        else
                        {
                            distance += 1;
                        }
                    }
                    else
                    {
                        distance += 1;
                    }
                }
                // si la diagonale est passable, on enchaîne
                distance += sqrt(2);
                // go vers bas droite 
            }
            else if (test.x > p2.x && test.y < p2.y)
            {
                test.x -= 1;
                test.y += 1;
                if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false) {
                    // cas où la diagonale est non passable
                    test.x += 1;
                    // check si le point du haut est passable
                    if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                    {
                        test.x -= 1;
                        test.y -= 1;
                        // check si le point de gauche est passable
                        if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                        {
                            memoire += 1;
                        }
                        else
                        {
                            distance += 1;
                        }
                    }
                    else
                    {
                        distance += 1;
                    }
                }
                // si la diagonale est passable, on enchaîne
                distance += sqrt(2);
                // go vers haut gauche
            }
            else if (test.x < p2.x && test.y < p2.y)
            {
                test.x += 1;
                test.y += 1;
                if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false) {
                    // cas où la diagonale est non passable
                    test.x -= 1;
                    // check si le point du haut est passable
                    if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                    {
                        test.x += 1;
                        test.y -= 1;
                        // check si le point de droite est passable
                        if (ptdd->at(getPointCoord(test)[0]).at(getPointCoord(test)[1]).passable == false)
                        {
                            memoire += 1;
                        }
                        else
                        {
                            distance += 1;
                        }
                    }
                    else
                    {
                        distance += 1;
                    }
                }
                // si la diagonale est passable, on enchaîne
                distance += sqrt(2);
                // go vers haut droite 
            }
        }
        std::cout << "Chemin entre les 2 points possibles." << std::endl;
    }
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


void initDeque(int n, std::deque<std::deque<Point>> * ptdd)
{
    std::deque<Point> td;
    Point p;

    for (int i = 0; i < n; i++)
    {
         td.clear();
         for (int j = 0; j < n; j++)
         {
             p.x = j;
             p.y = i;
             td.push_back(p);
         }
         ptdd->push_front(td);
    }
}

void addNorth(int n, std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;   
    int val = ptdd->at(0).at(0).y;

    for (int i = 0; i < n; i++)
    {       
        for (int j = 0; j < ptdd->at(0).size(); j++)
        {
            p.x = ptdd->at(ptdd->size() - 1).at(j).x;
            p.y = val + 1;
            td.push_back(p);
        }
        ptdd->push_front(td);
        td.clear();
        val++;
    }
}

void addEast(int n, std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    int valX;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < ptdd->size(); j++)
        {
            valX = ptdd->at(j).at(ptdd->at(j).size() - 1).x; // On lui donne la valeur X de son voisin direct
            p.x = valX + 1;
            p.y = ptdd->at(j).at(0).y; // On lui donne la valeur Y de son voisin en debut de ligne
            ptdd->at(j).push_back(p);
        }
    }
}

void addWest(int n, std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < ptdd->size(); j++)
        {
            p.x = ptdd->at(j).at(0).x - 1; // Il prend la valeur X - 1 du premier de la ligne
            p.y = ptdd->at(j).at(0).y; // Il prend la valeur Y du premier de la ligne
            ptdd->at(j).push_front(p);
        }
    }
}

void addSouth(int n, std::deque<std::deque<Point>>* ptdd)
{
    std::deque<Point> td;
    Point p;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < ptdd->at(0).size(); j++)
        {
            p.x = ptdd->at(ptdd->size() - 1).at(j).x; // Il prend la valeur X du dernier element de la ligne i
            p.y = ptdd->at(ptdd->size() - 1).at(j).y - 1; // Il prend la valeur en Y - 1 du dernier element  de la ligne i
            td.push_back(p);
        }
        ptdd->push_back(td);
        td.clear();
    }
    
}

void addPoint(int x, int y, std::deque<std::deque<Point>>* ptdd)
{
    if (x > ptdd->at(ptdd->size()-1).at(ptdd->size()-1).x)
    {
        addEast(x - ptdd->at(0).at(ptdd->size()-1).x, ptdd);
    }
    else if (x < ptdd->at(0).at(0).x)
    {
        addWest(abs(x), ptdd);
    }
    if (y > ptdd->at(ptdd->size()-1).at(ptdd->size()-1).y)
    {
        addNorth(y - ptdd->at(0).at(0).y, ptdd);
    } 
    else if (y < ptdd->at(0).at(0).y)
    {
        addSouth(abs(y), ptdd);
    }

}



int main()
{
    std::deque<std::deque<Point>> tdd;
    std::deque<std::deque<Point>> * ptdd;
    Point p;

   /* unsigned int n = 9;
    Map m(n);
    m.print();*/

    ptdd = &tdd;
    initDeque(5,ptdd);
    /*addNorth(3, ptdd);*/
    addPoint(-6,-8, ptdd);
    printDeque(ptdd);
    
    //Map::printMap();

    //ptdd = &tdd;
    //initDeque(9, ptdd);
    //addNorth(ptdd);
    //addEast(ptdd);
    //addWest(ptdd);
    //addSouth(ptdd);
    //printDeque(ptdd);
}
