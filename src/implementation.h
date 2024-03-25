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
  Last Updated: March 18, 2024
*/

#ifndef implementation_h
#define implementation_h

#include "common.h"

#define SIZE_U 2
#define SIZE_2U 4 // SIZE_U * 2
#define SIZE_T 6
#define SIZE_2T 36 // SIZE_T * 2
#define NONE -1
#define NUM_SOLUTIONS 4
#define SIZE_SOLUTION 6
#define BOARD_SIZE 6

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
struct orderedPair C[4] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};

/*
  F: T X T
  T is the Cartesian product of T and T.
  Number of possible elements in T is 36

  Author: Ganituen
*/
struct orderedPair F[SIZE_2T] = {
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
struct orderedPair S[4][6] = {
    {{1, 1},
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
    {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}}; // Solution for C(2,1)
                                                       // represented as "s"

/*
  P is the applicable quadrants that must be achieved in order
  to declare a winner.
  For example, if A was able to get the solutions of C(1,1) AND
  C(2,2), then they are the winner. Else if A got the solution
  C(1,1) AND C(1,2), the game is not over.

  Author: Kraut
*/
struct orderedPair P[SIZE_U][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

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
// struct orderedPair F1[SIZE_2T];
// struct orderedPair F2[SIZE_2T];
// struct orderedPair F3[SIZE_2T];

// struct orderedPair C1[4];
// struct orderedPair C2[4];

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
  - pos [struct orderedPair]: a 2-d array of the player's move
  - F3 [struct orderedPair]: array of orderedPairs
  - sizeF3 [int]: number of elements in F3
  - A [struct playerType]: player A
  - B [struct playerType]: player B
  - board [char]: 2-d array of the game board and moves

  @restrictions:
  - pos must be in F.

  @returns: none

  Credits to Telan and Kraut for additional interpretations.
  Author: Ganituen
*/
void NextPlayerMove(struct orderedPair pos, struct orderedPair F3[], int sizeF3,
                   struct playerType *A, struct playerType *B, char board[][6]);

/*
  GameOver handles ending the game and determines who won the
  game.

  @params:
  - over [bool]: boolean to check if the game is over.
  - next [bool]: boolean to check if it's player A's turn.
  - C1 [struct orderedPair]: array representing player 1's quadrants.
  - sizeC1 [int]: size of player 1's quadrants array.
  - C2 [struct orderedPair]: array representing player 2's quadrants.
  - sizeC2 [int]: size of player 2's quadrants array.

  @returns:
  - char *, winning message and who won. If the game is not over, an empty
  string is returned.

  Author: Ganituen
*/
char *GameOver(bool over, struct orderedPair C1[], int sizeC1,
               struct orderedPair C2[], int sizeC2, char result[][7], int sizeF3);

/* intializeF3: Initializes F3 for the program.

   @params:
   - F3 [struct orderedPair*]: an array of all unoccupied cells in the F matrix.

   @returns:
   - size of F3
*/
int initializeF3(struct orderedPair F3[]);

/*
  systemFact1: performs the first system fact and returns the
  cardinality of F3.

  @params:
  - F1 [struct orderedPair]: array F1. Moves of player 1 in board F.
  - F2 [struct orderedPair]: array F2. Moves of player 2 in board F.
  - F3 [struct orderedPair]: array F3. Available moves in board F.
  - sizeF1 [int]: cardinality of F1.
  - sizeF2 [int]: cardinality of F2.
  - sizeF3 [int]: cardinality of F3.

  @returns:
  - sizeF3 [int]: cardinality of F3.

  Precondition: intersection of F1 & F2 is a null set (player A and B do not
  have a move on the same cell)

  Author: Ganituen & Kraut
*/
int systemFact1(struct orderedPair F1[], struct orderedPair F2[],
                struct orderedPair F3[], int sizeF1, int sizeF2, int sizeF3);

/* checkIfGood: checks if pos is in F3 (set of all available moves).

  Remark: interpretation of "pos is an element of F3" in NextPlayerMove,
  line    1.

  @params:
  - pos [struct orderedPair]: current player's move.
  - F3 [struct orderedPair *]: set of all available moves in board F.
  - sizeF3 [int]: size of F3.

  @returns:
  - true if pos is in F3, else returns false.

  Assumption: over is false.

  Author: Kraut
*/
bool checkIfInF3(struct orderedPair pos, struct orderedPair F3[], int sizeF3);

/* checkForS: checks if the player has achieved a solution in S given their
   moves as a subset of F. If yes, adds the orderedPair quadrant to the player's
   set C.

   @params:
   - FPlayer [struct orderedPair]: array of the current player's moves.
   - sizeFPlayer [int]: size of FPlayer.
   - CPlayer [struct orderedPair]: array of the player's quadrant/s with
   complete solution.
   - CPlayerSize [int *]: size of CPlayer.

   @returns 1 if a new solution was found, else returns 0.

   Author: Kraut
*/
void checkForS(struct playerType *player);

#endif

/*
  END OF implementation.h
  Ganituen, Kraut, Telan

  CCDSTRU Machine Project
  S14, Ms. Jemie Que
*/