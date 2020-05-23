/*
 * getopt.c
 *
 * Description: Program to illustrate the getopt() function in C
 *
 *  Created on: 23-May-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <stdio.h>  /* For printf() */
#include <unistd.h> /* For getopt() */


void help(void)
{
	printf("Usage: ./getopt.out [-u] [-i inputfile] [-o outputfile]\n\n");
	printf("-h  show this help\n");
	printf("-i  input file\n");
	printf("-o  output file\n");
	printf("-x  extra option\n\n");
	printf("Please see `man 3 getopt` for more details\n\n");
}


int main(int argc, char *argv[])
{
	int opt;

	/*
	 * From `man 3 getopt`
	 *
	 * int getopt(int argc, char * const argv[], const char *optstring);
	 * extern char *optarg;
	 * extern int optind, opterr, optopt;
	 *
	 * optind - The index of the next element to be processed in argv, system initializes this value to  1
	 *
	 * If getopt() does not recognize an option character, it prints an error message to stderr,
	 * stores the character in optopt, and returns '?'.
	 * The calling program may prevent the error message by setting opterr to 0.
	 *
	 * If getopt() finds an option character in argv that was not included in optstring, or if it detects
	 * a missing option argument, it returns '?' and sets the external variable optopt to the actual
	 * option character.
	 *
	 * If the first character of optstring is a colon (':'), then getopt() returns ':' instead of '?' to
	 * indicate a  missing  option  argument.
	 *
	 * If  an  error  was detected, and the first character of optstring is not a colon and the external
	 * variable opterr is nonzero (which is the default), getopt() prints an error message.
	 *
	 * Here the optstring is "i:ou:"
	 * i - input file  - requires argument
	 * o - output file - requires argument
	 * u - user        - requires no argument
	 * h - help
	 */
	while((opt = getopt(argc, argv, "i:o:xh")) != -1) {
		switch(opt) {
		case 'i':
			printf("Option found: %c\n", opt);
			printf("Input file given is \"%s\"\n\n", optarg);
			break;
		case 'o':
			printf("Option found: %c\n", opt);
			printf("Output file given is \"%s\"\n\n", optarg);
			break;
		case 'x':
			printf("Option found: %c\n", opt);
			printf("Here we can do some useful work\n\n");
			break;
		case 'h':
			help();
			break;
		case ':':
			printf("Option needs an argument\n\n");
			break;
		case '?':
			printf("Unknown option given %c\n\n", optopt);
			break;
		default:
			printf("No option satisfied!!\n\n");
		}
	}

	/* optind is for the extra arguments which are not parsed */
	for(; optind < argc; optind++) {
		printf("Extra arguments: %s\n", argv[optind]);
	}

	return 0;
}

