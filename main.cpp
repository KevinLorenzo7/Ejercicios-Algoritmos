#include <iostream>

using namespace std;

void carga_archivos (FILE* m, int n)
{
    int numeros;

    for (int i = 0; i < n ; i++ )
    {
        cout << "Numero " << i+1 << ": ";
        cin >> numeros;
        fwrite( &numeros, sizeof (int), 1 , m );
    }

    return;
}

void muestra (FILE* m)
{
    int num, i = 0;
    fseek(m, 0, SEEK_SET);
    while(fread(&num, sizeof(int), 1, m))
    {
        cout << "Numero " << i+1 << ": " << num << endl;
        i++;
    }
    cout << endl;
    return;
}

void ordenamiento_asc (FILE* f1, FILE* f2, FILE* f3, int tot1, int tot2) //La funcion anda joya pero si pongo 2 valores iguales
//en ambos FILES se muestran 2 veces, como podria sacar eso
{
    int num1, num2, i = 0, j = 0, k = 0;

    fseek(f1, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);

    while ( i < tot1 && j < tot2 )
    {
        fread(&num1, sizeof(int), 1, f1);
        fread(&num2, sizeof(int), 1, f2);

        if ( num1 < num2 )
        {
            fseek(f2, (-1)* sizeof (int) , SEEK_CUR);
            fwrite(&num1, sizeof(int), 1, f3);
            i++;
        }
        else
        {
            fseek(f1, (-1)* sizeof (int) , SEEK_CUR);
            fwrite(&num2, sizeof(int), 1, f3);
            j++;
        }
    }
    for (k = i; k < tot1; k++)
    {
        fread(&num1, sizeof(int), 1, f1);
        fwrite(&num1, sizeof(int), 1, f3);
    }
    for (k = j; k < tot2; k++)
    {
        fread(&num2, sizeof(int), 1, f2);
        fwrite(&num2, sizeof(int), 1, f3);
    }
    return;
}

int main()
{
    FILE* f1;
    FILE* f2;
    FILE* f3;
    int a, b;

    cout << "Ingrese la cantidad de numeros ordenados a ingresar en el archivo 1" << endl;
    cin >> a;

    f1 = fopen("numeros_1.bin", "wb+");
    if ( !f1 )
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    carga_archivos (f1, a);
    //muestra(f1);

    cout << "Ingrese la cantidad de numeros ordenados a ingresar en el archivo 2" << endl;
    cin >> b;

    f2 = fopen("numeros_2.bin", "wb+");
    if ( !f2 )
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 2;
    }
    carga_archivos (f2, b);
    //muestra(f2);

    cout << "Los numeros ordenados ascendentemente en un 3er archivo son:" << endl;
    f3 = fopen("numeros_3.bin", "wb+");
    if ( !f3 )
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 3;
    }
    ordenamiento_asc (f1, f2, f3, a,b);

    fclose(f1);
    fclose(f2);
    muestra(f3);
    fclose(f3);

    return 0;
}
