#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);

    TOWER_DEFENCE_PATH = "../../TowerDefence/";

    srand(time(0));

    gameStart = true;
    gamePause = false;
    mapLoad = false;

//    qDebug() << "towerUnderConstruction: " << towerUnderConstruction;
//    qDebug() << "&towerUnderConstruction: " << &towerUnderConstruction;
    towerUnderConstruction = NULL;
//    qDebug() << "towerUnderConstruction: N: " << towerUnderConstruction;
//    qDebug() << "&towerUnderConstruction: N: " << &towerUnderConstruction;

    mainCoorMapX = 0, mainCoorMapY = 0;
    pixelsShiftMap = 32;
    spaceWidget = 0; // fix this. 16 and launch
    sizeCell = 64;
    zoomSizeCell = 8;
    zoomMaxSizeCell = 256;
    zoomMinSizeCell = 48;

    defaultNumCreateCreeps = 10;

    creepsMove_TimerMilliSec = 100;
    towersAttack_TimerMilliSec = 1000;
    scanMouseMove_TimerMilliSec = 100;

    creepsMove_TimerId = 0;
    towersAttack_TimerId = 0;
    scanMouseMove_TimerId = 0;

    scanMouseMove_TimerId = startTimer(scanMouseMove_TimerMilliSec);

    test = 0;

//    setMouseTracking(true);

    ui->loadMaps->setHidden(true);
    ui->clearMap->setHidden(true);
    ui->goCreeps->setHidden(true);
    ui->closeWidget->setHidden(true);

//    qDebug() << "GameWidget: X: " << width() << " Y: " << height();

//    setWindowState(Qt::WindowFullScreen);

//    int x = 65;//120
//    int y = 30;//60
//    field.createField(x, y);// 65, 30
//    this->setMaximumSize(spaceWidget*2 + x*sizeCell, spaceWidget*2 + y*sizeCell);
//    this->setMinimumSize(spaceWidget*2 + x*sizeCell, spaceWidget*2 + y*sizeCell);
//    this->move(0, 0);

//    for(int x = 0; x < field.getSizeX(); x++)
//        for(int y = 0; y < field.getSizeY(); y++)
//            if(rand()%101 <= 30)
//                field.setBusy(x, y, global_pixmap);

//    for(int x = field.getSizeX(); x >= 0; x--)
//        for(int y = field.getSizeY(); y >= 0; y--)
//            if(rand()%101 <= 10)
//                field.setTower(x, y);

//    int numCreepsK = 0;
//    for(int x = 0; x < field.getSizeX(); x++)
//        for(int y = 0; y < field.getSizeY(); y++)
//            if(rand()%101 <= 5)
//                if(numCreepsK++ < defaultNumCreateCreeps)
//                    field.setCreep(x, y);

//    field.createSpawnPoint(defaultNumCreateCreeps, 0, 0);
//    field.createExitPoint(field.getSizeX()-1, field.getSizeY()-1);

//    loadMap(TOWER_DEFENCE_PATH + "maps/arcticv1.tmx");
}

GameWidget::~GameWidget()
{
    field.deleteField();
    delete ui;
}

void GameWidget::timerEvent(QTimerEvent *event)
{
//    if(test == 1)
//        qDebug() << "test";
    int timerId = event->timerId();

    if(timerId == creepsMove_TimerId)
    {
        if(test == 0)
            field.setCreepInSpawnPoint();
        test = test<8 ? test+1 : 0;

        if(int result = field.stepAllCreeps())
        {
            if(result == 2)
            {
                QMessageBox msg;
                msg.setText("You WIN!");
                msg.exec();
                qDebug() << "You Win!";
                stopTimer_CreepsMoveAndTowerAttack();
            }
            else if(result == 1)
            {
                QMessageBox msg;
                msg.setText("You LOSE!");
                msg.exec();
                qDebug() << "You Lose!";
                stopTimer_CreepsMoveAndTowerAttack();
            }
            else if(result == -1)
            {
                if(field.deleteTower())
                    field.waveAlgorithm();
                else
                    stopTimer_CreepsMoveAndTowerAttack();
            }
        }
        else
            field.towersAttack();
    }
    else if(timerId == scanMouseMove_TimerId)
    {
        int curX = cursor().pos().x();
        int curY = cursor().pos().y();

//        qDebug() << "X: " << curX;
//        qDebug() << "Y: " << curY;

//        qDebug() << "width()" << width();
//        qDebug() << "height()" << height();

        if(curX == 0 || curY == 0 || curX == width()-1 || curY == height()-1)
        {
            if(curX == 0)
                if(mainCoorMapX < 0)
                    mainCoorMapX += pixelsShiftMap;
            if(curY == 0)
                if(mainCoorMapY < 0)
                    mainCoorMapY += pixelsShiftMap;
            if(curX == width()-1)
                if(mainCoorMapX+field.getSizeX()*sizeCell > width())
                    mainCoorMapX -= pixelsShiftMap;
            if(curY == height()-1)
                if(mainCoorMapY+field.getSizeY()*sizeCell > height())
                    mainCoorMapY -= pixelsShiftMap;

            mainCoorMapX = (mainCoorMapX > 0) ? 0 : mainCoorMapX;
            mainCoorMapY = (mainCoorMapY > 0) ? 0 : mainCoorMapY;

            mainCoorMapX = (mainCoorMapX + sizeCell*field.getSizeX() < width()) ? width()-sizeCell*field.getSizeX() : mainCoorMapX;
            mainCoorMapY = (mainCoorMapY + sizeCell*field.getSizeY() < height()) ? height()-sizeCell*field.getSizeY() : mainCoorMapY;
        }
        if(whichCell(curX, curY))
        {
            towerUnderConstructionX = curX;
            towerUnderConstructionY = curY;
        }
    }

    update();
}

