/*
  Machine Project for Discrete Structures (CCDSTRU)
  De La Salle University, Term 2 AY 2023-2024

  `common.h` is a header file that contains
  our common functions, typedef, and other macros.

  Created By:   GANITUEN, Zhean Robby L.
                KRAUT, Maria Clarisse P.
                TELAN, John Andrei S.

  Created For:  CCDSTRU Machine Project, Ms. Jemie Que

  Created On:   March 10, 2024
  Last Updated: March 18, 2024
*/

#ifndef common_h
#define common_h

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
  type definition for string characters.

  Author: Ganituen
*/
typedef char String[32];

/*
  orderedPair: a structure that stores an x and y value

  @fields:
  - x [int]: x value of ordered pair.
  - y [int]: y value of ordered pair.

  Author: Ganituen
*/
struct orderedPair {
  int x;
  int y;
};

/*
  playerType: a structure that stores a player's moves in the game.
 
  @fields:
  - F [struct orderedPair]: array to store player's F moves.
  - sizeF [int]: size of F moves, initialized to 0.
  - C [struct orderedPair]: array to store player's C moves.
  - sizeC [int]: size of C moves, initialized to 0.

  author: Kraut
*/
struct playerType {
  struct orderedPair F[36];
  int sizeF; //initialize to 0
  struct orderedPair C[4];
  int sizeC; //initialize to 0
};

/*
  binSearch: binary search algorithm for finding key in array.

  @params:
  - arr [struct orderedPair]: array where we do the search.
  - key [struct orderedPair]: an ordered pair that we try to find in arr.
  - arrSize [int]: number of eligible elements in arr.

  @returns:
  - mid, if index is found.
  - -1, otherwise.

  Author: Ganituen
*/
int binSearch(struct orderedPair arr[], struct orderedPair key, int arrSize);

/* linSearch: linear search algorithm for finding key in array (to be used for    C or F sets of players where moves may not necessarily be in order).

  @params:
  - arr [struct orderedPair *]: array to be searched
  - key [struct orderedPair]: element to search in array
  - size [int]: size of array

  @returns:
  - index where key is found, else returns -1.

  Author: Kraut
*/
int linSearch(struct orderedPair *arr, struct orderedPair key, int size);

#endif

/*
  END OF common.h
  Ganituen, Kraut, Telan

  CCDSTRU Machine Project
  S14, Ms. Jemie Que
*/