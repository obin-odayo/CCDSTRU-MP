/*
  Machine Project for Discrete Structures (CCDSTRU)
  De La Salle University, Term 2 AY 2023-2024

  `main.c` is the source code file that contains the main function of the
  project.

  Created By:   GANITUEN, Zhean Robby L.
                KRAUT, Maria Clarisse P.
                TELAN, John Andrei S.

  Created For:  CCDSTRU Machine Project, Ms. Jemie Que

  Created On:   March 07, 2024
  Last Updated: March 10, 2024
*/

#include "common.h"
#include "implementation.h"

/*
  README
  1. The instructions specify that we need to keep track of
  each other's contributions. Though there's a version control
  here in Replit, everytime we write a large chunk of code
  let's comment our name there. And if somebody were to make
  revisions on that, add your name on it. So, something like:
            "Author: GANITUEN, Revisions: Kraut"

  2. For ideas in the implementation of each specification,
  add your ideas in `notes.md`.
*/

/* player1

  Struct that contains all the data types for player 1.

  Credits to Kraut for the idea of using structs.
  Author: Ganituen
*/
struct player {
  String name;                                // name of the player
  struct orderedPair movesC[SIZE_T * SIZE_T]; // moves of the player in C.
                                              // (C1 or C2)
  struct orderedPair movesF[SIZE_U * SIZE_U]; // moves of the player in F.
                                              // (F1 or F2)
};

/*
  systemFact1: checks the first system fact and returns the
  cardinality of F3.

  @params:
  - F [int *]: array F.
  - F1 [int *]: array F1. Moves of player 1 in board F.
  - F2 [int *]: array F2. Moves of player 2 in board F.
  - F3 [int *]: array F3. Available moves in player 3.

  @returns:
  - cardinality [int]: cardinality of F3.

  Author: Ganituen
*/
int systemFact1(int F[][2], int F1[][2], int F2[][2], int F3[][2]) {
  int cardinality = 0; // variable of cardinality of F3.
                       // Assume as 0.
  int i, j;
  struct orderedPair
      unionF[SIZE_T]; // array that contains the union of F1 and F2.
                      // recall that F1 and F2 are subsets of F.

  int key[2];
  int size = 0; // int that stores the size of unionF
                // Assume as 0.
  bool checker;

  // add all elements of F1 to unionF
  for (i = 0; i < SIZE_T * SIZE_T; i++) {
    unionF->x = F1[i][0];
    unionF->y = F1[i][1];
    size++;
  }

  // all all elements of F2 to unionF, if unionF does not contain it yet.
  for (i = 0; i < SIZE_T * SIZE_T; i++) {
    key[0] = F2[i][0];
    key[1] = F2[i][1];
    checker = false; // bool that checks if key is in unionF or not.
                     // assume false

    for (j = 0; j < SIZE_T * SIZE_T; j++) {
      if (key[0] == unionF[j][0] && key[1] == unionF[j][1]) {
        checker = true;
        break;
      }
    }

    // if checker is not true
    if (!checker) {
      unionF[size][0] = key[0];
      unionF[size][1] = key[1];
      size++;
    }
  }

  // do the set subtraction of F - unionF
  for (i = 0; i < SIZE_T * SIZE_T; i++) {
    checker = false; // assume false
    key[0] = unionF[i][0];
    key[1] = unionF[i][1];

    for (j = 0; j < SIZE_T * SIZE_T; j++) {
      if (key[0] == F[j][0] && key[1] == F[j][1]) {
        checker = true;
        break;
      }
    }

    if (!checker) {
      F3[cardinality][0] = key[0];
      F3[cardinality][1] = key[1];
      cardinality++;
    }
  }

  return cardinality;
}

int main() {
  bool game_start = true;
  int i, j;
  struct player P1;
  struct player P2;

  while (game_start) {
    /* ========== SYSTEM INITIALIZATION

      Initialize two of boolean System Variables here.
      Good is false
      next is false

      I used V[] to represent the boolean values.
      - V[0] is true.
      - V[1] is false.

      Initialize C1, C2, F1, and F1 as empty sets then assign
      them to their respective structs.

      Author: Ganituen
    */
    good = V[1]; // true
    over = V[1];

    for (i = 0; i < SIZE_T * SIZE_T; i++)
      P1.movesF[i].x = F1[i];
    P2.movesF[i][j] = F2[i][j];
  }

  for (i = 0; i < SIZE_U * SIZE_U; i++)
    for (j = 0; j < 2; j++) {
      P1.movesC[i][j] = C1[i][j];
      P2.movesC[i][j] = C2[i][j];
    }

  /* ========== SYSTEM FACTS

    Check if the system facts are still valid.
    1. Get the array F3 given F1 and F2 after the moves.
    2. Check if game is over.

    Author: Ganituen [1];
            ___ [2]
  */
  int sizeF3 = systemFact1(F, P1.movesF, P2.movesF, F3);

  game_start = false;
}
return 0;
}