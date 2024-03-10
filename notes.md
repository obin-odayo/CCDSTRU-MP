# Notes
Notes on Machine Project specifications.

## Applicable Sets
- These seem to be arrays, so it would be best to implement them as arrays.

### Interpretations

- U  -  set of integers less than 3
- T  -  set of integers less than 7
- C  -  2 x 2 matrix of all ordered pairs from U
- F  -  6 x 6 matrix of all ordered pairs from T
- V  -  set of Boolean values (true and false)
- P  -  applicable quadrans to declare a winner
        a 2 x 2 matrix of 2-D arrays
- S  -  possible solutions for each quadrant of the 6 x 6 matrix


## System Variables
- "good", "over", "next" in V means that the phrases "good", "over", and "next" can have the property of true or false. (See System Initialization for these).

### Interpretations

- good  -  determines the legality of a move
- over  -  determines if the game is over
- next  -  determines if it's the next player's move
- C1    -  moves of player 1 in the board C. C1 subset of C.
- C2    -  moves of player 2 in the board C. C1 subset of C.
- F1    -  The moves of player 1 in the board F.
           F1 is a subset of F.
- F2    -  The moves of player 2 in the board F.
           F2 is a subset of F.
- F3    -  The moves available in the matrix F. 
           F3 is a subset of F.

## System Facts
- I think what system facts mean is that for every thing the program does, it must meet the two system facts (so, if the code does a process and we check a system fact after the process and it returns false. Then, the game is done.)

### Interpretations
- F3 = F - (F1 U F2)    -    The moves available in the matrix F.
- over iff. ...         -    Shows the game is done if the 
                             conditions are met

## System Initialization
- "good" and "next" is initialized as false.
- However, "next" (at initialization) is left without definition.
- Player A's sets
  - F1
  - C1
- Player B's sets
  - F2
  - C2
- F3 is the set of all available moves. No. of elements decreases as game progresses
- "over" is defined as false at first. "over" becomes true if there are no more available moves (F3 is an empty set) or if any of the two players were able to achieve an element in P based on their respective sets (C1 or C2).
  
## System States and Behavior
- I think what this means is that all the lines below it will run if the argument inside is true.
  - So, NextPlayerMove will run if pos in F is true.
  - And, GameOver will run if over is true.
- I think "next" indicates whose turn it is. If "next" is true, then it is Player A's turn. Else it is Player B's turn.
  - After every turn, "next" is updated as long as "over" is false (see last line of GameOver)
- "good" becomes true if a player move is legal (the cell is not occupied yet. In terms of the specs, "pos" must be an element in F3). If these conditions are met, F3 and either F1 or F2 are updated accordingly. I'm not sure if we should ask for another input or if the next player should take their turn if the move is invalid.
- I think "c" and "d" in NextPlayerMove refers to the quadrant in which the player made their move
  - For example, if pos = F(5,6), then c = 2 and d = 2. Thus, pos is in quadrant C(2,2). You can refer to the grid reference in specs.h for an idea of how it looks like.

## Miscellaneous
- Maybe we can implement structure dataypes for players for easier identification (set of moves, set of quadrants, and name)