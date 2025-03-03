#include <stdio.h>
#define SCREEN_WIDTH 20
#define ENEMY_COUNT 5

int main(void) {
  char input;
  int player_pos = 10;
  int screen_width = 20;
  int enemy_pos[ENEMY_COUNT] = {2, 5, 8, 11, 14};
  int enemy_direction = 1;
  int enemy_move_timer = 0;

  while (1) {
    printf("\033[2J\033[1;1H");

    for (int i = 0; i < screen_width; i++) {
      int is_enemy = 0;
      for (int j = 0; j < ENEMY_COUNT; j++) {
        if (i == enemy_pos[j]) {
          is_enemy = 1;
          break;
        }
      }
      if (is_enemy) {
        printf("X");
      } else {
        printf(" ");
      }
    }
    printf("\n");
    for (int i = 0; i < screen_width; i++) {
      if (i == player_pos) {
        printf("A");
      } else {
        printf(" ");
      }
    }
    printf("\n");
    printf("Move (a/d to move, q to quit): ");
    scanf("%c", &input);

    if (input == 'a' && player_pos > 0) {
      player_pos--;
    } else if (input == 'd' && player_pos < screen_width) {
      player_pos++;
    } else if (input == 'q') {
      break;
    }

    enemy_move_timer++;
    if (enemy_move_timer >= 3) { // Move every 3 loops
      for (int i = 0; i < ENEMY_COUNT; i++) {
        enemy_pos[i] += enemy_direction;
      }
      // Check if enemies hit the edge, reverse direction
      if (enemy_pos[ENEMY_COUNT - 1] >= SCREEN_WIDTH - 1 || enemy_pos[0] <= 0) {
        enemy_direction = -enemy_direction;
      }
      enemy_move_timer = 0; // Reset timer
    }
  }
  return 0;
}
