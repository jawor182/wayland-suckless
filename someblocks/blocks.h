//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    { "",         "sb-mpd",       1,    3  },
    { "",         "sb-date",     10,    10 },
    { "",         "sb-volume",    1,    9 },
    { "",         "battery",     30,    11},
    { "",         "sb-internet",  5,    7},

};



//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;
