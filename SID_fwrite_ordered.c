#include <gbpSID.h>
#include <unistd.h>

size_t SID_fwrite_ordered(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp){
  size_t r_val;
#if USE_MPI
#if USE_MPI_IO
  int    r_val_i;
  int    n_total;
  MPI_Status status;
  n_total=(int)(size_per_item*n_items);
  MPI_File_write_ordered(fp->fp,
                         buffer,
                         n_total,
                         MPI_BYTE,
                         &status);
  MPI_Get_count(&status,MPI_BYTE,&r_val_i);
  r_val=(size_t)r_val_i/size_per_item;
#else
  char   buffer_Sendrecv[IO_BUFFER_SIZE];
  size_t n_send;
  size_t n_unsent;
  size_t offset;
  size_t r_val_i;
  int    n_Sendrecv;
  int    n_items_rank;
  int    i_rank;
  int    source_rank;
  int    destin_rank;
  for(i_rank=0,r_val=0;i_rank<SID.n_proc;i_rank++){
        if(i_rank==MASTER_RANK && SID.I_am_Master){
           r_val=fwrite(buffer,
                        size_per_item,
                        n_items,
                        fp->fp);
        }
        else if(i_rank!=MASTER_RANK){
           if(SID.I_am_Master){
              source_rank =i_rank;
              destin_rank =MPI_PROC_NULL;
              n_send      =0; // Reset below
              n_items_rank=0; // Reset below
           }
           else if(i_rank==SID.My_rank){
              source_rank =MPI_PROC_NULL;
              destin_rank =MASTER_RANK;
              n_send      =n_items*size_per_item;
              n_items_rank=n_items;
           }
           else{
              source_rank =MPI_PROC_NULL;
              destin_rank =MPI_PROC_NULL;
              n_send      =0;
              n_items_rank=0;
           }
           SID_Sendrecv(&n_send,
                        1,
                        SID_SIZE_T,
                        destin_rank,
                        1918270,
                        &n_send,
                        1,
                        SID_SIZE_T,
                        source_rank,
                        1918270,
                        SID.COMM_WORLD);
           SID_Sendrecv(&n_items_rank,
                        1,
                        SID_SIZE_T,
                        destin_rank,
                        1918271,
                        &n_items_rank,
                        1,
                        SID_SIZE_T,
                        source_rank,
                        1918271,
                        SID.COMM_WORLD);
           n_unsent=n_send;
           r_val_i =0;
           offset  =0;
           while(n_unsent>0){
              if(n_unsent<=IO_BUFFER_SIZE)
                n_Sendrecv=(int)n_unsent;
              else
                n_Sendrecv=IO_BUFFER_SIZE;
              SID_Sendrecv(&n_Sendrecv,
                           1,
                           SID_INT,
                           destin_rank,
                           1918272,
                           &n_Sendrecv,
                           1,
                           SID_INT,
                           source_rank,
                           1918272,
                           SID.COMM_WORLD);
              SID_Sendrecv(&(((char *)buffer)[offset]),
                           n_Sendrecv,
                           SID_BYTE,
                           destin_rank,
                           1918273,
                           buffer_Sendrecv,
                           n_Sendrecv,
                           SID_BYTE,
                           source_rank,
                           1918273,
                           SID.COMM_WORLD);
              if(SID.I_am_Master)
                 r_val_i+=fwrite(buffer_Sendrecv,
                                 1,
                                 n_Sendrecv,
                                 fp->fp);
              n_unsent-=(size_t)n_Sendrecv;
              offset  +=(size_t)n_Sendrecv;
           }
           if(SID.I_am_Master && (r_val_i!=(size_t)n_send || offset!=n_send || n_unsent!=0))
             SID_trap_error("Problem in SID_fwrite_ordered (rank=%d: %zu!=%zu || %zu!=%zu || %zu!=0).",ERROR_IO_WRITE,i_rank,r_val_i,n_send,offset,n_send,n_unsent);
           else
             r_val+=n_items_rank;
        }
        SID_Barrier(SID.COMM_WORLD);
  }
  SID_Bcast(&r_val,sizeof(size_t),MASTER_RANK,SID.COMM_WORLD);
  sync();
#endif
#else
  r_val=fwrite(buffer,
               size_per_item,
               n_items,
               fp->fp);
  sync();
#endif
  return(r_val);
}

