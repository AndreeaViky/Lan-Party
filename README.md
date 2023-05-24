# Player readPlayer(FILE *file)
functie pentru citirea jucatorilor. am alocat memorie pentru firstName si secondName si am citit din fisier pentru fiecare jucator numele, prenumele si punctele

# Team readTeam(FILE *file)
functie pentru citirea echipelor. am citit numele echipei si numarul de jucatori, iar apoi cu un for, pentru fiecare jucator am folosit functia readPlayer

# Node *createList(FILE *file, int nrTeams)
crearea listei, cu un for pana la numarul echipelor. se adauga un nod nou cu o echipa, folosind functia readTeam.

# void printList(Node *head, FILE *file)
afisarea listei, numele echipelor

# int getRemainingTeams(int n)
pentru a gasi n-ul cerut, inmultind mereu puterea cu 2 pana cand power este mai mic sau egal cu n. 

# void deleteOneTeam(Node **head, float score)
pentru a sterge o echipa din lista cu scorul cel mai mic (am folosit si functia urmatoare). parcurg lista si cand gasesc o echipa cu punctajul minim o elimin, refacand legaturile. 

# float totalScore(Team team)
calcularea punctajului fiecarei echipe, adunand punctele jucatorilor si impartind la numarul acestora

# void deleteTeams(Node **head, int nrTeams)
functia de stergere a echipelor, functia ce rezolva task ul 2 am initializat n cu getRemainingTeams si am eliminat nrTeams - n echipe

# Queue *createQueue()
creare coada 

# Team copyTeam(Team team)
pentru a copia o echipa si a o putea adauga/scoate in/din stiva

# void enQueue(Queue *q, Team team)
adaug un element in coada 

# Team deQueue(Queue *q)
pentru a scoate din coada 

# void push(Node **top, Team v)
adauga element in stiva 

# Team pop(Node **top)
elimina element 

# void addMatch(Node *head, Queue *q)
sa puna meciurile in coada 

# int getElements(Node *head)
sa aflam cate elemente sunt in coada

# void addPoint(Team team)
adauga un punct la castigatori 

# void createMatches(Node *head, Node **stackTop8, FILE *printFile)
creeaza meciurile si pune in stiva castigatorii si pierzatorii, se foloseste de functia addMatch. in variabila number punem ce a returnat functia getElements.
pentru a afla nr de runde impartim mereu number la 2
cu un for pana la nr de runde scoatem echipele din coada si calculam scorul pentru fiecare. daca scorul1 este mai mare decat scoarul2 atunci ehipa1 va fi pusa in stiva de castigatori, iar cealalta in cea de pierzatori. pentru fiecare castigator se aduaga un punct
pentru a afisa top 8 aflam cate elemente are stiva de castigatori si punem toate elementele stivei de winners in stiva de top 8.

# Tree *newNode(Team val)
pentru a crea arborele BST 

# void inorder(Tree *root, FILE *printFile)
parcurgere in inordine

# Tree *insert(Tree *node, Team val)
insereaza un nod nou in arbore
