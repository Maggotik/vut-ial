
/* c016.c: **********************************************************}
{* Téma:  Tabulka s Rozptýlenými Položkami
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2014
**                              Radek Hranický, 2014-2018
**
** Vytvořete abstraktní datový typ
** TRP (Tabulka s Rozptýlenými Položkami = Hash table)
** s explicitně řetězenými synonymy. Tabulka je implementována polem
** lineárních seznamů synonym.
**
** Implementujte následující procedury a funkce.
**
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky (inicializace tabulky
**                 poté, co již byla použita)
**
** Definici typů naleznete v souboru c016.h.
**
** Tabulka je reprezentována datovou strukturou typu tHTable,
** která se skládá z ukazatelů na položky, jež obsahují složky
** klíče 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na další synonymum 'ptrnext'. Při implementaci funkcí
** uvažujte maximální rozměr pole HTSIZE.
**
** U všech procedur využívejte rozptylovou funkci hashCode.  Povšimněte si
** způsobu předávání parametrů a zamyslete se nad tím, zda je možné parametry
** předávat jiným způsobem (hodnotou/odkazem) a v případě, že jsou obě
** možnosti funkčně přípustné, jaké jsou výhody či nevýhody toho či onoho
** způsobu.
**
** V příkladech jsou použity položky, kde klíčem je řetězec, ke kterému
** je přidán obsah - reálné číslo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

void htInit ( tHTable* ptrht ) {
	//nastavenie vštkých ukazovateľov na NULL
	for(int i = 0; i < HTSIZE; i++){
		(*ptrht)[i] = NULL;
	}

}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není,
** vrací se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {
	//zistenie a pristúpenie k položke tabuľky 
	int index = hashCode(key);
	tHTItem *tmp = (*ptrht)[index];
	//prechod cyklusom kým sa nenájde hľadaný kľúč
	for(; tmp; tmp = tmp->ptrnext){
		if(tmp->key == key)
			return tmp; //vracia ukazateľ na nájdený prvok
	}
	//vracia NULL ak nenašlo prvok
	return NULL;
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
	tHTItem *tmp = htSearch(ptrht, key);
	//ak sa už v tabuľke nachádza, aktualizuje jeho dátovú časť
	if(tmp)
	{
		tmp->data = data;
		return;
	}
	tHTItem *newtmp = (tHTItem*)malloc(sizeof(tHTItem));
	if(!newtmp)
	{
		return; //chyba pri mallocu
	}
	newtmp->data = data;
	newtmp->key = key;
	int index = hashCode(key);//zistenie indexu pre kľúč
	//ak existuje synonyma, pripojenie za nový prvok
	if((tmp = (*ptrht)[index]))
	{
		newtmp->ptrnext = tmp;
	}
	//ulpženie prvku na začiatok zoznamu daného kľúča
	(*ptrht)[index] = newtmp;
	
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {
	//nájdenie položky podľa kľúča
	tHTItem *tmp = htSearch(ptrht, key);
	//ak položka neexistuje vracia NULL
	if(tmp == NULL)
		return NULL;
	else return &tmp->data; //inak vráti ukazateľ na dáta
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {
	//zistenie a pristúpenie k položke
	int index = hashCode(key);
	tHTItem *tmp = (*ptrht)[index];
	tHTItem *prevtmp = NULL;
	tHTItem *nexttmp = NULL;
	//cyklus hľadajúci daný kľúč
	for(; tmp; prevtmp = tmp, tmp = tmp->ptrnext)
	{
		nexttmp = tmp->ptrnext; //ukazateľ na ďalšiu položku
		if(tmp->key == key)
		{
			free(tmp); //uvolnenie položky
			//ak je na začiatku zoznamu nastavenie nasledujúcej položky
			if(prevtmp == NULL)
			{
				(*ptrht)[index] = nexttmp;
				return;
			}
			//nieje na začiatku teda nastavenie ďalšieho prvku predchádzajúceho prvku na nasledujúci
			prevtmp->ptrnext = nexttmp;
			return;
		}
	}
}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {
	tHTItem *tmp;
	tHTItem *todelete;
	//cyklus prejde cez celú tabuľku
	for(int i = 0; i <HTSIZE; i++)
	{
		//cyklus prejde cez celý zreťazený zoznam
		tmp = (*ptrht)[i];
		while(tmp != NULL)
		{
			todelete = tmp;
			tmp = tmp->ptrnext;
			free(todelete); //uvolnenie položky
		}
		(*ptrht)[i] = NULL; //nastavenie ukazateľa na NULL
	}
}
