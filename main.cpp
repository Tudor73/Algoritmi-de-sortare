#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <cmath>
using namespace std;

void bubbleSort(int v[], int n)
{
    for(int i = 0;i< n;i++){
        for(int j = 0;j< n-i;j++){
            if (v[j] > v[j+1])
                swap(v[j], v[j+1]);
        }
    }
}

void countSort(int v[100], int n)
{
    int maxim = 0;
    for(int i = 0;i< n;i++){
        if(v[i] > maxim)
            maxim = v[i];
    }
    vector<int>aparitii(maxim+1, 0);
    vector<int>output(n,0);
    for(int i= 0; i< n;i++){
        aparitii[v[i]]++;
    }

    for(int i =1;i<= maxim; i++){
        aparitii[i] += aparitii[i-1];
    }
    for(int i = 0;i< n; i++){
        output[aparitii[v[i]]-1] = v[i];
        aparitii[v[i]]--;
    }
    for(int i = 0;i< n; i++){
        v[i] = output[i];
    }

}
void countSort2(int v[], int n, int exp)
{
    int* output = new int[n];
    int i;
    int aparitii[10] = {0};
    for(i = 0; i< n; i++){
        aparitii[(v[i]/exp)%10]++;
    }
    for(i = 1; i< 10; i++)
        aparitii[i] += aparitii[i-1];
    for(i = n-1; i>=0; i--){
        output[aparitii[(v[i]/exp)%10]-1] = v[i];
        aparitii[(v[i]/exp)%10]--;
    }
    for(i = 0; i< n; i++)
        v[i] = output[i];
    delete[] output;

}

void radixSort(int v[], int n)
{
    int i, maxim = 0;
    for(i = 0; i< n; i++){
        if(v[i] > maxim)
            maxim = v[i];
    }
    int exp = 1;
    while(maxim / exp != 0){
        countSort2(v,n,exp);
        exp *= 10;
    }
}

