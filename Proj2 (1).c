#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>


/********************** Defined all the constant Values used in the program ********************/


#define MAX_SIZE 5000

#define WORD_SIZE 100

#define RIGHT_SYMBOLS 100


/************************** Defined node to store grammar rules ****************************/


struct GrammarNode{

    char left[WORD_SIZE];

    char **right;

    int rightSymbols;

};


/********************** Defined all the variables used in the program ********************/


char c;

char temp[MAX_SIZE];

int i = 0;

char** nonTerminals;

int x = 0;

int err = 0;

int numberOfNT = 0;

int j = 0;

int k = 0;

char start[WORD_SIZE];

int flag;

char check[MAX_SIZE];

int y;

char tempT[MAX_SIZE];

int z;

int NumberOfGrammarRule;

char** Terminals;

int numberOfT = 0;

struct GrammarNode *Grammar;

int l;

char **TerminalFirstList;

char **NonTerminalFirstList;

char **ReferenceList;

char firstOfEpsilon;

char firstOfZero;

char Reftemp[WORD_SIZE];

int change = 0;

int binaryArray[WORD_SIZE][WORD_SIZE];

int TerminalAdded = 0;

int NTindex = 0;

int Add = 0;

int m;

int n;

int p;

int checkNT;

int NTindex2 = 0;

int count = 0;

int Tempchange = 0;

int newIndex = 0;

int StringLength = 0;

char **NonTerminalFollowList;

int binaryArrayFollow[WORD_SIZE][WORD_SIZE];

int epsilon = 0;

int tempArray[WORD_SIZE][WORD_SIZE];

int exitloop;

int exitfor = 0;

int NewNTIndex = 0;

int GrammarIndex =-1;

int nonterminal = 0;

int point;

int StartIndex = -1;

int flag1;

int flag2;

int array2[RIGHT_SYMBOLS];


/********************** Defined all the functions used in the program ********************/


void readNonTerminals(char);

void skipSpace(char );

void putNonTerminals();

void readGrammarAndTerminals();

int isArrow(char);

void putTerminals();

void putGrammars();

void calculateFristSet();

int unionMinusEpsilon(int* , int*);

void printFirstSet();

void calculateFollowSet();

void printFollowSet();

void calculateStringLength();

int rule1(int);

int rule2(int);

int rule3(int);

int setUnion(int array1[], int array2[]);


/********************** Main Function of the program starts here ********************/


int main(int argc, char* argv[])

{

    c = getchar();

    skipSpace(c);

    c = getchar();

   

    readNonTerminals(c);

    if (err == 1){

        return 0;

    }

   

    putNonTerminals();

   

    readGrammarAndTerminals();

   

    putTerminals();

   

    putGrammars();

   

    calculateFristSet();

   

    //    printFirstSet();

   

    calculateFollowSet();

   

    //    printFollowSet();

   

   

   

   

    int task;

    if (argc < 2) {

        printf("Error: missing argument\n");

        return 1;

    }

    /* Note that argv[0] is the name of your executable

     * e.g. a.out, and the first argument to your program

     * is stored in argv[1]

     */

    task = atoi(argv[1]);

    switch (task) {

        case 1:

            calculateStringLength();

            break;

        case 2:

            printFirstSet();

            break;

        case 3:

            printFollowSet();

            break;

        default:

            printf("Error: unrecognized task number %d\n", task);

            break;

    }

   

   

   

   

   

    return 0;

}



/**************** Function for Checking for Space and ignoring them everywhere ********************/


void skipSpace(char c){

    while(isspace(c)) {

        c = getchar();

    }

    ungetc(c, stdin);

    return;

}


/**************** Reading all Non - Terminals from the first line of input ************************/

void readNonTerminals(char c){

    if (c == '#') {

        printf("There are no non-terminals in the program\n");

        err = 1;

    }else{

        while (c != '#') {

            while (!isspace(c)) {

                temp[x++] = c;

                c = getchar();

                if (c == '\n') {

                    c = getchar();

                    numberOfNT++;

                    temp[x++] = ' ';

                    skipSpace(c);

                    c = getchar();

                }

            }

            numberOfNT++;

            temp[x++] = c;

            skipSpace(c);

            c = getchar();

        }

        c = getchar();

        temp[x++] = '\0';

    }

    return;

}


