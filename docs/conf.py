#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# gbpSID documentation build configuration file
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute

import os
import subprocess
import sys
import git
import glob
import breathe # This is here so that pigar will catch it when generating requirements.txt

from datetime import datetime
from recommonmark.parser import CommonMarkParser

# Find the project root directory
git_repo = git.Repo(os.path.realpath(__file__), search_parent_directories=True)
dir_root = git_repo.git.rev_parse("--show-toplevel")
dir_python = os.path.abspath(os.path.join(dir_root, "python"))

# Include the paths to local python projects (including the _dev package)
for setup_py_i in glob.glob(dir_python + "/**/setup.py", recursive=True):
    sys.path.append(os.path.abspath(os.path.dirname(setup_py_i)))

# Include the project development module
import gbpSID_dev.project as prj
import gbpSID_dev.docs as docs

# Parse the project directory to learn what we need about the project
this_project = prj.project()

# Add it to the project path
breathe_directory = "%s/breathe/" % (this_project.params['dir_docs_build'])
sys.path.append(breathe_directory)

# If the is a Readthedocs build, then we need to run Doxygen
if (os.environ.get('READTHEDOCS', None) == 'True'):
    path_doxyfile=os.path.join(this_project.params['dir_docs'],"Doxyfile")
    dir_doxy_xml=os.path.join(this_project.params['dir_docs'],"xml")
    with open(path_doxyfile,"w") as fp_out:
        fp_out.write("OUTPUT_DIRECTORY=docs")
    subprocess.call("cd ../doxygen; doxygen %s"%(path_doxyfile), shell=True)
else:
    dir_doxy_xml=os.path.join(this_project.params['dir_docs_build'],"doxygen/xml")

# -- General configuration ------------------------------------------------

# Set minimal Sphinx version
needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ['sphinx.ext.autodoc',
              'sphinx.ext.doctest',
              'sphinx.ext.intersphinx',
              'sphinx.ext.todo',
              'sphinx.ext.coverage',
              'sphinx.ext.ifconfig',
              'sphinx.ext.viewcode',
              'breathe']

# Some things that Breathe needs
breathe_projects = {this_project.params['project_name']: dir_doxy_xml}
breathe_default_project = this_project.params['project_name']

# Add any paths that contain templates here, relative to this directory.
templates_path = ['%s/templates' % (this_project.dir_root)]

# Add a markdown parser
source_parsers = {
    '.md': CommonMarkParser,
}

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
source_suffix = ['.rst', '.md']

# The master toctree document.
master_doc = 'index'

# Exclude the source files in the docs directory
# (we've copied them to the build directory and
#  dont want to double count them.)
#exclude_patterns = '*.rst'

# General information about the project.
project = this_project.params['project_name']
year = datetime.today().year
copyright = str(year) + ', %s' % (this_project.params['project_author'])
author = this_project.params['project_author']

# The version info for the project you're documenting, acts as replacement for
# |version| and |release|, also used in various other places throughout the
# built documents.

# Extract version from .version file.
# n.b.: 'version' should be the short X.Y version
#       'release' should be the full version, including alpha/beta/rc tags
version = this_project.params['version']
release = this_project.params['release']

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This patterns also effect to html_static_path and html_extra_path
exclude_patterns = ['build*', '_build*', '**/extern']

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True

# -- Options for HTML output ----------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
html_theme_path = ['themes']
html_theme = 'gbp_theme'
html_show_sourcelink = False
html_favicon = '%s/static/favicon.ico' % (this_project.params['dir_docs'])
html_logo = '%s/static/logo.png' % (this_project.params['dir_docs'])

html_sidebars = {'**': ['globaltoc.html', 'relations.html', 'sourcelink.html', 'searchbox.html'], }

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
html_theme_options = {'gbp_project_name': this_project.params['project_name']}

extra_nav_links = {'Index': 'genindex.html'}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['static']

# -- Options for HTMLHelp output ------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = '%sdoc' % (this_project.params['project_name'])

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc,
     '%s.tex' %
     (this_project.params['project_name']),
     '%s Documentation' %
     (this_project.params['project_name']),
     this_project.params['project_author'],
     'manual'),
]


# -- Options for manual page output ---------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc,
     this_project.params['project_name'].lower(),
     '%s Documentation' %
     (this_project.params['project_name']),
     [author],
     1)]


# -- Options for Texinfo output -------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, this_project.params['project_name'], '%s Documentation' % (this_project.params['project_name']),
     author, this_project.params['project_name'], this_project.params['project_description'],
     'Miscellaneous'),
]
