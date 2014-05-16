#include <Fl/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <vector>
#include <string>
#include <fstream>
#include "board.h"
#include "manInput.h"
#include "outWindow.h"
#include "timer.h"

#define BSIZE 30 

using namespace std;

int manInput::dim;
Fl_Button * manInput::but1;
Fl_Button * manInput::but2;
vector< vector < Fl_Int_Input * > > manInput::input;

void manInput::input_cb(Fl_Widget *w, void* data){

	Fl_Int_Input * input = (Fl_Int_Input *)w;

	const char * val = input->value();

	if( (int)val[0] != 0 && (!isdigit((int)val[0]) || stoi(val) < 1))
		input->value(to_string(1).c_str());
	
	else if( (int)val[0] != 0 && (!isdigit((int)val[0]) || stoi(val) > dim*dim))
		input->value(to_string(dim*dim).c_str());

	input->redraw();

}

void manInput::button_cb(Fl_Widget *w, void* data){

	string encoding = "";
	int validCount = 0;
	for(int i = 0; i < (int)input.size(); i++){
		for(int j = 0; j < (int)input[i].size(); j++){
			const char * digit = input[i][j]->value();
			if( (int)digit[0] == 0){
				encoding += ". ";
			}
			else{
				encoding += string(digit)+" ";
				validCount++;
			}
		}

	}
	
	//cout << encoding << endl;

	if(validCount == 0){
		fl_message("You must enter at least one value!");
		return;
	}

	board b(encoding, dim);

	if(!b.init()){
		fl_message("It seems the puzzle is not valid!");
		return;
	}


	timer t;
	t.start();
	string solution = b.solve();
	t.stop();
	outWindow o(solution, dim, t.getTime());
	
	Fl::run();

	return;

}

void manInput::file_cb(Fl_Widget *w, void* data){

	fl_file_chooser_ok_label("Save");	
	const char *newfile = fl_file_chooser("Save File As?", "*", "filename.dat", 1);

	ofstream myfile;
	myfile.open (newfile);

	for(int i = 0; i < (int)input.size(); i++){
		for(int j = 0; j < (int)input.at(i).size(); j++){
			const char * digit = input[i][j]->value();
			if( (int)digit[0] == 0)
				myfile << ". ";
			else
				myfile << string(digit)+ " ";
		}

	}

	myfile.close();
	
}

manInput::manInput(int dim) :
	Fl_Window(dim*dim*BSIZE+10+(dim-1)*5, dim*dim*BSIZE+110+(dim-1)*5 , "Enter Values") {

	this->dim = dim;
	input.resize(dim*dim);

	for(int i = 0; i < dim*dim; i++)
		input.at(i).resize(dim*dim);

	this->begin();
		
		but1 = new Fl_Button( (dim*dim*BSIZE+10+(dim-1)*5)/2 - 30,
			dim*dim*BSIZE+5*(dim-1) + 17, 60, 30, "Solve!");	
		but1->callback(button_cb);

		but2 = new Fl_Button( (dim*dim*BSIZE+10+(dim-1)*5)/2 - 50,
			dim*dim*BSIZE+5*(dim-1) + 63, 100, 30, "Encode to File");	
		but2->callback(file_cb);

		int x_offset = 5;
		int y_offset = 5;

		for(int i = 0; i < dim*dim; i++){

			if(i%dim == 0 && i != 0 && i != dim*dim)
				x_offset += 5;
	
			y_offset = 5;
			
			for(int j = 0; j < dim*dim; j++){

				if(j%dim == 0 && j != 0 && j != dim*dim)
					y_offset += 5;

				input[i][j] = new Fl_Int_Input(x_offset+i*BSIZE, y_offset+j*BSIZE, BSIZE, BSIZE);
				input[i][j]->box(FL_FLAT_BOX);
				input[i][j]->textsize(20);
				input[i][j]->when(FL_WHEN_RELEASE);
				input[i][j]->callback(input_cb);
			}
		}

	this->end();

	this->show();

	return;	

}

