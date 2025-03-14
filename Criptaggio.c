#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void inserire_pw(char *passw, char *caratteri_speciali) // Funzione per inserire la password
{
    int i = 0;
    int j = 0;
    int trovato = 0;
    char carattere;

    printf(" _____________________________________________ \n");
    printf("|                                             |\n");
    printf("|  Inserire una password di max 15 caratteri  |\n");
    printf("|           che verra' crittografata:         |\n");
    printf("|                                             |\n");
    printf("|   Premere invio alla fine della digitazione |\n");
    printf("|  se non sono stati raggiunti i 15 caratteri |\n");
    printf("|_____________________________________________|\n");
    printf("Password: ");

    while (i < 15)
    {
        trovato = 0;
        carattere = getch();
        if (carattere == '\r') // Se l'utente preme "invio", termina la lettura
        {
            break;
        }
        for (j = 0; j < 6; j++)
        {
            if (carattere == caratteri_speciali[j] || carattere >= 'A' && carattere <= 'Z' || carattere >= 'a' && carattere <= 'z' || carattere >= '0' && carattere <= '9')
            {
                trovato = 1;
            }
        }

        if (trovato)
        {
            passw[i] = carattere;
            printf("*"); // Mostra a schermo un asterisco invece del carattere digitato
            i++;
        }
    }
    passw[i] = '\0';
}
bool car_speciale(char carattere, char *caratteri_speciali) // Funzione per verificare la presenza di caratteri speciali
{
    int i = 0;
    for (i = 0; i < 6; i++)
    {
        if (carattere == caratteri_speciali[i])
        {
            return true;
        }
    }
    return false;
}

void cripta_pw(char *passw, char *passw_crit, int lunghezza, char *caratteri_speciali) // Funzione per crittografare la password
{
    int i = 0;

    for (i = 0; i < lunghezza; i++)
    {
        if ((passw[i] >= 'a' && passw[i] <= 'w') || (passw[i] >= 'A' && passw[i] <= 'W')) // Incremento di 3 della posizione delle lettere se comprese tra "a/A" e "w/W"
        {
            passw_crit[i] = (char)(passw[i] + 3);
        }
        else if ((passw[i] >= 'x' && passw[i] <= 'z') || (passw[i] >= 'X' && passw[i] <= 'Z')) // Incremento di -26 + 3 della posizione delle lettere se comprese tra "x/X" e "y/Y"
        {
            passw_crit[i] = (char)(passw[i] - 26 + 3);
        }
        else if (passw[i] >= '0' && passw[i] <= '6') // Incremento di 3 della posizione dei numeri se compresi tra "0" e "6"
        {
            passw_crit[i] = (char)(passw[i] + 3);
        }
        else if (passw[i] >= '7' && passw[i] <= '9') // Incremento di -10 +3 della posizione dei numeri se compresi tra "7" e "9"
        {
            passw_crit[i] = (char)(passw[i] - 10 + 3);
        }
        else if (car_speciale(passw[i], caratteri_speciali)) // Chiamata della funzione per verificare la presenza di caratteri speciali e incremento di +3 della posizione dei caratteri speciali
        {
            passw_crit[i] = (char)(passw[i] + 3);
        }
        else
        {
            passw_crit[i] = (char)passw[i];
        }
    }
    passw_crit[lunghezza] = '\0';
}

int main()
{
    char caratteri_speciali[] = "!$=?^*";

    while (1) // Loop infinito per ripetere l'operazione
    {
        char passw[16];
        inserire_pw(passw, caratteri_speciali); // Inserimento della password

        int lunghezza = strlen(passw);  // Definizione della lunghezza della password
        char passw_crit[lunghezza + 1]; // Array per la password crittografata

        cripta_pw(passw, passw_crit, lunghezza, caratteri_speciali); // Crittografia della password

        printf("\nPassword crittografata: %s\n", passw_crit); // Output della password crittografata

        printf("\nPremere INVIO per inserire una nuova password o ESC per uscire...\n");

        char scelta;
        while (1)
        {
            scelta = getch();
            if (scelta == '\r') // Tasto INVIO
                break;
            else if (scelta == 27) // Tasto ESC
                return 0;
        }
        system("cls");
    }
}