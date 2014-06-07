#include <stdio.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_init_pcounter(pcounter_info *pcounter,
                       size_t         n_i,
                       int            n_report){

   // Initialize
   pcounter->n_report=n_report;
   pcounter->i_report=0;
   pcounter->n_i     =n_i;

   // Set the next pcounter report point
   if(pcounter->n_i>pcounter->n_report && n_report!=0)
      pcounter->i_report_next=MIN(pcounter->n_i,(size_t)((float)pcounter->n_i/(float)pcounter->n_report));
   // There is no reporting if n_i<n_report or n_report==0
   else
      pcounter->i_report_next=pcounter->n_i+1;

}

