#ifndef TILE_H
#define TILE_H

#include <iostream>


// Struct containing whether or not the given tile has walls in that cardinal direction
typedef struct boundaries {
    bool N;
    bool S;
    bool E;
    bool W;
}Boundaries;


// Tile class -- contains screen locations and whether or not walls exist
class Tile 
{
private:
    int _x_coord;
    int _y_coord;
    Boundaries _walls;
    int _ID;

public:

    //constructor -- note that default involves 
    Tile() {
        this->_x_coord = 0;
        this->_y_coord = 0;
        this->_walls.N = true;
        this->_walls.S = true;
        this->_walls.E = true;
        this->_walls.W = true;
        this->_ID = -1;
    }

    //sets the ID number to given integer
    void setID(int new_id) {
        this->_ID = new_id;
    }

    //returns the ID number
    int getID() {
        return this->_ID;
    }

    //retrieves x_coord
    int getX() {
        return this->_x_coord;
    }

    //retrieves y_coord
    int getY() {
        return this->_y_coord;
    }

    //retrieves Boundaries struct
    Boundaries & getWalls() {
        return this->_walls;
    }

    //sets (x,y) coordinates to the specified (x,y) values entered
    void setCoords(int x, int y) {
        this->_x_coord = x;
        this->_y_coord = y;
    }

    //reset all walls to exist
    void resetWalls() {
        this->_walls.N = true;
        this->_walls.S = true;
        this->_walls.E = true;
        this->_walls.W = true;
    }
};








#endif