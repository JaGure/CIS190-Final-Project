# CIS190 Final Project

## Connect 4

### Jake Gurevitch & Aydan Gooneratne

## Usage Instructions

To build the programs, run `make client` and `make server`. Run the server program with `./server` then run two client programs with `./client`.
Alternate doing moves and reseting the game with "R" between the two programs.

## Overview

We plan on making a multiplayer connect 4 game. The project will have multiple different components:

- Graphical user interface - for displaying game state and allowing users to make moves.
- Networking - Code for bidirectional communication between two client instances of our game (may also switch to a client-server model)
- Game Logic - the actual logic for the game. We will likely have to create various classes such as a `Piece` or `Board` class and implement algorithms for determining a winner given `Board` state.

## External Libs

- SFML (for graphics and networking)

## C++ Features

- Pieces are stored by the board in a container (2D array) and accessed via iterators.
- We used unique pointers as well in order to better manage our instantiated classes (relative to using raw pointers).

## Project Structure

The `Board` class manages the board interally. The `Game` class uses the `Board` class to run the game. The `Piece` class is used for drawing pieces (including piece physics). The `Main` class runs the game by launching a game client. Finally, the `Server` class launches a server which facilitates communciation between two clients.

## Time & Work Divide

Aydan will work on game logic and parts of networking. Jake will work on gui and parts of networking. Networking will probably take the most time to figure out and if we need to cut scope we could try and simplify that aspect of our project.
