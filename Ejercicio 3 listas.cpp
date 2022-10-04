#include <iostream>

/*Haga un procedimiento que reciba los mismos parámetros del punto 1 pero devuelva
una tercer lista con el contenido de ambas intercalado (es decir un nodo de la lista 1
seguido por un nodo de la lista 2, si una lista se finaliza primero quedan todos los
demás nodos de la otra lista consecutivos).*/

using namespace std;

struct Nodo
{
    float valor;
    Nodo *sgte;
};


void Mostrar_Valores (Nodo* inicio)
{
    if ( !inicio ) cout << "Hay que intercalar las listas primero, selecciona opcion 1";
    else cout << "Los valores insertados son: ";

    while(inicio)
    {
        cout << inicio->valor << " ";
        inicio = inicio->sgte;
    }
    cout << endl << endl;
    return;
}

Nodo* Intercalado_Listas (Nodo* l1, Nodo* l2)
{
    Nodo* l3 = new Nodo();
    Nodo* paux = NULL;

    l3->valor = l1->valor;
    l3->sgte = NULL;
    paux = l3;

    while ( l1->sgte && l2->sgte )
    {
        if(paux->valor == l1->valor)
        {
            paux->sgte = new Nodo();
            paux = paux->sgte;
            paux->valor = l2->valor;
            paux->sgte = NULL;
            l1 = l1->sgte;
        }
        if(paux->valor == l2->valor)
        {
            paux->sgte = new Nodo();
            paux = paux->sgte;
            paux->valor = l1->valor;
            paux->sgte = NULL;
            l2 = l2->sgte;
        }
    }

    while(l2)
    {
        paux->sgte = new Nodo();
        paux = paux->sgte;
        paux->valor = l2->valor;
        paux->sgte = NULL;
        l2 = l2->sgte;
    }

    while(l1)
    {
        paux->sgte = new Nodo();
        paux = paux->sgte;
        paux->valor = l1->valor;
        paux->sgte = NULL;
        l1 = l1->sgte;
    }

    cout << endl << endl;
    return l3;
}


void Insertar_Ordenado (Nodo* &inicio, float nuevo_valor)
{
    Nodo* anterior = NULL;
    Nodo* paux = inicio;
    Nodo* nuevo = NULL;

    while ( paux && paux->valor < nuevo_valor)
    {
        anterior = paux;
        paux = paux->sgte;
    }

    if ( paux != inicio)  //NO SE QUIERE MODIFICAR EL PRIMER NODO
    {
        nuevo = new Nodo();
        nuevo->valor = nuevo_valor;
        nuevo->sgte = paux;
        anterior->sgte = nuevo;
    }
    else    //SE QUIERE MODIFICAR EL PRIMER NODO
    {
        inicio = new Nodo();
        inicio->valor = nuevo_valor;
        inicio->sgte = paux;
    }
    return;
}


void Mostrar_Mayor(Nodo* inicio)
{
    float mayor = 0;

    if ( !inicio )
    {
        cout << "Hay que intercalar las listas primero, selecciona opcion 1";
        return;
    }

    else mayor = inicio->valor;
    while(inicio)
    {
        if(inicio->valor > mayor)
            mayor = inicio->valor;
        inicio = inicio->sgte;
    }
    cout << "El mayor de la lista es: " << mayor << endl << endl;
    return;
}

void Promedio(Nodo* inicio)
{
    float prom = 0, cant = 0;

    if ( !inicio )
    {
        cout << "Hay que intercalar las listas primero, selecciona opcion 1";
        return;
    }
    while(inicio)
    {
        prom += inicio->valor;
        cant++;
        inicio = inicio->sgte;
    }
    cout << "El promedio de la lista es: " << (prom/cant) << endl << endl;
    return;
}

int main()
{
    Nodo *l_1 = NULL;
    Nodo *l_2 = NULL;
    Nodo *l_3 = NULL;
    int cant_1, cant_2, i, valor;
    float v1, v2;

    cout << "Ingrese la cantidad de datos de la lista 1" << endl;
    cin >> cant_1;
    cout << "Ingrese la cantidad de datos de la lista 2" << endl;
    cin >> cant_2;

    cout << "Ingrese valores de la lista 1: " << endl;
    for( i = 0; i < cant_1; i++)
    {
        cout << "Valor " << i+1 << ": ";
        cin >> v1;
        Insertar_Ordenado(l_1, v1);
    }

    cout << endl;
    cout << "Ingrese valores de la lista 2: " << endl;
    for( i = 0; i < cant_2; i++)
    {
        cout << "Valor " << i+1 << ": ";
        cin >> v2;
        Insertar_Ordenado(l_2, v2);
    }
    cout << endl;

    do
    {
        //cout << endl;
        cout << "1 - Intercalar las listas" << endl;
        cout << "2 - Mostrar la lista final" << endl;
        cout << "3 - Mostrar el mayor elemento de la lista final" << endl;
        cout << "4 - Calcular el promedio de la lista final" << endl;
        cout << "0 - Terminar programa" << endl;
        cin >> valor;

        switch (valor)
        {
            case 0:
                exit(1);
                break;
            case 1:
                l_3 = Intercalado_Listas(l_1, l_2);
                break;
            case 2:
                Mostrar_Valores(l_3);
                break;
            case 3:
                Mostrar_Mayor(l_3);
                break;
            case 4:
                Promedio(l_3);
                break;
            default: cout << "Ingresaste una opcion incorrecta" << endl;
                break;
        }
    }while (valor != 0);

    return 0;
}
