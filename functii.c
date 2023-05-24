#include "functii.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Player readPlayer(FILE *file)
{
	Player player;

	player.firstName = (char *)malloc(20);
	fscanf(file, "%s", player.firstName);

	player.secondName = (char *)malloc(20);
	fscanf(file, "%s", player.secondName);

	fscanf(file, "%d", &player.points);

	return player;
}

Team readTeam(FILE *file)
{
	Team team;

	fscanf(file, "%d ", &team.nrPlayers);
	team.name = (char *)malloc(40);
	fgets(team.name, 40, file);

	if (team.name[strlen(team.name) - 3] == ' ')
		team.name[strlen(team.name) - 3] = '\0';
	else
		team.name[strlen(team.name) - 2] = '\0';

	team.players = (Player *)malloc(team.nrPlayers * sizeof(Player));

	for (int i = 0; i < team.nrPlayers; i++)
		team.players[i] = readPlayer(file);

	return team;
}

Node *createList(FILE *file, int nrTeams)
{
	Node *head = NULL;
	Node *newNode = NULL;

	for (int i = 0; i < nrTeams; i++)
	{
		newNode = malloc(sizeof(*newNode));
		newNode->val = readTeam(file);
		newNode->next = head;
		head = newNode;
	}

	return head;
}

void printList(Node *head, FILE *file)
{
	while (head != NULL)
	{
		fprintf(file, "%s\n", head->val.name);
		head = head->next;
	}
}

// pentru a gasi n -ul
int getRemainingTeams(int n)
{
	int power = 1;

	while (power <= n)
	{
		power = power * 2;
	}
	return power / 2;
}

// pentru a sterge o echipa din lista

void deleteOneTeam(Node **head, float score)
{

	if (*head == NULL)
		return;

	Node *headcopy = *head;
	if (totalScore(headcopy->val) == score)
	{
		*head = (*head)->next;
		free(headcopy);
		return;
	}

	Node *prev = *head;
	while (headcopy != NULL)
	{
		if (totalScore(headcopy->val) != score)
		{
			prev = headcopy;
			headcopy = headcopy->next;
		}
		else
		{
			prev->next = headcopy->next;
			free(headcopy);
			return;
		}
	}
}

// punctaj echipa
float totalScore(Team team)
{
	float mean = 0; // medie
	for (int i = 0; i < team.nrPlayers; i++)
	{
		mean += team.players[i].points;
	}

	return mean / (team.nrPlayers);
}

// functia task 2 - sterge echipe
void deleteTeams(Node **head, int nrTeams)
{
	int n = getRemainingTeams(nrTeams);

	for (int i = 0; i < nrTeams - n; i++)
	{
		float minValue = totalScore((*head)->val);
		Node *var = *head; // cap lista

		while (var != NULL)
		{
			if (totalScore(var->val) < minValue)
				minValue = totalScore(var->val);

			var = var->next;
		}

		deleteOneTeam(head, minValue);
	}
}

// task 3
// functie creare coada
Queue *createQueue()
{
	Queue *q = malloc(sizeof(*q));
	if (q == NULL)
		return NULL;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

// pentru a copia o echipa in alta
Team copyTeam(Team team)
{
	Team var;

	var.name = (char *)malloc(sizeof(char) * 40);
	strcpy(var.name, team.name);
	var.nrPlayers = team.nrPlayers;

	var.players = (Player *)malloc(sizeof(Player) * var.nrPlayers);
	for (int i = 0; i < var.nrPlayers; i++)
	{
		var.players[i].points = team.players[i].points;
	}
	return var;
}

// adaugare element in coada
void enQueue(Queue *q, Team team)
{
	Node *newNode = malloc(sizeof(Node));
	newNode->val = copyTeam(team);
	newNode->next = NULL;

	if (q->rear == NULL)
		q->rear = newNode;
	else
	{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}

	if (q->front == NULL)
		q->front = q->rear;
}

// stergere coada
int isEmpty(Queue *q)
{
	return (q->front == NULL);
}

// functie de scos din coada
Team deQueue(Queue *q)
{
	Node *aux;
	Team d;
	if (isEmpty(q))
		exit(1);

	aux = q->front;
	d = copyTeam(aux->val);
	q->front = (q->front)->next;
	free(aux);

	return d;
}

// functie pentru adaugare element in stiva

void push(Node **top, Team v)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->val = copyTeam(v);
	newNode->next = *top;
	*top = newNode;
}

