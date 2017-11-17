#ifndef GBPSID_MPI_H
#define GBPSID_MPI_H

#if USE_MPI
#include <mpi.h>
#endif

// MPI
#if USE_MPI
#if USE_DOUBLE
#define MPI_MY_REAL MPI_DOUBLE
#else
#define MPI_MY_REAL MPI_FLOAT
#endif
#define MPI_SIZE_T MPI_LONG_LONG
#endif

#define SID_MASTER_RANK 0

#if USE_MPI
#define SID_MAXLENGTH_PROCESSOR_NAME MPI_MAX_PROCESSOR_NAME
#else
#define SID_MAXLENGTH_PROCESSOR_NAME 64
#endif

#if USE_MPI
#define SID_COMM_WORLD (SID.COMM_WORLD->comm)
#define SID_IN_PLACE MPI_IN_PLACE
#define SID_COMM_NULL MPI_COMM_NULL
#define SID_GROUP_EMPTY MPI_GROUP_EMPTY
#define SID_Datatype MPI_Datatype
#define SID_CHAR MPI_CHAR
#define SID_INT MPI_INT
#define SID_UNSIGNED MPI_UNSIGNED
#define SID_LONG_LONG MPI_LONG_LONG
#define SID_LONG MPI_LONG
#define SID_SIZE_T MPI_LONG_LONG
#define SID_FLOAT MPI_FLOAT
#define SID_DOUBLE MPI_DOUBLE
#define SID_BYTE MPI_BYTE
#define SID_Op MPI_Op
#define SID_SUM MPI_SUM
#define SID_MAX MPI_MAX
#define SID_MIN MPI_MIN
#else
#define SID_COMM_WORLD NULL
#define SID_IN_PLACE NULL
#define SID_COMM_NULL NULL
#define SID_GROUP_EMPTY NULL
#define SID_Datatype int
#define SID_LONG_LONG SID_TTTP01
#define SID_LONG SID_TTTP02
#define SID_FLOAT SID_TTTP03
#define SID_DOUBLE SID_TTTP04
#define SID_INT SID_TTTP05
#define SID_UNSIGNED SID_TTTP06
#define SID_SIZE_T SID_TTTP07
#define SID_BYTE SID_TTTP08
#define SID_CHAR SID_TTTP09
#define SID_Op int
#define SID_SUM SID_TTTP01
#define SID_MAX SID_TTTP02
#define SID_MIN SID_TTTP03
#endif

// Use double precision judiciously?
#if USE_DOUBLE
#define SID_REAL SID_DOUBLE
#else
#define SID_REAL SID_FLOAT
#endif

// This datastructure keeps track of quantities
// relevant to MPI communicators
typedef struct SID_Comm SID_Comm;
struct SID_Comm {
#if USE_MPI
    MPI_Comm  comm;
    MPI_Group group;
#else
    char *comm;
    char *group;
#endif
    int n_proc;
    int My_rank;
};

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void SID_Comm_init(SID_Comm **comm);
void SID_Comm_free(SID_Comm **comm);
void SID_Comm_list(SID_Comm *comm_in,int comm_id,SID_Comm *comm_out);
void SID_Comm_split(SID_Comm *comm_in, int colour, int key, SID_Comm *comm_out);
void SID_Type_size(SID_Datatype type, int *size);
void SID_Send(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, SID_Comm *comm);
void SID_Recv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm);
void SID_Sendrecv(void *       sendbuf,
                  int          sendcount,
                  SID_Datatype sendtype,
                  int          dest,
                  int          sendtag,
                  void *       recvbuf,
                  int          recvcount,
                  SID_Datatype recvtype,
                  int          source,
                  int          recvtag,
                  SID_Comm *   comm);
void SID_Reduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, int root, SID_Comm *comm);
void SID_Allreduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, SID_Comm *comm);
void SID_Barrier(SID_Comm *comm);
void SID_Bcast(void *buffer, int count, SID_Datatype datatype, int source_rank, SID_Comm *comm);

#ifdef __cplusplus
}
#endif

#endif