void interclasare(int v[], int st, int mij, int dr)
{

    int n1 = mij - st +1;
    int n2 = dr - mij ;
    int* L = new int[n1];
    int* R = new int[n2];
    int k = st;
    for (int i = 0; i< n1 ; i++)
        L[i] = v[st+i];
    for(int i = 0; i< n2 ; i++)
        R[i] = v[mij + 1 + i ];

    int i = 0, j = 0;
    while( i < n1 && j < n2){
        if(L[i]<= R[j]){
            v[k] = L[i];
            i++;
        }
        else{
            v[k] = R[j];
            j++;
        }

        k++;
    }
    while(i < n1){
        v[k] = L[i];
        i++;
        k++;
    }
    while(j< n2){
        v[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;

}
void mergeSort(int v[], int st, int dr )
{
    if(st < dr){
        int mij = st + (dr-st)/2;
        mergeSort(v, st, mij);
        mergeSort(v, mij+1, dr);
        interclasare(v,st,mij,dr);
    }
    return;
}

int partitie(int v[], int st, int dr)
{
    int i = st, j = dr, ok = 1;
    while(i < j ){
        if(v[i] > v[j]){
            swap(v[i], v[j]);
            ok = !ok;
        }
    if( ok == 1)
        i++;
    else
        j--;
    }
    return i;

}

void quickSort(int v[], int st, int dr)
{
        if(st < dr){
            int p = partitie(v,st,dr);
            quickSort(v,st,p-1);
            quickSort(v, p+1, dr);
        }
        else return;
}
bool test_sort(int v[], int n)
{   for(int i = 0; i< n-1; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}

void copy_array(int v[], int a[], int n)
{
    for(int i = 0; i< n ; i++)
        a[i] = v[i];
}

void generate_random(int v[], int n, int Nmax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(0, Nmax);
    for (int i=0; i<n; i++){
        v[i] = dis(gen);
    }
}

void generate_constant(int v[], int n, int Nmax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(0, Nmax);
    int x = dis(gen);
    for(int i = 0; i< n;i++){
        v[i] = x;
    }
}

void generate_almost_sorted(int v[], int n, int Nmax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis(0, Nmax);
    for (int i=0; i<n; i++){
        v[i] = dis(gen);
    }
    int m = n*90/100;
    sort(v,v+m);
}

int main()
{
    ifstream f("file.in");
    int T;
    f >> T;
    int a[T][2];
    for(int i = 1;i<= T; i++){
        int x,y ; f >> x>>y;
        a[i][1] = x;
        a[i][2] = y;
    }

    for(int i = 1; i<= T; i++){
        int N = a[i][1];
        int Nmax = a[i][2];
        int* v = new int[N];
        int* a = new int[N];
        int ok1 = 0;
        int ok2 = 0;
        int ok = 1;
        if( N > pow(10,9) || Nmax > pow(10,9))
            ok = 0;
        generate_random(v,N,Nmax);
        cout << "TEST " << i << endl;
        cout << "N = " << N << " NMax = "<< Nmax<<endl<<endl;

        auto start = chrono::system_clock::now();
        auto finish = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = finish-start;
        if (N > pow(10,5)){
                cout << "bubbleSort: NU POT SORTA"<<endl;
            }
        else{
            copy_array(v,a,N);
            start = chrono::system_clock::now();
            bubbleSort(a,N);
            finish = chrono::system_clock::now();
            elapsed_seconds = finish-start;
            cout << "bubbleSort: elapsed time = " << elapsed_seconds.count();
            if(test_sort(a,N) == true)
                cout << " CORECT " << endl;
            else cout << " INCORECT "<< endl;
        }

        cout << endl;
        if(ok == 0)
            cout << "countSort: NU POT SORTA"<<endl;
        else{
            copy_array(v,a,N);
            start = chrono::system_clock::now();
            countSort(a,N);
            finish = chrono::system_clock::now();
            elapsed_seconds = finish-start;
            cout << "countSort: elapsed time = " << elapsed_seconds.count();
            if(test_sort(a,N) == true)
                cout << " CORECT " << endl;
            else cout << " INCORECT "<< endl;
        }
        cout <<endl;
        if(ok == 0)
            cout << "radixSort: NU POT SORTA"<<endl;
        else{
            copy_array(v,a,N);
            start = chrono::system_clock::now();
            radixSort(a,N);
            finish = chrono::system_clock::now();
            elapsed_seconds = finish-start;
            cout << "radixSort: elapsed time = " << elapsed_seconds.count();
            if(test_sort(a,N) == true)
                cout << " CORECT " << endl;
            else cout << " INCORECT "<< endl;
            }
        cout << endl;

        if(ok == 0)
            cout << "mergeSort: NU POT SORTA"<<endl;
        else{
            copy_array(v,a,N);
            start = chrono::system_clock::now();
            mergeSort(a,0,N);
            finish = chrono::system_clock::now();
            elapsed_seconds = finish-start;
            cout << "mergeSort: elapsed time = " << elapsed_seconds.count();
            if(test_sort(a,N) == true)
                cout << " CORECT " << endl;
            else cout << " INCORECT "<< endl;
        }
        cout << endl;

        if((N > pow(10,6) && Nmax < 1000) || ok == 0 ){
            cout << "quickSort: NU POT SORTA"<<endl;
        }
        else{
            copy_array(v,a,N);
            start = chrono::system_clock::now();
            quickSort(a,0,N);
            finish = chrono::system_clock::now();
            elapsed_seconds = finish-start;
            cout << "quickSort: elapsed time = " << elapsed_seconds.count();
            if(test_sort(a,N) == true)
                cout << " CORECT " << endl;
            else cout << " INCORECT "<< endl;
        }
        cout << endl;
//
//        copy_array(v,a,N);
 //      start = chrono::system_clock::now();
 //       sort(a,a+N);
//         finish = chrono::system_clock::now();
//         elapsed_seconds = finish-start;
//         cout << "introSort: elapsed time = " << elapsed_seconds.count();
//         if(test_sort(a,N) == true)
//             cout << " CORECT " << endl;
//         else cout << " INCORECT "<< endl;
        delete[] v;
        delete[] a;
    }
    return 0;
}
