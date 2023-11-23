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
        x = 0; 
        y = 0; 
    }

    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    ~Point(){}
};



// Classe representant la carte
class Map 
{
private:
    // l'objet map est un pointeur vers un deque a 2 dimension contenant des Point
    std::shared_ptr<std::deque<std::deque<Point>>> tableau;

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
        tableau = std::make_shared<std::deque<std::deque<Point>>>();

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
        for (auto ligne : *tableau)
        {
            for (auto val : ligne)
            {
                std::cout << val.x << "/" << val.y << "\t";
            }
            std::cout << std::endl;
        }
    }



    /**
    * ajoute une ligne avant la première ligne de la carte 
    */
    void addNorth()
    {
        std::deque<Point> td;
        Point p;

        for (int i = 0; i < tableau->at(0).size(); i++)
        {
            p.x = tableau->at(0).at(0).x - 1;
            p.y = i;
            td.push_back(p);
        }

        tableau->push_front(td);
    }

    /**
    * ajoute une ligne apres la derniere ligne de la carte
    */
    void addSouth()
    {
        std::deque<Point> td;
        Point p;

        for (int i = 0; i < tableau->at(0).size(); i++)
        {
            p.x = tableau->at(tableau->size() - 1).at(0).x + 1; // Il prend la valeur X + 1 du dernier de la ligne i
            p.y = tableau->at(tableau->size() - 1).at(i).y; // Il prend la valeur Y du dernier  de la ligne i
            td.push_back(p);
        }

        tableau->push_back(td);
    }

    /**
    * ajoute une colonne apres la derniere colonne de la carte
    */
    void addEast()
    {
        std::deque<Point> td;
        Point p;

        for (int i = 0; i < tableau->size(); i++)
        {
            p.x = tableau->at(i).at(0).x; // On lui donne la valeur X de son voisin en debut de ligne
            p.y = tableau->at(i).at(tableau->at(i).size() - 1).y + 1; // On lui donne la valeur Y de son voisin direct (fin de ligne)
            tableau->at(i).push_back(p);
        }
    }

    /**
    * ajoute une colonne avant la premiere colonne de la carte
    */
    void addWest()
    {
        std::deque<Point> td;
        Point p;

        for (int i = 0; i < tableau->size(); i++)
        {
            p.x = tableau->at(i).at(0).x; // Il prend la valeur X du premier de la ligne
            p.y = tableau->at(i).at(0).y - 1; // Il prend la valeur Y - 1 du premier de la ligne
            tableau->at(i).push_front(p);
        }
    }
};



int main()
{

    unsigned int n = 9;
    Map m(n);

    /*m.addNorth();
    m.addNorth();
    m.addSouth();
    m.addSouth();
    m.addEast();
    m.addEast();
    m.addWest();
    m.addWest();*/

    Point p1(-2,-2);

    m.print();

  
    //Map::printMap();

}