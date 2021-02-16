#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEM 1024 // line max length

/*
 * asplit written by deven blake; to the extent possible this program
 * is licensed under the public domain where applicable and the
 * UNLICENSE where not applicable
 * 
 * plan9ports' and FreeBSD's cat implementations, util-linux's colrm,
 * and gnu's ls referenced heavily. especially colrm.
 * 
 * i find this utility to be of use, but my programming is not the
 * best. if you feel you can write this better, be my guest. i will
 * probably use your implementation :>
*/

void
usage(char *argv0) {
	printf("Usage: %s [STRING] [SELECTION]\n", argv0);
	printf("\
Splits ASCII lines from STDIN by STRING and outputs the span of text between\n\
the SELECTION-1th and SELECTIONth occurrence of STRING in each line of text.\n\
If there is no specified SELECTION, outputs the amount of times STRING\n\
occurs in each line of text.\n\
");
}

int
main(int argc, char *argv[]) {
	FILE *in;
	char line[LINEM];
	int lineindex = 0; // 1-indexed
	int lp; // points to a place in a Line
	char pc; // last-Printed character
	int sp; // points to a place in an arg String
	int occurrences = 0;
	FILE *out;

	if(argc < 2) { usage(argv[0]); return 0; }

	in = stdin; // could add [FILE] to the args but it doesn't seem useful
	out = stdout;

	while(fgets(line, LINEM, in)) {
		++lineindex;
		pc = 0;
		if((strlen(line) == LINEM-1) && (line[LINEM-1] != '\n'))
			fprintf(
				stderr,
				"%s:%s:%d: Maximum line length possibly exceeded\n",
				argv[0], "<stdin>", lineindex
			);
		occurrences = 0;
		for(lp = 0; lp < strlen(line); lp++) {
			for(sp = 0; (line[lp+sp] == *(argv[1]+sp)) && line[lp+sp] && *(argv[1]+sp); sp++);
			if(sp == strlen(argv[1])) {
				occurrences += 1;
				lp += sp - 1;
			} else if(argc > 2 && occurrences == atoi(argv[2])) {
				pc = line[lp];
				fprintf(out, "%c", line[lp]);
			}
		}
		if(argc < 3) fprintf(out, "%d\n", occurrences);
		else if(pc != '\n') fprintf(out, "\n");
	}

	if(in != stdin) fclose(in);
	return 0;
}
