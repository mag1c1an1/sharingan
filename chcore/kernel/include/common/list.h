#ifndef COMMON_LIST_H
#define COMMON_LIST_H
struct list_head {
  struct list_head *prev;
  struct list_head *next;
};
#endif