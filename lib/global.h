#include <iostream>
#include <windows.h>

using namespace std;
const int DELAY = 30;

#define TAB '\t'
#define ENTER '\n'
#define PI 3.1416
#define G 9.8

#define BELL '\007'
#define ENTER '\n'
#define UPPER 300
// enum MES { ENE = 1, FEB, MAR, ABR, MAY, JUN, JUL, AGO, SEP, OCT, NOV, DIC };

enum MENU
{
    SALIR = 0,
    AGREGAR,
    PRESENTAR,
    GUARDAR_BINARIO,
    BUSCAR_P,
    BUSCAR_PB,
    ELIMINAR,
    CREDITO
};
// enum MENU_DELIVERY {AGREGAR = 0, , GUARDAR, SALIR};

void showProgressBar_u(string nombre, int indexLetra)
{
    string str;
    cout << "\r[";
    for (int barra = 0; barra <= nombre.length(); barra++)
    {
        if (barra < indexLetra)
            str += nombre[barra];
        cout << ((barra <= indexLetra && barra > 0) ? "#" : " ");
        Sleep(DELAY);
    }
    cout << "] "
         << 100 * indexLetra / nombre.length() << "% "
         << "\t\t Loading: " << indexLetra << " de " << nombre.length() << " \t " << str
         << endl;
    // fflush(stdout);
}

string showAvance(string loading, int rellenar)
{
    char caracteres[] = "/-\\"; //"-=-";
    string relleno = "";
    for (size_t i = 0; i < rellenar; i++)
        relleno += " ";
    for (int x = 0; x <= 4; x++)
    {
        cout << loading << caracteres[x % 3] << relleno << "]";
        Sleep(100);
    }
    return "o";
}

void showProgressBar_a(string nombre, int indexLetra)
{
    string str, loading = "\r [";
    for (int barra = 0; barra <= nombre.length(); barra++)
    {
        if (barra < indexLetra)
            str += nombre[barra];
        loading += ((barra <= indexLetra && barra > 0) ? showAvance(loading, nombre.length() - barra) : " ");
        cout << loading;
    }
    cout << "] "
         << 100 * indexLetra / nombre.length() << "% "
         << "\t\t Loading: " << indexLetra << " de " << nombre.length() << " \t " << str
         << endl;
    // fflush(stdout);
}

void showProgressBar_i(string nombre, int indexLetra)
{
    int loops = 0;
    bool avanza = true;
    string str, loading = "---------------------------";
    for (int barra = 0; barra <= nombre.length(); barra++)
    {
        if (barra < indexLetra)
            str += nombre[barra];

        for (int i = 0; loops <= indexLetra;)
        {
            string str = loading;
            cout << "\r [" << str.insert(i, "<-=->") << "]";
            Sleep(10);
            i += (avanza) ? 1 : -1;

            if (i == loading.length() || i == 0)
            {
                avanza = !avanza;
                loops++;
            }
        }
    }
    cout << 100 * indexLetra / nombre.length() << "% "
         << "\t\t Loading: " << indexLetra << " de " << nombre.length() << " \t " << str
         << endl;
    // fflush(stdout);
}

void showProgressBar_x(string nombre, int indexLetra)
{
    string str, loading = "\r";
    for (int barra = 0; barra <= nombre.length(); barra++)
    {
        if (barra < indexLetra)
            str += nombre[barra];
        char caracteres[] = "|/-\\"; //"-=-";
        for (int x = 0; x <= 4; x++)
        {
            cout << loading << caracteres[x % 4] << " ";
            Sleep(20);
        }
        cout << loading;
    }
    cout << 100 * indexLetra / nombre.length() << "% "
         << "\t Loading: " << indexLetra << " de " << nombre.length() << " \t " << str
         << endl;
    // fflush(stdout);
}

// enum boolean
// {
//     NO,
//     YES
// };
// enum months
// {
//     ENE = 1,
//     FEB,
//     MAR,
//     ABR,
//     MAY,
//     JUN,
//     JUL,
//     AGO,
//     SEP,
//     OCT,
//     NOV,
//     DIC
// };

enum Colors
{ // Listado de colores (La letra "L" al inicio, indica que es un color mas claro que su antecesor).
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LGREY = 7,
    DGREY = 8,
    LBLUE = 9,
    LGREEN = 10,
    LCYAN = 11,
    LRED = 12,
    LMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// procedimiento para cambiar el color del fondo y/o pantalla
void setColor(int Background, int Text)
{
    int colorTexto = Text + (Background * 16);         // los colores van del 0 al 255 por eso se multiplica por 16
    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE); // referenciamos a la consola.
    SetConsoleTextAttribute(terminal, colorTexto);
}

char Creditos[310] = "\n\n\tCREDITOS\tGRUPO 6\n\n\tJefferson Chileno \t-\tJefferson.chileno@epn.edu.ec\n\tDavid Quille \t\t-\tDavid.quille@epn.edu.ec\n\tEmilio Quinga \t\t-\temilio.quinga@epn.edu.ec\n\tDario Palma \t\t-\tdario.palma@epn.edu.ec\n\tJhoel Narvaez \t\t-\tRoberto.Narvaez@epn.Edu.ec\n\tBryan Salazar \t\t-\tbryan.salazar02@epn.edu.ec\n\n";