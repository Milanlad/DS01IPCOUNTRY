#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAXCHAR 1024
unsigned long duree;
struct timeval debutCalcul, finCalcul;

int main (int agrc, char *argv[])
{
gettimeofday(&debutCalcul,NULL);// démare le timer pour le calcule
char ip_from_convert[99];
char ip_to_convert[99];
char country_convert[99];
memset(ip_from_convert,0,99);
memset(ip_to_convert,0,99);
memset(country_convert,0,99);
long int ip_0 =0;
long int ip_1 =0;
long int ip_2 =0;
long int ip_3 =0;
long int ip_decimal = 0; // l'ip stocker sous un seul entier de 4 octets au lieu de 4 entier de 1 octets
sscanf(argv[1],"%ld.%ld.%ld.%ld",&ip_0,&ip_1,&ip_2,&ip_3);
if (ip_0<0 || ip_0 >255 || ip_1<0 || ip_1>255 || ip_2<0 || ip_2>255 || ip_3<0 || ip_3>255)
    {
    printf("Ip non valide valeur doivent etre comprise en 0 et 255 compris !!!\n");
    return 0 ;
    }                                            
ip_0= ip_0 * 256 * 256 * 256;
ip_1= ip_1 * 256 * 256;
ip_2= ip_2 * 256;
ip_3= ip_3;
ip_decimal = ip_0 + ip_1 + ip_2 + ip_3;
FILE *fp;
char Ligne[MAXCHAR];
char *Sortie;
fp = fopen("geoip.csv","r");
while (feof(fp) != true)
    {
    int stop_at_third = 0 ;
    int long ip_from = 0;
    int long ip_to = 0;
    int member = 0;
    fgets(Ligne, MAXCHAR, fp);
    Sortie = strtok(Ligne, ",");
    while(Sortie != NULL && stop_at_third != 1 )
        {
        if (member == 0)    // on passe dans ce if 2 fois par ligne et l'orsque l'on est sur le premier argument et 2eme argument de la ligne soit l'ip from et l'ip to
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
    if (ip_decimal >= ip_from && ip_decimal <= ip_to)
        {
        printf("Le pays est : %s\n",country_convert);
        gettimeofday(&finCalcul,NULL);
        duree = ((finCalcul.tv_sec - debutCalcul.tv_sec) * 1000000) + (finCalcul.tv_usec - debutCalcul.tv_usec);
        printf( "Duree %ld ms\n", duree );  
        return 0;
        }
    memset(ip_from_convert,0,20);
    memset(ip_to_convert,0,20);
    memset(country_convert,0,20);
    }
return 0;
}