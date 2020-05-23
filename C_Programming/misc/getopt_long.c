/*
 * getopt_long.c
 *
 * Description: Program to illustrate the getopt_long() function in C
 *              For more details, please see `man 3 getopt`
 *
 *  Created on: 23-May-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <stdio.h>   /* For printf() */
#include <getopt.h>  /* For getopt_long() */

/* Flag set by ‘--verbose’. */
static int verbose_flag;

/*
  struct option {
  	  const char *name;
  	  int         has_arg;
  	  int        *flag;
  	  int         val;
  };
 */
static struct option long_options[] = {
	/* These options set a flag. if verbose verbose_flag == 1, if brief verbose_flag == 0 */
	{"verbose", no_argument,       &verbose_flag, 1},
	{"brief",   no_argument,       &verbose_flag, 0},
	{"infile",  required_argument, NULL,          'i'},
	{"outfile", required_argument, NULL,          'o'},
	{"extra",   no_argument,       NULL,          'x'},
	{"help",    no_argument,       NULL,          'h'},
	/* End of array */
	{NULL, 0, NULL, 0}
};

void help()
{
	printf("\nOptions:\n");
	printf("  -h, --help          Show this menu\n");
	printf("  -i, --infile=arg    input file\n");
	printf("  -o, --outfile=arg   output file\n");
	printf("  -x, --extra         some extra option\n");
	printf("\n");
}

int main(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long(argc, argv, "i:o:xh", long_options, NULL)) != -1) {
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

	/* Instead of reporting ‘--verbose’ and ‘--brief’ as they are encountered, we report the final status resulting from them. */
	if(verbose_flag)
		printf("Verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if(optind < argc) {
		printf("Unknown option ARGV-elements: ");
		while(optind < argc)
			printf("%s \n", argv[optind++]);
	}

	return 0;
}

