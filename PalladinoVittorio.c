#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct El_List
{
    int Autonomia;
    struct El_List* Next;
}ElementiLista;

typedef struct El_Tree
{
    int Auto_Max;
    int Distanza;
    struct El_Tree* P;
    struct El_Tree* Sx;
    struct El_Tree* Dx;
    struct El_List* Next;
}ElementiAlbero;

typedef struct El_Percorso
{
    struct El_Percorso* PrevP;
    struct El_Percorso* NextP;
    struct El_Tree* NextT;
}ElementiPercorso;

typedef ElementiAlbero* tree;
typedef ElementiLista* PuntaLista;


/*FUNZIONI AUSILIARE*/
/*+++++++++++++++++++++++++++++++++++++++*/

int raggiungibile(int Dist, ElementiAlbero* Nodo);

void inorder_tree_walk(ElementiAlbero* Root);

void stampalista(ElementiLista* L);

ElementiLista* cancellalista(ElementiLista* L);

ElementiLista* cancellalista_elemento(ElementiAlbero* Nodo, int Autonomia);

ElementiLista* aggiungilista_elemento(ElementiAlbero* Nodo, ElementiLista* L, int Autonomia);

ElementiAlbero* tree_search(ElementiAlbero* Root, int Dist);

ElementiAlbero* tree_successor(ElementiAlbero* x);

ElementiAlbero* tree_minimum(ElementiAlbero* x);

ElementiAlbero* tree_maximun(ElementiAlbero* x);

ElementiPercorso* cancellalista_percorso(ElementiPercorso* P);

ElementiPercorso* cancellalista_percorso_contrario(ElementiPercorso* P);

void stampalista_percorso(ElementiPercorso* P);

void stampalista_percorso_contrario(ElementiPercorso* P);

ElementiAlbero* tree_predecessor(ElementiAlbero* x);

ElementiAlbero* CancellaAlbero(ElementiAlbero* Root);

/*++++++++++++++++++++++++++++++++++++++*/
/*FUNZIONE PROGETTO*/

ElementiAlbero* aggiungi_stazione(ElementiLista* L, ElementiAlbero* Root, int Max_Autonomia);

ElementiAlbero* demolisci_stazione(ElementiLista* L, ElementiAlbero* Root);

ElementiAlbero* rottama_auto(ElementiAlbero* Root,ElementiLista* L_DaRottamare);

ElementiAlbero* aggiungi_auto(ElementiAlbero* Root, ElementiLista* L_DaAggiungere);

ElementiPercorso* pianifica_percorso_lista(ElementiAlbero *Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito);

ElementiPercorso* Costruisci_Lista_Contrario(ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito);

int Sistema_Percorso(ElementiPercorso* Inizio, ElementiPercorso* Fine, ElementiPercorso* MuoviPercorso);

/*++++++++++++++++++++++++++++++++++++++*/

