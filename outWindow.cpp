#include "outWindow.h"
#include <iostream>
#include <sstream>

#define BSIZE 30 

vector< vector <Fl_Box *> > outWindow::out;

outWindow::outWindow(string encoding, int dim, double time) : 

	Fl_Window(dim*dim*BSIZE+10+(dim-1)*5, dim*dim*BSIZE+50+10+(dim-1)*5, "Solution"){

	out.resize(dim*dim);
	
	for(int i = 0; i < dim*dim; i++)
			out.at(i).resize(100);
		

	string buff;
	stringstream ssbuf(encoding);
	vector<string> words;

	while (ssbuf >> buff)
		words.push_back(buff);

	this->begin();
	int x_offset = 5;
		int y_offset = 5;

		for(int i = 0; i < dim*dim; i++){

			if(i%dim == 0 && i != 0 && i != dim*dim)
				x_offset += 5;
	
			y_offset = 5;
			
			for(int j = 0; j < dim*dim; j++){

				if(j%dim == 0 && j != 0 && j != dim*dim)
					y_offset += 5;

				out[i][j] = new Fl_Box(x_offset+i*BSIZE, y_offset+j*BSIZE, BSIZE, BSIZE);
				const char * currChar = words[i*dim*dim+j].c_str();
				out[i][j]->copy_label(currChar);
				out[i][j]->box(FL_FLAT_BOX);
				out[i][j]->labelsize(20);
				out[i][j]->color(255);

			}
		}

	string s_time = "Solved in\n" + to_string(time*1000) +" ms ";
	Fl_Box * timeBox = new Fl_Box( (dim*dim*BSIZE+10+(dim-1)*5)/2 - 50,
			dim*dim*BSIZE+5*(dim-1) + 30, 100,10);
			timeBox->copy_label(s_time.c_str());

	this->end();
	this->show();

}