/**************** Putting Non - Terminals in Non- terminals String from Temporary String *************/

void putNonTerminals(){

    nonTerminals = (char**)malloc(sizeof(char*)*numberOfNT);

    for (i = 0; i<numberOfNT; i++) {

        nonTerminals[i] = (char*)malloc(sizeof(char)*WORD_SIZE);

        for (j=0; j<WORD_SIZE && temp[k]!= ' '; j++, k++) {

            nonTerminals[i][j] = temp[k];

        }

        nonTerminals[i][j] = '\0';

        k++;

    }

   

    strcpy(start, nonTerminals[0]);

   

    //    for (i=0; i<numberOfNT; i++) {

    //        printf("The non terminals are %s\n", nonTerminals[i]);

    //    }

    return;

}


/************************ Reading the grammar rules and checking for terminals **********************/

void readGrammarAndTerminals(){

    memset(temp, 0, sizeof(temp));

    x = 0;

    y = 0;

    z = 0;

    NumberOfGrammarRule = 0;

    c = getchar();

    skipSpace(c);

    c = getchar();

   

    while (1) {

        skipSpace(c);

        c = getchar();

       

        skipSpace(c);

        c = getchar();

        while (!isspace(c)) {

            temp[x++] = c;

            c = getchar();

        }

        temp[x++] = c;

       

        c = getchar();

        skipSpace(c);

        c = getchar();

        if (isArrow(c)) {

            temp[x++] = '-';

            temp[x++] = '>';

        }

       

        c = getchar();

        skipSpace(c);

        c = getchar();

        while (c != '#') {

            while (!isspace(c)) {

                temp[x++] = c;

                check[y++] = c;

                c = getchar();

            }

            temp[x++] = c;

           

            flag = 1;

            for (i=0; i<numberOfNT; i++) {

                if(!strcmp( nonTerminals[i], check)){

                    flag = 0;

                    break;

                }

            }

           

            if (flag){

                numberOfT++;

                for (j = 0; j<=y; j++) {

                    tempT[z++] = check[j];

                }

                tempT[z++] = ' ';

            }

           

            memset(check, 0, sizeof(check));

            y = 0;

            c = getchar();

            skipSpace(c);

            c = getchar();

        }

       

        NumberOfGrammarRule++;

        temp[x++] = '#';

       

        skipSpace(c);

        c = getchar();

        c = getchar();

        if (c == '#'|| c == '\n' || c == ' ') {

            c = getchar();

            skipSpace(c);

            c = getchar();

            if (c == '#') {

                tempT[z++] = '\0';

                return;

            }

        }

    }

    return;

}


/******************* Putting Terminals in Terminals String from Temporary String *****************/

void putTerminals(){

    k = 0;

    Terminals = (char**)malloc(sizeof(char*)*(numberOfT*2));

    for (i = 0; i<numberOfT; i++) {

        Terminals[i] = (char*)malloc(sizeof(char)*WORD_SIZE);

        for (j=0; j<WORD_SIZE && tempT[k]!= ' '; j++, k++) {

            Terminals[i][j] = tempT[k];

        }

        Terminals[i][j] = '\0';

        k++;

    }

   

   

   

    //    for (i=0; i<numberOfT; i++) {

    //        printf("The terminals are %s\n", Terminals[i]);

    //    }

    return;

}



/**************** Function to Check for Arrow in Grammars and skip them ************************/


int isArrow(char c){

    flag = 0;

   

    if (c == '-') {

        c = getchar();

        skipSpace(c);

        c = getchar();

        if (c == '>') {

            flag = 1;

        }

    }

    return flag;

}



/**************** Putting Grammars in Data Structure from Temporary String ********************/

