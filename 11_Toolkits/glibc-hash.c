#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>

enum {
    INITIAL_COUNT = 1,
    STR_MAX_SIZE = 80
};

void f(gpointer key, gpointer value, gpointer str) {
    g_printf(str, key, GPOINTER_TO_INT(value));
}

int cmp(gconstpointer x,  gconstpointer y, gpointer data) {
    return GPOINTER_TO_INT(g_hash_table_lookup(data, *(gchar**) x)) - GPOINTER_TO_INT(g_hash_table_lookup(data, *(gchar**) y));
}


int main(void) {
    char text[STR_MAX_SIZE + 1] = { 0 };
    int c;
    int i = 0;

    while ((c = getchar()) != EOF) {
        text[i++] = c;
    }
    
    gchar** tokens = g_strsplit_set(text, ".,\n\r ", -1);
    GHashTable* counters = g_hash_table_new(g_str_hash, g_str_equal);

    for (gchar** iterator = tokens; *iterator; ++iterator) {
        gchar* prepared = g_strstrip(*iterator);
        if (!g_strcmp0(prepared, "")) {
            continue;
        }

        gpointer existing = g_hash_table_lookup(counters, prepared);
        if (!existing) {
            g_hash_table_insert(counters, prepared, GINT_TO_POINTER(INITIAL_COUNT));
        } else {
            g_hash_table_insert(counters, prepared, GINT_TO_POINTER(GPOINTER_TO_INT(existing) + 1));
        }
    }
    
    guint len;
    gchar** keys = (gchar**) g_hash_table_get_keys_as_array(counters, &len);
    GArray* keys_arr = g_array_new(FALSE, FALSE, sizeof(gchar*));
    for (gchar** iterator = keys; *iterator; ++iterator) {
        gchar* str = g_strdup(*iterator); // for below macro to work
        g_array_append_val(keys_arr, str);
    }
    g_array_sort_with_data(keys_arr, (GCompareDataFunc) cmp, counters);
    
    for (i = 0; i < keys_arr->len; ++i) {
        gchar* word = g_array_index(keys_arr, gchar*, i);
        g_printf("%s: %d\n", word, GPOINTER_TO_INT(g_hash_table_lookup(counters, word)));
    }

    g_strfreev(tokens);
    g_hash_table_destroy(counters);
    g_array_free(keys_arr, FALSE);
    return 0;
}

