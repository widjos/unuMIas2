#include "operation.h"


Operation::Operation()
{

}

void Operation::createDisk(struct  dataValues auxInput){
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


void Operation::cleanStr(char input[]){

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


void Operation::writeDiskFile( struct  dataValues auxInput){
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


void Operation::writeFile(int size,struct dataValues auxInput){

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


string Operation::getDirs(char input[]){

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


int Operation::getRandomId(){

    return rand() % 100 + 5000;
}


void Operation::showMBR(char input[]){

    struct baseDisk temp;
    std::ifstream file (input, std::ios::binary);
     file.read ((char*) &temp, sizeof(temp));


     char* dt = ctime(&temp.date);

     cout << "Fecha: " << dt << endl;
     cout << "Formatp: "<<temp.disk_fit << endl;
     cout << "Tama;o : "<<temp.mbr_tamano << endl;
     cout << "Id :     "<<temp.mbr_disk_signature <<endl;

}
