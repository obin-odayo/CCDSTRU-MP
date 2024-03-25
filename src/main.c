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
  Last Updated: March 18, 2024
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
  binSearch: binary search algorithm for finding key in array (to be used for
  set F3).

  @params:
  - arr [struct orderedPair]: array where we do the search.
  - size [int]: size of arr.
  - key [struct orderedPair]: an ordered pair that we try to find in arr.

  @returns:
  - mid, if index is found.
  - -1, otherwise.
  Author: Ganituen
*/
int binSearch(struct orderedPair arr[], struct orderedPair key, int size) {
  int low = 0;
  int high = size - 1;
  int mid;

  while (low <= high) {
    mid = low + (high - low) / 2;

    // If the key is found
    if (arr[mid].x == key.x && arr[mid].y == key.y)
      // return index
      return mid;
    // for key is bigger
    if (arr[mid].x < key.x || (arr[mid].x == key.x && arr[mid].y < key.y))
      low = mid + 1;
    // for key is smaller
    else
      high = mid - 1;
  }

  return -1; // key not found
}

/* linSearch: linear search algorithm for finding key in array (to be used for
   C or F sets of players where moves may not necessarily be in order).

  @params:
  - arr [struct orderedPair *]: array to be searched
  - key [struct orderedPair]: element to search in array
  - size [int]: size of array

  @returns:
  - index where key is found, else returns -1.

  Author: Kraut
*/
int linSearch(struct orderedPair *arr, struct orderedPair key, int size) {
  int i;

  for (i = 0; i < size; i++)
    if (key.x == arr[i].x && key.y == arr[i].y)
      return i;

  return -1;
}

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
                struct orderedPair F3[], int sizeF1, int sizeF2, int sizeF3) {
  int i, j;
  int sizeUnion = 0;
  struct orderedPair unionF[sizeF1 + sizeF2];
  int index;

  // Get union of F1 and F2
  for (i = 0; i < sizeF1; i++) {
    // only copy if it is not 0. (i.e., not empty)
    if (F1[i].x > 0) {
      unionF[i].x = F1[i].x;
      unionF[i].y = F1[i].y;
      sizeUnion++;
    } else
      break; // break if end of F1
  }

  // do binary search and add all the ordered pairs in F2 not in unionF
  for (i = 0; i < sizeF2; i++) {
    // run if linSearch is not -1. So key is not found.
    if (linSearch(unionF, F2[i], sizeUnion) < 0) {
      unionF[sizeUnion].x = F2[i].x;
      unionF[sizeUnion].y = F2[i].y;
      sizeUnion++;
    }
  }
  // perform set difference on F3 and unionF (Contributed by: Kraut)
  for (i = 0; i < sizeUnion; i++) {
    index = binSearch(F3, unionF[i], sizeF3);
    if (index >= 0) {
      sizeF3--;
      for (j = index; j < sizeF3; j++)
        F3[j] = F3[j + 1]; // remove element from F3
    }
  }
  return sizeF3;
}

/* initializeF3: initializes the F3 matrix of all available moves for the game
   proper.

   @params:
   - F3[struct orderedPair]: array of F3

   @returns:
   - SIZE_2T [int]: initial cardinality of F3.

   Author: Kraut
*/
int initializeF3(struct orderedPair F3[]) {
  int i, j;
  int ctr = 0;
  for (i = 1; i < 7; i++)
    for (j = 1; j < 7; j++) {
      F3[ctr].x = i;
      F3[ctr].y = j;
      ctr++;
    }
  return SIZE_2T;
}

/* initializeBoard: initializes the board for the
   game proper.

   @params:
   - board [char**]: board to be initialized.

   Author: Telan
*/
void initializeBoard(char board[][6]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

/* updateBoard: updates the board based on player's
   input.

   @params:
   - player [struct playerType]: current player
   - mark [char]: mark of the current player
   - board [char**]: board to be updated

   @returns: none

   Precondition: intersection of F1 & F2 is a null
   set (player A and player B do not have a similar
   move)

   Author: Telan & Kraut
*/
void updateBoard(struct playerType player, char mark, char board[][6]) {
  int i, j;

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      if (board[i][j] != mark &&
          linSearch(player.F, F[i * 6 + j], player.sizeF) >= 0)
        board[i][j] = mark;
    }
  }
}

