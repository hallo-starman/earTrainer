#include <iostream>
using namespace std;
#include <gtkmm.h>
//#include <gst/gst.h>

#include "earTrainer.cc"

earTrainer trainer;
string numChords;

class Display : public Gtk::Window
{
	public:
		Display();
		Gtk::Button play;
		Gtk::Button reset;
		Gtk::Grid trainerGrid;
		Gtk::Entry guess;
		Gtk::Label myLabel;
		void on_entry_activate();
		void on_play_button_clicked();
		void on_reset_button_clicked();
		string labelText = "Total Correct: 0 / ";

	
};

// when the user presses enter, 
// the program checks the text entered
// and determines if it matches the chord that was played
void Display::on_entry_activate()
{
	if(trainer.chords.size() > 0 && trainer.isCorrect(guess.get_text()))
	{	
		trainer.numCorrect++;	
		labelText = "Total Correct: ";
		labelText.append(to_string(trainer.numCorrect));
		labelText.append(" / ");
		labelText.append(numChords);
		myLabel.set_text(labelText);
		trainer.chords.erase(find(trainer.chords.begin(), trainer.chords.end(), trainer.current)); 
		trainer.getChord(trainer.chords);
	}
	guess.set_text("");
}

// when the user hits play, the chord sounds out
void Display::on_play_button_clicked()
{
	trainer.playChord(trainer.getCurrentPath());
	cout << trainer.getCurrentPath() << endl;
}

// the user can reset the list and start over with their training
void Display::on_reset_button_clicked()
{
	string labelText = "Total Correct: 0 / ";
	labelText.append(numChords);
	myLabel.set_text(labelText);
	trainer.eraseChords();
	trainer.run();
}


Display::Display()
{

	set_default_size(200, 200);
	set_title("EarTrainer");
	numChords = to_string(trainer.totalChords);
	labelText.append(numChords);
	myLabel.set_text(labelText);
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
	
	play.signal_clicked().connect(sigc::mem_fun(*this, &Display::on_play_button_clicked));
	guess.signal_activate().connect(sigc::mem_fun(*this, &Display::on_entry_activate));
	reset.signal_clicked().connect(sigc::mem_fun(*this, &Display::on_reset_button_clicked));

	show_all_children();
	trainer.run();

}


int main(int argc, char *argv[])
{

	Gtk::Main kit(argc, argv);
	gst_init(&argc, &argv);
	Display window;

	Gtk::Main::run(window);
}
