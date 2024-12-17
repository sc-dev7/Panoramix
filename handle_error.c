/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** sc
*/

#include "my.h"

int handle_argc(int ac)
{
    if (ac != 5) {
        printf("USAGE: ./panoramix <nb_villagers>");
        printf("<pot_size> <nb_fights> <nb_refills>\n");
        printf("Values must be >0.\n");
        return 1;
    } else {
        return 0;
    }
}

int handle_rules(int nb_villagers, int pot_size, int nb_fights, int nb_refills)
{
    if (nb_villagers <= 0 || pot_size <= 0 ||
    nb_fights <= 0 || nb_refills <= 0) {
        printf("USAGE: ./panoramix <nb_villagers>");
        printf("<pot_size> <nb_fights> <nb_refills>\n");
        printf("Values must be >0.\n");
        return 1;
    } else {
        return 0;
    }
}
