// tp_dpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <deque>
#include <vector>

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

    Point(int _x, int _y, bool _passable)
    {
        x = _x;
        y = _y;
        passable = _passable;
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
        init(n, 2);
    }

    Map()
    {
    }

    ~Map()
    {}


    /**
    * @param n Taille de la matrice (n*n)
    * @param initType 
    *       0 que des non passable
    *       1 que des passable
    *       2 aleatoire
    */
    void init(unsigned int n, int initType)
    {
        pMap = std::make_shared<std::deque<std::deque<Point>>>();

        std::deque<Point> td;
        Point p;

        if (initType == 0)
        {
            p.passable = false;
        }
        else
        {
            p.passable = true;
        }

        for (unsigned int i = 0; i < n; i++)
        {
            td.clear();
            for (unsigned int j = 0; j < n; j++)
            {
                p.x = j;
                p.y = i;
                if (initType == 2)
                {
                    p.passable = (rand() % 2);
                }
                td.push_back(p);
            }
            pMap->push_front(td);
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
                if (val.passable)
                {
                    std::cout << "o" << "\t";
                } 
                else
                {
                    std::cout << "x" << "\t";
                }
            }
            std::cout << std::endl;
        }
    }

    void printXY()
    {
        for (auto ligne : *pMap)
        {
            for (auto val : ligne)
            {
                std::cout << val.x << "/" << val.y << "\t";
            }
            std::cout << std::endl;
        }
    }

    /**
    * Ajoute un point dans le tableau si il n'existe pas
    */
    void add(Point p)
    {
        if (p.x > pMap->at(pMap->size() - 1).at(pMap->size() - 1).x)
        {
            addEast(p.x - pMap->at(0).at(pMap->size() - 1).x);
        }
        else if (p.x < pMap->at(0).at(0).x)
        {
            addWest(abs(p.x));
        }
        if (p.y > pMap->at(pMap->size() - 1).at(pMap->size() - 1).y)
        {
            addNorth(p.y - pMap->at(0).at(0).y);
        }
        else if (p.y < pMap->at(0).at(0).y)
        {
            addSouth(abs(p.y));
        }

        int* coord = new int[2];
        coord = getPointCoord(p);
        pMap->at(coord[0]).at(coord[1]).passable = p.passable;
    }

    /**
    * retourne les coordonnées du point passe en parametre
    */
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




    /**
    * ajoute une ligne avant la première ligne de la carte 
    */
    void addNorth(int n)
    {
        std::deque<Point> td;
        Point p;
        int val = pMap->at(0).at(0).y;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < pMap->at(0).size(); j++)
            {
                p.x = pMap->at(pMap->size() - 1).at(j).x;
                p.y = val + 1;
                td.push_back(p);
            }
            pMap->push_front(td);
            td.clear();
            val++;
        }
    }

    /**
    * ajoute une ligne apres la derniere ligne de la carte
    */
    void addSouth(int n)
    {
        std::deque<Point> td;
        Point p;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < pMap->at(0).size(); j++)
            {
                p.x = pMap->at(pMap->size() - 1).at(j).x; // Il prend la valeur X du dernier element de la ligne i
                p.y = pMap->at(pMap->size() - 1).at(j).y - 1; // Il prend la valeur en Y - 1 du dernier element  de la ligne i
                td.push_back(p);
            }
            pMap->push_back(td);
            td.clear();
        }

    }

    /**
    * ajoute une colonne apres la derniere colonne de la carte
    */
    void addEast(int n)
    {
        std::deque<Point> td;
        Point p;
        int valX;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < pMap->size(); j++)
            {
                valX = pMap->at(j).at(pMap->at(j).size() - 1).x; // On lui donne la valeur X de son voisin direct
                p.x = valX + 1;
                p.y = pMap->at(j).at(0).y; // On lui donne la valeur Y de son voisin en debut de ligne
                pMap->at(j).push_back(p);
            }
        }
    }

    /**
    * ajoute une colonne avant la premiere colonne de la carte
    */
    void addWest(int n)
    {
        std::deque<Point> td;
        Point p;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < pMap->size(); j++)
            {
                p.x = pMap->at(j).at(0).x - 1; // Il prend la valeur X - 1 du premier de la ligne
                p.y = pMap->at(j).at(0).y; // Il prend la valeur Y du premier de la ligne
                pMap->at(j).push_front(p);
            }
        }
    }

    //searchPath()

};



int main()
{

    unsigned int n = 9;
    Map m(n);
  /*  m.addNorth(1);
    m.addNorth(1);
    m.addSouth(1);
    m.addSouth(1);
    m.addEast(1);
    m.addEast(1);
    m.addWest(1);
    m.addWest(1);*/

    Point p1(1,2, false);
    m.add(p1);

    m.print();
    m.printXY();

  
    //Map::printMap();

}