#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#define TAM 10

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10


// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);


/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElementsaux;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElementsaux =(void **) malloc(sizeof(void *)*AL_INITIAL_VALUE );//pido memoria para el puntero a un puntero. memoria multiplicada por una variable definida
        if(pElementsaux != NULL)
        {
            this->size=0;
            this->pElements=pElementsaux;//se le pasa el puntero al campo de la lista de elementos de array list
            this->reservedSize=AL_INITIAL_VALUE;//le asigno el valor inicial del tama�o de la memoria al campo de arraylist
            this->add=al_add;//le asigno la direccion de memoria de la funcion
            this->len=al_len; // '''''''''''''''''''''''''''''''''''''''''''
            this->set=al_set;// '''''''''''''''''''''''''''''''''''''''''''
            this->remove=al_remove;// '''''''''''''''''''''''''''''''''''''''''''
            this->clear=al_clear;// '''''''''''''''''''''''''''''''''''''''''''
            this->clone=al_clone;// '''''''''''''''''''''''''''''''''''''''''''
            this->get=al_get;// '''''''''''''''''''''''''''''''''''''''''''
            this->contains=al_contains;// '''''''''''''''''''''''''''''''''''''''''''
            this->push=al_push;// '''''''''''''''''''''''''''''''''''''''''''
            this->indexOf=al_indexOf;// '''''''''''''''''''''''''''''''''''''''''''
            this->isEmpty=al_isEmpty;// '''''''''''''''''''''''''''''''''''''''''''
            this->pop=al_pop;// '''''''''''''''''''''''''''''''''''''''''''
            this->subList=al_subList;// '''''''''''''''''''''''''''''''''''''''''''
            this->containsAll=al_containsAll;// '''''''''''''''''''''''''''''''''''''''''''
            this->deleteArrayList = al_deleteArrayList;// '''''''''''''''''''''''''''''''''''''''''''
            this->sort = al_sort;
            this->filter = al_filter;
            returnAux = this;
        }
        else
        {
            free(this);// en caso de que no encuentre espacio en memoria para el doble puntero. lo destruyo
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    void** paux;
    int flag=0;

    if(this!=NULL && pElement !=NULL )
    {

        if(this->size==this->reservedSize)
        {
            paux =(void**) realloc(this->pElements, sizeof(void*)*(this->reservedSize + AL_INCREMENT));

            if(paux!=NULL)
            {
                this->pElements = paux;
                this->reservedSize= this->reservedSize + AL_INCREMENT;
            }
            else
            {
                flag=1;
            }
        }

        if(flag==0)
        {
            this->pElements[this->size]= pElement;
            returnAux=0;
            this->size++;
        }
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        al_clear(this);
        free(this);
        returnAux= 0;
    }

    return returnAux;
}

