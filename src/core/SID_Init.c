#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <gbpSID.h>

void strip_path_local(char *string);
void strip_path_local(char *string) {
    int i_char;
    int j_char;
    int i_start;

    int string_size = strlen(string);
    for(i_char = 0, i_start = 0; i_char < string_size; i_char++) {
        char temp_char[2];
        sprintf(temp_char, "%c", string[i_char]);
        if(!strcmp(temp_char, "/"))
            i_start = i_char + 1;
    }
    if(i_start > 0) {
        for(i_char = 0, j_char = i_start; j_char < string_size; i_char++, j_char++)
            strncpy(&(string[i_char]), &(string[j_char]), 1);
        sprintf(&(string[i_char]), "");
    }
}

//! Initialize the SID run-time environment
//! \param argc A pointer to the argument count passed to main()
//! \param argv A pointer to the argument list passed to main()
//! \param mpi_comm_as_void An optional MPI communicator to inherit from.  Set to NULL to ignore.
//!
//! This function should be called as soon as possible for any project utilizing *gbpSID*.  It takes pointers to the run-time arguments passed to
//! main() and an optional communicator to inherit from as parameters
void SID_Init(SID_MARK_USED(int *argc, USE_MPI), char **argv[], void *mpi_comm_as_void) {
    int status;
    int i_level;
    int i_char;
    int flag_continue;
    int flag_passed_comm;

    // MPI-specific things
#if USE_MPI
    int      n_keys;
    int      i_key;
    char     key[256];
    char     key_value[256];
    int      key_exists;
    char     nodes_string[256];
    SID_fp   fp_tmp;
    FILE *   fp_hack;
    int      node_name_length;
    MPI_Comm mpi_comm;
#if USE_MPI_IO
    MPI_Info info_disp;
#endif

    if(mpi_comm_as_void == NULL) {
        flag_passed_comm = GBP_FALSE;
        MPI_Init(argc, argv);
        MPI_Comm_dup(MPI_COMM_WORLD, &mpi_comm);
    } else {
        MPI_Comm_dup(*((MPI_Comm *)mpi_comm_as_void), &mpi_comm);
        flag_passed_comm = GBP_TRUE;
    }

    MPI_Comm_size(mpi_comm, &(SID.n_proc));
    MPI_Comm_rank(mpi_comm, &(SID.My_rank));

    SID.My_node = (char *)SID_malloc(SID_MAXLENGTH_PROCESSOR_NAME * sizeof(char));
    MPI_Get_processor_name(SID.My_node, &node_name_length);
    if(node_name_length >= SID_MAXLENGTH_PROCESSOR_NAME - 1)
        SID_exit_error("SID_MAXLENGTH_PROCESSOR_NAME needs to be increased", SID_ERROR_LOGIC);

    // Make my_rank=SID_MASTER_RANK the master
    if(SID.My_rank == SID_MASTER_RANK)
        SID.I_am_Master = GBP_TRUE;
    else
        SID.I_am_Master = GBP_FALSE;

    // Identify the last rank
    if(SID.My_rank == SID.n_proc - 1)
        SID.I_am_last_rank = GBP_TRUE;
    else
        SID.I_am_last_rank = GBP_FALSE;

#if USE_MPI_IO
    // Fetch collective buffering defaults
    MPI_Info_create(&(SID.file_info));
    if(SID.I_am_Master) {
        fp_hack = fopen(".tmp.SID", "w+");
        fclose(fp_hack);
    }
    MPI_Barrier(mpi_comm);
    MPI_File_open(mpi_comm, ".tmp.SID", MPI_MODE_WRONLY, MPI_INFO_NULL, &(fp_tmp.fp));
    MPI_File_get_info(fp_tmp.fp, &info_disp);
    MPI_Info_get_nkeys(info_disp, &n_keys);
    for(i_key = 0; i_key < n_keys; i_key++) {
        MPI_Info_get_nthkey(info_disp, i_key, key);
        MPI_Info_get(info_disp, key, MPI_MAX_INFO_VAL, key_value, &key_exists);
        if(key_exists)
            MPI_Info_set((SID.file_info), key, key_value);
    }
    MPI_File_close(&(fp_tmp.fp));
    if(SID.I_am_Master)
        remove(".tmp.SID");

    // Set user-defined colective buffering optimizations
    sprintf(nodes_string, "%d", GBP_MIN(SID.n_proc, SID_N_IO_FILES_MAX));
    MPI_Info_set((SID.file_info), "cb_nodes", nodes_string);
    MPI_Info_set((SID.file_info), "cb_config_list", "*:1");
#endif
#else
    if(mpi_comm_as_void == NULL)
        flag_passed_comm = GBP_FALSE;
    else
        flag_passed_comm = GBP_TRUE;
    SID.My_rank = SID_MASTER_RANK;
    SID.n_proc  = 1;
    SID.My_node = (char *)SID_malloc(SID_MAXLENGTH_PROCESSOR_NAME * sizeof(char));
    sprintf(SID.My_node, "localhost");
#endif

    /*
    #if !USE_MPI_IO
        SID.n_groups=SID.n_proc/SID_N_IO_FILES_MAX;
        if(SID.n_proc%SID_N_IO_FILES_MAX) SID.n_groups++;
        SID.My_group=SID.My_rank/SID_N_IO_FILES_MAX;
    #endif
    */

    // Set ranks to the left and right
    SID.rank_to_right = (SID.My_rank + 1) % SID.n_proc;
    SID.rank_to_left  = SID.My_rank - 1;
    if(SID.rank_to_left < 0)
        SID.rank_to_left = SID.n_proc - 1;

    // Intitialize log timing information
    SID.time_start_level = (time_t *)SID_malloc(sizeof(time_t) * SID_LOG_MAX_LEVELS);
    SID.time_stop_level  = (time_t *)SID_malloc(sizeof(time_t) * SID_LOG_MAX_LEVELS);
    SID.time_total_level = (int *)SID_malloc(sizeof(int) * SID_LOG_MAX_LEVELS);
    SID.IO_size          = (double *)SID_malloc(sizeof(double) * SID_LOG_MAX_LEVELS);
    SID.flag_use_timer   = (int *)SID_malloc(sizeof(int) * SID_LOG_MAX_LEVELS);
    for(i_level = 0; i_level < SID_LOG_MAX_LEVELS; i_level++) {
        SID.time_start_level[i_level] = 0;
        SID.time_stop_level[i_level]  = 0;
        SID.time_total_level[i_level] = 0;
        SID.IO_size[i_level]          = 0.;
        SID.flag_use_timer[i_level]   = GBP_FALSE;
    }

    // Initialize other log information
    if(flag_passed_comm)
        SID.fp_log = NULL;
    else
        SID.fp_log = stderr;
    SID.level          = 0;
    SID.indent         = GBP_TRUE;
    SID.logging_active = GBP_TRUE;
    SID.verbosity      = SID_LOG_MAX_LEVELS;

    // Store the name of the binary executable that brought us here
    strcpy(SID.My_binary, (*argv)[0]);
    strip_path_local(SID.My_binary);

#if USE_MPI_IO
    if(SID.I_am_Master) {
        fp_hack = fopen(".tmp.SID", "w+");
        fclose(fp_hack);
    }
    MPI_Barrier(mpi_comm);
    SID_fopen(".tmp.SID", "w", &fp_tmp);
    MPI_File_get_info(fp_tmp.fp, &info_disp);
    if(SID.I_am_Master) {
        fprintf(stdout, "\n");
        fprintf(stdout, "MPI-I/O Configuration:\n");
        fprintf(stdout, "---------------------\n");
        MPI_Info_get_nkeys(info_disp, &n_keys);
        for(i_key = 0; i_key < n_keys; i_key++) {
            MPI_Info_get_nthkey(info_disp, i_key, key);
            MPI_Info_get(info_disp, key, MPI_MAX_INFO_VAL, key_value, &key_exists);
            if(key_exists)
                fprintf(stdout, "key %2d of %d: {%s}={%s}\n", i_key + 1, n_keys, key, key_value);
        }
        fprintf(stdout, "\n");
    }
    SID_fclose(&fp_tmp);
    if(SID.I_am_Master)
        remove(".tmp.SID");
#endif

    // Create private COMM_WORLD
    SID_Comm_init(&(SID_COMM_WORLD));
#if USE_MPI
    MPI_Comm_dup(mpi_comm, &((SID_COMM_WORLD)->comm));
    MPI_Comm_group((SID_COMM_WORLD)->comm, &((SID_COMM_WORLD)->group));
    MPI_Comm_size(SID_COMM_WORLD->comm, &((SID_COMM_WORLD)->n_proc));
    MPI_Comm_rank(SID_COMM_WORLD->comm, &((SID_COMM_WORLD)->My_rank));

    // We have duplicated our duplicate mpi communicator - now we can free the
    // original duplicate
    MPI_Comm_free(&mpi_comm);
#else
    SID_COMM_WORLD->comm    = NULL;
    SID_COMM_WORLD->group   = NULL;
    SID_COMM_WORLD->n_proc  = 1;
    SID_COMM_WORLD->My_rank = SID_MASTER_RANK;
#endif

    // Start total-run-ime timer
    (void)time(&(SID.time_start));
}