void putGrammars(){

    Grammar = (struct GrammarNode*)malloc(sizeof(struct GrammarNode)*NumberOfGrammarRule);

    k = 0;

    for (i =0 ; i<NumberOfGrammarRule; i++) {

        Grammar[i].right = (char **)malloc(sizeof(char*)*RIGHT_SYMBOLS);

        Grammar[i].rightSymbols = 0;

        for (j = 0; j<WORD_SIZE && temp[k] != ' ' ; j++, k++) {

            Grammar[i].left[j] = temp[k];

        }

        Grammar[i].left[j] = '\0';

        k++;

       

        while (temp[k] == ' ' || temp[k] == '-' || temp[k] == '>') {

            k++;

        }

       

        for (j = 0; j<RIGHT_SYMBOLS && temp[k] != '#'; j++, k++) {

            Grammar[i].right[j] = (char *)malloc(sizeof(char*)*WORD_SIZE);

            for (l = 0; l<WORD_SIZE && (temp[k] != ' ' && temp[k] != '\n'); l++, k++) {

                Grammar[i].right[j][l] = temp[k];

            }

            Grammar[i].right[j][l] = '\0';

            Grammar[i].rightSymbols++;

        }

       

        if (Grammar[i].rightSymbols == 0) {

            Grammar[i].right[0] = (char*)malloc(sizeof(char)*WORD_SIZE);

            Grammar[i].right[0][0] = '#';

            Grammar[i].right[0][1] = '\0';

            Grammar[i].rightSymbols++;

        }

        k++;

    }

   

    //    for (i=0; i<NumberOfGrammarRule; i++) {

    //        for (j=0; j<Grammar[i].rightSymbols; j++) {

    //            printf("The grammars are %s %s %d\n", Grammar[i].left, Grammar[i].right[j], Grammar[i].rightSymbols);

    //        }

    //    }

    return;

}


