//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    { "",         "sb-date",     30,    10 },
    { "",         "sb-idle",      0,    7  },
    { "",         "sb-volume",   10,    9  },
    { "",         "sb-battery",  30,    11 },
    { "",         "sb-internet",  1,    8  },
};



//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 4;
