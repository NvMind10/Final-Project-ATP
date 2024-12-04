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

//Tampilkan playlist
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist kosong.\n");
        return;
    }
    Song *temp = head;
    printf("Daftar Lagu:\n");
    while (temp != NULL) {
        printf("- %s oleh %s\n", temp->title, temp->singer);
        temp = temp->next;
    }
}

// Simpan playlist ke file
void savePlaylistToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    Song *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%s\n", temp->title, temp->singer);
        temp = temp->next;
    }

    fclose(file);
    printf("Playlist berhasil disimpan di file '%s'.\n", filename);
}

// Sorting berdasarkan judul atau penyanyi
void sortPlaylist(int bySinger) {
    if (head == NULL || head->next == NULL) return;

    for (Song *i = head; i != NULL; i = i->next) {
        for (Song *j = i->next; j != NULL; j = j->next) {
            if ((bySinger && strcmp(i->singer, j->singer) > 0) ||
                (!bySinger && strcmp(i->title, j->title) > 0)) {
                // Tukar data lagu
                char tempTitle[100], tempSinger[100];
                strcpy(tempTitle, i->title);
                strcpy(tempSinger, i->singer);
                strcpy(i->title, j->title);
                strcpy(i->singer, j->singer);
                strcpy(j->title, tempTitle);
                strcpy(j->singer, tempSinger);
            }
        }
    }
    printf("Playlist berhasil disortir.\n");
}

// Menu utama
void menu() {
    int choice;
    char title[100], singer[100], filename[100];

    do {
        printf("\nMenu:\n");
        printf("1. Tambahkan Lagu\n");
        printf("2. Hapus Lagu\n");
        printf("3. Tampilkan Playlist\n");
        printf("4. Simpan Playlist ke File\n");
        printf("5. Sortir Playlist (1: Judul, 2: Penyanyi)\n");
        printf("6. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan buffer input

        switch (choice) {
            case 1:
                printf("Masukkan judul lagu: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Hilangkan newline
                printf("Masukkan nama penyanyi: ");
                fgets(singer, sizeof(singer), stdin);
                singer[strcspn(singer, "\n")] = '\0';
                addSong(title, singer);
                break;
            case 2:
                printf("Masukkan judul lagu yang ingin dihapus: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                removeSong(title);
                break;
            case 3:
                displayPlaylist();
                break;
            case 4:
                printf("Masukkan nama file untuk menyimpan: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                savePlaylistToFile(filename);
                break;
            case 5:
                printf("Sortir berdasarkan (1: Judul, 2: Penyanyi): ");
                int sortChoice;
                scanf("%d", &sortChoice);
                sortPlaylist(sortChoice == 2);
                break;
            case 6:
                printf("Keluar dari aplikasi.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}