void GameWidget::keyPressEvent(QKeyEvent * event)
{
    int key = event->key();

    if(key == Qt::Key_0)
    {
//        qDebug

//        test = 1;
    }
    else if(key == Qt::Key_Left)
    {
        if(mainCoorMapX < 0)
            mainCoorMapX += pixelsShiftMap;
    }
    else if(key == Qt::Key_Up)
    {
        if(mainCoorMapY < 0)
            mainCoorMapY += pixelsShiftMap;
    }
    else if(key == Qt::Key_Right)
    {
        if(mainCoorMapX+field.getSizeX()*sizeCell > width())
            mainCoorMapX -= pixelsShiftMap;
    }
    else if(key == Qt::Key_Down)
    {
        if(mainCoorMapY+field.getSizeY()*sizeCell > height())
            mainCoorMapY -= pixelsShiftMap;
    }
    else if(key == Qt::Key_B)
    {
        qDebug() << "keyPressEvent::B";

        buildTower();
    }
//    if(key == Qt::Key_0)
//    {
//        if(waveAlgorithm(mouseX, mouseY) == 1)
//            global_text2 = "Yes!";
//        else
//            global_text2 = "No!";

//        field.createExitPoint(mouseX,mouseY);

//    }
//    else if(event->button() == Qt::XButton2)
//    {
//        field.createSpawnPoint(defaultNumCreateCreeps, mouseX, mouseY);
//        field.setCreep(mouseX,mouseY);
//    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *)
{
//    if(test == 1)
//        qDebug() << "test";
//    test = test<100 ? test+1 : 0;
//    qDebug() << "Paint" << test;
    p.begin(this);
    if(gameStart)
    {
//        if(!gamePause)
//        {
            drawField();
            drawRelief();
//            drawTowersByField();
            drawTowersByTowers();
            drawCreeps();
//            drawGrid();
//            drawStepsAndMouse();
            drawTowerUnderConstruction();

            p.setPen(QColor(255,0,0));
            p.drawLine(width()/2-5, height()/2-5, width()/2+5, height()/2+5);
            p.drawLine(width()/2+5, height()/2-5, width()/2-5, height()/2+5);

            p.setPen(QColor(255,0,0));
//            p.drawText(width()-width()/4, height()-height()/10, QString("%1").arg(mainCoorMapX));
//            p.drawText(width()-width()/4, height()-height()/10+20, QString("%1").arg(mainCoorMapY));
            p.drawText(10, 20, QString(global_text.c_str()));
            p.drawText(10, 40, QString(global_text2.c_str()));
            p.drawText(10, 60, QString("%1").arg(mainCoorMapX));
            p.drawText(10, 80, QString("%1").arg(mainCoorMapY));
            p.drawText(10, 100, QString("%1").arg(towerUnderConstructionX));
            p.drawText(10, 120, QString("%1").arg(towerUnderConstructionY));
//        }
    }
    p.end();
}

void GameWidget::drawGrid()
{
    p.setPen(QColor(100,60,21));

    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int k = 0; k < fieldX+1; k++)
        p.drawLine(mainCoorMapX + spaceWidget + k*sizeCell, mainCoorMapY + spaceWidget, mainCoorMapX + spaceWidget + k*sizeCell, mainCoorMapY + spaceWidget + sizeCell*fieldY);

    for(int k = 0; k < fieldY+1; k++)
        p.drawLine(mainCoorMapX + spaceWidget, mainCoorMapY + spaceWidget + k*sizeCell, mainCoorMapX + spaceWidget + sizeCell*fieldX, mainCoorMapY + spaceWidget + k*sizeCell);
}

void GameWidget::drawField()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell;
            int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell;
            int localSizeCell = sizeCell;

            if(mapLoad)
                p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getPixmapOfCell(x, y));
        }
    }
}

void GameWidget::drawRelief()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell;//+1;
            int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell;//+1;
            int localSizeCell = sizeCell;//-1;

            if(field.containBusy(x, y))
            {
//                if(!mapLoad)
                    p.fillRect(pxlsX+1, pxlsY+1, localSizeCell-1, localSizeCell-1, QColor(0, 0, 0));
//                else
                    p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getBusyPixmapOfCell(x, y));
            }
        }
    }
}

void GameWidget::drawTowersByField()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell;//+1;
            int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell;// - sizeCell;//+1;
            int localSizeCell = sizeCell*2;//-1; // NOT GOOD WORK!!!!!!!!!!

            if(field.containTower(x, y))
            {
                if(!mapLoad)
                    p.fillRect(pxlsX+1, pxlsY+1, localSizeCell-1, localSizeCell-1, QColor(127, 255, 0));
                else
                    p.drawPixmap(pxlsX, pxlsY, localSizeCell/* + sizeCell*/, localSizeCell/* + sizeCell*/, field.getTowerPixmap(x, y));
            }
        }
    }
}

void GameWidget::drawTowersByTowers()
{
    std::vector<Tower*> towers = field.getAllTowers();

    int size = towers.size();
    for(int k = 0; k < size; k++)
    {
        int x = towers[k]->currX;
        int y = towers[k]->currY;
        int size = towers[k]->defTower->size;

        int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell;
        int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell;
        int localSizeCell = sizeCell*size;

        if(!mapLoad)
            p.fillRect(pxlsX+1, pxlsY+1, localSizeCell-1, localSizeCell-1, QColor(127, 255, 0));
        else
            p.drawPixmap(pxlsX, pxlsY, localSizeCell/* + sizeCell*/, localSizeCell/* + sizeCell*/, towers[k]->pixmap);

        int attackX = towers[k]->attackX;
        int attackY = towers[k]->attackY;
        if(attackX != -1 && attackY != -1)
        {
            attackX = mainCoorMapX + spaceWidget + attackX*sizeCell;
            attackY = mainCoorMapY + spaceWidget + attackY*sizeCell;
            p.drawLine(pxlsX+localSizeCell/2, pxlsY+localSizeCell/2, attackX, attackY);
        }

        QPixmap bullet_fly_up = towers[k]->defTower->bullet_fly_up;
        QPixmap bullet_fly_up_right = towers[k]->defTower->bullet_fly_up_right;
        QPixmap bullet_fly_right = towers[k]->defTower->bullet_fly_right;
        QPixmap bullet_fly_down_right = towers[k]->defTower->bullet_fly_down_right;
        QPixmap bullet_fly_down = towers[k]->defTower->bullet_fly_down;
        QPixmap bullet_fly_down_left = towers[k]->defTower->bullet_fly_down_left;
        QPixmap bullet_fly_left = towers[k]->defTower->bullet_fly_left;
        QPixmap bullet_fly_up_left = towers[k]->defTower->bullet_fly_up_left;

        p.drawPixmap(pxlsX, pxlsY - localSizeCell, localSizeCell, localSizeCell, bullet_fly_up);
        p.drawPixmap(pxlsX + localSizeCell, pxlsY - localSizeCell, localSizeCell, localSizeCell, bullet_fly_up_right);
        p.drawPixmap(pxlsX + localSizeCell, pxlsY, localSizeCell, localSizeCell, bullet_fly_right);
        p.drawPixmap(pxlsX + localSizeCell, pxlsY + localSizeCell, localSizeCell, localSizeCell, bullet_fly_down_right);
        p.drawPixmap(pxlsX, pxlsY + localSizeCell, localSizeCell, localSizeCell, bullet_fly_down);
        p.drawPixmap(pxlsX - localSizeCell, pxlsY + localSizeCell, localSizeCell, localSizeCell, bullet_fly_down_left);
        p.drawPixmap(pxlsX - localSizeCell, pxlsY, localSizeCell, localSizeCell, bullet_fly_left);
        p.drawPixmap(pxlsX - localSizeCell, pxlsY - localSizeCell, localSizeCell, localSizeCell, bullet_fly_up_left);
    }
}