/** \brief  length of arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        returnAux= this->size;
    }

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;

    if(this!= NULL && index>= 0 &&  index < al_len(this))
    {
        returnAux = *(this->pElements+index);
    }

    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;

    if(this != NULL && pElement != NULL)
    {

        for(i=0; i< this->size; i++)
        {

            if(*(this->pElements+i) == pElement)
            {
                returnAux = 1;
                break;
            }
            else
            {
                returnAux = 0;
            }
        }
    }

    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this !=NULL &&  pElement != NULL && index>=0 && index <= al_len(this))
    {

        if(index < al_len(this))
        {
            *(this->pElements+index)= pElement;
        }
        else
        {
            al_add(this,pElement);
        }
        returnAux=0;
    }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!= NULL && index>=0 && index<= al_len(this))
    {

        contract(this,index);
        returnAux=0;
    }

    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    void** aux;
    if(this!=NULL)

    {
        this->size=0;
        aux=(void**)realloc(this->pElements, sizeof(void*)*(AL_INCREMENT));
        if(aux != NULL)
        {
            this->pElements = aux;
            this->reservedSize=AL_INCREMENT;
            returnAux = 0;
        }
    }

    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux = NULL;
    ArrayList* this2;
    int i;

    if(this!= NULL)
    {
        this2=al_newArrayList();

        if(this2!= NULL)
        {

            for(i=0; i < this->size; i++)
            {
                al_add(this2, *(this->pElements+i));
            }
        }
        returnAux=this2;
    }

    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this!= NULL && pElement != NULL && index>=0 && index <= al_len(this))
    {
        al_add(this, pElement);

        if(index != al_len(this))
        {

            expand(this,index);
            al_set(this,index,pElement);
        }
        returnAux=0;
    }

    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;

    if(this!= NULL && pElement != NULL)
    {

        for(i=0; i<this->size; i++)
        {

            if(*(this->pElements+i)== pElement)
            {
                returnAux= i;
                break;
            }
        }
    }

    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {

        returnAux=1;

        if(al_len(this) > 0)
        {
            returnAux=0;
        }
    }

    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;
    void* pAux;

    if(this!=NULL && index>=0 && index< al_len(this))
    {
        pAux= *(this->pElements+index);
        al_remove(this, index);
        returnAux= pAux;
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
    void* returnAux = NULL;
    ArrayList* this2;
    int i;

    if(this != NULL)
    {
        this2=al_newArrayList();

        if(this2!=NULL && from>=0 && to>= 0 && from < to && from <= (this->len(this)) && to <= al_len(this) )
        {

            for(i=from; i < to; i++)
            {
                al_add(this2,*(this->pElements+i));
            }
            returnAux= this2;
        }
    }

    return returnAux ;
}





/** \brief Devuelve true si la lista pList contiene todos los elementos de pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1,i;
    if(this !=  NULL && this2 != NULL)
    {
        for(i=0; i<this->size; i++)
        {
            if(this->len(this) == al_len(this2))
            {
                if(*(this->pElements+i) == *(this2->pElements+i))
                {
                    returnAux = 1;
                }
                else
                {
                    returnAux = 0;
                }
            }
            else
            {
                returnAux = 0;
            }
        }
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux = -1;
    void* pAux;
    int aux;
    int i;
    int j;

    if(this!= NULL && *(pFunc)!= NULL)
    {

        if(order==1)
        {
            returnAux= 0;

            for(i=0; i < (this->size-1); i++)
            {

                for(j=i+1; j < this->size ; j++)
                {

                    aux=pFunc(*(this->pElements+i),*(this->pElements+j));

                    if(aux==1)
                    {
                        pAux = *(this->pElements+j);
                        *(this->pElements+j) = *(this->pElements+i);
                        *(this->pElements+i) = pAux;
                    }
                }
            }
        }
        else if(order==0)
        {
            returnAux= 0;

            for(i=0; i < (this->size-1); i++)
            {

                for(j=i+1; j < this->size ; j++)
                {

                    aux=pFunc(*(this->pElements+i),*(this->pElements+j));

                    if (aux==-1)
                    {
                        pAux = *(this->pElements+j);
                        *(this->pElements+j) = *(this->pElements+i);
                        *(this->pElements+i) = pAux;
                    }
                }
            }
        }
        else
        {
            returnAux=-1;
        }
    }

    return returnAux;
}

/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    void** pAux;

    if(this!= NULL)
    {
        pAux= (void**) realloc(this,sizeof(void*)*(this->reservedSize+AL_INCREMENT));

        if(pAux!=NULL)
        {
            this->pElements = pAux;
            this->reservedSize = (this->reservedSize + AL_INCREMENT);
            returnAux=0;
        }
    }

    return returnAux;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;
    int flag;
    int i;

    if(this!= NULL && index>= 0 && index <= al_len(this))
    {

        if(index < al_len(this))
        {

            for(i=this->size-1; i>=index; i--)
            {
                *(this->pElements+i) = *(this->pElements+i);
            }
        }
        returnAux=0;
    }
    else
    {
        flag=resizeUp(this);

        if(flag==0)
        {
            returnAux=0;
        }
    }

    return returnAux;
}



/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    int j;

    if(this!= NULL && index>= 0 && index < al_len(this))
    {

        for(j=index+1; j< this->size; j++)
        {
            *(this->pElements+(j-1)) = *(this->pElements+j);
        }
        this->size--;
        returnAux=0;
    }

    return returnAux;
}


ArrayList* al_filter(ArrayList* listIn, int (*functionFilter)(void*))
{
    ArrayList* nuevoArray = NULL;

    void* item;
    int i;
    int aux;
    int index;

    if(listIn != NULL && (functionFilter)!= NULL)
    {
        nuevoArray =al_newArrayList();
        aux = al_len(listIn);
        for(i=0; i< aux; i++)
        {
            item=al_get(listIn,i);
            index = functionFilter(item);
            if(index==1)
            {
                nuevoArray->add(nuevoArray, item);
            }

        }

    }


    return nuevoArray;
}
