// tp_dpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>

// Structure representant un point sur la carte 
// Chaque Point a des coordonnees entiers X et Y
// Et un type passable / non passable
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

    Map()
    {
        pMap = std::make_shared<std::deque<std::deque<Point>>>();
    }


    /**
    * @param mapSize Taille de la matrice (mapSize*mapSize)
    * @param initType
    *       0 que des non passable
    *       1 que des passable
    *       2 aleatoire
    **/
    Map(unsigned int mapSize, int initType)
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

        for (unsigned int i = 0; i < mapSize; i++)
        {
            td.clear();
            for (unsigned int j = 0; j < mapSize; j++)
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


    ~Map()
    {}


    void destroyMap()
    {
        // detruire la map
    }


    /**
    * Retourne le nombre de ligne de la carte
    **/
    unsigned int getNbRow()
    {

        return pMap->size();
    }


    /**
    * Retourne le nombre de colonne de la carte
    **/
    unsigned int getNbCol()
    {
        return pMap->at(0).size();
    }


    /**
    * Affiche dans la console la carte avec des o si la case est passable
    * et des x si la case n'est pas passable 
    **/
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


    /**
    * Affiche dans la console chaque point de la carte avec leur coordonnees
    **/
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
    * Ajoute un point dans le tableau (En remplacant l'ancien point)
    **/
    void add(Point p)
    {

        if (p.x > pMap->at(pMap->size() - 1).at(pMap->at(0).size() - 1).x)
        {
            addEast(p.x - pMap->at(0).at(pMap->size() - 1).x);
        }
        else if (p.x < pMap->at(0).at(0).x)
        {
            addWest(abs(p.x));
        }
        if (p.y > pMap->at(pMap->size() - 1).at(pMap->at(0).size() - 1).y)
        {
            addNorth(p.y - pMap->at(0).at(0).y);
        }
        else if (p.y < pMap->at(0).at(0).y)
        {            
            addSouth(abs(p.y));
        }

        int* coord = new int[2];
        coord = getPointIndexes(p);
        pMap->at(coord[0]).at(coord[1]).passable = p.passable;
 
    }


    /**
    * Retourne le point duquel on passe les indices en parametres
    * @param row Indice de la ligne
    * @param col Indice de la colonne
    **/
    Point getPointByIndexes(unsigned int row, unsigned int col)
    {
        if ((row >= pMap->size()) || (col >= pMap->at(row).size()))
        {
            std::cout << "Vous essayez d'acceder a une case qui n'existe pas (" << row << ", " << col << ")" << std::endl;
        }

        return pMap->at(row)[col];
    }


    /**
    * Retourne un pointeur vers les coordonnées X et Y du point passe en parametre
    * [0] = X
    * [1] = Y
    * 
    * Si le point n'est pas trouve, retourne nullptr
    * 
    * @param p Le point a partir duquel on veut les coordonnees
    **/
    int* getPointIndexes(Point p)
    {
        int* indexes = new int[2];

        for (int i = 0; i < pMap->size(); i++)
        {
            for (int j = 0; j < pMap->at(i).size(); j++)
            {
                if ((p.x == pMap->at(i).at(j).x) && (p.y == pMap->at(i).at(j).y))
                {
                    indexes[0] = i;
                    indexes[1] = j;
                    return indexes;
                }
            }
        }

        indexes = nullptr;
        return indexes;
    }


    /**
    * Ajoute une ligne avant la première ligne de la carte 
    **/
    void addNorth(int n)
    {
        std::deque<Point> td;
        Point p;
        int val = pMap->at(0).at(0).y;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < pMap->at(i).size(); j++)
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
    * Ajoute une ligne apres la derniere ligne de la carte
    **/
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
    **/
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
    **/
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


};

// x et y les coordonnees
void perlin(float x, float y)
{

}

int main()
{

    unsigned int n = 8;
    Map m(n, 2);

  /*  m.addNorth(1);
    m.addNorth(1);
    m.addSouth(1);
    m.addSouth(1);
    m.addEast(1);
    m.addEast(1);
    m.addWest(1);
    m.addWest(1);*/


    Point p1(2, 2, true);
    Point p2(0, 0, true);
    Point p3(0, 7, true);
    Point p4(7, 2, true);

    m.add(p1);
    m.add(p2);
    m.add(p3);
    m.add(p4);

    m.print();
    m.printXY();

    // Creation d'une fenetre 800 par 800
    sf::RenderWindow window(sf::VideoMode(800, 800), "Nom de la fenetre test");

    float cellSize = 100.0;
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(cellSize, cellSize));

    while (window.isOpen()) 
    {

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        // il faut effacer avant de reafficher
        window.clear();

        for (int i = 0; i < m.getNbRow(); ++i)
        {
            for (int j = 0; j < m.getNbCol(); ++j)
            {
                cell.setSize(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setFillColor(sf::Color::White);
                window.draw(cell);

                if (!m.getPointByIndexes(i,j).passable)
                {
                    cell.setFillColor(sf::Color::Black);
                }
              
                if ((m.getPointByIndexes(i, j).x == p1.x) && (m.getPointByIndexes(i, j).y == p1.y))
                {
                    cell.setFillColor(sf::Color::Blue);
                }

                if ((m.getPointByIndexes(i, j).x == p2.x) && (m.getPointByIndexes(i, j).y == p2.y))
                {
                    cell.setFillColor(sf::Color::Red);
                }

                cell.setSize(sf::Vector2f(cellSize - 20, cellSize - 20));
                cell.setPosition((j * cellSize + 10), (i * cellSize) + 10);
                window.draw(cell);
             
            }
        }

        window.display();
    }


    return 0;

}