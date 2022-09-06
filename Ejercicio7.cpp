#include <iostream>
#include <string.h>

using namespace std;

#define NOMBRE 12
#define FECHA_NAC 10

struct alumnos
{
    char nombre [NOMBRE];
    char apellido [NOMBRE];
    int legajo;
    int DNI;
    char fecha_nacimiento [FECHA_NAC];
};

void buscar_legajo()
{
    FILE *f;
    alumnos a;
    int leg;
    bool flag = false;

    f = fopen("alumnos.bin", "rb");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    cout << "Ingrese legajo del alumno a buscar: ";
    cin >> leg;
    cout << endl;

    fseek(f, 0 , SEEK_SET);
    while ( fread( &a, sizeof (alumnos), 1 , f ) )
    {
        if ( leg == a.legajo )
        {
            cout << "El alumno es: " << endl;
            cout << "Nombre: " << a.nombre << endl;
            cout << "Apellido: " << a.apellido << endl;
            cout << "Legajo: " << a.legajo << endl;
            cout << "DNI: " << a.DNI << endl;
            cout << "Fecha de nacimiento: " << a.fecha_nacimiento << endl;
            cout << endl;
            flag = true;
        }
    }
    if (!flag)
        cout << "No hay ningun alumno con ese legajo" << endl;
    cout << endl;
    fclose (f);
    return;
}

void buscar_dni()
{
    FILE *f;
    alumnos a;
    int doc;
    bool flag = false;

    f = fopen("alumnos.bin", "rb");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    cout << "Ingrese DNI del alumno a buscar: ";
    cin >> doc;
    cout << endl;

    fseek(f, 0 , SEEK_SET);
    while ( fread( &a, sizeof (alumnos), 1 , f ) )
    {
        if ( doc == a.DNI )
        {
            cout << "El alumno es: " << endl;
            cout << "Nombre: " << a.nombre << endl;
            cout << "Apellido: " << a.apellido << endl;
            cout << "Legajo: " << a.legajo << endl;
            cout << "DNI: " << a.DNI << endl;
            cout << "Fecha de nacimiento: " << a.fecha_nacimiento << endl;
            cout << endl;
            flag = true;
        }
    }
    if (!flag)
        cout << "No hay ningun alumno con ese DNI" << endl;
    cout << endl;
    fclose (f);
    return;
}

int cant_elementos (FILE *f)
{
    int cant;
    long tam;
    fseek (f, 0 , SEEK_END);
    tam = ftell(f);
    cant = tam / sizeof(alumnos);
    return cant;
}

void burbuja (int legajos[], int tam)
{
    int i = 0, j = 0, aux;
    for (i = 0; i < (tam - 1); i++)
    {
        for (j = 0; j < (tam - 1); j++)
        {
            if ( legajos[j+1] < legajos[j] )
            {
                aux = legajos[j];
                legajos[j] = legajos[j+1];
                legajos[j+1] = aux;
            }
        }
    }
    return;
}

void ordenar()
{
    FILE *f;
    alumnos a;
    int cant, i = 0, j = 0,pos, k;
    f = fopen("alumnos.bin", "rb+");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    cant = cant_elementos(f);
    cout << "CANT ES: " << cant << endl;
    int legajos [cant];
    fseek (f, 0 , SEEK_SET);

    while ( fread( &a, sizeof (alumnos), 1 , f ) )
    {
        legajos[i] = a.legajo;
        i++;
    }
    /*cout << "I vale: " << i << endl;
    cout << "Los legajos son: " << endl;
    for (j = 0; j < i ; j++)
        cout << legajos[j] << endl;*/

    burbuja (legajos, cant);

    /*cout << "Los legajos ordenados son: " << endl;
    for (j = 0; j < i ; j++)
        cout << legajos[j]<< endl;*/

    fseek (f, 0 , SEEK_SET);
    for (k = 0; k < (cant - 1) ; k++)
    {
        for (j = 0; j < (cant - 1); j++)
        {
            if ( fread( &a, sizeof (alumnos), 1 , f ) )
                if ( a.legajo == legajos[j] )
            {
                pos = ftell(f) - ( i * sizeof(alumnos) ); //ESTA PARTE ES LA QUE NO ENCUENTRO EL ALGORITMO CORRECTO PARA QUE ESCRIBA ORDENADAMENTE
                fseek(f, pos , SEEK_SET);
                fwrite( &a, sizeof (alumnos), 1 , f );
                i--;
                //cout << "entro"<< endl;
            }

        }
        i = cant - k;
    }
    cout << "Los nombres se ordenaron correctamente por legajo, listelos si desea verlos" << endl;
    return;
}

