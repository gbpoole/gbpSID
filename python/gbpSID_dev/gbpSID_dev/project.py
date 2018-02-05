import os
import sys
import git
import yaml

class project:
    def __init__(self):

        # Find the root directory
        git_repo = git.Repo(os.path.realpath(__file__), search_parent_directories=True)
        self.dir_root = git_repo.git.rev_parse("--show-toplevel")

        # Set project.yml filename
        filename_prj = os.path.join(self.dir_root,".project.yml")

        # Read project yml file into dictionary
        fp_in = open(filename_prj,"r")
        ## Return a list of dictionaries (generally 1 key each)
        params_list=yaml.load(fp_in) 
        ## Convert to single dictionary
        self.params={ k: v for d in params_list for k, v in d.items() } 

        # Set some project direcories
        self.params['dir_docs']         = os.path.abspath(os.path.join(self.dir_root,"docs"))
        self.params['dir_docs_api_src'] = os.path.abspath(os.path.join(self.dir_root,"docs/src"))
        self.params['dir_docs_build']   = os.path.abspath(os.path.join(self.dir_root,"docs/build"))
        self.params['dir_python']       = os.path.abspath(os.path.join(self.dir_root,"python"))
        self.params['dir_python_pkg']   = os.path.abspath(os.path.join(self.dir_root,'python/gbpSID/'))

        # Check if this is a C-project (the appropriate makefile will be present if so)
        if(os.path.isfile(os.path.join(self.dir_root,".Makefile-c"))):
            self.params['is_C_project'] = True
        else:
            self.params['is_C_project'] = False

        # Check if this is a Python-project (the appropriate makefile will be present if so)
        if(os.path.isfile(os.path.join(self.dir_root,".Makefile-py"))):
            self.params['is_Python_project'] = True
        else:
            self.params['is_Python_project'] = False

        # Extract version & release from .version file.
        # TODO: Need to split version from release.
        try:
            with open("%s/.version"%(self.dir_root),"r") as fp_in:
                self.params['version'] = str(fp_in.readline()).strip('\n')
        except:
            print("Project '.version' file not found.  Setting version='unset'")
            self.params['version'] ='unset'
        self.params['release'] = self.params['version']

    def print(self):
        print("Project information:")
        print("-------------------")
        for k,v in sorted(self.params.items()):
            print('   '+k+" = "+str(v))
