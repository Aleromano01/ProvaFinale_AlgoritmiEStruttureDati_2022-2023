#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct ListaDoppia{
    int dist;
    int s;
    struct ListaDoppia* next;
    struct ListaDoppia* prev;
    struct ListaDoppia* head;
    struct ListaDoppia* tail;
};

struct VeicoloNodo {
    int autonomy;
    struct VeicoloNodo *next;
};

struct Station{
    int distance;
    struct VeicoloNodo* veicoliElettriciBST;
    struct Station* left;
    struct Station* right;
    struct Station* parent;
};
struct VeicoloNodo* insertCar(struct VeicoloNodo* root, int autonomy);
struct Station* insert(struct Station* root, int distance, int numCar, int* autonomy);
struct VeicoloNodo* createNodo(int autonomy);
struct Station* minValueNode(struct Station* root);
bool searchStation(struct Station* head, int distance);
struct Station* findStation(struct Station* head, int distance);
struct VeicoloNodo* destroyCar(struct VeicoloNodo* root);
struct Station* demolisci(struct Station* head, int distance);
struct Station* addCar(struct Station* head, int distance, int autonomia);
bool findCar(struct VeicoloNodo* head, int autonomia);
struct Station* rottamaAuto(struct Station* head, int distance, int autonomia);
void stampaAutostrada(struct Station* head);
void stampaStation(struct VeicoloNodo* root);
int numStation(struct Station* head) ;
struct VeicoloNodo* removeCar(struct VeicoloNodo* root, int autonomia);
void pianificaPercorso(struct Station* part,struct Station* arr,struct Station* head, int partenza, int arrivo);
struct VeicoloNodo* findMaxCar(struct VeicoloNodo* head);
struct Station* tree_minimum(struct Station* stat);
struct Station* tree_maximum(struct Station* stat);
struct Station* successor(struct Station* head , int distance);
struct Station* predecessor (struct Station* head,int distance);

void modificaListaCaso1(struct Station* head,struct ListaDoppia* lista,int arrivo, int partenza);
void modificaListaCaso2(struct Station* head,struct ListaDoppia* lista,int arrivo, int partenza);
struct ListaDoppia* createNode(int dist, int s);
void append(struct ListaDoppia* head_ref, int dist, int s);
void printForward(struct ListaDoppia* head);
void freeLista(struct ListaDoppia* root);
int main(int argc, char* argv[]) {

    struct Station* autostrada = NULL;

    char command[10000];
    int distance;
    int numVeic;
    int autonomia;
    int partenza;
    int arrivo;

    if (argc < 2) {
        fprintf(stderr, "Errore: Percorso del file non specificato.\n");
        fprintf(stderr, "Uso: %s <percorso_del_file_di_input>\n", argv[0]);
        return 1;
    }

    FILE* file_input = fopen(argv[1], "r");
    if (file_input == NULL) {
        fprintf(stderr, "Errore: Impossibile aprire il file '%s'.\n", argv[1]);
        return 1;
    }

    while(fscanf(file_input, "%s", command) == 1){
        if(strcmp(command,"aggiungi-stazione")==0){
            if(fscanf(file_input, "%d", &distance) != 1){
                exit(1);
            }
            if(fscanf(file_input, "%d", &numVeic) != 1){
                exit(1);
            }
            int* autonomie = (int*)malloc(numVeic*sizeof(int));
            for(int i=0;i<numVeic;i++){
                if(fscanf(file_input, "%d", &autonomie[i]) != 1){
                    exit(1);
                }
            }
            autostrada = insert(autostrada,distance,numVeic,autonomie);
            free(autonomie);
        }else if(strcmp(command,"demolisci-stazione")==0){
            if(fscanf(file_input, "%d", &distance) != 1){
                exit(1);
            }
            autostrada = demolisci(autostrada,distance);
        }else if(strcmp(command,"aggiungi-auto")==0){
            if(fscanf(file_input, "%d", &distance) != 1){
                exit(1);
            }
            if(fscanf(file_input, "%d", &autonomia) != 1){
                exit(1);
            }
            autostrada = addCar(autostrada, distance, autonomia);
        }else if(strcmp(command,"rottama-auto")==0){
            if(fscanf(file_input, "%d", &distance) != 1){
                exit(1);
            }
            if(fscanf(file_input, "%d", &autonomia) != 1){
                exit(1);
            }
            autostrada = rottamaAuto(autostrada,distance,autonomia);
        }else if(strcmp(command,"pianifica-percorso")==0){
            if(fscanf(file_input, "%d", &partenza) != 1){
                exit(1);
            }
            if(fscanf(file_input, "%d", &arrivo) != 1){
                exit(1);
            }
            pianificaPercorso(autostrada,autostrada,autostrada,partenza,arrivo);
        }
    }

    fclose(file_input);


    return 0;
}
struct VeicoloNodo* createNodo(int autonomy){
    struct VeicoloNodo* newNodo = (struct VeicoloNodo*)malloc(sizeof(struct VeicoloNodo));
    newNodo->autonomy = autonomy;
    newNodo->next = NULL;
    return newNodo;

}
struct VeicoloNodo* insertCar(struct VeicoloNodo* root, int autonomy) {
    struct VeicoloNodo* newNodo = createNodo(autonomy);

