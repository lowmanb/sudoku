#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <string>
#include <iostream>
#include <fstream>
#include "startWindow.h"
#include "board.h"
#include <math.h>
#include "manInput.h"
#include "outWindow.h"
#include "timer.h"

using namespace std;

Fl_Button * startWindow::but1;
Fl_Button * startWindow::but2;
Fl_Simple_Counter * startWindow::val;

void startWindow::manual_cb(Fl_Widget *w, void* data){

	manInput m(val->value());
	Fl::run();
	return;
}

void startWindow::file_cb(Fl_Widget *w, void* data){

	fl_file_chooser_ok_label("Solve!");	
	char * path = fl_file_chooser("Choose Input File", "*.dat", "", 0);
	

	if(path == NULL)
		return;
	
	string encoding = ""; 
	fstream fin(path, fstream::in);
	string word;

	int validCount = 0;
	while (fin >> word){
		validCount++;	
		encoding += word + " ";
	}

	if(validCount != pow(stoi(to_string(val->value())), 4)){
		fl_message("The file dimension does not match the given dimension.\n\nEither the wrong dimension was given, or the file is not a valid sudoku puzzle.");
		return;	
	}
	
	//cout << encoding << endl;
	int dim  = stoi(to_string(val->value()));
	board b(encoding, dim);

	if(!b.init()){
		fl_message("It seems that this puzzle is not valid!");
		return;
	}
		
	timer t;
	t.start();
	string solution = b.solve();
	t.stop();
	outWindow o(solution, stoi(to_string(val->value())), t.getTime());

	Fl::run();

	return;
}

void startWindow::quit_cb(Fl_Widget *w, void* data){ exit(2); }

startWindow::startWindow() : Fl_Window(250, 250, "Sudoku Solver") {

	this->begin();
	
		val = new Fl_Simple_Counter(50, 30, 150, 30, "Size of Inner Squares");
			val->step(1);
			val->range(2, 6);
			val->value(3);

		but1 = new Fl_Button(50, 110, 150, 30, "Manual Editor");
			but1->callback(manual_cb);
	
		but2 = new Fl_Button(50, 180, 150, 30, "Choose File");
			but2->callback(file_cb);

	this->end();
	this->callback(quit_cb);
	this->show();

}
