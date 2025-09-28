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

enum object_type {
  TYPE_NO_TYPE = 0,
  TYPE_CAP_GROUP,
  TYPE_THREAD,
  TYPE_CONNECTION,
  TYPE_NOTIFICATION,
  TYPE_IRQ,
  TYPE_PMO,
  TYPE_VMSPACE,
#ifdef CHCORE_OPENTRUSTEE
  TYPE_CHANNEL,
  TYPE_MSG_HDL,
#endif /* CHCORE_OPENTRUSTEE */
  TYPE_PTRACE,
  TYPE_NR,
};

#endif