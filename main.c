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
  binSearch: binary search algorithm for finding key in array.

  @params:
  - arr [struct orderedPair]: array where we do the search.
  - size [int]: size of arr.
  - key [struct orderedPair]: an ordered pair that we try to find in arr.

  @returns:
  - mid, if index is found.
  - 0, otherwise.
  Author: Ganituen
*/
int binSearch(struct orderedPair arr[], struct orderedPair key){
  int low = 0;
  int high = SIZE_2T - 1; 
  int mid;

  while (low <= high){
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

  return 0; // key not found
}

/*
  systemFact1: checks the first system fact and returns the
  cardinality of F3.

  @params:
  - F [struct orderedPair]: array F.
  - F1 [struct orderedPair]: array F1. Moves of player 1 in board F.
  - F2 [struct orderedPair]: array F2. Moves of player 2 in board F.
  - F3 [struct orderedPair]: array F3. Available moves in player 3.

  @returns:
  - cardinality [int]: cardinality of F3.

  Author: Ganituen
*/
int systemFact1(struct orderedPair F[], struct orderedPair F1[], struct orderedPair F2[], struct orderedPair F3[]) {
    int cardinality = 0; // cardinality of F3, the output of the function.
    int i;
    int sizeUnion = 0;
    struct orderedPair unionF[SIZE_2T];
    
    // Get union of F1 and F2
    for (i = 0; i < SIZE_2T; i++){
      // only copy if it is not 0. (i.e., not empty)
      if (F1[i].x > 0){
        unionF[i].x = F1[i].x;
        unionF[i].y = F1[i].y;
        sizeUnion++;
      } else break; // break if end of F1
    }

    // do binary search and add all the ordered pairs in F2 not in unionF
    for (i = 0; i < SIZE_2T; i++){
      // run if binSearch is not 0. So key is not found.
      if(!binSearch(unionF, F2[i])){
        unionF[sizeUnion].x = F2[i].x;
        unionF[sizeUnion].y = F2[i].y;
        sizeUnion++;
      }
    }

    // TO DO. SET SUBTRACTION OF F and unionF
    // TO DO. SET THIS AS F3
    // TO DO. CALCULATE CARDINALITY OF F3
        
    
    return cardinality;
}

int main()
{
  int i;
  
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

  return 0;
}