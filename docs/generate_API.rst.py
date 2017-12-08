import os
import sys
import re
import gbpBuild_docs
from gbpBuild_docs import *

project_name  = "gbpSID"
project_dir   = "/Users/gpoole/gbpSID/"
filename_root = 'API'

def generate_rst_file(input_dir,output_dir):
    # Open the output file for writing
    outFile = open(output_dir + "/" + filename_root + '.rst', "w")

    # Generate a list of the project's header files (and their modules)
    header_file_list = []
    module_list      = []
    parse_cmake_project(project_dir,"INCFILES", header_file_list,module_list,prepend_path=True,strip_ext=False)

    # Generate a list of doxygen groups in those header files
    group_list = []
    harvest_doxygen_groups(header_file_list,group_list)

    # copy header to output file
    add_project_file(input_dir,filename_root,".header",outFile)

    # ----------- Output logic for this file starts here -----------

    # Loop over the modules, adding each in turn to the API docs
    for module_i in module_list:
        flag_write_header = True

        # 1) ... add this module's classes group ...
        module_group = module_i+"_classes"
        group_found = group_list[group_list[:][0].index(module_group)] if module_group in group_list[:][0] else None
        if(group_found != None):
            # Add the header if there is material for this module
            if(flag_write_header):
                add_project_file(input_dir,filename_root,'.'+module_i+".header",outFile)
                outFile.write("\n")
                flag_write_header=False
            outFile.write(group_found[1]+"\n")
            outFile.write('`'*len(group_found[1])+"\n")
            write_group_to_file(outFile,module_group,project_name)

        # 2) ... add this module's functions ...
        function_list=[]
        parse_cmake_project(project_dir,"SRCFILES", function_list, module_select=module_i,prepend_path=False,strip_ext=True)
        flag_write_header_group=True
        for fctn in function_list:
            # Add the header if there is material for this module
            if(flag_write_header):
                add_project_file(input_dir,filename_root,'.'+module_i+".header",outFile)
                outFile.write("\n")
                flag_write_header=False
            if(flag_write_header_group):
                title_txt = 'Functions'
                outFile.write(title_txt+"\n")
                outFile.write('`'*len(title_txt)+"\n")
                flag_write_header_group=False
            outFile.write(".. doxygenfunction:: "+fctn+"\n")
            outFile.write("   :project: "+project_name+"\n\n")

        # 3) ... add any remaining defined groups ...
        for [group_i,group_i_desc] in group_list:
            group_words=group_i.split("_",1)
            if(len(group_words)==2):
                module_group=group_words[1]
                if(group_words[0]==module_i and module_group!="classes"):
                    # Add the header if there is material for this module
                    if(flag_write_header):
                        add_project_file(input_dir,filename_root,'.'+module_i+".header",outFile)
                        outFile.write("\n")
                        flag_write_header=False
                    outFile.write(group_i_desc+"\n")
                    outFile.write('`'*len(group_i_desc)+"\n")
                    write_group_to_file(outFile,group_i,project_name)

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
