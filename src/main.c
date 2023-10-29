#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t cursor;
struct dirent* cursor_dirent;
char dir_name[1024] = "./";

bool renaming = false;
char new_name[1024];

int main(int argc, char *argv[]) {
    system("clear");
    while (1) {
        DIR* d = opendir(dir_name);
        if (!d) {
            fprintf(stderr, "Failed to open directory: \"%s\"", dir_name);
            return 1;
        }
        
        size_t index = 0;
        struct dirent* dir = NULL;
        while ((dir = readdir(d)) != NULL) {
            if (index == cursor) {
                printf("\033[47m\033[30m%s\033[0m\n", dir->d_name);
                cursor_dirent = dir;
            } else {
                printf("%s\n", dir->d_name);              
            }
            ++index;
        }
        
        system(renaming ? "/bin/stty cooked" : "/bin/stty raw");
        
        char c = getchar();
        if (renaming) {
            if (c == ':') {
                rename(cursor_dirent->d_name, new_name);
                renaming = false;
            } else {
                int len = strlen(new_name);
                assert((len+1) <= 1024);
                new_name[len] = c;
                new_name[len+1] = '\0';
            }
        } else {
            switch (c) {
                case '\033': {
                    getchar();
                    switch (getchar()) {
                        case 'A': {
                            if (cursor > 0) {
                                --cursor;
                            }
                        } break;
                        case 'B': {
                            if (cursor < index-1) {
                                ++cursor;
                            }
                        } break;
                    }
                } break;
                case 'q': {
                    system("/bin/stty cooked");
                    printf("Exit.");
                    return 0;
                }
                case 'r': {
                    renaming = true;
                } break;
                case 'd': {
                    if (cursor_dirent->d_type == DT_REG) {
                        remove(cursor_dirent->d_name);
                    }
                } break;
                case ':': {
                    if (cursor_dirent->d_type == DT_DIR) {
                        cursor = 0;
                        strcat(dir_name, cursor_dirent->d_name);
                        strcat(dir_name, "/");
                    }
                } break;
                case 'o': {
                    char str[2048];
                    sprintf(str, "nvim %s", cursor_dirent->d_name);
                    system(str);
                } break;
            }
        }
        closedir(d);
        system("/bin/stty cooked");
        system("clear");
    }

    system("/bin/stty cooked");
    return 0;
}
