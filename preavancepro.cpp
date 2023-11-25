
#pragma warning( disable :148, 4996).
#include "framework.h"
#include "preavancepro.h"
#include <CommCtrl.h>
#include <commdlg.h>
#include <string>
#include <wctype.h>
#include<locale.h>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <oleauto.h>
#include <sstream>
#include <codecvt>
#include <fstream>

#define MAX_LOADSTRING 100
using namespace std;
struct Doctor {
    WCHAR nombreDoc[255];
    WCHAR CEDULA[9];
    WCHAR DIRFOT[255];
    WCHAR CLVUSU[100];
    WCHAR CONTRA[100];

};
struct NODOLA
{
    Doctor* dato;
    NODOLA* siguiente;
    NODOLA* anterior;
};
struct listaA {
    NODOLA* origen;
    NODOLA* fin;
} LISTADOCTORES;
struct cita
{
    WCHAR fecha[11];
    WCHAR hora[11];
    WCHAR tel[12];
    WCHAR especie[100];
    WCHAR pac[100];
    WCHAR motivo[100];
    double cost;
    WCHAR status[30];
    WCHAR cliente[100];
    WCHAR Doctor[255];
};
struct nodoB
{
    cita* dato;
    nodoB* siguiente;
    nodoB* anterior;
};
struct citas
{
    nodoB* origen;
    nodoB* fin;
} listadocitas;
int x=0;
WCHAR docAct[255];
WCHAR ClVACT[100];
WCHAR CONACT[100];
WCHAR DIRACT[255];
bool menu(int opcion, HWND ventana);
bool esSoloLetras(WCHAR* str) {
    setlocale(LC_ALL, "");  // Establece la localización al valor predeterminado del sistema
    for (int i = 0; str[i] != L'\0'; i++) {
        if (!iswalpha(str[i]) && str[i] != L' ') {
            return false;
        }
    }
    return true;
}
bool esSoloNumeros(WCHAR* str) {
    setlocale(LC_ALL, "");  // Establece la localización al valor predeterminado del sistema
    for (int i = 0; str[i] != L'\0'; i++) {
        if (!iswdigit(str[i])) {
            return false;
        }
    }
    return true;
}
void agregarDoctor(WCHAR* nombreDoc, WCHAR* CEDULA,WCHAR* DIRFOT, WCHAR* CLVUSU, WCHAR* CONTRA) {
   
    if (!esSoloLetras(nombreDoc)) {
        //cout << "Los campos nombre, APpt y APmt deben contener solo letras." << endl;
        MessageBox(NULL, L"No tiene puras letras el nombre", L"Error", MB_OK | MB_ICONERROR);
        x = 1;
        return;
    }
    else
    {
        x = 0;
    }
    Doctor* nuevoDoctor = new Doctor;
    wcscpy_s(nuevoDoctor->nombreDoc, nombreDoc);
    wcscpy_s(nuevoDoctor->CEDULA, CEDULA);
    wcscpy_s(nuevoDoctor->DIRFOT, DIRFOT);
    wcscpy_s(nuevoDoctor->CLVUSU, CLVUSU);
    wcscpy_s(nuevoDoctor->CONTRA, CONTRA);
    NODOLA* nuevoNodo = new NODOLA;
    nuevoNodo->dato = nuevoDoctor;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = LISTADOCTORES.fin;

    if (LISTADOCTORES.fin != NULL) {
        LISTADOCTORES.fin->siguiente = nuevoNodo;
    }

    LISTADOCTORES.fin = nuevoNodo;

    if (LISTADOCTORES.origen == NULL) {
        LISTADOCTORES.origen = nuevoNodo;
    }
    MessageBox(NULL, L"ingresado con exito", L"Excelente", MB_OK | MB_ICONERROR);
}
Doctor* buscarDoctorW(const WCHAR* CLVUSU, const WCHAR* CONTRA) {
    NODOLA* nodoActual = LISTADOCTORES.origen;
    while (nodoActual != NULL) {
        if (wcscmp(nodoActual->dato->CLVUSU, CLVUSU) == 0 && wcscmp(nodoActual->dato->CONTRA, CONTRA) == 0) {
            return nodoActual->dato;
        }
        nodoActual = nodoActual->siguiente;
    }

    return NULL;
}
Doctor* buscarDoctorx(WCHAR* CLVACT, WCHAR* CONACT) {
    NODOLA* nodoActual = LISTADOCTORES.origen;
    while (nodoActual != NULL) {
        if (wcscmp(nodoActual->dato->CLVUSU, CLVACT) == 0 && wcscmp(nodoActual->dato->CONTRA, CONACT) == 0) {
            
            
            return nodoActual->dato;
        }
        nodoActual = nodoActual->siguiente;
    }

    return NULL;
}
void modificarDoctor(WCHAR* nombreDoc, WCHAR* CEDULA, WCHAR* DIRFOT, WCHAR* CLVUSU, WCHAR* CONTRA, WCHAR* CLVACT, WCHAR* CONACT) {
    Doctor* doctor = buscarDoctorx(CLVACT, CONACT);

    if (doctor != NULL) {
        wcsncpy_s(doctor->nombreDoc, sizeof(doctor->nombreDoc) / sizeof(wchar_t), nombreDoc, _TRUNCATE);
        wcsncpy_s(doctor->CEDULA, sizeof(doctor->CEDULA) / sizeof(wchar_t), CEDULA, _TRUNCATE);
        wcsncpy_s(doctor->DIRFOT, sizeof(doctor->DIRFOT) / sizeof(wchar_t), DIRFOT, _TRUNCATE);
        wcsncpy_s(doctor->CLVUSU, sizeof(doctor->CLVUSU) / sizeof(wchar_t), CLVUSU, _TRUNCATE);
        wcsncpy_s(doctor->CONTRA, sizeof(doctor->CONTRA) / sizeof(wchar_t), CONTRA, _TRUNCATE);
        wcsncpy_s(docAct, sizeof(docAct) / sizeof(wchar_t), doctor->nombreDoc, _TRUNCATE);
        wcsncpy_s(ClVACT, sizeof(ClVACT) / sizeof(wchar_t), doctor->CLVUSU, _TRUNCATE);
        wcsncpy_s(DIRACT, sizeof(DIRACT) / sizeof(wchar_t), doctor->DIRFOT, _TRUNCATE);
        #pragma warning( suppress :4996).
        wcscpy(CONACT, doctor->CONTRA);
    }
    else {
        MessageBox(NULL, L"Error", L"Error", MB_OK | MB_ICONERROR);
    }
}
Doctor* buscarDoctor2(const WCHAR* nombreDoc) {
    NODOLA* nodoActual = LISTADOCTORES.origen;
    while (nodoActual != NULL) {
        if (wcscmp(nodoActual->dato->nombreDoc, nombreDoc) == 0) {
            return nodoActual->dato;
        }
        nodoActual = nodoActual->siguiente;
    }

    return NULL;
}
// apartado de citas
void ordenarCitas() {
    // Verificar si la lista está vacía
    if (listadocitas.origen == NULL) {
        
        return;
    }

    // Ordenar la lista utilizando el algoritmo de burbuja
    bool intercambio;
    do {
        intercambio = false;
        nodoB* actual = listadocitas.origen;
        while (actual->siguiente != NULL) {
            // Convertir las fechas y horas WCHAR a time_t
            std::tm fechaActualTm = { 0 };
            std::wistringstream ssFechaActual(actual->dato->fecha);
            ssFechaActual.imbue(std::locale("es_ES.utf8"));
            ssFechaActual >> std::get_time(&fechaActualTm, L"%d-%m-%Y");

            std::tm fechaSiguienteTm = { 0 };
            std::wistringstream ssFechaSiguiente(actual->siguiente->dato->fecha);
            ssFechaSiguiente.imbue(std::locale("es_ES.utf8"));
            ssFechaSiguiente >> std::get_time(&fechaSiguienteTm, L"%d-%m-%Y");

            std::tm horaActualTm = { 0 };
            std::wistringstream ssHoraActual(actual->dato->hora);
            ssHoraActual.imbue(std::locale("es_ES.utf8"));
            ssHoraActual >> std::get_time(&horaActualTm, L"%H:%M");

            std::tm horaSiguienteTm = { 0 };
            std::wistringstream ssHoraSiguiente(actual->siguiente->dato->hora);
            ssHoraSiguiente.imbue(std::locale("es_ES.utf8"));
            ssHoraSiguiente >> std::get_time(&horaSiguienteTm, L"%H:%M");

            time_t fechaActual = mktime(&fechaActualTm);
            time_t fechaSiguiente = mktime(&fechaSiguienteTm);
            time_t horaActual = mktime(&horaActualTm);
            time_t horaSiguiente = mktime(&horaSiguienteTm);

            // Comparar las fechas y horas
            if (fechaActual > fechaSiguiente || (fechaActual == fechaSiguiente && horaActual > horaSiguiente)) {
                // Intercambiar las citas
                cita* temp = actual->dato;
                actual->dato = actual->siguiente->dato;
                actual->siguiente->dato = temp;

                // Asegurarse de que los punteros anterior y siguiente estén correctamente configurados
                if (actual->anterior != NULL) {
                    actual->anterior->siguiente = actual->siguiente;
                }
                if (actual->siguiente->siguiente != NULL) {
                    actual->siguiente->siguiente->anterior = actual;
                }
                nodoB* tempNodo = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                tempNodo->siguiente = actual;
                tempNodo->anterior = actual->anterior;
                actual->anterior = tempNodo;

                intercambio = true;
            }
            else {
                actual = actual->siguiente;
            }
        }
    } while (intercambio);
}
bool esCitaValida(const WCHAR* fechaCita, const WCHAR* horaCita) {
    // Convertir la fecha de la cita a un objeto tm
    std::tm fechaCitaTm = { 0 };
    std::wistringstream ssFecha(fechaCita);
    ssFecha.imbue(std::locale("es_ES.utf8"));
    ssFecha >> std::get_time(&fechaCitaTm, L"%d-%m-%Y");

    // Convertir la hora de la cita a un objeto tm
    std::tm horaCitaTm = { 0 };
    std::wistringstream ssHora(horaCita);
    ssHora.imbue(std::locale("es_ES.utf8"));
    ssHora >> std::get_time(&horaCitaTm, L"%H:%M");

    // Obtener la fecha y hora actuales
    std::time_t t = std::time(NULL);
    std::tm tiempoActual;
    localtime_s(&tiempoActual, &t);

    // Verificar si la fecha de la cita es anterior a la fecha actual
    if (difftime(mktime(&fechaCitaTm), mktime(&tiempoActual)) < 0) {
        return false;
    }

    // Si la fecha de la cita es hoy, verificar si la cita está a menos de media hora de llevarse a cabo
    if (fechaCitaTm.tm_mday == tiempoActual.tm_mday && fechaCitaTm.tm_mon == tiempoActual.tm_mon && fechaCitaTm.tm_year == tiempoActual.tm_year) {
        int diffMinutos = (horaCitaTm.tm_hour - tiempoActual.tm_hour) * 60 + (horaCitaTm.tm_min - tiempoActual.tm_min);
        if (diffMinutos < 2) {
            return false;
        }
    }

    return true;
}
cita* buscarCita(const WCHAR* fechaCita, const WCHAR* horaCita, const WCHAR* cliente, const WCHAR* pac, const WCHAR* doctor) {
    nodoB* nodoActual = listadocitas.origen;
    while (nodoActual != NULL) {
        cita* citaActual = nodoActual->dato;
        if (wcscmp(citaActual->fecha, fechaCita) == 0 && wcscmp(citaActual->hora, horaCita) == 0 && wcscmp(citaActual->cliente, cliente) == 0 && wcscmp(citaActual->pac, pac) == 0 && wcscmp(citaActual->Doctor, doctor) == 0) {
            if (esCitaValida(fechaCita, horaCita)) {
                return citaActual;
            }
            else {
                return NULL;
            }
        }
        nodoActual = nodoActual->siguiente;
    }

    return NULL;
}
void crearCita(WCHAR* fecha, WCHAR* hora, WCHAR* tel, WCHAR* especie, WCHAR* pac, WCHAR* motivo, double cost, WCHAR* status, WCHAR* cliente, WCHAR* Doctor) {
    // Validar los campos del doctor
    if (!esSoloLetras(pac) || !esSoloLetras(cliente) || !esSoloLetras(Doctor)) {
        // mandar un mensaje de error cout << "Los campos de paciente, cliente y doctor deben contener solo letras." << endl;
        return;
    }
    // Validar la fecha de la cita
    if (!esCitaValida(fecha,hora)) {
        // mandar un message box cout << "La fecha de la cita no puede ser anterior a la fecha actual." << endl;
        return;
    }
    // Crear una nueva cita
    cita* nuevaCita = new cita;

    wcscpy_s(nuevaCita->fecha, fecha);
    wcscpy_s(nuevaCita->hora, hora);
    wcscpy_s(nuevaCita->tel, tel);
    wcscpy_s(nuevaCita->especie, especie);
    wcscpy_s(nuevaCita->pac, pac);
    wcscpy_s(nuevaCita->motivo, motivo);
    nuevaCita->cost = cost;
    wcscpy_s(nuevaCita->status, status);
    wcscpy_s(nuevaCita->cliente, cliente);
    wcscpy_s(nuevaCita->Doctor, Doctor);


    // Crear un nuevo nodo
    nodoB* nuevoNodo = new nodoB;
    nuevoNodo->dato = nuevaCita;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = listadocitas.fin;

    // Agregar el nuevo nodo a la lista
    if (listadocitas.fin != NULL) {
        listadocitas.fin->siguiente = nuevoNodo;
    }
    listadocitas.fin = nuevoNodo;

    if (listadocitas.origen == NULL) {
        listadocitas.origen = nuevoNodo;
    }
}
void modificarCita(const WCHAR* fechaCita, const WCHAR* horaCita, const WCHAR* cliente, const WCHAR* pac, WCHAR* nuevaFecha, WCHAR* nuevaHora, WCHAR* nuevoTel, WCHAR* nuevaEspecie, WCHAR* nuevoPac, WCHAR* nuevoMotivo, double nuevoCost, WCHAR* nuevoStatus, WCHAR* nuevoCliente, WCHAR* nuevoDoctor) {
    // Buscar la cita existente
    cita* citaExistente = buscarCita(fechaCita, horaCita, cliente, pac, docAct);
    if (citaExistente == NULL) {
        // La cita no existe
        return;
    }

    // Validar los campos del doctor
    if (!esSoloLetras(nuevoPac) || !esSoloLetras(nuevoCliente) || !esSoloLetras(nuevoDoctor)) {
        // mandar un mensaje de error cout << "Los campos de paciente, cliente y doctor deben contener solo letras." << endl;
        return;
    }
    // Validar la fecha de la cita
    if (!esCitaValida(nuevaFecha, nuevaHora)) {
        // mandar un message box cout << "La fecha de la cita no puede ser anterior a la fecha actual." << endl;
        return;
    }

    // Modificar los datos de la cita
    wcscpy_s(citaExistente->fecha, nuevaFecha);
    wcscpy_s(citaExistente->hora, nuevaHora);
    wcscpy_s(citaExistente->tel, nuevoTel);
    wcscpy_s(citaExistente->especie, nuevaEspecie);
    wcscpy_s(citaExistente->pac, nuevoPac);
    wcscpy_s(citaExistente->motivo, nuevoMotivo);
    citaExistente->cost = nuevoCost;
    wcscpy_s(citaExistente->status, nuevoStatus);
    wcscpy_s(citaExistente->cliente, nuevoCliente);
    wcscpy_s(citaExistente->Doctor, nuevoDoctor);
}
void eliminarCitasEliminadas(citas& lista) {
    nodoB* actual = lista.origen;
    while (actual != nullptr) {
        // Si el status es "ELIMINADA"
        if (wcscmp(actual->dato->status, L"ELIMINADA") == 0) {
            // Si el nodo a eliminar es el origen
            if (actual == lista.origen) {
                lista.origen = actual->siguiente;
                if (lista.origen != nullptr) {
                    lista.origen->anterior = nullptr;
                }
            }
            else {
                actual->anterior->siguiente = actual->siguiente;
                if (actual->siguiente != nullptr) {
                    actual->siguiente->anterior = actual->anterior;
                }
            }
            // Si el nodo a eliminar es el fin
            if (actual == lista.fin) {
                lista.fin = actual->anterior;
            }
            nodoB* temp = actual;
            actual = actual->siguiente;
            delete temp->dato;
            delete temp;
        }
        else {
            actual = actual->siguiente;
        }
    }
}
nodoB* buscarCitasPorFechaDoctor(const WCHAR* fechaCita, const WCHAR* doctor) {
    nodoB* citasCoincidentes = NULL;
    nodoB* nodoActual = listadocitas.origen;
    while (nodoActual != NULL) {
        cita* citaActual = nodoActual->dato;
        if (wcscmp(citaActual->fecha, fechaCita) == 0 && wcscmp(citaActual->Doctor, doctor) == 0) {
            nodoB* nuevaCita = (nodoB*)malloc(sizeof(nodoB));
            nuevaCita->dato = citaActual;
            nuevaCita->siguiente = citasCoincidentes;
            citasCoincidentes = nuevaCita;
        }
        nodoActual = nodoActual->siguiente;
    }

    return citasCoincidentes;
}
void guardarDoctoresEnArchivo() {
    std::ofstream archivo("doctores.bin", std::ios::binary);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Guardar datos de los doctores
    for (NODOLA* nodo = LISTADOCTORES.origen; nodo != nullptr; nodo = nodo->siguiente) {
        std::string nombreDoc = converter.to_bytes(nodo->dato->nombreDoc);
        archivo.write(nombreDoc.c_str(), nombreDoc.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string CEDULA = converter.to_bytes(nodo->dato->CEDULA);
        archivo.write(CEDULA.c_str(), CEDULA.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string DIRFOT = converter.to_bytes(nodo->dato->DIRFOT);
        archivo.write(DIRFOT.c_str(), DIRFOT.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string CLVUSU = converter.to_bytes(nodo->dato->CLVUSU);
        archivo.write(CLVUSU.c_str(), CLVUSU.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string CONTRA = converter.to_bytes(nodo->dato->CONTRA);
        archivo.write(CONTRA.c_str(), CONTRA.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
    }

    archivo.close();

    // Limpiar la lista de doctores
    LISTADOCTORES.origen = nullptr;
    LISTADOCTORES.fin = nullptr;
}
void guardarCitasEnArchivo() {
    std::ofstream archivo("citas.bin", std::ios::binary);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Guardar datos de las citas
    for (nodoB* nodo = listadocitas.origen; nodo != nullptr; nodo = nodo->siguiente) {
        std::string fecha = converter.to_bytes(nodo->dato->fecha);
        archivo.write(fecha.c_str(), fecha.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string hora = converter.to_bytes(nodo->dato->hora);
        archivo.write(hora.c_str(), hora.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string tel = converter.to_bytes(nodo->dato->tel);
        archivo.write(tel.c_str(), tel.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string especie = converter.to_bytes(nodo->dato->especie);
        archivo.write(especie.c_str(), especie.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string pac = converter.to_bytes(nodo->dato->pac);
        archivo.write(pac.c_str(), pac.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string motivo = converter.to_bytes(nodo->dato->motivo);
        archivo.write(motivo.c_str(), motivo.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string status = converter.to_bytes(nodo->dato->status);
        archivo.write(status.c_str(), status.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string cliente = converter.to_bytes(nodo->dato->cliente);
        archivo.write(cliente.c_str(), cliente.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        std::string Doctor = converter.to_bytes(nodo->dato->Doctor);
        archivo.write(Doctor.c_str(), Doctor.size());
        archivo.put('\0');  // Agregar un carácter nulo al final del campo
        archivo.write((char*)&nodo->dato->cost, sizeof(double));
    }

    archivo.close();

    // Limpiar la lista de citas
    listadocitas.origen = nullptr;
    listadocitas.fin = nullptr;
}
void cargarDoctoresDesdeArchivo() {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::ifstream archivo("doctores.bin", std::ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        //std::cout << "El archivo no existe o no se pudo abrir." << std::endl;
        return;
    }

    // Cargar datos de los doctores
    while (!archivo.eof()) {
        Doctor* doctor = new Doctor;
        std::string nombreDoc;
        std::getline(archivo, nombreDoc, '\0');
        std::wstring nombreDocW = converter.from_bytes(nombreDoc);
#pragma warning( suppress :4996).
        wcscpy(doctor->nombreDoc, nombreDocW.c_str());
        std::string CEDULA;
        std::getline(archivo, CEDULA, '\0');
        std::wstring CEDULAW = converter.from_bytes(CEDULA);
#pragma warning( suppress :4996).
        wcscpy(doctor->CEDULA, CEDULAW.c_str());
        std::string DIRFOT;
        std::getline(archivo, DIRFOT, '\0');
        std::wstring DIRFOTW = converter.from_bytes(DIRFOT);
#pragma warning( suppress :4996).
        wcscpy(doctor->DIRFOT, DIRFOTW.c_str());
        std::string CLVUSU;
        std::getline(archivo, CLVUSU, '\0');
        std::wstring CLVUSUW = converter.from_bytes(CLVUSU);
#pragma warning( suppress :4996).
        wcscpy(doctor->CLVUSU, CLVUSUW.c_str());
        std::string CONTRA;
        std::getline(archivo, CONTRA, '\0');
        std::wstring CONTRAW = converter.from_bytes(CONTRA);
#pragma warning( suppress :4996).
        wcscpy(doctor->CONTRA, CONTRAW.c_str());
        NODOLA* nodo = new NODOLA;
        nodo->dato = doctor;
        nodo->siguiente = nullptr;
        nodo->anterior = LISTADOCTORES.fin;
        if (LISTADOCTORES.fin != nullptr) {
            LISTADOCTORES.fin->siguiente = nodo;
        }
        LISTADOCTORES.fin = nodo;
        if (LISTADOCTORES.origen == nullptr) {
            LISTADOCTORES.origen = nodo;
        }
    }

    archivo.close();
}
void cargarCitasDesdeArchivo() {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::ifstream archivo("citas.bin", std::ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        //std::cout << "El archivo no existe o no se pudo abrir." << std::endl;
        return;
    }

    // Cargar datos de las citas
    std::string fecha;
    while (std::getline(archivo, fecha, '\0')) {
        cita* citaNueva = new cita;
        std::wstring fechaW = converter.from_bytes(fecha);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->fecha, fechaW.c_str());
        std::string hora;
        std::getline(archivo, hora, '\0');
        std::wstring horaW = converter.from_bytes(hora);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->hora, horaW.c_str());
        std::string tel;
        std::getline(archivo, tel, '\0');
        std::wstring telW = converter.from_bytes(tel);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->tel, telW.c_str());
        std::string especie;
        std::getline(archivo, especie, '\0');
        std::wstring especieW = converter.from_bytes(especie);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->especie, especieW.c_str());
        std::string pac;
        std::getline(archivo, pac, '\0');
        std::wstring pacW = converter.from_bytes(pac);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->pac, pacW.c_str());
        std::string motivo;
        std::getline(archivo, motivo, '\0');
        std::wstring motivoW = converter.from_bytes(motivo);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->motivo, motivoW.c_str());
        std::string status;
        std::getline(archivo, status, '\0');
        std::wstring statusW = converter.from_bytes(status);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->status, statusW.c_str());
        std::string cliente;
        std::getline(archivo, cliente, '\0');
        std::wstring clienteW = converter.from_bytes(cliente);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->cliente, clienteW.c_str());
        std::string Doctor;
        std::getline(archivo, Doctor, '\0');
        std::wstring DoctorW = converter.from_bytes(Doctor);
#pragma warning( suppress :4996).
        wcscpy(citaNueva->Doctor, DoctorW.c_str());
        archivo.read((char*)&citaNueva->cost, sizeof(double));
        // Crea un nuevo nodo y añade la cita a la lista
        nodoB* nodo = new nodoB;
        nodo->dato = citaNueva;
        nodo->siguiente = nullptr;
        nodo->anterior = listadocitas.fin;
        if (listadocitas.fin != nullptr) {
            listadocitas.fin->siguiente = nodo;
        }
        listadocitas.fin = nodo;
        if (listadocitas.origen == nullptr) {
            listadocitas.origen = nodo;
        }
    }

    archivo.close();
}






// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LISTADOCTORES.origen = NULL;
    LISTADOCTORES.fin = NULL;
    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PREAVANCEPRO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PREAVANCEPRO));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PREAVANCEPRO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PREAVANCEPRO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND ventana = CreateDialog(hInst,MAKEINTRESOURCE(Login), NULL, WndProc);
   
   if (!ventana)
   {
      return FALSE;
   }

   ShowWindow(ventana, nCmdShow);
   UpdateWindow(ventana);

   return TRUE;
}

LRESULT CALLBACK RegistrarCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if( x==0)
    { 
    ShowWindow(GetDlgItem(hWnd, IDC_STATICx), SW_HIDE); // Ocultar
    }
    
    switch (message)
    {
       case WM_COMMAND:
       {
          
           int wmId = LOWORD(wParam);
           // Analizar las selecciones de menú:
           switch (wmId)
           {
           case IDC_aceptar: {
               WCHAR nom[255];
               GetDlgItemText(hWnd, IDC_EDIT1, nom, 255);
               WCHAR cedula[9];
               GetDlgItemText(hWnd, IDC_EDIT2, cedula, 9);
               WCHAR DIRFOT[255];
               GetDlgItemText(hWnd, IDC_EDIT3, DIRFOT, 255);
               WCHAR CLVUSU[100];
               GetDlgItemText(hWnd, ID_edit4, CLVUSU, 100);
               WCHAR CONTRA[100];
               GetDlgItemText(hWnd, IDC_EDIT5, CONTRA, 100);
               if (wcslen(nom) == 0 || wcslen(cedula) == 0 || wcslen(DIRFOT) == 0 || wcslen(CLVUSU) == 0 || wcslen(CONTRA) == 0) {
                   x = 1;
               }
               else {
                   agregarDoctor(nom, cedula, DIRFOT, CLVUSU, CONTRA);
               }
               if (x == 1)
               {
                   //muestra el error
                   ShowWindow(GetDlgItem(hWnd, IDC_STATICx), SW_SHOW);
                   SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), L"");
                   SetWindowText(GetDlgItem(hWnd, IDC_EDIT2), L"");
                   SetWindowText(GetDlgItem(hWnd, IDC_EDIT3), L"");
                   SetWindowText(GetDlgItem(hWnd, ID_edit4), L"");
                   SetWindowText(GetDlgItem(hWnd, IDC_EDIT5), L"");
               }
               if (x == 0)
               {

                   HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(Login), NULL, WndProc);
                   ShowWindow(ventana, SW_SHOW);
                   EndDialog(hWnd, 0);
               }
           }break;
           case IDC_FOTO:
           {
               WCHAR ruta[300] = { 0 };
               OPENFILENAME ofn;
               ZeroMemory(&ofn, sizeof(ofn));
               ofn.lStructSize = sizeof(OPENFILENAME);
               ofn.hwndOwner = hWnd;
               ofn.lpstrFile = ruta;
               ofn.nMaxFile = 1000;
               ofn.lpstrFilter = L"Hola Bitmap\0*.bmp\0";
               ofn.nFilterIndex = 1;
               ofn.lpstrTitle = NULL;
               ofn.nMaxFileTitle = 0;
               ofn.lpstrInitialDir = NULL;
               ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
               if (GetOpenFileName(&ofn)) {
                   SetDlgItemText(hWnd,
                       IDC_EDIT3,
                       ruta);
               }
                  
           }
           break;
           default: {
               return DefWindowProc(hWnd, message, wParam, lParam);
           }break;
           }break;
       }
       break;
        default:
        break;
    }return FALSE;

}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//


