#ifndef OPERATION_H
#define OPERATION_H
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string.h>
#include <algorithm>
#include <ctime>

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
        char  type[216];
        char  name[216];

    } ;

    struct baseDisk {
      int       mbr_tamano;
      int       mbr_disk_signature;
      time_t    date;
      char      disk_fit;
      int       mbr_partition1;
      int       mbr_partition2;
      int       mbr_partition3;
      int       mbr_partition4;

    };

    struct partition{
      char part_status;
      char part_type;
      char part_fit;
      int  part_start;
      int  part_size;
      char part_name[16];

    };


    struct ExtDisk {

        char     part_status;
        char     part_fit;
        int      part_start;
        int      part_size;
        int      part_next;
        char     part_name[16];
    };


    static int K ;
    static void createDisk(struct  dataValues auxInput);
    static void cleanStr(char input[]);
    static void writeDiskFile( struct  dataValues auxInput);
    static void writeFile(int size, struct  dataValues auxInput);
    static string getDirs(char input[]);
    static void showMBR(char input[]);

private:

    static int getRandomId();


};

#endif // OPERATION_H
