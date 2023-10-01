#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Wait.h"


Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a background process to finish.");
    parser().registerPositional("PROCESS_ID", "Process ID of the background process to wait for.");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{

    int processID = 0;

    // Converts process ID into integer and checks if it is valid
    // if not valid returns error
    if ((processID = atoi(arguments().get("PROCESS_ID"))) <= 0) {
        
        ERROR("Process ID Invalid" << arguments().get("PROCESS_ID") << "'");
        return IOError;
    }

    int status; 

    // Uses waitpid function to suspend execution
    if (waitpid(processID, &status, 0) == -1) {

        ERROR("Failed to wait:" << strerror(errno));
        return IOError;
    }

    return Success; 
}