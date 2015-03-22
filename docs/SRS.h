Introduction \ Purpose

TowerDefence – игра стратегического направления, цель которой развить навыки тактического и стратегического мышления человека.
Игрок строит башни, и не позволяет крипам дойти до нужной цели.

Introduction \ Document conventions ------------------

-----------------

------------------------------------------------------

Introduction \ References

Фрейморк Qt и вся его документация. http://doc.qt.io/
Пару раз заходил на Хабр! http://habrahabr.ru/

Overall Description \ Product features

Когда система запускает приложение, вызывается функция main, внутри которой создаётся объект класса Widgetcontroller. Перед этим загружается заголовочный файл этого класса. Вся реализация внутри класса Widgetcontroller будет направлена на создание игрового меню и всего приложения.

Overall Description \ Operating environment

Операционная система: кросс-платформенное приложение (Windows/Linux). Там где Qt позволит скомпилировать - будет работать :)
Версии компиляторов: тестировалась только на MinGW 4.8 32b.
Софт: сторонний редактор карт Tiled Map.
Железо: процессор Intel(R) Core(TM) i7-3632QM CPU @ 2.20GHz (8 CPUs), ~2.2GHz; оперативная память 8192MB RAM, видеокарта 1792 MB, клавиатура, мышь.

Overall Description \ Design and implementation constraints

При написании приложения использовался язык программирования Qt C++.
Стандарты кодирования - ...
Стандарты обмена данными - ...
Ограничения накладываемые Operational Enviroment - ...
Ограничения которые могут быть наложены бизнес-логикой проекта - ...

Overall Description \ User documentation

Пользователю, который будет пользоваться приложением понадобится следующая документация - руководство пользователю.

System features \ System feature "Moving Camera"

Moving Camera - Передвегает "камеру" для обзора карты.

System features \ System feature "Moving Camera" \ Description and priority

Когда пользоветель поддодвигает курсор мыши к краю экрана или нажимает клавиши со стрелочками. Вызывается функция void GameWidget::keyPressEvent(QKeyEvent * event) или void GameWidget::timerEvent(QTimerEvent *event) соответственно.
Затем идет пересчет переменных (mainCoorMapX, mainCoorMapY), в соответствии с тем к какому краяю экрана была поддведена мышь или нажата клавиша.
Эта фича может показать пользователю всю карту.
Приоритет----------------

System features \ System feature "Scroll"

Scroll - приближение/отдаление камеры от карты

System features \ System feature "Moving Camera" \ Description and priority


External interface requirements
Данное приложение будет связываться с внешним миром только через клавиатуру и мышь.
API - QtFramework



