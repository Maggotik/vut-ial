
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                              Úpravy: Kamil Jeřábek, září 2020
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      DisposeList ... zrušení všech prvků seznamu,
**      InitList ...... inicializace seznamu před prvním použitím,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int errflg;
int solved;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
    L->Act = NULL;
    L->First = NULL;
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
}

void DisposeList (tList *L) {
    //cyklus prejde zoznamom a zruší všetky prvky
    tElemPtr tmp;
    tmp = L->First;
    while(L->First != NULL){
        L->First = tmp->ptr;
        free(tmp);
    }
    //nastavenie vštkých ukazovateľov zoznamu na NULL
    L->First = NULL;
    L->Act = NULL;
    
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
}

void InsertFirst (tList *L, int val) {
    //alokovanie nového prvku
    tElemPtr tmp =(tElemPtr) malloc(sizeof(struct tElem));
    if(!tmp){
        Error();
        return;
    }
    tmp->data = val; //nastavenie dátovej zložky
    tmp->ptr = L->First; //nastavenie ukazovateľa na začiatok
    L->First = tmp; //na začiatku bude nový prcok
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    

/* V případě řešení, smažte tento řádek! */
}

void First (tList *L) {
    L->Act = L->First; //nastavenie prvého prvku ako aktívny
/*  
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
                  /* V případě řešení, smažte tento řádek! */
}

void CopyFirst (tList *L, int *val) {
    //kontrola či je zoznam prázdny
    if(L->Act != NULL){
        *val = L->First->data; //data z prvého prvku sa skopírujú do val
    }
    else{
        Error();
        return;
    }
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
}

void DeleteFirst (tList *L) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        tElemPtr tmp;
        tmp = L->First;
        L->First = tmp->ptr;
        //ak je prvý aktívny, aktivita sa stratí
        if(tmp == L->Act){
            L->Act = NULL;
        }
        free(tmp); //uvolnenie
    }
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
}	

void PostDelete (tList *L) {
    tElemPtr tmp;
    //kontrola ze je zoznam aktívny a že je čo zrušiť
    if(L->Act != NULL){
        if(L->Act->ptr != NULL){
            tmp = L->Act->ptr; //ukazateľ prvok ktorý rušíme
            L->Act->ptr = tmp->ptr; //preklenutie
            free(tmp); //uvolnenie
        }
    }

/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
}

void PostInsert (tList *L, int val) {
    //kontrola či je zoznam aktívny
    if(L->Act != NULL){
        //alokácia nového prvku
        tElemPtr tmp =(tElemPtr) malloc(sizeof(struct tElem));
        if(!tmp){
            Error();
            return;
        }
    tmp->data = val; //nastavenie dátovej zložky
    tmp->ptr = L->Act->ptr; //nastavenie ukazovateľa kam sa budú dáta vkladať
    L->Act->ptr = tmp; //nastavenie dát
    }
    else{
        Error();
        return;
    }
    
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
}

void Copy (tList *L, int *val) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        *val = L->Act->data; //dáta aktívneho prvku uložené do val
    }
    else{
        Error();
        return;
    }
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
}

void Actualize (tList *L, int val) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        L->Act->data = val; //aktualizovanie aktívneho prvku
    }
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
}

void Succ (tList *L) {
    //kontrola že je zoznam aktívny
    if(L->Act != NULL){
        L->Act = L->Act->ptr; //posun aktivity
    }
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
}

int Active (tList *L) {
    //kontrola že je zoznam aktívny
    return L->Act != NULL;
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
}

/* Konec c201.c */
