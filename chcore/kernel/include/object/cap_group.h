#ifndef OBJECT_CAP_GROUP_H
#define OBJECT_CAP_GROUP_H

#include "common/list.h"
#include "common/lock.h"

struct object_slot {
  int slot_id;
  struct cap_group *cap_group;
  struct object *object;
  /* link copied slots pointing to the same object */
  struct list_head copies;
  cap_right_t rights;
};
struct slot_table {};

struct cap_group {
  struct slot_table slot_table;
  /* Proctect thread_list and thread_cnt */
  struct lock threads_lock;
  struct list_head thread_list;
  /* The number of threads */
  int thread_cnt;

  /*
   * Each process has a unique badge as a global identifier which
   * is set by the system server, procmgr.
   * Currently, badge is used as a client ID during IPC.
   */
  badge_t badge;
  int pid;

  /* Ensures the cap_group_exit function only be executed once */
  int notify_recycler;

  /* A ptrace object that the process attached to */
  void *attached_ptrace;

  /* Now is used for debugging */
  char cap_group_name[MAX_GROUP_NAME_LEN + 1];

  /* Each Process has its own futex status */
  struct lock futex_lock;
  struct htable futex_entries;
};

#define current_cap_group (current_thread->cap_group)

/*
 * ATTENTION: These interfaces are for capability internal use.
 * As a cap user, check object.h for interfaces for cap.
 */
int alloc_slot_id(struct cap_group *cap_group);

static inline void free_slot_id(struct cap_group *cap_group, cap_t slot_id) {
  struct slot_table *slot_table = &cap_group->slot_table;
  clear_bit(slot_id, slot_table->slots_bmp);
  clear_bit(slot_id / BITS_PER_LONG, slot_table->full_slots_bmp);
  slot_table->slots[slot_id] = NULL;
}

static inline struct object_slot *get_slot(struct cap_group *cap_group,
                                           cap_t slot_id) {
  if (slot_id < 0 || slot_id >= cap_group->slot_table.slots_size)
    return NULL;
  return cap_group->slot_table.slots[slot_id];
}

static inline void install_slot(struct cap_group *cap_group, cap_t slot_id,
                                struct object_slot *slot) {
  BUG_ON(!get_bit(slot_id, cap_group->slot_table.slots_bmp));
  cap_group->slot_table.slots[slot_id] = slot;
}

void *get_opaque(struct cap_group *cap_group, cap_t slot_id, bool type_valid,
                 int type, cap_right_t mask, cap_right_t rights);

int __cap_free(struct cap_group *cap_group, cap_t slot_id,
               bool slot_table_locked, bool copies_list_locked);

struct cap_group *create_root_cap_group(char *, size_t);

void cap_group_deinit(void *ptr);

/* Fixed badge for root process and servers */
#define ROOT_CAP_GROUP_BADGE (1) /* INIT */
#define PROCMGR_BADGE ROOT_CAP_GROUP_BADGE
#define FSM_BADGE (2)
#define LWIP_BADGE (3)
#define TMPFS_BADGE (4)
#define SERVER_BADGE_START (5)
#define DRIVER_BADGE_START (100)
#define APP_BADGE_START (200)

/**
 * Fixed pcid for root process (PROCMGR_PCID) and servers,
 * which is exacly the same to the definition in proc.h.
 */
#define ROOT_PROCESS_PCID (1)
#define FSM_PCID (2)
#define LWIP_PCID (3)
#define TMPFS_PCID (4)

/* Syscalls */
cap_t sys_create_cap_group(unsigned long cap_group_args_p);

#endif /* OBJECT_CAP_GROUP_H */
