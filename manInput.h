#include <Fl/Fl.H>
#include <FL/Fl_Int_Input.H>
#include <Fl/FL_Button.H>
#include <Fl/FL_Widget.H>
#include <Fl/FL_Window.H>
#include <vector>

using namespace std;

class manInput : public Fl_Window {

	public:

		manInput(int dim);

	private:
		
		static void button_cb(Fl_Widget *w, void* data);
		static void file_cb(Fl_Widget *w, void* data);
		static void input_cb(Fl_Widget *w, void* data);
		static vector< vector <Fl_Int_Input *> > input;
		static Fl_Button * but1;
		static Fl_Button * but2;
		static int dim;

};
