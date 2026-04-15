// hash_table.c
#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 将字符串映射为一个无符号长整型哈希值，用于确定键值对在哈希表中的存储位置
unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

// 创建一个空的哈希表，初始化所有桶指针为 NULL
HashTable *create_hash_table() {
  HashTable *table = malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

// 释放单个哈希节点及其内部存储的键和值字符串所占用的内存
void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

// 遍历并释放哈希表中所有节点以及哈希表结构本身所占用的内存
void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

// 将指定的键值对插入哈希表；若键已存在可更新或忽略，成功返回 1
int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      free(node->value);
      node->value = strdup(value);
      return 1;
    }
    node = node->next;
  }

  HashNode *new_node = malloc(sizeof(HashNode));
  new_node->key = strdup(key);
  new_node->value = strdup(value);
  new_node->next = table->buckets[hash];
  table->buckets[hash] = new_node;

  return 1;
}

// 在哈希表中根据键查找对应的值，找到则返回值的指针，否则返回 NULL
const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->value;
    }
    node = node->next;
  }

  return NULL; // 未找到
}
