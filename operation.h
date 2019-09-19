#ifndef OPERATION_H
#define OPERATION_H
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string.h>
using namespace std;

class Operation
{
public:
    Operation();

    struct dataValues {

        int   size;
        char  unit[216];
        char  path[216];
        char  fit[216];

    } ;

    int K = 1024;
    static void createDisk(struct  dataValues auxInput);
    static void cleanStr(char input[]);
};

#endif // OPERATION_H
