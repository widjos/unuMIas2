#include "operation.h"


Operation::Operation()
{

}

void Operation::createDisk(struct  dataValues auxInput)
{
    cout << "fit :" << auxInput.fit << "\n" << endl;
    cout << "The path is: " << auxInput.path << "\n" << endl;
    cout << "SIze :" << auxInput.size << "\n" << endl;
    cout << "UNit :" << auxInput.unit  << "\n" << endl;


    if(strlen(auxInput.path) != 0  || auxInput.size > 0){

               writeDiskFile(auxInput);

    }
    else
        cout << "Hace falta especificar la ruta de su disco o el tamano no es permitido \n" << endl;

}

void Operation::cleanStr(char input[])
{

    int index;
    int index2=0;
    char cae[256];
    strcpy(cae,input);

    for(index = 0 ; index < sizeof (cae) ; index++){

        if(cae[index] != '\"'  ){
            input[index2] = cae[index];
            index2++;
        }


    }
}

void Operation::writeDiskFile( struct  dataValues auxInput)
{
    int K = 1024;
    int t ;

    if( strcmp(auxInput.unit,"K") == 0){
         t =K * auxInput.size ;

         writeFile(t, auxInput);

    }
    else /*if(strcmp(auxInput.unit,"M") == 0/*|| strlen(auxInput.unit) == 0)*/{
         t =K * K * auxInput.size;
         writeFile(t, auxInput);

    }
}

void Operation::writeFile(int size,struct dataValues auxInput)
{

    static struct baseDisk mbr ;
    int status;
    string tempFit;
    string command = "sudo mkdir -p ";
    command += getDirs(auxInput.path);
    status = system(command.c_str());

    if(strlen(auxInput.fit) == 0)  mbr.disk_fit= 'B';
    else  mbr.disk_fit= auxInput.fit[0];

    mbr.mbr_tamano = size;
    mbr.date = time(0);
    mbr.mbr_disk_signature = getRandomId();

    if(status==-1)//creating a directory
        {
           cout << "cant create the directory \n"<< endl ;
            cerr<<"Error :  "<<strerror(errno)<<endl;
        }
        else
        {
           ofstream diskFile (auxInput.path);//writing to a file
            if (diskFile.is_open())
            {

                diskFile.write((char*)&mbr, sizeof(mbr));
                for(int i = 0 ; i < size; i++)
                    diskFile << 0 ;

                diskFile.close();
                cout << "disco creado con exitp" << endl;
                showMBR(auxInput.path);
            }
            else
                cout << "Unable to open file";
        }


}

string Operation::getDirs(char input[])
{

    string temp ;
    for(int i = 0 ; i < strlen(input) ; i++ ){
        if(input[i] == '/'){
            int  index =i;

             string temp1;
            do{
                temp1 += input[index];
                index++;
                if(input[index] == '\0')
                    break;
            }while((input[index] != '/'));

            if(input[index] != '\0'){
                temp += temp1;
            }

        }


    }



    return temp;
}

int Operation::getRandomId()
{
    return rand() % 100 + 5000;
}

void Operation::showMBR(char input[])
{

    struct baseDisk temp;
    std::ifstream file (input, std::ios::binary);
     file.read ((char*) &temp, sizeof(temp));


     char* dt = ctime(&temp.date);

     cout << "Fecha: " << dt << endl;
     cout << "Formatp: "<<temp.disk_fit << endl;
     cout << "Tama;o : "<<temp.mbr_tamano << endl;
     cout << "Id :     "<<temp.mbr_disk_signature <<endl;

}

void Operation::removeDisk(char input[])
{

    int status=remove(input);
        if(status==0)
            cout<<"file "<< input<<" deleted successfully..!!\n";
        else
        {
            cout<<"Unable to delete file "<< input<<"\n";
            perror("Error Message ");
        }

}

void Operation::administrerDisk(struct  dataValues auxInput)
{

    if(auxInput.add > 0  && strlen(auxInput.delet) != 0)
    {
        cout << "Imposible  crear la particion con las instruciones delete y add" << endl;
    }else
    {
       if(auxInput.add > 0)
       {
           cout << "Se agregara espacio a una particion" << endl;
       }
       else if (strlen(auxInput.delet) != 0)
       {
           cout << "Se eliminara una particion "<< endl;
       }
       else 
       {
           writePartition(auxInput, 1);
           cout << "Se creara una nueva particion " << endl;
       }

    }

}