    //Lista Vuota
    if(root == NULL) return newNodo;

    //Inserimento in testa
    if(root->autonomy <= newNodo->autonomy){
        newNodo->next = root;
        return newNodo;
    }

    struct VeicoloNodo *point = root;
    while(point->next != NULL && point->next->autonomy > newNodo->autonomy){
        point = point->next;
    }

    newNodo->next = point->next;
    point->next = newNodo;
    return root;




    /*if (root == NULL || (autonomy < root->autonomy)) {
        newNodo->next = root;

        if (root != NULL) {
            root->prev = newNodo;
        }
        return newNodo;
    }
    struct VeicoloNodo *current = root;
    while (current->next != NULL && current->next->autonomy < autonomy) {
        current = current->next;
    }
    newNodo->next = current->next;
    newNodo->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNodo;
    }
    current->next = newNodo;
    return root;*/
}

struct Station* insert(struct Station* root, int distance, int numCar, int* autonomy) {
    if(searchStation(root,distance)==true){
        printf("non aggiunta\n");
        return root;
    }
    struct Station* z=   (struct Station*)malloc(sizeof(struct Station));
    if(z==NULL){
        //     printf("errore allocazione\n");
        return root;
    }
    z->distance = distance;
//    z->numVeicolo = numCar;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->veicoliElettriciBST = NULL;

    for(int i=0; i < numCar; i++){
        z->veicoliElettriciBST = insertCar(z->veicoliElettriciBST, autonomy[i]);
    }
    struct Station* y=NULL;
    struct Station* x = root;
    while(x!=NULL){
        y=x;
        if(z->distance < x->distance){
            x= x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y==NULL){
        root = z;
    }else if(z->distance < y->distance){
        y->left =z;
    }else{
        y->right = z;
    }
    printf("aggiunta\n");

    return root;

}

struct Station* minValueNode(struct Station* root){
    struct Station* current = root;
    while(current!=NULL && current->left!=NULL  ){
        current = current->left;
    }
    return current;
}

bool searchStation(struct Station* head, int distance){
    if (head==NULL){
        //    printf("non trovata\n");
        return false;
    }
    if(distance == head->distance){
        //    printf("trovata alla distanza %d\n",head->distance);
        return true;
    }
    if(distance < head->distance){
        return searchStation(head->left,distance);
    }else{
        return searchStation(head->right,distance);
    }
}
struct Station* findStation(struct Station* head, int distance){
    if (head==NULL){
        // printf("non trovata\n");
        return NULL;
    }
    if(distance == head->distance){
        //    printf("trovata alla distanza %d\n",head->distance);
        return head;
    }
    if(distance < head->distance){
        return findStation(head->left,distance);
    }else{
        return findStation(head->right,distance);
    }
}
struct VeicoloNodo* destroyCar(struct VeicoloNodo* root){
    if(root==NULL){
        return NULL;
    }
    struct VeicoloNodo* next = root->next;
    free(root);
    return destroyCar(next);
}
struct Station* transplant(struct Station* root, struct Station* u, struct Station* v){
    if(u->parent==NULL){
        root = v;
    }else if(u==u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    if(v!=NULL){
        v->parent = u->parent;
    }
    return root;
}


struct Station* demolisci(struct Station* head, int distance) {
    struct Station *current = findStation(head, distance);
    if (head == NULL) {
        printf("non demolita\n");
        return head;
    }
    if (current == NULL) {
        printf("non demolita\n");
        return head;
    }
    if (current->left == NULL) {
        head = transplant(head, current, current->right);
    } else if (current->right == NULL) {
        head = transplant(head, current, current->left);
    } else {
        struct Station *y = minValueNode(current->right);
        if (y->parent != current) {
            head = transplant(head, y, y->right);
            y->right = current->right;
            y->right->parent = y;
        }
        head = transplant(head, current, y);
        y->left = current->left;
        y->left->parent = y;
    }
    destroyCar(current->veicoliElettriciBST);
    free(current);
    printf("demolita\n");
    return head;
}

struct Station* addCar(struct Station* head, int distance, int autonomia){

