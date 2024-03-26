# myFind Program

## Description
This program enables a user to parallelly find different files in a folder without the usage of the Linux command `find` as a child process.

### Usage
./myfind [-R] [-i] searchpath filename1 [filename2] …[filenameN]


The main program accepts the arguments `<searchpath>` and `<filename1 .. N>`. It supports a variable number of arguments (= variable number of filenames to look for) and allows the options `-R` and `-i` to be placed anywhere in the arguments list.

#### Options
- `-R`: Switches myfind to recursive mode to find all matching files in and below the searchpath folder. Otherwise, the files are only searched in the searchpath folder.
- `-i`: Performs a case-insensitive search.

#### Parameters
- `searchpath`: Can be an absolute or a relative path.
- `filename`: Only filenames as plain string are supported. No need for paths, subpaths, or wildcards.

### Example
./myfind ./ test.txt test.doc test

Here, myfind searches for the 3 files in the current working directory in parallel.

### Implementation Details
The main program forks a child-process for each filename and looks for the file in the defined searchpath. In case a file is found, an entry in the following output format will be printed to stdout (unsorted; but readable in full lines). See the code comments above `main` for how this requirement was achieved.

#### Output Format
<pid>: <filename>: <complete-path-to-found-file>\n

- `<pid>`: Process-id of the child-process that finds the entry.
- `<filename>`: References the filename that was passed into the main program as an argument.
- `<complete-path-to-found-file>`: Absolute path to the found file.

### Hints
- The parent-process must react on the termination of child-processes to prevent a zombie apocalypse.
- Use `getopt()` for argument parsing.
- Check the code samples in Moodle if you are not familiar with file system functions in C.
- Code quality and compliance to the principles of C-programming is part of the grading. Comment, structure, and indent your code properly.

