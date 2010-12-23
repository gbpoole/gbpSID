#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_print_syntax(int       argc,
		      char     *argv[],
		      SID_args  args[]){
  int      i_char;
  int      first1=TRUE;
  int      first2=TRUE;
  int      i_args=0;
  SID_arg *this_args;
  int      flag=TRUE;

  for(i_char=strlen(argv[0])-1;i_char>0 && flag;i_char--){
    if(argv[0][i_char]=='/')
      flag=FALSE;
  }

  fprintf(stderr,"\nSYNTAX: %s ",&(argv[0][i_char]));
  i_args=0;
  while(args[i_args]!=NULL){
    this_args=(SID_arg *)(args[i_args]);
    if(this_args->key!=NULL && this_args->flag_required){
      if(first1){
	fprintf(stderr,"-%c",((char *)(this_args->key))[0]);
	first1=FALSE;
      }
      else
	fprintf(stderr,"%c",((char *)(this_args->key))[0]);
    }
    i_args++;
  }
  i_args=0;
  while(args[i_args]!=NULL){
    this_args=(SID_arg *)(args[i_args]);
    if(this_args->key!=NULL && !this_args->flag_required){
      if(first1){
	fprintf(stderr,"-[%c",((char *)(this_args->key))[0]);
	first1=FALSE;
	first2=FALSE;
      }
      else{
	if(first2)
	  fprintf(stderr,"[%c",((char *)(this_args->key))[0]);
	else
	  fprintf(stderr,"%c",((char *)(this_args->key))[0]);
      }
    }
    i_args++;
  }
  if(!first2)
    fprintf(stderr,"]");
  i_args=0;
  while(args[i_args]!=NULL){
    this_args=(SID_arg *)(args[i_args]);
    if(this_args->key==NULL){
      if(this_args->flag_required)
	fprintf(stderr," %s",((char *)(this_args->var_name)));
      else
	fprintf(stderr," [%s]",((char *)(this_args->var_name)));
    }
    i_args++;
  }
  fprintf(stderr,"\n------\n\n");
  
}

