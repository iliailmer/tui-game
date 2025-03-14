#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define SCREEN_WIDTH 20
#define ENEMY_COUNT 5
#define CHARACTER "/\\"
#define BULLET "*"
#include <time.h>
void delay_ms(int ms) {
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
}

int input;
int main(void) {
  int enemy_pos[ENEMY_COUNT] = {2, 5, 8, 11, 14};
  int enemy_direction = 1;
  int enemy_move_timer = 0;

  initscr();            // initialize ncurses
  keypad(stdscr, TRUE); // Enable special keys
  noecho();             // Don't show typed characters
  curs_set(0);
  refresh();
  int x_main = COLS / 2;
  int y_main = LINES - 2;

  while (1) {
    mvprintw(y_main, x_main, CHARACTER);
    int x_bullet = x_main;
    int y_bullet = y_main - 1;

    input = getch();
    if (input == 'q') {
      break;
    }
    switch (input) {
    case KEY_LEFT:
      if (x_main > 1) {
        mvprintw(y_main, x_main, "    ");
        x_main -= 2;
      }
      break;
    case KEY_RIGHT:
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
      }
      mvprintw(y_bullet, x_bullet, " ");
    }
  }
  endwin();
  return 0;
}
