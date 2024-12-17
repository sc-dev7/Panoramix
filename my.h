/*
** EPITECH PROJECT, 2024
** Makefile
** File description:
** ok
*/

#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    int pot_size;
    int nb_fights;
    int nb_refills;
    int serving_left;
    int nb_villagers;
    int end_druid;
    sem_t sem_druid;
    sem_t sem_villagers;
    pthread_t druid;
    pthread_t *villagers;
    pthread_mutex_t pot_mutex;
} arg_t;

typedef struct {
    arg_t *arg;
    pthread_t villagers;
    int id;
} villager_t;

int handle_argc(int ac);
int handle_rules(int villagers, int pot, int fights, int refills);
