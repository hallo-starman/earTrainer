// compile with `pkg-config --cflags --libs gstreamer-1.0`

#include <vector>
#include <gst/gst.h>
#include <cstring>
#include <iostream> 
#include <string>
#include <dirent.h>
#include <cstdlib>
#include <algorithm>
using namespace std;


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
		int numCorrect;
		struct chord selected;
		int totalChords = 14;

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

	// checks if guess matches the current chord
	bool isCorrect(string choice)
	{	
		// if user enters lowercase, this changes to uppercase
		if(islower(choice[0]))
		{
			choice[0] = toupper(choice[0]);
		}

		if(choice == current.name)
			return true;
		return false;
	}

	void eraseChords()
	{
		chords.erase(chords.begin(), chords.end());
	}

	string getCurrentPath()
	{
		return current.file;
	}

	// will initialize chord list
	void run()
	{
		vector<chord> chordList;		
		chordList = getChordList();
		selected = getChord(chordList);
		numCorrect = 0;
	}

	void playChord(string path)
	{
		GstElement *pipeline;
		const char* partPath = "playbin uri=file:///home/shelby/Documents/projects/chordSamples/";
		char resultPath[150];
		strcpy(resultPath, partPath);
		strcat(resultPath, path.c_str());
		// gst_parse_launch takes a const char* in first parameter
		// c_str() results in a const char*
		// strcpy and strcat are used to concatenate the two 'strings'
		pipeline = gst_parse_launch(resultPath, NULL);
		gst_element_set_state(pipeline, GST_STATE_PLAYING);
		cout << resultPath << endl;
	}

};


