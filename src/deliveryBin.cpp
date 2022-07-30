#include <iostream> // entradas salidas en consola y string cout cin ...
#include <fstream>  // manejo de archivos
#include <vector>   // gestiona las listas / arreglos / buffers
#include <string>
//#include <cstring>
#include <sstream>
#include "../lib/global.h"
#include <bits/stdc++.h>
#include <dirent.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

using namespace std;
const string whiteSpaces(" \f\n\r\t\v");
struct provincia
{
    int ID;
    char sNombre[50];
    int iPoblacion;
    float fTemperatura;
    char lstPlatoTipico[100];
};
vector<provincia> lstProvincia;
const string pathfilebinary = "resorce/database/delivery.dat";

bool leerArchivoBinario();
void escribirArchivoBinario();
void presentarProvincias();
void presentarProvincia();
void presentarProvincia(provincia p);
int provinciaRepetida(char provincia[50]);
void agregarProvincia();
void eliminarProvincia();
void buscarProvincia();
void buscarProvinciaBinario();

void trimRight(string &str);
void trimLeft(string &str);
void trim(string &str);

int menu();

string tolowerStr(string str);
void segmentarCadena(const string str, const char delim, vector<string> &lst);

int main()
{
    leerArchivoBinario();
    do
    {
        system("cls");
        switch (menu())
        {
        case AGREGAR:
            agregarProvincia();
            break;
        case PRESENTAR:
            presentarProvincias();
            break;
        case GUARDAR_BINARIO:
            escribirArchivoBinario();
            break;
        case BUSCAR_P:
            buscarProvincia();
            break;
        case BUSCAR_PB:
            buscarProvinciaBinario();
            break;
        case ELIMINAR:
            eliminarProvincia();
            break;
        case CREDITO:
            setColor(0, 9);
            for (auto &&i : Creditos)
            {
                cout << i;
                usleep(7000);
            }
            system("PAUSE");
            break;
        case SALIR:
            cout << "bye bye ...";
            exit(0);
        default:
            setColor(0, 4);
            cout << "Seleccion no valida \n";
            setColor(0, 15);
            getch();
            break;
        }
    } while (true);
    return 1;
}

bool leerArchivoBinario()
{
    ifstream rf(pathfilebinary, ios::in | ios::binary);
    cout << "Abrir archivo:" << pathfilebinary << endl;
    if (!rf)
    {
        cout << " << error >>" << endl;
        return false;
    }
    provincia tp[1];
    while (rf.read((char *)&tp[0], sizeof(provincia)))
        lstProvincia.push_back(tp[0]);
    rf.close();
    return true;
}
void escribirArchivoBinario()
{
    ofstream f(pathfilebinary, ios::out | ios_base::binary);
    if (f.good())
    {
        setColor(0, 2);
        cout << endl
             << " GUARDADO EXITOSO: " << pathfilebinary << endl;
        for (auto &&prov : lstProvincia) // { [*],[*],[*]...}
            f.write((char *)&prov, sizeof(provincia));
        // f.write((char*)&lstProvincia[0], lstProvincia.size() * sizeof(provincia));
    }
    f.close();
    setColor(0, 8);
    system("PAUSE");
}

void agregarProvincia()
{
    string str = "s";
    string datos;
    char datosNumericos[5];
    int contadorDeProvincias = 0;
    bool dataVacio = false;

    do
    {
        struct provincia prov;
        for (auto &&prov : lstProvincia)
            contadorDeProvincias++;
        prov.ID = contadorDeProvincias;
        setColor(0, 2);
        cout << endl
             << "----- Ingresar datos de provincia -----" << endl;

        do
        {
        volverNombre:
            for (int i = 0; i < 50; i++)
                prov.sNombre[i] = '\0'; // Reiniciar cada vez que pregunte
            setColor(0, 14);
            cout << "<+> Nombre: ";
            setColor(0, 13);
            fflush(stdin);
            getline(cin, datos);
            trim(datos);
            for (int i = 0; i < datos.length(); i++)
                prov.sNombre[i] += datos[i];
            fflush(stdin);

            dataVacio = false;
            for (int i = 0; i < 50; i++)
                if (prov.sNombre[i] == '\n' || prov.sNombre[i] == '\0' || prov.sNombre[i] == '\t' || prov.sNombre[i] == ' ')
                    dataVacio = true;
                else
                {
                    dataVacio = false;
                    break;
                }

            setColor(0, 4);
            if (dataVacio == true)
            {
                cout << "WARNING! NO es posible dejar espacios en blanco\n";
                goto volverNombre;
            }
        } while (provinciaRepetida(prov.sNombre) == 0);

        do
        {
            setColor(0, 14);
            cout << "<+> Poblacion: ";
            setColor(0, 13);
            cin >> datosNumericos;
            prov.iPoblacion = atoi(datosNumericos);

            setColor(0, 4);
            if (prov.iPoblacion == 0)
                cout << "WARNING! Dato no valido.\n";
            fflush(stdin);
        } while (prov.iPoblacion == 0);
        fflush(stdin);

        do
        {
            setColor(0, 1);
            cout << "<+> Temperatura: ";
            setColor(0, 13);
            cin >> datosNumericos;
            prov.fTemperatura = atof(datosNumericos);
            setColor(0, 4);
            if (prov.fTemperatura == 0)
                cout << "WARNING! Dato no valido.\n";
            fflush(stdin);
        } while (prov.fTemperatura == 0);
        fflush(stdin);

    volverPlatosTipicos:
        for (int i = 0; i < 100; i++)
            prov.lstPlatoTipico[i] = '\0'; // Reiniciar cada vez que pregunte
        setColor(0, 12);
        cout << "<+> PlatoTipico (separados por coma): ";
        setColor(0, 13);
        fflush(stdin);
        getline(cin, datos);
        trim(datos);
        for (int i = 0; i < datos.length(); i++)
            prov.lstPlatoTipico[i] += datos[i];

        // fflush(stdin);

        dataVacio = false;
        for (int i = 0; i < 100; i++)
            if (prov.lstPlatoTipico[i] == '\n' || prov.lstPlatoTipico[i] == '\0' || prov.lstPlatoTipico[i] == '\t' || prov.lstPlatoTipico[i] == ' ')
                dataVacio = true;
            else
            {
                dataVacio = false;
                break;
            }

        setColor(0, 4);
        if (dataVacio == true)
        {
            cout << "WARNING! NO es posible dejar espacios en blanco\n";
            goto volverPlatosTipicos;
        }
        lstProvincia.push_back(prov);

        setColor(0, 2);
        cout << "Deseas salir (s): ";
        setColor(0, 13);
        cin >> str;
        fflush(stdin);
        // cin.ignore();
    } while (str != "s");
}

