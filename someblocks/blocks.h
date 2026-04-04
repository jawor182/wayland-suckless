//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    { "",         "sb-date",     10,    10 },
    { "",         "sb-battery",  30,    11 },
    { "",         "sb-volume",    1,    9  },
    { "",         "sb-internet",  1,    8  },

};



//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 4;