int main()
{
    //LA VARIABILE INIZIO PERCORSO SERVE NEL CASO IN CUI FINE.DISTANZA < INIZIO.DISTANZA PER NON CAMBIARE LA FUNZIONE DI STAMPA PERCORSO
    char parola1[50];
    char parola2[50];
    ElementiLista *L , *P;
    ElementiAlbero* Radice = NULL, *Inizio, *Fine;
    ElementiPercorso* Percorso = NULL, *PercorsoCostruito = NULL, *PrecPercorso = NULL;
    ElementiPercorso* Percorso2 = NULL, *PercorsoCostruito2 = NULL, *PrecPercorso2 = NULL, *FinePercorso2 = NULL;
    int lettere, ritorno_sistema = 0;
    int Max_Autonomia;
    int i;

 
/*INPUT DA STDIN*/

while(scanf("%[^-]-%s ", parola1, parola2) != EOF)
    {
            L = malloc(sizeof(ElementiLista));
            P = L;

            Max_Autonomia = -1;
            i = 0;
            lettere = scanf("%d", &(P->Autonomia));
            if(lettere != 1)
            printf("errore");
        

          while(fgetc(stdin) != '\n') // raggiungo la fine della riga
            {
                P->Next = malloc(sizeof(ElementiLista));
                P = P->Next;
                lettere = scanf("%d", &(P->Autonomia)); // continua a leggere gli interi fino ad incotrare la newline
                if(i == 1)
                {
                    if(P->Autonomia > Max_Autonomia)
                        Max_Autonomia = P->Autonomia;
                }
                else
                    i++;
            }
            P->Next = NULL;

            if(strcmp(parola1, "aggiungi") == 0)
            {
                if(strcmp(parola2, "auto") == 0)
                {
                    Radice = aggiungi_auto(Radice, L);
                    L = cancellalista(L);
                }
                if(strcmp(parola2, "stazione") == 0)
                {
                    Radice = aggiungi_stazione(L, Radice, Max_Autonomia);
                }
            }
            if(strcmp(parola1, "demolisci") == 0)
            {
                if(strcmp(parola2, "stazione") == 0)
                {
                   Radice = demolisci_stazione(L, Radice);
                   L = cancellalista(L);
                }
            }
            if(strcmp(parola1, "rottama") == 0)
            {
                if(strcmp(parola2, "auto") == 0)
                {
                   Radice = rottama_auto(Radice, L);
                   L = cancellalista(L);
                }
            }
            if(strcmp(parola1, "pianifica") == 0)
            {
                if(strcmp(parola2, "percorso") == 0)
                {
                    Inizio = tree_search(Radice, L->Autonomia);
                    Fine = tree_search(Radice, L->Next->Autonomia);
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
                            Percorso = pianifica_percorso_lista(Inizio, Fine, PercorsoCostruito->PrevP, PrecPercorso);
                        }
                        if(L->Autonomia > L->Next->Autonomia)
                        {              
                            //PRIMO: COSTRUISCO LA LISTA AL CONTRARIO UTILIZZANDO I PRECEDECESSORI 

                            PercorsoCostruito2 = malloc(sizeof(ElementiPercorso));
                            PercorsoCostruito2->NextT = Fine;
                            PercorsoCostruito2->NextP = NULL;
                            PercorsoCostruito2->PrevP = NULL;
                            PrecPercorso2 = PercorsoCostruito2;
                            
                            Percorso2 = Costruisci_Lista_Contrario(Inizio, Fine, PercorsoCostruito2->NextP, PrecPercorso2);


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
                                Percorso2 = cancellalista_percorso_contrario(Percorso2);
                                free(PercorsoCostruito);
                            }
                            else
                            { 
                            //PERCORSO PUNTA ALL'INIZIO, LO RIPORTO ALLA FINE
                            //PROVO AD INVERTIRE IL FUNZIONAMENTO DI SISTEMA PERCORSO FACENDOLO PARTIRE DALL'INIZIO
                               
                            
                                do 
                                {
                                  ritorno_sistema = Sistema_Percorso(FinePercorso2->NextP->NextP, FinePercorso2, FinePercorso2->NextP);
                               //   ritorno_sistema = Sistema_Percorso(Percorso2, Percorso2->PrevP->PrevP, Percorso2->PrevP);
                            
                                }while(ritorno_sistema == 1);
                              

                                while(Percorso2->NextP != NULL)
                                {
                                Percorso2 = Percorso2->NextP;
                                }   
                                stampalista_percorso_contrario(Percorso2);
                                printf("\n");
                                Percorso2 = cancellalista_percorso_contrario(Percorso2);
                                //cancello percorsocostruito che viene \u00e8 stato creato ma viene usato solo se siamo nel secondo caso
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
                            stampalista_percorso(Percorso);
                            printf("\n");
                        }
                        Percorso = cancellalista_percorso(Percorso);
                    }
                    L = cancellalista(L);
                    
                }
            }



        }

    Radice = CancellaAlbero(Radice);



    return 0;
}

void stampalista(ElementiLista* L)
{
    if(L == NULL)
        return;
    printf("%d ", L->Autonomia);
    stampalista(L->Next);
}

ElementiLista* cancellalista(ElementiLista* L)
{
    if(L != NULL)
    {
        L->Next = cancellalista(L->Next);
        free(L);
    }
    return NULL;
}


