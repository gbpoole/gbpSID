import os
import sys
import re

project_name  = "gbpSID"
project_dir   = "/Users/gpoole/gbpSID/"
filename_root = 'API'

def parse_cmake_local(cur_dir,search_string,result_list,active_API_module="undefined",module_select=None,module_list=None,prepend_path=True,strip_ext=False):
    # TODO: Remove external directories from files and paths
    # TODO: Remove submodules from files and paths
    with open( cur_dir + "/" + "local.cmake", 'r') as infile:
        for line in infile:
            line=line.strip()
            if(len(line)>0):
                if(line[0] != '#'):
                    # Remove '()'s and '"'s and split into words
                    words = line.replace('('," ").replace(')'," ").replace('"'," ").split()
                    # If this is an append line, then we have an item to keep
                    if(words[1] == "APPEND" and len(words)==4):
                        if(words[2]==search_string):
                            item = words[3]
                            # If we've asked to strip extensions, do so
                            if(strip_ext):
                                item=os.path.splitext(item)[0]
                            # If we've asked to prepend paths, do so
                            if(prepend_path):
                                item=cur_dir + '/' + item
                            # Append to the result
                            if(module_select == None or (module_select != None and active_API_module==module_select)):
                                result_list.append(item)
                                if(module_list != None):
                                    module_list.append(active_API_module)
                # Else we may have a Doxygen module directive.  Check for it
                else:
                    words = line[1:].split()
                    if(len(words)==2):
                        if(words[0] == 'set_active_API_module'):
                            active_API_module = words[1]

def parse_cmake_project(cur_dir,search_string,result_list,module_list=None,module_select=None,prepend_path=True,strip_ext=False):
    # Add local entries to list
    parse_cmake_local(cur_dir,search_string,result_list,module_list=module_list,module_select=module_select,prepend_path=prepend_path,strip_ext=strip_ext)

    # Build list of local project directories
    local_dirs = []
    parse_cmake_local(cur_dir,"SRCDIRS",local_dirs)
    parse_cmake_local(cur_dir,"PASSDIRS",local_dirs)

    # Recurse over local project directories
    for local_dir in local_dirs:
        if (os.path.isdir(local_dir) == True):
            parse_cmake_project(local_dir,search_string,result_list,module_list=module_list,module_select=module_select,prepend_path=prepend_path,strip_ext=strip_ext)

def harvest_doxygen_groups(file_list,group_list):
    # Loop over header files
    for file_i in file_list:
        with open(file_i, 'r') as infile:
            # Loop over each line in the file
            for line in infile:
                # Check for a Doygren comment and return its starting position (if there is one)
                comment_start=line.find("//!")
                if comment_start>=0:
                    # Check for a group definition
                    group_start=line.find("\\defgroup",comment_start+3)
                    if(group_start>0):
                        # Add the definition name to the list
                        words=line[group_start:].strip().split(' ',2)
                        group_list.append([words[1],words[2]])

def write_group_to_file(outFile,group_to_write):
    outFile.write(".. doxygengroup:: "+group_to_write+"\n")
    outFile.write("   :project: "+project_name+"\n")
    outFile.write("   :content-only:\n")
    outFile.write("   :members:\n\n")

def add_project_file(input_dir,filename_root,filename_modifier,outFile):
    filename_in = input_dir+"/"+filename_root+'.rst'+filename_modifier
    if(os.path.isfile(filename_in)):
        with open(filename_in,'r') as inFile:
            for line in inFile :
                outFile.write(line)

def generate_rst_file():
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
            write_group_to_file(outFile,module_group)

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
                    write_group_to_file(outFile,group_i)

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
generate_rst_file()
