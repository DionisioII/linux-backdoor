
# Overview

Files and scripts for the creation of a bash script ( examMalware.sh). this script will install a kernel module onto the system, loads it into memory, and configures the system to load it on boot. 
The module sets up a kernel thread which randomly changes system time and creates a backdoor at port 4444 with root privileges.

The pre-compiled version of the module is inserted in the files.tar in payload directory;

N.B. the module I used is compiled for 4.13 linux kernel version but it should be possible to compile it for other versions too( though I did'n try it). For kernel release inferior to 3.0, code for backward compatibility is inserted as a comment in the code file examModule.c.


# Files Description 

examModule.c --> Code for the linux kernel module. It sets up a kernel thread which randomly changes system time( by 
				 deafult every 10 seconds but this beahviour can be changed passing the parameter "seconds" as a command line argument when loading the module). When loaded this module also calls netcat to create a backdoor at port 4444 with root privileges.

/installer/payload -> directory which contains:

					files.tar --> tar containing the pre-compiled version of the module and the netcat binaries

					installation.sh --> shell script for the installation of the module; it moves the executable in the kernel/driver directory, updates module dependencies and makes sure it gets loaded at start-up

/installer/builder.sh --> it's the script that builds the self-extracting script. It compresses the payload directory
						  into a tarball and then merges the decompression script with the tar.gz of the payload folder creating the final examMalware.sh script

/installer/decompress.sh --> The compressed archive of the payload directory is actually appended onto this script.
							 When ran, the script will remove the archive, decompress it in a temporary folder and execute the install.sh script we have located in the payload folder 





