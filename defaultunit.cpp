#include "defaultunit.h"

DefaultUnit::DefaultUnit()
{
}

void DefaultUnit::clearVectors()
{
    walk_up.clear();
    walk_up_right.clear();
    walk_right.clear();
    walk_down_right.clear();
    walk_down.clear();
    walk_down_left.clear();
    walk_left.clear();
    walk_up_left.clear();

    attack_up.clear();
    attack_up_right.clear();
    attack_right.clear();
    attack_down_right.clear();
    attack_down.clear();
    attack_down_left.clear();
    attack_left.clear();
    attack_up_left.clear();

    death_up.clear();
    death_up_right.clear();
    death_right.clear();
    death_down_right.clear();
    death_down.clear();
    death_down_left.clear();
    death_left.clear();
    death_up_left.clear();
}
