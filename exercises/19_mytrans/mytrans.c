// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 去除字符串首尾的空格、制表符、换行等空白字符
void trim(char *str) {
    if(!str || strlen(str) == 0) return;

    int end = strlen(str) - 1;
    while(end >= 0 && isspace((unsigned char)str[end])){
        str[end] = '\0';
        end--;
    }

    int start = 0;
    while(isspace((unsigned char)str[start])){
        start++;
    }

    if(start > 0){
        memmove(str, str + start, strlen(str + start) + 1);
    }
}

// 从词典文件中逐行读取单词及其翻译，并将键值对存入哈希表，同时统计词条总数
int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    trim(line);       // 去掉首尾空白，尤其是行尾的 \n

    if (strlen(line) == 0) {
      continue;       // 跳过空行
    }

    if (line[0] == '#') {
      // 这一行是单词："#code" → 提取 "code"
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      in_entry = 1;   // 标记：已经读到单词，正在等待翻译
    }
    else if (strncmp(line, "Trans:", 6) == 0) {
      // 这一行是翻译："Trans:n. 码..." → 提取 "n. 码..."
      strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
      current_translation[sizeof(current_translation) - 1] = '\0';

      if (in_entry && strlen(current_word) > 0) {
        // 单词和翻译都凑齐了，插入哈希表
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;     // 词条计数加一
        in_entry = 0;        // 重置标记
        current_word[0] = '\0';
        current_translation[0] = '\0';
      }
    }
  }

  fclose(file);
  return 0;
}
