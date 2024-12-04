#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
typedef struct Song {
    char title[100];
    char singer[100];
    struct Song *next;
} Song;

// Fungsi prototypes
void addSong(Song **head, char *title, char *singer);
void displayPlaylist(Song *head);
void login(char *username);

// Fungsi Main
int main() {
    Song *playlist = NULL;
    int pilihan;
    char title[100], singer[100];
    char username[100];

    // pemanggilan fungsi login
    login(username);

    while (1) {
        printf("\nMENU\n");
        printf("1. Tambahkan Lagu\n");
        printf("2. Tampilkan Playlist\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        getchar(); // To consume newline character

        switch (pilihan) {
            case 1:
                printf("Masukkan judul: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
                printf("Nama Penyanyi: ");
                fgets(singer, 100, stdin);
                singer[strcspn(singer, "\n")] = '\0'; // Remove trailing newline
                addSong(&playlist, title, singer);
                break;


            case 2:
                displayPlaylist(playlist); //pemanggilan fungsi display playlist
                break;

            case 3:
                printf("\nSelamat tinggal, %s!\n", username);
                return 0;

            default:
                printf("\nPilihannya ga ada!!!\n");
        }
    }

    return 0;
}

// Fungsi login
void login(char *username) {
    printf("Selamat datang di Melodi!\n");
    printf("Masukkan Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove trailing newline
    printf("\nHai, %s! Mau dengerin apa hari ini?\n", username);
}

// Fungsi untuk menambahkan lagu
void addSong(Song **head, char *title, char *singer) {
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->singer, singer);
    newSong->next = *head;
    *head = newSong;
    printf("\nLagu berhasil ditambahkan\n");
}

// Fungsi untuk menampilkan playlist
void displayPlaylist(Song *head) {
    if (!head) {
        printf("\nPlaylistmu kosong nih :(\n");
        return;
    }
    Song *current = head;
    printf("\nPlaylist:\n");
    while (current) {
        printf("Judul: %s, Penyanyi: %s\n", current->title, current->singer);
        current = current->next;
    }
}