# CIS190 Final Project
## Connect 4
### Jake Gurevitch & Aydan Gooneratne

## Overview

We plan on making a multiplayer connect 4 game. The project will have multiple different components:
* Graphical user interface - for displaying game state and allowing users to make moves.
* Networking - Code for bidirectional communication between two client instances of our game (may also switch to a client-server model)
* Game Logic - the actual logic for the game. We will likely have to create various classes such as a `Piece` or `Board` class and implement algorithms for determining a winner given `Board` state.

## External Libs

This may change depending on our needs but for now the plan is to use:

* Boost.Asio - a networking library
* cairomm - simple graphics library

## C++ Features

* Pieces will be stored by the board in a collection (likely a vector) and accessed via iterators. 
* We anticipate using unique pointers as well in order to better manage our instantiated classes (relative to using raw pointers).

## Project Structure

We anticipate writing several classes in order to manage state in our game (e.g., `Piece`, `Board`, `User/Player` - for networking). These will all be independent; there will likely not be a class hierarchy. 

## Time & Work Divide

Aydan will work on game logic and parts of networking. Jake will work on gui and parts of networking. Networking will probably take the most time to figure out and if we need to cut scope we could try and simplify that aspect of our project.
