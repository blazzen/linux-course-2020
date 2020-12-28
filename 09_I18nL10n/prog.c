#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(void) {
    setlocale (LC_ALL, "");
	bindtextdomain ("prog", LOCALE_PATH);
	textdomain("prog");

    printf(_("Please, think of a number from 1 to 100\n"));

    unsigned char min = 1;
    unsigned char max = 100;
    do {
        unsigned char half = (min + max) / 2;
        printf(_("Is your number greater than %hhu? (y - yes, n - no)\n"), half);
        
        char ans[16] = { 0 };
        while (strcmp(ans, _("y")) && strcmp(ans, _("n"))) {
            scanf("%s", ans);
        }

        if (!strcmp(ans, _("y"))) {
            min = half + 1;
        } else {
            max = half;
        }
    } while (min != max);

    printf(_("Your number is %hhu\n"), max);

    return 0;
}

