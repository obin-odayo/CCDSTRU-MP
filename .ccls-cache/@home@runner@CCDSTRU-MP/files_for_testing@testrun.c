
#include <stdio.h>
#define SIZE_U 2
#define SIZE_2U 4 // SIZE_U * 2
#define SIZE_T 6
#define SIZE_2T 36 // SIZE_T * 2
#define NONE -1
#define NUM_SOLUTIONS 4
#define SIZE_SOLUTION 6
#define BOARD_SIZE 6


struct orderedPair {
  int x;
  int y;
};

struct playerType {
  struct orderedPair F[36];
  int sizeF; //initialize to 0
  struct orderedPair C[4];
  int sizeC; //initialize to 0
};

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
{{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}}; 

struct orderedPair F[SIZE_2T] = {
{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3},
{2, 4}, {2, 5}, {2, 6}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
{4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 1}, {5, 2}, {5, 3},
{5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

struct orderedPair P[SIZE_U][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

int linSearch(struct orderedPair *arr, struct orderedPair key, int size)
{
  int i;

  for (i = 0; i < size; i++)
    if (key.x == arr[i].x && key.y == arr[i].y)
      return i;

  return -1;
}

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

int systemFact1(struct orderedPair F1[], struct orderedPair F2[], struct                         orderedPair F3[], int sizeF1, int sizeF2, int sizeF3) {
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
  // run if binSearch is not -1. So key is not found.
  if (linSearch(unionF, F2[i], sizeUnion) < 0) {
    unionF[sizeUnion].x = F2[i].x;
    unionF[sizeUnion].y = F2[i].y;
    sizeUnion++;
  }
}
  //perform set difference on F3 and unionF
  for (i = 0; i < sizeUnion; i++)
  {
    index = binSearch(F3, unionF[i], sizeF3);
    if (index >= 0)
    {
      sizeF3--;
      for (j = index; j < sizeF3; j++)
          F3[j] = F3[j+1]; //remove element from F3
    }
  }
  return sizeF3;
}

int initializeF3(struct orderedPair F3[])
  {
    int i, j;
    int ctr = 0;
    for (i = 1; i < 7; i++)
      for (j = 1; j < 7; j++)
        {
          F3[ctr].x = i;
          F3[ctr].y = j;
          ctr++;
        }
    return SIZE_2T;
  }

/* checkForS: checks if the player has achieved a solution in S given their        moves as a subset of F. If yes, adds the orderedPair quadrant to the            player's set C.

   @params:
   - FPlayer [struct orderedPair]: array of the current player's moves.
   - sizeFPlayer [int]: size of FPlayer.
   - CPlayer [struct orderedPair]: array of the player's quadrant with complete     solution.
   - CPlayerSize [int *]: size of CPlayer.

   @returns 1 if a new solution was found, else returns 0.

   Author: Kraut
*/
void checkForS(struct playerType *player)
{
  int i, j;
  int solFound;
  struct orderedPair currQuadrant;

  for (i = 0; i < NUM_SOLUTIONS; i++) {
      solFound = 1;
      currQuadrant.x = (S[i][0].x - 1)/3 + 1;
      currQuadrant.y = (S[i][0].y - 1)/3 + 1;
      for (j = 0; j < SIZE_SOLUTION; j++) 
          if (S[i][j].x > 0)
            if (linSearch(player->F, S[i][j], player->sizeF) < 0) {
              solFound = 0;
              break;
        }
      //if solution was found and is not yet in CPlayer
      //interpretation for |P(F) intersect S| > |C| in NextPlayerMove of the MP specs
      if (solFound && (linSearch(player->C, currQuadrant, player->sizeC) < 0)){
        player->C[player->sizeC] = currQuadrant;
        player->sizeC++;
      }
  }
}

/*
  checkIfGood: checks if pos is in F3 (set of all available moves).

  @params:
  - pos [struct orderedPair]: current player's move.
  - F3 [struct orderedPair]: set of all available moves.
  - sizeF3 [int]: size of F3.
  
  @returns:
  - 1 if pos is in F3, else returns 0.
  
  Author: Kraut
*/
int checkIfGood(struct orderedPair pos, struct orderedPair F3[], int sizeF3)
{
  if (binSearch(F3, pos, sizeF3) < 0) //if pos was not found in F3
    return 0;
  else return 1;
}

int checkForP(struct orderedPair CPlayer[], int sizeCPlayer)
{
  int i, j;
  int winFound;
  
  for (i = 0; i < 2; i++)
    {
      winFound = 1;
      for (j = 0; j < 2; j++)
        if (linSearch(CPlayer, P[i][j], sizeCPlayer) < 0)
          winFound = 0;
      if (winFound)
        return 1;
    }
  return 0;
}

int systemFact2(struct playerType A, struct playerType B, int sizeF) {
  if (checkForP(A.C, A.sizeC) || checkForP(B.C, B.sizeC) || sizeF == 0) 
    return 1; //return negated value of over

  else return 0; //return current value of over
}
/* Assumption: over is false and next is either true or false.
  */
int getPlayerInput(struct orderedPair FPlayer[], int *sizeFPlayer, struct orderedPair F3[], int sizeF3)
{
  struct orderedPair pos;

  do {
    printf(" Enter your row and column moves: ");
    scanf("%d%d", &pos.x, &pos.y);
    if (pos.x > 6 || pos.x < 1 ||
        pos.y > 6 || pos.y < 1)
      printf("Invalid column/row.\n");
  } while (pos.x > 6 || pos.x < 1 ||
        pos.y > 6 || pos.y < 1);

  if (checkIfGood(pos, F3, sizeF3)) {
    FPlayer[*sizeFPlayer] = pos;
    (*sizeFPlayer)++;
    return 1;
  }
  else return 0;
}

void initializeBoard(char board[][6]) {
  int i, j;
    for ( i = 0; i < BOARD_SIZE; i++) {
        for ( j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void updateBoard(struct playerType player, char mark, char board[][6])
{
  int i, j;

  for (i = 0; i < 6; i++) {
    for(j = 0; j < 6; j++) {
      if (board[i][j] != mark && linSearch(player.F, F[i*6+j], player.sizeF) >= 0)
        board[i][j] = mark;
    }
  }
}

void printBoard(char board[][6]) {
  int i, j;
    printf("\n    1 2 3 4 5 6\n");
    printf("   -------------\n");
    for ( i = 0; i < BOARD_SIZE; i++) {
        printf("%d |", i + 1);
        for ( j = 0; j < BOARD_SIZE; j++) {
            printf(" %c", board[i][j]);
        }
        printf("\n");
    }
    if (next == true)
        printf("A:");
    else printf("B:");
}
int main()
{
  int i;
  struct playerType A;
  A.sizeF = 0;
  A.sizeC = 0;
  struct playerType B;
  B.sizeF = 0;
  B.sizeC = 0;
  struct orderedPair F3[36];
  int sizeF3 = initializeF3(F3);
  int next = 0;
  char board[6][6];
  initializeBoard(board);
  
  while (!checkForP(A.C, A.sizeC) && !checkForP(B.C, B.sizeC) && sizeF3 != 0)
    {
      if (next)
      {
        printf("\n[A] ");
        if (getPlayerInput(A.F, &A.sizeF, F3, sizeF3))
          checkForS(&A);
      }
      else
      {
        printf("\n[B]");
        if (getPlayerInput(B.F, &B.sizeF, F3, sizeF3))
          checkForS(&B);
      }

      sizeF3 = systemFact1(A.F, B.F, F3, A.sizeF, B.sizeF, sizeF3);

      if (next)
        updateBoard(A, 'x', board);
      else
        updateBoard(B, 'o', board);
      
      printBoard(board);
      next = !next;

      
    }
}
