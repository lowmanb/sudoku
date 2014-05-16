#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Simple_Counter.H>
#include <FL/Fl_Widget.H>

class startWindow  : public Fl_Window {

	
	public:

		startWindow();
	
	private:

		static void manual_cb(Fl_Widget *w, void* data);
		static void file_cb(Fl_Widget *w, void* data);
		static void quit_cb(Fl_Widget *w, void* data);
		static Fl_Button * but1;
		static Fl_Button * but2;
		static Fl_Simple_Counter * val;

};
