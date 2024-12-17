/*
** EPITECH PROJECT, 2024
** PANORAMIX
** File description:
** ok
*/

#include "my.h"

pthread_mutex_t pot_mutex = PTHREAD_MUTEX_INITIALIZER;

int handle_drink_and_attack(villager_t *villager, int fight_number)
{
    pthread_mutex_lock(&pot_mutex);
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        villager->id, villager->arg->serving_left);
    if (villager->arg->serving_left == 0 && villager->arg->nb_refills > 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n",
            villager->id);
        sem_post(&villager->arg->sem_druid);
        sem_wait(&villager->arg->sem_villagers);
    }
    if (villager->arg->serving_left > 0) {
        villager->arg->serving_left--;
        printf("Villager %d: Take that roman scum! Only %d left.\n",
            villager->id, (villager->arg->nb_fights - fight_number - 1));
    } else {
        pthread_mutex_unlock(&pot_mutex);
        printf("Villager %d: ON EST MOOOORT!!!!\n", villager->id);
        return 0;
    }
    pthread_mutex_unlock(&pot_mutex);
    return 1;
}

void *v_action(void *my_arg)
{
    villager_t *villager = (villager_t *)my_arg;

    printf("Villager %d: Going into battle!\n", villager->id);
    for (int i = 0; i != villager->arg->nb_fights; i++) {
        if (handle_drink_and_attack(villager, i) == 0) {
            break;
        }
    }
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
    return NULL;
}

void *druid_action(void *my_arg)
{
    arg_t *arg = (arg_t *)my_arg;

    printf("Druid: I'm ready... but sleepy...\n");
    while (arg->nb_refills > 0) {
        sem_wait(&arg->sem_druid);
        if (arg->end_druid == 1) {
            break;
        }
        arg->nb_refills --;
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I");
        printf(" can only make %d more refills after this one.\n",
        arg->nb_refills);
        arg->serving_left = arg->pot_size;
        sem_post(&arg->sem_villagers);
    }
    if (arg->nb_refills == 0) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    }
    return NULL;
}

void *start_panoramix(void *my_arg)
{
    arg_t *arg = (arg_t *)my_arg;
    villager_t villager_ids[arg->nb_villagers];
    pthread_t villagers[arg->nb_villagers];

    sem_init(&arg->sem_druid, 0, 0);
    sem_init(&arg->sem_villagers, 0, 0);
    pthread_create(&arg->druid, NULL, druid_action, arg);
    for (int i = 0; i != arg->nb_villagers; i++) {
        villager_ids[i].arg = arg;
        villager_ids[i].id = i;
        pthread_create(&villagers[i], NULL, v_action, &villager_ids[i]);
    }
    for (int i = 0; i != arg->nb_villagers; i++)
        pthread_join(villagers[i], NULL);
    arg->end_druid = 1;
    sem_post(&arg->sem_druid);
    pthread_join(arg->druid, NULL);
    sem_destroy(&arg->sem_villagers);
    sem_destroy(&arg->sem_druid);
    pthread_mutex_destroy(&pot_mutex);
}

int main(int ac, char **av)
{
    arg_t *arg = malloc(sizeof(arg_t));

    if (handle_argc(ac) == 1) {
        return 84;
    }
    arg->nb_villagers = atoi(av[1]);
    arg->pot_size = atoi(av[2]);
    arg->nb_fights = atoi(av[3]);
    arg->nb_refills = atoi(av[4]);
    arg->serving_left = arg->pot_size;
    if (handle_rules(arg->nb_villagers,
    arg->pot_size, arg->nb_fights, arg->nb_refills) == 1) {
        return 84;
    }
    start_panoramix(arg);
    return 0;
}
