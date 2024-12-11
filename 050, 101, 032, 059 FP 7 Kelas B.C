#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Lagu
typedef struct Song {
    char Judul[100];
    char Penyanyi[100];
    struct Song *next;
} Song;

// Struct Playlist
typedef struct Playlist {
    char name[100];
    Song *head;
    struct Playlist *next;
} Playlist;

Playlist *playlists = NULL;

// Prototype Fungsi
void login(char *Username);
Playlist* BuatPlaylist(const char *name);
void TambahkanPlaylist(const char *name);
Playlist* CariPlaylist(const char *name);
void TambahLagu(const char *NamaPlaylist, const char *Judul, const char *Penyanyi);
void HapusLagu(const char *NamaPlaylist, const char *Judul);
void TampilkanPlaylist(const char *NamaPlaylist);
void SavePlaylistkeFile(const char *NamaPlaylist, const char *filename);
void UrutkanPlaylist(const char *NamaPlaylist, int bySinger);
void menu();

// Fungsi LogIn
void login(char *Username) {
    printf("Selamat datang di Melodi!\n");
    printf("Masukkan Username: ");
    fgets(Username, 100, stdin);
    Username[strcspn(Username, "\n")] = '\0'; // Remove trailing newline
    printf("\nHai, %s! Mau dengerin apa hari ini?\n", Username);
}

// Fungsi membuat playlist
Playlist* BuatPlaylist(const char *name) {
    Playlist *newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    strcpy(newPlaylist->name, name);
    newPlaylist->head = NULL;
    newPlaylist->next = NULL;
    return newPlaylist;
}

// Menambahkan playlist
void TambahkanPlaylist(const char *name) {
    Playlist *newPlaylist = BuatPlaylist(name);
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

// Menemukan playlist
Playlist* CariPlaylist(const char *name) {
    Playlist *temp = playlists;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Tambah lagu ke playlist
void TambahLagu(const char *NamaPlaylist, const char *Judul, const char *Penyanyi) {
    Playlist *playlist = CariPlaylist(NamaPlaylist);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", NamaPlaylist);
        return;
    }

    Song *newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->Judul, Judul);
    strcpy(newSong->Penyanyi, Penyanyi);
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
    printf("Lagu '%s' oleh '%s' berhasil ditambahkan ke playlist '%s'.\n", Judul, Penyanyi, NamaPlaylist);
}

// Hapus lagu dari playlist
void HapusLagu(const char *NamaPlaylist, const char *Judul) {
    Playlist *playlist = CariPlaylist(NamaPlaylist);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", NamaPlaylist);
        return;
    }

    Song *temp = playlist->head, *prev = NULL;
    while (temp != NULL && strcmp(temp->Judul, Judul) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Lagu '%s' tidak ditemukan di playlist '%s'.\n", Judul, NamaPlaylist);
        return;
    }

    if (prev == NULL) {
        playlist->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Lagu '%s' berhasil dihapus dari playlist '%s'.\n", Judul, NamaPlaylist);
}

// Display lagu di playlist
void TampilkanPlaylist(const char *NamaPlaylist) {
    Playlist *playlist = CariPlaylist(NamaPlaylist);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", NamaPlaylist);
        return;
    }

    printf("Playlist: %s\n", playlist->name);
    if (playlist->head == NULL) {
        printf("Playlist kosong.\n");
        return;
    }

    Song *temp = playlist->head;
    while (temp != NULL) {
        printf("- %s oleh %s\n", temp->Judul, temp->Penyanyi);
        temp = temp->next;
    }
}

// Simpan playlist
void SavePlaylistkeFile(const char *NamaPlaylist, const char *filename) {
    Playlist *playlist = CariPlaylist(NamaPlaylist);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", NamaPlaylist);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    Song *temp = playlist->head;
    while (temp != NULL) {
        fprintf(file, "%s,%s\n", temp->Judul, temp->Penyanyi);
        temp = temp->next;
    }

    fclose(file);
    printf("Playlist '%s' berhasil disimpan di file '%s'.\n", NamaPlaylist, filename);
}

// Urutkan lagu
void UrutkanPlaylist(const char *NamaPlaylist, int bySinger) {
    Playlist *playlist = CariPlaylist(NamaPlaylist);
    if (playlist == NULL) {
        printf("Playlist '%s' tidak ditemukan.\n", NamaPlaylist);
        return;
    }

    if (playlist->head == NULL || playlist->head->next == NULL) return;

    for (Song *i = playlist->head; i != NULL; i = i->next) {
        for (Song *j = i->next; j != NULL; j = j->next) {
            if ((bySinger && strcmp(i->Penyanyi, j->Penyanyi) > 0) ||
                (!bySinger && strcmp(i->Judul, j->Judul) > 0)) {
                // Swap data lagu
                char tempTitle[100], tempSinger[100];
                strcpy(tempTitle, i->Judul);
                strcpy(tempSinger, i->Penyanyi);
                strcpy(i->Judul, j->Judul);
                strcpy(i->Penyanyi, j->Penyanyi);
                strcpy(j->Judul, tempTitle);
                strcpy(j->Penyanyi, tempSinger);
            }
        }
    }
    printf("Playlist '%s' berhasil disortir.\n", NamaPlaylist);
}

void menu() {
    int choice;
    char Username[100];
    char NamaPlaylist[100], Judul[100], Penyanyi[100], filename[100];

    login(Username);

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
        getchar();

        switch (choice) {
            case 1:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                TambahkanPlaylist(NamaPlaylist);
                break;
            case 2:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                printf("Masukkan judul lagu: ");
                fgets(Judul, sizeof(Judul), stdin);
                Judul[strcspn(Judul, "\n")] = '\0';
                printf("Masukkan nama penyanyi: ");
                fgets(Penyanyi, sizeof(Penyanyi), stdin);
                Penyanyi[strcspn(Penyanyi, "\n")] = '\0';
                TambahLagu(NamaPlaylist, Judul, Penyanyi);
                break;
            case 3:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                printf("Masukkan judul lagu yang ingin dihapus: ");
                fgets(Judul, sizeof(Judul), stdin);
                Judul[strcspn(Judul, "\n")] = '\0';
                HapusLagu(NamaPlaylist, Judul);
                break;
            case 4:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                TampilkanPlaylist(NamaPlaylist);
                break;
            case 5:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                printf("Masukkan nama file untuk menyimpan: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                SavePlaylistkeFile(NamaPlaylist, filename);
                break;
            case 6:
                printf("Masukkan nama playlist: ");
                fgets(NamaPlaylist, sizeof(NamaPlaylist), stdin);
                NamaPlaylist[strcspn(NamaPlaylist, "\n")] = '\0';
                printf("Sortir berdasarkan (1: Judul, 2: Penyanyi): ");
                int sortChoice;
                scanf("%d", &sortChoice);
                UrutkanPlaylist(NamaPlaylist, sortChoice == 2);
                break;
            case 7:
                printf("\nSelamat tinggal, %s!\n", Username);
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