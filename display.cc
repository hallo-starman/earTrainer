#include <iostream>
using namespace std;
#include <gtkmm.h>
#include <gst/gst.h>

class Display : public Gtk::Window
{
	public:
		Display();
		Gtk::Button play;
		Gtk::Button reset;
		Gtk::Grid trainerGrid;
		Gtk::Entry guess;
		Gtk::Label myLabel;

};

Display::Display()
{
	set_default_size(200, 200);
	set_title("EarTrainer");

	myLabel.set_text("Total Correct: ");
	play.add_label("Play");
	reset.add_label("Reset");
	guess.set_max_length(10);
	add(trainerGrid);
	trainerGrid.set_border_width(55);
	trainerGrid.add(play);
	trainerGrid.add(reset);
	trainerGrid.attach_next_to(guess, play, Gtk::POS_BOTTOM, 2, 1);
	trainerGrid.attach_next_to(myLabel, guess, Gtk::POS_BOTTOM, 2, 6);	
	trainerGrid.set_row_spacing(10);

	//trainerGrid.show_all();
	show_all_children();


}

void on_button_clicked()
{
	cout << "You clicked Play!" << endl;	
}

int main(int argc, char *argv[])
{

	Gtk::Main kit(argc, argv);
	Display window;

	Gtk::Main::run(window);
	window.play.signal_clicked().connect(sigc::ptr_fun(&on_button_clicked));
}
