import os
import sys
import re
from   subprocess import call

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

def write_group_to_file(outFile,group_to_write,project_name):
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
