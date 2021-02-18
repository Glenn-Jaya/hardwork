#ifndef PROC_H
#define PROC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "manager.h"

void childWork(idManager processManager, int* work);
void endChild(pid_t pid);

void runProcesses(int totalProcesses, int maxConcurrent);

#endif //PROC_H
