#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    srand(time(0));

    gameStart = true;
    gamePause = false;
    mapLoad = false;

    spaceWidget = 50;
    sizeCell = 15;

    defaultNumCreateCreeps = 30;
    millisecForTimer = 200;
    creepsMoveTimerId = 0;

    test = 0;

    int x = 120;
    int y = 60;
    field.createField(x, y);// 65, 30
    setMaximumSize(spaceWidget*2 + x*sizeCell, spaceWidget*2 + y*sizeCell);
    setMinimumSize(spaceWidget*2 + x*sizeCell, spaceWidget*2 + y*sizeCell);

    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            int procent = 30;
            if(rand()%101 <= procent)
                field.setBusy(x, y, global_pixmap);
        }
    }

//    int numCreepsK = 0;
//    for(int x = 0; x < field.getSizeX(); x++)
//    {
//        for(int y = 0; y < field.getSizeY(); y++)
//        {
//            int procent = 10;
//            if(rand()%101 <= procent)
//            {
//                if(numCreepsK++ < defaultCreateCreeps)
//                {
//                    field.setCreep(x, y);
//                }
//            }
//        }
//    }

//    field.createSpawnPoint(defaultNumCreateCreeps, 0, 0);
//    field.createExitPoint(field.getSizeX()-1, field.getSizeY()-1);
}

Widget::~Widget()
{
    field.deleteField();
    delete ui;
}

void Widget::timerEvent(QTimerEvent *)
{
    field.setCreep();
    if(int result = field.stepAllCreeps())
    {
        if(result == 1)
        {
            killTimer(creepsMoveTimerId);
            creepsMoveTimerId = 0;
        }
        else if(result == -1)
        {
            field.deleteTower();
            field.waveAlgorithm();
        }
    }
    else
        field.towersAttack();

    update();
}

void Widget::keyPressEvent(QKeyEvent * event)
{
//    int key = event->key();

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
}

void Widget::paintEvent(QPaintEvent *)
{
//    test = test<100 ? test+1 : 0;
//    qDebug() << "Paint" << test;
    p.begin(this);
    if(gameStart)
    {
//        if(!gamePause)
//        {
            p.setPen(QColor(255,0,0));
//            p.drawText(width()-width()/4, height()-height()/10, QString(global_text.c_str()));
//            p.drawText(width()-width()/4, height()-height()/10+20, QString(global_text2.c_str()));
            p.drawText(10, 20, QString(global_text.c_str()));
            p.drawText(10, 20+20, QString(global_text2.c_str()));

            drawGrid();
            drawField();
            drawRelief();
            drawCreeps();
            drawTowers();
//            drawStepsAndMouse();
//        }
    }
    p.end();
}

void Widget::drawGrid()
{
    p.setPen(QColor(100,60,21));

    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int k = 0; k < fieldX+1; k++)
        p.drawLine(spaceWidget + k*sizeCell, spaceWidget, spaceWidget + k*sizeCell, spaceWidget + sizeCell*fieldY);

    for(int k = 0; k < fieldY+1; k++)
        p.drawLine(spaceWidget, spaceWidget + k*sizeCell, spaceWidget + sizeCell*fieldX, spaceWidget + k*sizeCell);
}

void Widget::drawField()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = spaceWidget + x*sizeCell;
            int pxlsY = spaceWidget + y*sizeCell;
            int localSizeCell = sizeCell;

            p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getPixmapOfCell(x, y));
        }
    }
}

void Widget::drawRelief()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = spaceWidget + x*sizeCell;//+1;
            int pxlsY = spaceWidget + y*sizeCell;//+1;
            int localSizeCell = sizeCell;//-1;

            if(field.containBusy(x, y))
            {
                p.fillRect(pxlsX+1, pxlsY+1, localSizeCell-1, localSizeCell-1, QColor(0, 0, 0));
                p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getBusyPixmapOfCell(x, y));
            }
        }
    }
}

