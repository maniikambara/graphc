#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Memeriksa apakah sebuah graf terhubung atau tidak, menggunakan algoritma penelusuran graf secara mendalam (Depth-First Search).
bool isConnected(int a[][10], int n) {
    bool visit[10];
    int stack[10];
    int top = -1;
    for (int i = 0; i < n; i++) {
        visit[i] = false;
    }
    visit[0] = true;
    stack[++top] = 0;
    while (top != -1) {
        int curr = stack[top--];
        for (int i = 0; i < n; i++) {
            if (a[curr][i] && !visit[i]) {
                visit[i] = true;
                stack[++top] = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!visit[i])
            return false;
    }
    return true;
}

// Program Utama
int main() {
    int a[10][10] = {{0}};
    int d[10][2] = {{0}};
    int n;
    int T[10] = {0};
    int w[10] = {0};
    system("cls");
    printf("+--------------------------------------------+\n\n");
    printf("\t\tPROGRAM GRAPH\n\n");
    printf("+--------------------------------------------+\n\n");
    printf("\tMasukan Jumlah Vertex = ");
    scanf("%d", &n);
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printf("Jika vertex ke %d dan vertex ke %d terhubung, ketik 1 dan 0 jika tidak : ", i + 1, j + 1);
                scanf("%d", &a[i][j]);
                if (a[i][j] == 1) {
                    d[i][1]++; // Menghitung derajat vertex
                }
            }
            else {
                a[i][j] = 0;
            }
        }
    }
    printf("\n\nMatriks Ketetanggan\n\n");
    for (int i = 0; i < n; i++) {
        printf("|");
        for (int j = 0; j < n; j++) {
            printf(" %d |", a[i][j]);
        }
        printf("\n");
    }

    // Menampilkan derajat vertex
    printf("\nJumlah Derajat Setiap Vertex\n");
    for (int i = 0; i < n; i++) {
        d[i][0] = i; // Inisialisasi urutan derajat vertex
        printf("Derajat vertex ke %d adalah %d\n", i + 1, d[i][1]);
    }

    // Metode Bubble Sort untuk mengurutkan derajat vertex dari yang terbesar ke terkecil
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (d[i][1] < d[j][1]) {
                int temp = d[i][1];
                d[i][1] = d[j][1];
                d[j][1] = temp;
                temp = d[i][0];
                d[i][0] = d[j][0];
                d[j][0] = temp;
            }
        }
    }
    printf("\nHasil Bubble Sort Derajat Setiap Vertex\n");
    for (int i = 0; i < n; i++) {
        printf("Derajat vertex ke %d adalah %d\n", d[i][0] + 1, d[i][1]);
    }

    // Cetak graf terhubung atau tidak
    if (isConnected(a, n)) {
        printf("\nGraph Terhubung\n");
    } else {
        printf("\nGraph Tidak Terhubung\n");
    }

    // Algoritma Pewarnaan Vertex
    int warna = 1;
    w[d[0][0]] = warna;
    int total = 1;
    for (int i = 1; i < n; i++) { // mulai dari indeks 1 karena vertex pertama sudah diwarnai
        T[i] = a[d[i][0]][0]; // Mengambil tetangga vertex pertama
    }
    while (total < n) {
        for (int i = 1; i < n; i++) { // mulai dari indeks 1 karena vertex pertama sudah diwarnai
            if (w[d[i][0]] == 0 && T[d[i][0]] == 0) {
                bool available = true;
                for (int j = 0; j < n; j++) {
                    if (a[d[i][0]][j] && w[j] == warna) {
                        available = false;
                        break;
                    }
                }
                if (available) {
                    w[d[i][0]] = warna;
                    total++;
                    for (int j = 1; j < n; j++) { // mulai dari indeks 1 karena vertex pertama sudah diwarnai
                        if (T[j] == 0) {
                            T[j] += a[d[i][0]][j];
                        }
                    }
                }
            }
        }
        warna++;
        for (int j = 1; j < n; j++) { // mulai dari indeks 1 karena vertex pertama sudah diwarnai
            T[j] = 0;
        }
    }
    printf("\nWarna Setiap Vertex\n");
    for (int i = 0; i < n; i++) {
        printf("Warna Vertex ke-%d : %d\n", i + 1, w[i]);
    }

    return 0;
}