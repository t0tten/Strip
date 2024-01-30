#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

using namespace std;

bool match(string& filename, string& strip);

int main (int argc, char** argv)
{

	string filename_str 	= "";
	string strip_str 	= "";

	switch (argc)
	{
		case 2:
			getline(cin, filename_str);
			strip_str 	= argv[1];
			break;
		case 3:
			filename_str 	= argv[1];
			strip_str 	= argv[2];
			break;
		default:
			cout << "Usage: strp [filename] <strip>" << endl;
			return 1;
	}

	struct stat buf;
	if (stat (filename_str.c_str(), &buf) != 0)
	{
		cout << "Error: File does not exists" << endl;
		return 2;
	}

	if (!match(filename_str, strip_str))
	{
		cout << "Error: Filename does not ends with \"" << strip_str << "\"" << endl;
		return 3;
	}

	int endIndex = filename_str.length() - strip_str.length();
	string newFilename_str = filename_str.substr(0, endIndex);
	if (stat (newFilename_str.c_str(), &buf) == 0)
	{
		cout << "Error: A file with that name already exists" << endl;
		return 4;
	}
	
	ofstream(filename_str).put('a');
	rename(filename_str.c_str(), newFilename_str.c_str());

	return 0;
}

bool match(string& filename, string& strip)
{
	bool isMatch = false;
	if (strip.length() < filename.length())
	{
		int offset = filename.length() - strip.length();
		isMatch = true;
		for (int i = strip.length(); i > 0 && isMatch; i--)
		{
			if (strip[i] != filename[offset + i])
			{
				isMatch = false;
			}
		}
	}
	return isMatch;
}
