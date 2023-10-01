#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Wait.h"


Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a background process to finish.");
    parser().registerPositional("PID", "Process ID of the background process to wait for.");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    pid_t pid = 0;
   
   // Convert input to pid
 if ((pid = atoi(arguments().get("PID"))) <= 0)
    {
        ERROR("invalid pid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }



}