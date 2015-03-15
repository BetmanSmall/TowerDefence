#include "field.h"

using namespace std;

void Field::createField(int newSizeX, int newSizeY)
{
    if(field == NULL)
    {
        field = new Cell[newSizeX*newSizeY];
        towers.createField(newSizeX*newSizeY);
        creeps.createMass(30);

        gameOverLimitCreeps = 3;
        currentFinishedCreeps = 0;

        sizeX = newSizeX;
        sizeY = newSizeY;
        mouseX = -1;
        mouseY = -1;
        exitPointX = -1;
        exitPointY = -1;
        spawnPointX = -1;
        spawnPointY = -1;
    }
    else
    {
        deleteField();
        createField(newSizeX, newSizeY);
    }
}

void Field::deleteField()
{
    if(field != NULL)
    {
        delete[] field;
        field = NULL;
        towers.deleteField();
        creeps.deleteMass();
    }
}

void Field::setFaction(Faction* faction)
{
    faction1 = faction;
}

bool Field::createSpawnPoint(int num, int x, int y)
{
    for(int k = 0; k < creeps.getAmount(); k++)
    {
        Creep* creep = creeps.getCreep(k);
        int creepX = creep->currX;
        int creepY = creep->currY;
        clearCreep(creepX, creepY);
    }

    if(x == -1 && y == -1)
    {
        if(!isSetSpawnPoint())
            return false;
    }
    else
    {
        spawnPointX = x;
        spawnPointY = y;
        clearBusy(x,y);
    }
    creeps.deleteMass();
    creeps.createMass(num);
    currentFinishedCreeps = 0;
    return true;
}

void Field::createExitPoint(int x, int y)
{
    exitPointX = x;
    exitPointY = y;
    clearBusy(x, y);
    waveAlgorithm(x, y);
}

int Field::getSizeX()
{
    return sizeX;
}

int Field::getSizeY()
{
    return sizeY;
}

bool Field::towersAttack()
{
    for(int k = 0; k < towers.getAmount(); k++)
    {
        Tower* tmpTower = towers.getTower(k);
        int x = tmpTower->currX;
        int y = tmpTower->currY;
        int type = tmpTower->type;
        int radius = tmpTower->radius; // 1 // 5

        int defaultHp = 100;

        int exitX = x, exitY = y;

        for(int tmpY = (0-radius); tmpY <= radius; tmpY++)
        {
            for(int tmpX = (0-radius); tmpX <= radius; tmpX++)
            {
                if(!(tmpX == 0 && tmpY == 0))
                {
                    int hp = getCreepHpInCell(x + tmpX, y + tmpY);
                    if(hp <= defaultHp && hp != 0)
                    {
                        exitX = x + tmpX;
                        exitY = y + tmpY;
                        defaultHp = hp;
                    }
                }
            }
        }

        if(exitX != x || exitY != y)
        {
//            if(type == 1)
            Creep* creep;
            if(creeps.attackCreep(exitX, exitY, tmpTower->attack, creep))
            {
//                qDebug() << "Kill: " << clearCreep(exitX, exitY);//, creep);
            }
        }
    }
    return true;
}

void Field::waveAlgorithm(int x, int y)
{
    qDebug() << "Field::waveAlgorithm() :: X: " << x << " Y: " << y;
    if(x == -1 && y == -1)
        if(isSetExitPoint())
        {
            waveAlgorithm(exitPointX, exitPointY);
            return;
        }

    if(!containBusy(x, y) && !containTower(x, y))
    {
        for(int tmpX = 0; tmpX < getSizeX(); tmpX++)
            for(int tmpY = 0; tmpY < getSizeY(); tmpY++)
                clearStepCell(tmpX, tmpY);

        setStepCell(x, y, 1);

        waveStep(x, y, 1);
    }
}

