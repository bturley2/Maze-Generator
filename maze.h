#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "tile.h"
#include "DisjSets.h"


using std::cout;
using std::endl;
using std::vector;

#define TILE_SIZE 25

class Maze 
{
private:
    vector<vector<Tile>> _maze;
    std::ofstream _outfile;
    DisjSets * _sets;



    //master control function which generates a 20x20 maze by default
    void buildMaze(int x = 20, int y = 20, std::string filename = "maze.svg") {

        clearMaze(x, y);    //generate the fully tiled maze -- remember to open (1,1) W and (20,20) E
        _sets = new DisjSets(x * y);    // create a new Disjoint Set object w/ the number of items in the maze

        _outfile.open(filename);  //open filestream
        prepareFile(filename == "maze.svg");      //fill filestream w/ opening lines


        createPath(x,y);   //fill out the maze -- connect sets until only 1 set exists


        printMaze();    //print current maze's lines to the filestream

        _outfile << "</svg>";   //fill filestream w/ closing line
        _outfile.close();   //close filestream
    }

    //randomly selects tiles and connects them to nearby tiles until all tiles are in the same set
    void createPath(int x_max, int y_max) {


        //keep going until there is only one set left
        while(_sets->getNumSets() > 1) {


            //pick a random cell (x,y) that is not along the border
            int x = 0, y = 0;
            x = rand() % x_max;
            y = rand() % y_max;


            //check the walls in random order,
            //if the tile across that wall belongs to a different set, then merge them
            // and update their boundaries to reflect the change

            int direction = rand() % 4;

            if(direction == 0 && connectSets(x, y, x - 1, y)) {   //W
                _maze.at(x).at(y).getWalls().W = false;  //update W wall
                _maze.at(x - 1).at(y).getWalls().E = false;  //update neighbor's E wall
            }
            else if (direction == 1 && connectSets(x, y, x, y - 1)) { //N
                _maze.at(x).at(y).getWalls().N = false;  //update N wall
                _maze.at(x).at(y - 1).getWalls().S = false;  //update neighbor's S wall
            }
            else if (direction == 2 && connectSets(x, y, x + 1, y)) { //E
                _maze.at(x).at(y).getWalls().E = false;  //update E wall
                _maze.at(x + 1).at(y).getWalls().W = false;  //update neighbor's E wall
            }
            else if (direction == 3 && connectSets(x, y, x, y + 1)) { //S
                _maze.at(x).at(y).getWalls().S = false;  //update S wall
                _maze.at(x).at(y + 1).getWalls().N = false;  //update neighbor's N wall
            }
 
        }

    }

    //checks if two tiles are a part of the same set. 
    //If they are, then merges them and updates tile's boundaries to reflect the change
    //returns bool representing whether or not the sets were merged
    bool connectSets(int x1, int y1, int x2, int y2) {
        
        //check bounds first
        if(x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 
            || x1 >= _maze.size() || y1 >= _maze.at(0).size() 
            || x2 >= _maze.size() || y2 >= _maze.at(0).size() ) {
            return false;
        }

        int first = _maze.at(x1).at(y1).getID();
        int second = _maze.at(x2).at(y2).getID();

        if(_sets->find(first) != _sets->find(second)) {
            _sets->unionSets(first, second);
            return true;
        }
        return false;
    }

    //prints the entire maze as it currently exists to _outfile
    void printMaze() {

        // <line x1="100" x2="125" y1="50" y2="50" style="stroke:black; stroke-width:2"/>          << endl;
        for(int i = 0; i < _maze.size(); ++i) {

            for(int k = 0; k < _maze.at(i).size(); ++k) {
                Boundaries wall = _maze.at(i).at(k).getWalls(); //store the wall values
                int x = _maze.at(i).at(k).getX();      //store the x_coord
                int y = _maze.at(i).at(k).getY();      //store the y_coord
                
                if(wall.N) {    //check N wall
                    printLine(x, x + TILE_SIZE, y, y);
                }

                if(wall.S) {    //check S wall
                    printLine(x, x + TILE_SIZE, y + TILE_SIZE, y + TILE_SIZE);
                }

                if(wall.E) {    //check E wall
                    printLine(x + TILE_SIZE, x + TILE_SIZE, y, y + TILE_SIZE);
                }

                if(wall.W) {    //check W wall
                    printLine(x, x, y, y + TILE_SIZE);
                }
            }
        }


    }

    //prints a single line to the outfile given the (x,y) values for location
    //helper function for printMaze()
    void printLine(int x_start, int x_end, int y_start, int y_end) {
        _outfile << "<line x1=\"" << x_start << "\" x2=\"" << x_end << "\" y1=\"" << y_start << "\" y2=\"" << y_end
                 << "\" style=\"stroke:black; stroke-width:2\"/>" << endl;
    }

    //prints the opening 12 or so .svg lines provided by the instructor into the output file
    void prepareFile(bool regular_maze) {
        _outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        _outfile << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
        _outfile << "<svg xmlns=\"http://www.w3.org/2000/svg\">" << endl << endl;
        _outfile << "<text x=\"35\" y=\"70\" font-family=\"Arial\" font-size=\"25\" fill=\"black\">" << endl;
        _outfile << "	Start" << endl << "</text>" << endl;
        
        if(regular_maze) {
            _outfile << "<text x=\"" << 607 << "\" y=\"" << 547 << "\" font-family=\"Arial\" font-size=\"25\" fill=\"black\">" << endl;
        }
        else {
                    _outfile << "<text x=\"" << 107 + 100 * TILE_SIZE << "\" y=\"" << 77 + 50 * TILE_SIZE
                        << "\" font-family=\"Arial\" font-size=\"25\" fill=\"black\">" << endl;

        }

        _outfile << "	End" << endl << "</text>" << endl << endl;
    }

    //resets all values of _maze to be of size (x,y),
    //resets each tile to have all walls and each tile to be its own set,
    //resets _num_sets
    void clearMaze(int x, int y) {
        int count = 0;
        _maze.resize(x);
        
        for (int i = 0; i < _maze.size(); ++i) {
            _maze.at(i).resize(y);

            for(int k = 0; k < y; ++k) {
                _maze.at(i).at(k).setCoords(i * 25 + 100, k * 25 + 50);   //set the coordinates
                _maze.at(i).at(k).resetWalls();     //reset to have all walls
                _maze.at(i).at(k).setID(count++);   //set their ID number starting at 0
            }
        }

        //remove wall at (1,1) W and (20,20) E -- (entrance/exit to maze)
        _maze.at(0).at(0).getWalls().W = false;
        _maze.at(x - 1).at(y - 1).getWalls().E = false;
    }



public:

    //default constructor -- executes buildMaze() function w/ appropriate parameters
    Maze(bool bigmaze = false) {
        srand((unsigned int) time(NULL));

        if(bigmaze) {
            buildMaze(100, 50, "bigmaze.svg");
        }
        else {
            buildMaze();
        }
    }
};





#endif