// compile with `pkg-config --cflags --libs gstreamer-1.0`
#include <gst/gst.h>
#include <cstring>
#include <iostream>
using namespace std;

class soundPlayer
{
	GstElement *pipeline;
	
	void playChord(string path)
	{
		const char* partPath = "playbin uri=file:///home/shelby/Documents/projects/chordSamples/";
		char resultPath[150];
		strcpy(resultPath, partPath);
		strcat(resultPath, path.c_str());
		// gst_parse_launch takes a const char* in first parameter
		// c_str() results in a const char* 
		// strcpy and strcat are used to concatenate the two 'strings'
		pipeline = gst_parse_launch(resultPath, NULL);	
		gst_element_set_state(pipeline, GST_STATE_PLAYING);
	}
};

int main(int argc, char *argv[])
{
	gst_init(&argc, &argv);

}
