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
  Last Updated: March 10, 2024
*/

#ifndef common_h
#define common_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef char String[32];

struct orderedPair {
  int x;
  int y;
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
int systemFact1(struct orderedPair F[], struct orderedPair F1[], struct orderedPair F2[], struct orderedPair F3[]);

#endif