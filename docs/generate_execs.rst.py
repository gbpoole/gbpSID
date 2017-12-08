import os
import sys
import re
from subprocess    import check_output
from gbpBuild_docs import *

project_name  = "gbpSID"
project_dir   = "/Users/gpoole/gbpSID/"
filename_root = 'execs'

def reformat_Clara_help_to_rst(lines_in):
    lines_out = []
    flag_remove_top_blank_lines=True
    for line in lines_in:
        if(len(line)>0 or not flag_remove_top_blank_lines):
            lines_out.append(line)
            flag_remove_top_blank_lines=False
    return(''.join(lines_out))

def generate_rst_file(input_dir,output_dir):
    # Open the output file for writing
    outFile = open(output_dir + "/" + filename_root + '.rst', "w")

    # Generate a list of the project's header files (and their modules)
    header_file_list   = []
    header_module_list = []
    parse_cmake_project(project_dir,"INCFILES", header_file_list,header_module_list,prepend_path=True,strip_ext=False)
    module_list=list(set(header_module_list))

    # Generate a list of doxygen groups in those header files
    group_list = []
    harvest_doxygen_groups(header_file_list,group_list)

    # copy header to output file
    add_project_file(input_dir,filename_root,".header",outFile)

    # ----------- Output logic for this file starts here -----------

    # Loop over the modules, adding each in turn to the API docs
    for module_i in module_list:
        exe_list=[]
        parse_cmake_project(project_dir,"EXEFILES", exe_list, module_select=module_i,prepend_path=False,strip_ext=True)
        flag_write_header=True
        for exec_i in exe_list:
            # Add the header if there is material for this module
            if(flag_write_header):
                add_project_file(input_dir,filename_root,'.'+module_i+".header",outFile)
                outFile.write("\n")
                flag_write_header=False

            # Send output of executable to the output file
            outFile.write(exec_i+'\n')
            outFile.write('-'*len(exec_i)+'\n')
            out = check_output(["/Users/gpoole/gbpSID/build-dev/"+exec_i, "-h"]).decode("utf-8")
            outFile.write(reformat_Clara_help_to_rst(out))

        # Add the footer if there is material for this module
        if(not flag_write_header):
            add_project_file(input_dir,filename_root,'.'+module_i+".footer",outFile)

    # ---------------------------------------------------------------

    # copy footer to output file
    add_project_file(input_dir,filename_root,".footer",outFile)

    # Close output file
    outFile.close()

input_dir     = sys.argv[1]
output_dir    = sys.argv[2]
generate_rst_file(input_dir,output_dir)
