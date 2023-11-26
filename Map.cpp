#include "Map.hpp"

Map::Map()
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
Map::Map(unsigned int mapSize, int initType)
{
    pMap = std::make_shared<std::deque<std::deque<Point>>>();

    std::deque<Point> td;
    Point p;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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


Map::~Map()
{}


void Map::destroyMap()
{
    // detruire la map
}


/**
* Retourne le nombre de ligne de la carte
**/
unsigned int Map::getNbRow()
{
    return pMap->size();
}


/**
* Retourne le nombre de colonne de la carte
**/
unsigned int Map::getNbCol()
{
    return pMap->at(0).size();
}


/**
* Affiche dans la console la carte avec des o si la case est passable
* et des x si la case n'est pas passable
**/
void Map::print()
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
void Map::printXY()
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
void Map::add(Point p)
{

    if (p.x > pMap->at(pMap->size() - 1).at(pMap->at(0).size() - 1).x)
    {
        addEast(p.x - pMap->at(0).at(pMap->size() - 1).x);
    }
    else if (p.x < pMap->at(0).at(0).x)
    {
        addWest(abs(p.x));
    }
    if (p.y > pMap->at(0).at(0).y)
    {
        addNorth(p.y - pMap->at(0).at(0).y);
    }
    else if (p.y < pMap->at(pMap->size()-1).at(pMap->size()-1).y)
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
Point Map::getPointByIndexes(unsigned int row, unsigned int col)
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
int* Map::getPointIndexes(Point p)
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
* Definit passable le point avec les indices i , j
*
**/
void Map::setPassable(int i, int j, bool _passable)
{
    pMap->at(i).at(j).passable = _passable;
}

/**
* ajoute une colonne apres la derniere colonne de la carte
**/
void Map::addEast(unsigned int n)
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
* Ajoute une ligne avant la première ligne de la carte
**/
void Map::addNorth(unsigned int n)
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
void Map::addSouth(unsigned int n)
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
* ajoute une colonne avant la premiere colonne de la carte
**/
void Map::addWest(unsigned int n)
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

//
// METHODES CONCERNANT LA RECHERCHE DE CHEMIN :
// 

 // méthode pour vérifier si le point est passable ou non, et si le point est out of bounds
bool Map::isValid(int x, int y) {
    if (pMap->at(x).at(y).passable == false || x >= pMap->size() || y >= pMap->at(0).size())
    {
        return false;
    }
    return true;
}

bool Map::isDestination(int x, int y, Point dest)
{
    if (x == dest.x && y == dest.y)
    {
        return true;
    }
    return false;
}

// calcul de l'heuristique
double Map::calculateH(int x, int y, Point dest)
{
    double H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));
    return H;
}

