#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <errno.h>
#include "stdlib.h"
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority process");
    parser().registerPositional("Priority", "Change the priority level for to this level");
    parser().registerPositional("PID", "Change the scheduling priority process");
    parser().registerFlag('n', "PRIORITY", "Changed process priority level"); 
}

Renice::Result Renice::exec()
{   

    const Vector<Argument *> & positionals = arguments().getPositionals();

    //Checks if the priority level is valid, if not return error
    Priority priority = atoi(*(positionals[0]->getValue()));
    if (priority < 1 || priority > 5)
    {
        ERROR("Invalid, Failed to set priority for process");   
        return InvalidArgument;
    }

    const ProcessClient process;
    const ProcessClient::Result result = process.changePriority((ProcessID)atoi(*(positionals[1]->getValue())), priority);

    return Success;
}