void calculateFristSet(){

    /********** Initializing all terminals first list and putting the corresponding terminals ***********/

   

    TerminalFirstList = (char **)malloc(sizeof(char*)*numberOfT);

    for (i = 0; i<numberOfT; i++) {

        TerminalFirstList[i] = (char*)malloc(sizeof(char)*WORD_SIZE);

        for (j=0; j<WORD_SIZE && Terminals[i][j] != '\0'; j++) {

            TerminalFirstList[i][j] = Terminals[i][j];

        }

    }

   

    /*********************** Making First of Epsilon Epsiolon and Zero Zero *****************************/

    firstOfEpsilon = '#';

    firstOfZero = '0';

   

    /******** Initializing all non - terminals first list and keeping them blank Initially***************/

   

    NonTerminalFirstList = (char **)malloc(sizeof(char*)*NumberOfGrammarRule);

    for (i = 0; i<NumberOfGrammarRule; i++) {

        NonTerminalFirstList[i] = (char*)malloc(sizeof(char)*WORD_SIZE);

        for (j = 0; j<WORD_SIZE; j++) {

            // Keeping the First Set of Non - Terminals Empty

        }

    }

   

    //    for (i = 0; i<numberOfT; i++) {

    //            printf("Terminal first list are %s\n",TerminalFirstList[i]);

    //    }

    //

    //    for (i = 0; i<numberOfNT; i++) {

    //        printf("Non - Terminal first list initially are %s\n",NonTerminalFirstList[i]);

    //    }

   

    /************ Creating the reference set of terminals and epsilon and EndOfFile *********************/

   

    ReferenceList = (char **)malloc(sizeof(char*)*(numberOfT+2));   // +2 for epsilon and EOF

    ReferenceList[0] = (char *)malloc(sizeof(char)*(WORD_SIZE));

    ReferenceList[1] = (char *)malloc(sizeof(char)*(WORD_SIZE));

    ReferenceList[0][0] = '#';

    ReferenceList[0][1] = '\0';

    ReferenceList[1][0] = '$';

    ReferenceList[1][1] = '\0';

    for (i = 2; i < (numberOfT + 2); i++) {

        ReferenceList[i] = (char *)malloc(sizeof(char)*(WORD_SIZE));

        for (j = 0; j<WORD_SIZE && Terminals[i-2][j] != '0'; j++) {

            ReferenceList[i][j] = Terminals[i-2][j];

        }

        ReferenceList[i-2][j] = '\0';

    }

   

   

    //    for (i = 0; i<(numberOfT+2); i++) {

    //        printf("reference list before sorting is %s\n",ReferenceList[i]);

    //    }

   

    /****** Sorting the reference set of terminals and epsilon and EndOfFile alphabetically*************/

   

    for (i = 2; i<(numberOfT + 1); i++) {

        for (j=i+1; j<(numberOfT + 2); j++) {

            if (strcmp(ReferenceList[i], ReferenceList[j])>0) {

                strcpy(Reftemp, ReferenceList[i]);

                strcpy(ReferenceList[i], ReferenceList[j]);

                strcpy(ReferenceList[j], Reftemp);

            }

        }

    }

   

    /** Removing the duplicate terminals from the reference set of terminals and epsilon and EndOfFile **/

   

    j = 2;

    for (i = 3; i<(numberOfT+2); i++) {

        if(strcmp(ReferenceList[i] , ReferenceList[j])){

            j++;

            ReferenceList[j] = ReferenceList[i];

        }

    }

    numberOfT = j-1;

   

    //    for (i = 0; i<(numberOfT+2); i++) {

    //        printf("reference list are %s\n",ReferenceList[i]);

    //    }

   

    for (i = 0; i<NumberOfGrammarRule; i++) {

        for (j = 0; j<(numberOfT+2); j++) {

            binaryArray[i][j] = 0;

        }

    }

   

    /************************************ Calculating the First Set ***********************************/

   

    change = 1;

   

    while (change) {

        change = 0;

       

        for (i = 0; i<NumberOfGrammarRule; i++) {

           

            for (n = 0; n<NumberOfGrammarRule; n++) {

                for (p = n+1; p<NumberOfGrammarRule; p++) {

                    if (!strcmp(Grammar[n].left , Grammar[p].left)) {

                        checkNT = unionMinusEpsilon(binaryArray[n], binaryArray[p]);

                        checkNT = unionMinusEpsilon(binaryArray[p], binaryArray[n]);

                    }

                }

            }

           

           

           

            if (Grammar[i].rightSymbols == 0) {

                binaryArray[i][0] = 1;

                change = 1;

            }

           

           

           

           

           

            j = 0;

            TerminalAdded = 0;

            for (k = 0; k < (numberOfT+2) ; k++) {

                if(!strcmp(Grammar[i].right[j],ReferenceList[k])){

                    if (binaryArray[i][k]==1) {

                        Tempchange = 0;

                        TerminalAdded = 0;

                    }else{

                        binaryArray[i][k] = 1;

                        TerminalAdded = 1;

                        Tempchange = 1;

                    }

                }

            }

           

            if (Tempchange) {

                change = 1;

            }

           

            if (Tempchange) {

                Tempchange = 0;

                continue;

            }

           

            NTindex = -1;

            for (k = 0; k<NumberOfGrammarRule; k++) {

                if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                    NTindex = k;

                }

            }

           

            Add = 1;

            while (Add) {

                Add = 0;

                if (NTindex != -1) {

                    Add = unionMinusEpsilon(binaryArray[i], binaryArray[NTindex]); // ADD THE FIRST LIST OF NON TERMINAL TO THE NON TERMINAL IN LHS

                    if (Add == 1) {

                        change = 1;

                    }

                   

                    if ((binaryArray[i][0] == 1) && (Add == 0))  {

                        if (binaryArray[NTindex][0]==1) {

                            j++;

                            if (j<Grammar[i].rightSymbols) {

                                for (z = 2; z<(numberOfT+2); z++) {

                                    if (!strcmp(Grammar[i].right[j], ReferenceList[z])) {

                                        binaryArray[i][z] = 1;

                                        TerminalAdded = 1;

                                    }

                                }

                                if (TerminalAdded == 0) {

                                    for (z = 0; k<NumberOfGrammarRule; z++) {

                                        if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                                            NTindex2 = k;

                                        }

                                    }

                                    Add = unionMinusEpsilon(binaryArray[i], binaryArray[NTindex2]);

                                }

                               

                                if (Add) {

                                    change = 1;

                                }

                            }

                        }

                    }

                   

                    if ((binaryArray[i][0] == 1) && (Add == 1)) {

                        j++;

                        if (j<Grammar[i].rightSymbols) {

                            binaryArray[i][0] = 0;

                            for (z = 2; z<(numberOfT+2); z++) {

                                if (!strcmp(Grammar[i].right[j], ReferenceList[z])) {

                                    binaryArray[i][z] = 1;

                                    TerminalAdded = 1;

                                }

                            }

                           

                            if (TerminalAdded == 0) {

                                for (z = 0; k<NumberOfGrammarRule; z++) {

                                    if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                                        NTindex2 = k;

                                    }

                                }

                                Add = unionMinusEpsilon(binaryArray[i], binaryArray[NTindex2]);

                            }

                            if (Add) {

                                change = 1;

                            }

                        }

                    }

                }

            }

        }

    }

   

    for (i = 0; i<(NumberOfGrammarRule); i++) {

        for (j = 0; j<(numberOfT+2); j++) {

            if (binaryArray[i][j]) {

                strcat(NonTerminalFirstList[i], ReferenceList[j]);

                strcat(NonTerminalFirstList[i], ", ");

            }

        }

    }

   

    //    for (i=0; i<NumberOfGrammarRule; i++) {

    //      printf("Final First List of Non - terminal no %d is %s\n", i+1, NonTerminalFirstList[i]);

    //    }

   

   

    return;

}


