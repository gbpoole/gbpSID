#ifndef GBPSID_TOOLS_H
#define GBPSID_TOOLS_H

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void set_exchange_ring_ranks(int *rank_to, int *rank_from, int i_rank);
void exchange_ring_buffer(void *send_buffer, size_t buffer_type_size, size_t send_count, void *receive_buffer, size_t *receive_count, int i_rank);

#ifdef __cplusplus
}
#endif

#endif
