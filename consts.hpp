#ifndef CONSTS_HPP
#define CONSTS_HPP

#define NUM_COLS 7
#define NUM_ROWS 6

#define PADDING 20                                                        // half the amount of space in between circles on the board
#define WIDTH ((2 * PIECE_RADIUS * NUM_COLS) + (2 * NUM_COLS * PADDING))  // allows for evenly spaced circles across the board
#define HEIGHT ((2 * PIECE_RADIUS * NUM_ROWS) + (2 * NUM_ROWS * PADDING)) // allows for evenly spaced circles top to bottom

#define GRAVITY 0.01f
#define PIECE_RADIUS 50
#define HITBOX_RADIUS (PIECE_RADIUS + (PADDING / 2))

#endif // CONSTS_HPP