/****************** Printing the FIRST Set of All Non - Terminals as they appear in First Section of Grammar Rules **************/


void printFirstSet(){

    //    for (i=0; i<NumberOfGrammarRule; i++) {

    //        printf("Final First List of Non - terminal %s is %s\n", Grammar[i].left, NonTerminalFirstList[i]);

    //    }

   

    for (i = 0; i<numberOfNT; i++) {

        newIndex = 0;

        StringLength = 0;

        for (j = 0; j<NumberOfGrammarRule; j++) {

            if(!strcmp(nonTerminals[i], Grammar[j].left)){

                newIndex = j;

            }

        }

       

        StringLength = (int )strlen(NonTerminalFirstList[newIndex]);

       

        NonTerminalFirstList[newIndex][StringLength - 2] = ' ';

        NonTerminalFirstList[newIndex][StringLength - 1] = '\0';

       

        printf("FIRST(%s) = { %s}\n", nonTerminals[i], NonTerminalFirstList[newIndex]);

    }

    return;

}




/************************************ Adding FIRST(X) to FIRST(A) for A -> X *****************************************/


int unionMinusEpsilon(int* array1, int* array2){

    flag = 0;

    for (m = 0; m<(numberOfT+2); m++) {

        if ((array1[m]==0) && (array2[m]==0)) {

            array1[m] = 0;

        }

        else if((array1[m]==0) && (array2[m]==1)) {

            array1[m] = 1;

            flag = 1;

        }

        else if((array1[m]==1) && (array2[m]==0)) {

            array1[m] = 1;

        }

        else{

            array1[m] = 1;

        }

    }

    return flag;

}


/************************************ Calculating the Follow Set ***********************************/