void GameWidget::drawCreeps()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int num = field.containCreep(x, y);
            if(num)
            {
                int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell;//+1;
                int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell;// - sizeCell/2;//+1;
                int localSizeCell = sizeCell;//-1;
                int localSpaceCell = sizeCell/3;

//                QColor color = QColor(num*10, num*10, num*10);
//                p.fillRect(pxlsX+1 + localSpaceCell, pxlsY+1 + localSpaceCell, localSizeCell-1 - 2*(localSpaceCell), localSizeCell-1 - 2*(localSpaceCell), color);

                std::vector<Creep*> creeps = field.getCreeps(x, y);
                int size = creeps.size();
                for(int k = 0; k < size; k++)
                {
                    if(creeps[k]->alive || creeps[k]->preDeath) // fixed!!!
                    {
                        int lastX, lastY;
                        int animationCurrIter, animationMaxIter;
                        QPixmap pixmap = creeps[k]->getAnimationInformation(&lastX, &lastY, &animationCurrIter, &animationMaxIter);

                        pxlsX = mainCoorMapX + spaceWidget + x*sizeCell - localSpaceCell;
                        pxlsY = mainCoorMapY + spaceWidget + y*sizeCell - localSpaceCell;

                        if(lastX < x)
                            pxlsX -= (sizeCell/animationMaxIter)*(animationMaxIter-animationCurrIter);
                        if(lastX > x)
                            pxlsX += (sizeCell/animationMaxIter)*(animationMaxIter-animationCurrIter);
                        if(lastY < y)
                            pxlsY -= (sizeCell/animationMaxIter)*(animationMaxIter-animationCurrIter);
                        if(lastY > y)
                            pxlsY += (sizeCell/animationMaxIter)*(animationMaxIter-animationCurrIter);

                        p.drawPixmap(pxlsX, pxlsY, localSizeCell + localSpaceCell*2, localSizeCell + localSpaceCell*2, pixmap);
    //                    p.drawRect(pxlsX, pxlsY, localSizeCell + localSpaceCell*2, localSizeCell + localSpaceCell*2);

                        int maxHP = 100;
                        int hp = creeps[k]->hp;
                        float hpWidth = localSizeCell-5;
                        hpWidth = hpWidth/maxHP*hp;
//                        qDebug() << "hpWidth: " << hpWidth;

                        p.drawRect(pxlsX + localSpaceCell+2, pxlsY, localSizeCell-4, 10);
                        p.fillRect(pxlsX + localSpaceCell+3, pxlsY+1, hpWidth, 9, QColor(Qt::green));
                    }
                }
            }
        }
    }
}

void GameWidget::drawStepsAndMouse()
{
    p.setPen(QColor(255,150,150));

    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = mainCoorMapX + spaceWidget + x*sizeCell+1;
            int pxlsY = mainCoorMapY + spaceWidget + y*sizeCell+1;
            int localSizeCell = sizeCell-1;
            int localSpaceCell = sizeCell/4;

            p.drawPixmap(sizeCell, 0, global_pixmap.width(), global_pixmap.height(), global_pixmap);

            if(field.getStepCell(x, y))
                p.drawText(pxlsX + sizeCell/2-5, pxlsY + sizeCell/2+5, QString("%1").arg(field.getStepCell(x, y)));

            if(field.isSetSpawnPoint(x,y))
                p.fillRect(pxlsX + localSpaceCell, pxlsY + localSpaceCell, localSizeCell - 2*(localSpaceCell), localSizeCell - 2*(localSpaceCell), QColor(255, 162, 0));

            if(field.isSetExitPoint(x,y))
                p.fillRect(pxlsX + localSpaceCell, pxlsY + localSpaceCell, localSizeCell - 2*(localSpaceCell), localSizeCell - 2*(localSpaceCell), QColor(0, 255, 0));
        }
    }
}

void GameWidget::drawTowerUnderConstruction()
{
    if(towerUnderConstruction != NULL)
    {
        QPixmap towerPix = towerUnderConstruction->pixmap;
        int towerSize = towerUnderConstruction->size;
        int pixSizeCell = towerPix.width() / towerSize;

        QColor cGreen(0, 255, 0, 80);
        QColor cRed(255, 0, 0, 80);
    //    vector<QPixmap> pixmaps;

//        qDebug() << "towerPix: " << towerPix;
//        qDebug() << "towerSize: " << towerSize;
//        qDebug() << "pixSizeCell: " << pixSizeCell;

    //    int columns = towerPix.width() / towerUnderConstruction->size;
    //    int rows = towerPix.height() / towerUnderConstruction->size;

        for(int x = 0; x < towerSize; x++)
        {
            for(int y = 0; y < towerSize; y++)
            {
                QPixmap pix = towerPix.copy(x*pixSizeCell, y*pixSizeCell, pixSizeCell, pixSizeCell);

                int pxlsX = mainCoorMapX + spaceWidget + (towerUnderConstructionX+x)*sizeCell;//+1;
                int pxlsY = mainCoorMapY + spaceWidget + (towerUnderConstructionY+y)*sizeCell;//+1;

                p.drawPixmap(pxlsX, pxlsY, sizeCell, sizeCell, pix);

                if(field.containEmpty(towerUnderConstructionX+x, towerUnderConstructionY+y))
                    p.fillRect(pxlsX, pxlsY, sizeCell, sizeCell, cGreen);
                else
                    p.fillRect(pxlsX, pxlsY, sizeCell, sizeCell, cRed);
            }
        }
    }
}

bool GameWidget::whichCell(int &mouseX, int &mouseY)
{
    int tmpX, tmpY;
    tmpX = ( (mouseX+sizeCell - spaceWidget - mainCoorMapX) / sizeCell);
    tmpY = ( (mouseY+sizeCell - spaceWidget - mainCoorMapY) / sizeCell);
    if(tmpX > 0 && tmpX < field.getSizeX()+1)
        if(tmpY > 0 && tmpY < field.getSizeY()+1)
        {
            mouseX = tmpX-1;
            mouseY = tmpY-1;
            return true;
        }

    return false;
}

