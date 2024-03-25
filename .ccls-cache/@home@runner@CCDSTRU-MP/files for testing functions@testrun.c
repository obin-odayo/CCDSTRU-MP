
#include <stdio.h>
#define SIZE_U 2
#define SIZE_2U 4 // SIZE_U * 2
#define SIZE_T 6
#define SIZE_2T 36 // SIZE_T * 2
#define NONE -1
#define NUM_SOLUTIONS 4
#define SIZE_SOLUTION 6


struct orderedPair {
  int x;
  int y;
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
  if (binSearch(unionF, F2[i], sizeUnion) < 0) {
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
int checkForS(struct orderedPair FPlayer[], int sizeFPlayer, struct orderedPair CPlayer[], int *sizeCPlayer)
{
  int i, j;
  int ind;
  int solFound;
  struct orderedPair currQuadrant;

  for (i = 0; i < NUM_SOLUTIONS; i++)
    {
      solFound = 1;
      currQuadrant.x = (S[i][0].x - 1)/3 + 1;
      currQuadrant.y = (S[i][0].y - 1)/3 + 1;
      for (j = 0; j < SIZE_SOLUTION; j++)
        {
          if (S[i][j].x > 0)
          {
            ind = linSearch(FPlayer, S[i][j], sizeFPlayer);
            if (ind < 0)
              solFound = 0;
          }
        }
      //if solution was found and is not yet in CPlayer
      //interpretation for |P(F) intersect S| > |C| in NextPlayerMove of the MP         specs
      if (solFound && (linSearch(CPlayer, currQuadrant, *sizeCPlayer) < 0))
      {
        CPlayer[*sizeCPlayer] = currQuadrant;
        (*sizeCPlayer)++;
        return 1;
      }
    }
  return 0;
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
  int i;
  int ind;

  for (i = 0; i < sizeF3; i++)
    {
      ind = binSearch(F3, pos, sizeF3);
      if (ind >= 0)
        break;
    }

  if (ind < 0) //if pos was not found in F3
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

int systemFact2(int sizeF3, struct orderedPair C1[], int sizeC1, struct orderedPair C2[], int sizeC2, char * winner)
{
  if (sizeF3 == 0)
    return 1;

  else
  {
    if (checkForP(C1, sizeC1))
    {
      *winner = 'A';
      return 1;
    }
      
    else if (checkForP(C2, sizeC2))
    {
      *winner = 'B';
      return 1;
    }
      
    else 
    {
      *winner = '\0';
      return 0;
    }
  }
}

int main()
{
  int i;
  struct orderedPair F1[10] = {{4, 4},
 {4, 6},
 {5, 5},
 {6, 4},
 {6, 6},
  {1, 1},
   {1, 3},
   {2, 2},
   {3, 1},
   {3, 3}
};
  int sizeF1 = 10;
  struct orderedPair F2[10] = {{2, 1}, {2, 2}, {2, 3}, {2, 5}, {5, 5}};
  int sizeF2 = 5;
  struct orderedPair F3[SIZE_2T];
  int sizeF3 = initializeF3(F3);
  sizeF3 = systemFact1(F1, F2, F3, sizeF1, sizeF2, sizeF3);
  struct orderedPair C1[4];
  struct orderedPair C2[4];
  int sizeC1 = 0;
  int sizeC2 = 0;
  struct orderedPair pos = {5, 5};
  char winner;
  
  printf("%d\n", checkIfGood(pos, F3, sizeF3));
  sizeF3 = systemFact1(F1, F2, F3, sizeF1, sizeF2, sizeF3);
  printf("%d\n", checkForS(F1, sizeF1, C1, &sizeC1));
  printf("%d\n", checkForS(F1, sizeF1, C1, &sizeC1));
  for (i = 0; i < sizeC1; i++)
    printf("%d, %d\n", C1[i].x, C1[i].y);
  printf("%d\n", checkForP(C1, sizeC1));
  printf("%d\n", systemFact2(sizeF3, C1, sizeC1, C2, sizeC2, &winner));
}