void Widget::drawTowers()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = spaceWidget + x*sizeCell;//+1;
            int pxlsY = spaceWidget + y*sizeCell;//+1;
            int localSizeCell = sizeCell;//-1;

            if(field.containTower(x, y))
            {
                p.fillRect(pxlsX+1, pxlsY+1, localSizeCell-1, localSizeCell-1, QColor(127, 255, 0));
                p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getTowerPixmap(x, y));
            }
        }
    }
}

void Widget::drawCreeps()
{
    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = spaceWidget + x*sizeCell;//+1;
            int pxlsY = spaceWidget + y*sizeCell;//+1;
            int localSizeCell = sizeCell;//-1;
            int localSpaceCell = sizeCell/4;

            if(field.containCreep(x, y))
            {
                p.fillRect(pxlsX+1 + localSpaceCell, pxlsY+1 + localSpaceCell, localSizeCell-1 - 2*(localSpaceCell), localSizeCell-1 - 2*(localSpaceCell), QColor(255, 0, 0));
                p.drawPixmap(pxlsX, pxlsY, localSizeCell, localSizeCell, field.getCreepPixmap(x, y));
            }
        }
    }
}

void Widget::drawStepsAndMouse()
{
    p.setPen(QColor(150,150,150));

    int fieldX = field.getSizeX();
    int fieldY = field.getSizeY();

    for(int y = 0; y < fieldY; y++)
    {
        for(int x = 0; x < fieldX; x++)
        {
            int pxlsX = spaceWidget + x*sizeCell+1;
            int pxlsY = spaceWidget + y*sizeCell+1;
            int localSizeCell = sizeCell-1;
            int localSpaceCell = sizeCell/4;

            p.drawPixmap(50, 0, global_pixmap.width(), global_pixmap.height(), global_pixmap);

            if(field.getStepCell(x, y))
                p.drawText(pxlsX + sizeCell/2-5, pxlsY + sizeCell/2+5, QString("%1").arg(field.getStepCell(x, y)));

            if(field.isSetSpawnPoint(x,y))
                p.fillRect(pxlsX + localSpaceCell, pxlsY + localSpaceCell, localSizeCell - 2*(localSpaceCell), localSizeCell - 2*(localSpaceCell), QColor(255, 162, 0));

        }
    }
}

bool Widget::whichCell(int *mouseX, int *mouseY)
{
    int tmpX, tmpY;
    tmpX = ((*mouseX+sizeCell - spaceWidget)/sizeCell);
    tmpY = ((*mouseY+sizeCell - spaceWidget)/sizeCell);
    if(tmpX > 0 && tmpX < field.getSizeX()+1)
        if(tmpY > 0 && tmpY < field.getSizeY()+1)
        {
            *mouseX = tmpX-1;
            *mouseY = tmpY-1;
            return true;
        }

    return false;
}

void Widget::startCreepTimer()
{
    qDebug() << "startCreepTimer()";
    if(field.isSetSpawnPoint())
    {
        if(creepsMoveTimerId)
            killTimer(creepsMoveTimerId);

        creepsMoveTimerId = startTimer(millisecForTimer);
    }
}

void Widget::mousePressEvent( QMouseEvent * event )
{
    int mouseX = event->x();
    int mouseY = event->y();

    QString text = QString("%1/%2").arg(mouseX).arg(mouseY);
    global_text = text.toStdString().c_str();

    if(whichCell(&mouseX,&mouseY))
    {
        text = QString("%1/%2").arg(mouseX).arg(mouseY);
        global_text2 = text.toStdString().c_str();

//        cerr << "Button:" << event->button() << endl;

        if(event->button() == Qt::LeftButton)
        {
            if(!field.containTower(mouseX, mouseY))
                field.setTower(mouseX, mouseY);
            else
                field.deleteTower(mouseX, mouseY);

            if(!field.containBusy(mouseX, mouseY))
                field.waveAlgorithm();
        }
        else if(event->button() == Qt::RightButton)
        {
            QPixmap pixmap;
            if(!field.containBusy(mouseX,mouseY))
                field.setBusy(mouseX,mouseY, pixmap);
            else
                field.clearBusy(mouseX,mouseY);
        }
        else if(event->button() == Qt::XButton1)
        {
    //        if(waveAlgorithm(mouseX, mouseY) == 1)
    //            global_text2 = "Yes!";
    //        else
    //            global_text2 = "No!";

            field.createExitPoint(mouseX,mouseY);
            if(field.isSetSpawnPoint())
                startCreepTimer();
        }
        else if(event->button() == Qt::XButton2)
        {
            field.setMousePress(mouseX,mouseY);
            field.createSpawnPoint(defaultNumCreateCreeps, mouseX, mouseY);

            startCreepTimer();
        }
    }
    update();
}

