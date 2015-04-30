#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_init(int       *argc,
              char     **argv[],
              SID_args   args[],
              void      *mpi_comm_as_void){
  int  status;
  int  i_level;
  int  i_char;
  int  flag_continue;
  int  flag_passed_comm;

  // MPI-specific things
#if USE_MPI
  int      n_keys;
  int      i_key;
  char     key[256];
  char     key_value[256];
  int      key_exists;
  char     nodes_string[256];
  SID_fp   fp_tmp;
  FILE    *fp_hack;
  int      node_name_length;
  MPI_Comm mpi_comm;
#if USE_MPI_IO
  MPI_Info info_disp;
#endif

  if(mpi_comm_as_void == NULL){
    flag_passed_comm=FALSE;
    MPI_Init(argc,argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &mpi_comm);
  }
  else{
    mpi_comm = *((MPI_Comm *) mpi_comm_as_void);
    flag_passed_comm=TRUE;
  }

  MPI_Comm_size(mpi_comm, &(SID.n_proc));
  MPI_Comm_rank(mpi_comm, &(SID.My_rank));

  SID.My_node =(char *)SID_malloc(SID_MAXLENGTH_PROCESSOR_NAME * sizeof(char));
  MPI_Get_processor_name(SID.My_node, &node_name_length);
  if (node_name_length >= SID_MAXLENGTH_PROCESSOR_NAME-1)
    SID_trap_error("SID_MAXLENGTH_PROCESSOR_NAME needs to be increased",ERROR_LOGIC);

  // Make my_rank=MASTER_RANK the master
  if(SID.My_rank==MASTER_RANK)
    SID.I_am_Master=TRUE;
  else
    SID.I_am_Master=FALSE;

  // Identify the last rank
  if(SID.My_rank==SID.n_proc-1)
    SID.I_am_last_rank=TRUE;
  else
    SID.I_am_last_rank=FALSE;

  #if USE_MPI_IO
  // Fetch collective buffering defaults
  MPI_Info_create(&(SID.file_info));
  if(SID.I_am_Master){
    fp_hack=fopen(".tmp.SID","w+");    
    fclose(fp_hack);
  }
  MPI_Barrier(mpi_comm);
  MPI_File_open(mpi_comm,
                ".tmp.SID",
                MPI_MODE_WRONLY,
                MPI_INFO_NULL,
                &(fp_tmp.fp));
  MPI_File_get_info(fp_tmp.fp,&info_disp);
  MPI_Info_get_nkeys(info_disp,&n_keys);
  for(i_key=0;i_key<n_keys;i_key++){
    MPI_Info_get_nthkey(info_disp,i_key,key);
    MPI_Info_get(info_disp,key,MPI_MAX_INFO_VAL,key_value,&key_exists);
    if(key_exists)
      MPI_Info_set((SID.file_info),key,key_value);
  }
  MPI_File_close(&(fp_tmp.fp));
  if(SID.I_am_Master)
    remove(".tmp.SID");

  // Set user-defined colective buffering optimizations
  sprintf(nodes_string,"%d",MIN(SID.n_proc,N_IO_FILES_MAX));
  MPI_Info_set((SID.file_info),"cb_nodes",            nodes_string);
  MPI_Info_set((SID.file_info),"cb_config_list",      "*:1");
  #endif
#else
  if(mpi_comm_as_void==NULL)
    flag_passed_comm=FALSE;
  else
    flag_passed_comm=TRUE;
  SID.My_rank=MASTER_RANK;
  SID.n_proc =1;
  SID.My_node =(char *)SID_malloc(SID_MAXLENGTH_PROCESSOR_NAME * sizeof(char));
  sprintf(SID.My_node,"localhost");
#endif

/*
#if !USE_MPI_IO
    SID.n_groups=SID.n_proc/N_IO_FILES_MAX;
    if(SID.n_proc%N_IO_FILES_MAX) SID.n_groups++;
    SID.My_group=SID.My_rank/N_IO_FILES_MAX;
#endif
*/

  // Set ranks to the left and right
  SID.rank_to_right  =(SID.My_rank+1)%SID.n_proc;
  SID.rank_to_left   = SID.My_rank-1;
  if(SID.rank_to_left<0)
    SID.rank_to_left = SID.n_proc-1;

  // Intitialize log timing information
  SID.time_start_level=(time_t *)SID_malloc(sizeof(time_t)*SID_LOG_MAX_LEVELS);
  SID.time_stop_level =(time_t *)SID_malloc(sizeof(time_t)*SID_LOG_MAX_LEVELS);
  SID.time_total_level=(int    *)SID_malloc(sizeof(int)   *SID_LOG_MAX_LEVELS);
  SID.IO_size         =(double *)SID_malloc(sizeof(double)*SID_LOG_MAX_LEVELS);
  SID.flag_use_timer  =(int    *)SID_malloc(sizeof(int)   *SID_LOG_MAX_LEVELS);
  for(i_level=0;i_level<SID_LOG_MAX_LEVELS;i_level++){
    SID.time_start_level[i_level]=0;
    SID.time_stop_level[i_level] =0;
    SID.time_total_level[i_level]=0;
    SID.IO_size[i_level]         =0.;
    SID.flag_use_timer[i_level]  =FALSE;
  }

  // Initialize other log information
#if USE_MPI
  if(*argc>1)
    SID.fp_in        =fopen((*argv)[1],"r");
  else
    SID.fp_in        =NULL;
#else
  SID.fp_in          =stdin;
#endif
  if(flag_passed_comm)
    SID.fp_log       = NULL;
  else
    SID.fp_log       = stderr;
  SID.level          =0;
  SID.indent         =TRUE;
  SID.awake          =TRUE;
  SID.flag_results_on=FALSE;
  SID.verbosity      =SID_LOG_MAX_LEVELS;

  // Store the name of the binary executable that brought us here
  strcpy(SID.My_binary,(*argv)[0]);
  strip_path(SID.My_binary);

  // Initialize argument information
  if(args!=NULL){
    if((status=SID_parse_args(*argc,*argv,args))>0){
      SID_print_syntax(*argc,*argv,args);
      SID_exit(status);
    }
  }
  else
    SID.args=NULL;

#if USE_MPI_IO
  if(SID.I_am_Master){
    fp_hack=fopen(".tmp.SID","w+");
    fclose(fp_hack);
  }
  MPI_Barrier(mpi_comm);
  SID_fopen(".tmp.SID","w",&fp_tmp);
  MPI_File_get_info(fp_tmp.fp,&info_disp);
  if(SID.I_am_Master){
    fprintf(stdout,"\n");
    fprintf(stdout,"MPI-I/O Configuration:\n");
    fprintf(stdout,"---------------------\n");
    MPI_Info_get_nkeys(info_disp,&n_keys);
    for(i_key=0;i_key<n_keys;i_key++){
      MPI_Info_get_nthkey(info_disp,i_key,key);
      MPI_Info_get(info_disp,key,MPI_MAX_INFO_VAL,key_value,&key_exists);
      if(key_exists)
        fprintf(stdout,"key %2d of %d: {%s}={%s}\n",i_key+1,n_keys,key,key_value);
    }
    fprintf(stdout,"\n");
  }
  SID_fclose(&fp_tmp);
  if(SID.I_am_Master)
    remove(".tmp.SID");
#else
  #if USE_MPI
  if(SID.I_am_Master)
    fprintf(stdout,"MPI-I/O switched off.\n\n");
  #endif
#endif

  // Create private COMM_WORLD
  SID_Comm_init(&(SID.COMM_WORLD));
#if USE_MPI
  MPI_Comm_dup(mpi_comm,                &((SID.COMM_WORLD)->comm));
  MPI_Comm_group((SID.COMM_WORLD)->comm,&((SID.COMM_WORLD)->group));
  MPI_Comm_size(SID.COMM_WORLD->comm,   &((SID.COMM_WORLD)->n_proc));
  MPI_Comm_rank(SID.COMM_WORLD->comm,   &((SID.COMM_WORLD)->My_rank));

  // We have duplicated our duplicate mpi communicator - now we can free the
  // original duplicate
  MPI_Comm_free(&mpi_comm);
#else
  SID.COMM_WORLD->comm   =NULL;
  SID.COMM_WORLD->group  =NULL;
  SID.COMM_WORLD->n_proc =1;
  SID.COMM_WORLD->My_rank=MASTER_RANK;
#endif

  // Start total-run-ime timer
  (void)time(&(SID.time_start));

  // Default max wallclock
  SID.max_wallclock=DEFAULT_MAX_WALLCLOCK_TIME;
}

