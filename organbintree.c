/**
*
    DONALD RICHARDS
    ASSIGNMENT COP3502-P4-OrganBinTree
    11-8-2013

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20                            //---------------------------------------------------------
#define BLOODTYPESIZE 4                                                                             //
                                                                                                    //
typedef struct {                                                                                    //
    int month;                                                                                      //
    int day;                                                                                        //
    int year;                                                                                       //
} dateT;                                                                                            //
                                                                                                    //
typedef struct {                                                                                    //
    int hour;                                                                    // PROVIDED BY PDF
    int minute;                                                                                     //
} timeT;                                                                                            //
                                                                                                    //
typedef struct {                                                                                    //
    char * name;                                                                                    //
    char * organName;                                                                               //
    char bloodtype[BLOODTYPESIZE];                                                                  //
    dateT dateAdded;                                                                                //
    timeT timeAdded;                                                                                //
    int organReceived;                                                                              //
} organT;                                   //--------------------------------------------------------

struct node {                               //--------------------------------------------------------
    organT * data;                                                                                  //
    struct node * left;                                                         // STRUCT TO TRAVERSE TREE
    struct node * right;                                                                            //
};                                          //--------------------------------------------------------

organT * inputPerson();                     //-----------------------------------------------------------
struct node * makeNode(organT * data);                                                                 //
int compare(organT * this,organT * otherOrgan);                                                        // DECLARE FUNCTIONS 
void printPerson(organT * Person);                                                                     //
void runApp ();                                                                          // MAIN FUNCTION
void insert(struct node ** root, organT * insOrg );                                                       //
void searchTree(organT ** matchFound , struct node * tree , char * organ, char * bloodtype);           //
void freeAll(struct node ** tree);         //------------------------------------------------------------

void runApp(){
    int n;
    scanf("%d",&n);  //--------------------------------------------------------------------------------------- NUMBER OF PEOPLE 
    struct node * tree ;
    int i, o;

    for ( i = 0 ; i < n ; i++){
        if ( i == 0 ) tree = makeNode(inputPerson()); //------------------------------------------------------ IF TREE IS EMPTY MAKE TREE INSERT PERSON
        else{
            insert(&tree,inputPerson());  //------------------------------------------------------------------ INSERT PERSON INTO TREE
        }
    } // END OF FOR LOOP

    scanf("%d",&o); //----------------------------------------------------------------------------------------- NUMBER OF ORGANS

    for ( i = 0 ; i < o ; i++ ){ //---------------------------------------------------------------------------- FOR EACH PERSON LOOP
        char * organTemp = (char *)malloc(sizeof(char)*20);
        char * bloodtypeTemp = (char *)malloc(sizeof(char)*20);
        organT * matchFound = NULL ;

        scanf("%s %s",organTemp,bloodtypeTemp); //------------------------------------------------------------- INPUT ORGAN AND TYPE 

        searchTree(&matchFound, tree,organTemp,bloodtypeTemp); //---------------------------------------------- SEARCH TREE FOR MATCH
        printPerson((matchFound));  //------------------------------------------------------------------------- MATCH FOUND, SOMEONE WILL LIVE!

        free(organTemp);     //-------------------------------------------------------------------------------- FREE TEMP MEMORY 
        free(bloodtypeTemp); //-------------------------------------------------------------------------------- 
    } // END OF FOR LOOP

    freeAll(&tree);  //---------------------------------------------------------------------------------------- FREE DYNAMICALLY ALLOCATED MEMORY
} // END OF runApp

organT * inputPerson(){ //------------------------------------------------------------------------------------- PUT PERSON AND -> DATA 
    char temp;
    char * name = (char *)malloc(sizeof(char)*20);  //--------------------------------------------------------- DYNAMICALLY ALLOCATE MEMORY
    char * organName = (char *)malloc(sizeof(char)*20); //----------------------------------------------------- DYNAMICALLY ALLOCATE MEMORY
    char bloodtype[BLOODTYPESIZE];

    int month;
    int day;
    int year;
    int hour;
    int minute;

    scanf("%s%s%s%d%c%d%c%d%d%c%d",name,organName,bloodtype,&month,&temp,&day,&temp,&year,&hour,&temp,&minute);

    organT  * Person = (organT *)malloc(sizeof(organT));  //--------------------------------------------------- DYNAMICALLY ALLOCATE MEMORY
    Person->name = (char *) malloc(sizeof(char)*(strlen(name)+2)); //------------------------------------------ DYNAMICALLY ALLOCATE MEMORY FOR NAME
    Person->organName = (char *) malloc(sizeof(char)*(strlen(organName)+2)); //-------------------------------- DYNAMICALLY ALLOCATE MEMORYOrganName
    Person->organReceived = 0;              //----------------------------------------------------------------- DEFAULT VALUE OF ORGAN RECIEVED

    strcpy(Person->name, name);             //----------------------------------------------------------------- STRING COPY TO NAME
    strcpy(Person->organName, organName);   //----------------------------------------------------------------- STRING COPY TO ORGAN NAME
    strcpy(Person->bloodtype, bloodtype);   //----------------------------------------------------------------- STRING COPY BLOD TYPE

    Person->dateAdded.month = month;        //----------------------------------------------------------------- MONTH VALUE ADDED TO PERSON
    Person->dateAdded.day= day;             //----------------------------------------------------------------- DAY VALUE ADDED TO PERSON 
    Person->dateAdded.year = year;          //----------------------------------------------------------------- YEAR VALUE ADDED TO PERSON
    Person->timeAdded.minute= minute;       //----------------------------------------------------------------- MINUTE VALUE ADDED TO PERSON
    Person->timeAdded.hour = hour;          //----------------------------------------------------------------- HOUR VALUE ADDED TO PERSON

    free(name);                             //----------------------------------------------------------------- FREE DYNAMICALLY ALLOCATED MEMORY
    free(organName);                        //----------------------------------------------------------------- FREE DYNAMICALLY ALLOCATED MEMORY
    return Person;                          //----------------------------------------------------------------- RETURN PERSON FOR COMPARE AND PRINT
} // END OF INPUT PERSON

struct node * makeNode(organT * data){      //----------------------------------------------------------------- STRUCT FOR NODE 
    struct node * matchFound = (struct node * )malloc(sizeof(struct node));
    matchFound->data = data ;
    matchFound->left = NULL ;
    matchFound->right= NULL ;
    return matchFound ;
} // END OF MAKE node

void insert(struct node ** root, organT * insOrg ){ //------------------------------------------------------------ INSERT INTO TREE
    if (*root == NULL){
       (*root) = makeNode(insOrg) ;
        }
    else if (compare((*root)->data, insOrg)==1){ //--------------------------------------------------------------- INSERT TO RIGHT
        insert(&((*root)->right), insOrg);
        }
    else if (compare(((*root)->data), insOrg)==0){ //------------------------------------------------------------- INSERT TO LEFT
        insert(&((*root)->left), insOrg);
        }
    else{
        return;
        }
} // END OF INSERT 

void searchTree(organT ** matchFound , struct node * tree , char * organ, char * bloodtype){
    if ( tree != NULL ){    //-------------------------------------------------------------------------------- TRAVERSE TREE 
        searchTree(matchFound , tree->left, organ, bloodtype);
        if (strcmp(organ, tree->data->organName)==0 &&      //------------------------------------------------ IF MATCH 
            strcmp(bloodtype, tree->data->bloodtype)==0 &&
            tree->data->organReceived == 0 && *matchFound == NULL ) {

            tree->data->organReceived = 1 ;
            *matchFound = tree->data;
            return;
            }
        searchTree(matchFound , tree->right,organ,bloodtype); //----------------------------------------------- FIND OTHER MATCHES 
        }
} // END OF SEARCH TREE

int compare(organT * this,organT * otherOrgan){                             // -------------------------------- COMPARES ORGAN THEN DATE 
    if (strcmp(this->organName, otherOrgan->organName)!=0) return 1 ;                                 //------- Found this code online 
    else{                                                                                             //------- But it made so much sense I 
        if (strcmp(this->bloodtype, otherOrgan->bloodtype)!=0 ) return 1 ;                            //------- found myself using the format
        else{                                                                                         //------- So not to plagerize I'm referencing 
            if (this->dateAdded.year < otherOrgan->dateAdded.year) return 1 ;                         //------- it here. 
            else if (this->dateAdded.year > otherOrgan->dateAdded.year) return 0 ;
            else{
                if ( this->dateAdded.month < otherOrgan->dateAdded.month ) return 1 ;
                else if ( this->dateAdded.month > otherOrgan->dateAdded.month) return 0 ;
                else{
                    if (this->dateAdded.day < otherOrgan->dateAdded.day) return 1 ;
                    else if (this->dateAdded.day > otherOrgan->dateAdded.day) return 0 ;
                    else{
                        if (this->timeAdded.hour < otherOrgan->timeAdded.hour ) return 1 ;
                        else if (this->timeAdded.hour > otherOrgan->timeAdded.hour ) return 0 ;
                        else{
                            if (this->timeAdded.minute < otherOrgan->timeAdded.minute ) return 1 ;
                            else if (this->timeAdded.minute > otherOrgan->timeAdded.minute ) return 0 ;
                            else {
                                if ( strcmp(this->name, otherOrgan->name) == 0 ){
                                    return -1 ;
                                }
                                else{
                                    return  0 ;
                                }
                            } // END OF MINUTE
                        } // END OF HOUR
                    } // END OF DAY
                } // END OF MONTH
            } // END OF YEAR
        } // END OF BLOOD TYPE
    } // END OF ORGAN NAME 
} // END OF COMPARE

void printPerson(organT * Person){
    if (Person != NULL){  //--------------------------------------------------------------------------- IF PERSON EXIST PRINT PERSON AND ORGAN 
        printf("%s %s\n",Person->name,Person->organName);
    }
    else{
        printf("No Match Found\n");  //---------------------------------------------------------------- NO ONE FOUND 
        }
} // END OF PRINT PERSON

void freeAll(struct node ** tree ){      //------------------------------------------------------------
    if ( *tree != NULL ){                                                                            // 
        freeAll(&((*tree)->left));                                                                   //
        freeAll(&((*tree)->right));                                                                  //
        free((*tree)->data->name);                           // FREE ALL DYNAMICALLY ALLOCATED MEMORY
        free((*tree)->data->organName);                                                              //
        free((*tree)->data);                                                                         //
        free(*tree);                    //-------------------------------------------------------------
        }
} // END OF FREE ALL 

int main(){                             //---------------------------------------------------- MAIN
    runApp();                           //---------------------------------------------------- RUNS APP 
} // END OF MAIN