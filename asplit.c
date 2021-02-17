#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEM 1024

/* returns bool, if true the line var is shorter than the actual input */
#define OFLOW(line) ((strlen(line) == LINEM-1) && (line[LINEM-1] != '\n'))

/* asplit written by deven blake 2021; licensed under the public domain
 * where applicable and the UNLICENSE where not applicable */

void
usage(char *argv0) {
	printf("Usage: %s [STRING] [SELECTION]\n", argv0);
	printf("\
    Splits ASCII lines from STDIN by STRING and outputs the span of text \n\
    between the SELECTION-1th and SELECTIONth occurrence of STRING in each \n\
    line of text. If there is no specified SELECTION, outputs the amount of\n\
    times STRING occurs in each line of text.\n\
");
}

int
main(int argc, char *argv[]) {
	FILE *in;
	char line[LINEM];
	int lineindex = 0; /* line numbers start at 1 */
	int lp;
	char pc;
	int sp;
	int occurrences = 0;
	FILE *out;
	int overflow = 0;

	if(argc < 2) { usage(argv[0]); return 0; }

	in = stdin;
	out = stdout;

	while(fgets(line, LINEM, in)) {
		if(overflow && OFLOW(line) == 0) {
			overflow = 0;
			continue;
		} else if(overflow)
			continue;
		++lineindex;
		pc = 0;
		overflow = OFLOW(line);
		if(overflow)
			fprintf(
				stderr,
				"%s:%s:%d: Maximum line length possibly exceeded\n",
				argv[0], "<stdin>", lineindex
			);
		occurrences = 0;
		for(lp = 0; lp < strlen(line); lp++) {
			/* checks to see if the string at the point == argv[1]
			 * if (sp == strlen(argv[1])) after the loop, it does */
			for(sp = 0; (line[lp+sp] == *(argv[1]+sp)) && (line[lp+sp] != '\0') && (*(argv[1]+sp) != '\0'); sp++);
			if(sp == strlen(argv[1])) {
				occurrences += 1;
				lp += sp - 1;
			} else if(argc > 2 && occurrences == atoi(argv[2])) {
				pc = line[lp];
				fprintf(out, "%c", pc);
			}
		}
		if(argc < 3) fprintf(out, "%d\n", occurrences);
		else if(pc != '\n') fprintf(out, "\n");
	}

	if(in != stdin) fclose(in);
	return 0;
}