void calculateFollowSet(){

    change = 0;

    NonTerminalFollowList = (char **)malloc(sizeof(char*)*NumberOfGrammarRule);

    for (i = 0; i<NumberOfGrammarRule; i++) {

        NonTerminalFollowList[i] = (char*)malloc(sizeof(char)*WORD_SIZE);

        for (j = 0; j<WORD_SIZE; j++) {

            // Keeping the Follow Set of Non - Terminals Empty

        }

    }

   

    for (i = 0; i<NumberOfGrammarRule; i++) {

        for (j = 0; j<(numberOfT+2); j++) {

            binaryArrayFollow[i][j] = 0;

        }

    }

   

    change = 1;

   

    while (change) {

        change = 0;

       

        for (i = 0; i<NumberOfGrammarRule; i++) {

           

            for (n = 0; n<NumberOfGrammarRule; n++) {

                for (p = n+1; p<NumberOfGrammarRule; p++) {

                    if (!strcmp(Grammar[n].left , Grammar[p].left)) {

                        checkNT = unionMinusEpsilon(binaryArrayFollow[n], binaryArrayFollow[p]);

                        checkNT = unionMinusEpsilon(binaryArrayFollow[p], binaryArrayFollow[n]);

                    }

                }

            }

            // Rule 1

            if (!strcmp(start, Grammar[i].left)) {

               

                if (!binaryArrayFollow[i][1]) {

                    binaryArrayFollow[i][1] = 1;

                    Tempchange = 1;

                }

            }

           

            if (Tempchange) {

                change = 1;

                Tempchange = 0;

                continue;

            }

           

            // Rule 2

            j = 0;

            while (j<Grammar[i].rightSymbols-1) {

                j++;

            }

            NTindex = -1;

            GrammarIndex = -1;

            for (k = 0; k<NumberOfGrammarRule; k++) {

                if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                    NTindex = k;

                    for (l = 0; l<NumberOfGrammarRule; l++) {

                        if (!strcmp(Grammar[i].left, Grammar[l].left)) {

                            GrammarIndex = l;

                        }

                    }

                }

            }

           

            if (NTindex != -1 && GrammarIndex != -1) {

                Add = unionMinusEpsilon(binaryArrayFollow[NTindex], binaryArrayFollow[GrammarIndex]);

                if (Add) {

                    change = 1;

                    Add = 0;

                }

            }

           

            //Rule 3

            epsilon = 1;

            exitfor = 0;

            NTindex = -1;

            nonterminal = 0;

           

            for (j = 0; j<Grammar[i].rightSymbols; j++) {

               

                for (k = 0; k<NumberOfGrammarRule; k++) {

                    if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                        NTindex = k;

                        nonterminal = 1;

                    }

                }

               

                if (nonterminal) {

                    l = j+1;

                    while ((l>j) && (l<Grammar[i].rightSymbols)) {

                        exitloop = 1;

                        for (y = 0; y<NumberOfGrammarRule; y++) {

                            if (!strcmp(Grammar[i].right[l], Grammar[y].left)) {

                                if (!binaryArray[y][0]) {

                                    epsilon = 0;

                                }

                                exitloop = 0;

                            }

                        }

                        l++;

                    }

                }

               

                GrammarIndex = -1;

                if (NTindex != -1 && nonterminal == 1) {

                    if ((epsilon == 1) && (exitloop == 0)) {

                        for (x = 0; x<NumberOfGrammarRule; x++) {

                            if (!strcmp(Grammar[i].left, Grammar[x].left)) {

                                GrammarIndex = x;

                            }

                           

                            Add = unionMinusEpsilon(binaryArrayFollow[NTindex], binaryArrayFollow[GrammarIndex]);

                        }

                        if (Add) {

                            change = 1;

                            Add = 0;

                            exitfor = 1;

                        }

                    }

                }

               

                if (exitfor) {

                    break;

                }

            }

           

           

            for (j = 0; j<Grammar[i].rightSymbols; j++) {

                NTindex = -1;

                NewNTIndex = -1;

                nonterminal = 0;                                                                                        //Rule 4

                for (k = 0; k<NumberOfGrammarRule; k++) {

                    if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                        NTindex = k;

                        nonterminal = 1;

                    }

                }

               

                if (!nonterminal) {

                    continue;

                }

               

                l = j+1;

                if (l<Grammar[i].rightSymbols) {

                    for (y = 0; y<NumberOfGrammarRule; y++) {

                        if (!strcmp(Grammar[i].right[l], Grammar[y].left)) {

                            NewNTIndex = y;

                        }

                    }

                   

                    if (NTindex != -1 && NewNTIndex != -1) {

                        for (n = 0; n<NumberOfGrammarRule; n++) {

                            for (p = 0; p<(numberOfT+2); p++) {

                                tempArray[n][p] = 0;

                            }

                        }

                        for (z = 1; z<(numberOfT+2); z++) {

                            tempArray[NewNTIndex][z] = binaryArray[NewNTIndex][z];

                        }

                       

                        Add = unionMinusEpsilon(binaryArrayFollow[NTindex], tempArray[NewNTIndex]);

                       

                        if (Add) {

                            change = 1;

                            Add = 0;

                            exitfor = 1;

                        }

                    }

                    StartIndex = -1;

                    if (NTindex != -1){

                        for (y = 0; y<(numberOfT+2); y++) {

                            if (!strcmp(Grammar[i].right[l], ReferenceList[y])) {

                                StartIndex = y;

                            }

                        }

                        if (StartIndex != -1) {

                            if (!binaryArrayFollow[NTindex][StartIndex]) {

                                binaryArrayFollow[NTindex][StartIndex] = 1;

                                change = 1;

                            }

                        }

                    }

                }

            }

           

           

            for (j = 0; j<Grammar[i].rightSymbols; j++) {

                NTindex = -1;

                NewNTIndex = -1;

                nonterminal = 0;                                                                                        //Rule 5

                for (k = 0; k<NumberOfGrammarRule; k++) {

                    if (!strcmp(Grammar[i].right[j], Grammar[k].left)) {

                        NTindex = k;

                        nonterminal = 1;

                    }

                }

               

                if (!nonterminal) {

                    continue;

                }

               

                l = j+1;

                if (l<Grammar[i].rightSymbols) {

                    while ((l>j) && (l<Grammar[i].rightSymbols)) {

                        exitloop = 1;

                        for (y = 0; y<NumberOfGrammarRule; y++) {

                            if (!strcmp(Grammar[i].right[l], Grammar[y].left)) {

                                if (!binaryArray[y][0]) {

                                    epsilon = 0;

                                    NewNTIndex = y;

                                    exitloop = 0;

                                    break;

                                }

                            }

                        }

                        if (!exitloop) {

                            break;

                        }

                        l++;

                    }

                   

                    if (NTindex != -1 && NewNTIndex != -1) {

                        for (n = 0; n<NumberOfGrammarRule; n++) {

                            for (p = 0; p<(numberOfT+2); p++) {

                                tempArray[n][p] = 0;

                            }

                        }

                        for (z = 1; z<(numberOfT+2); z++) {

                            tempArray[NewNTIndex][z] = binaryArray[NewNTIndex][z];

                        }

                       

                        Add = unionMinusEpsilon(binaryArrayFollow[NTindex], tempArray[NewNTIndex]);

                       

                        if (Add) {

                            change = 1;

                            Add = 0;

                            exitfor = 1;

                        }

                    }
/*
                    StartIndex = -1;

                    if (NTindex != -1){

                        for (y = 0; y<(numberOfT+2); y++) {

                            if (!strcmp(Grammar[i].right[l], ReferenceList[y])) {

                                StartIndex = y;

                            }

                        }

                        if (StartIndex != -1) {

                            if (!binaryArrayFollow[NTindex][StartIndex]) {

                                binaryArrayFollow[NTindex][StartIndex] = 1;

                                change = 1;

                            }

                        }

                    }   */

                }

            }

           

           

           

        }

    }

   

   

   

   

   

   

   

    for (i = 0; i<(NumberOfGrammarRule); i++) {

        for (j = 0; j<(numberOfT+2); j++) {

            if (binaryArrayFollow[i][j]) {

                strcat(NonTerminalFollowList[i], ReferenceList[j]);

                strcat(NonTerminalFollowList[i], ", ");

            }

        }

    }

   

    //    for (i=0; i<NumberOfGrammarRule; i++) {

    //        printf("Final Follow List of Non - terminal %s is %s\n", Grammar[i].left, NonTerminalFollowList[i]);

    //    }

   

    return;

}