void Field::waveStep(int x, int y, int step)
{
#ifdef CIRCLET8
    //------------3*3----------------
    bool mass[3][3];
    int nextStep = step+1;

    for(int tmpY = -1; tmpY < 2; tmpY++)
        for(int tmpX = -1; tmpX < 2; tmpX++)
            mass[tmpX+1][tmpY+1] = setNumOfCell(x + tmpX, y + tmpY, nextStep);

    for(int tmpY = -1; tmpY < 2; tmpY++)
        for(int tmpX = -1; tmpX < 2; tmpX++)
            if(mass[tmpX+1][tmpY+1])
                waveStep(x + tmpX, y + tmpY, nextStep);
#else
    //------------2*2----------------
    bool mass[4];
    int nextStep = step+1;
    int x1 = x-1, x2 = x, x3 = x+1;
    int y1 = y-1, y2 = y, y3 = y+1;

    mass[0] = setNumOfCell(x1, y2, nextStep);
    mass[1] = setNumOfCell(x2, y1, nextStep);
    mass[2] = setNumOfCell(x2, y3, nextStep);
    mass[3] = setNumOfCell(x3, y2, nextStep);

    if(mass[0])
        waveStep(x1, y2, nextStep);
    if(mass[1])
        waveStep(x2, y1, nextStep);
    if(mass[2])
        waveStep(x2, y3, nextStep);
    if(mass[3])
        waveStep(x3, y2, nextStep);
#endif
}

