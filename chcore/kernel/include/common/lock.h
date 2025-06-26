#ifndef COMMON_LOCK_H
#define COMMON_LOCK_H

#include "common/types.h"

struct lock {
  volatile u64 slock;
};
#endif