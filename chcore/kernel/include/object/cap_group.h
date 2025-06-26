#ifndef OBJECT_CAP_GROUP_H
#define OBJECT_CAP_GROUP_H

#include "common/lock.h"

struct object_slot {};
struct slot_table {};

struct cap_group {
  struct slot_table slot_table;
  struct lock threads_lock;
  int thread_cnt;
  // .. others
};

#endif