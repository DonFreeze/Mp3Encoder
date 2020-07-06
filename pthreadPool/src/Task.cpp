#include "Task.h"

using namespace threadpool;

void Task::operator()()
{
    (* funcPtr )( arg );

    if ( arg != NULL )
    {
        delete arg;
    }
}

void Task::run()
{
    (*funcPtr)( arg );
}
