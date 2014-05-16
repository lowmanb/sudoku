#include <FL/Fl_Text_Display.H>
#include <Fl/FL_Widget.H>
#include <Fl/FL_Window.H>
#include <Fl/FL_Box.H>
#include <vector>
#include <string>

using namespace std;

class outWindow : public Fl_Window {

	public:
		
		outWindow(string encoding, int dim, double time);

	private:
		static vector< vector <Fl_Box *> > out;

};
