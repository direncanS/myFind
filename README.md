# myFind
write a program in C/C++ that enables a user to parallelly find different files in a folder without the usage of the linux command “find” as a child process
Usage:
./myfind [-R] [-i] searchpath filename1 [filename2] …[filenameN]
The main program accepts the arguments <searchpath> and <filename1 .. N>. Keep in mind that a
variable number of arguments (= variable number of filenames to look for) can be used and that the
options -R and -i can be placed anywhere in the arguments list.
• -R:
o should switch myfind in recursive mode and find all matching files in and below the
searchpath folder
(else the files should only be searched in the searchpath folder)
• -i
o case in-sensitive search
• searchpath
o can be an absolute or a relative path.
• filename
o only filenames as plain string
o no support for paths, subpaths, wildcards required.
Example:
./myfind ./ test.txt test.doc test
Here, myfind searches for the 3 files in the current working directory in parallel.
www.technikum-wien.at 2
The main program fork()s a child-process for each filename and looks for the file in the defined
searchpath. In case a file is found, an entry in the following output format will be printed to stdout
(unsorted; but readable in full lines). Describe in the code how you achieved this requirement (in
comment above main).
Output-Format:
<pid>: <filename>: <complete-path-to-found-file>\n
• <pid>: process-id of the child-process that finds the entry.
• <filename>: references the filename that was passed into the main program as an argument.
• <complete-path-to-found-file>: absolute path to found file
Hints:
• The parent-process must react on the termination of child-processes (prevent a zombie
apocalypse).
• Use getopt() for argument parsing.
• Check the code-samples in moodle if you are not familiar with file system functions in C.
• Code quality and compliance to the principles of C-programming is part of the grading.
• Comment, structure and indent your code properly. 