void eliminarProvincia()
{
    string provinciaConsola;
    bool provinciaEliminada = false;
    int posicion = 0;
    int ID = 0;
    setColor(0, 2);
    cout << "\n<-> Nombre: ";
    setColor(0, 13);
    getline(cin, provinciaConsola);
    trim(provinciaConsola);
    for (auto &&prov : lstProvincia)
    {
        string data(prov.sNombre); // convertimos CHAR TO STRING
        if (tolowerStr(prov.sNombre) == tolowerStr(provinciaConsola))
        {
            lstProvincia.erase(lstProvincia.begin() + posicion);
            provinciaEliminada = true;
            break;
        }
        posicion++;
    }

    setColor(0, 12);
    if (provinciaEliminada)
        cout << "Los datos de '" << provinciaConsola << "' han sido eliminados correctamente" << endl;
    else
        cout << "La provincia '" << provinciaConsola << "' no existe" << endl;

    for (auto &&prov : lstProvincia)
        prov.ID = ID++; // Reasignacion de ID

    // VERIFICAR QUE SI SE ELIMINO
    cout << "\n\nLista de provincias: " << endl
         << endl;
    for (auto &&pro : lstProvincia)
        cout << pro.sNombre << endl;
    cout << endl;
    setColor(0, 8);
    system("PAUSE");
}

int provinciaRepetida(char provincia[50])
{
    string dataUser(provincia);
    for (auto &&pro : lstProvincia)
    {
        string data(pro.sNombre); // convertimos CHAR TO STRING
        if (tolowerStr(data) == tolowerStr(dataUser))
        {
            setColor(0, 12);
            cout << "WARNING! Provincia '" << provincia << "' ya se encuentra registrada" << endl;
            setColor(0, 15);
            return 0;
        }
    }
    return -1;
}