void Field::setMousePress(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

bool Field::getMousePress(int x, int y)
{
    if(mouseX != -1 && mouseY != -1)
        if((x == mouseX && y == mouseY) || (x == -1 && y == -1))
            return true;

    return false;
}

bool Field::isSetSpawnPoint(int x, int y)
{
    if(spawnPointX != -1 && spawnPointY != -1)
        if((x == spawnPointX && y == spawnPointY) || (x == -1 && y == -1))
            return true;

    return false;
}

bool Field::isSetExitPoint(int x, int y)
{
    if(exitPointX != -1 && exitPointY != -1)
        if((x == exitPointX && y == exitPointY) || (x == -1 && y == -1))
            return true;

    return false;
}

// Возвращает 2 все мертвы.
// Возвращает 1 превышен лимит пришедших крипов.
// Возвращает 0 если просто все сходили.
// Возвращает -1 если хоть один крип не может сходить, ей там на верху, уничтожьте их всех!
int Field::stepAllCreeps()
{
    bool allDead = true;
    for(int k = 0; k < creeps.getAmount(); k++)
    {
        int result = stepOneCreep(k);
        if(result != -2)
            allDead = false;

        if(result == 1)
        {
            currentFinishedCreeps++;
            if(currentFinishedCreeps >= gameOverLimitCreeps)
                return 1;
        }
        else if(result == -1)
            return -1;
    }

    if(allDead)
        return 2;
    else
        return 0;
}

int Field::stepOneCreep(int num)
{
//    qDebug() << "Field::stepOneCreep()";
    Creep* tmpCreep = creeps.getCreep(num);
    if(tmpCreep->alive)
    {
        if(tmpCreep->animationCurrIter < tmpCreep->animationMaxIter)
        {
//            qDebug() << "tmpCreep->animationCurrIter: " << tmpCreep << "->" << tmpCreep->animationCurrIter;
            tmpCreep->pixmap = tmpCreep->walkPixmaps[tmpCreep->animationCurrIter++];
//            tmpCreep->animationCurrIter = tmpCreep->animationCurrIter+1;
        }
        else
        {
            int currX = tmpCreep->currX;
            int currY = tmpCreep->currY;

            int exitX = currX, exitY = currY;

            int min = getNumStep(currX,currY);
            if(min == 1)
                return 1;
            if(min == 0)
                return -1;

            int defaultStep = min;
            //--------------Looking specific cell-----------------------
            for(int tmpY = -1; tmpY < 2; tmpY++)
                for(int tmpX = -1; tmpX < 2; tmpX++)
                    if(!(tmpX == 0 && tmpY == 0))
                    {
                        int num = getNumStep(currX + tmpX, currY + tmpY);
                        if(num <= min && num != 0)
                            if(num == min)
                            {
                                if(rand()%2)
                                {
                                    exitX = currX + tmpX;
                                    exitY = currY + tmpY;
                                }
                            }
                            else if(num == defaultStep-1)
                            {
                                exitX = currX + tmpX;
                                exitY = currY + tmpY;
                                min = num;
                            }
                    }
            //-----------------------------------------------------------

            if(exitX != currX || exitY != currY)
            {
//                qDebug() << "exitX: " << exitX << " exitY: " << exitY;
//                qDebug() << "currX: " << currX << " currY: " << currY;
                clearCreep(currX, currY, tmpCreep);
                tmpCreep->lastX = currX;
                tmpCreep->lastY = currY;
                tmpCreep->currX = exitX;
                tmpCreep->currY = exitY;
                tmpCreep->number = min;
                tmpCreep->animationCurrIter = 0;

                if(exitX < currX && exitY < currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_up_left.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_up_left;
                }
                else if(exitX == currX && exitY < currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_up.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_up;
                }
                else if(exitX > currX && exitY < currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_up_right.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_up_right;
                }
                else if(exitX < currX && exitY == currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_left.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_left;
                }
                else if(exitX > currX && exitY == currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_right.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_right;
                }
                else if(exitX < currX && exitY > currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_down_left.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_down_left;
                }
                else if(exitX == currX && exitY > currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_down.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_down;
                }
                else if(exitX > currX && exitY > currY)
                {
                    tmpCreep->animationMaxIter = tmpCreep->defUnit->walk_down_right.size();
                    tmpCreep->walkPixmaps = tmpCreep->defUnit->walk_down_right;
                }
//                qDebug() << "tmpCreep->animationMaxIter: " << tmpCreep << "->" << tmpCreep->animationMaxIter;
                tmpCreep->pixmap = tmpCreep->walkPixmaps[0];

                setCreep(exitX, exitY, tmpCreep);
            }
//            else
//            {
//                cerr << "Bad" << endl;
//                return false;
//            }
        }
    }
    else
        return -2;

    return 0;
}

int Field::getNumStep(int x, int y)
{
    if(x >= 0 && x < getSizeX())
        if(y >= 0 && y < getSizeY())
            if(!containBusy(x, y))
                if(!containTower(x, y))
                    return getStepCell(x, y);

    return 0;
}

int Field::getStepCell(int x, int y)
{
    return field[sizeX*y + x].step;
}

bool Field::setNumOfCell(int x, int y, int step)
{
    if(x >= 0 && x < getSizeX())
        if(y >= 0 && y < getSizeY())
            if(!containBusy(x, y) && !containTower(x, y))
                if(getStepCell(x, y) > step || getStepCell(x, y) == 0)
                {
                    setStepCell(x, y, step);
                    return true;
                }

    return false;
}

void Field::setStepCell(int x, int y, int step)
{
    field[sizeX*y + x].step = step;
}

void Field::clearStepCell(int x, int y)
{
    field[sizeX*y + x].step = 0;
}

Creep* Field::getCreep(int x, int y)
{
    if(!field[sizeX*y + x].creeps.empty())
        return field[sizeX*y + x].creeps.front();
    else
        return NULL;
//    return field[sizeX*y + x].creep;
}

std::vector<Creep*> Field::getCreeps(int x, int y)
{
//    if(!field[sizeX*y + x].creeps.empty())
        return field[sizeX*y + x].creeps;
//    else
//        return NULL;
}

int Field::getCreepHpInCell(int x, int y)
{
    if(x >= 0 && x < getSizeX())
        if(y >= 0 && y < getSizeY())
            if(containCreep(x,y))
                return creeps.getHP(x, y);

    return 0;
}

bool Field::containBusy(int x, int y)
{
    return field[sizeX*y + x].busy;
}

bool Field::containTower(int x, int y)
{
//    return (field[sizeX*y + x].tower != NULL);
    return field[sizeX*y + x].tower;
}

int Field::containCreep(int x, int y, Creep *creep)
{
    if(!field[sizeX*y + x].creeps.empty())
    {
        if(creep == NULL)
            return field[sizeX*y + x].creeps.size();
        else
            for(int k = 0; k < field[sizeX*y + x].creeps.size(); k++)
                if(field[sizeX*y + x].creeps[k] == creep)
                    return k+1;
    }
//    if(field[sizeX*y + x].creep != NULL)
//        if(field[sizeX*y + x].creep->alive)
//            return true;
    return 0;
}

bool Field::setBusy(int x, int y, QPixmap pixmap)
{
    if(field[sizeX*y + x].null)
    {
        field[sizeX*y + x].busy = true;
        field[sizeX*y + x].null = false;
        if(!pixmap.isNull())
            field[sizeX*y + x].busyPixmap = pixmap;
        return true;
    }
    else
        return false;
}

bool Field::setTower(int x, int y, int type)
{
    if(field[sizeX*y + x].null)
    {
        if(!isSetExitPoint(x, y) && !isSetSpawnPoint(x, y))
        {
            field[sizeX*y + x].tower = towers.createTower(x, y);
            field[sizeX*y + x].null = false;
            return true;
        }
    }
    return false;
}

bool Field::setTower(int x, int y, Tower tower)
{
    if(field[sizeX*y + x].null)
    {
        if(!isSetExitPoint(x, y) && !isSetSpawnPoint(x, y))
        {
            field[sizeX*y + x].tower = towers.createTower(x, y, tower);
            field[sizeX*y + x].null = false;
            return true;
        }
    }
    return false;
}

bool Field::setCreep(int x, int y, Creep* creep)//, int type)
{
    if(x == -1 && y == -1)
        return setCreep(spawnPointX, spawnPointY, creep);//, type);

    if(field[sizeX*y + x].null || !field[sizeX*y + x].creeps.empty())
    {
        if(creep == NULL)
        {
            Creep* creep;
            if(creepSet)
                creep = creeps.createCreep(x, y, faction1->getDefaultUnitById(0));
            else
                creep = creeps.createCreep(x, y, faction1->getDefaultUnitById(1));
            creepSet = !creepSet;

            if(creep == NULL)
                return false;
            field[sizeX*y + x].creeps.push_back(creep);
//            field[sizeX*y + x].creep = creeps.createCreep(x, y);
//            if(field[sizeX*y + x].creep == NULL)
//                return false;
        }
        else
            field[sizeX*y + x].creeps.push_back(creep);
//            field[sizeX*y + x].creep = creep;

        field[sizeX*y + x].null = false;
        return true;
    }

    return false;
}

bool Field::clearBusy(int x, int y)
{
    if(!field[sizeX*y + x].null)
    {
        if(containBusy(x,y))
        {
            field[sizeX*y + x].busy = false;
            field[sizeX*y + x].null = true;
            return true;
        }
    }

    return false;
}

bool Field::clearTower(int x, int y)
{
    if(!field[sizeX*y + x].null)
    {
        if(containTower(x,y))
        {
            field[sizeX*y + x].tower = NULL;
            field[sizeX*y + x].null = true;
            return true;
        }
    }
    return false;
}

bool Field::clearCreep(int x, int y, Creep *creep)
{
    if(!field[sizeX*y + x].null)
    {
        if(creep == NULL)
            field[sizeX*y + x].creeps.clear();
        else if(int num = containCreep(x, y, creep))
        {
            field[sizeX*y + x].creeps.erase(field[sizeX*y + x].creeps.begin()+(num-1));
//            field[sizeX*y + x].creep = NULL;
        }

        if(field[sizeX*y + x].creeps.empty())
            field[sizeX*y + x].null = true;

        return true;
    }
    return false;
}

bool Field::deleteTower(int x, int y)
{
    if(towers.deleteTower(x, y))
        return clearTower(x, y);
    return false;
}

bool Field::setPixmapInCell(int x, int y, QPixmap pixmap)
{
    field[sizeX*y + x].backgroundPixmap = pixmap;
}

bool Field::setPixmapForCreep(QPixmap pixmap)
{
    creeps.setDefaulPixmapForCreep(pixmap);
}

bool Field::setPixmapForTower(QPixmap pixmap)
{
    towers.setDefaulPixmapForTower(pixmap);
}

QPixmap Field::getBusyPixmapOfCell(int x, int y)
{
    return field[sizeX*y + x].busyPixmap;
}

QPixmap Field::getPixmapOfCell(int x, int y)
{
    return field[sizeX*y + x].backgroundPixmap;
}

QPixmap Field::getCreepPixmap(int x, int y)
{
    return creeps.getCreepPixmap(x, y);
}

QPixmap Field::getTowerPixmap(int x, int y)
{
    return towers.getTowerPixmap(x, y);
}
