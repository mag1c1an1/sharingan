
#include "common/list.h"
struct thread {
  struct list_head node;
  struct list_head ready_queue_node;
};