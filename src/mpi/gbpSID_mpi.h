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

// Set an alias to the SID communicator so that
//    the API meets the principle of being a 
//    MPI->SID drop-in replacement.
#define SID_COMM_WORLD (SID.COMM_WORLD)

#if !USE_MPI
typedef struct SID_Status SID_Status;
struct SID_Status {
    int SID_SOURCE;
    int SID_TAG;
};
#endif

#if USE_MPI
#define SID_Status MPI_Status
#define SID_SUCCESS MPI_SUCCESS
#define SID_STATUS_IGNORE MPI_STATUS_IGNORE
#define SID_SOURCE MPI_SOURCE;
#define SID_TAG MPI_TAG;
#define SID_ANY_SOURCE MPI_ANY_SOURCE
#define SID_ANY_TAG MPI_ANY_TAG
#define SID_IN_PLACE MPI_IN_PLACE
#define SID_COMM_NULL MPI_COMM_NULL
#define SID_Request MPI_Request
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
#define SID_STATUS_IGNORE NULL
#define SID_ANY_SOURCE 1
#define SID_ANY_TAG 1
#ifdef _MAIN
SID_Status SID_SUCCESS={SID_ANY_SOURCE,SID_ANY_TAG};
#else
extern SID_Status SID_SUCCESS;
#endif
#define SID_IN_PLACE NULL
#define SID_COMM_NULL NULL
#define SID_Request int
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
void SID_Recv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Status *status);
void SID_Isend(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, SID_Comm *comm, SID_Request *request);
void SID_Irecv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Request *request);
void SID_Ssend(void *buf,
               int count,
               SID_Datatype datatype,
               int dest,
               int tag,
               SID_Comm *comm);
void SID_Sendrecv(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, void *recvbuf,
                  int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Status *status);
void SID_Probe(int source,
               int tag,
               SID_Comm *comm,
               SID_Status *status);
void SID_Waitall(int count,
                 SID_Request array_request[],
                 SID_Status  array_status[]);
void SID_Allgather(void         *sendbuf,
                   int           sendcount,
                   SID_Datatype  sendtype,
                   void         *recvbuf,
                   int           recvcount,
                   SID_Datatype  recvtype,
                   SID_Comm     *comm);
void SID_Allgatherv(void        *sendbuf,
                    int          sendcount,
                    SID_Datatype sendtype,
                    void        *recvbuf,
                    int         *recvcounts,
                    int         *displs,
                    SID_Datatype recvtype,
                    SID_Comm    *comm);
void SID_Gatherv(void        *sendbuf,
                 int          sendcount,
                 SID_Datatype sendtype,
                 void        *recvbuf,
                 int         *recvcounts,
                 int         *displs,
                 SID_Datatype recvtype,
                 int          root,
                 SID_Comm    *comm);
void SID_Scatterv(void        *sendbuf,
                  int         *sendcounts,
                  int         *displs,
                  SID_Datatype sendtype,
                  void        *recvbuf,
                  int          recvcount,
                  SID_Datatype recvtype,
                  int          root,
                  SID_Comm    *comm);

void SID_Reduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, int root, SID_Comm *comm);
void SID_Allreduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, SID_Comm *comm);
void SID_Barrier(SID_Comm *comm);
void SID_Bcast(void *buffer, int count, SID_Datatype datatype, int source_rank, SID_Comm *comm);
double SID_Wtime( void );

#ifdef __cplusplus
}
#endif

#endif
