#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#if WITHOUT_UTF == 0
    #define PCRE2_UCP_CUSTOM PCRE2_UCP
#else
    #define PCRE2_UCP_CUSTOM 0
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include <ncurses.h>
#include <locale.h>

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void match(char* inA, char* inB, WINDOW* winO)
{
    wprintw(winO, " PCRE2_UCP: %d\n", PCRE2_UCP_CUSTOM);
    wprintw(winO, " WITHOUT_UTF: %d\n", WITHOUT_UTF);
    wprintw(winO, " Entered: %s %s\n", inA, inB);
    pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR) inA;
    subject = (PCRE2_SPTR) inB;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP_CUSTOM, &errnum, &erroffs, NULL);

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        wprintw(winO, " PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        return;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            wprintw(winO, " No match\n");
            break;
        default:
            wprintw(winO, " Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return;
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++)
        wprintw(winO, " %2ld: %.*s\n", ovector[2*i], 
			     (int)(ovector[2*i+1] - ovector[2*i]),
			     subject + ovector[2*i]);

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */
}

void main() {
        setlocale(LC_ALL, "");

	WINDOW *winA, *winB, *winO;
	char inA[MAXSTR], inB[MAXSTR];
	int c = 0;
	int half;

	initscr();
	cbreak();
	printw("Input:");
	refresh();

	half = (COLS-2*DX)/2;
	winA = newwin(ONLELINE, half, DX, DX);
	winB = newwin(ONLELINE, half, DX, DX+half);
	winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
	keypad(winA, TRUE);
	keypad(winB, TRUE);
	scrollok (winO, TRUE);
	wmove(winO, 1, 0);
	do {
		werase(winA);
		werase(winB);

		box(winA, '|', '-');
		wrefresh(winA);
		box(winB, '|', '-');
		wrefresh(winB);
		box(winO, '|', '-');
		wrefresh(winO);

		mvwgetnstr(winA, 1, 1, inA, MAXSTR);
		mvwgetnstr(winB, 1, 1, inB, MAXSTR);
		match(inA, inB, winO);
                wprintw(winO, "\n");
                wrefresh(winO);
	} while(*inA);

	endwin();

}