LRESULT CALLBACK infocall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        Doctor* doctor = buscarDoctorW(ClVACT, CONACT);
        if (doctor != NULL) {
            
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT1x), doctor->nombreDoc);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT2x), doctor->CEDULA);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT3x), doctor->DIRFOT);
            SetWindowText(GetDlgItem(hWnd, ID_edit4x), doctor->CLVUSU);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT5x), doctor->CONTRA);
            HBITMAP imagen =
                (HBITMAP)LoadImage(hInst,
                    DIRACT,
                    IMAGE_BITMAP,
                    150, 200,
                    LR_LOADFROMFILE |
                    LR_DEFAULTCOLOR |
                    LR_DEFAULTSIZE);
            if (imagen != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_FOTO2), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
            }
            
        }
        else {
            MessageBox(NULL, L"Doctor no encontrado", L"Error", MB_OK | MB_ICONERROR);
        }

    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId)
        {
        case IDC_Trasladar: {
            WCHAR nombr[255];
            GetDlgItemText(hWnd, IDC_EDIT1x, nombr, 255);
            WCHAR cedulac[9];
            GetDlgItemText(hWnd, IDC_EDIT2x, cedulac, 9);
            WCHAR DIRFOTTc[255];
            GetDlgItemText(hWnd, IDC_EDIT3x, DIRFOTTc, 255);
            WCHAR CLVUSUUc[100];
            GetDlgItemText(hWnd, ID_edit4x, CLVUSUUc, 100);
            WCHAR CONTRAAc[100];
            GetDlgItemText(hWnd, IDC_EDIT5x, CONTRAAc, 100);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT1x2),nombr);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT2x2), cedulac);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT3x2), DIRFOTTc);
            SetWindowText(GetDlgItem(hWnd, ID_edit4x2), CLVUSUUc);
            SetWindowText(GetDlgItem(hWnd, IDC_EDIT5x2), CONTRAAc);
        }
        break;
        case IDC_EDITAR:
        {
            // Asume que hEdit es el controlador de tu control de edición
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT1x2), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT2x2), TRUE);
            EnableWindow(GetDlgItem(hWnd, ID_edit4x2), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT5x2), TRUE);

        }
        break;
        case IDC_FOTO3:
        {
            WCHAR ruta[300] = { 0 };
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = ruta;
            ofn.nMaxFile = 1000;
            ofn.lpstrFilter = L"Hola Bitmap\0*.bmp\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (GetOpenFileName(&ofn)) {
                SetDlgItemText(hWnd,
                    IDC_EDIT3x2,
                    ruta);
            }
         
        }
        break;
        case IDC_Guardar:
        {
            if (!IsWindowEnabled(GetDlgItem(hWnd, IDC_EDIT1x2))) {
                MessageBox(NULL, L"No se puede editar ahora", L"Error", MB_OK | MB_ICONERROR);

            }
            else {
                WCHAR nomm[255];
                GetDlgItemText(hWnd, IDC_EDIT1x2, nomm, 255);
                if (!esSoloLetras(nomm))
                {
                    MessageBox(NULL, L"No tiene puras letras el nombre", L"Error", MB_OK | MB_ICONERROR);
                    break;
                }
                else
                {
                    WCHAR cedulaa[9];
                    GetDlgItemText(hWnd, IDC_EDIT2x2, cedulaa, 9);
                    WCHAR DIRFOTT[255];
                    GetDlgItemText(hWnd, IDC_EDIT3x2, DIRFOTT, 255);
                    WCHAR CLVUSUU[255];
                    GetDlgItemText(hWnd, ID_edit4x2, CLVUSUU, 255);
                    WCHAR CONTRAA[255];
                    GetDlgItemText(hWnd, IDC_EDIT5x2, CONTRAA, 255);
                    modificarDoctor(nomm, cedulaa, DIRFOTT, CLVUSUU, CONTRAA, ClVACT, CONACT);
                    //MessageBox(NULL, L"La Pagina va a actualizarse", L"exito", MB_OK | MB_ICONINFORMATION);
                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Info), NULL, infocall);
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                }
            }

        }
        break;
        case IDCANCEL: {
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT1x), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT2x), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT3x), FALSE);
            EnableWindow(GetDlgItem(hWnd, ID_edit4x), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_EDIT5x), FALSE);
        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        EndDialog(hWnd, 0);
        break;
    }
    return 0;
}
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (x == 0)
    {
        ShowWindow(GetDlgItem(hWnd, IDC_STATICC), SW_HIDE); // Ocultar
    }
    switch (message)
    {
    case WM_INITDIALOG:
    {
        
    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDC_BUTTON1: {
            // falta checar que no se quiebre si ambos campos estan vacios.
            cargarDoctoresDesdeArchivo();
            cargarCitasDesdeArchivo();
            WCHAR usu[100];
            GetDlgItemText(hWnd, IDC_EDIT1, usu, 100);
            //
            WCHAR contr[100];
            GetDlgItemText(hWnd, IDC_EDIT2, contr, 100);

            Doctor* doctor = buscarDoctorW(usu, contr);
            if (doctor != NULL) {
                wcscpy_s(docAct, doctor->nombreDoc);
                wcscpy_s(ClVACT, doctor->CLVUSU);
                wcscpy_s(CONACT, doctor->CONTRA);
                wcscpy_s(DIRACT, doctor->DIRFOT);
            }
            else {

            }
            if (docAct[0] == L'\0')
            {
                x = 1;
                ShowWindow(GetDlgItem(hWnd, IDC_STATICC), SW_SHOW);
            }
            else
            {//IDD_Info
                x = 0;
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Info), NULL, infocall);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
        break;
        case Bt_Registrar: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_registro), NULL, RegistrarCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    break;
    case WM_DESTROY:{
        EndDialog(hWnd, 0);
    }break;
    }
    return 0;
}
LRESULT CALLBACK Citascall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        HBITMAP imagen =
            (HBITMAP)LoadImage(hInst,
                DIRACT,
                IMAGE_BITMAP,
                150, 200,
                LR_LOADFROMFILE |
                LR_DEFAULTCOLOR |
                LR_DEFAULTSIZE);
        if (imagen != NULL)
        {
            SendMessage(GetDlgItem(hWnd, IDC_FOTO4), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
        } SetWindowText(GetDlgItem(hWnd, IDC_EDIT15),docAct);
        HWND hWndComboBox = GetDlgItem(hWnd, IDC_especie);
        LONG style = GetWindowLong(hWndComboBox, GWL_STYLE);
        style &= ~CBS_DROPDOWN; // Elimina CBS_DROPDOWN
        style |= CBS_DROPDOWNLIST; // Añade CBS_DROPDOWNLIST
        SetWindowLong(hWndComboBox, GWL_STYLE, style);
        
        const WCHAR* elementos[] = { TEXT("Perro"), TEXT("Gato"), TEXT("REPTIL"), TEXT("OTRO") };
        for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); i++) {
            SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)elementos[i]);
        }

        return TRUE;
    }

    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId)
        {
        case IDC_REGISTRAR:
        {
            WCHAR FECHA[11];
            GetDlgItemText(hWnd, IDC_FECHA, FECHA, 11);
            WCHAR CLI[100];
            GetDlgItemText(hWnd, IDC_CLI, CLI, 255);
            WCHAR TEL[12];
            GetDlgItemText(hWnd, IDC_TEL, TEL, 12);
            WCHAR PAC[100];
            GetDlgItemText(hWnd, IDC_PAC, PAC, 100);
            WCHAR MOTV[100];
            GetDlgItemText(hWnd, IDC_MOTV, MOTV, 100);
            WCHAR COST[100];
            GetDlgItemText(hWnd, IDC_COST, COST, 100);

            // Convertir WCHAR a double
            double costValue = wcstod(COST, NULL);

            WCHAR HORA[11];
            GetDlgItemText(hWnd, IDC_HORA, HORA, 11);
            WCHAR especie[100];
            GetDlgItemText(hWnd, IDC_especie, especie, 100);
            WCHAR STATUS[30] = L"PENDIENTE";
            if (!esSoloNumeros(TEL)|| !esSoloNumeros(COST))
            {
                MessageBox(NULL, L"", L"No son puros numeros el costo o el telefono", MB_OK | MB_ICONERROR);
            }
            else {
                if (wcslen(FECHA) == 0 || wcslen(CLI) == 0 || wcslen(TEL) == 0 || wcslen(MOTV) == 0 || wcslen(COST) == 0) {
                    MessageBox(NULL, L" existe algun campo vacio", L"Error", MB_OK | MB_ICONERROR);
                }
                else {
                    crearCita(FECHA, HORA, TEL, especie, PAC, MOTV, costValue, STATUS, CLI, docAct);
                    ordenarCitas();
                    MessageBox(NULL, L"Cita Registrada", L"Exito", MB_OK | MB_ICONERROR);
                }
            }

        }break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        EndDialog(hWnd, 0);
        break;
    }
    return 0;
}
LRESULT CALLBACK Modicall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
        {
            HBITMAP imagen =
                (HBITMAP)LoadImage(hInst,
                    DIRACT,
                    IMAGE_BITMAP,
                    150, 200,
                    LR_LOADFROMFILE |
                    LR_DEFAULTCOLOR |
                    LR_DEFAULTSIZE);
            if (imagen != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_FOTO6), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
            } SetWindowText(GetDlgItem(hWnd, IDC_EDIT17), docAct);
            HWND hWndComboBox = GetDlgItem(hWnd, IDC_especie2);
            LONG style = GetWindowLong(hWndComboBox, GWL_STYLE);
            style &= ~CBS_DROPDOWN; // Elimina CBS_DROPDOWN
            style |= CBS_DROPDOWNLIST; // Añade CBS_DROPDOWNLIST
            SetWindowLong(hWndComboBox, GWL_STYLE, style);

            const WCHAR* elementos[] = { TEXT("Perro"), TEXT("Gato"), TEXT("REPTIL"), TEXT("OTRO") };
            for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); i++) {
            SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)elementos[i]);
            }
            HWND hWndComboBox1 = GetDlgItem(hWnd, IDC_COMBO1);
            LONG style1 = GetWindowLong(hWndComboBox1, GWL_STYLE);
            style1 &= ~CBS_DROPDOWN; // Elimina CBS_DROPDOWN
            style1 |= CBS_DROPDOWNLIST; // Añade CBS_DROPDOWNLIST
            SetWindowLong(hWndComboBox1, GWL_STYLE, style1);

            const WCHAR* opciones[] = { TEXT("PENDIENTE"), TEXT("CANCELADA"), TEXT("EFECTUADA"),TEXT("ELIMINADA") };
            for (int i = 0; i < sizeof(opciones) / sizeof(opciones[0]); i++) {
                SendMessage(hWndComboBox1, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)opciones[i]);
            }


            return TRUE;
        }
        break;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            if (menu(wmId, hWnd)) {
                return FALSE;
            }
            switch (wmId)
            {
            case IDC_BUSCAR:
            {
                WCHAR FECHA[11];
                GetDlgItemText(hWnd, IDC_FECHA, FECHA, 11);
                WCHAR hora[11];
                GetDlgItemText(hWnd, IDC_HORA, hora, 11);
                WCHAR clie[12];
                GetDlgItemText(hWnd, IDC_EDIT1, clie, 12);
                WCHAR PAC[100];
                GetDlgItemText(hWnd, IDC_EDIT2, PAC, 100);
                //Doctor* doctor = buscarDoctorW(ClVACT, CONACT);
                cita* cita = buscarCita(FECHA, hora, clie, PAC, docAct);
                if (cita != NULL) {
                    double cast = cita->cost;
                    WCHAR buffer[50];
                    swprintf(buffer, 50, L"%f", cast);
                    SetWindowText(GetDlgItem(hWnd, IDC_EDIT3), cita->tel);
                    SetWindowText(GetDlgItem(hWnd, IDC_EDIT4), cita->status);
                    SetWindowText(GetDlgItem(hWnd, IDC_EDIT13), cita->especie);
                    SetWindowText(GetDlgItem(hWnd, IDC_EDIT5), cita->motivo);
                    SetWindowText(GetDlgItem(hWnd, IDC_EDIT6), buffer);

                }
                else {
                    MessageBox(NULL, L"Cita no encontrada", L"Error", MB_OK | MB_ICONERROR);
                }

            }break;
            case IDC_Guardar:
            {
                // falta hacer una validacion donde no este todo vacio... y ademas de habilitar todo
                // lo deshabilitado 
                WCHAR FECHA[11];
                GetDlgItemText(hWnd, IDC_FECHA, FECHA, 11);
                WCHAR hora[11];
                GetDlgItemText(hWnd, IDC_HORA, hora, 11);
                WCHAR clie[12];
                GetDlgItemText(hWnd, IDC_EDIT1, clie, 12);
                WCHAR PAC[100];
                GetDlgItemText(hWnd, IDC_EDIT2, PAC, 100);
                // nuevos datos
                WCHAR FECHAN[11];
                GetDlgItemText(hWnd, IDC_FECHA2, FECHAN, 11);
                WCHAR horaN[11];
                GetDlgItemText(hWnd, IDC_HORA2, horaN, 11);
                WCHAR clieN[12];
                GetDlgItemText(hWnd, IDC_EDIT7, clieN, 12);
                WCHAR PACN[100];
                GetDlgItemText(hWnd, IDC_EDIT8, PACN, 100);
                WCHAR costo[10];
                GetDlgItemText(hWnd, IDC_EDIT12, costo, 10);
                double valor = wcstod(costo, NULL);
                WCHAR status[30];
                GetDlgItemText(hWnd, IDC_COMBO1, status, 30);
                WCHAR motiv[100];
                WCHAR especie[30];
                WCHAR tel[12];
                GetDlgItemText(hWnd, IDC_EDIT9, tel, 12);
                GetDlgItemText(hWnd, IDC_especie2, especie, 100);
                GetDlgItemText(hWnd, IDC_EDIT11, motiv, 100);
                if (wcscmp(status, L"ELIMINADA") == 0) 
                {
                    // Código para eliminar el nodo
                    modificarCita(FECHA, hora, clie, PAC, FECHAN, horaN, tel, especie, PACN, motiv, valor, status, clieN, docAct);
                    eliminarCitasEliminadas(listadocitas);
                    MessageBox(NULL, L"Cita Eliminada", L"Exito", MB_OK | MB_ICONERROR);
                }else
                {
                    modificarCita(FECHA, hora, clie, PAC, FECHAN, horaN, tel, especie, PACN, motiv, valor, status, clieN, docAct);
                    eliminarCitasEliminadas(listadocitas);
                    ordenarCitas();
                    MessageBox(NULL, L"Cita modificada", L"Exito", MB_OK | MB_ICONERROR);
                }
  
            }
            break;
            case IDC_SALTO:
            {
                WCHAR FECHA[11];
                GetDlgItemText(hWnd, IDC_FECHA, FECHA, 11);
                WCHAR hora[11];
                GetDlgItemText(hWnd, IDC_HORA, hora, 11);
                WCHAR clie[12];
                GetDlgItemText(hWnd, IDC_EDIT1, clie, 12);
                WCHAR PAC[100];
                GetDlgItemText(hWnd, IDC_EDIT2, PAC, 100);
                WCHAR moti[100];
                GetDlgItemText(hWnd, IDC_EDIT5, moti, 100);
                WCHAR status[30];
                GetDlgItemText(hWnd, IDC_EDIT4, status, 30);
                WCHAR TEL[12];
                GetDlgItemText(hWnd, IDC_EDIT3, TEL, 12);
                WCHAR buffer[50];
                GetDlgItemTextW(hWnd, IDC_EDIT6, buffer,50);
                //double caste = wcstod(buffer, NULL);
                //swprintf(buffer, 50, L"%f", caste);
                SetWindowText(GetDlgItem(hWnd, IDC_FECHA2), FECHA);
                SetWindowText(GetDlgItem(hWnd, IDC_HORA2), hora);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT7), clie);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT8), PAC);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT9), TEL);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT11), moti);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT10), status);
                SetWindowText(GetDlgItem(hWnd, IDC_EDIT12), buffer);
                EnableWindow(GetDlgItem(hWnd, IDC_EDIT9), TRUE);
                EnableWindow(GetDlgItem(hWnd, IDC_especie2), TRUE);
                EnableWindow(GetDlgItem(hWnd, IDC_EDIT11), TRUE);
                EnableWindow(GetDlgItem(hWnd, IDC_EDIT12), TRUE);
                EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), TRUE);

            }
            break;
            default: {
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
            }
            break;
        }
        
    }
    return 0;
}
LRESULT CALLBACK Agendacall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
        {
            HBITMAP imagen =
                (HBITMAP)LoadImage(hInst,
                    DIRACT,
                    IMAGE_BITMAP,
                    150, 200,
                    LR_LOADFROMFILE |
                    LR_DEFAULTCOLOR |
                    LR_DEFAULTSIZE);
            if (imagen != NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_FOTO8), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
            } SetWindowText(GetDlgItem(hWnd, IDC_EDIT19), docAct);
            WCHAR fechaCita[11];
            GetDlgItemText(hWnd, IDC_FECHAC, fechaCita, 11);
            // Añadir las citas
            nodoB* citas = buscarCitasPorFechaDoctor(fechaCita, docAct);
            nodoB* nodoActual = citas;
            while (nodoActual != NULL) {
                cita* citaActual = nodoActual->dato;

                // Formatear los datos de la cita en una cadena
                WCHAR buffer[256];
                swprintf(buffer, sizeof(buffer) / sizeof(WCHAR), L"%s %s %s %s %s %s %.2f %s %s",
                    citaActual->fecha, citaActual->hora, citaActual->tel, citaActual->especie,
                    citaActual->pac, citaActual->motivo, citaActual->cost, citaActual->status,
                    citaActual->cliente);

                // Añadir la cadena al ListBox
                SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_ADDSTRING, 0, (LPARAM)buffer);

                nodoActual = nodoActual->siguiente;
            }
           

        }
        break;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            if (menu(wmId, hWnd)) {
                return FALSE;
            }
            switch (wmId)
            {
            case IDC_BUSCAR:
            {
                WCHAR fechaCita[11];
                GetDlgItemText(hWnd, IDC_FECHAC, fechaCita, 11);
                // Añadir las citas
                nodoB* citas = buscarCitasPorFechaDoctor(fechaCita, docAct);
                nodoB* nodoActual = citas;
                while (nodoActual != NULL) {
                    cita* citaActual = nodoActual->dato;

                    // Formatear los datos de la cita en una cadena
                    WCHAR buffer[256];
                    swprintf(buffer, sizeof(buffer) / sizeof(WCHAR), L"%s %s %s %s %s %s %.2f %s %s",
                        citaActual->fecha, citaActual->hora, citaActual->tel, citaActual->especie,
                        citaActual->pac, citaActual->motivo, citaActual->cost, citaActual->status,
                        citaActual->cliente);

                    // Añadir la cadena al ListBox
                    SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_ADDSTRING, 0, (LPARAM)buffer);

                    nodoActual = nodoActual->siguiente;
                }
                // malloc();
            }break;
            default: {
               return DefWindowProc(hWnd, message, wParam, lParam);
                }
             break;
            }
            break;
        }
        break;
    default:
        break;
    }
    return 0;
}
bool menu(int opcion, HWND ventana) {
    INT_PTR result = 0;

    switch (opcion) {
    case ID_INFO2: {
        HWND pron = ventana;
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Info), NULL, infocall);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(pron, 0);

    } break;
    case ID_AGENDA: {
        HWND pron = ventana;
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_AGENDA), NULL, Agendacall);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(pron, 0);
    } break;
    case ID_Modificar2:{
            HWND pron = ventana;
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Cambios), NULL,Modicall);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(pron, 0);
        }
    break;
    case ID_CITAS: {
        HWND pron = ventana;
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Citas), NULL, Citascall);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(pron, 0);
    } break;
    case ID_SALIR:
    {
        guardarCitasEnArchivo();
        guardarDoctoresEnArchivo();
        PostQuitMessage(0);
    }
    default:
    {
        return false;
    }
    break;
    }
    return TRUE;
}
