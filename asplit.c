#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylen.h"

#define LINEM 1024+1

#define OFLOW(STR) (strlen(STR) == ARRAYLEN(STR)-1 && STR[ARRAYLEN(STR)-1] != '\n')

void
usage(char *name){
	printf("Usage: %s [STRING] [SELECTION]\n", name);
	printf("\
    Splits ASCII lines from STDIN by STRING and outputs the span of text \n\
    between the SELECTION-1th and SELECTIONth occurrence of STRING in each \n\
    line of text. If there is no specified SELECTION, outputs the amount of\n\
    times STRING occurs in each line of text.\n\
");
	return;
}

int
main(int argc, char *argv[]){
	FILE *in;
	size_t ls = LINEM;
	char *line = (char *)calloc(ls, sizeof(char));
	int li = 0; /* line numbers start at 1 */
	size_t lp;
	char pc;
	size_t sp;
	int occurrences = 0;
	size_t offset = 0;
	FILE *out;
	int overflow = 0;

	if(argc < 2){
		usage(argv[0]);
		exit(0);
	}

	in = stdin;
	out = stdout;

	while(fgets(line + offset, ls, in)){
		if(OFLOW(line)){
			offset += ls - 1;
			ls += ARRAYLEN(line);
			if(realloc(line, ls) == NULL){
				fprintf(stderr, "%s: Couldn't re-allocate memory (%d bytes)\n", argv[0], ls*sizeof(char));
				exit(1);
			}
			continue;
		}
		if(offset > 0)
			offset = 0;
		++li;
		pc = 0;
		occurrences = 0;
		for(lp = 0; lp < strlen(line); lp++){
			/* checks to see if the string at the point == argv[1]
			 * if (sp == strlen(argv[1])) after the loop, it does */
			for(sp = 0; line[lp+sp] == *(argv[1]+sp) && line[lp+sp] && *(argv[1]+sp); sp++);
			if(sp == strlen(argv[1])){
				++occurrences;
				lp += sp - 1;
			}else if(argc > 2 && occurrences == atoi(argv[2])){
				pc = line[lp];
				fprintf(out, "%c", pc);
			}
		}
		if(argc < 3)
			fprintf(out, "%d\n", occurrences);
		else if(pc != '\n')
			fprintf(out, "\n");
	}

	if(in != stdin)
		fclose(in);
	return 0;
}
