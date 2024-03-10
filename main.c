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
  Last Updated: March 11, 2024
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
int systemFact1(struct orderedPair F[], struct orderedPair F1[], struct orderedPair F2[], struct orderedPair F3[]) {
    // Get union of F1 and F2
    struct orderedPair unionF[SIZE_2T];

    return cardinality;
}

int main()
{
  int i, j;
  
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

  struct orderedPair complete[12] = {
      {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};
  struct orderedPair A[12] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {8, 8}};
  struct orderedPair B[12] = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  struct orderedPair F[12];
  
  // for (i = 0; i < SIZE_U * SIZE_U; i++)
  // {
  //   P1.movesC[i].x = C1[i].x;
  //   P2.movesC[i].y = C2[i].y;
  // }

  /* ========== SYSTEM FACTS

    Check if the system facts are still valid.
    1. Get the array F3 given F1 and F2 after the moves.
    2. Check if game is over.

    Author: Ganituen [1];
            ___ [2]
  */
  int sizeF3 = systemFact1(complete, A, B, F);

  for (i = 0; i < 12; i++)
  {
    printf("F\t (%d, %d)\n", F[i].x, F[i].y);
  }

  return 0;
}