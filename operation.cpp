#include "operation.h"


Operation::Operation()
{

}

void Operation::createDisk(struct  dataValues auxInput){
      cout << "fit :" << auxInput.fit << "\n" << endl;
    cout << "The path is: " << auxInput.path << "\n" << endl;
    cout << "SIze :" << auxInput.size << "\n" << endl;
    cout << "UNit :" << auxInput.unit  << "\n" << endl;

    /*
    if(strlen(auxInput.path) != 0  || auxInput.size > 0){
       if(strlen(auxInput.unit) != 0){
           if(strlen(auxInput.fit) == 0){

               if(mkdir(auxInput.path,0777)==-1)//creating a directory
                   {
                      cout << "cant create the directory \n"<< endl ;

                   }
                   else
                   {
                       ofstream write ("pathname/file.txt");//writing to a file
                       if (write.is_open())
                       {
                           write << "This is a line."<<endl;
                           write << "This is another line."<<endl;
                           write.close();
                       }
                       else
                           cout << "Unable to open file";
                   }

           }else{

           }



       }else{

       }

    }
    else
        cout << "Hace falta especificar la ruta de su disco o el tamano no es especifico \n" << endl;


    if(mkdir("pathname",0777)==-1)//creating a directory
        {
           cout << "cant create the directory \n"<< endl ;

        }
        else
        {
            ofstream write ("pathname/file.txt");//writing to a file
            if (write.is_open())
            {
                write << "This is a line."<<endl;
                write << "This is another line."<<endl;
                write.close();
            }
            else
                cout << "Unable to open file";
        }

}



*/
}

void Operation::cleanStr(char input[]){
    int c;
    int index;
    char ca[256];

    for(index = 0 ; index < sizeof (input) ; index++){
        c = input[index];
        if(c != '\"')
            ca[index] = c;
    }

    cout << "csdd : "<< ca << endl;
 }