void GameWidget::startTimer_CreepsMoveAndTowerAttack()
{
    qDebug() << "startTimer_CreepsMoveAndTowerAttack()";
    if(field.isSetSpawnPoint())
    {
        if(creepsMove_TimerId)
            killTimer(creepsMove_TimerId);

        creepsMove_TimerId = startTimer(creepsMove_TimerMilliSec);
    }
}

void GameWidget::stopTimer_CreepsMoveAndTowerAttack()
{
    qDebug() << "stopTimer_CreepsMoveAndTowerAttack()";
    if(creepsMove_TimerId)
        killTimer(creepsMove_TimerId);

    creepsMove_TimerId = 0;
}

void GameWidget::buildTower(int x, int y)
{
    if(x == -1 && y == -1)
    {
        qDebug() << "buildTower1(" << x << "," << y << ");";

        vector<DefaultTower*> towers = faction.getFirstTowers();
        int size = towers.size();
//        qDebug() << "towers.size(): " << size;

        QMessageBox msgBox;
        msgBox.setText("Какую башню ты хочешь построить?");

        for(int k = 0; k < size; k++)
        {
            QPushButton* b1 = new QPushButton(QIcon(towers[k]->pixmap), QString());
            msgBox.addButton(b1, QMessageBox::AcceptRole);
        }
//        qDebug() << "buildTower(-1, -1) level 2";

        int ret = msgBox.exec();
//        qDebug() << "ret: " << ret;

        towerUnderConstruction = towers[ret];
//        qDebug() << "buildTower(-1, -1) level 3";

//        field.setTower(mouseX, mouseY, towers[ret]);
    }
    else
    {
        if(towerUnderConstruction == NULL)
        {
            qDebug() << "buildTower2(" << x << "," << y << ");";

            vector<DefaultTower*> towers = faction.getFirstTowers();
            int size = towers.size();
//            qDebug() << "towers.size(): " << size;

            QMessageBox msgBox;
            msgBox.setText("Какую башню ты хочешь построить?");

            for(int k = 0; k < size; k++)
            {
                QPushButton* b1 = new QPushButton(QIcon(towers[k]->pixmap), QString());
                msgBox.addButton(b1, QMessageBox::AcceptRole);
            }
//            qDebug() << "buildTower(" << x << "," << y << "); level2";

            int ret = msgBox.exec();
//            qDebug() << "ret: " << ret;

            field.setTower(x, y, towers[ret]);
//            qDebug() << "buildTower(" << x << "," << y << "); level3";
        }
        else
        {
            if(field.setTower(x, y, towerUnderConstruction))
                towerUnderConstruction = NULL;
        }
    }
}

void GameWidget::mousePressEvent(QMouseEvent * event)
{
    int mouseX = event->x();
    int mouseY = event->y();

    QString text = QString("%1/%2").arg(mouseX).arg(mouseY);
    global_text = text.toStdString().c_str();

    if(whichCell(mouseX,mouseY))
    {
        text = QString("%1/%2").arg(mouseX).arg(mouseY);
        global_text2 = text.toStdString().c_str();

//        qDebug() << "Button:" << event->button();

        if(event->button() == Qt::LeftButton)
        {
            if(field.containEmpty(mouseX, mouseY))
                buildTower(mouseX, mouseY);
            else if(field.containTower(mouseX, mouseY))
                field.deleteTower(mouseX, mouseY);

            if(!field.containBusy(mouseX, mouseY))
                field.waveAlgorithm();
        }
        else if(event->button() == Qt::XButton1)
        {
            QPixmap pixmap;
            if(!field.containBusy(mouseX,mouseY))
                field.setBusy(mouseX,mouseY, pixmap);
            else
                field.clearBusy(mouseX,mouseY);
        }
        else if(event->button() == Qt::RightButton)
        {
//            if(waveAlgorithm(mouseX, mouseY) == 1)
//                global_text2 = "Yes!";
//            else
//                global_text2 = "No!";

            field.createExitPoint(mouseX,mouseY);
            if(field.isSetSpawnPoint())
                startTimer_CreepsMoveAndTowerAttack();
//            test = 1;

//            field.setCreep(mouseX, mouseY);
        }
        else if(event->button() == Qt::XButton2)
        {
            field.setMousePress(mouseX,mouseY);
            field.createSpawnPoint(defaultNumCreateCreeps, mouseX, mouseY);

            startTimer_CreepsMoveAndTowerAttack();
        }
        else if(event->button() == Qt::MidButton)
        {
            field.setCreep(mouseX, mouseY);
        }
    }
    update();
}

void GameWidget::wheelEvent(QWheelEvent * event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;

//    qDebug() << "x: " << event->x();
//    qDebug() << "y: " << event->y();

    if (!numPixels.isNull())
        qDebug() << "numPixels: " << numPixels;
    else if (!numDegrees.isNull())
    {
        QPoint numSteps = numDegrees / 15;
        qDebug() << "numSteps: " << numSteps; // QPoint(0,1) up : QPoint(0,-1) down

        int wheelX = numSteps.x();
        int wheelY = numSteps.y();

        if(wheelX == 0 && wheelY != 0)
        {
            if(wheelY > 0)
            {
                if(sizeCell < zoomMaxSizeCell)
                    for(int k = 0; k < wheelY; k++)
                    {
                        sizeCell += zoomSizeCell;
                        mainCoorMapX -= (zoomSizeCell*field.getSizeX()/2);
                        mainCoorMapY -= (zoomSizeCell*field.getSizeY()/2);

                        int mouseMapX = event->x();
                        int mouseMapY = event->y();
                        int mapCenterX = width()/2;
                        int mapCenterY = height()/2;
                        mainCoorMapX -= (mouseMapX-mapCenterX);
                        mainCoorMapY -= (mouseMapY-mapCenterY);
                    }
            }
            else
            {
//                if(sizeCell*field.getSizeX()-zoomSizeCell*sizeCell > width() && sizeCell*field.getSizeY()-zoomSizeCell*sizeCell > height())
//                if(sizeCell*field.getSizeX()-zoomSizeCell*sizeCell < width() )
                    if(sizeCell > zoomMinSizeCell)
                    {
                        wheelY = -wheelY;
                        for(int k = 0; k < wheelY; k++)
                        {
                            sizeCell -= zoomSizeCell;
                            mainCoorMapX += (zoomSizeCell*field.getSizeX()/2);
                            mainCoorMapY += (zoomSizeCell*field.getSizeY()/2);
                        }
                    }
            }
            mainCoorMapX = (mainCoorMapX > 0) ? 0 : mainCoorMapX;
            mainCoorMapY = (mainCoorMapY > 0) ? 0 : mainCoorMapY;

            mainCoorMapX = (mainCoorMapX + sizeCell*field.getSizeX() < width()) ? width()-sizeCell*field.getSizeX() : mainCoorMapX;
            mainCoorMapY = (mainCoorMapY + sizeCell*field.getSizeY() < height()) ? height()-sizeCell*field.getSizeY() : mainCoorMapY;
        }
    }
//    event->accept();
}