std::vector<Point> Map::aStar(Point origin, Point dest)
{
    std::vector<Point> empty;
    int* destCoord = getPointIndexes(dest);
    if (isValid(destCoord[0], destCoord[1]) == false)
    {
        std::cout << "Destination is an obstacle" << std::endl;
        return empty;
        //Destination non valide
    }
    if (isDestination(origin.x, origin.y, dest))
    {
        std::cout << "You are the destination" << std::endl;
        return empty;
        //le départ correspond à l'arrivée
    }

    //bool closedList[pMap->size()][pMap->at(0).size()];
    std::vector<std::vector<bool>> closedList(pMap->size(), std::vector<bool>(pMap->at(0).size(), false));

    // Nouvelle map
    // Point allMap[pMap->size()][pMap->at(0).size()];
    std::vector<std::vector<Point>> allMap(pMap->size(), std::vector<Point>(pMap->at(0).size()));

    //std::array<std::array<Point, pMap->at(0).size()>, pMap->size()> allMap;
    for (int x = 0; x < pMap->size(); x++)
    {
        for (int y = 0; y < pMap->at(0).size(); y++)
        {
            allMap[x][y].fCost = FLT_MAX;
            allMap[x][y].gCost = FLT_MAX;
            allMap[x][y].hCost = FLT_MAX;
            allMap[x][y].parentX = -1;
            allMap[x][y].parentY = -1;
            allMap[x][y].x = x;
            allMap[x][y].y = y;

            closedList[x][y] = false;
        }
    }

    //positionnement du point de départ sur la map
    /*int x = origin.x;
    int y = origin.y;*/
    int* indexes = nullptr;

    indexes = getPointIndexes(origin);
    int x = indexes[0];
    int y = indexes[1];

    allMap[x][y].fCost = 0.0;
    allMap[x][y].gCost = 0.0;
    allMap[x][y].hCost = 0.0;
    allMap[x][y].parentX = x;
    allMap[x][y].parentY = y;

    std::vector<Point> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationFound = false;
    indexes = nullptr;

    while (!openList.empty() && openList.size() < pMap->size() * pMap->at(0).size())
    {
        Point point;
        do
        {
            float temp = FLT_MAX;
            std::vector<Point>::iterator itPoint;
            for (std::vector<Point>::iterator it = openList.begin(); it != openList.end(); it = next(it))
            {
                Point n = *it;
                if (n.fCost < temp)
                {
                    temp = n.fCost;
                    itPoint = it;
                }
            }

            point = *itPoint;
            openList.erase(itPoint);

            indexes = getPointIndexes(point);
        } while ((indexes != nullptr) && (isValid(indexes[0], indexes[1]) == false));

        indexes = getPointIndexes(point);
        /*x = point.x;
        y = point.y;*/
        if (indexes != nullptr)
        {
            x = indexes[0];
            y = indexes[1];
            closedList[x][y] = true;

            indexes = nullptr;
            //pour chaque voisin, en partant de haut-gauche à bas-droite
            for (int newX = -1; newX <= 1; newX++)
            {
                for (int newY = -1; newY <= 1; newY++)
                {
                  
                    double gNew, hNew, fNew;
                    Point p(point.x + newX, point.y + newY, point.passable);
                    point = p;
                    indexes = getPointIndexes(p);
                    x = indexes[0];
                    y = indexes[1];
                    if ((indexes != nullptr) && isValid(indexes[0], indexes[1]))
                    {
                        if (isDestination(point.x + newX, point.y + newY, dest))
                        {
                            //allMap[x + newX][y + newY].parentX = point.x;
                            allMap[x][y].parentX = point.x;
                            allMap[x][y].parentY = point.y;
                            destinationFound = true;
                            return makePath(allMap, dest);
                        }
                        //else if (closedList[x + newX][y + newY] == false)
                        else if (closedList[x][y] == false)
                        {
                            gNew = point.gCost + 1.0;
                            hNew = calculateH(x, y, dest);
                            fNew = gNew + hNew;
                            // Check si le chemin trouvé est meilleur que le précédent
                            if (allMap[x][y].fCost == FLT_MAX || allMap[x][y].fCost > fNew)
                            {
                                // maj des points voisins
                                allMap[x][y].fCost = fNew;
                                allMap[x][y].gCost = gNew;
                                allMap[x][y].hCost = hNew;
                                allMap[x][y].parentX = point.x;
                                allMap[x][y].parentY = point.y;
                                openList.emplace_back(allMap[x][y]);
                            }
                        }
                    }
                }
            }
        }
    }
    if (destinationFound == false)
    {
        std::cout << "Destination not found" << std::endl;
        return empty;
    }
}

std::vector<Point> Map::makePath(std::vector<std::vector<Point>> map, Point dest)
{
    try
    {
        std::cout << "Found a path" << std::endl;
        int x = dest.x;
        int y = dest.y;
        std::stack<Point> path;
        std::vector<Point> usablePath;

        while (!(map[x][y].parentX == x && map[x][y].parentY == y) && map[x][y].x != -1 && map[x][y].y != -1)
        {
            path.push(map[x][y]);
            int tempX = map[x][y].parentX;
            int tempY = map[x][y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(map[x][y]);

        while (!path.empty())
        {
            Point top = path.top();
            path.pop();
            usablePath.emplace_back(top);
        }
        return usablePath;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
