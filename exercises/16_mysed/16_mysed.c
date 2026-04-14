#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }
    // char old[MAX_LINE_LENGTH], new[MAX_LINE_LENGTH];
    int i = 2;
    int start = i;
    while (cmd[i] != '/' && cmd[i] != '\0') i++;
    if (cmd[i] != '/') return -1;

    *old_str = malloc(i - start + 1);
    strncpy(*old_str, cmd + start, i - start);
    (*old_str)[i - start] = '\0';

    i++;  // 跳过 '/'
    start = i;
    
    // 找 new_str 的结束位置
    while (cmd[i] != '/' && cmd[i] != '\0') i++;
    if (cmd[i] != '/') return -1;
    
    *new_str = malloc(i - start + 1);
    strncpy(*new_str, cmd + start, i - start);
    (*new_str)[i - start] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char* pos = strstr(str, old);
    if (!pos) return;

    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    size_t tail_len = strlen(pos + old_len);

    memmove(pos + new_len, pos + old_len, tail_len + 1);

    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
