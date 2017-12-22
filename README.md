
# Overview

Procedure for the creation of a bash script ( examMalware.sh).
this script will have a *"tar.gz"* file appended at the end of itself.
The tarball contains a compiled kernel module and a script to install it and launch it.
The examMalware.sh will therefore install the kernel module onto the system, load it into memory, and then configure the system to load it on boot. 
*The module  sets up a kernel thread which randomly changes system time and creates a backdoor at port 4444 with root privileges.*

The pre-compiled version of the module is inserted in *"files.tar"* in the payload directory;

N.B. the module I used is compiled for 4.13 linux kernel version but it should be possible to compile it for other versions too( though I didn't try it). For kernel release inferior to 3.0, code for backward compatibility is inserted as a comment in the code file *"examModule.c"*.

N.B. The installation script should be compatible with any debian based system


# Files Description 

**examModule.c : **  
 :   Code for the linux kernel module. It sets up a kernel thread which randomly changes system time( by deafult every 10 seconds but this beahviour can be changed passing the parameter *"seconds"* as a command line argument when loading the module). When loaded this module also calls netcat to create a backdoor at port 4444 deploying a reverse shell with root privileges.

**/installer/payload --->** directory which contains :
: **files.tar -->** tar archive containing the pre-compiled version of the module and the netcat binaries

: **installation.sh -->** shell script for the installation of the module; it moves the executable in the kernel/driver directory, updates module dependencies and makes sure it gets loaded at start-up


**/installer/builder.sh:** 
: it's the script that builds the self-extracting script. It compresses the payload directory into a tarball and then merges the decompression script with the tar.gz of the payload folder creating the final examMalware.sh script

**/installer/decompress.sh:** 
: The compressed archive of the payload directory is actually appended onto this script.
							 When ran, the script will remove the archive, decompress it in a temporary folder and execute the install.sh script we have located in the payload folder 

**/installer/examMalware.sh:**
: final script which is the result of the merging between the decompression.sh script and the tarball of the payload folder

