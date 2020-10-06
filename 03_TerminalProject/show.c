#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <string.h>

#define DX 3

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please, pass some text file as program argument\n");
        return 1;
    }

    struct stat file_stats;
    stat(argv[1], &file_stats);

    char* buf = calloc(file_stats.st_size + 1, sizeof(*buf));
    int fd = open(argv[1], O_RDONLY);
    read(fd, buf, file_stats.st_size);

    initscr();
    noecho();
    cbreak();
    printw("Opened file: %s\n", argv[1]);
    refresh(); 

    WINDOW *win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);

    int c = 0;
    char* cur = buf;
    char* next_line = cur;
    do {
        switch(c) {
            case KEY_DOWN:
                next_line = strchr(cur, '\n');
                if (next_line && next_line + 2 < buf + file_stats.st_size) {
                    cur = next_line + 1;
                }
                break;
            case KEY_UP:
                if (cur > buf) {
                    char tmp = *(cur - 1);
                    *(cur - 1) = 0;
                    next_line = strrchr(buf, '\n');
                    *(cur - 1) = tmp;
                    if (next_line) {
                        cur = next_line + 1;
                    } else {
                        cur = buf;
                    }
                }
                break;
        }

        werase(win);
        mvwprintw(win, 0, 0, "%s", cur);
        wrefresh(win);
    } while((c = wgetch(win)) != 27);

    endwin();
    free(buf);
    return 0;
}