//void GameWidget::mouseReleaseEvent(QMouseEvent * event);

/*void GameWidget::mouseMoveEvent(QMouseEvent * event)
{
////    static int maxX = 0;
////    static int maxY = 0;

//    int x = event->x();
//    int y = event->y();
//    qDebug() << "x: " << x;
//    qDebug() << "y: " << y;

////    if (x > maxX)
////        maxX = x;
////    if (y > maxY)
////        maxY = y;

////    qDebug() << "maxX: " << maxX << ", SmaxY: " << maxY;

//    int globalX = event->globalX();
//    int globalY = event->globalY();
//    qDebug() << "globalX: " << globalX;
//    qDebug() << "globalY: " << globalY;

//    if(x < 0)
//        drawWidgetCurrX =- 10;
//    if(y < 0)
//        drawWidgetCurrY =- 10;
//    if(x > width())
//        drawWidgetCurrX =+ 10;
//    if(y > height())
//        drawWidgetCurrY =+ 10;

////    test = test<100 ? test+1 : 0;
////    qDebug() << "mouseMoveEvent()" << test;

//    update();
}*/

/*void GameWidget::leaveEvent(QEvent *event)
{
    qDebug() << "leaveEvent()";
}*/

void GameWidget::loadMap(QString mapName)
{
    if(creepsMove_TimerId)
    {
        killTimer(creepsMove_TimerId);
        creepsMove_TimerId = 0;
    }

    if(mapLoad)
        mapLoad = false;

    QFile* file = new QFile(mapName);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't load map: " << mapName;
        return;
    }

    QXmlStreamReader xmlReader(file);

    //map
    int mapSizeX, mapSizeY;
    int mapTileWidth;//, mapTileHeight;

    //tileset
    vector<TileSet> tileSets;
    TileSet tileSet;
