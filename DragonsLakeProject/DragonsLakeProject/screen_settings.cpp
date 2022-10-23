#include "header.h"

void screen_settings(int* width, int* height, bool* fullscreen, int argc, const char* argv[]) {
	//running through all the arguments in search of -window and -screen (in case if someone will decide to add more arguments)
	for (int i = 1; i < argc; i++) {
		if (i == argc - 1) {
			break;
		}
		if (strcmp(argv[i], "-window") == 0) { //if arg is "-window"
			std::string sizeString;
			//running through the argument string to put chars into sizeString, when x is found set width to sizeString and rest of string (after x) is set to height
			while (*(argv[i + 1])) { 
				if (*(argv[i + 1]) == 'x' || *(argv[i + 1]) == 'X' ) {
					*(argv[i + 1])++;
					*width = atoi(sizeString.c_str());
					sizeString = "";
					continue;
				}
				sizeString += *(argv[i + 1]);
				*(argv[i + 1])++;
			}
			*height = atoi(sizeString.c_str());
		}
		if (strcmp(argv[i], "-screen") == 0) { //if arg is "-screen"
			if (!strcmp(argv[i + 1], "1")) {
				*fullscreen = true;
			}
		}
	}
}