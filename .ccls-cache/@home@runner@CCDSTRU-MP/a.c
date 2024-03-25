#include "common.h"

/*
 */
char *GameOver(bool over) {
  // result is either B wins
  // or A wins
  char *result[2] = {"B wins", "A wins"};
  int player = 0; // index of the player that won
                  // 1 is player A
                  // 2 is player B

  if (over)
    player = 1;
  return result[player];
}

int main() { printf("%s", GameOver(0)); }