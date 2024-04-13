#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*SOSTITUIRE L'ALBERO ROSSO NERI CON GLI ALBERI, DA AGGIUNGERE FUNZIONE DI FIXUP IN AGGIUNGI STAZIONE E RIMUOVI STAZIONE*/

typedef struct El_List
{
    int Autonomia;
    struct El_List* Next;
}ElementiLista;

typedef struct El_Tree
{
    int Distanza;
    struct El_Tree* P;
    struct El_Tree* Sx;
    struct El_Tree* Dx;
    struct El_List* Next;
    int Color; // 1 = rosso, 0 = nero
}ElementiAlbero;

typedef struct El_Percorso
{
    struct El_Percorso* PrevP;
    struct El_Percorso* NextP;
    struct El_Tree* NextT;
}ElementiPercorso;

typedef ElementiAlbero* tree;
typedef ElementiLista* PuntaLista;


/*FUNZIONI RB TREE*/

ElementiAlbero* Insert_Fixup(ElementiAlbero* Root, ElementiAlbero* z, ElementiAlbero* T_NIL);

ElementiAlbero* Right_Rotate(ElementiAlbero* Root, ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiAlbero* Left_Rotate(ElementiAlbero* Root, ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiAlbero* Delete_Fixup(ElementiAlbero* Root, ElementiAlbero* x, ElementiAlbero* T_NIL);

/*FUNZIONI AUSILIARE*/
/*+++++++++++++++++++++++++++++++++++++++*/

int raggiungibile(int Dist, ElementiLista* L, ElementiAlbero* T_NIL);

void inorder_tree_walk(ElementiAlbero* Root, ElementiAlbero* T_NIL);

void stampalista(ElementiLista* L, ElementiAlbero* T_NIL);

ElementiLista* cancellalista(ElementiLista* L, ElementiAlbero* T_NIL);

ElementiLista* cancellalista_elemento(ElementiAlbero* Nodo, int Autonomia, ElementiAlbero* T_NIL);

ElementiLista* aggiungilista_elemento(ElementiAlbero* Nodo, ElementiLista* L, int Autonomia, ElementiAlbero* T_NIL);

ElementiAlbero* tree_search(ElementiAlbero* Root, int Dist, ElementiAlbero* T_NIL);

ElementiAlbero* tree_successor(ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiAlbero* tree_minimum(ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiAlbero* tree_maximun(ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiPercorso* cancellalista_percorso(ElementiPercorso* P, ElementiAlbero* T_NIL);

ElementiPercorso* cancellalista_percorso_contrario(ElementiPercorso* P, ElementiAlbero* T_NIL);

void stampalista_percorso(ElementiPercorso* P, ElementiAlbero* T_NIL);

void stampalista_percorso_contrario(ElementiPercorso* P, ElementiAlbero* T_NIL);

ElementiAlbero* tree_predecessor(ElementiAlbero* x, ElementiAlbero* T_NIL);

ElementiAlbero* CancellaAlbero(ElementiAlbero* Root, ElementiAlbero* T_NIL);

/*++++++++++++++++++++++++++++++++++++++*/
/*FUNZIONE PROGETTO*/

ElementiAlbero* aggiungi_stazione(ElementiLista* L, ElementiAlbero* Root, ElementiAlbero* T_NIL);

ElementiAlbero* demolisci_stazione(ElementiLista* L, ElementiAlbero* Root, ElementiAlbero* T_NIL);

ElementiAlbero* rottama_auto(ElementiAlbero* Root,ElementiLista* L_DaRottamare, ElementiAlbero* T_NIL);

ElementiAlbero* aggiungi_auto(ElementiAlbero* Root, ElementiLista* L_DaAggiungere, ElementiAlbero* T_NIL);

ElementiAlbero* Cerca_Successore_Andata(ElementiAlbero* Root, int Dist_Inizio, int Dist_Fine, ElementiAlbero* Min_Successore, ElementiAlbero* T_NIL);

ElementiPercorso* pianifica_percorso_lista(ElementiAlbero* Root, ElementiAlbero *Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito, ElementiAlbero* T_NIL);

ElementiAlbero* Cerca_Successore_Ritorno(ElementiAlbero* Root, int Dist_Inizio, int Dist_Fine, ElementiAlbero* Max_Successore, ElementiAlbero* T_NIL);

ElementiPercorso* Costruisci_Lista_Contrario(ElementiAlbero* Root, ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito, ElementiAlbero* T_NIL);

int Sistema_Percorso(ElementiPercorso* Inizio, ElementiPercorso* Fine, ElementiPercorso* MuoviPercorso, ElementiAlbero* T_NIL);

/*++++++++++++++++++++++++++++++++++++++*/

int main()
{
    //LA VARIABILE INIZIO PERCORSO SERVE NEL CASO IN CUI FINE.DISTANZA < INIZIO.DISTANZA PER NON CAMBIARE LA FUNZIONE DI STAMPA PERCORSO
    char parola1[50];
    char parola2[50];
    ElementiLista *L , *P;

    ElementiAlbero *Root, *T_NIL, *Inizio, *Fine;
    ElementiPercorso *PercorsoCostruito = NULL;
    ElementiPercorso* Percorso= NULL, *PrecPercorso = NULL;
    ElementiPercorso* Percorso2 = NULL, *PercorsoCostruito2 = NULL, *PrecPercorso2 = NULL, *FinePercorso2 = NULL;

    int lettere, ritorno_sistema = 0;

    T_NIL = malloc(sizeof(ElementiAlbero));
    T_NIL -> Next = NULL;
    T_NIL -> P = NULL;
    T_NIL -> Sx = NULL;
    T_NIL -> Dx = NULL;
    T_NIL -> Distanza = -1;
    T_NIL -> Color = -1;

    Root = T_NIL;

 
/*INPUT DA STDIN*/

while(scanf("%[^-]-%s ", parola1, parola2) != EOF)
    {
            L = malloc(sizeof(ElementiLista));
            P = L;
            
            lettere = scanf("%d", &(P->Autonomia));
            if(lettere != 1)
            printf("errore");
        

          while(fgetc(stdin) != '\n') // raggiungo la fine della riga
            {
                P->Next = malloc(sizeof(ElementiLista));
                P = P->Next;
                lettere = scanf("%d", &(P->Autonomia)); // continua a leggere gli interi fino ad incotrare la newline
            }
            P->Next = NULL;

            if(strcmp(parola1, "aggiungi") == 0)
            {
                if(strcmp(parola2, "auto") == 0)
                {
                    Root = aggiungi_auto(Root, L, T_NIL);
                    L = cancellalista(L, T_NIL);
                }
                if(strcmp(parola2, "stazione") == 0)
                {
                    Root = aggiungi_stazione(L, Root, T_NIL);
                }
            }
            if(strcmp(parola1, "demolisci") == 0)
            {
                if(strcmp(parola2, "stazione") == 0)
                {
                   Root = demolisci_stazione(L, Root, T_NIL);
                   L = cancellalista(L, T_NIL);
                }
            }
            if(strcmp(parola1, "rottama") == 0)
            {
                if(strcmp(parola2, "auto") == 0)
                {
                   Root = rottama_auto(Root, L, T_NIL);
                   L = cancellalista(L, T_NIL);
                }
            }
            if(strcmp(parola1, "pianifica") == 0)
            {
                if(strcmp(parola2, "percorso") == 0)
                {
                    Inizio = tree_search(Root, L->Autonomia, T_NIL);
                    Fine = tree_search(Root, L->Next->Autonomia, T_NIL);
                    PercorsoCostruito = malloc(sizeof(ElementiPercorso));

                    //NEL CASO IN CUI L'INIZIO E LA FINE COINCIDANO EVITO DI CHIAMARE LA FUNZIONE PIANIFICA-PERCORSO IN QUANDO A QUESTA PASSO PERCORSOCOSTRUITO.PREV E A STO PUNTO POSSO DIRETTAMENTE STAMPARE IL PERCORSO SENZA DOVERLA INUTILMENTE CHIAMARE
                    if(L->Autonomia == L->Next->Autonomia)
                    {
                        PercorsoCostruito->NextT = Inizio;
                        PercorsoCostruito->NextP = NULL;
                        printf("%d", PercorsoCostruito->NextT->Distanza);
                        printf("\n");
                        free(PercorsoCostruito);
                    }
                    else
                    {   
                        if(L->Autonomia < L->Next->Autonomia)
                        {
                            PercorsoCostruito->NextT = Fine;
                            PercorsoCostruito->NextP = NULL;
                            PercorsoCostruito->PrevP = NULL;
                            PrecPercorso = PercorsoCostruito;
                            Percorso = pianifica_percorso_lista(Root, Inizio, Fine, PercorsoCostruito->PrevP, PrecPercorso, T_NIL);
                        }
                        if(L->Autonomia > L->Next->Autonomia)
                        {              
                            //PRIMO: COSTRUISCO LA LISTA AL CONTRARIO UTILIZZANDO I PRECEDECESSORI 

                            PercorsoCostruito2 = malloc(sizeof(ElementiPercorso));
                            PercorsoCostruito2->NextT = Fine;
                            PercorsoCostruito2->NextP = NULL;
                            PercorsoCostruito2->PrevP = NULL;
                            PrecPercorso2 = PercorsoCostruito2;
                            
                            Percorso2 = Costruisci_Lista_Contrario(Root, Inizio, Fine, PercorsoCostruito2->NextP, PrecPercorso2, T_NIL);


                            while(Percorso2->PrevP != NULL)
                            {
                                Percorso2 = Percorso2->PrevP;
                            }
                            FinePercorso2 = Percorso2;

                            while(Percorso2->NextP != NULL)
                            {
                                Percorso2 = Percorso2->NextP;
                            }
                      
                            if(Percorso2->NextT != Inizio)
                            {
  
                                printf("nessun percorso");
                                printf("\n");
                                Percorso2 = cancellalista_percorso_contrario(Percorso2, T_NIL);
                                free(PercorsoCostruito);
                            }
                            else
                            { 
                            //PERCORSO PUNTA ALL'INIZIO, LO RIPORTO ALLA FINE
                            //PROVO AD INVERTIRE IL FUNZIONAMENTO DI SISTEMA PERCORSO FACENDOLO PARTIRE DALL'INIZIO
                               
                            
                                do 
                                {
                                  ritorno_sistema = Sistema_Percorso(FinePercorso2->NextP->NextP, FinePercorso2, FinePercorso2->NextP, T_NIL);
                               //   ritorno_sistema = Sistema_Percorso(Percorso2, Percorso2->PrevP->PrevP, Percorso2->PrevP);
                            
                                }while(ritorno_sistema == 1);
                              

                                while(Percorso2->NextP != NULL)
                                {
                                Percorso2 = Percorso2->NextP;
                                }   
                                stampalista_percorso_contrario(Percorso2, T_NIL);
                                printf("\n");
                                Percorso2 = cancellalista_percorso_contrario(Percorso2, T_NIL);
                                //cancello percorsocostruito che viene è stato creato ma viene usato solo se siamo nel secondo caso
                                free(PercorsoCostruito);

                            }
                        }
                    }
                    if(L->Autonomia < L->Next->Autonomia)
                    {
                        //SERVE A FAR RITORNARE LA LISTA FINO ALLA FINE
                        while(Percorso->PrevP != NULL)
                            Percorso = Percorso->PrevP;

                        if(Percorso->NextT != Inizio)
                            printf("nessun percorso\n");
                        else
                        {
                            stampalista_percorso(Percorso, T_NIL);
                            printf("\n");
                        }
                        Percorso = cancellalista_percorso(Percorso, T_NIL);
                    }
                    
                    L = cancellalista(L, T_NIL);
                    
                }
            }
        }

  
    Root = CancellaAlbero(Root, T_NIL);
    free(T_NIL);



    return 0;
}

void stampalista(ElementiLista* L, ElementiAlbero* T_NIL)
{
    if(L == NULL)
        return;
    printf("%d ", L->Autonomia);
    stampalista(L->Next, T_NIL);
}

ElementiLista* cancellalista(ElementiLista* L, ElementiAlbero* T_NIL)
{
    if(L != NULL)
    {
        L->Next = cancellalista(L->Next, T_NIL);
        free(L);
    }
    return NULL;
}


ElementiLista* cancellalista_elemento(ElementiAlbero* Nodo, int Autonomia, ElementiAlbero* T_NIL)
{
    ElementiLista* Pred = NULL;
    ElementiLista* Muovi = Nodo->Next;
    int cancellato = 0;

    if(Muovi->Autonomia == Autonomia)
    {
        Nodo->Next = Muovi->Next;
        free(Muovi);
        cancellato = 1;
    }
    else
    {
        Pred = Muovi;
        Muovi = Muovi->Next;
        while(Muovi != NULL && cancellato == 0)
        {
            if(Muovi->Autonomia == Autonomia)
            {
                Pred->Next = Muovi->Next;
                free(Muovi);
                cancellato = 1;
            }
            else
            {
                Pred = Muovi;
                Muovi = Muovi->Next;
            }
        }
    }

    //NON ROTTAMATA
    if(cancellato == 1)
        printf("rottamata\n");
    else
        printf("non rottamata\n");

    return Nodo->Next;
}

ElementiLista* aggiungilista_elemento(ElementiAlbero* Nodo, ElementiLista* L, int Autonomia, ElementiAlbero* T_NIL)
{
    ElementiLista *L_Aggiungi;

    //nodo da aggingere
    L_Aggiungi = malloc(sizeof(ElementiLista)); 
    L_Aggiungi->Autonomia = Autonomia;

    L_Aggiungi->Next = Nodo->Next;
    Nodo->Next = L_Aggiungi;
    printf("aggiunta\n");

    return Nodo->Next;
}

void inorder_tree_walk(ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    
    if(x != T_NIL)
    {
               printf("%d ", x->Distanza);
        printf("colore:%d\n", x->Color);
        inorder_tree_walk(x->Sx, T_NIL);

       inorder_tree_walk(x->Dx, T_NIL);
    }
}

ElementiAlbero* tree_search(ElementiAlbero* Root, int Dist, ElementiAlbero* T_NIL)
{   
    if(Root == T_NIL || Dist == Root->Distanza)
    {
        return Root;
    }
    if(Dist < Root->Distanza)
        return tree_search(Root->Sx, Dist, T_NIL);
    else return tree_search(Root->Dx, Dist, T_NIL);
}

ElementiAlbero* tree_successor(ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    ElementiAlbero* y;
    if(x->Dx != T_NIL)
        return tree_minimum(x->Dx, T_NIL);
    y = x->P;
    while(y != T_NIL && x == y->Dx)
    {
        x = y;
        y = y->P;
    }
    return y;
}

ElementiAlbero* tree_predecessor(ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    ElementiAlbero* y;
    if(x->Sx != T_NIL)
        return tree_maximun(x->Sx, T_NIL);
    y = x->P;
    while(y != T_NIL && x == y->Sx)
    {
        x = y;
        y = y->P;
    }
    return y;
}

ElementiAlbero* tree_minimum(ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    while(x->Sx != T_NIL)
        x = x->Sx;
    return x;
}

ElementiAlbero* tree_maximun(ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    while(x->Dx != T_NIL)
        x = x->Dx;
    return x;
}


ElementiAlbero* aggiungi_stazione(ElementiLista* L, ElementiAlbero* Root,ElementiAlbero* T_NIL) 
/*contiene la Root dell'albero e la lista da aggiungere*/
{
 
    ElementiAlbero* Nuovo, *y, *x;
    Nuovo = malloc(sizeof(ElementiAlbero));

    Nuovo->Next = NULL;
    Nuovo->Dx = T_NIL;
    Nuovo->Sx = T_NIL;
    Nuovo->P = T_NIL;

    y = T_NIL;
    x = Root;
    Nuovo->Distanza = L->Autonomia;


    while(x != T_NIL)
    {
        y = x;
        if(Nuovo->Distanza == x->Distanza)
        {
            printf("non aggiunta\n");
            free(Nuovo);
            L = cancellalista(L, T_NIL);
            return Root;
        }
        if(Nuovo->Distanza < x->Distanza)
            x = x->Sx;
        else x = x->Dx;
    }
    Nuovo->P = y;
    if(y ==  T_NIL)
        Root = Nuovo;
    else
    {
        if(Nuovo->Distanza < y->Distanza)
            y->Sx = Nuovo;
        else
            y->Dx = Nuovo;
    }
    //collego il nodo dell'albero alla lista di auto cancellando il primo elemento della lista passata che contine la distanza
    Nuovo->Next = L->Next->Next;
    printf("aggiunta\n");
    //ELIMINO I PRIMI DUE ELEMENTI DELLA LISTA CHE CONTENEVANO DISTANZA E AUTONOMIA
    free(L->Next);
    free(L);
    Nuovo->Color = 1;
    Nuovo->Dx = T_NIL;
    Nuovo->Sx = T_NIL;
    Root = Insert_Fixup(Root, Nuovo, T_NIL);


    return Root;

}

//ritorna il nodo eleminato
ElementiAlbero* demolisci_stazione(ElementiLista* L, ElementiAlbero* Root, ElementiAlbero* T_NIL)
{
    ElementiAlbero* ToDelete, *y, *x;
    ElementiLista* ListaDaCancellareScambio;

    ToDelete = tree_search(Root, L->Autonomia , T_NIL);

    if(ToDelete == T_NIL)
    {
        printf("non demolita\n");
        return Root;
    }



    if(ToDelete->Sx == T_NIL || ToDelete->Dx == T_NIL)
        y = ToDelete;
    else
        y = tree_successor(ToDelete, T_NIL);
    if(y->Sx != T_NIL)
        x = y->Sx;
    else 
        x = y->Dx;
    x->P = y->P;
    if(y->P == T_NIL)
        Root = x;
    else
    {
        if(y == y->P->Sx)
            y->P->Sx = x;
        else
            y->P->Dx = x;
    }

    if (y != ToDelete)
    {
        ToDelete->Distanza = y->Distanza;
        ListaDaCancellareScambio = ToDelete->Next;
        ToDelete->Next = y->Next;
    }
    else
    {
        ListaDaCancellareScambio = y->Next;
    }


   
    printf("demolita\n");

    y->Next = cancellalista(ListaDaCancellareScambio, T_NIL);
    if(y->Color == 0)
    {
    	free(y);
    	Root = Delete_Fixup(Root, x, T_NIL);
    }
    else
    	free(y);



    return Root;
}

ElementiAlbero* rottama_auto(ElementiAlbero* Root, ElementiLista* L_DaRottomare, ElementiAlbero* T_NIL)
{
    ElementiAlbero* NodoLista_ToDelete;
    int AutonomiaDaEliminare;

    NodoLista_ToDelete = tree_search(Root, L_DaRottomare->Autonomia, T_NIL); // ho trovato il nodo nella cui lista devo cercare l'elemento da eliminare

    if(NodoLista_ToDelete == T_NIL)
    {
        printf("non rottamata\n");
        return Root;
    }

    AutonomiaDaEliminare = L_DaRottomare->Next->Autonomia;
    
    //rottamo la macchina
    cancellalista_elemento(NodoLista_ToDelete, AutonomiaDaEliminare, T_NIL);

    return Root;
}

ElementiAlbero* aggiungi_auto(ElementiAlbero* Root, ElementiLista* L_DaAggiungere, ElementiAlbero* T_NIL)
{
    ElementiAlbero* Nodo;
    int Distanza;
    Distanza = L_DaAggiungere->Autonomia;

    Nodo = tree_search(Root, Distanza, T_NIL);
    if(Nodo == T_NIL)
    {
        printf("non aggiunta\n");
        return Root;
    }

    aggiungilista_elemento(Nodo, L_DaAggiungere, L_DaAggiungere->Next->Autonomia , T_NIL);

    return Root;
}


int raggiungibile(int Dist, ElementiLista* L, ElementiAlbero* T_NIL)
{
    /*RICERCA DI UN ELEMENTO IN UNA LISTA*/
    ElementiLista* P;
    P = L;

    while(P != NULL)
    {
        if(P->Autonomia >= Dist)
            return 1; //raggiungibile
        P = P->Next;
    }
    return 0; //non raggiungibile
}

ElementiPercorso* cancellalista_percorso(ElementiPercorso* P, ElementiAlbero* T_NIL)
{
    if(P != NULL)
    {
        P->NextP = cancellalista_percorso(P->NextP, T_NIL);
        free(P);
    }
    return NULL;
}

ElementiPercorso* cancellalista_percorso_contrario(ElementiPercorso* P, ElementiAlbero* T_NIL)
{
    ElementiPercorso* P1;

    if(P != NULL)
    {
        P1 = P->PrevP;
        free(P);
        cancellalista_percorso_contrario(P1, T_NIL);
        return NULL;
    }
    return NULL;
}

void stampalista_percorso_contrario(ElementiPercorso* P, ElementiAlbero* T_NIL)
{
    if(P != NULL)
    {
        if(P->PrevP == NULL)
            printf("%d", P->NextT->Distanza);
        else
            printf("%d ", P->NextT->Distanza);
        stampalista_percorso_contrario(P->PrevP, T_NIL);
    }

}

void stampalista_percorso(ElementiPercorso* P, ElementiAlbero* T_NIL)
{
    if(P != NULL)
    {
        //ULTIMO ELEMENTO
        if(P->NextP == NULL)
        {
            printf("%d", P->NextT->Distanza);  
            stampalista_percorso(P->NextP, T_NIL);  
        }
        else
        {
            printf("%d ", P->NextT->Distanza);
            stampalista_percorso(P->NextP, T_NIL);
        }

    }
}

ElementiPercorso* pianifica_percorso_lista(ElementiAlbero* Root, ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito, ElementiAlbero* T_NIL)
{
    ElementiAlbero* P_Muovi;

    //NEL CASO IN CUI LA FINE COINCIDA CON L'INIZIO CI SONO DUE POSSIBILITà, O LA LISTA ERA VUOTA, OPPURE SIAMO ARRIVATI ALLA FINE DEL PERCORSO è QUESTO è IL CASO BASE PER TERMINARE L'ALGORITMO
    if(Fine == Inizio)
    {
        return PercorsoCostruito;
    }

    if(Inizio->Distanza < Fine->Distanza)
    {
        P_Muovi = Inizio;

        while(P_Muovi != Fine && raggiungibile(Fine->Distanza - P_Muovi->Distanza, P_Muovi->Next, T_NIL) == 0)
        {
            //CON LE LISTE MI MUOVO IN QUESTO MODO
            // P_Muovi = P_Muovi->Next;
            P_Muovi = tree_successor(P_Muovi, T_NIL);
        }

        if(P_Muovi != Fine && raggiungibile(Fine->Distanza - P_Muovi->Distanza, P_Muovi->Next, T_NIL) == 1)
        {
            PercorsoCostruito = malloc(sizeof(ElementiPercorso));
            PercorsoCostruito->NextP = Prec_PercorsoCostruito;
            PercorsoCostruito->NextT = P_Muovi;

            if(P_Muovi == Inizio)
            {
            	PercorsoCostruito->PrevP = NULL;
                return PercorsoCostruito;
            }
            else
            {
                PercorsoCostruito->PrevP = NULL;
                Prec_PercorsoCostruito = PercorsoCostruito;
                PercorsoCostruito->PrevP = pianifica_percorso_lista(Root, Inizio, P_Muovi, PercorsoCostruito->PrevP, Prec_PercorsoCostruito, T_NIL);
                return PercorsoCostruito;
            }
        }
        else //SIAMO ARRIVATI ALLA FINE QUINDI NON VI è ALCUN NODO CHE CI PERMETTA DI ARRIVARE ALLA FINE. IN TAL CASO AGGIUNGI IN TESTA ALLA LISTA PERCORSO, UN NULL CHE SERVE A CAPIRE CHE IL PERCORSO NON ESISTE, FACENDO SOLAMENTE UN CONTROLLO CHE CONSISTE NEL CONTROLLARE SE LA TESTA è UGUALE ALL'INIZIO, SE SI ALLORA IL PERCORSO è STATO COSTRUITO, SENNO IL PERCORSO NON è DISPONIBILE.
        {
            PercorsoCostruito = malloc(sizeof(ElementiPercorso));
            PercorsoCostruito->NextT = P_Muovi;
            PercorsoCostruito->NextP = Prec_PercorsoCostruito;
            PercorsoCostruito->PrevP = NULL;
            return PercorsoCostruito;
        }
    }
    
    return PercorsoCostruito;
}

ElementiAlbero* Cerca_Successore_Andata(ElementiAlbero* Root, int Dist_Inizio, int Dist_Fine, ElementiAlbero* Min_Successore, ElementiAlbero* T_NIL)
{
    if(Root != T_NIL)
    {
        if(Root->Distanza >= Dist_Inizio && Root->Distanza <= Dist_Fine)
        {
            if(raggiungibile(Dist_Fine - Root->Distanza, Root->Next, T_NIL) == 1)
                if(Min_Successore->Distanza > Root->Distanza)
                    Min_Successore = Root;
        }
        Min_Successore = Cerca_Successore_Andata(Root->Sx, Dist_Inizio, Dist_Fine, Min_Successore, T_NIL);
        Min_Successore = Cerca_Successore_Andata(Root->Dx, Dist_Inizio, Dist_Fine, Min_Successore, T_NIL);
        return Min_Successore;
    }
    else
        return Min_Successore;
}

ElementiPercorso* Costruisci_Lista_Contrario(ElementiAlbero* Root, ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito, ElementiAlbero* T_NIL)
{
    ElementiAlbero* P_Muovi;

    if(Fine == Inizio)
    {
        return PercorsoCostruito;
    }

    if(Inizio->Distanza > Fine->Distanza)
    {
        P_Muovi = Fine;

        P_Muovi = Cerca_Successore_Ritorno(Root, Inizio->Distanza, Fine->Distanza, P_Muovi, T_NIL);

        if(P_Muovi != Fine && raggiungibile(P_Muovi->Distanza - Fine->Distanza, P_Muovi->Next, T_NIL) == 1)
        {
            PercorsoCostruito = malloc(sizeof(ElementiPercorso));
            PercorsoCostruito->PrevP = Prec_PercorsoCostruito;
            PercorsoCostruito->NextT = P_Muovi;
            Prec_PercorsoCostruito->NextP = PercorsoCostruito;

            if(P_Muovi == Inizio)
            {
                PercorsoCostruito->NextP = NULL;
                return PercorsoCostruito;
            }
            else
            {
                PercorsoCostruito->NextP = NULL;
                Prec_PercorsoCostruito = PercorsoCostruito;
                PercorsoCostruito->NextP =  Costruisci_Lista_Contrario(Root, Inizio, P_Muovi, PercorsoCostruito->NextP, Prec_PercorsoCostruito, T_NIL);
                return PercorsoCostruito;
            }
        }
        else
        {
            PercorsoCostruito = malloc(sizeof(ElementiPercorso));
            PercorsoCostruito->NextT = P_Muovi;
            PercorsoCostruito->PrevP = Prec_PercorsoCostruito;
            Prec_PercorsoCostruito->NextP = PercorsoCostruito;
            PercorsoCostruito->NextP = NULL;
            return PercorsoCostruito;
        }

    }
    return PercorsoCostruito;
}

ElementiAlbero*  Cerca_Successore_Ritorno(ElementiAlbero* Root, int Dist_Inizio, int Dist_Fine, ElementiAlbero* Max_Successore, ElementiAlbero* T_NIL)
{
    if(Root != T_NIL)
    {
        if(Root->Distanza <= Dist_Inizio && Root->Distanza >= Dist_Fine)
        {
            if(raggiungibile(Root->Distanza - Dist_Fine, Root->Next, T_NIL) == 1)
                if(Max_Successore->Distanza < Root->Distanza)
                    Max_Successore = Root;
        }
        Max_Successore = Cerca_Successore_Ritorno(Root->Sx, Dist_Inizio, Dist_Fine, Max_Successore, T_NIL);
        Max_Successore = Cerca_Successore_Ritorno(Root->Dx, Dist_Inizio, Dist_Fine, Max_Successore, T_NIL);
        return Max_Successore;
    }
    else
        return Max_Successore;
}

int Sistema_Percorso(ElementiPercorso* Inizio, ElementiPercorso* Fine, ElementiPercorso* PercorsoCostruito, ElementiAlbero* T_NIL)
{
    ElementiAlbero* P_Muovi;
    int Modificato = 0;
    int Risultato;

    //CASO BASE
    if(PercorsoCostruito->NextP == NULL)
    {
        return 0;
    }
    else
    P_Muovi = tree_predecessor(PercorsoCostruito->NextT, T_NIL);

    while(P_Muovi != Fine->NextT && Modificato == 0)
    {
        if(raggiungibile(Inizio->NextT->Distanza - P_Muovi->Distanza, Inizio->NextT->Next, T_NIL) == 1)
        {
            if(raggiungibile(P_Muovi->Distanza - PercorsoCostruito->PrevP->NextT->Distanza, P_Muovi->Next, T_NIL) == 1)
            {
                //IN QUESTO CASO FACCIO LO SWITCH SENNO NON CAMBIO E VADO AVANTI CON I SUCCESSORI RIPETENDO LA STESSA DOMANDA
                PercorsoCostruito->NextT = P_Muovi;
                Modificato = 1;
            }
        }
        P_Muovi = tree_predecessor(P_Muovi, T_NIL);
    }
   

    if(Modificato == 1)
    {
        return 1;
    }
    else
    {
        Risultato = Sistema_Percorso(Inizio->NextP, PercorsoCostruito, Inizio, T_NIL);
        return Risultato;
    }
}

//++++++++++++++++FUNZIONI ALBERI ROSSO NERI++++++++++++++

ElementiAlbero* Insert_Fixup(ElementiAlbero* Root, ElementiAlbero* z, ElementiAlbero* T_NIL)
{
    ElementiAlbero *x, *y;

    if(z == Root)
        Root->Color = 0;
    else
    {
        x = z->P;
        if(x->Color == 1)
        {
            if(x == x->P->Sx)
            {
                y = x->P->Dx;
                if(y->Color == 1)
                {
                    x->Color = 0; //caso 1
                    y->Color = 0;
                    x->P->Color = 1;
                    Root = Insert_Fixup(Root, x->P, T_NIL);
                }
                else
                {
                    if(z == x->Dx)
                    {
                        z = x; //caso 2
                        Root = Left_Rotate(Root, z, T_NIL);
                        x = z->P;
                    }                
                	x->Color = 0; //caso 3
                x->P->Color = 1;
                Root = Right_Rotate(Root, x->P, T_NIL);
                }


            }
            else
            {
                if(x == x->P->Dx)
                {
                y = x->P->Sx;
                if(y->Color == 1)
                {
                    x->Color = 0;
                    y->Color = 0;
                    x->P->Color = 1;
                    Root = Insert_Fixup(Root, x->P, T_NIL);
                }
                else
                {
                    if(z == x->Sx)
                    {
                        z = x;
                        Root = Right_Rotate(Root, z, T_NIL);
                        x = z->P;
                    }
                    x->Color = 0;
                    x->P->Color = 1;
                    Root = Left_Rotate(Root, x->P, T_NIL);
                }

                }
            }
        }
    }

    return Root;
}


ElementiAlbero* Left_Rotate(ElementiAlbero* Root, ElementiAlbero* x, ElementiAlbero* T_NIL)
{
    ElementiAlbero *y;

    y = x->Dx;
    x->Dx = y->Sx;

    //T.NIL
    if(y->Sx != T_NIL)
    {
        y->Sx->P = x;
    }
    y->P = x->P;
    if(x->P == T_NIL)
        Root = y;
    else
    {
        if(x == x->P->Sx)
            x->P->Sx = y;
        else
        x->P->Dx = y;
    }
    y->Sx = x;
    x->P = y;

    return Root;
}

ElementiAlbero* Right_Rotate(ElementiAlbero* Root, ElementiAlbero* y, ElementiAlbero* T_NIL)
{
    ElementiAlbero* x;

    x = y->Sx;

    y->Sx = x->Dx;

    if(x->Dx != T_NIL)
    {
        x->Dx->P = y;
    }
    x->P = y->P;
    if(y->P == T_NIL)
    {
        Root = x;
    }
    else
    {
        if(y == y->P->Dx)
            y->P->Dx = x;
        else
            y->P->Sx = x;
    }
    x->Dx = y;
    y->P = x;

    return Root;
}

ElementiAlbero* Delete_Fixup(ElementiAlbero* Root, ElementiAlbero* x, ElementiAlbero* T_NIL)
{

    ElementiAlbero *w;

    if(x->P == T_NIL || x->Color == 1)
        x->Color = 0;
    else
    {
        if(x == x->P->Sx)
        {
            w = x->P->Dx;
            if(w->Color == 1)
            {
                w->Color = 0;
                x->P->Color = 1;
                Root = Left_Rotate(Root,x->P, T_NIL);
                w = x->P->Dx;
            }
            if(w->Sx->Color == 0 && w->Dx->Color == 0)
            {
                w->Color = 1;
                Root = Delete_Fixup(Root, x->P, T_NIL);
            }
            else
            {
                if(w->Dx->Color == 0)
                {
                    w->Sx->Color = 0;
                    w->Color = 1;
                    Root = Right_Rotate(Root, w, T_NIL);
                    w = x->P->Dx;
                }           
            w->Color = x->P->Color;
            x->P->Color = 0;
            w->Dx->Color = 0;
            Root = Left_Rotate(Root, x->P, T_NIL);

            }           

        }
        else
        {
            if(x == x->P->Dx)
            {
            w = x->P->Sx;
            if(w->Color == 1)
            {
                w->Color = 0;
                x->P->Color = 1;
                Root = Right_Rotate(Root,x->P, T_NIL);
                w = x->P->Sx;
            }
            if(w->Dx->Color == 0 && w->Sx->Color == 0)
            {
                w->Color = 1;
                Root = Delete_Fixup(Root, x->P, T_NIL);
            }
            else
            {
                if(w->Sx->Color == 0)
                {
                    w->Dx->Color = 0;
                    w->Color = 1;
                    Root = Left_Rotate(Root, w, T_NIL);
                    w = x->P->Sx;
                }            
            w->Color = x->P->Color;
            x->P->Color = 0;
            w->Sx->Color = 0;
            Root = Right_Rotate(Root, x->P, T_NIL);
            }            


            }
        }
    } 

    return Root;  
}

ElementiAlbero* CancellaAlbero(ElementiAlbero* Root, ElementiAlbero* T_NIL)
{
    ElementiAlbero* Supporto;
    if(Root == T_NIL)
        return T_NIL;
    else
    {
        Root->Sx = CancellaAlbero(Root->Sx, T_NIL);
        Root->Dx = CancellaAlbero(Root->Dx, T_NIL);
	
        if(Root->P != T_NIL)
        {
            if(Root == Root->P->Sx)
                Root->P->Sx = T_NIL;
            else
                Root->P->Dx = T_NIL;
        Root->Next = cancellalista(Root->Next, T_NIL);
        free(Root);
        return Root;
        }
        else
        {
            Supporto = Root;
            Root->Next = cancellalista(Root->Next, T_NIL);
            Root = T_NIL;
            free(Supporto);
            return Root;
        }
    }

}