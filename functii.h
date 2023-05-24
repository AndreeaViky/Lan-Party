#ifndef FUNCTII_H
#define FUNCTII_H

#include <stdio.h>

struct Player
{
    char *firstName;
    char *secondName;
    int points;
};
typedef struct Player Player;

struct Team
{
    char *name;
    int nrPlayers;
    Player *players;
};
typedef struct Team Team;

// structura listei
struct Node
{
    Team val;
    struct Node *next;
};
typedef struct Node Node;

// structura cozii
struct Queue
{
    Node *front, *rear;
};
typedef struct Queue Queue;

struct Tree
{
    Team val;
    struct Tree *left, *right;
};
typedef struct Tree Tree;

Player readPlayer(FILE *fileName);
Team readTeam(FILE *file);
void readFromFile(Team **teamList);
void displayData(Team *teamList);

Node *createList(FILE *file, int nrTeams);
void printList(Node *head, FILE *file);

int getRemainingTeams(int n);
void deleteOneTeam(Node **head, float score);
float totalScore(Team team);
void deleteTeams(Node **head, int nrTeams);

// task 3
Queue *createQueue();
Team copyTeam(Team team);
void enQueue(Queue *q, Team team);
int isEmpty(Queue *q);
void deleteQueue(Queue *q);
Team deQueue(Queue *q);

// stiva
void push(Node **top, Team v);
Team pop(Node **top);
// int isEmpty(Node *top);
int top(Node *top);
// punem meciurile in coada
void addMatch(Node *head, Queue *q);
void createMatches(Node *head, Node **stackTop8, FILE *printFile);
int getElements(Node *head);
void deleteStack(Node **top);
void freeStack(Node **stack);

// task 4
Tree *newNode(Team val);
void inorder(Tree *root, FILE *printFile);
Tree *insert(Tree *node, Team val);

#endif