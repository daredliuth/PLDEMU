#include <stdio.h>
#include <stdbool.h>

//Constantes para escalado.
#define TAM_NOMBRE_PIN 3
#define TAM_ENTRADAS 12
#define TAM_SALIDAS 12
//Memorias
#define TAM_MEMORIA_1 7
#define TAM_MEMORIA_2 7
//
#define TAM_REGISTRO 3
#define TAM_VARIABLES 3

//Constantes de configuración.
#define MEGA2560 true
#define ESP32 !MEGA2560

struct ESStruct{
    char nombrePin[3];
    int valor;
    int pinFisico;
};

void ImprimirPin(struct ESStruct pin){
    printf("Pin: ");
    for(int i=0; i < TAM_NOMBRE_PIN; i++){
        printf("%c", pin.nombrePin[i]);
    }
    printf(" - Valor: %d - Pin fisico: %d\n", pin.valor, pin.pinFisico);
}

void ConfiguracionInicial(struct ESStruct arregloEntradas[TAM_ENTRADAS], struct ESStruct arregloSalidas[TAM_SALIDAS]){
    int pinesFisicosEntradas[TAM_ENTRADAS];
    int pinesFisicosSalidas[TAM_SALIDAS];
    if(MEGA2560){
        printf("Placa seleccionada: MEGA2560\n");
        int megaEntradas[TAM_ENTRADAS] = {22,23,24,25,26,27,28,29,53,52,51,50};
        int megaSalidas[TAM_SALIDAS] = {54,55,57,58,59,60,61,62,63,64,65,66};

        for(int i=0; i<TAM_ENTRADAS; i++){ pinesFisicosEntradas[i] = megaEntradas[i]; }
        for(int i=0; i<TAM_SALIDAS; i++){ pinesFisicosSalidas[i] = megaSalidas[i]; }

    }
    else{
        printf("Placa seleccionada: ESP32\n");
        int espEntradas[TAM_ENTRADAS] = {36,39,34,35,32,33,25,26,27,14,12,13};
        int espSalidas[TAM_SALIDAS] = {23,22,3,21,19,18,5,17,16,4,2,15};
        for(int i=0; i<TAM_ENTRADAS; i++){ pinesFisicosEntradas[i] = espEntradas[i]; }
        for(int i=0; i<TAM_SALIDAS; i++){ pinesFisicosSalidas[i] = espSalidas[i]; }
    }

    for(int i=0; i< TAM_ENTRADAS; i++){
        arregloEntradas[i].nombrePin[0] = 'E';
        //Obtenemos las decenas.
        int decenas, unidades;
        unidades = i%10;
        decenas = (i - unidades) / 10;
        //printf("Decenas: %d - Unidades: %d\n", decenas, unidades);
        arregloEntradas[i].nombrePin[1] = '0' + decenas;
        arregloEntradas[i].nombrePin[2] = '0' + unidades;
        arregloEntradas[i].valor = 0;
        arregloEntradas[i].pinFisico = pinesFisicosEntradas[i];
    }

    for(int i=0; i< TAM_SALIDAS; i++){
        arregloSalidas[i].nombrePin[0] = 'S';
        //Obtenemos las decenas.
        int decenas, unidades;
        unidades = i%10;
        decenas = (i - unidades) / 10;
        //printf("Decenas: %d - Unidades: %d\n", decenas, unidades);
        arregloSalidas[i].nombrePin[1] = '0' + decenas;
        arregloSalidas[i].nombrePin[2] = '0' + unidades;
        arregloSalidas[i].valor = 0;
        arregloSalidas[i].pinFisico = pinesFisicosSalidas[i];
    }

    for (int i=0; i<TAM_ENTRADAS; i++){
        ImprimirPin(arregloEntradas[i]);
    }
    printf("\n");
    for(int i=0; i<TAM_ENTRADAS; i++){
        ImprimirPin(arregloSalidas[i]);
    }
    printf("\n");
}

int Memoria1(int direccion){
    int salida[TAM_MEMORIA_1] = {0x8A, 0x1B, 0x24, 0x4D, 0x6C, 0x8E, 0x00};
    printf("Salida de la memoria 1: Hex - %X, Int - %d\n",salida[direccion], salida[direccion], salida[direccion]);
    return salida[direccion];
}

int Memoria2(int direccion){
    int salida[TAM_MEMORIA_1] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    printf("Salida de la memoria 2: Hex - %X, Int - %d\n",salida[direccion], salida[direccion], salida[direccion]);
    return salida[direccion];
}

//Añade aquí la lógica de tu programa.
void Logica(){

}

//Variables de control.
bool continuar = true;
bool modoAutomatico = false;
int contadorModoAutomatico = 0;
int entradaUsuario = 0;

//Variables del ejercicio
struct RegistroStruct{
    char nombre;
    int valor;
};

struct VariableStruct{
    char nombre;
    int valor;
};

int main(){
    struct ESStruct entradas[TAM_ENTRADAS];
    struct ESStruct salidas[TAM_SALIDAS];
    ConfiguracionInicial(entradas, salidas);

    //Variables del ejercicio;
    struct RegistroStruct registro[TAM_REGISTRO];
    registro[0].nombre = 'C';
    registro[0].valor = 0;
    registro[1].nombre = 'B';
    registro[1].valor = 0;
    registro[2].nombre = 'A';
    registro[2].valor = 0;
    
    struct VariableStruct variables[TAM_VARIABLES];
    variables[0].nombre = 'x';
    variables[0].valor = 0;
    variables[1].nombre = 'y';
    variables[1].valor = 0;
    variables[2].nombre = 'z';
    variables[2].valor = 0;

    Memoria1(0x3);
    Memoria2(5);

    while(continuar){
        Logica();
        //Imprimimos las entradas y salidas.
        if(modoAutomatico){
            for(int i=0; i<contadorModoAutomatico; i++){
                //Automatizar la asignación de variables.
                Logica();
            }
            printf("Limite de iteraciones alcanzado (%d)\nSaliendo de la simulación.", &contadorModoAutomatico);
            continuar = false;
        }

        else{
            for(int i=0; i<TAM_VARIABLES; i++){
                printf("Escriba el valor de %c: $->", variables[i].nombre);
                scanf("%d",&variables[i].valor);
            }
            printf("Continuar? 1:Si / 0: No. $->");
            scanf("%d", &entradaUsuario);
            if(entradaUsuario != 1){continuar = false;}
        }
    }
    printf("Saliendo de la simulacion.");
    return 0;
}
