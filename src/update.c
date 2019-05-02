/*
** EPITECH PROJECT, 2018
** src/update
** File description:
** you're a bad developer
*/

#include "world.h"
#include "my.h"

extern const char *dialog[];
extern const char *name[];

void    clear_buff(my_framebuff_t *buff, double *z_buff)
{
    int i = 0;
    int len = WM * HM;

    while (i < len) {
        z_buff[i] = -1;
        buff->pixels[i * 4] = 0;
        buff->pixels[i * 4 + 1] = 0;
        buff->pixels[i * 4 + 2] = 0;
        buff->pixels[i * 4 + 3] = 0;
        i++;
    }
}

void    update(my_game_t *game, play_t *play, png_t *png)
{
    sfRenderWindow_clear(game->win->window, sfBlack);
    sfTexture_updateFromPixels(game->win->texture, game->win->framebuff->pixels,
WM, HM, 0, 0);
    sfRenderWindow_drawSprite(game->win->window, game->win->sprite, NULL);
    users_interaction(play, game);
    action_game(play);
    if (game->value_talk == 0)
        dialogue(&png[game->value_talk], game->win->window, "", "");
    else
        dialogue(&png[game->value_talk], game->win->window,
                 name[game->value_talk], dialog[game->value_talk]);
}