/****************** Printing the FOLLOW Set of All Non - Terminals as they appear in First Section of Grammar Rules **************/


void printFollowSet(){

    //    for (i=0; i<NumberOfGrammarRule; i++) {

    //        printf("Final First List of Non - terminal %s is %s\n", Grammar[i].left, NonTerminalFirstList[i]);

    //    }

   

    for (i = 0; i<numberOfNT; i++) {

        newIndex = 0;

        StringLength = 0;

        for (j = 0; j<NumberOfGrammarRule; j++) {

            if(!strcmp(nonTerminals[i], Grammar[j].left)){

                newIndex = j;

            }

        }

       

        StringLength = (int )strlen(NonTerminalFollowList[newIndex]);

       

        NonTerminalFollowList[newIndex][StringLength - 2] = ' ';

        NonTerminalFollowList[newIndex][StringLength - 1] = '\0';

       

        printf("FOLLOW(%s) = { %s}\n", nonTerminals[i], NonTerminalFollowList[newIndex]);

    }

    return;

}


/************************ Calulating if Non terminals can produce a string of length 1 ***************************/


void calculateStringLength(){

   

    int array[RIGHT_SYMBOLS];

    int length = 0;

    int array3[RIGHT_SYMBOLS];

   

    for (i = 0; i<NumberOfGrammarRule; i++) {

        array2[i] = 0;

    }

   

    for (i = 0; i<NumberOfGrammarRule; i++) {

        if (binaryArray[i][0]) {

            array[i] = 1;

        }

        else{

            array[i] = 0;

        }

    }

 

   

   

    for (i=0; i<NumberOfGrammarRule; i++) {

       

       

       

       

        if (Grammar[i].rightSymbols==1){

           

            if (!strcmp(Grammar[i].right[0], "#")) {

                continue;

            }

           

            for (j = 0; j<numberOfT; j++) {

                if (!strcmp(Grammar[i].right[0], Terminals[j])) {

                    length = 1;

                }

            }

           

       

            if (!length) {

                length = rule2(i);

            }

        }

 

        if (Grammar[i].rightSymbols>1 && length == 0) {

            length = rule3(i);

        }

     

        if (length == 1) {

            for (j = 0; j<numberOfNT; j++) {

                if (!strcmp(Grammar[i].left,nonTerminals[j])) {

                    array2[j] = 1;

                }

            }

           

            length = 0;

 //           array2[i] = 1;

        }

    }

 /*

    for (i = 0; i<NumberOfGrammarRule; i++) {

        for (j = i+1; j<NumberOfGrammarRule; j++) {

            if (!strcmp(Grammar[i].left,Grammar[j].left)) {

                if (array2[i] == 0 && array2[j] == 0) {

                    array2[i] = 0;

                    array2[j] = 0;

                }

                else if (array2[i] == 0 && array2[j] == 1) {

                    array2[i] = 1;

                    array2[j] = 1;

                }

                else if (array2[i] == 1 && array2[j] == 0) {

                    array2[i] = 1;

                    array2[j] = 1;

                }

                else{

                    array2[i] = 1;

                    array2[j] = 1;

                }

            }

        }

    }

   

   */

    for (i = 0; i<numberOfNT; i++) {

        if (array2[i] == 1) {

            printf("%s : YES\n", nonTerminals[i]);

        }

        else{

            printf("%s : NO\n", nonTerminals[i]);

        }

    }

   

    return;

}