    struct Station* station = findStation(head,distance);
    if(station==NULL){
        printf("non aggiunta\n");
        return head;
    }else {
        station->veicoliElettriciBST = insertCar(station->veicoliElettriciBST, autonomia);
        printf("aggiunta\n");
     //   station->numVeicolo++;
        return head;
    }
}

bool findCar(struct VeicoloNodo* head, int autonomia){
    while(head!=NULL && head->autonomy > autonomia){
        head=head->next;
    }
    if(head == NULL) return false;
    if(head->autonomy == autonomia) return true;
    return false;
}
struct Station* rottamaAuto(struct Station* head, int distance, int autonomia) {
    struct Station* station = findStation(head, distance);
    if (station == NULL ) {
        printf("non rottamata\n");
        return head;
    }

    if(findCar(station->veicoliElettriciBST, autonomia) == false){
        printf("non rottamata\n");
        return head;
    }else{
        station->veicoliElettriciBST= removeCar(station->veicoliElettriciBST, autonomia);
        printf("rottamata\n");
    }
    return head;
}
struct VeicoloNodo* removeCar(struct VeicoloNodo* root, int autonomia) {
    if (root == NULL) {
        return NULL;
    }

    if(root->autonomy == autonomia){
        struct VeicoloNodo* ret = root->next;
        free(root);
        return ret;
    }

    struct VeicoloNodo* temp = root;
    while(temp->next!=NULL && temp->next->autonomy > autonomia){
        temp=temp->next;
    }

    if(temp->next->autonomy == autonomia){
        struct VeicoloNodo* freed = temp->next;
        temp->next = temp->next->next;
        free(freed);
    };
    return root;

}

/*
void stampaAutostrada(struct Station* head){
    if(head==NULL){
        return;
    }
    stampaAutostrada(head->left);

    printf("distanza %d\n",head->distance);
//    stampaStation(head->veicoliElettriciBST);
    if(head->numVeicolo==0){
        printf("nessuna macchina\n");
    }else{
        int max=findMaxCar(head->veicoliElettriciBST)->autonomy;
        printf("la macchina con più autonomia della stazione %d è:%d \n",head->distance,max);

    }
       struct Station* succ =successor(head, head->distance);
      struct Station* pred= predecessor(head,head->distance);

      if(succ != NULL){
          printf("succ %d\n",succ->distance);
      }
      if(pred!=NULL){
          printf("pred %d\n",pred->distance);
      }

    stampaAutostrada(head->right);
}
void stampaStation(struct VeicoloNodo* root) {
    struct VeicoloNodo* current = root;
    while(current!=NULL){
        printf("autonomia %d\n",current->autonomy);
        current = current->next;
    }
}*/
struct VeicoloNodo* findMaxCar(struct VeicoloNodo* head){
    return head;
}

int numStation(struct Station* head) {
    if (head == NULL) {
        return 0;
    }
    int x= numStation(head->left);
    int y= numStation(head->right);
    return 1 + x + y;
}

struct Station* successor(struct Station* head,int distance){
    struct Station* current = findStation(head,distance);
    if(current==NULL){
        return NULL;
    }
    struct Station* succ = NULL;

