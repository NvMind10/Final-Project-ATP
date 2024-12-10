#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[100];
    char singer[100];
    struct Song *next;
} Song;

typedef struct Playlist {
    char name[100];
    Song *head;
    struct Playlist *next;
} Playlist;

Playlist *playlists = NULL;

// Fungsi untuk membuat playlist baru
Playlist* createPlaylist(const char *name) {
    Playlist *newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    strcpy(newPlaylist->name, name);
    newPlaylist->head = NULL;
    newPlaylist->next = NULL;
    return newPlaylist;
}

// Tambahkan playlist ke daftar playlist
void addPlaylist(const char *name) {
    Playlist *newPlaylist = createPlaylist(name);
    if (playlists == NULL) {
        playlists = newPlaylist;
    } else {
        Playlist *temp = playlists;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPlaylist;
    }
    printf("Playlist '%s' berhasil dibuat!\n", name);
}

// Cari playlist berdasarkan nama
Playlist* findPlaylist(const char *name) {
    Playlist *temp = playlists;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Tambahkan lagu ke playlist
void addSongToPlaylist(const char *playlistName, const char *title, const char *singer) {
    Playlist *playlist = findPlaylist(playlistName);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", playlistName);
        return;
    }

    Song *newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->singer, singer);
    newSong->next = NULL;

    if (playlist->head == NULL) {
        playlist->head = newSong;
    } else {
        Song *temp = playlist->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Lagu '%s' oleh '%s' berhasil ditambahkan ke playlist '%s'.\n", title, singer, playlistName);
}

// Hapus lagu dari playlist
void removeSongFromPlaylist(const char *playlistName, const char *title) {
    Playlist *playlist = findPlaylist(playlistName);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", playlistName);
        return;
    }

    Song *temp = playlist->head, *prev = NULL;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Lagu '%s' tidak ditemukan di playlist '%s'.\n", title, playlistName);
        return;
    }

    if (prev == NULL) {
        playlist->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Lagu '%s' berhasil dihapus dari playlist '%s'.\n", title, playlistName);
}

// Tampilkan semua lagu di playlist
void displayPlaylist(const char *playlistName) {
    Playlist *playlist = findPlaylist(playlistName);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", playlistName);
        return;
    }

    printf("Playlist: %s\n", playlist->name);
    if (playlist->head == NULL) {
        printf("Playlist kosong.\n");
        return;
    }

    Song *temp = playlist->head;
    while (temp != NULL) {
        printf("- %s oleh %s\n", temp->title, temp->singer);
        temp = temp->next;
    }
}

// Simpan playlist ke file
void savePlaylistToFile(const char *playlistName, const char *filename) {
    Playlist *playlist = findPlaylist(playlistName);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", playlistName);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    Song *temp = playlist->head;
    while (temp != NULL) {
        fprintf(file, "%s,%s\n", temp->title, temp->singer);
        temp = temp->next;
    }

    fclose(file);
    printf("Playlist '%s' berhasil disimpan di file '%s'.\n", playlistName, filename);
}

// Sorting lagu dalam playlist
void sortPlaylist(const char *playlistName, int bySinger) {
    Playlist *playlist = findPlaylist(playlistName);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", playlistName);
        return;
    }

    if (playlist->head == NULL || playlist->head->next == NULL) return;

    for (Song *i = playlist->head; i != NULL; i = i->next) {
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
    printf("Playlist '%s' berhasil disortir.\n", playlistName);
}

// Menu utama
void menu() {
    int choice;
    char playlistName[100], title[100], singer[100], filename[100];

    do {
        printf("\nMenu:\n");
        printf("1. Tambahkan Playlist Baru\n");
        printf("2. Tambahkan Lagu ke Playlist\n");
        printf("3. Hapus Lagu dari Playlist\n");
        printf("4. Tampilkan Lagu dalam Playlist\n");
        printf("5. Simpan Playlist ke File\n");
        printf("6. Sortir Lagu dalam Playlist\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan buffer input

        switch (choice) {
            case 1:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                addPlaylist(playlistName);
                break;
            case 2:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                printf("Masukkan judul lagu: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                printf("Masukkan nama penyanyi: ");
                fgets(singer, sizeof(singer), stdin);
                singer[strcspn(singer, "\n")] = '\0';
                addSongToPlaylist(playlistName, title, singer);
                break;
            case 3:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                printf("Masukkan judul lagu yang ingin dihapus: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                removeSongFromPlaylist(playlistName, title);
                break;
            case 4:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                displayPlaylist(playlistName);
                break;
            case 5:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                printf("Masukkan nama file untuk menyimpan: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                savePlaylistToFile(playlistName, filename);
                break;
            case 6:
                printf("Masukkan nama playlist: ");
                fgets(playlistName, sizeof(playlistName), stdin);
                playlistName[strcspn(playlistName, "\n")] = '\0';
                printf("Sortir berdasarkan (1: Judul, 2: Penyanyi): ");
                int sortChoice;
                scanf("%d", &sortChoice);
                sortPlaylist(playlistName, sortChoice == 2);
                break;
            case 7:
                printf("Keluar dari aplikasi.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}