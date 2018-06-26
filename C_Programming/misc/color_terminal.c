/*
 * This is a tutorial more than an example to show how to change the 
 * terminal colors(foreground and background).
 */

/*
 * @escape	\033 or \e or \x1b
 * @example	"\033[<attr;color>m"
 * @reset	"\033[0m" It is recomended to use at the end
 * @link	"http://misc.flogisoft.com/bash/tip_colors_and_formatting"
 */

/*
 * Attribute
 *
 * 1	Bold/Bright
 * 2	Dim
 * 4	Underline
 * 5	Blink (Does not work with most of the terminal emulators
 *		works in the tty and XTerm)
 * 7	Reverse (invert the foreground and background colors)
 * 8	Hidden (usefull for passwords) 
 */

/*
 * Foreground Color
 *
 * 30	Black
 * 31	Red
 * 32	Green
 * 33	Yellow
 * 34	Blue
 * 35	Magenta
 * 36	Cyan
 * 37	Light Grey
 * 90	Dark Grey
 * 91	Light Red
 * 92	Light Green
 * 93	Light Yellow
 * 94	Light Blue
 * 95	Light Magenta
 * 96	Light Cyan
 * 97	White
 *
 */

/*
 * Background Color
 *
 * 40	Black
 * 41	Red
 * 42	Green
 * 43	Yellow
 * 44	Blue
 * 45	Magenta
 * 46	Cyan
 * 47	Light Grey
 * 100	Dark Grey
 * 101	Light Red
 * 102	Light Green
 * 103	Light Yellow
 * 104	Light Blue
 * 105	Light Magenta
 * 106	Light Cyan
 * 107	White
 *
 */

/*****************
#!/bin/bash

# This program is free software. It comes without any warranty.
# The shell script to demonstrate all 256 colors
# both foreground and background

	for fgbg in 38 48 ; do #Foreground/Background
	for color in {0..256} ; do #Colors
	#Display the color
	echo -en "\e[${fgbg};5;${color}m ${color}\t\e[0m"
	#Display 10 colors per lines
	if [ $((($color + 1) % 10)) == 0 ] ; then
	echo #New line
	fi
	done
	echo #New line
	done
	exit 0

****************/
/*
 * One line execution
 * echo -e "\033[41mHello World \033[0m"
 * Here "[41m" you can add any combination you want separating with colon(;)
 * Ex: echo -e "\033[1;41;97mHello World \033[0m"
 * "[1;41;97m" 1-Bold/Bright, 41-Red Background, 97-Foreground White, \033[0m Reset to default
 */

#include <stdio.h>

#define		BLACK		"\033[0;30m"
#define 	RED		"\033[0;31m"
#define 	GREEN		"\033[0;32m"
#define 	YELLOW		"\033[0;33m"
#define 	BLUE		"\033[0;34m"
#define 	MAGENTA		"\033[0;35m"
#define 	CYAN		"\033[0;36m"
#define 	GREY		"\033[0;37m"
#define 	RESET		"\033[0m"

int main()
{
	printf("%sThis is Black\n", BLACK);
	printf("%sThis is Red\n", RED);
	printf("%sThis is Green\n", GREEN);
	printf("%sThis is Yellow\n", YELLOW);
	printf("%sThis is Blue\n", BLUE);
	printf("%sThis is Magenta\n", MAGENTA);
	printf("%sThis is Cyan\n", CYAN);
	printf("%sThis is Reset to default\n", RESET);
	return 0;
}