//    DefaultUnit unit;
//    bool loadUnit = false;

    //layer
    bool layer = false;
    bool ground = false;
    int x = 0;
    int y = 0;

    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        if(xmlReader.isStartElement())
        {
            QString nameElement = xmlReader.name().toString();
            //qDebug() << "StartElement: " << nameElement;

            if(nameElement == "map")
            {
                mapSizeX = xmlReader.attributes().value("width").toInt();
                mapSizeY = xmlReader.attributes().value("height").toInt();
                mapTileWidth = xmlReader.attributes().value("tilewidth").toInt();
//                mapTileHeight = xmlReader.attributes().value("tileheight").toInt();
                //qDebug() << "mapSizeX: " << mapSizeX;
                //qDebug() << "mapSizeY: " << mapSizeY;
                //qDebug() << "mapTileWidth: " << mapTileWidth;
                //qDebug() << "mapTileHeight: " << mapTileHeight;

                field.createField(mapSizeX, mapSizeY);
//                setMaximumSize(spaceWidget*2 + mapSizeX*sizeCell, spaceWidget*2 + mapSizeY*sizeCell);
//                setMinimumSize(spaceWidget*2 + mapSizeX*sizeCell, spaceWidget*2 + mapSizeY*sizeCell);
            }
            else if(nameElement == "tileset")
            {
                tileSet.firstTileID = xmlReader.attributes().value("firstgid").toInt();
                tileSet.name = xmlReader.attributes().value("name").toString();
                tileSet.spacing = xmlReader.attributes().value("spacing").toInt();
                tileSet.margin = xmlReader.attributes().value("margin").toInt();
                tileSet.tileWidth = xmlReader.attributes().value("tilewidth").toInt();
                tileSet.tileHeight = xmlReader.attributes().value("tileheight").toInt();
                //qDebug() << "tileSet.firstTileID: " << tileSet.firstTileID;
                qDebug() << "tileSet.name: " << tileSet.name;
                //qDebug() << "tileSet.spacing: " << tileSet.spacing;
                //qDebug() << "tileSet.margin: " << tileSet.margin;
//                qDebug() << "tileSet.tileWidth: " << tileSet.tileWidth;
//                qDebug() << "tileSet.tileHeight: " << tileSet.tileHeight;

                if(tileSet.name.contains("tower"))
                {
//                    qDebug() << "tileSet.name.contains('creep')";

                    DefaultTower tower;
//                    loadUnit = true;

                    xmlReader.readNext(); // <tileset "empty">
                    xmlReader.readNext(); // <properties>
//                    qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                    xmlReader.readNext(); // <properties "empty">
                    xmlReader.readNext(); // <property>
//                    qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();

                    while(xmlReader.name().toString() == "property")
                    {
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();

                        if(xmlReader.attributes().value("name").toString() == "attack")
                            tower.attack = xmlReader.attributes().value("value").toInt();
                        else if(xmlReader.attributes().value("name").toString() == "name")
                            tower.name = xmlReader.attributes().value("value").toString();
                        else if(xmlReader.attributes().value("name").toString() == "radius")
                            tower.radius = xmlReader.attributes().value("value").toInt();
                        else if(xmlReader.attributes().value("name").toString() == "size")
                            tower.size = xmlReader.attributes().value("value").toInt();
                        else if(xmlReader.attributes().value("name").toString() == "type")
                            tower.type = xmlReader.attributes().value("value").toInt();

                        xmlReader.readNext(); // </property>
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                        xmlReader.readNext(); // </property "empty">
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                        xmlReader.readNext(); // <property> - </properties>
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                    }

//                    qDebug() << "tower.attack" << tower.attack;

//                    qDebug() << "tower.type" << tower.type;

                    xmlReader.readNext(); // </properties "empty">
                    xmlReader.readNext(); // <image>

                    if(xmlReader.name().toString() == "image")
                    {
                        QString imagePath = xmlReader.attributes().value("source").toString();
//                        qDebug() << "imagepath: " << imagePath;

                        imagePath.prepend(TOWER_DEFENCE_PATH + "maps/");
                        //qDebug() << imagePath;
                        if(!tileSet.img.load(imagePath))
                        {
                            qDebug() << "Failed to load tile sheet.";
                            return;
                        }

                        int columns = tileSet.img.width() / tileSet.tileWidth;
                        int rows = tileSet.img.height() / tileSet.tileHeight;

//                        qDebug() << "columnsPixmap: " << columns;
//                        qDebug() << "rowsPixmap: " << rows;

                        for(int y = 0; y < rows; y++)
                            for(int x = 0; x < columns; x++)
                            {
                                QRect rect(tileSet.margin + (tileSet.spacing * x) + (x * tileSet.tileWidth), tileSet.margin + (tileSet.spacing * y) + (y * tileSet.tileHeight), tileSet.tileWidth, tileSet.tileHeight);
                                tileSet.subRects.push_back(rect);
                            }
                    }

                    xmlReader.readNext(); // </image>
                    xmlReader.readNext(); // </image "empty">
                    xmlReader.readNext(); // <terraintypes>
                    xmlReader.readNext(); // <terraintypes "empty">
                    xmlReader.readNext(); // <terrain>

                    while(xmlReader.name().toString() == "terrain")
                    {
                        QString name = xmlReader.attributes().value("name").toString();
                        int tileGID = xmlReader.attributes().value("tile").toInt();
                        QPixmap pixmap = tileSet.img.copy(tileSet.subRects[tileGID]);

                        if(name == "idle_up")
                            tower.pixmap = pixmap;
                        else if(name == "bullet_fly_up")
                            tower.bullet_fly_up = pixmap;
                        else if(name == "bullet_fly_up_right") {
                            tower.bullet_fly_up_right = pixmap;
                            tower.bullet_fly_up_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "bullet_fly_right") {
                            tower.bullet_fly_right = pixmap;
                            tower.bullet_fly_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "bullet_fly_down_right") {
                            tower.bullet_fly_down_right = pixmap;
                            tower.bullet_fly_down_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "bullet_fly_down")
                            tower.bullet_fly_down = pixmap;

/*//                        IN DEVELOPING..
                            tower.idle_up = pixmap;
                        else if(name == "idle_up_right")
                        {
                            tower.idle_up_right = pixmap;
                            tower.idle_up_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_right")
                        {
                            tower.idle_right = pixmap;
                            tower.idle_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_down_right")
                        {
                            tower.idle_down_right = pixmap;
                            tower.idle_down_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_down")
                            tower.idle_down = pixmap;
                        else if(name.contains("walk"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    tower.walk_up.push_back(pixmap);
                                else
                                {
                                    tower.walk_up_right.push_back(pixmap);
                                    tower.walk_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    tower.walk_right.push_back(pixmap);
                                    tower.walk_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    tower.walk_down_right.push_back(pixmap);
                                    tower.walk_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    tower.walk_down.push_back(pixmap);
                            }
                        }
                        else if(name.contains("attack"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    tower.attack_up.push_back(pixmap);
                                else
                                {
                                    tower.attack_up_right.push_back(pixmap);
                                    tower.attack_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    tower.attack_right.push_back(pixmap);
                                    tower.attack_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    tower.attack_down_right.push_back(pixmap);
                                    tower.attack_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    tower.attack_down.push_back(pixmap);
                            }
                        }
                        else if(name.contains("death"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    tower.death_up.push_back(pixmap);
                                else
                                {
                                    tower.death_up_right.push_back(pixmap);
                                    tower.death_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    tower.death_right.push_back(pixmap);
                                    tower.death_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    tower.death_down_right.push_back(pixmap);
                                    tower.death_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    tower.death_down.push_back(pixmap);
                            }
                        }*/

                        xmlReader.readNext(); // </terrain>
                        xmlReader.readNext(); // </terrain "empty">
                        xmlReader.readNext(); // <terrain> - </terraintypes>
                    }

//                    qDebug() << "unit.walk" << unit.walk_down.size();
//                    qDebug() << "tower.walk_down.size(): " << &tower << "->" << tower.walk_down.size();
                    qDebug() << "faction.creatyNewTower(unit);";
                    faction.creatyNewTower(tower);
//                    unit.clearVectors();
                }
                else if(tileSet.name.contains("creep"))
                {
//                    qDebug() << "tileSet.name.contains('creep')";

                    DefaultUnit unit;
//                    loadUnit = true;

                    xmlReader.readNext(); // <tileset "empty">
                    xmlReader.readNext(); // <properties>
//                    qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                    xmlReader.readNext(); // <properties "empty">
                    xmlReader.readNext(); // <property>
//                    qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();

                    while(xmlReader.name().toString() == "property")
                    {
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();

                        if(xmlReader.attributes().value("name").toString() == "health_point")
                            unit.healtPoint = xmlReader.attributes().value("value").toInt();
                        else if(xmlReader.attributes().value("name").toString() == "name")
                            unit.name = xmlReader.attributes().value("value").toString();

                        xmlReader.readNext(); // </property>
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                        xmlReader.readNext(); // </property "empty">
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                        xmlReader.readNext(); // <property> - </properties>
//                        qDebug() << xmlReader.name().toString() << " " << xmlReader.isStartElement();
                    }

//                    qDebug() << "unit.healtPoint" << unit.healtPoint;
//                    qDebug() << "unit.name" << unit.name;

                    xmlReader.readNext(); // </properties "empty">
                    xmlReader.readNext(); // <image>

                    if(xmlReader.name().toString() == "image")
                    {
                        QString imagePath = xmlReader.attributes().value("source").toString();
//                        qDebug() << "imagepath: " << imagePath;

                        imagePath.prepend(TOWER_DEFENCE_PATH + "maps/");
                        //qDebug() << imagePath;
                        if(!tileSet.img.load(imagePath))
                        {
                            qDebug() << "Failed to load tile sheet.";
                            return;
                        }

                        int columns = tileSet.img.width() / tileSet.tileWidth;
                        int rows = tileSet.img.height() / tileSet.tileHeight;

//                        qDebug() << "columnsPixmap: " << columns;
//                        qDebug() << "rowsPixmap: " << rows;

                        for(int y = 0; y < rows; y++)
                            for(int x = 0; x < columns; x++)
                            {
                                QRect rect(tileSet.margin + (tileSet.spacing * x) + (x * tileSet.tileWidth), tileSet.margin + (tileSet.spacing * y) + (y * tileSet.tileHeight), tileSet.tileWidth, tileSet.tileHeight);
                                tileSet.subRects.push_back(rect);
                            }
                    }

                    xmlReader.readNext(); // </image>
                    xmlReader.readNext(); // </image "empty">
                    xmlReader.readNext(); // <terraintypes>
                    xmlReader.readNext(); // <terraintypes "empty">
                    xmlReader.readNext(); // <terrain>

                    while(xmlReader.name().toString() == "terrain")
                    {
                        QString name = xmlReader.attributes().value("name").toString();
                        int tileGID = xmlReader.attributes().value("tile").toInt();
                        QPixmap pixmap = tileSet.img.copy(tileSet.subRects[tileGID]);

                        if(name == "idle_up")
                            unit.idle_up = pixmap;
                        else if(name == "idle_up_right")
                        {
                            unit.idle_up_right = pixmap;
                            unit.idle_up_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_right")
                        {
                            unit.idle_right = pixmap;
                            unit.idle_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_down_right")
                        {
                            unit.idle_down_right = pixmap;
                            unit.idle_down_left = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));
                        }
                        else if(name == "idle_down")
                            unit.idle_down = pixmap;
                        else if(name.contains("walk"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    unit.walk_up.push_back(pixmap);
                                else
                                {
                                    unit.walk_up_right.push_back(pixmap);
                                    unit.walk_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    unit.walk_right.push_back(pixmap);
                                    unit.walk_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    unit.walk_down_right.push_back(pixmap);
                                    unit.walk_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    unit.walk_down.push_back(pixmap);
                            }
                        }
                        else if(name.contains("attack"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    unit.attack_up.push_back(pixmap);
                                else
                                {
                                    unit.attack_up_right.push_back(pixmap);
                                    unit.attack_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    unit.attack_right.push_back(pixmap);
                                    unit.attack_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    unit.attack_down_right.push_back(pixmap);
                                    unit.attack_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    unit.attack_down.push_back(pixmap);
                            }
                        }
                        else if(name.contains("death"))
                        {
                            if(name.contains("up"))
                            {
                                if(!name.contains("right"))
                                    unit.death_up.push_back(pixmap);
                                else
                                {
                                    unit.death_up_right.push_back(pixmap);
                                    unit.death_up_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("right"))
                            {
                                if(!name.contains("down"))
                                {
                                    unit.death_right.push_back(pixmap);
                                    unit.death_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                                else
                                {
                                    unit.death_down_right.push_back(pixmap);
                                    unit.death_down_left.push_back(QPixmap::fromImage(pixmap.toImage().mirrored(true, false)));
                                }
                            }
                            else if(name.contains("down"))
                            {
                                if(!name.contains("right"))
                                    unit.death_down.push_back(pixmap);
                            }
                        }
                        xmlReader.readNext(); // </terrain>
                        xmlReader.readNext(); // </terrain "empty">
                        xmlReader.readNext(); // <terrain> - </terraintypes>
                    }

//                    qDebug() << "unit.walk" << unit.walk_down.size();
                    qDebug() << "unit.walk_down.size(): " << &unit << "->" << unit.walk_down.size();
                    qDebug() << "faction.creatyNewUnit(unit);";
                    faction.creatyNewUnit(unit);
//                    unit.clearVectors();
                }
            }
            else if(nameElement == "image")
            {
                QString imagePath = xmlReader.attributes().value("source").toString();
                //qDebug() << "imagepath: " << imagePath;

                imagePath.prepend(TOWER_DEFENCE_PATH + "maps/");
                //qDebug() << imagePath;
                if(!tileSet.img.load(imagePath))
                {
                    qDebug() << "Failed to load tile sheet.";
                    return;
                }

                int columns = tileSet.img.width() / tileSet.tileWidth;
                int rows = tileSet.img.height() / tileSet.tileHeight;

                qDebug() << "columnsPixmap: " << columns;
                qDebug() << "rowsPixmap: " << rows;

                for(int y = 0; y < rows; y++)
                    for(int x = 0; x < columns; x++)
                    {
//                        qDebug() << "x1: " << tileSet.margin + (tileSet.spacing * x) + (x * tileWidth);
//                        qDebug() << "y1: " << tileSet.margin + (tileSet.spacing * y) + (y * tileHeight);
//                        qDebug() << "tileWidth: " << tileWidth;
//                        qDebug() << "tileHeight: " << tileHeight;
                        QRect rect(tileSet.margin + (tileSet.spacing * x) + (x * tileSet.tileWidth), tileSet.margin + (tileSet.spacing * y) + (y * tileSet.tileHeight), tileSet.tileWidth, tileSet.tileHeight);
//                        qDebug() << "push_back:" << rect;

                        tileSet.subRects.push_back(rect);
                    }
            }
            else if(nameElement == "terrain")
            {
                QString name = xmlReader.attributes().value("name").toString();
                int tileGID = xmlReader.attributes().value("tile").toInt();
//                    QPixmap pixmap = tileSet.img;
//                    pixmap = pixmap.copy(tileSet.subRects[tileGID]);
                QPixmap pixmap = tileSet.img.copy(tileSet.subRects[tileGID]);
//                QPixmap pixmapMirrored = QPixmap::fromImage(pixmap.toImage().mirrored(true, false));

                if(name == "Creep")
                {
                    global_pixmap = pixmap;
                    field.setPixmapForCreep(pixmap);
//                    qDebug() << "Creep Set!";
                }
                if(tileSet.name.contains("creep"))
                {
                    // GAVNO!!
                }
                else if(name == "Tower")
                {
//                    int towerAttack = -1;
//                    int towerRadius = -1;
//                    int towerType = -1;

//                    xmlReader.readNext(); // <properties>
//                    xmlReader.readNext(); // <property>

//                    while(xmlReader.name().toString() == "property")
//                    {
//                        if(xmlReader.attributes().value("name").toString() == "attack")
//                            towerAttack = xmlReader.attributes().value("value").toInt();
//                        else if(xmlReader.attributes().value("name").toString() == "radius")
//                            towerRadius = xmlReader.attributes().value("value").toInt();
//                        else if(xmlReader.attributes().value("name").toString() == "type")
//                            towerType = xmlReader.attributes().value("value").toInt();
//                        xmlReader.readNext();
//                    }

//                    global_pixmap = pixmap;
//                    field.setPixmapForTower(pixmap);
//                    faction.creatyNewTower(towerType, towerRadius, towerAttack, pixmap);
//                    qDebug() << "Tower Set!";
                }
            }
            else if(nameElement == "layer")
            {
                layer = true;
                if(xmlReader.attributes().value("name") == "ground")
                    ground = true;
                else
                    ground = false;

                x = 0;
                y = 0;
            }
//            if(nameElement == "data")
            else if(nameElement == "tile")
            {
                if(layer)
                {
                    int num = 0;
                    int tileGID = xmlReader.attributes().value("gid").toInt();

                    int size = tileSets.size();
                    for(int k = 0; k < size; k++)
                        if(tileGID >= tileSets[k].firstTileID)
                            num = k;

                    int subRectToUse = tileGID - tileSets[num].firstTileID;

                    // Устанавливаем TextureRect каждого тайла
                    if (subRectToUse >= 0)
                    {
                        QPixmap pixmap = tileSets[num].img;
                        pixmap = pixmap.copy(tileSets[num].subRects[subRectToUse]);
                        if(ground)
                            field.setBusy(x, y, pixmap);
                        else
                            field.setPixmapInCell(x, y, pixmap);
                    }
                    else
                    {
                        //qDebug() << "subRectToUse: " << subRectToUse;
                    }

                    x++;
                    if (x >= mapSizeX)
                    {
                        x = 0;
                        y++;
                        if(y >= mapSizeY)
                            y = 0;
                    }
                }
            }
//            if(nameElement == "objectgroup")
            else if(nameElement == "object")
            {
                QString name = xmlReader.attributes().value("name").toString();

                int num = 0;
                int tileGID = xmlReader.attributes().value("gid").toInt();

                int size = tileSets.size();
                for(int k = 0; k < size; k++)
                    if(tileGID >= tileSets[k].firstTileID)
                        num = k;

                int tileObjectID = tileGID - tileSets[num].firstTileID;
//                int tileObjectID = xmlReader.attributes().value("gid").toInt() - firstTileID;
                int x = xmlReader.attributes().value("x").toInt();
                int y = xmlReader.attributes().value("y").toInt();

//                qDebug() << "tileObjectID: " << tileObjectID;
//                qDebug() << "x: " << x;
//                qDebug() << "y: " << y;
                x = x / mapTileWidth; // В файле кординаты графические. Поэтому преобразуем в игровые.
                y = (y - mapTileWidth) / mapTileWidth;
//                qDebug() << "change_x: " << x;
//                qDebug() << "change_y: " << y;

                QPixmap pixmap = tileSets[num].img;
                pixmap = pixmap.copy(tileSets[num].subRects[tileObjectID]);

                if(name == "spawnPoint")
                {
//                    qDebug() << "name: " << name;
                    field.setPixmapInCell(x, y, pixmap);
                    field.setMousePress(x, y);
                    field.createSpawnPoint(defaultNumCreateCreeps, x, y);
                }
                else if(name == "exitPoint")
                {
//                    qDebug() << "name: " << name;
                    field.setPixmapInCell(x, y, pixmap);
                    field.createExitPoint(x, y);
//                    startCreepTimer();
                }
            }
        }
        else if(xmlReader.isEndElement())
        {
            QString nameElement = xmlReader.name().toString();
            //qDebug() << "EndElement: " << nameElement;

            if(nameElement == "tileset")
            {
                tileSets.push_back(tileSet);
                tileSet.subRects.clear();
//                if(loadUnit)
//                {
////                    qDebug() << "faction.creatyNewUnit(unit);";
////                    faction.creatyNewUnit(unit);
////                    unit.clearVectors();
//                    loadUnit = false;
//                }
            }
            else if(nameElement == "layer")
                layer = false;
        }

        xmlReader.readNext();
    }
    if(xmlReader.hasError())
    {
        qDebug() << "Error: " << xmlReader.errorString();
    }
    else
        qDebug() << "Completed load map.";

    field.setFaction(&faction);

    mapLoad = true;
    tileSet.subRects.clear();
    tileSets.clear();
    file->close();
//    update();
}

void GameWidget::on_loadMaps_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "../TowerDefence/maps/", tr("Maps (*.xml)"));

//    qDebug() << "FileName: " << fileName;

    loadMap(fileName);
}

