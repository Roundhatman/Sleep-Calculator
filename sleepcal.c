#include <stdio.h>
#include <windows.h>
#include <time.h>

#define BUF_LEN 0x100
#define _XOPEN_SOURCE 700

#define DEFAULT_MSG 0x007
#define HEADING1    0x003
#define HEADING2    0x002
#define OUTPUT_MSG  0x006
#define ERROR_MSG   0x004

float cy;

void SleepNow(void);
void SleepLater(void);
void SetColor(int);

int main(void) {
    char usr;

    // Welcome
    SetColor(HEADING1);
    SetConsoleTitle("SL33P C4LCUL4TOR - L.SW4RN4JITH");
    printf("SL33P C4LCUL4TOR - L.SW4RN4JITH\n");
    printf("-------------------------------\n\n");

    SetColor(HEADING2);
    printf("Introduction :\n");
    SetColor(OUTPUT_MSG);
    printf("This is an experimental program based on sleep cycles.\n"
           "Waking up in the middle of a sleep cycle leaves you feeling tired.\n"
           "A sleep cycle typically last 90min and a 'good night' sleep has about 5 cycles.\n\n");

    SetColor(HEADING2);
    printf("Guide :\n");
    SetColor(OUTPUT_MSG);
    printf("The program let you select sleep now/sleep later.If you select 'sleep now' it will give five time options\n"
           "to wake-up.Otherwise, it will give five time options to hit the bed.Be careful when you enter data.\n"
           "{D=Date, HH=Two number hours in 24 format, MM=Two number minutes.}\n"
           "Do not use electronic devices like mobile phones before sleep, use reading/night mode if it is unavoidable.\n\n");
    SetColor(HEADING2);
    printf("Disclaimer:\n");
    SetColor(OUTPUT_MSG);
    printf("L.Swarnajith, the author of this program, disclaims any liability for any damage caused by using or misusing\n"
            "this software.This program was written in pure C and no harmful instructions were included.No health issues were\n"
            "reported so far (v1.0)\n\n");

    // Gather sleep data
    SetColor(DEFAULT_MSG);
    printf("\nDuration you normally sleep (in hours ex:7.5) : ");
    scanf("%f",&cy);
    if (cy<=0 || cy>=10){
        SetColor(ERROR_MSG);
        printf("WTF ? Meet a doctor.\n");
        SetColor(DEFAULT_MSG);
        system("Pause");
        return 1;
    }
    cy *= 0x2D0;

    // Gather operation type & calculate
    SetColor(DEFAULT_MSG);
    printf("Do you want to sleep now ? 'Y/N' : ");
    scanf("%s",&usr);;
    if (usr==0x059 || usr==0x079) SleepNow();
    else if (usr==0x04E || usr==0x06E) SleepLater();
    else {
        SetColor(ERROR_MSG);
        printf("WTF ? Meet an eye doctor.\n");
        SetColor(DEFAULT_MSG);
        system("Pause");
        return 1;
    }

    // End
    SetColor(HEADING2);
    printf("\nPlease send feedback, lakmilaswarnajith@gmail.com\n");
    SetColor(DEFAULT_MSG);
    system("Pause");
    return 0;
}

void SleepNow(){
    // Get current time
    time_t rawtime = time(NULL);
    if (rawtime == -1){
        SetColor(ERROR_MSG);
        printf("\nError! Faild to initialize time.\n");
        SetColor(DEFAULT_MSG);
        system("Pause");
        exit(1);
    }

    // Output
    SetColor(HEADING2);
    printf("\nYou should wakeup at, \n");
    for (int i=1; i<=5; i++){
        char tbuf[BUF_LEN];
        time_t wt_raw = rawtime + (i*cy);
        struct tm *ptm = localtime(&wt_raw);

        if (ptm == NULL) {
            SetColor(ERROR_MSG);
            printf("\nError! Faild to initialize localtime.\n");
            SetColor(DEFAULT_MSG);
        system("Pause");
            exit(1);
        }

        SetColor(OUTPUT_MSG);
        strftime(tbuf, BUF_LEN, "%d/%b - %H:%M", ptm);
        printf("Cycle #%d : %s\n",i,tbuf);
    }
}
void SleepLater(){
    struct tm tm;
    char usd[0x00F];
    int d, h, m;

    // Get wake-up time
    SetColor(DEFAULT_MSG);
    printf("When you want to wakeup (DD HH:MM) :");
    scanf("%d %d:%d",&d, &h, &m);

    // Convert to UNiX time
    struct tm xmas = { 0, m, h, d, 01, 116};
    time_t rawtime = mktime(&xmas);

    if (rawtime == -1) {
        SetColor(ERROR_MSG);
        printf("Error ! Failed to initialize time\n");
        SetColor(DEFAULT_MSG);
        system("Pause");
        exit(1);
    }

    // Outputs
    SetColor(HEADING2);
    printf("\nYou should sleep at, \n");
    for (int i=1; i<=5; i++){
        char tbuf[BUF_LEN];
        time_t wt_raw = rawtime - (i*cy);
        struct tm *ptm = localtime(&wt_raw);

        if (ptm == NULL) {
            SetColor(ERROR_MSG);
            printf("\nError! Faild to initialize localtime.\n");
            SetColor(DEFAULT_MSG);
            system("Pause");
            exit(1);
        }

        SetColor(OUTPUT_MSG);
        strftime(tbuf, BUF_LEN, "%d/%b - %H:%M", ptm);
        printf("Cycle #%d : %s\n",i,tbuf);
    }

}

void SetColor(int color){
    fflush(stdout);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color | FOREGROUND_INTENSITY);
}