    if(current->right!=NULL){
        return tree_minimum(head->right);
    }
    succ= current->parent;
    while(succ!=NULL &&  current ==succ->right){
        current = succ;
        succ = succ->parent;
    }
    if(succ!= NULL && succ->distance>current->distance){
        return succ;
    }else{
        return NULL;
    }

    return succ;
}
struct Station* tree_minimum(struct Station* stat){
    if(stat==NULL){
        return NULL;
    }
    while(stat->left!=NULL){
        stat=stat->left;
    }
    return stat;
}
struct Station* tree_maximum(struct Station* stat){
    while(stat->right!=NULL){
        stat=stat->right;
    }
    return stat;
}
struct Station* predecessor (struct Station* head,int distance){
    struct Station* current = findStation(head,distance);
    if(current==NULL){
        return NULL;
    }

    struct Station* pred = NULL;
    if(current->left!=NULL) {
        return tree_maximum(current->left);
    }

    while (current->parent != NULL && current == current->parent->left) {
        current = current->parent;
    }

    if(current->parent == NULL){
        return NULL;
    }
    return current->parent;
    return pred;
}
int calcolaNumeroStazioniTraStazioni(struct Station* root, int partenza, int arrivo) {
    if (root == NULL) {
        return 0;
    }

    if (partenza < root->distance && arrivo < root->distance) {
        // Entrambe le stazioni sono nel sottoalbero sinistro
        return calcolaNumeroStazioniTraStazioni(root->left, partenza, arrivo);
    } else if (partenza > root->distance && arrivo > root->distance) {
        // Entrambe le stazioni sono nel sottoalbero destro
        return calcolaNumeroStazioniTraStazioni(root->right, partenza, arrivo);
    } else {
        // Una stazione è nel sottoalbero sinistro e l'altra nel sottoalbero destro,
        // quindi includi la stazione radice e somma i risultati dei sottoalberi
        return 1 + calcolaNumeroStazioniTraStazioni(root->left, partenza, arrivo) +
               calcolaNumeroStazioniTraStazioni(root->right, partenza, arrivo);
    }
}


void pianificaPercorso(struct Station* part,struct Station* arr,struct Station* head, int partenza, int arrivo) {
    part = findStation(head, partenza);
    //  printf("partenza %d\n",part->distance);
    arr = findStation(head, arrivo);
    if (arrivo == partenza && part != NULL) {
        printf("%d\n", partenza);
        return;
    } else if (part->veicoliElettriciBST == NULL) {
        printf("nessun percorso\n");
        return;
        //   printf("nessuna macchina\n");
        return;
    }
    if(partenza<arrivo){
        struct ListaDoppia* lista=NULL;
        lista = (struct ListaDoppia*)malloc(sizeof(struct ListaDoppia));
        lista->head = NULL;
        lista->tail = NULL;

        struct Station* current = part;
        if(current->veicoliElettriciBST==NULL){
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        struct Station* succ = successor(part, partenza);
        if(succ->distance==arrivo && current->distance+findMaxCar(current->veicoliElettriciBST)->autonomy >= arrivo){
            append(lista,partenza,partenza+findMaxCar(current->veicoliElettriciBST)->autonomy);
            append(lista,arrivo,0);
            printForward(lista->head);
            freeLista(lista->head);
            return;
        }else if(succ->distance==arrivo && current->distance+findMaxCar(current->veicoliElettriciBST)->autonomy < arrivo){
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        struct Station* z;
        int a,b,max=0,stat=0;

        append(lista,partenza,partenza+findMaxCar(current->veicoliElettriciBST)->autonomy);
        while(succ->distance != arrivo && succ!=NULL){
            a = current->distance + findMaxCar(current->veicoliElettriciBST)->autonomy;
            b= succ->distance+ findMaxCar(succ->veicoliElettriciBST)->autonomy;
            if(a >=succ->distance){

                if(b>=max){
                    max=b;
                    stat=succ->distance;
                }
                succ = successor(succ,succ->distance);
            }else{
                if(successor(current,current->distance)->distance==succ->distance){
                    printf("nessun percorso\n");
                    freeLista(lista->head);
                    return ;
                }
                z= findStation(head,stat);
                append(lista,z->distance,z->distance+findMaxCar(z->veicoliElettriciBST)->autonomy);
                succ = successor(z,z->distance);
                current = findStation(head,z->distance);
                max = current->distance;
            }
            if( succ!=NULL && succ->distance==arrivo && current->distance+findMaxCar(current->veicoliElettriciBST)->autonomy >= arrivo ){
                append(lista,arrivo,0);
            }


        }
        if(succ->distance == arrivo && max < arrivo){
            //NO percorso
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        if(lista->tail->dist!=arrivo){
            z= predecessor(head,succ->distance);
            struct VeicoloNodo* max = findMaxCar(z->veicoliElettriciBST);
            int iMax = max == NULL ? 0 : max->autonomy;
            append(lista,z->distance,z->distance+iMax);
            max = findMaxCar(succ->veicoliElettriciBST);
            iMax = max == NULL ? 0 : max->autonomy;
            append(lista,succ->distance,succ->distance+iMax);
        }
        if(part->distance+ findMaxCar(part->veicoliElettriciBST)->autonomy >= arrivo){
            append(lista,arrivo,arrivo);
        }
        //   printForward(lista->head);
        modificaListaCaso1(head,lista->head,arrivo,partenza);
        printForward(lista->head);
        freeLista(lista->head);
    }else {
        struct ListaDoppia *lista = NULL;
        lista = (struct ListaDoppia *) malloc(sizeof(struct ListaDoppia));
        lista->head = NULL;
        lista->tail = NULL;

        struct Station *current = part;
        struct Station *pred = predecessor(part, partenza);
        if(current->veicoliElettriciBST==NULL){
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        if (pred->distance == arrivo && current->distance - findMaxCar(current->veicoliElettriciBST)->autonomy <= arrivo) {
            append(lista, partenza, partenza - findMaxCar(current->veicoliElettriciBST)->autonomy);
            append(lista, arrivo, 0);
            printForward(lista->head);
            freeLista(lista->head);
            return;
        } else if (pred->distance == arrivo && current->distance - findMaxCar(current->veicoliElettriciBST)->autonomy >= arrivo) {
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        struct Station *z;
        int a=0,min=0,stat=pred->distance,b=0;
        min = pred->distance - findMaxCar(pred->veicoliElettriciBST)->autonomy;

        append(lista, partenza, partenza - findMaxCar(current->veicoliElettriciBST)->autonomy);
        while (pred->distance != arrivo && pred != NULL) {
            if(pred->veicoliElettriciBST==NULL){
                printf("nessun percorso\n");
                freeLista(lista->head);
                return;
            }
            a = current->distance - findMaxCar(current->veicoliElettriciBST)->autonomy;
            b = pred->distance - findMaxCar(pred->veicoliElettriciBST)->autonomy;
            //Pred raggiungibile
            if (a <= pred->distance) {
                //pred mi porta piu lontano della precedente scelta
                if(b<=min){
                    min=b;
                    stat=pred->distance;
                }
                pred = predecessor(pred, pred->distance);
            } else { //Pred non raggiungibile
                //non ho trovato alcuna stazione
                if (predecessor(current, current->distance)->distance == pred->distance) {
                    printf("nessun percorso\n");
                    freeLista(lista->head);
                    return;
                }
                z = findStation(head, stat);
                append(lista, z->distance, z->distance - findMaxCar(z->veicoliElettriciBST)->autonomy);
                pred = predecessor(z, z->distance);
                current = findStation(z, z->distance);
                min = current->distance;
            }
            if (pred != NULL && pred->distance == arrivo &&
                current->distance - findMaxCar(current->veicoliElettriciBST)->autonomy <= arrivo) {
                append(lista, arrivo, 0);
            }


        }
        if(pred->distance == arrivo && min > arrivo){
            //NO percorso
            printf("nessun percorso\n");
            freeLista(lista->head);
            return;
        }
        if (lista->tail->dist != arrivo) {
            z = successor(pred, pred->distance);
            struct VeicoloNodo* max = findMaxCar(z->veicoliElettriciBST);
            int iMax = max == NULL ? 0 : max->autonomy;
            append(lista, z->distance, z->distance - iMax);
            max = findMaxCar(pred->veicoliElettriciBST);
            iMax = max == NULL ? 0 : max->autonomy;
            append(lista, pred->distance, pred->distance - iMax);
        }
        if (part->distance - findMaxCar(part->veicoliElettriciBST)->autonomy < arrivo) {
            append(lista, arrivo, arrivo);
        }
        //   printForward(lista->head);
        modificaListaCaso2(head, lista->head, arrivo, partenza);
        printForward(lista->head);
        freeLista(lista->head);
    }

}

void modificaListaCaso1(struct Station* head,struct ListaDoppia* lista,int arrivo, int partenza){
    // printf("modifica lista\n");
    while(lista->next !=NULL){
        lista=lista->next;
    }
    lista=lista->prev;
    struct Station* succ= findStation(head,arrivo);
    struct Station* current = findStation(head,lista->dist);
    if(predecessor(head,current->distance)==NULL){
        return;
    }
    struct Station* pred = predecessor(current,current->distance);
    int max=0;
    while(pred!=NULL && pred->distance!=partenza && lista->prev!=NULL) {
        max=0;
        while (lista->prev != NULL && pred!=NULL && pred->distance != lista->prev->dist ) {
            if(pred->veicoliElettriciBST!=NULL){
                if (pred->distance + findMaxCar(pred->veicoliElettriciBST)->autonomy >= succ->distance) {
                    max = pred->distance;
                }
            }

            pred = predecessor(pred, pred->distance);


        }
        if(max==0){
            lista = lista->prev;
            succ = findStation(head, lista->next->dist);
        }else{
            lista->dist = max;
            lista = lista->prev;
            succ = findStation(head, max);
        }


        pred = predecessor(head,lista->dist);
    }

}

void modificaListaCaso2(struct Station* head,struct ListaDoppia* lista,int arrivo, int partenza){
    // printf("modifica lista\n");
    while(lista->next !=NULL){
        lista=lista->next;
    }
    lista=lista->prev;

    struct Station* succ= findStation(head,arrivo);
    struct Station* current = findStation(head,lista->dist);
    if(predecessor(head,current->distance)==NULL){
        return;
    }
    struct Station* pred = predecessor(current,current->distance);
    int max=0;
    while(pred!=NULL && pred->distance!=partenza && lista->prev!=NULL) {
        max=0;
        while (lista->prev != NULL && pred!=NULL && pred->distance >= lista->prev->s ) {
            if(pred->veicoliElettriciBST!=NULL){
                if (pred->distance - findMaxCar(pred->veicoliElettriciBST)->autonomy <= succ->distance) {
                    max = pred->distance;
                }
            }

            pred = predecessor(pred, pred->distance);


        }
        if(max==0){
            lista = lista->prev;
            succ = findStation(head, lista->next->dist);
        }else{
            lista->dist = max;
            lista = lista->prev;
            succ = findStation(head, max);
        }


        pred = predecessor(head,lista->dist);
    }

}

struct ListaDoppia* createNode(int dist, int s){
    struct ListaDoppia* newNodo = (struct ListaDoppia*)malloc(sizeof(struct ListaDoppia));
    newNodo->dist = dist;
    newNodo->s = s;
    newNodo->next = NULL;
    newNodo->prev = NULL;
    return newNodo;
}
void append(struct ListaDoppia* head_ref, int dist, int s){
    struct ListaDoppia* newNodo = createNode(dist,s);
    if(head_ref->tail==NULL){
        head_ref->tail = newNodo;
        head_ref->head = newNodo;
    }else{
        head_ref->tail->next = newNodo;
        newNodo->prev = head_ref->tail;
        head_ref->tail = newNodo;
    }

}
void printForward(struct ListaDoppia* head) {
    struct ListaDoppia* current = head;
    int dist = current->dist;
    printf("%d",dist);
    current=current->next;
    while (current != NULL) {
        dist = current->dist;
        printf(" %d", dist);
        current = current->next;
    }
    printf("\n");

}
void freeLista(struct ListaDoppia* root){
    if(root==NULL){
        return ;
    }
    struct ListaDoppia *current = root;
    while (root!=NULL) {
        current = root->next;
        free(root);
        root = current;
    }

}