/*void Widget::on_loadMaps_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./maps/", tr("Maps (*.tdm)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString str;
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("File is broken.");

    int newSizeX, newSizeY;

    if(!file.atEnd())
    {
        str = QString(file.readLine());
        if(str.indexOf("TowerDefenceMap") == -1)
        {
            msgBox.exec();
            return;
        }
    }

    if(!file.atEnd())
    {
        str = QString(file.readLine());

        newSizeX = str.toInt();

        if(!file.atEnd())
        {
            str = QString(file.readLine());

            newSizeY = str.toInt();
        }
    }

    field.createField(newSizeX, newSizeY);
    setMinimumSize(spaceWidget*2 + newSizeX*sizeCell, spaceWidget*2 + newSizeY*sizeCell);
    setMaximumSize(spaceWidget*2 + newSizeX*sizeCell, spaceWidget*2 + newSizeY*sizeCell);

    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            if(!file.atEnd())
            {
                str = QString(file.readLine());
                if(str.toInt())
                    field.setBusy(x, y);
            }
            else
            {
                msgBox.exec();
                return;
            }
        }
    }

    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            if(!file.atEnd())
            {
                str = QString(file.readLine());
                if(str.toInt())
                    field.setTower(x, y);
            }
            else
            {
                msgBox.exec();
                return;
            }
        }
    }

    file.close();
    update();
}*/

void GameWidget::on_clearMap_clicked()
{
    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            field.deleteTower(x, y);
            field.clearBusy(x, y);
//            field.clearStepCell(x, y);
        }
    }

//    int numCreepsK = 0;
//    for(int x = 0; x < field.getSizeX(); x++)
//    {
//        for(int y = 0; y < field.getSizeY(); y++)
//        {
//            int procent = 0;
    //            {
        //            {
//            if(rand()%101 <= procent)
//            {
    //            {
    //                if(numCreepsK++ < 30)
    //                {
//                {
//                    field.setCreep(x, y);
//                }
//            }
//        }
//    }

    update();
}

void GameWidget::on_closeWidget_clicked()
{
    signal_closeWidget();
}

void GameWidget::on_goCreeps_clicked()
{
    field.waveAlgorithm();
    field.createSpawnPoint(defaultNumCreateCreeps);
    startTimer_CreepsMoveAndTowerAttack();
}
