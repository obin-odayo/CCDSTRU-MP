/*
  Machine Project for Discrete Structures (CCDSTRU)
  De La Salle University, Term 2 AY 2023-2024

  `implementation.h` is a header file that contains
  our interpretations of the specs sheet.

  Created By:   GANITUEN, Zhean Robby L.
                KRAUT, Maria Clarisse P.
                TELAN, John Andrei S.

  Created For:  CCDSTRU Machine Project, Ms. Jemie Que

  Created On:   March 07, 2024
  Last Updated: March 10, 2024
*/

#ifndef implementation_h
#define implementation_h

#include "common.h"

#define SIZE_U 2
#define SIZE_T 6
#define NONE -1
#define ROW_INDEX 0
#define COL_INDEX 1

/*
  README
  To help navigate this file, use file command and search:
      - APPLICABLE SETS
      - SYSTEM VARIABLES
      - SYSTEM FACTS
      - SYSTEM INITIALIZATION
      - SYSTEM STATES AND BEHAVIOR

  TO DO:
  1. Implement System Variables, Facts, Initialization, States
  and Behavior.
*/

/* ========== APPLICABLE SETS
  Remark. Given the restrictions for all the sets. The elements   inside the
  sets remain fixed and non-removable.
*/

/*
  [1] U: {x in Z+ | x < 3}
  U contains all x s.t. x is a positive integer that's less
  than 3.
  Only two (3-1) possible elements in U.

  Author: Ganituen
*/
int U[SIZE_U] = {1, 2};

/*
  [2] T: {x in Z+ | x < 7}
  T contains all x s.t. x is a positive integer that's less than 7.
  Only six (7-1) possible elements in T.

  Author: Ganituen
*/
int T[SIZE_T] = {1, 2, 3, 4, 5, 6};

/*
  C: U x U
  C is the Cartesian product of U and U.
  Number of possible elements in C is 4.

  Author: Ganituen
*/
orderedPair C[SIZE_U * SIZE_U] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};

/*
  F: T X T
  T is the Cartesian product of T and T.
  Number of possible elements in T is 36

  Author: Ganituen
*/
orderedPair F[SIZE_T * SIZE_T] = {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3},
    {2, 4}, {2, 5}, {2, 6}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
    {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 1}, {5, 2}, {5, 3},
    {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

/*
  V: {true, false}
  V contains Booleans
  Remark. We can also use 0 (false) and 1 (true) here. But for
  readability's sake, I used stdbool "true" and "false".

  Author: Ganituen
*/
bool V[2] = {true, false};

/*
  S contains all the possible solutions for each quadrant in
  the 6x6 grid.
  See comment below for reference.
  Remark. NONE is used to indicate that it is an extra space.
  Most solutions require only 5 coordinates while one solution
  needs 6.

       [1] [2] [3] [4] [5] [6]
  [1]   x |   | x |   | v |
       -----------------------
  [2]     | x |   | v | v | v
       -----------------------
  [3]   x |   | x |   | v |
       -----------------------
  [4]   s |   | s | o |   | o
       -----------------------
  [5]   s |   | s |   | o |
       -----------------------
  [6]   s |   | s | o |   | o

  C(1,1) = Rows 1-3 and columns 1-3 only
  C(1,2) = Rows 1-3 and columns 4-6 only
  C(2,1) = Rows 4-6 and columns 1-3 only
  C(2,2) = Rows 4-6 and columns 4-6 only

  Credits to Telan for the interpretation.

  Author: Kraut
*/
orderedPair S[4][6] = {{{1, 1},
                        {1, 3},
                        {2, 2},
                        {3, 1},
                        {3, 3},
                        {NONE, NONE}}, // Solution for C(1,1) represented as "x"
                       {{4, 4},
                        {4, 6},
                        {5, 5},
                        {6, 4},
                        {6, 6},
                        {NONE, NONE}}, // Solution for C(2,2) represented as "o"
                       {{1, 5},
                        {2, 4},
                        {2, 5},
                        {2, 6},
                        {3, 5},
                        {NONE, NONE}}, // Solution for C(1,2) represented as "v"
                       {{4, 1},
                        {4, 3},
                        {5, 1},
                        {5, 3},
                        {6, 1},
                        {6, 3}}}; // Solution for C(2,1) represented as "s"

/*
  P is the applicable quadrants that must be achieved in order
  to declare a winner.
  For example, if A was able to get the solutions of C(1,1) AND
  C(2,2), then they are the winner. Else if A got the solution
  C(1,1) AND C(1,2), the game is not over.

  Author: Kraut
*/
orderedPair P[SIZE_U][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

/* ========== SYSTEM VARIABLES
 */

/*
  good, over, and next are variables who's definitions are in
  the array V, good, over, next in V. Therefore, these have
  boolean values just like V.

  good: dictates whether the move is legal or not.
  over: dictates whether the game is still in plaay or not.
  next: dictates whether it is the next player's turn or not.

  Credits to Telan and Kraut for interpretation of "good".
  Author: Ganituen
*/

bool good;
bool over;
bool next;

/*
  The subsets of F and C. Since all of these are subsets of F
  and C, then their dimensions should also equal F and C to
  facilitate all possible elements.
*/
orderedPair F1[SIZE_T * SIZE_T];
orderedPair F2[SIZE_T * SIZE_T];
orderedPair F3[SIZE_T * SIZE_T];

orderedPair C1[SIZE_U * SIZE_U];
orderedPair C2[SIZE_U * SIZE_U];

/* ========== SYSTEM FACTS
 */

/* ========== SYSTEM INITIALIZATION

  System initialization is included in main.c
*/

/* ========== SYSTEM STATES AND BEHAVIOR
 */
/*
  NextPlayerMove handles the player actions in the game board C.

  @params:
  - pos [int *]: a 2-d array of the player's move

  @restrictions:
  - pos must be in F.

  @returns: none

  Credits to Telan and Kraut for additional interpretations.
  Author: Ganituen
*/
void NextPlayerMove(int pos[SIZE_U]);

/*
  GameOver handles ending the game and determines who won the
  game.

  @params:
  - over [bool]: boolean to check if the game is over.

  @returns:
  - bool, to stop the game from going to the next player.

  Author: Ganituen
*/
bool GameOver(bool over);
#endif