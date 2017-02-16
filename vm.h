#ifndef VM_H_C4OZU8CQ
#define VM_H_C4OZU8CQ

#include "datatypes.h"

/* Exit from the VM normally */
#define gst_exit(vm, r) ((vm)->ret = (r), longjmp((vm)->jump, 1))

/* Bail from the VM with an error. */
#define gst_error(vm, e) ((vm)->error = (e), longjmp((vm)->jump, 2))

/* Crash. Not catchable, unlike error. */
#define gst_crash(vm, e) ((vm)->error = (e), longjmp((vm)->jump, 3))

/* Error if the condition is false */
#define gst_assert(vm, cond, e) do \
    { if (!(cond)) { gst_error((vm), (e)); } } while (0)

/* Type assertion */
#define gst_assert_type(vm, f, t) \
    gst_assert((vm), (f).type == (t), "Expected a different type.")

/* Initialize the VM */
void gst_init(Gst * vm);

/* Deinitialize the VM */
void gst_deinit(Gst * vm);

/* Load a function to be run on the VM */
void gst_load(Gst * vm, GstValue func);

/* Start running the VM */
int gst_start(Gst * vm);

/* Run garbage collection */
void gst_collect(Gst * vm);

/* Collect garbage if enough memory has been allocated since
 * the previous collection */
void gst_maybe_collect(Gst * vm);

/* Allocate memory */
void * gst_alloc(Gst * vm, uint32_t amount);

/* Allocate zeroed memory */
void * gst_zalloc(Gst * vm, uint32_t amount);

/* Get an argument from the stack */
GstValue gst_arg(Gst * vm, uint16_t index);

/* Put a value on the stack */
void gst_set_arg(Gst * vm, uint16_t index, GstValue x);

/* Get the number of arguments on the stack */
uint16_t gst_count_args(Gst * vm);

#endif /* end of include guard: VM_H_C4OZU8CQ */
