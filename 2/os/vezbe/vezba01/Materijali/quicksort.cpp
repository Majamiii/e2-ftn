#include <iostream>
using namespace std;

void qsort_(int a[], int l, int d);
int izaberi_pivota(int a[], int l, int d);
void zameni(int a[], int gde, int koga);
int particionisanje(int a[], int l, int d);
void ispisi(int a[], int l, int d);

int main(){

    int a[] = {7,6,5,4,9,8,1,2,0,3};

    int d = sizeof(a) / sizeof(a[0]) - 1;

    qsort_(a, 0, d);
    ispisi(a,0,d);

    return 0;
}


void qsort_(int a[], int l, int d){     // sortiraj deo niza od l do d

    if(l<d){
        int p = izaberi_pivota(a, l, d);
        cout<<endl<<"Pivot je "<<a[p]<<" i na mestu "<<p+1<<endl;
        zameni(a,l,p);
        p = particionisanje(a,l,d);
        qsort_(a,l,p);
        qsort_(a,p+1,d);
    }

}

void ispisi(int a[], int l, int d){
    for(int i=l;i<d+1;i++){
        cout<<endl<<a[i];
    }
    cout<<endl;
}

int izaberi_pivota(int a[], int l, int d){

    if(d-l>2){
        int x = (a[l]+a[l+1]+a[d])/3;

        for(int i=l;i<d;i++){
            if(a[i]==x){
                return i;
            }
        }
    }
    
    return l;

}

void zameni(int a[], int gde, int koga){
    int temp = a[gde];
    a[gde] = a[koga];
    a[koga] = temp;
}

int particionisanje(int a[], int l, int d){
    int p=l;
    int j;
    for(j=l+1;j<d+1;j++){
        if (a[j]<a[l]){         // pivot je na mestu l
            zameni(a, ++p, j);
        }
    }
    zameni(a,p,l);
    return p;
}