/* printBoard: displays the board of all player
   moves.

   @params:
   - board [char[][]]: board to be displayed

   @returns: none

   Author: Telan
*/
void printBoard(char board[][6]) {
  int i, j;
  printf("\n    1 2 3 4 5 6\n");
  printf("   -------------\n");
  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d |", i + 1);
    for (j = 0; j < BOARD_SIZE; j++) {
      printf(" %c", board[i][j]);
    }
    printf("\n");
  }
}

/* getPlayerInput: gets the player's input for their moves. Continues asking for
  input until pos is an element in F. Output of this function is to be used in
  nextPlayerMove.

  @params: none

  @returns:
  - pos (input)

  Author: Kraut
  */
struct orderedPair getPlayerInput() {
  struct orderedPair pos;

  do {
    if (next == true)
      printf("\n[A]");
    else
      printf("\n[B]");
    printf(" Enter your row and column moves: ");
    /*  Debugging, GANITUEN
        - Original code:
          scanf("%d %d", &pos.x, &pos.y);
        - Error message:
          warning: ignoring returnn value of
            `scanf` declared with attribute
            `warn_unused result`
        - Disregard this, this seems like a Replit problem(?)
          compiled this on my own computer and there's no problem
    */
    scanf("%d %d", &pos.x, &pos.y);
    if (pos.x > 6 || pos.x < 1)
      printf("Invalid row.\n");
    else if (pos.y > 6 || pos.y < 1)
      printf("Invalid column.\n");
  } while (pos.x > 6 || pos.x < 1 || pos.y > 6 ||
           pos.y < 1); // universe of discourse of set F

  return pos;
}

/* checkIfInF3: checks if pos is in F3 (set of all available moves).

  Assumption: over is false and next is either true or false.

  Remark: interpretation of "pos is an element of F3" in NextPlayerMove,
  line 1.

  @params:
  - pos [struct orderedPair]: current player's move.
  - F3 [struct orderedPair []]: set of all available moves in board F.
  - sizeF3 [int]: size (cardinality) of F3.

  @returns:
  - true if pos is in F3, else returns false.

  Author: Kraut
*/
bool checkIfInF3(struct orderedPair pos, struct orderedPair F3[], int sizeF3) {
  if (binSearch(F3, pos, sizeF3) < 0) // if pos was not found in F3
    return V[1];                      // false

  else
    return V[0]; // true
}

/* checkForS: checks if the player has achieved a solution in S given their
   moves as a subset of F. If yes, adds the orderedPair quadrant to the
   player's set C.

   @params:
   - player [struct playerType *]: pointer to a certain player.

   Author: Kraut
*/
void checkForS(struct playerType *player) {
  int i, j;
  int solFound;
  struct orderedPair currQuadrant;

  for (i = 0; i < NUM_SOLUTIONS; i++) {
    solFound = 1;
    currQuadrant.x = (S[i][0].x - 1) / 3 + 1;
    currQuadrant.y = (S[i][0].y - 1) / 3 + 1;
    for (j = 0; j < SIZE_SOLUTION; j++)
      if (S[i][j].x > 0)
        if (linSearch(player->F, S[i][j], player->sizeF) < 0) {
          solFound = 0;
          break;
        }
    // if solution was found and is not yet in CPlayer
    // interpretation for |P(F) intersect S| > |C| in NextPlayerMove of the MP
    // specs
    if (solFound && (linSearch(player->C, currQuadrant, player->sizeC) < 0)) {
      player->C[player->sizeC] = currQuadrant;
      player->sizeC++;
    }
  }
}

/* checkForP: checks a player's set C if they have the necessary quadrants to
  win the game.

  Remark: This function is the interpretation of the statement Ex(x is an
  element of PowerSet(C) ^ |x| > 0 ^ x is an element of P)

  Notes: This function does not check if F3 is an empty set (i.e. no more
  available moves)

  @params:
  - CPlayer [struct orderedPair []]: array of the player's quadrant/s with
  complete solution.
  - sizeCPlayer [int]: size (cardinality) of CPlayer.

  @returns:
  - 1 if a subset of P was found in the player's power set C, else returns 0.

  Author: Kraut
*/
int checkForP(struct orderedPair CPlayer[], int sizeCPlayer) {
  int i, j;
  int winFound;

  for (i = 0; i < 2; i++) {
    winFound = 1;
    for (j = 0; j < 2; j++)
      if (linSearch(CPlayer, P[i][j], sizeCPlayer) < 0) {
        winFound = 0;
        break;
      }
    if (winFound)
      return 1;
  }
  return 0;
}

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
  - char *, winning message and who won.

  Credits to Telan for adding missing parameters
  Author: Ganituen
