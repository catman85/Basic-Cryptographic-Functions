#include <stdio.h>

// C συνάρτηση για την ανεπτυγμένη μορφή του
// Αλγορίθμου του Ευκλείδη
int efkl2(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; //για την αναδρομική
    int gcd = efkl2(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

//οδηγίες χρήσης
void usage(void){
        printf("Type 2 integers with a space between them and hit Enter\n");
}

int main(int argc, char *argv[])
{
    int x, y, a, b;
     //δεχόμαστε input και σαν arguments απο το command line
     if(argc!=3){
                while(scanf("%d%d",&a, &b)!=2){
                        usage(); 	//οδηγίες χρήσης
                        while(getchar()!='\n');
                }
     }else{
                a=atoi(argv[1]);
                b=atoi(argv[2]);
     }
    //επειδή μια συνάρτηση δέν μπορεί να επιστρέφει πολλές τιμές
    //της δίνουμε σάν ορίσματα τις διευθύνσεις των x,y
    int g = efkl2(a, b, &x, &y);
    printf("gcd(%d, %d) = %d = %d*%d + %d*%d\n",
           a, b, g, x, a, y, b);
    return 0;
}