void modificar() //FUNCIONA BIEN, PERO SI LUEGO DE MODIFICAR SE LISTA HACE BIEN LA MODIFICACION PERO SE AGREGA MIL ALUMNOS MAS
{
    FILE *f;
    alumnos a;
    int leg, pos;
    bool flag = false;

    f = fopen("alumnos.bin", "rb+");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    cout << "Ingrese legajo del alumno a modificar: ";
    cin >> leg;
    cout << endl;

    fseek(f, 0 , SEEK_SET);
    while ( fread( &a, sizeof (alumnos), 1 , f ) )
    {
        if ( leg == a.legajo )
        {
            pos = ftell(f) - sizeof(alumnos);
            fseek(f, pos , SEEK_SET);
            cout << "Ingrese los datos del alumno a modificar: " << endl;
            cout << "Nombre: ";
            cin >> a.nombre;
            cout << "Apellido: ";
            cin >> a.apellido;
            cout << "DNI: ";
            cin >> a.DNI;
            cout << "Fecha de nacimiento: ";
            cin >> a.fecha_nacimiento;
            cout << endl;
            fwrite( &a, sizeof(alumnos), 1 , f );
            flag = true;
        }
    }

    if (!flag)
        cout << "No hay ningun alumno con ese legajo" << endl;
    cout << endl;
    fclose (f);
    return;
}


void agregar_alumnos ()
{
    FILE *f;
    alumnos a;
    f = fopen("alumnos.bin", "ab+");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    cout << endl;
    cout << "Ingrese los datos del alumno: " << endl;
    cout << "Nombre: ";
    cin >> a.nombre;
    cout << "Apellido: ";
    cin >> a.apellido;
    cout << "Legajo: ";
    cin >> a.legajo;
    cout << "DNI: ";
    cin >> a.DNI;
    cout << "Fecha de nacimiento: ";
    cin >> a.fecha_nacimiento;
    cout << endl;
    fwrite( &a, sizeof(alumnos), 1 , f );
    fclose (f);
    return;
}

void listar_alumnos ()
{
    FILE *f;
    alumnos a;

    f = fopen("alumnos.bin", "rb");
    if ( !f )
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    fseek(f, 0 , SEEK_SET);

    cout << endl;
    while ( fread( &a, sizeof (alumnos), 1 , f ) )
    {
        cout << "Nombre: " << a.nombre << endl;
        cout << "Apellido: " << a.apellido << endl;
        cout << "Legajo: " << a.legajo << endl;
        cout << "DNI: " << a.DNI << endl;
        cout << "Fecha de nacimiento: " << a.fecha_nacimiento << endl;
        cout << endl;
    }
    fclose (f);

    return;
}

int main()
{
    int opcion;
    do
    {
        cout << endl;
        cout << "1 - Agregar alumno" << endl;
        cout << "2 - Listar todos los alumnos" << endl;
        cout << "3 - Buscar alumno por legajo" << endl;
        cout << "4 - Buscar alumno por DNI" << endl;
        cout << "5 - Ordenar archivo por legajo" << endl;
        cout << "6 - Modificar alumno por legajo" << endl;
        cout << "7 - Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1: agregar_alumnos();
                break;
            case 2: listar_alumnos();
                break;
            case 3: buscar_legajo();
                break;
            case 4: buscar_dni();
                break;
            case 5: ordenar();
                break;
            case 6: modificar();
                break;
            case 7: exit(1);
                break;
            default: cout << "Ingresaste una opcion erronea" << endl;
                break;
        }

    }while (opcion != 7);

    return 0;
}
