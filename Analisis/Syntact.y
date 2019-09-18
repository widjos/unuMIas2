
%{
#include <stdio.h>
#include <stdlib.h>



//int yylex (void);

extern int yylineno;    //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna;     //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext;    //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
int yylex (void);
void yyerror (const char  *);


%}


%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
char TEXT2 [256];
//class NodoAST *nodito;
}


//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output  "parser.cpp"
%define parse.error verbose
%locations

//TERMINALES DE TIPO TEXT, SON STRINGS
%token<TEXT> Value_Int;
%token<TEXT> Value_Double;
%token<TEXT> Value_Char;
%token<TEXT> Value_String;
%token<TEXT> Id;

%token<TEXT>   exit_command;
%token<TEXT>   Mkdisk;
%token<TEXT>   Rmdisk;
%token<TEXT>   Fdisk;
%token<TEXT>   Mount;
%token<TEXT>   Unmount;
%token<TEXT>   Report;
%token<TEXT>   Execute;
%token<TEXT>   Size;
%token<TEXT>   Fit;
             
%token<TEXT>   Bf;
%token<TEXT>   Ff;
%token<TEXT>   Wf;
%token<TEXT>   Unit;
%token<TEXT>   Kbytes;
%token<TEXT>   Mbytes;
%token<TEXT>   Bytes;
             
%token<TEXT>   Path;
%token<TEXT>   Type;
%token<TEXT>   Primary;
%token<TEXT>   Extended;
             
%token<TEXT>   Logic;
%token<TEXT>   Delete;
%token<TEXT>   Fast;
%token<TEXT>   Full;
%token<TEXT>   Name;
%token<TEXT>   Add;
%token<TEXT>   Mbr;
  
%token<TEXT>   Ebr;
%token<TEXT>   Disc;
%token<TEXT>   Identify;
%token<TEXT>   Url;




/*------------- NONTerminals ------------------*/


%type<TEXT> S      Line ;
%type<TEXT> MK     RM       F       M  UM  REP  EXE ;
%type<TEXT> MAKE   FIT
%type<TEXT> UBYTE  FOPTION  STR_VAL REP_TYPE   P_OPTION  ;
%type<TEXT> DTYPE  TPARTITION ;


%start S

%%

S:   S Line                                                                       {;}
   |   Line                                                                       {;}

  ;


Line:   Mkdisk  MK                                                                 { printf("Make Comand executed ");        }
     |  Rmdisk  RM                                                                 { printf("Removed disk  ");      }
     |  Fdisk   F                                                                  { printf("administer disk command ");  }
     |  Mount   M                                                                  { printf("mount   disk command ");     }
     |  Unmount UM                                                                 { printf("unmount disk command ");     }
     |  Report  REP                                                                { printf("report  disk command ");     }
     |  Execute RM                                                                 { printf("execute disk command ");     }                    
     |  exit_command                                                               { printf("Saliendo del gestor de discos \n");   exit(EXIT_SUCCESS);                  }
     |  error                                                                      {   }
;


MK: MK MAKE                                                                        {;}         
    | MAKE                                                                         {;}
;


MAKE: Size '=' Value_Int                                     {   }
    | Path '=' P_OPTION                                      {   }
    | Unit '=' UBYTE   
    | Fit  '=' FOPTION 
;

RM: Path '=' P_OPTION                                           {printf(" Path ");}
;

F: F FIT                                                        {;}        
  | FIT                                                         {;}
  
;

FIT:    Size    '=' Value_Int                                                     {;}  
   |    Unit    '=' UBYTE                                                         {;}
   |    Path    '=' P_OPTION                                                      {;}
   |    Type    '=' TPARTITION                                                    {;}
   |    Fit     '=' FOPTION                                                       {;}
   |    Delete  '=' DTYPE                                                         {;}  
   |    Name    '=' Id                                                            {;}
   |    Add     '=' Value_Int                                                     {;}      
;



M:  Path '=' P_OPTION    Name '=' Id                                             { printf(" Path and Name ");} 
   | Name '=' Id         Path '=' P_OPTION                                       { printf(" Name and Path ");}
   | error
;

UM: Identify '=' Id                                                                { printf(" Identify ");     }
    | error 
;

REP: Identify   '=' Id  Path '=' P_OPTION  Name '=' REP_TYPE                       { printf(" Name , Path , Id ");     } 
    | error       
;


EXE: Path    '=' P_OPTION                                                          { printf(" Path ");  }
    | error
;





STR_VAL: Value_String                                                               {;}
        | Id                                                                         {;}
        | error                                                                      {;}   
        
;

UBYTE: Kbytes                                                                 {$=$1;}
      | Mbytes                                                                {$=$1;}
      | Bytes                                                                 {$=$1;}
;

FOPTION:  Bf                                                                          {;}
        | Ff                                                                         {;}
        | Wf                                                                         {;}
        | error                                                                      {;} 
;


REP_TYPE: Mbr                                                                { printf(" Mbr  "); }
         | Disc                                                               { printf(" Disc "); } 
         | error                                                              {}    
;         


P_OPTION: Value_String                                                        { $=$1; }
         | Url                                                                { $=$1; }    
 ; 

DTYPE: Fast                                                                   {}
      | Full                                                                  {}

 ;

TPARTITION: Primary                                                           {}
          | Extended                                                          {}  
          | Logic                                                             {}
;



%%


struct dataValues {

    int    size;
    char[] fit;
    char   unit;
    char * path;

}

dataValues auxStruct;


void yyerror(const char* mens)
{
    fprintf(stderr , mens,  "%s\n"  );
}

