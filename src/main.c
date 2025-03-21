// TODO: add some sort of AI for enemies?
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define SCREEN_WIDTH 20
#define ENEMY_COUNT 5
#define CHARACTER "/\\"
#define ENEMY ";,,;"
#define ENEMY_SIZE 4
#define BULLET "*"
#include <time.h>
void delay_ms(int ms) {
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
}

typedef struct {
  int x_coord;
  int y_coord;
  bool is_defeated;
} enemy;

int input;
bool KEY_PRESSED = 0;
int main(void) {
  enemy enemies[ENEMY_COUNT];
  initscr();            // initialize ncurses
  keypad(stdscr, TRUE); // Enable special keys
  noecho();             // Don't show typed characters
  curs_set(0);
  refresh();
  for (int i = 0; i < ENEMY_COUNT; i = i + 1) {
    enemies[i].x_coord =
        COLS / 2 -
        (ENEMY_SIZE + 1) * (ENEMY_COUNT / 2 - i); //+1 is because of space
    enemies[i].y_coord = 1;
    enemies[i].is_defeated = 0;
  }

  int x_main = COLS / 2;
  int y_main = LINES - 2;

  while (1) {
    KEY_PRESSED = 0;
    mvprintw(y_main, x_main, CHARACTER);
    int x_bullet = x_main;
    int y_bullet = y_main - 1;

    for (int i = 0; i < ENEMY_COUNT; i++) {
      // display enemies
      if (!enemies[i].is_defeated) {
        mvprintw(enemies[i].y_coord, enemies[i].x_coord, ENEMY);
      }
    }
    input = getch();
    if (input == 'q') {
      break;
    }
    switch (input) {

    case KEY_LEFT:
      KEY_PRESSED = 1;
      if (x_main > 1) {
        mvprintw(y_main, x_main, "    ");
        x_main -= 2;
      }
      break;
    case KEY_RIGHT:
      KEY_PRESSED = 1;
      if (x_main < COLS - 4) {
        mvprintw(y_main, x_main, "    ");
        x_main += 2;
      }
      break;
    case ' ':

      while (y_bullet > 1) {
        mvprintw(y_bullet, x_bullet, BULLET);
        refresh();
        delay_ms(100);
        mvprintw(y_bullet, x_bullet, " ");
        refresh();
        y_bullet -= 1;
        for (int i = 0; i < ENEMY_COUNT; i++) {
          if (enemies[i].y_coord == y_bullet &&
              x_bullet >= enemies[i].x_coord &&
              x_bullet <= enemies[i].x_coord + ENEMY_SIZE) {
            enemies[i].is_defeated = 1;
            mvprintw(enemies[i].y_coord, enemies[i].x_coord, "    ");
            break;
          }
        }
      }
      mvprintw(y_bullet, x_bullet, " ");
    }
    // move enemies down
    if (!KEY_PRESSED) {
      for (int i = 0; i < ENEMY_COUNT; i = i + 1) {
        if (!enemies[i].is_defeated) {
          mvprintw(enemies[i].y_coord, enemies[i].x_coord, "    ");
          enemies[i].y_coord = enemies[i].y_coord + 1;
          mvprintw(enemies[i].y_coord, enemies[i].x_coord, ENEMY);
        }
      }
    }
  }
  endwin();
  return 0;
}
