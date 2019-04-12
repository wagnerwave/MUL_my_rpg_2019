/*
** EPITECH PROJECT, 2018
** src/turn
** File description:
** check your malloc!
*/

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "world.h"

void    enemy_one_turn(my_game_t *game, enemy_t *enemy)
{
    int pos[4][3] = {{-1, 0, 180}, {0, 1, 90}, {1, 0, 0}, {0, -1, 270}};
    int i = 0;
    int choix = -1;
    int tmp = pow((int)enemy->pos.z - (int)game->camera->move.z, 2) +
pow((int)enemy->pos.x - (int)game->camera->move.x, 2);
    char type;

    while (i < 4) {
        if ((int)enemy->pos.y == (int)game->camera->move.y &&
(int)enemy->pos.y - 1 >= 0 && (int)enemy->pos.y <
game->room[game->actual_room]->y_max && (int)enemy->pos.z + pos[i][0] >= 0 &&
(int)enemy->pos.z + pos[i][0] < game->room[game->actual_room]->z_max &&
(int)enemy->pos.x + pos[i][1] >= 0 && (int)enemy->pos.x + pos[i][1] <
game->room[game->actual_room]->x_max && game->room[game->actual_room]->room
[(int)enemy->pos.y][(int)enemy->pos.z + pos[i][0]][(int)enemy->pos.x +
pos[i][1]] == '.' && game->room[game->actual_room]->room[(int)enemy->pos.y - 1]
[(int)enemy->pos.z + pos[i][0]][(int)enemy->pos.x + pos[i][1]] == 'O' &&
pow((int)enemy->pos.z + pos[i][0] - (int)game->camera->move.z, 2) +
pow((int)enemy->pos.x + pos[i][1] - (int)game->camera->move.x, 2) < tmp) {
            choix = i;
            tmp = pow((int)enemy->pos.z + pos[i][0] - (int)game->camera->
move.z, 2) + pow((int)enemy->pos.x + pos[i][1] - (int)game->camera->move.x, 2);
        }
        i++;
    }
    if (choix == -1)
        return ;
    if (tmp == 0) {
        rotation(enemy->obj, pos[choix][2] - enemy->yaw);
        enemy->yaw = pos[choix][2];
        game->player->vie -= enemy->degat;
        if (game->player->vie < 0)
            game->player->vie = 0;
        printf("vie: %d\n", game->player->vie);
        return ;
    }
    type = game->room[game->actual_room]->room[(int)enemy->pos.y]
[(int)enemy->pos.z][(int)enemy->pos.x];
    game->room[game->actual_room]->room[(int)enemy->pos.y][(int)enemy->pos.z]
[(int)enemy->pos.x] = '.';
    enemy->pos.z += pos[choix][0];
    enemy->pos.x += pos[choix][1];
    game->room[game->actual_room]->room[(int)enemy->pos.y][(int)enemy->pos.z]
[(int)enemy->pos.x] = type;
    rotation(enemy->obj, pos[choix][2] - enemy->yaw);
    enemy->yaw = pos[choix][2];
}

void    enemy_turn(my_game_t *game)
{
    static int  cnt = 0;

    while (cnt < game->room[game->actual_room]->nb_enemy &&
(game->room[game->actual_room]->enemy[cnt].vie <= 0 ||
game->room[game->actual_room]->enemy[cnt].pnj > 0 || (int)game->room
[game->actual_room]->enemy[cnt].pos.y != (int)game->camera->move.y))
        cnt++;
    if (cnt >= game->room[game->actual_room]->nb_enemy) {
        cnt = 0;
        game->my_turn = 1;
    }
    if (sfClock_getElapsedTime(game->clock).microseconds >=
game->time_fg + 256000) {
        enemy_one_turn(game, &(game->room[game->actual_room]->enemy[cnt]));
        cnt++;
        game->time_fg = sfClock_getElapsedTime(game->clock).microseconds;
    }
}
