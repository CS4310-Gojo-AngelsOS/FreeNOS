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
    parser().setDescription("Changes process priority based on PID");
    parser().registerPositional("Priority", "New priority for the process");
    parser().registerPositional("PID", "PID of the changed process");
    parser().registerFlag('n', "PRIORITY", "Changed process priority"); 
}

Renice::Result Renice::exec()
{   

    const Vector<Argument *> & positionals = arguments().getPositionals();

    //validates the priority level (Error if not between 1 and 5)
    Priority priority = atoi(*(positionals[0]->getValue()));
    if (priority < 1 || priority > 5)
    {
        ERROR("Not Valid - priority level must be between 1 to 5");   
        return InvalidArgument;
    }

    const ProcessClient process;
    const ProcessClient::Result result = process.changePriority((ProcessID)atoi(*(positionals[1]->getValue())), priority);

    return Success;
}