void Widget::on_loadMaps_clicked()
{
    if(creepsMoveTimerId)
    {
        killTimer(creepsMoveTimerId);
        creepsMoveTimerId = 0;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "../TowerDefence/maps/", tr("Maps (*.xml)"));

    if(mapLoad)
        mapLoad = !mapLoad;

//    qDebug() << "FileName: " << fileName;

    QFile* file = new QFile(fileName);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QXmlStreamReader xmlReader(file);

    //map
    int newSizeX, newSizeY;

    //tileset
    int firstTileID;
    int spacing, margin;

    //image
    QString imagePath;
//    sf::Image img;
    QPixmap img;
    // Вектор из прямоугольников изображений (TextureRect)
//    vector< sf::Rect<int> > subRects;
    vector< QRect > subRects;

    //layer
//    Layer layer;
    bool ground = false;
    int x = 0;
    int y = 0;

    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        if(xmlReader.isStartElement())
        {
            QString nameElement = xmlReader.name().toString();
//            qDebug() << nameElement;

            if(nameElement == "map")
            {
//                qDebug() << nameElement;
                newSizeX = xmlReader.attributes().value("width").toInt();
                newSizeY = xmlReader.attributes().value("height").toInt();
                tileWidth = xmlReader.attributes().value("tilewidth").toInt();
                tileHeight = xmlReader.attributes().value("tileheight").toInt();
//                qDebug() << "Width: " << newSizeX;
//                qDebug() << "Height: " << newSizeY;
//                qDebug() << "tileWidth: " << tileWidth;
//                qDebug() << "tileHeight: " << tileHeight;

                field.createField(newSizeX, newSizeY);
                setMaximumSize(spaceWidget*2 + newSizeX*sizeCell, spaceWidget*2 + newSizeY*sizeCell);
                setMinimumSize(spaceWidget*2 + newSizeX*sizeCell, spaceWidget*2 + newSizeY*sizeCell);
            }
            if(nameElement == "tileset")
            {
//                qDebug() << nameElement;
                firstTileID = xmlReader.attributes().value("firstgid").toInt();
                spacing = xmlReader.attributes().value("spacing").toInt();
                margin = xmlReader.attributes().value("margin").toInt();
//                qDebug() << "firstTileID: " << firstTileID;
//                qDebug() << "spacing: " << spacing;
//                qDebug() << "margin: " << margin;
            }
            if(nameElement == "image")
            {
//                qDebug() << nameElement;
                imagePath = xmlReader.attributes().value("source").toString();
//                qDebug() << "imagepath: " << imagePath;

                if(!img.load(imagePath))
                {
                    qDebug() << "Failed to load tile sheet.";
                    return;
                }

                int columns = img.width() / tileWidth;
                int rows = img.height() / tileHeight;

//                qDebug() << "columnsPixmap: " << columns;
//                qDebug() << "rowsPixmap: " << rows;

                for(int y = 0; y < rows; y++)
                    for(int x = 0; x < columns; x++)
                    {
                        QRect rect(margin + (spacing * x) + (x * tileWidth), margin + (spacing * y) + (y * tileHeight), tileWidth, tileHeight);

                        subRects.push_back(rect);
                    }
            }
            if(nameElement == "terrain")
            {
                QString name = xmlReader.attributes().value("name").toString();
                int tileGID = xmlReader.attributes().value("tile").toInt();
                if(name == "Creep")
                {
                    QPixmap pixmap = img;
                    pixmap = pixmap.copy(subRects[tileGID]);
//                    global_pixmap = pixmap;
                    field.setPixmapForCreep(pixmap);
//                    qDebug() << "Creep Set!";
                }
                if(name == "Tower")
                {
                    QPixmap pixmap = img;
                    pixmap = pixmap.copy(subRects[tileGID]);
//                    global_pixmap = pixmap;
                    field.setPixmapForTower(pixmap);
//                    qDebug() << "Tower Set!";
                }
            }
            if(nameElement == "layer")
            {
//                qDebug() << nameElement;
                if(xmlReader.attributes().value("name") == "ground")
                    ground = true;
                else
                    ground = false;

                x = 0;
                y = 0;
            }
//            if(nameElement == "data")
            if(nameElement == "tile")
            {
//                qDebug() << nameElement;
                int tileGID = xmlReader.attributes().value("gid").toInt();
                int subRectToUse = tileGID - firstTileID;

                // Устанавливаем TextureRect каждого тайла
                if (subRectToUse >= 0)
                {
                    QPixmap pixmap = img;
                    pixmap = pixmap.copy(subRects[subRectToUse]);
                    if(ground)
                    {
                        field.setBusy(x, y, pixmap);
                    }
                    else
                    {
                        field.setPixmapInCell(x, y, pixmap);
                    }
                }

                x++;
                if (x >= newSizeX)
                {
                    x = 0;
                    y++;
                    if(y >= newSizeY)
                        y = 0;
                }
            }
//            if(nameElement == "objectgroup")
            if(nameElement == "object")
            {
//                qDebug() << "test1";
                QString name = xmlReader.attributes().value("name").toString();
                int tileObjectID = xmlReader.attributes().value("gid").toInt() - firstTileID;
                int x = xmlReader.attributes().value("x").toInt();
                int y = xmlReader.attributes().value("y").toInt();

//                qDebug() << "tileObjectID: " << tileObjectID;
//                qDebug() << "x: " << x;
//                qDebug() << "y: " << y;
                x = x / tileWidth; // В файле кординаты графические. Поэтому преобразуем в игровые.
                y = (y - tileWidth) / tileWidth;
//                qDebug() << "change_x: " << x;
//                qDebug() << "change_y: " << y;

                QPixmap pixmap = img;
                pixmap = pixmap.copy(subRects[tileObjectID]);

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

        xmlReader.readNext();
    }
    if(xmlReader.hasError())
    {
        qDebug() << "Error: " << xmlReader.errorString();
    }
    qDebug() << "Completed load map.";
    mapLoad = true;
    subRects.clear();
    file->close();
    update();
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

void Widget::on_clearMap_clicked()
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
//            if(rand()%101 <= procent)
//            {
//                if(numCreepsK++ < 30)
//                {
//                    field.setCreep(x, y);
//                }
//            }
//        }
//    }

    update();
}

void Widget::on_saveMaps_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./maps/", tr("Maps (*.tdm)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    //=================================
//    out << "\"TowerDefenceMap\"" << "\n";
//    out << "{" << "\n";
//    out << "\t" << "sixeX = \"" << field.getSizeX() << "\";\n";
//    out << "\t" << "sixeY = \"" << field.getSizeY() << "\";\n";

//    out << "\t" << "busy = \"";
//    for(int x = 0; x < field.getSizeX(); x++)
//    {
//        for(int y = 0; y < field.getSizeY(); y++)
//        {
//            if(field.containBusy(x,y))
//                out << "1";
//            else
//                out << "0";
//        }
//    }
//    out << "\";\n";
//    out << "}" << "\n";
    //=================================
    out << "TowerDefenceMap" << "\n";
    out << field.getSizeX() << "\n";
    out << field.getSizeY() << "\n";

    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            if(field.containBusy(x,y))
                out << "1\n";
            else
                out << "0\n";
        }
    }

    for(int x = 0; x < field.getSizeX(); x++)
    {
        for(int y = 0; y < field.getSizeY(); y++)
        {
            if(field.containTower(x,y))
                out << "1\n";
            else
                out << "0\n";
        }
    }
    //=================================

    file.close();
}

void Widget::on_goCreeps_clicked()
{
    field.createSpawnPoint(defaultNumCreateCreeps);
    startCreepTimer();
}