void Operation::writePartition(struct  dataValues auxInput, int option)
{
    FILE * fp;
    struct partition partToWrite, partTemporal;
    bool canWrite = 0;
    int numberPartition = 0;
    cout <<"path : " <<auxInput.path << endl;
    fp = fopen (auxInput.path , "r+");


    if(fp == nullptr)
    {
      cout << "The Disk doesnt exist to create wath do you want" << endl;
      cerr<<"Error :  "<<strerror(errno)<<endl;
    }
      else
    {

        int t = 1024;
        switch(option)
        {
            case 1:
               // Leer el mbr para ver si existe un espacio para escribir la particion
                struct baseDisk mbrTemp;
                fseek(fp, 0, SEEK_SET);
                fread(&mbrTemp, sizeof (struct  baseDisk), 1, fp);

                if(strlen(auxInput.type) == 0)
                    partToWrite.part_type = 'P';
                else
                    partToWrite.part_type = auxInput.type[0];



                if(mbrTemp.mbr_partition1.part_start == 0)
                    numberPartition = 1;
                else if(mbrTemp.mbr_partition2.part_start == 0)
                    numberPartition = 2;
                else if(mbrTemp.mbr_partition3.part_start == 0)
                    numberPartition = 3;
                 else if(mbrTemp.mbr_partition4.part_start == 0)
                    numberPartition = 4;
                else{
                    cout << "NO hay spacio para escribir la particion" << endl;
                    return;
                }

        
                if(  auxInput.size > 0 &&   strlen(auxInput.name) > 1)
                {



                    strcpy(partToWrite.part_name , auxInput.name);
                    if((strlen(auxInput.fit) == 0))
                    {
                      partToWrite.part_fit = 'W';
                    }
                    else
                    {
                        partToWrite.part_fit= auxInput.fit[0];
                    }
                    if( strcmp(auxInput.unit,"B") == 0)
                        t = auxInput.size;
                    else if (strcmp(auxInput.unit,"M") == 0)
                        t = t* t * auxInput.size;
                    else
                        t = t * auxInput.size;

                     partToWrite.part_size = t;    // Tamaño en bytes


                     partToWrite.part_status = 'F';  // Significa que no esta en uso

                     switch(numberPartition){
                     case 1:
                            partToWrite.part_start = sizeof (baseDisk)+1;
                            mbrTemp.mbr_partition1.part_start = partToWrite.part_start;
                            cout << "Se escribio una nueva particion en el espacion para 1" << endl;
                         break;
                     case 2:
                            fseek(fp, mbrTemp.mbr_partition1.part_start, SEEK_SET);
                            fread(&partTemporal, sizeof (struct  partition), 1, fp);
                            partToWrite.part_start = partTemporal.part_start + partTemporal.part_size +1 ;
                            mbrTemp.mbr_partition2.part_start = partToWrite.part_start;
                            cout << "Se escribio una nueva particion en el espacion para 2" << endl;

                         break;
                     case 3:

                         fseek(fp, mbrTemp.mbr_partition2.part_start, SEEK_SET);
                         fread(&partTemporal, sizeof (struct  partition), 1, fp);
                         partToWrite.part_start = partTemporal.part_start + partTemporal.part_size +1 ;
                         mbrTemp.mbr_partition3.part_start = partToWrite.part_start;
                         cout << "Se escribio una nueva particion en el espacion para 3" << endl;

                         break;
                     case 4:
                         fseek(fp, mbrTemp.mbr_partition3.part_start, SEEK_SET);
                         fread(&partTemporal, sizeof (struct  partition), 1, fp);
                         partToWrite.part_start = partTemporal.part_start + partTemporal.part_size +1 ;
                         mbrTemp.mbr_partition4.part_start = partToWrite.part_start;
                         cout << "Se escribio una nueva particion en el espacion para 4" << endl;

                         break;
                      default:

                         break;
                     }


                    // Se escribe de nuevo el mbr
                    fseek(fp, 0, SEEK_SET);
                    fwrite(&mbrTemp , sizeof (struct baseDisk), 1,fp);

                    //Aqui se escribe la particion en el disco
                    fseek(fp, partToWrite.part_start, SEEK_SET);
                    fwrite(&partToWrite , sizeof (struct partition), 1,fp);

                    if(fwrite != 0)
                          cout<< "se escribio la particion "<< endl;
                     else
                          cout << "no se pudo escribir"<< endl;
                    
                    fclose(fp);
                    showReportDisk(auxInput.path);
                    
                }else
                {
                 cout << "no se puede crear una nueva particion" << endl;
                }
                break;
            case 2:
    
                break;
            case 3:
                break;
        }
    }
}


void Operation::showReportDisk(char* path)
{
    FILE * fp;
    struct baseDisk tempMbr;
        fp = fopen (path, "r+");
        if(fp == nullptr)
        {
            cout << "Error" << endl;
            return;
        }
         else
        {
           fseek(fp,0, SEEK_SET);
           fread(&tempMbr, sizeof (struct  baseDisk), 1, fp);
           cout << "datos del disco mbr " << endl;

           cout << "date: " << ctime(&tempMbr.date) << endl;
           cout <<  "tamano: " << tempMbr.mbr_tamano << endl;
           cout <<  "p1: " << tempMbr.mbr_partition1.part_start << endl;
           cout <<  "p2: " << tempMbr.mbr_partition2.part_start << endl;
           cout <<  "p3: " << tempMbr.mbr_partition3.part_start << endl;
           cout <<  "p3: " << tempMbr.mbr_partition4.part_start << endl;
           fclose(fp);
           if(tempMbr.mbr_partition1.part_start != 0)
                printPartitionRep(tempMbr.mbr_partition1.part_start,path);
           if(tempMbr.mbr_partition2.part_start != 0)
                printPartitionRep(tempMbr.mbr_partition2.part_start,path);
           if(tempMbr.mbr_partition3.part_start != 0)
                printPartitionRep(tempMbr.mbr_partition3.part_start,path);
           if(tempMbr.mbr_partition4.part_start != 0)
                printPartitionRep(tempMbr.mbr_partition4.part_start,path);


        }
}


void Operation::printPartitionRep(int direccion, char * dir)
  {
    FILE * fp;
    struct partition partToRead;
    fp = fopen (dir, "r+");
    if(fp == nullptr)
    {
        cout << "Error" << endl;
        return;
    }
     else
    {
        fseek(fp, direccion, SEEK_SET);
         fread(&partToRead , sizeof (struct partition), 1 , fp);

        cout << "Datos de la particion: " << partToRead.part_name << endl;
        cout <<  "Fit: " <<partToRead.part_fit << endl;
        cout <<  "Size:" <<partToRead.part_size << endl;
        cout <<  "TYpe:" <<partToRead.part_type << endl;
        cout <<  "INicia:" <<partToRead.part_start << endl;
        fclose(fp);
    }

}
