
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2020
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
}

void DLDisposeList (tDLList *L) {
    //cyklus prejde zoznamom a zruší všetky prvky
    tDLElemPtr tmp;
    tmp = L->First;
    while(L->First != NULL){
        L->First = L->First->rptr;
        free(tmp);
    }
    //nastavenie vštkých ukazovateľov zoznamu na NULL
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
}

void DLInsertFirst (tDLList *L, int val) {
    //alokovanie nového prvku
    tDLElemPtr tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem));
    if(!tmp){
        DLError();
        return;
    }
    tmp->data = val; //nastavenie dát
    tmp->rptr = L->First; //nastavenie pravého ukazovateľa na pôvodný prvý prvok
    tmp->lptr = NULL; //nastavenie ľavého ukazovateľa na NULL
    //kontrola či zoznam nieje prázdny
    if(L->First != NULL){
        L->First->lptr = tmp; //nastavenie ľavého ukazovateľa na nový prvok
    }
    else{
        L->Last = tmp; //nastavenie posledného prvku na nový prvok
    }
    L->First = tmp; //nastavenie nového prvku na prvý

/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
}

void DLInsertLast(tDLList *L, int val) {
    //alokovanie nového prvku
    tDLElemPtr tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem));
    if(!tmp){
        DLError();
        return;
    }
    tmp->data = val; //nastavenie dát
    tmp->lptr = L->Last; //nastavenie ľavého ukazovateľa na pôvodný posledný prvok
    tmp->rptr = NULL; //nastavenie pravého ukazovateľa na NULL
    //kontrola či zoznam nieje prázdny
    if(L->Last != NULL){
        L->Last->rptr = tmp; //nastavenie pravého ukazovateľa na nový prvok
    }
    else{
        L->First = tmp; //nastavenie prvého prvku na nový prvok
    }
    L->Last = tmp; //nastavenie nového prvku na posledný
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
}

void DLFirst (tDLList *L) {
    L->Act = L->First; //nastavenie prvého prvku na aktívny
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
}

void DLLast (tDLList *L) {
    L->Act = L->Last; //nastavenie posledného prvku ako aktívny
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/	
}

void DLCopyFirst (tDLList *L, int *val) {
    //kontrola že zoznam nieje prázdny
    if(L->First != NULL){
        *val = L->First->data; ////data z prvého prvku sa skopírujú do val
    }
    else{
        DLError();
        return;
    }
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
}

void DLCopyLast (tDLList *L, int *val) {
    //kontrola že zoznam nieje prázdny
    if(L->Last != NULL){
        *val = L->Last->data; ////data z posledného prvku sa skopírujú do val
    }
    else{
        DLError();
        return;
    }
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
}

void DLDeleteFirst (tDLList *L) {
    tDLElemPtr tmp;
    //kontrola že zoznam nieje prázdny
    if(L->First != NULL){
        tmp = L->First;
        //ak je prvý prvok aktívny, aktivita sa stráca
        if(L->Act == L->First){
            L->Act = NULL;
        }
        //ak je prvý prvok zároveň posledný, obidve budú NULL
        if(L->First == L->Last){
            L->First = NULL;
            L->Last = NULL;
        }
        else{
            L->First = L->First->rptr; //aktualiuácia začiatku zoznamu
            L->First->lptr = NULL; //nastavenie ukazovateľa vľavo na NULL
        }
        free(tmp); //uvolnenie
    }
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
}	

