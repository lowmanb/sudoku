#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class board{
	
	public:
		
		board(string puzzle, int dim);
		string solve();
		bool init();

	private:

		struct coord{
			int x;
			int y;
		};

		vector< vector< vector<coord> > > peers;
		vector< vector< vector<bool> > >  values;	
		vector< vector< vector< vector <coord> > > >  units;	

		bool assign(coord c, int digit);
		bool eliminate(coord c, int digit);
		bool search();

		coord getLeast(vector<vector<vector<bool> > > values);
		bool is_solved();
		int boardLen, boxLen, peerSize;
		vector<string> puzzle;

};