ElementiLista* cancellalista_elemento(ElementiAlbero* Nodo, int Autonomia)
{
    ElementiLista* Pred = NULL;
    ElementiLista* Muovi = Nodo->Next;
    ElementiLista* InizioLista = NULL;
    int cancellato = 0;
    int Max = -1;

    if(Muovi->Autonomia == Autonomia)
    {
        Nodo->Next = Muovi->Next;
        free(Muovi);
        cancellato = 1;
        if(Autonomia == Nodo->Auto_Max)
        {
            InizioLista = Nodo->Next;
            while(InizioLista != NULL)
            {
                if(InizioLista->Autonomia > Max)
                {
                    Max = InizioLista->Autonomia;
                }
                InizioLista = InizioLista->Next;
            }
            Nodo->Auto_Max = Max;
        }
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
                if(Autonomia == Nodo->Auto_Max)
                {
                    InizioLista = Nodo->Next;
                    while(InizioLista != NULL)
                    {
                        if(InizioLista->Autonomia > Max)
                        {
                            Max = InizioLista->Autonomia;
                        }
                    InizioLista = InizioLista->Next;
                    }

                    Nodo->Auto_Max = Max;
                }
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

ElementiLista* aggiungilista_elemento(ElementiAlbero* Nodo, ElementiLista* L, int Autonomia)
{
    ElementiLista *L_Aggiungi;

if(Autonomia > Nodo->Auto_Max)
{
    Nodo->Auto_Max = Autonomia;
}

    //nodo da aggingere
    L_Aggiungi = malloc(sizeof(ElementiLista)); 
    L_Aggiungi->Autonomia = Autonomia;

    L_Aggiungi->Next = Nodo->Next;
    Nodo->Next = L_Aggiungi;
    printf("aggiunta\n");

    return Nodo->Next;
}

void inorder_tree_walk(ElementiAlbero* x)
{
    if(x != NULL)
    {
        printf("%d ", x->Distanza);
        inorder_tree_walk(x->Sx);
        inorder_tree_walk(x->Dx);
    }
}

ElementiAlbero* tree_search(ElementiAlbero* Root, int Dist)
{   
    if(Root == NULL || Dist == Root->Distanza)
        return Root;
    if(Dist < Root->Distanza)
        return tree_search(Root->Sx, Dist);
    else return tree_search(Root->Dx, Dist);
}

ElementiAlbero* tree_successor(ElementiAlbero* x)
{
    ElementiAlbero* y;
    if(x->Dx != NULL)
        return tree_minimum(x->Dx);
    y = x->P;
    while(y != NULL && x == y->Dx)
    {
        x = y;
        y = y->P;
    }
    return y;
}

ElementiAlbero* tree_minimum(ElementiAlbero* x)
{
    while(x->Sx != NULL)
        x = x->Sx;
    return x;
}

ElementiAlbero* aggiungi_stazione(ElementiLista* L, ElementiAlbero* Root, int Max_Autonomia) 
/*contiene la radice dell'albero e la lista da aggiungere*/
{
    ElementiAlbero *Nuovo, *y, *x;

    Nuovo = malloc(sizeof(ElementiAlbero));

    Nuovo->Next = NULL;
    Nuovo->Dx = NULL;
    Nuovo->Sx = NULL;
    Nuovo->P = NULL;
    Nuovo->Auto_Max = Max_Autonomia;
    
    y = NULL;
    x = Root;
    Nuovo->Distanza = L->Autonomia;

    while(x != NULL)
    {
        y = x;
        if(Nuovo->Distanza == x->Distanza)
        {
            free(Nuovo);
            L = cancellalista(L);
            printf("non aggiunta\n");
            return Root;
        }
        if(Nuovo->Distanza < x->Distanza)
            x = x->Sx;
        else x = x->Dx;
    }
    Nuovo->P = y;
    if(y ==  NULL)
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
    //ELIMINO I PRIMI DUE ELEMENTI DELLA LISTA CHE CONTENEVANO DISTANZA E NUMERO DI MACCHINE
    free(L->Next);
    free(L);
    printf("aggiunta\n");

    return Root;

}

//ritorna il nodo eleminato
ElementiAlbero* demolisci_stazione(ElementiLista* L, ElementiAlbero* Root)
{
    ElementiAlbero* ToDelete, *y, *x;
    ElementiLista* ListaDaCancellareScambio;

    ToDelete = tree_search(Root, L->Autonomia);

    if(ToDelete == NULL)
    {
        printf("non demolita\n");
        return Root;
    }



    if(ToDelete->Sx == NULL || ToDelete->Dx == NULL)
        y = ToDelete;
    else
        y = tree_successor(ToDelete);
    if(y->Sx != NULL)
        x = y->Sx;
    else x = y->Dx;
    if(x != NULL)
        x->P = y->P;
    if(y->P == NULL)
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
        ToDelete->Auto_Max = y->Auto_Max;
        ToDelete->Distanza = y->Distanza;
        ListaDaCancellareScambio = ToDelete->Next;
        ToDelete->Next = y->Next;
    }
    else
    {
        ListaDaCancellareScambio = y->Next;
    }
            

    

    y->Next = cancellalista(ListaDaCancellareScambio);
    printf("demolita\n");
    free(y);

    return Root;
}

ElementiAlbero* rottama_auto(ElementiAlbero* Root, ElementiLista* L_DaRottomare)
{
    ElementiAlbero* NodoLista_ToDelete;
    int AutonomiaDaEliminare;

    NodoLista_ToDelete = tree_search(Root, L_DaRottomare->Autonomia); // ho trovato il nodo nella cui lista devo cercare l'elemento da eliminare

    if(NodoLista_ToDelete == NULL)
    {
        printf("non rottamata\n");
        return Root;
    }
    if(NodoLista_ToDelete->Next == NULL)
    {
        printf("non rottamata\n");
        return Root;
    }

    AutonomiaDaEliminare = L_DaRottomare->Next->Autonomia;
    
    //rottamo la macchina
    NodoLista_ToDelete->Next = cancellalista_elemento(NodoLista_ToDelete, AutonomiaDaEliminare);

    return Root;
}

ElementiAlbero* aggiungi_auto(ElementiAlbero* Root, ElementiLista* L_DaAggiungere)
{
    ElementiAlbero* Nodo;
    int Distanza;
    Distanza = L_DaAggiungere->Autonomia;

    Nodo = tree_search(Root, Distanza);
    if(Nodo == NULL)
    {
        printf("non aggiunta\n");
        return Root;
    }

    Nodo->Next = aggiungilista_elemento(Nodo, L_DaAggiungere, L_DaAggiungere->Next->Autonomia);


    return Root;
}


int raggiungibile(int Dist, ElementiAlbero* Nodo)
{
    /*RICERCA DI UN ELEMENTO IN UNA LISTA*/
    
    //PER EVITARE DI SCORRERE OGNI VOLTA LA LISTA DELLE AUTONOMOBILI

        if(Nodo->Auto_Max >= Dist)
            return 1;
        else
            return 0; //non raggiungibile
}

ElementiPercorso* cancellalista_percorso(ElementiPercorso* P)
{
    if(P != NULL)
    {
        P->NextP = cancellalista_percorso(P->NextP);
        free(P);
    }
    return NULL;
}

ElementiPercorso* cancellalista_percorso_contrario(ElementiPercorso* P)
{
    ElementiPercorso* P1;

    if(P != NULL)
    {
        P1 = P->PrevP;
        free(P);
        cancellalista_percorso_contrario(P1);
        return NULL;
    }
    return NULL;
}

void stampalista_percorso_contrario(ElementiPercorso* P)
{
    if(P != NULL)
    {
        if(P->PrevP == NULL)
            printf("%d", P->NextT->Distanza);
        else
            printf("%d ", P->NextT->Distanza);
        stampalista_percorso_contrario(P->PrevP);
    }

}

void stampalista_percorso(ElementiPercorso* P)
{
    if(P != NULL)
    {
        //ULTIMO ELEMENTO
        if(P->NextP == NULL)
        {
            printf("%d", P->NextT->Distanza);  
            stampalista_percorso(P->NextP);  
        }
        else
        {
            printf("%d ", P->NextT->Distanza);
            stampalista_percorso(P->NextP);
        }

    }
}

ElementiAlbero* tree_maximun(ElementiAlbero* x)
{
    while(x->Dx != NULL)
        x = x->Dx;
    return x;
}

ElementiPercorso* pianifica_percorso_lista(ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito)
{
    ElementiAlbero* P_Muovi;

    if(Fine == Inizio)
    {
        return PercorsoCostruito;
    }

    if(Inizio->Distanza < Fine->Distanza)
    {
        P_Muovi = Inizio;

        while(P_Muovi != Fine && raggiungibile(Fine->Distanza - P_Muovi->Distanza, P_Muovi) == 0)
        {
            // P_Muovi = P_Muovi->Next;
            P_Muovi = tree_successor(P_Muovi);
        }

        if(P_Muovi != Fine && raggiungibile(Fine->Distanza - P_Muovi->Distanza, P_Muovi) == 1)
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
                PercorsoCostruito->PrevP =  pianifica_percorso_lista(Inizio, P_Muovi, PercorsoCostruito->PrevP, Prec_PercorsoCostruito);
                return PercorsoCostruito;
            }
        }
        else
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

ElementiAlbero* tree_predecessor(ElementiAlbero* x)
{
    ElementiAlbero* y;
    if(x->Sx != NULL)
        return tree_maximun(x->Sx);
    y = x->P;
    while(y != NULL && x == y->Sx)
    {
        x = y;
        y = y->P;
    }
    return y;
}

void stampalista_percorso_contrario2(ElementiPercorso* X)
{
    ElementiPercorso* P;
    P = X;

    while(P != NULL)
    {
        if(P->PrevP == NULL)
            printf("%d", P->NextT->Distanza);
        else
            printf("%d ", P->NextT->Distanza);
        
        P = P->PrevP;
    }
}

ElementiPercorso* Costruisci_Lista_Contrario(ElementiAlbero* Inizio, ElementiAlbero* Fine, ElementiPercorso* PercorsoCostruito, ElementiPercorso* Prec_PercorsoCostruito)
{
    ElementiAlbero* P_Muovi;

    if(Fine == Inizio)
    {
        return PercorsoCostruito;
    }

    if(Inizio->Distanza > Fine->Distanza)
    {
        P_Muovi = Inizio;

        while(P_Muovi != Fine && raggiungibile(P_Muovi->Distanza - Fine->Distanza, P_Muovi) == 0)
        {
            P_Muovi = tree_predecessor(P_Muovi);
        }

        if(P_Muovi != Fine && raggiungibile(P_Muovi->Distanza - Fine->Distanza, P_Muovi) == 1)
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
                PercorsoCostruito->NextP =  Costruisci_Lista_Contrario(Inizio, P_Muovi, PercorsoCostruito->NextP, Prec_PercorsoCostruito);
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

//con predecessore : da basso ad alto
int Sistema_Percorso(ElementiPercorso* Inizio, ElementiPercorso* Fine, ElementiPercorso* PercorsoCostruito)
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
    P_Muovi = tree_predecessor(PercorsoCostruito->NextT);

    while(P_Muovi != Fine->NextT && Modificato == 0)
    {
        if(raggiungibile(Inizio->NextT->Distanza - P_Muovi->Distanza, Inizio->NextT) == 1)
        {
            if(raggiungibile(P_Muovi->Distanza - PercorsoCostruito->PrevP->NextT->Distanza, P_Muovi) == 1)
            {
                PercorsoCostruito->NextT = P_Muovi;
                Modificato = 1;
            }
        }
        P_Muovi = tree_predecessor(P_Muovi);
    }
   

    if(Modificato == 1)
    {
        return 1;
    }
    else
    {
        Risultato = Sistema_Percorso(Inizio->NextP, PercorsoCostruito, Inizio);
        return Risultato;
    }
}

ElementiAlbero* CancellaAlbero(ElementiAlbero* Root)
{
    ElementiAlbero* Supporto;
    if(Root == NULL)
        return NULL;
    else
    {
        Root->Sx = CancellaAlbero(Root->Sx);
        Root->Dx = CancellaAlbero(Root->Dx);
	
        if(Root->P != NULL)
        {
            if(Root == Root->P->Sx)
                Root->P->Sx = NULL;
            else
                Root->P->Dx = NULL;
        Root->Next = cancellalista(Root->Next);
        free(Root);
        return Root;
        }
        else
        {
            Supporto = Root;
            Root->Next = cancellalista(Root->Next);
            Root = NULL;
            free(Supporto);
            return Root;
        }
    }

}
