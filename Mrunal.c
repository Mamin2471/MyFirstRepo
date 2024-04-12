/*
* FILE : f8.cpp
* PROJECT : Focused Assignment 8
* PROGRAMMER : Mrunal Amin
* FIRST VERSION : 29-03-2024
* DESCRIPTION : This program takes command line arguments to specify how many times to write a given text to a file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

// Constant for maximum characters in string and maximum path length
const int MAX_CHARS_IN_STRING = 21;
const int MAX_PATH_LENGTH = MAX_CHARS_IN_STRING + 1 + MAX_CHARS_IN_STRING + 1;

//structure to hold input data
struct MyData 
{
    int howMany;
    char theText[MAX_CHARS_IN_STRING] = { '\0' };
    char directoryPath[MAX_CHARS_IN_STRING] = { '\0' };
    char filename[MAX_CHARS_IN_STRING] = { '\0' };

};

int main(int argc, char* argv[]) 
{
    //count the number of commmand line arguments
    int count = 0;
    while (argv[count] != NULL) 
    {
        count++;
    }

    if (count != 5) 
    {
        printf("Error: Incorrect number of arguments.\n");
        return 1;
    }

    //Put the command line variables into the MyData struct.
    struct MyData myArgs;
    myArgs.howMany = atoi(argv[1]);
    strncpy(myArgs.theText, argv[2], sizeof(myArgs.theText) - 1);
    myArgs.theText[sizeof(myArgs.theText) - 1] = '\0';
    strncpy(myArgs.directoryPath, argv[3], sizeof(myArgs.directoryPath) - 1);
    myArgs.directoryPath[sizeof(myArgs.directoryPath) - 1] = '\0';
    strncpy(myArgs.filename, argv[4], sizeof(myArgs.filename) - 1);
    myArgs.filename[sizeof(myArgs.filename) - 1] = '\0';

    //calulate the length of the full path and allocate memory for it
    int fullPathLength = sizeof(myArgs.directoryPath) + sizeof("/") + sizeof(myArgs.filename) + 1;
    char* fullPath = new char[fullPathLength];
   
    //create the full path by concatenating the directory and filename
    strcpy(fullPath, myArgs.directoryPath);
    strcat(fullPath, "/");
    strcat(fullPath, myArgs.filename);

    //open file for writing
    FILE* file = fopen(fullPath, "w");
    if (file == NULL) 
    {
        printf("can't open file\n");
        return 1;
    }

    //write theText howMany times into the file
    for (int i = 0; i < myArgs.howMany; ++i) 
    {
        if (fprintf(file, "%s\n", myArgs.theText) < 0) 
        {
            printf("can't write file\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}