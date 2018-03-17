#include <stdlib.h>
#include <string.h>
#include <gbpLib.h>
#include <gbpDomain.h>

void set_exchange_ring_ranks(int *rank_to, int *rank_from, int i_rank) {
    if(i_rank != 0) {
        // Set the rank we will send to
        (*rank_to) = SID.My_rank - i_rank;
        if((*rank_to) < 0)
            (*rank_to) += SID.n_proc;
        else if((*rank_to) >= SID.n_proc)
            (*rank_to) -= SID.n_proc;

        // Set the rank we will receive from
        (*rank_from) = SID.My_rank + i_rank;
        if((*rank_from) < 0)
            (*rank_from) += SID.n_proc;
        else if((*rank_from) >= SID.n_proc)
            (*rank_from) -= SID.n_proc;
    } else {
        (*rank_to)   = SID.My_rank;
        (*rank_from) = SID.My_rank;
    }
}