*/
char *GameOver(bool over, struct orderedPair C1[], int sizeC1,
               struct orderedPair C2[], int sizeC2, char result[][7],
               int sizeF3) {
  // result is either B wins
  // or A wins

  int player = 0; // index of the player that won
                  // 1 is player A
                  // 2 is player B
  // check who won
  // TODO: MISSING PARAMETERS, solved by Telan
  // add exists x (x in P(C1) && |x| > 0 && x in P)
  if (over == true && next == true && checkForP(C1, sizeC1) > 0) {
    player = 1;
    return result[player];
  }

  // add exists x (x in P(C1) && |x| > 0 && x in P)
  else if (over == true && next == false && checkForP(C2, sizeC2) > 0) {
    player = 2;
    return result[player];
  }

  else if (over == true && sizeF3 == 0)
    return result[3];

  // next player's move
  else {
    next = !next;
    return result[0]; // return nothing
  }
}

/*
  NextPlayerMove handles the player actions in the game board.

  @params:
  - pos [struct orderedPair]: a 2-d array of the player's move
  - F3 [struct orderedPair]: array of orderedPairs
  - sizeF3 [int]: number of elements in F3
  - A [struct playerType *]: pointer to player A
  - B [struct playerType *]: pointer to player B
  - board [char]: 2-d array of the game board and moves

  @restrictions:
  - pos must be in F.

  @returns: none

  Credits to Telan and Kraut for additional interpretations.
  Author: Ganituen & Kraut
*/
void NextPlayerMove(struct orderedPair pos, struct orderedPair F3[], int sizeF3,
                    struct playerType *A, struct playerType *B,
                    char board[][6]) {

  // this performs line 4 of nextPlayerMove in the specs
  if (over == false && next == true && checkIfInF3(pos, F3, sizeF3)) {
    A->F[A->sizeF++] = pos; // update F set and size
    updateBoard(*A, 'x', board);
    checkForS(A); // this performs line 6 of nextPlayerMove in the specs
  }

  // this performs line 5 of nextPlayerMove in the specs
  else if (over == false && next == false && checkIfInF3(pos, F3, sizeF3)) {
    B->F[B->sizeF++] = pos; // update F set and size
    updateBoard(*B, 'o', board);
    checkForS(B); // this performs line 7 of nextPlayerMove in the specs
  }
}

/* systemFact2: performs system fact 2 in the specs.
  @params:
  - sizeF3 [int]: cardinality of F3
  - A [struct playerType]: player A
  - B [struct playerType]: player B

  @returns: boolean value of over

  Author: Kraut
*/
bool systemFact2(int sizeF3, struct playerType A, struct playerType B) {
  if (checkForP(A.C, A.sizeC) || checkForP(B.C, B.sizeC) || sizeF3 == 0)
    return true;
  else
    return false;
}

int main() {
  struct orderedPair F3[SIZE_2T];
  int sizeF3 = initializeF3(F3);

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
  next = V[1];
  char *checker;
  struct playerType A; // F1, C1
  A.sizeF = 0;
  A.sizeC = 0;
  struct playerType B; // F2, C2
  B.sizeF = 0;
  B.sizeC = 0;
  char result[4][7] = {"\0", "A wins", "B wins", "draw"};
  struct orderedPair pos;
  char board[SIZE_T][SIZE_T];
  initializeBoard(board);

  while (true) {

    printBoard(board);
    pos = getPlayerInput();

    // call NextPlayerMove(pos)
    NextPlayerMove(pos, F3, sizeF3, &A, &B, board);
    /* ========== SYSTEM FACTS

      Check if the system facts are still valid.
      1. Get the array F3 given F1 and F2 after the moves.
      2. Check if game is over.
        - Recall GameOver has type char *
        - If the game is not over it prints out a blank string (i.e., "")
        - Continue the game if it is not true

      Author: Ganituen and Kraut
    */
    sizeF3 = systemFact1(A.F, B.F, F3, A.sizeF, B.sizeF, sizeF3);
    over = systemFact2(sizeF3, A, B);

    checker = GameOver(over, A.C, A.sizeC, B.C, B.sizeC, result, sizeF3);
    if (strcmp(checker, "")) {
      printf("\n%s!\n", checker);
      break; // end the game
    }
    /* ========== GAME PROPER
       1.
    */
  }
  printf("\nFinal board:\n");
  printBoard(board);
  return 0;
}

/*
  END OF main.c
  Ganituen, Kraut, Telan

  CCDSTRU Machine Project
  S14, Ms. Jemie Que
*/