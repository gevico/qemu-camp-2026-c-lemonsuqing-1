// main.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// 将字符串中的每个英文字符转换为小写形式
void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

// 程序入口：创建哈希表、加载词典、读取文本并逐词查询翻译结果后输出
int main() {
  // 步骤1：创建一个空的哈希表，用于存储词典中的单词和翻译
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");

  // 步骤2：从 dict.txt 加载词典到哈希表中
  // dict_count 用于记录成功加载了多少个词条
  uint64_t dict_count = 0;
  if (load_dictionary("dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  // 步骤3：打开待翻译的文本文件 text.txt
  FILE* file = fopen("text.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  // 步骤4：逐行读取文本内容
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    // 跳过空行，不做处理
    if (strlen(line) == 0) {
        continue;
    }

    char *token;
    token = strtok(line, " ");

    while(token != NULL){
      // 1. 转小写
      to_lowercase(token);

      const char *translation = hash_table_lookup(table, token);

      if (translation != NULL) {
        printf("原文: %s\t翻译: %s\n", token, translation);
      } else {
        printf("原文: %s\t未找到该单词的翻译。\n", token);
      }

      token = strtok(NULL, " ");

    }

  }

  fclose(file);
  free_hash_table(table);
  return 0;
}
