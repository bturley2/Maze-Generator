#ifndef DISJSETS_H
#define DISJSETS_H

#include <vector>
#include "tile.h"

using std::vector;
using std::cout;
using std::endl;

class DisjSets
{
private:
    vector<int> _sets;
    int _num_sets;

    //updates _num_sets to ensure the value is correct
    void updateNumSets() {
        int count = 0;
        for(int i = 0; i < _sets.size(); ++i) {
            if(_sets.at(i) == -1) {++count;}
        }
        
        _num_sets = count;
    }

public:

    DisjSets(int num_items) {
        this->_num_sets = num_items;
        this->_sets.resize(num_items);

        //set all values to -1 since initially all of them are their own set
        for(int i = 0; i < num_items; ++i) {
            _sets.at(i) = -1;
        }
    }

    //returns the number of sets 
    //(# of times -1 appears in the data structure)
    int getNumSets() {
        return _num_sets;
    }

    //returns the index/ID to which this set belongs
    int find(int id) {

        if (id > _sets.size() - 1 || id < 0) {   //check for out of bounds errors
            cout << "Invalid find() operation in DisjSets object. Out of bounds error called at index: " << id << endl;
            return -1;
        }

        int cur_index = id;

        while (_sets.at(cur_index) != -1) {
            cur_index = _sets.at(cur_index);
        }

        return cur_index;
    }

    //combines two sets together
    void unionSets(int id_1, int id_2) {
        //check for out of bounds errors
        if((id_1 > _sets.size() - 1) || (id_2 > _sets.size() - 1) || id_1 < 0 || id_2 < 0) {
            cout << "Out of bounds call made -- see DisjSets.h function unionSets()" << endl;
            return;
        }

        int master_1 = find(id_1), master_2 = find(id_2);   //store the parent to which each item points

        //set the right parent to point at the left parent
        _sets.at(master_2) = master_1;


        updateNumSets();
    }

};










#endif