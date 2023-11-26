// tp_dpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stack>
#include "Map.hpp"
#include "Point.hpp"


/**
* Surchage de l'operateur < pour qu'il puisse prendre en compte des points
**/
inline bool operator < (const Point& lhs, const Point& rhs)
{
    return lhs.fCost < rhs.fCost;
}

/**
* Verifie si un pint est contenu dans le vecteur de point
**/
bool contains(Point p, std::vector<Point> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if ((p.x == v[i].x)
            &&
            (p.y == v[i].y))
        {
            return true;
        }
    }
    return false;
}


// ******* Methode pour le bruit de perlin ******* //

/**
* Calcul des vecteurs de taille 1 pour chaque coin de la grille
* @param gridSize Taille de la grille
**/
std::shared_ptr<std::vector<std::vector<std::vector<float>>>> initUnitVectors(int gridSize)
{

    std::shared_ptr<std::vector<std::vector<std::vector<float>>>> unitVectors;
    unitVectors = std::make_shared<std::vector<std::vector<std::vector<float>>>>();
    ;
    std::vector<std::vector<float>> rowVec;
    std::vector<float> unitVec;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i <= gridSize; i++)
    {
        rowVec.clear();
        for (int j = 0; j <= gridSize; j++)
        {
            unitVec.clear();

            float angle = (float)(rand() % 360); // en degres
            angle = angle * 3.14 / 180;

            float x = std::cos(angle);
            float y = std::sin(angle);

            unitVec.push_back(x);
            unitVec.push_back(y);
            rowVec.push_back(unitVec);
        }
        unitVectors->push_back(rowVec);
    }
    return unitVectors;
}


/**
* Retourne la partie decimal d'un nombre a virgule
**/
float getDecimalPart(float val)
{
    return val - (int)val;
}


/**
* Fonction permettant de rendre la separation fluide
**/
float cubicInterpolation(float x, float y, int w)
{
    return (y - x) * (3 - w * 2) * w * w + x;
}


/**
* Calcule de produit scalaire
**/
float dotProduct(std::vector<float> v1, std::vector<float> v2)
{
    float res = 0;
    for (size_t i = 0; i < v1.size(); i++)
    {
        res = res + (v1.at(i) * v2.at(i));
    }
    return res;
}


/**
* @param x
* @param y
* @param unitVectors Vecteur aleatoire de taille 1 pour chaque intersection de la grille
**/
float perlinNoise(float x, float y, std::shared_ptr<std::vector<std::vector<std::vector<float>>>> unitVectors)
{
    // On calcule la distance entre notre point et chaque coin (de la grille)
    std::vector<float> dTopLeft;
    dTopLeft.push_back(getDecimalPart(x));
    dTopLeft.push_back(getDecimalPart(y));

    std::vector<float> dTopRight;
    dTopRight.push_back(1 - getDecimalPart(x));
    dTopRight.push_back(getDecimalPart(y));

    std::vector<float> dBottomLeft;
    dBottomLeft.push_back(getDecimalPart(x));
    dBottomLeft.push_back(1 - getDecimalPart(y));

    std::vector<float> dBottomRight;
    dBottomRight.push_back(1 - getDecimalPart(x));
    dBottomRight.push_back(1 - getDecimalPart(y));


    // produit scalaire entre la distance du point au coin top left et le unit vecteur du coin top left
    float dotProductLeft = dotProduct(dTopLeft, unitVectors->at((int)x).at((int)y));

    float dotProductRight = dotProduct(dTopLeft, unitVectors->at((int)x).at(ceil(y)));
    float interpolationTop = cubicInterpolation(dotProductLeft, dotProductRight, getDecimalPart(x));

    // produit scalaire bottom
    dotProductLeft = dotProduct(dBottomLeft, unitVectors->at(ceil(x)).at((int)y));

    dotProductRight = dotProduct(dBottomLeft, unitVectors->at(ceil(x)).at(ceil(y)));
    float interpolationBottom = cubicInterpolation(dotProductLeft, dotProductRight, getDecimalPart(x));

    float val = cubicInterpolation(interpolationTop, interpolationBottom, getDecimalPart(y));
    return val;
}

// ******* ******* //




int main()
{

    // Taille de la fenetre en pixels
    unsigned int windowSize = 500;

    // Taille de la carte
    unsigned int n = 100;
    
    // Taille de la grille (<n)
    float unitVectorsSize = 5;

    Map m(n, 2);

    // On definit les cases comme passable / non passable selon le resultat du bruit de perlin
    
    std::shared_ptr<std::vector<std::vector<std::vector<float>>>> unitVectors = initUnitVectors(unitVectorsSize);
    float div = n / unitVectorsSize;

    for (int i = 0; i < m.getNbRow(); ++i)
    {
        for (int j = 0; j < m.getNbCol(); ++j)
        {

            float val = perlinNoise((float)j / div, (float)i / div, unitVectors);
            if (val > 0)
            {
                m.setPassable(i, j, true);
            }
            else
            {
                m.setPassable(i, j, false);
            }

        }
    }

    Point p1(1, 1, true);
    Point p2(1, 5, true);

    m.add(p1);
    m.add(p2);

    //m.printXY();

    /*std::vector<Point> path = m.aStar(p1, p2);
    std::cout << "size " << path.size() << std::endl;
    
    // On affiche le chemin trouve dans la console

    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i].x << " " << path[i].y << std::endl;
    }*/


    // 
    // Ensuite on affiche la fenetre avec des cases :
    // noires : non passable
    // blanches : passable
    // rouge : p1
    // bleu : p2
    // vert : chemin 
 
    // taille d'une case de la fenetre (pixel)
    float cellSize = (float)windowSize/n;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Carte");

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
                Point p = m.getPointByIndexes(i, j);


                cell.setSize(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setFillColor(sf::Color::White);
                window.draw(cell);


                if (!p.passable)
                {
                    cell.setFillColor(sf::Color::Black);
                }
              
                if ((p.x == p1.x) && (p.y == p1.y))
                {
                    cell.setFillColor(sf::Color::Blue);
                }

                if ((p.x == p2.x) && (p.y == p2.y))
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