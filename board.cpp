#include <vector>
#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <math.h>
#include "board.h"
#include "timer.h"

using namespace std;

int contains( vector<bool> v, int digit){
	return v[digit-1];
}

int getVal(vector<bool> v){
	
	for(int i = 0; i < (int)v.size(); i++)
		if(v[i] == true)
			return i+1;
	
	return -1;
}

int getTrue(vector<bool> b){
	
	int ret = 0;
	for(int i = 0; i < (int)b.size(); i++)
		if(b[i] == true)
			ret++;
	
	return ret;
}

bool board::is_solved(){

	bool ret = true;
	for(int i = 0; i < boardLen; i++)
		for(int j = 0; j < boardLen; j++)
			if( getTrue(values[i][j]) != 1)
				ret = false;
	
	return ret;
}

board::coord board::getLeast(vector<vector<vector<bool> > > values){

	int minVal  = boardLen;
	coord minCoord;
	
	for(int i = 0; i < boardLen; i++){
		for(int j = 0; j < boardLen; j++){
			int currVal = getTrue(values[i][j]);
			if(currVal > 1 && currVal < minVal){
				minVal = currVal;
				minCoord.x = i;
				minCoord.y = j;
			}
		}
	}

	return minCoord;

}

board::board(string puzzle, int dim){


	string buff;
	stringstream ssbuf(puzzle);

	while (ssbuf >> buff){
		this->puzzle.push_back(buff);
	}


	boardLen = dim*dim;
	boxLen = dim;
	peerSize = 3*boardLen - 2*boxLen-1;

	//initializing all vectors
	peers.resize(boardLen);
	values.resize(boardLen);
	units.resize(boardLen);

	for(int i = 0; i < boardLen; i++){
		peers[i].resize(boardLen);
		values[i].resize(boardLen);
		units[i].resize(boardLen);
	}

	//settting the peers and values for each coordinate i,j
	for(int i = 0; i < boardLen; i++){	
		for(int j = 0; j < boardLen; j++){
			
			values[i][j].resize(boardLen);
			units[i][j].resize(3);
			
			vector<coord> * currPeers = &peers[i][j];	
			vector< vector<coord> > * currUnits = &units[i][j];	


			//getting row
			for(int k = 0; k < boardLen; k++){
				coord tmp;
				tmp.x = k;
				tmp.y = j;
				(*currUnits)[0].push_back(tmp);
				if(k != i)
					currPeers->push_back(tmp);
			}
			
			//getting column
			for(int k = 0; k < boardLen; k++){
				coord tmp;
				tmp.x = i;
				tmp.y = k;
				(*currUnits)[1].push_back(tmp);
				if(k != j)
					currPeers->push_back(tmp);
			}

			//getting box
			int box_x = (int)(i/boxLen);
			int box_y = (int)(j/boxLen);

			for(int k = 0; k < boxLen; k++){
				for(int m = 0; m < boxLen; m++){
					
					int abs_x = box_x*boxLen + k;
					int abs_y = box_y*boxLen + m;

					coord tmp;
					tmp.x=abs_x;
					tmp.y=abs_y;
					(*currUnits)[2].push_back(tmp);

					if(i != abs_x && j != abs_y)
						currPeers->push_back(tmp);
				}
			}

			//initializing all values to true
			for(int k = 0; k < boardLen; k++)
				values[i][j][k] = true;

		}
	}

}

bool board::init(){


//loop through puzze and assign values
	for(int i = 0; i < boardLen; i++){
		for(int j = 0; j < boardLen; j++){
			coord tmp;
			tmp.x = i;
			tmp.y = j;
			string currNum = puzzle[i*boardLen+j].c_str();
			if( isdigit(currNum[0]) && currNum != "0"){
				if(!assign(tmp, stoi(currNum)))
					return false;
			}
		}
	}

	return true;
}

string board::solve(){ 

	if(!search())
		cout << "No Solution Found." << endl;
	
	string solved = "";	
	for(int i = 0; i < boardLen; i++){
		for(int j = 0; j < boardLen; j++){
			solved += to_string( getVal( values[i][j] ) ) + " ";
		}
	}
			
	return solved;

}


//backtrack
bool board::search(){


	if( is_solved() )
		return true;

	vector<vector<vector<bool> > > valsCopy = values;
	coord min  = getLeast(values);

	for(int i = 0; i < boardLen; i++){
		if( assign(min, i+1) )
			if( search() )
				return true;
		
		values = valsCopy;

	}
			
	return false;
}
	

//assign -- calls eliminate
bool board::assign(coord c, int digit){

	for(int i = 0; i < (int)values[c.x][c.y].size(); i++){
		if(i != digit-1){
			if(!eliminate(c, i+1)){
				return false;
			}
		}
	}

	return true;

}

bool board::eliminate(coord c, int digit) {

	vector<bool> * currVals = &values[c.x][c.y];

	if (!contains(*currVals, digit)){
		return true;
	}

	(*currVals)[digit-1] = false;
	
	int n = getTrue( *currVals );

	if (n == 0)
		return false;
	else if (n == 1) {
		int v = getVal(*currVals);
		for (int i = 0; i < (int)peers[c.x][c.y].size(); i++){
				if (!eliminate(peers[c.x][c.y][i], v)){
						return false;
				}
		}
	}

	for (int i = 0; i < 3; i++) {

		vector<coord> * currUnit = &units[c.x][c.y][i];

		int n = 0;
		coord newAssign;
		newAssign.x = 0;
		newAssign.y = 0;

		coord * ptr = &newAssign;

		for (int j = 0; j < (int)currUnit->size(); j++) {
			int x = (*currUnit)[j].x;
			int y = (*currUnit)[j].y;
			coord tmp;
			tmp.x = x;
			tmp.y = y;
			if( contains(values[x][y], digit) ){
				n++; 
				ptr->x = tmp.x;
				ptr->y = tmp.y;
			}

		}

		if (n == 0)
			return false;
		
		else if (n == 1){
			if (!assign(*ptr, digit))
				return false;
		}
	}

	return true;
}

