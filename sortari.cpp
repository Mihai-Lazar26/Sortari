#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

ifstream fin("teste.txt");
ofstream fout("timpi.txt");

void bubblesort(int *ar, int n)
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(ar[i]>ar[j]) swap(ar[i],ar[j]);
}

void countsort(int *ar, int n)
{
    int mini, maxi;
    mini=maxi=ar[0];
    for(int i=1; i<n; i++)
    {
        if(ar[i]>maxi) maxi=ar[i];
        if(ar[i]<mini) mini=ar[i];
    }
    int m;
    m=maxi-mini;
    int *ap;
    ap = new int[m+1];
    for(int i=0; i<=m; i++)
        ap[i] = 0;
    for(int i=0; i<n; i++)
        ap[ar[i]-mini]++;

    for(int i=1; i<=m; i++)
        ap[i]=ap[i]+ap[i-1];

    int *ari;
    ari = new int[n];
    for(int i=0; i<n; i++)
    {
        ari[ap[ar[i]-mini]-1] = ar[i];
        ap[ar[i]-mini]--;
    }

    for(int i=0; i<n; i++)
        ar[i]=ari[i];

    delete[] ap;
    delete[] ari;
}

void radixsort(int *ar, int n)
{
    int maxi=ar[0], k=0, d, cifre[2], *aux;
    aux=new int[n];
    for(int i=1; i<n; i++)
        if(ar[i]>maxi) maxi=ar[i];
    d=2;
    while(maxi)
    {
        maxi/=2;
        k++;
    }
    for(int i=0; i<k; i++)
    {
        cifre[0]=cifre[1]=0;
        for(int j=0; j<n; j++)
            aux[j]=0;

        for(int j=0; j<n; j++)
            cifre[(ar[j]>>i)%2]++;

        cifre[0]--;
        cifre[1] += cifre[0];

        for(int j=n-1; j>=0; j--)
        {
            aux[cifre[(ar[j]>>i)%2]]=ar[j];
            cifre[(ar[j]>>i)%2]--;
        }

        for(int j=0; j<n; j++)
            ar[j]=aux[j];
    }
    delete[] aux;
}

void interclasare(int *ar, int st, int mi, int dr)
{
    int *aux, it=0;
    aux= new int[dr-st+1];
    int is=st, fs=mi, id=mi+1, fd=dr, j=0;
    while(is<=fs && id<=fd)
    {
        if(ar[is]<=ar[id])
            aux[it++]=ar[is++];
        else
            aux[it++]=ar[id++];
    }

    for(int i=is; i<=fs; i++)
        aux[it++]=ar[i];
    for(int i=id; i<=fd; i++)
        aux[it++]=ar[i];

    for(int i=st; i<=dr; i++)
    {
        ar[i]=aux[j];
        j++;
    }
    delete[] aux;
}


void mergesort(int *ar, int st, int dr)
{
    int mi=(st+dr)/2;
    if(st<dr)
    {
        mergesort(ar,st,mi);
        mergesort(ar,mi+1,dr);
        interclasare(ar,st,mi,dr);
    }
}

int partitie(int *ar, int low, int high)
{
    int pivot=(rand()%(high-low+1))+low;
    swap(ar[pivot], ar[high]);
    int i=low-1;
    for(int j=low; j<high; j++)
        if(ar[j]<ar[high])
        {
            i++;
            swap(ar[i],ar[j]);
        }
    swap(ar[high],ar[i+1]);
    return i+1;
}


void quicksort(int *ar, int low, int high)
{
    if(low<high)
    {
        int pi = partitie(ar,low,high);
        quicksort(ar,low,pi-1);
        quicksort(ar,pi+1,high);
    }
}


bool tester(int *ar, int n)
{
    for(int i=1; i<n; i++)
        if(ar[i]<ar[i-1]) return false;

    return true;
}



int main()
{
    srand(time(0));
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    int T;
    fin>>T;
    for(int i=1; i<=T; i++)
    {
        int n, maxi;
        fin>>n>>maxi;
        int *ar, *copie;
        ar= new int[n];
        copie = new int[n];


        for(int i=0; i<n; i++)
        {
            ar[i]=rand()%(maxi+1);
            copie[i]=ar[i];
        }


        if(n<=100000)
        {

            start = high_resolution_clock::now();

            bubblesort(copie, n);

            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop - start);
            cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Bubble_sort dureaza: "<<duration.count()<<" nanosecunde ";
            if(tester(copie, n))
                cout<<"succes\n";
            else cout<<"esec\n";
            fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Bubble_sort dureaza: "<<duration.count()<<" nanosecunde ";
            if(tester(copie, n))
                fout<<"succes\n";
            else fout<<"esec\n";
        }
        else
        {
            cout<<"Bubble sort nu poate sorta\n";
            fout<<"Bubble sort nu poate sorta\n";
        }

        for(int i=0; i<n; i++)
            copie[i]=ar[i];

        start = high_resolution_clock::now();

        countsort(copie,n);

        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Count_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            cout<<"succes\n";
        else cout<<"esec\n";
        fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Count_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            fout<<"succes\n";
        else fout<<"esec\n";

        for(int i=0; i<n; i++)
            copie[i]=ar[i];

        start = high_resolution_clock::now();

        radixsort(copie,n);

        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Radix_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            cout<<"succes\n";
        else cout<<"esec\n";
        fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Radix_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            fout<<"succes\n";
        else fout<<"esec\n";

        for(int i=0; i<n; i++)
            copie[i]=ar[i];

        start = high_resolution_clock::now();

        mergesort(copie,0,n-1);

        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Merge_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            cout<<"succes\n";
        else cout<<"esec\n";
        fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Merge_sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            fout<<"succes\n";
        else fout<<"esec\n";


        if(n<131072)
        {
            for(int i=0; i<n; i++)
                copie[i]=ar[i];

            start = high_resolution_clock::now();

            quicksort(copie,0,n-1);

            stop = high_resolution_clock::now();
            duration = duration_cast<nanoseconds>(stop - start);
            cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Quick_sort dureaza: "<<duration.count()<<" nanosecunde ";
            if(tester(copie, n))
                cout<<"succes\n";
            else cout<<"esec\n";
            fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" Quick_sort dureaza: "<<duration.count()<<" nanosecunde ";
            if(tester(copie, n))
                fout<<"succes\n";
            else fout<<"esec\n";
        }
        else
        {
            cout<<"Quick sort nu poate sorta\n";
            fout<<"Quick sort nu poate sorta\n";
        }

        for(int i=0; i<n; i++)
            copie[i]=ar[i];

        start = high_resolution_clock::now();

        sort(copie,copie+n);

        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        cout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" std::sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            cout<<"succes\n";
        else cout<<"esec\n";
        fout<<"Numar valori: "<<n<<" Maximul: "<<maxi<<" std::sort dureaza: "<<duration.count()<<" nanosecunde ";
        if(tester(copie, n))
            fout<<"succes\n";
        else fout<<"esec\n";


        delete[] ar;
        delete[] copie;
    }

    return 0;
}
