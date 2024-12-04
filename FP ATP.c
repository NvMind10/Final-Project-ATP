#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[100];
    char singer[100];
    struct Song *next;
} Song;

Song *head = NULL;

// Fungsi untuk membuat node baru
Song* createSong(const char *title, const char *singer) {
    Song *newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->singer, singer);
    newSong->next = NULL;
    return newSong;
}

// Tambahkan lagu ke playlist
void addSong(const char *title, const char *singer) {
    Song *newSong = createSong(title, singer);
    if (head == NULL) {
        head = newSong;
    } else {
        Song *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Lagu '%s' oleh '%s' berhasil ditambahkan!\n", title, singer);
}

// Hapus lagu berdasarkan judul
void removeSong(const char *title) {
    Song *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Lagu '%s' tidak ditemukan.\n", title);
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Lagu '%s' berhasil dihapus.\n", title);
}

//Tampilkan lagu dalam playlist