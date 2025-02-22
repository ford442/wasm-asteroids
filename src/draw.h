#ifndef __DRAW_H
#define __DRAW_H
struct bullet;
struct explosion;
struct highscores;
struct player;
void draw_bullets(const struct bullet *,unsigned int n);
void draw_explosions(const struct explosion *,unsigned int n);
void draw_gameover_text();
void draw_highscores(const struct highscores *);
void draw_instructions();
void draw_level_title();
void draw_lives(int lives);
void draw_new_high_score_input();
void draw_new_high_score_message();
void draw_new_high_score_enter_to_continue();
void draw_player(const struct player *);
void draw_player_exploding(const struct player *);
void draw_score(unsigned int score);
void draw_title();
#endif
