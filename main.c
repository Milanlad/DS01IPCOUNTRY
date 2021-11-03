#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAXCHAR 1024
unsigned long duree;
struct timeval debutCalcul, finCalcul;

// Convertie une ip de la forme string X.X.X.X en int X 
int ip_convert_to_decimal (char ip_who_convert[99])
{
    long int ip_0 =0;
    long int ip_1 =0;
    long int ip_2 =0;
    long int ip_3 =0;
    long int ip_dec =0;
    sscanf(ip_who_convert,"%ld.%ld.%ld.%ld",&ip_0,&ip_1,&ip_2,&ip_3); 
    if (ip_0<0 || ip_0 >255 || ip_1<0 || ip_1>255 || ip_2<0 || ip_2>255 || ip_3<0 || ip_3>255)
    {
        return -1 ;
    }
    ip_0= ip_0 * 256 * 256 * 256;
    ip_1= ip_1 * 256 * 256;
    ip_2= ip_2 * 256;
    ip_3= ip_3;
    ip_dec = ip_0 + ip_1 + ip_2 + ip_3;
    return ip_dec ;
}

//vide les tableau de char 
void reset_memorie_case (char ip_from_convert_f[99], char ip_to_convert_f[99], char country_convert_f[99])
{
    memset(ip_from_convert_f,0,99);
    memset(ip_to_convert_f,0,99);
    memset(country_convert_f,0,99);
}

// retourne si il y as un cas d'erreur pour le moment : Vérif de la valeur de l'ip , Vérif du nombre d'arguments
bool error_verif (int argc_f, int ip_decimal_f)
{
    if(argc_f !=2)
    {
        printf("NOMBRE D'ARGUMENT MAUVAIS\n");
        return true;
    }
    if(ip_decimal_f == -1)
    {
        printf("Ip non conforme <0 ou >255 veuillez rentrer une ip valide\n ");
        return true;
    }
    return false;
}

void timer_print ()
{
    gettimeofday(&finCalcul,NULL);
    duree = ((finCalcul.tv_sec - debutCalcul.tv_sec) * 1000000) + (finCalcul.tv_usec - debutCalcul.tv_usec);
    printf( "Duree %ld ms\n", duree );  
}

// main du programme 
int main (int agrc, char *argv[])
{ 
    gettimeofday(&debutCalcul,NULL);// démare le timer pour le calcule
    bool error_state = false ;
    char ip_from_convert[99];
    char ip_to_convert[99];
    char country_convert[99];
    char ip_convert[99];
    int error_nb_arg = 0;
    long int ip_decimal = 0; // l'ip stocker sous un seul entier de 4 octets au lieu de 4 entier de 1 octets
    reset_memorie_case(ip_from_convert,ip_to_convert,country_convert);
    strcpy(ip_convert,argv[1]);
    ip_decimal = ip_convert_to_decimal(ip_convert);
    if (error_state == true) // si une erreur est détecter ferme le programme
    {
        printf("Fermeture du programme\n");
        return 0;
    }
    FILE *fp;
    char Ligne[MAXCHAR];
    char *Sortie;
    fp = fopen("geoip.csv","r");
    // != NULL a ajouter pour gestion fichier vide
    while (feof(fp) != true)
    {
        int stop_at_third = 0 ;
        int long ip_from = 0;
        int long ip_to = 0;
        int member = 0; // permet de savoir a quel argument de la ligne nous sommes
        fgets(Ligne, MAXCHAR, fp);
        Sortie = strtok(Ligne, ",");
        while(Sortie != NULL && stop_at_third != 1 )
        {
            if (member == 0) 
            {
                for (int i = 1;Sortie[i] != '"';i++)
                {
                    ip_from_convert[i-1]=Sortie[i];
                }
                ip_from = atol(ip_from_convert);
            }
            if(member == 1)
            {
                for (int i = 1;Sortie[i] != '"';i++)
                {
                    ip_to_convert[i-1]=Sortie[i];
                }
                ip_to = atol(ip_to_convert);
            }
            if(member == 2)
            {
                for (int i = 1;Sortie[i] != '"';i++)
                {
                    country_convert[i-1]=Sortie[i];
                }
                stop_at_third = 1;
            }
            Sortie = strtok(NULL, ",");
            member ++;
        }
        if (ip_decimal >= ip_from && ip_decimal <= ip_to) // vérifie si l'ip est dans l'intervale de ligne en question 
        {
            printf("Le pays est : %s\n",country_convert);
            timer_print();
            return 0;
        }
    reset_memorie_case(ip_from_convert,ip_to_convert,country_convert);
    }
    return 0;
}