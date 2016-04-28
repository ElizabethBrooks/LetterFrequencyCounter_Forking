/*
    Name: Elizabeth Brooks
    File: CS470 Lab2
    Date Modified: o4/28/2016
*/
//Imports
#include <stdio.h>
#include <unistd.h>
//Main method
int main(int argc, char **argv)
{
    //Initialize variables for counting character frequency
    char characterList[52] = {'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z'};
    int ch, i, r, j, k, p; //Variables for tracking current index positions
    pid_t pid; //Process ID for forks
    int letterFrequency = 0; //Counter for letter pair frequency
    char fileNameInput[44]; //Character array for file name input
    FILE * userFile = 0;
    printf("Please enter the name and extension of a file to count letter frequencies: "); //Request user input for file name
    scanf("%s", fileNameInput); //Store file name input
    userFile = fopen(fileNameInput, "r"); //Open input file
    if(userFile) { //Verify the file exists
        printf("Frequency Table:\n"); //Prepare to print the frequency table while forking
        for(i=0, j=0, k=1, p=0; i < 26; i++, j++, k++, p+=2){ //Create 26 forks to search for each letter pair
            pid = fork(); //Fork for each character pair
            if(pid < 0){
                printf("Error creating process.. exiting program.");
                return 1; //Exit program
            }else if(pid == 0){ //Child process
                while(ch!=EOF){ //While file has characters
                    ch = fgetc(userFile); //Retrieve next character in the input file
                    if ((ch == characterList[j]) || (ch == characterList[k])) //Check if the character is the current letter pair
                        letterFrequency++; //Increment frequency counter
                } //End while
                printf("%c-%c: %i\n", characterList[p], characterList[p+1], letterFrequency); //Display current character pair frequency
                letterFrequency = 0; //Reset frequency counter
                fseek(userFile,0,SEEK_SET); //Reset to file start
                return 0; //Exit child process
            }else{ //Parent process
                wait(NULL); //Wait for child process
            } //End else
        } //End for
    } else { //Return error if file does not exist
        printf("File not found... exiting program.\n"); 
        return 0; //Exit program
    }//End else
    fclose(userFile); //Close the  input file
    return 1; //Final return statement
}//End main