void presentarProvincia(provincia p)
{
    setColor(0, 14);
    cout << "ID: ";
    setColor(0, 7);
    cout << p.ID << endl;
    setColor(0, 14);
    cout << "Nombre: ";
    setColor(0, 7);
    cout << p.sNombre << endl;
    setColor(0, 9);
    cout << "Poblacion: ";
    setColor(0, 7);
    cout << p.iPoblacion << endl;
    setColor(0, 9);
    cout << "Temperatura: ";
    setColor(0, 7);
    cout << p.fTemperatura << " C" << endl;
    // cout << fixed << setprecision(0) << p.fTemperatura << "\0176C" << endl;
    setColor(0, 12);
    cout << "Platos-Tipicos: ";
    setColor(0, 7);
    cout << p.lstPlatoTipico << endl;

    setColor(0, 7);
    vector<string> lstPlatoTipico;
    segmentarCadena(p.lstPlatoTipico, ',', lstPlatoTipico);
    for (const auto &pt : lstPlatoTipico)
        cout << "\t" << pt << endl;
    cout << endl;
    setColor(0, 15);
}
void presentarProvincias()
{
    setColor(0, 2);
    cout << endl
         << "--------  Provincias  --------" << endl;
    for (auto &&prov : lstProvincia)
        presentarProvincia(prov);
    setColor(0, 8);
    system("PAUSE");
}
void buscarProvincia()
{
    int coincidencias = 0;
    bool encontrado = false;
    string sProv;
    int porcentajeCoincidencia = 0;

    setColor(0, 2);
    cout << "\nIngrese la provincia que desea buscar: ";
    setColor(0, 13);
    getline(cin, sProv);
    trim(sProv);

    for (auto &&prov : lstProvincia) // RECORRE PROVINCIA
    {
        string data(prov.sNombre);               // convertimos CHAR TO STRING
        for (int i = 0; i < sProv.length(); i++) // ->LETRA
        {
            if (tolowerStr(data)[i] == tolowerStr(sProv)[i]) // LETRAS SON IGUALES?
                coincidencias++;
            porcentajeCoincidencia = (coincidencias * 100) / sProv.length();
        }
        if (porcentajeCoincidencia > 70)
        {
            presentarProvincia(prov);
            encontrado = true;
        }

        coincidencias = 0;
    }
    setColor(0, 12);
    if (!encontrado)
        cout << "WARNING! '" << sProv << "' No se encuentra registrado en la base de datos." << endl;
    setColor(0, 8);
    system("PAUSE");
}
void buscarProvinciaBinario()
{
    string provinciaRequerida;
    bool encontrado = false;
    int posicionProvinciaRequerida = 0;

    setColor(0, 2);
    cout << endl
         << "Ingrese nombre de provincia: ";
    setColor(0, 13);
    getline(cin, provinciaRequerida);
    trim(provinciaRequerida);

    for (auto &&prov : lstProvincia) // RECORRE PROVINCIA
    {
        string data(prov.sNombre);                                                     // convertimos CHAR TO STRING
        if (tolowerStr(provinciaRequerida) == tolowerStr(data) && encontrado == false) // LETRAS SON IGUALES?
        {
            encontrado = true;
            break;
        }
        posicionProvinciaRequerida++;
    }

    ifstream rf(pathfilebinary, ios::in | ios::binary);
    if (!rf)
    {
        cout << " << Error al leer Binario >>" << endl;
        setColor(0, 8);
        system("PAUSE");
        exit(0);
    }

    if (encontrado)
    {
        rf.seekg(posicionProvinciaRequerida * sizeof(provincia));
        provincia p;
        rf.read(reinterpret_cast<char *>(&p), sizeof(provincia));
        presentarProvincia(p);
        rf.close();
    }
    else
        cout << "WARNING! '" << provinciaRequerida << "' No se encuentra registrado en la base de datos." << endl;
    posicionProvinciaRequerida = 0; // Reiniciar el valor de busqueda
    setColor(0, 8);
    system("PAUSE");
}

int menu()
{
    int eleccion;
    do
    {
        fflush(stdin);
        setColor(0, 6);
        cout << endl;
        cout << "(+)----- ";
        setColor(0, 14);
        cout << "Provincias";
        setColor(0, 9);
        cout << " del ";
        setColor(0, 4);
        cout << "Ecuador";
        setColor(0, 6);
        cout << " -----(+)\n";
        setColor(0, 2);
        cout << endl
             << "Ingresa una opcion: \n"
             << endl;
        setColor(0, 3);
        cout << AGREGAR << " | Agregar provincias           |" << endl
             << PRESENTAR << " | listado de provincias        |" << endl
             << GUARDAR_BINARIO << " | Guardar provincias           |" << endl
             << BUSCAR_P << " | Buscar Provincias Avanzadas  |" << endl
             << BUSCAR_PB << " | Buscar Provincias Binario    |" << endl
             << ELIMINAR << " | Eliminar provincias          |" << endl
             << CREDITO << " | Creditos                     |" << endl
             << SALIR << " | Salir del sistema            |" << endl;

        setColor(0, 2);
        cout << "\nSu seleccion: ";
        setColor(0, 13);
        fflush(stdin);
        cin >> eleccion;
        fflush(stdin);
    } while (eleccion < 0);
    return eleccion;
}
string tolowerStr(string str)
{
    for (int x = 0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}

void segmentarCadena(const string str, const char delim, vector<string> &outlst)
{
    string strDiv;
    stringstream s(str);
    while (getline(s, strDiv, delim))
        outlst.push_back(strDiv);
}

void trimRight(string &str)
{
    string::size_type pos = str.find_last_not_of(whiteSpaces);
    str.erase(pos + 1);
}

void trimLeft(string &str)
{
    string::size_type pos = str.find_first_not_of(whiteSpaces);
    str.erase(0, pos);
}

void trim(string &str)
{
    trimRight(str);
    trimLeft(str);
}
/*

TAREA: deliberyBin
- 0.5 por item resuelto
- Equipos de 5 o 6 personas

 | Agregar provincias      |   << arreglar, evitar repetidos, Agregar a la estructura unsigned int Id (autoincremental)
 | Presentar provincias    |   << listar todas las provincias
 | Buscar provincia        |   << pedir nombre de provincia ... buscar y presentar : LOja
 | Buscar Avanzada         |   << pedir nombre de provincia ... buscar y presentar las que coindidan : loxa, --> loja
 | Guardar provincias      |
 | Eliminar provincias     |
0| Salir del sistema      |

>> captuas de pantalla del trabajo colaborativo
<< investigar como recupera directamente del archivo la estructura de datos >>
>> agregar color 0,1



Lista:

Chileno: Evitar repetidos-Todo
david y Chileno: Eliminar :)

comparar caracter por caracter, con un contador, regla 3 40%

*/