// eleminiare element

Team pop(Node **top)
{
	Node *temp = (*top);
	Team aux = copyTeam(temp->val);
	*top = (*top)->next;
	free(temp);
	return aux;
}

// functie care sa faca meciurile
void addMatch(Node *head, Queue *q)
{
	while (head != NULL)
	{
		enQueue(q, head->val);
		head = head->next;
	}
}

int getElements(Node *head)
{
	int number = 0;

	while (head != NULL)
	{
		number++;
		head = head->next;
	}

	return number;
}

// functie golire stiva
void deleteStack(Node **top)
{
	Node *temp;

	while ((*top) != NULL)
	{
		temp = *top;
		*top = (*top)->next;
		free(temp->val.name);
		free(temp->val.players);
		free(temp);
	}
}

// functie pentru a adauga 1 punct
void addPoint(Team team)
{
	for (int i = 0; i < team.nrPlayers; i++)
	{
		team.players[i].points += 1;
	}
}

// functie task 3
void createMatches(Node *head, Node **stackTop8, FILE *printFile)
{
	Node *winners = NULL;
	Node *losers = NULL;
	Queue *queue = createQueue();

	addMatch(head, queue);

	int number = getElements(head);
	int rounds = 0;

	while (number > 1)
	{
		number = number / 2;
		rounds++;
	}

	for (int i = 0; i < rounds; i++)
	{
		fprintf(printFile, "\n--- ROUND NO:%d\n", i + 1);
		Team team1, team2;
		float score1, score2;
		while (queue->front != NULL)
		{
			team1 = deQueue(queue);
			team2 = deQueue(queue);

			fprintf(printFile, "%-33s-%33s\n", team1.name, team2.name);
			score1 = totalScore(team1);
			score2 = totalScore(team2);

			if (score1 > score2)
			{
				push(&winners, team1);
				push(&losers, team2);
			}
			else
			{
				push(&winners, team2);
				push(&losers, team1);
			}
		}
		queue->front = queue->rear = NULL;

		deleteStack(&losers);
		losers = NULL;

		Node *var = winners;
		fprintf(printFile, "\nWINNERS OF ROUND NO:%d\n", i + 1);

		while (var != NULL)
		{
			addPoint(var->val);
			fprintf(printFile, "%-34s-  %.2f\n", var->val.name, totalScore(var->val));
			var = var->next;
		}

		if (getElements(winners) == 8)
		{
			Node *j = winners;
			while (j != NULL)
			{
				push(stackTop8, j->val);
				j = j->next;
			}
		}

		addMatch(winners, queue);

		deleteStack(&winners);
		winners = NULL;
	}
}

// task 4
// arbori
// A utility function to create a new BST node
Tree *newNode(Team val)
{
	Tree *temp = (Tree *)malloc(sizeof(Tree));

	temp->val = copyTeam(val);
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST
void inorder(Tree *root, FILE *printFile)
{
	if (root != NULL)
	{
		inorder(root->right, printFile);
		fprintf(printFile, "%-34s-  %.2f\n", root->val.name, totalScore(root->val));
		inorder(root->left, printFile);
	}
}

// A utility function to insert
// a new node with given key in BST
Tree *insert(Tree *node, Team val)
{
	// If the tree is empty, return a new node
	if (node == NULL)
		return newNode(val);

	// Otherwise, recur down the tree
	if (totalScore(val) < totalScore(node->val))
		node->left = insert(node->left, val);
	else if (totalScore(val) > totalScore(node->val))
		node->right = insert(node->right, val);
	else if (strcmp(val.name, node->val.name) > 0)
		node->right = insert(node->right, val);
	else
		node->left = insert(node->left, val);

	// Return the (unchanged) node pointer
	return node;
}
