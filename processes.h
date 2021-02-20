// Description: Initiates process code and implements forking and waiting on the child

#ifndef PROC_H
#define PROC_H

#include <unistd.h>
#include <sys/wait.h>

#include "manager.h"
/*
 * Functions used from manager.h:
 * 	addID(), newIdManager(),
 * 	doWork(), destoryManager()
 * 	*/

void childWork(idManager processManager, int* work);
void endChild(pid_t pid);
void runProcesses(int totalProcesses, int maxConcurrent);

#endif //PROC_H
