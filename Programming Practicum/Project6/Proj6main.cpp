//	Author: Edward Plesa, Spring 2021, CS211, Proj. 6

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "MyList.h"
#include "Island.h"
#include "FileList.h"

class ArchipelagoExpedition
{
private:
    // Create the Data Members for the Archipelago Network here
    FileList* files;
    Island* islands;
    int size;

public:

    // Use a constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition()
    {
        files = new FileList();
        islands = new Island[10];
        size = 10;
    }
    
    ~ArchipelagoExpedition() {
    	for (int i = 0; i < size; i++) {
        	islands[i].resetAdj();
        }
        delete[] islands;
        islands = nullptr;
        files->resetFiles();
        delete files;
        files = nullptr;
    }

    bool bfs(int b, MyList& IslandQueue) {
        while (IslandQueue.isEmpty() == false) {
            int a = IslandQueue.top();
            IslandQueue.popFront();

            for (int i = 0; i < islands[a - 1].getEdges(); i++) {
                int c = islands[a - 1].getNthIsland(i);
                if (islands[c - 1].getVisited() == -1) {
                    islands[c - 1].setVisited(a);
                    if (c == b) {
                        return true;
                    }
                    IslandQueue.pushBack(c);
                }
            }
        }
        return false;
    }

    void breadthFirstSearch(int x, int y) {
        MyList IslandQueue;

        for (int i = 0; i < size; i++) {
            islands[i].setVisited(-1);
        }

        IslandQueue.pushBack(x);

        if (bfs(y, IslandQueue) == false) {
            cout << "You can NOT get from island " << x << " to island " << y << endl;
            return;
        }
        else {
            cout << "You can get from island " << x << " to island " << y << endl;
            MyList pathList;
            int currentIsland = y;
            pathList.pushFront(currentIsland);
            do {
                currentIsland = islands[currentIsland - 1].getVisited();
                pathList.pushFront(currentIsland);
            } while (currentIsland != x);

            if (pathList.isEmpty() == false) {
                cout << "shortest path from " << x << " to " << y << ": ";
                pathList.printBFS();
            }
            cout << endl;
        }
    }


    // The main loop for reading in input
    void processCommandLoop(FILE* inFile)
    {
        char  buffer[300];
        char* input;

        input = fgets(buffer, 300, inFile);   // get a line of input

        // loop until all lines are read from the input
        while (input != NULL)
        {
            // process each line of input using the strtok functions 
            char* command;
            command = strtok(input, " \n\t");

            printf("*%s*\n", command);

            if (command == NULL)
                printf("Blank Line\n");

            else if (strcmp(command, "q") == 0) {
                for (int i = 0; i < size; i++) {
                    islands[i].resetAdj();
                }
                delete[] islands;
                islands = nullptr;
                files->resetFiles();
                delete files;
                files = nullptr;
                exit(1);
            }

            else if (strcmp(command, "?") == 0)
                showCommands();

            else if (strcmp(command, "t") == 0)
                doTravel();

            else if (strcmp(command, "r") == 0)
                doResize();

            else if (strcmp(command, "i") == 0)
                doInsert();

            else if (strcmp(command, "d") == 0)
                doDelete();

            else if (strcmp(command, "l") == 0)
                doList();

            else if (strcmp(command, "f") == 0)
                doFile();

            else if (strcmp(command, "#") == 0)
                ;

            else
                printf("Command is not known: %s\n", command);

            input = fgets(buffer, 300, inFile);   // get the next line of input

        }
    }

    void showCommands()
    {
        printf("The commands for this project are:\n");
        printf("  q\n");
        printf("  ?\n");
        printf("  #\n");
        printf("  t <int1> <int2>\n");
        printf("  r <int>\n");
        printf("  i <int1> <int2>\n");
        printf("  d <int1> <int2>\n");
        printf("  l\n");
        printf("  f <filename>\n");
    }

    void doTravel()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \n\t");


        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }


        printf("Performing the Travel Command from %d to %d\n",
            val1, val2);

        if (val1 < 1 || val1 > size || val2 < 1 || val2 > size) {
            cout << "Invalid value for island\n";
            return;
        }

        breadthFirstSearch(val1, val2);
    }

    void doResize()
    {
        int val1 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }



        if (val1 > 0) {
            printf("Performing the Resize Command with %d\n", val1);

            for (int i = 0; i < size; i++) {
                islands[i].resetAdj();
            }
            delete[] islands;

            size = val1;

            islands = new Island[size];
        }
    }

    void doInsert()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        const int num = val1 - 1;

        if (val1 < 1 || val1 > size || val2 < 1 || val2 > size) {
            cout << "Invalid value for island\n";
            return;
        }
        
        if (val1 == val2) {
        	cout << "Can not add ferry ride to self\n";
        	return;
        }

        cout << "Performing the Insert Command for " << val1 << endl;

        islands[num].insertEdge(val2);

        //inUse++;
    }

    void doDelete()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        cout << "Performing the Delete Command for " << val1 << endl;
        const int num = val1 - 1;

        if (val1 < 1 || val1 > size || val2 < 1 || val2 > size) {
            cout << "Invalid value for island\n";
            return;
        }

        islands[num].removeEdge(val2);
    }

    void doList()
    {
        cout << "Displaying the adjacency list:\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << " -->"; islands[i].printEdges();
            cout << endl;
        }
    }

    void doFile()
    {
        // get a filename from the input
        char* fname = strtok(NULL, " \r\n\t");
        if (fname == NULL)
        {
            printf("Filename expected\n");
            return;
        }

        printf("Performing the File command with file: %s\n", fname);

        // next steps:  (if any step fails: print an error message and return ) 
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns
        if (files->searchFile(fname) == false) {

            files->pushBackFile(fname);

            FILE* pFile;
            pFile = fopen(fname, "r");

            if (pFile == NULL) {
                cout << "Cannot open the file\n";
            }
            else {
                processCommandLoop(pFile);
                fclose(pFile);

                files->deleteFile(fname);
            }            
        }
        else {
        	cout << "File is already in use\n";
        }
        
    }
};

int main(int argc, char** argv)
{
    // set up the varqiable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf("\nEnter commands at blank line\n");
    printf("    (No prompts are given because of f command)\n");
    islandData.processCommandLoop(inFile);

    printf("Goodbye\n");
    return 0;
}

