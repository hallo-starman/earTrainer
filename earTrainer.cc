#include <vector>
#include <iostream> 
#include <string>
#include <dirent.h>
#include <cstdlib>
#include <algorithm>
using namespace std;

//#include <libglademm.h> 

// a chord has a location and a name
struct chord
{
	string file;	
	string name;
};

inline bool operator==(const chord& lhs, const chord& rhs)
{
	return lhs.name == rhs.name && lhs.file == rhs.file;
}

//chord current;

class earTrainer
{	
	public:
		struct chord current;
		int num;
		vector<chord> chords;
		// plays the chord for the user
		void playChord(chord curr);
		
	vector<chord> getChordList()
	{
		//first, get the name of each file in chord directory
		// and make that name the filename
		// chordSamples is the directory

		// pointer to directory
		DIR *dp;
		// pointer to dirent struct
		struct dirent *ent;
		// the name of directory containing chord files
		string dirName = "chordSamples";
		
		// open directory
		dp = opendir(dirName.c_str());
		if (dp != NULL)
		{
			// while there are files to read
			// print them out
			while((ent = readdir(dp)) != NULL)
			{
				char firstLetter = ent->d_name[0];

				if(firstLetter != '.')
				{
					// initialize a chord struct
					// set the filename
					struct chord thisChord;
					thisChord.file = ent->d_name;
					// now get the actual name of the chord
					// and that will be the chord name
					// slicing off 'cleanchord-' and '.aif'
					int pos = thisChord.file.find("-");
					thisChord.name = thisChord.file.substr(pos + 1);
					int pos2 = thisChord.name.find(".");
					thisChord.name = thisChord.name.substr(0, pos2);
					// add the whole chord to the list
					chords.push_back(thisChord);
				}
			}
			closedir(dp);
		}
		return chords;
	}

	chord getChord(vector<chord> &chords)
	{
		srand(time(0));
		int num = rand() % chords.size();
		//cout << num << endl;
		current = chords.at(num);
		return current;

	}

	bool isCorrect(string choice)
	{
		if(islower(choice[0]))
		{
			choice[0] = toupper(choice[0]);
		}

		if(choice == current.name)
			return true;
		return false;
		

	}

};


int main(int argc, char *argv[])
{

	// initialize a vector of chords
	vector<chord> chordList;
	// instantiate an object
	earTrainer start;
	// assign chords to list
	chordList = start.getChordList();
	// number of correct guesses
	int numCorrect = 0;

	for(int i = 0; i < chordList.size(); i++)
	{
		cout << chordList.at(i).name << endl;

	}
		cout << chordList.size() << endl;
	do
	{
		struct chord selected = start.getChord(chordList);
		cout << selected.name << endl;

		string guess;
		cin >> guess;
		if(start.isCorrect(guess))
		{
			// user has guessed correctly
			numCorrect++;
			cout << "you are correct" << endl;
			chordList.erase(find(chordList.begin(), chordList.end(), selected));
			for(int i = 0; i < chordList.size(); i++)
			{
				cout << chordList.at(i).name << endl;

			}
				cout << chordList.size() << endl;

		}
		else
			cout << "You're wrong " << endl;
	
	} while (chordList.size() > 0);


}