int rule1(int i){

    flag = 0;

    if (Grammar[i].rightSymbols==1) {

        for (j = 0; j<numberOfT; j++) {

            if (!strcmp(Grammar[i].right[0], Terminals[j])) {

                flag = 1;

            }

        }

    }

    return flag;

}


int rule2(int i){

    flag1 = 0;

    NTindex = -1;

    if (Grammar[i].rightSymbols == 1) {

       

        for (j=i; j<NumberOfGrammarRule; j++) {

            if (!strcmp(Grammar[i].right[0], Grammar[j].left)) {

                NTindex = j;

                break;

            }

        }

        if (NTindex == -1) {

            for (j=0; j<NumberOfGrammarRule; j++) {

                if (!strcmp(Grammar[i].right[0], Grammar[j].left)) {

                    NTindex = j;

                    break;

                }

            }

        }

       

       

   


        while (NTindex<NumberOfGrammarRule) {

       

       

        if (Grammar[NTindex].rightSymbols == 1) {

            flag1 = rule1(NTindex);

           

            if (!flag1) {

                flag1 = rule2(NTindex);

            }

            else{

                break;

            }

        }

//        else{

//            flag1 = rule3(NTindex);

//            if (flag1) {

//                break;

//            }

       

       

//        }

            NTindex++;

        }


   

    }

    return flag1;

}


int rule3(int i){

    flag2 = 0;

    int count = 0;

    int generateEpsilon = 1;

    int index = 0;

   

    for (j = 0; j<Grammar[i].rightSymbols; j++) {

        for (k = 0; k<=numberOfT; k++) {

            if (Terminals[k] == NULL) {

                continue;

            }

            if (!strcmp(Grammar[i].right[j], Terminals[k])) {

                count++;

                break;

            }

        }

    }

   

    if (count>=2) {

        flag2 = 0;

        return flag2;

    }

   

    if (count == 1) {

        for (j = 0; j<Grammar[i].rightSymbols; j++) {

            for (k = 0; k<NumberOfGrammarRule; k++) {

                if (!strcmp(Grammar[k].left, Grammar[i].right[j])) {

                    if (!binaryArray[k][0]) {

                        generateEpsilon = 0;

                    }

                }

            }

        }

        if (!generateEpsilon) {

            flag2 = 0;

            return flag2;

        }

        else{

            flag2 = 1;

            return flag2;

        }

    }

   

    count = 0;

    for (j = 0; j<Grammar[i].rightSymbols; j++) {

        for (k = 0; k<NumberOfGrammarRule; k++) {

            if (!strcmp(Grammar[k].left, Grammar[i].right[j])) {

                if (!binaryArray[k][0]) {

                    index = k;

                    count++;

                    break;

                }

            }

        }

    }

   

    if (count>=2) {

        flag2 = 0;

        return flag2;

    }

   

    if (count == 1) {

       

        flag2 = array2[index];

        return flag2;

    }

    return flag2;

}
