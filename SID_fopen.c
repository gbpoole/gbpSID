#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

int SID_fopen(char   *filename,
              char   *mode,
              SID_fp *fp){
   int r_val=TRUE;
#if USE_MPI
#if USE_MPI_IO
   FILE *fp_NFS_hack;
   char *filename_test_hack;
   int   filename_test_hack_length;
   // -------------------------------------------
   // This is a hack to fix a bug which can occur
   //   when trying to write to a new file over NFS
   filename_test_hack_length=strlen(filename)+1; // +1 needed to catch the terminating /0 as well
   MPI_Bcast(&filename_test_hack_length,1,MPI_INT,MASTER_RANK,SID.COMM_WORLD);
   filename_test_hack=(char *)malloc(sizeof(char)*filename_test_hack_length);
   if(SID.I_am_Master)
     strcpy(filename_test_hack,filename);
   MPI_Bcast(filename_test_hack,filename_test_hack_length,MPI_CHAR,MASTER_RANK,SID.COMM_WORLD);
   if(!strcmp(mode,"w")){
     if(SID.I_am_Master || strcmp(filename,filename_test_hack)!=0){
       if((fp_NFS_hack=fopen(filename,"r"))==NULL){
         fp_NFS_hack=fopen(filename,"w+");
         fclose(fp_NFS_hack);
       }
       else{
         remove(filename);
         fp_NFS_hack=fopen(filename,"w+");
         fclose(fp_NFS_hack);
       }
     }
   }
   else if(!strcmp(mode,"a")){
     if(SID.I_am_Master){
       if((fp_NFS_hack=fopen(filename,"r"))==NULL){
         fp_NFS_hack=fopen(filename,"w+");
         fclose(fp_NFS_hack);
       }
     }
   }
   free(filename_test_hack);
   MPI_Barrier(SID.COMM_WORLD);
   // -------------------------------------------
   if(!strcmp(mode,"r")){
     r_val=!(MPI_File_open(SID.COMM_WORLD,
                           filename,
                           MPI_MODE_RDONLY,
                           SID.file_info,
                           &(fp->fp)));
   }
   else if(!strcmp(mode,"w")){
     r_val=!(MPI_File_open(SID.COMM_WORLD,
                           filename,
                           MPI_MODE_WRONLY,
                           SID.file_info,
                           &(fp->fp)));
   }
   else if(!strcmp(mode,"a")){
     r_val=!(MPI_File_open(SID.COMM_WORLD,
                           filename,
                           MPI_MODE_WRONLY|MPI_MODE_APPEND,
                           SID.file_info,
                           &(fp->fp)));
   }
   else{
     r_val =FALSE;
   }
#else
  (fp->fp)=fopen(filename,mode);
  if((fp->fp)!=NULL)
    r_val==TRUE;
  else
    r_val=FALSE;
#endif
#else
  (fp->fp)=fopen(filename,mode);
  if((fp->fp)!=NULL)
    r_val==TRUE;
  else
    r_val=FALSE;
#endif
  return(r_val);
}

