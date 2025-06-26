#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H

#include "common/list.h"
#include "common/lock.h"
#include "common/types.h"

struct object {
  u64 type;
  u64 size;
  struct list_head copies_head;
  struct lock copies_lock;
  volatile unsigned long refcount;
  /*
   * opaque marks the end of this struct and the real object will be
   * stored here. Now its address will be 8-byte aligned.
   */
  u64 opaque[];
};

#endif