void DLDeleteLast (tDLList *L) {
    tDLElemPtr tmp;
    //kontrola že zoznam nieje prázdny
    if(L->Last != NULL){
        tmp = L->Last;
        //ak je posledný prvok aktívny, aktivita sa stráca
        if(L->Act == L->Last){
            L->Act = NULL;
        }
        //ak je posledný prvok zároveň prvý, obidvé budú NULL
        if(L->Last == L->First){
            L->Last = NULL;
            L->First = NULL;
        }
        else{
            L->Last = L->Last->lptr; //aktualizácia konca zoznamu
            L->Last->rptr = NULL; //nastavenie ukazovateľa vpravo na NULL
        }
        free(tmp); //uvolnenie
    }
/*
** Zruší poslední prvek seznamu L.
** Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/ 
}

void DLPostDelete (tDLList *L) {
    //kontrola či je zoznam aktívny a či je čo zrušiť
    if(L->Act != NULL){
        if(L->Act->rptr != NULL){
            tDLElemPtr tmp;
            tmp = L->Act->rptr; //ukazovateľ na rušený prvok
            L->Act->rptr = tmp->rptr; //preklenutie rušeného prvku
            //ak je tmp posledný prvok, nastavenie na aktívny
            if(tmp == L->Last){
                L->Last = L->Act;
            }
            //ak nieje, ľavý ukazateľ prvku za tmp bude aktívny prvok
            else{
                tmp->rptr->lptr = L->Act;
            } 
            free(tmp); //uvolnenie
        }
    }
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
}

void DLPreDelete (tDLList *L) {
    //kontrola či je zoznam aktívny a či je čo zrušiť
    if(L->Act != NULL){
        if(L->Act->lptr != NULL){
            tDLElemPtr tmp;
            tmp = L->Act->lptr; //ukazovateľ na rušený prvok
            L->Act->lptr = tmp->lptr; //preklenutie rušného prvku
            //ak je tmp prvý prvok, nastavenie na aktívny
            if(tmp == L->First){
                L->First = L->Act;
            }
            //ak nieje, pravý ukazateľ prvku pred tmp bude aktívny prvok
            else{
                tmp->lptr->rptr = L->Act;
            }
            free(tmp); //uvolnenie
        }
    }
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
}

void DLPostInsert (tDLList *L, int val) {
    //kontrola či je zoznam aktívny
    if(L->Act != NULL){
        //alokácia nového prvku
        tDLElemPtr tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem));
        if(!tmp){
            DLError();
            return;
        }
        tmp->data = val; //nastavenie dát
        tmp->rptr = L->Act->rptr; //nastavenie pravého ukazovateľa na pravý ukazateľ aktívneho prvku
        tmp->lptr = L->Act; //nastavenie ľavého ukazovateľa na aktívny prvok
        L->Act->rptr = tmp;
        //ak je aktívny prvok posledný, nový prvok bude posledný
        if(L->Act == L->Last){
            L->Last = tmp;
        }
        //ak nieje, nastavenie ľavého ukazovateľa prvku napravo na nový prvok
        else{
            tmp->rptr->lptr = tmp;
        }
    }
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
}

void DLPreInsert (tDLList *L, int val) {
    //kontrola či je zoznam aktívny
    if(L->Act != NULL){
        //alokácia nového prvku
        tDLElemPtr tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem));
        if(!tmp){
            DLError();
            return;
        }
        tmp->lptr = L->Act->lptr; //nastavenie ľavého ukazovateľa na ľavý ukazzateľ aktívneho prvku
        L->Act->lptr->rptr = tmp; //nastavenie prvého ukazovateľa prvku pred aktívnym prvok na tmp
        L->Act->lptr = tmp; //nastavenie ľavého ukazovateľa aktívneho prvku na nový prvok
        tmp->rptr = L->Act; //nastavenie pravého ukazovateľa nového prvku na aktívny
        tmp->data = val; //uloženie dát

    }
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
}

void DLCopy (tDLList *L, int *val) {
    //kontrola či je zoznam aktívny
    if(L->Act != NULL){
        *val = L->Act->data; //dáta aktívneho prvku uložené do val
    }
    else{
        DLError();
        return;
    }
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
}

void DLActualize (tDLList *L, int val) {
    //kontrola či je zoznam aktívny
    if(L->Act != NULL){
        L->Act->data = val; //aktualizovanie aktívneho prvku
    }
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
}

void DLSucc (tDLList *L) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        L->Act = L->Act->rptr; //posun aktivity na nasledujúci
    }
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
}


void DLPred (tDLList *L) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        L->Act = L->Act->lptr; //posun aktivity na predchádzajúci
    }
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
}

int DLActive (tDLList *L) {
    //kontrola že je zoznam aktívny
    return L->Act != NULL;
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
}

/* Konec c206.c*/
