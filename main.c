#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc < 4)
        return 0;

    Node *head = NULL;

    FILE *taskFile = fopen(argv[1], "r");
    FILE *dataFile = fopen(argv[2], "r");
    FILE *printFile = fopen(argv[3], "w");

    if (taskFile == NULL)
    {
        puts("File ..");
        exit(1);
    }

    if (dataFile == NULL)
    {
        puts("File ..");
        exit(1);
    }

    if (printFile == NULL)
    {
        puts("File ..");
        exit(1);
    }

    int nrTasks[5], nrTeams;

    fscanf(dataFile, "%d", &nrTeams);

    // task 1
    for (int i = 0; i < 5; i++)
    {
        fscanf(taskFile, "%d", &nrTasks[i]);
    }

    if (nrTasks[0] == 1)
    {
        head = createList(dataFile, nrTeams);
        if (nrTasks[1] == 0)
            printList(head, printFile);
    }

    // task 2

    if (nrTasks[1] == 1)
    {
        deleteTeams(&head, nrTeams);
        printList(head, printFile);
    }

    // task 3

    Node *stackTop8 = NULL;
    if (nrTasks[2] == 1)
    {
        createMatches(head, &stackTop8, printFile);
    }

    // task 4

    if (nrTasks[3] == 1)
    {
        Tree *root = NULL;
        Node *i = stackTop8;

        while (i != NULL)
        {
            root = insert(root, i->val);
            i = i->next;
        }
        fprintf(printFile, "\nTOP 8 TEAMS:\n");
        inorder(root, printFile);
    }

    // eliberez lista si stack ul cu top 8
    deleteStack(&head);
    deleteStack(&stackTop8);

    return 0;
}