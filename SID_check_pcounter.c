#include <stdio.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_check_pcounter(pcounter_info *pcounter,
                        size_t         i){
  if(i>=pcounter->i_report_next){
     SID_log("%3d%% complete.",SID_LOG_COMMENT|SID_LOG_TIMER,(int)((100./(float)pcounter->n_report)*(float)(pcounter->i_report)));
     pcounter->i_report_next=MIN(pcounter->n_i,(size_t)((float)(pcounter->n_i-i)/(float)(pcounter->n_report-pcounter->i_report)));
     pcounter->i_report++;
  }
}

