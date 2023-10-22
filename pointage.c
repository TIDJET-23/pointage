#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>

sqlite3* db;
FILE *exportFile = NULL;


void clearScreen() {
    system("clear");
}


void printMainMenu() {
    printf("\n========= Menu Principal =========\n");
    printf("1. pointage\n");
    printf("2. Liste pointages\n");
    printf("3. Quitter\n");
    printf("==================================\n");
    printf("#~ ");
}


void printPointageMenu() {
    printf("\n========= Menu Pointage =========\n");
    printf("1. Entrée\n");
    printf("2. Sortie Pause\n");
    printf("3. Entrée Pause\n");
    printf("4. Sortie\n");
    printf("5. Retour au menu principal\n");
    printf("=================================\n");
    printf("#~ ");
}


void printDisplayExportMenu() {
    printf("\n====== Menu Affichage/Exportation ======\n");
    printf("1. Afficher les points\n");
    printf("2. Exporter les points\n");
    printf("3. Retourner au Menu Principal\n");
    printf("========================================\n");

    printf("#~ ");
}



int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    static char lastDate[20] = "";  
    static int firstRow = 1;       
    if (firstRow || strcmp(lastDate, argv[0]) != 0) {
        if (!firstRow) {
            printf("\n------------------------------------------------------------------------------------------\n");
        }
        printf("| %s \t\t |", argv[0]);
        firstRow = 0;
        strcpy(lastDate, argv[0]);
    }
    if (strcmp(argv[1], "/") == 0) {
        printf(" # \t\t |");
    } else {
        printf(" %s \t |", argv[1]);
    }
    return 0;
}


void listPointages(int month, int year) {
    char sql[400];

    printf("==========================================================================================\n");
    
    switch (month) {
        case 1:
            printf("\t\t\t\t Janvier \t %d \n", year);
            break;
        case 2:
            printf("\t\t\t\t Février \t %d \n", year);
            break;
        case 3:
            printf("\t\t\t\t Mars \t %d \n", year);
            break;
        case 4:
            printf("\t\t\t\t Avril \t %d \n", year);
            break;
        case 5:
            printf("\t\t\t\t Mai \t %d \n", year);
            break;
        case 6:
            printf("\t\t\t\t Juin \t %d \n", year);
            break;
        case 7:
            printf("\t\t\t\t Juillet \t %d \n", year);
            break;
        case 8:
            printf("\t\t\t\t Août \t %d \n", year);
            break;
        case 9:
            printf("\t\t\t\t Septembre \t %d \n", year);
            break;
        case 10:
            printf("\t\t\t\t Octobre \t %d \n", year);
            break;
        case 11:
            printf("\t\t\t\t Novembre \t %d \n", year);
            break;
        case 12:
            printf("\t\t\t\t Décembre \t %d \n", year);
            break;
        default:
            printf("\t\t\t\t Mois inconnu \t %d \n", year);
            break;
    }
    
    printf("==========================================================================================\n");
    printf("==========================================================================================\n");

    printf("| date \t\t\t |  entrée \t |  sortie_pause |  entrée_pause |  sortie \t |\n");
    printf("==========================================================================================\n");
    snprintf(sql, sizeof(sql), "SELECT Date, Time FROM Pointages WHERE strftime('%%m', Date) = '%02d' AND strftime('%%Y', Date) = '%04d';", month, year);
    if (sqlite3_exec(db, sql, callback, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error\n");
    }
    printf("\n------------------------------------------------------------------------------------------\n");
    printf("\n");
}



int callbackFile(void *NotUsed, int argc, char **argv, char **azColName) {
    static char lastDate[20] = "";
    static int firstRow = 1; 
    if (exportFile == NULL) {
        exportFile = fopen("exported_data.txt", "w");
        if (exportFile == NULL) {
            fprintf(stderr, "Error opening export file\n");
            return 1;
        }
    }
    if (firstRow || strcmp(lastDate, argv[0]) != 0) {
        if (!firstRow) {
            fprintf(exportFile, "\n------------------------------------------------------------------------------------------\n");
        }
        fprintf(exportFile, "| %s \t\t |", argv[0]);
        firstRow = 0;
        strcpy(lastDate, argv[0]);
    }
    if (strcmp(argv[1], "/") == 0) { fprintf(exportFile, " # \t\t |");
    } else { 
        fprintf(exportFile, " %s \t |", argv[1]);
    }
    return 0;
}


void listPointagesFile(int month, int year) {
    char sql[400];
    exportFile = fopen("exported_data.txt", "w");
    if (exportFile == NULL) {
        fprintf(stderr, "Error opening export file\n");
        return;
    }

    fprintf(exportFile, "==========================================================================================\n");
    
    switch (month) {
        case 1:
            fprintf(exportFile, "\t\t\t\t Janvier \t %d \n", year);
            break;
        case 2:
            fprintf(exportFile, "\t\t\t\t Février \t %d \n", year);
            break;
        case 3:
            fprintf(exportFile, "\t\t\t\t Mars \t %d \n", year);
            break;
        case 4:
            fprintf(exportFile, "\t\t\t\t Avril \t %d \n", year);
            break;
        case 5:
            fprintf(exportFile, "\t\t\t\t Mai \t %d \n", year);
            break;
        case 6:
            fprintf(exportFile, "\t\t\t\t Juin \t %d \n", year);
            break;
        case 7:
            fprintf(exportFile, "\t\t\t\t Juillet \t %d \n", year);
            break;
        case 8:
            fprintf(exportFile, "\t\t\t\t Août \t %d \n", year);
            break;
        case 9:
            fprintf(exportFile, "\t\t\t\t Septembre \t %d \n", year);
            break;
        case 10:
            fprintf(exportFile, "\t\t\t\t Octobre \t %d \n", year);
            break;
        case 11:
            fprintf(exportFile, "\t\t\t\t Novembre \t %d \n", year);
            break;
        case 12:
            fprintf(exportFile, "\t\t\t\t Décembre \t %d \n", year);
            break;
        default:
            fprintf(exportFile, "\t\t\t\t Mois inconnu \t %d \n", year);
            break;
    }
    
    fprintf(exportFile, "==========================================================================================\n");

    fprintf(exportFile, "==========================================================================================\n");
    fprintf(exportFile, "| date \t\t\t |  entrée \t |  sortie_pause |  entrée_pause |  sortie \t |\n");
    fprintf(exportFile, "==========================================================================================\n");
    snprintf(sql, sizeof(sql), "SELECT Date, Time FROM Pointages WHERE strftime('%%m', Date) = '%02d' AND strftime('%%Y', Date) = '%04d';", month, year);
    if (sqlite3_exec(db, sql, callbackFile, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error\n");
    }
    fprintf(exportFile, "\n------------------------------------------------------------------------------------------\n");
    fclose(exportFile);
    printf("export with succes");
}


void createTable() {
    char *errMsg;
    const char *sql = "CREATE TABLE IF NOT EXISTS Pointages (ID INTEGER PRIMARY KEY, Type TEXT, Date TEXT, Time TEXT, UNIQUE(Type, Date));";
    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}


int selectCallback(void *data, int argc, char **argv, char **azColName) {
    int *recordExists = (int *)data;

    if (argc > 0) {
        *recordExists = 1; // L'enregistrement existe déjà
    }

    return 0;
}

void recordPointage(const char* type) {
    time_t now;
    struct tm* timeinfo;
    char dateP[11];  
    char timeP[9]; 
    time(&now);
    timeinfo = localtime(&now);
    strftime(dateP, 11, "%Y-%m-%d", timeinfo); 
    strftime(timeP, 9, "%H:%M:%S", timeinfo);  


    if (strcmp(type, "Entrée") == 0) {

            char selectSql[100];
            snprintf(selectSql, sizeof(selectSql), "SELECT * FROM Pointages WHERE Type = '%s' AND Date = '%s';", type, dateP);
            int recordExists = 0;
            // Exécutez la requête SELECT
            if (sqlite3_exec(db, selectSql, selectCallback, &recordExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement existant\n");
                return;
            }
            if (recordExists == 0) {
                char insertSql[100];
                snprintf(insertSql, sizeof(insertSql), "INSERT INTO Pointages (Type, Date, Time) VALUES ('%s', '%s', '%s');", type, dateP, timeP);
                if (sqlite3_exec(db, insertSql, 0, 0, 0) != SQLITE_OK) {
                    fprintf(stderr, "Erreur lors de l'insertion des données\n");
                }else{
                    clearScreen();
                    fprintf(stderr, "Vous êtes pointé avec succès\n");
                }
            } else {
                clearScreen();
                fprintf(stderr, "Vous êtes déjà pointé\n");
            }

    } else if (strcmp(type, "Sortie_Pause") == 0) {

            char selectSql[100];
            snprintf(selectSql, sizeof(selectSql), "SELECT * FROM Pointages WHERE Type = '%s' AND Date = '%s';", type, dateP);
            int recordExists = 0;
            // Exécutez la requête SELECT
            if (sqlite3_exec(db, selectSql, selectCallback, &recordExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement existant\n");
                return;
            }

            // Vérifiez si un enregistrement de entrer existe
            char selectEntrerSql[100];
            snprintf(selectEntrerSql, sizeof(selectEntrerSql), "SELECT * FROM Pointages WHERE Type = 'Entrée' AND Date = '%s';", dateP);
            int entrerExists = 0;
            // Exécutez la requête SELECT
            if (sqlite3_exec(db, selectEntrerSql, selectCallback, &entrerExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement existant\n");
                return;
            }

            if (recordExists == 1){                
                clearScreen();
                fprintf(stderr, "Vous êtes déjà pointé\n");
            } else if (entrerExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Entrée' d'abord.\n");
            }else{
                // Maintenant, insérez le type 2
                char insertSqlType2[100];
                snprintf(insertSqlType2, sizeof(insertSqlType2), "INSERT INTO Pointages (Type, Date, Time) VALUES ('%s', '%s', '%s');", type, dateP, timeP);
                if (sqlite3_exec(db, insertSqlType2, 0, 0, 0) != SQLITE_OK) {
                    fprintf(stderr, "Erreur lors de l'insertion des données de type 2\n");
                }else{
                    clearScreen();
                    fprintf(stderr, "Vous êtes pointé avec succès\n");
                }
            }

    } else if (strcmp(type, "Entrée_Pause") == 0) {

            char selectSql[100];
            snprintf(selectSql, sizeof(selectSql), "SELECT * FROM Pointages WHERE Type = '%s' AND Date = '%s';", type, dateP);
            int recordExists = 0;
            // Exécutez la requête SELECT
            if (sqlite3_exec(db, selectSql, selectCallback, &recordExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement existant\n");
                return;
            }
        
            // Vérifiez si un enregistrement de type "Entrée" existe
            char selectSqlEntrée[100];
            snprintf(selectSqlEntrée, sizeof(selectSqlEntrée), "SELECT * FROM Pointages WHERE Type = 'Entrée' AND Date = '%s';", dateP);
            int entréeExists = 0;
            // Exécutez la requête SELECT pour "Entrée"
            if (sqlite3_exec(db, selectSqlEntrée, selectCallback, &entréeExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement Entrée existant\n");
                return;
            }

           // Vérifiez si un enregistrement de type "Sortie_Pause" existe
            char selectSqlSortiePause[100];
            snprintf(selectSqlSortiePause, sizeof(selectSqlSortiePause), "SELECT * FROM Pointages WHERE Type = 'Sortie_Pause' AND Date = '%s';", dateP);
            int sortiePauseExists = 0;
            // Exécutez la requête SELECT pour "Sortie_Pause"
            if (sqlite3_exec(db, selectSqlSortiePause, selectCallback, &sortiePauseExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement Sortie_Pause existant\n");
                return;
            }


            if (recordExists == 1){                
                clearScreen();
                fprintf(stderr, "Vous êtes déjà pointé\n");
            } else if (entréeExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Entrée' d'abord\n");
            } else if (sortiePauseExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Entrée_Pause' d'abord\n");
            }else{
                // Maintenant, insérez le type 2
                char insertSqlType2[100];
                snprintf(insertSqlType2, sizeof(insertSqlType2), "INSERT INTO Pointages (Type, Date, Time) VALUES ('%s', '%s', '%s');", type, dateP, timeP);
                if (sqlite3_exec(db, insertSqlType2, 0, 0, 0) != SQLITE_OK) {
                    fprintf(stderr, "Erreur lors de l'insertion des données de type 2\n");
                }else{
                    clearScreen();
                    fprintf(stderr, "Vous êtes pointé avec succès\n");
                }
            }

    } else if (strcmp(type, "Sortie") == 0) {

            char selectSql[100];
            snprintf(selectSql, sizeof(selectSql), "SELECT * FROM Pointages WHERE Type = '%s' AND Date = '%s';", type, dateP);
            int recordExists = 0;
            // Exécutez la requête SELECT
            if (sqlite3_exec(db, selectSql, selectCallback, &recordExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement existant\n");
                return;
            }

            // Vérifiez si un enregistrement de type "Entrée" existe
            char selectSqlEntrée[100];
            snprintf(selectSqlEntrée, sizeof(selectSqlEntrée), "SELECT * FROM Pointages WHERE Type = 'Entrée' AND Date = '%s';", dateP);
            int entréeExists = 0;
            // Exécutez la requête SELECT pour "Entrée"
            if (sqlite3_exec(db, selectSqlEntrée, selectCallback, &entréeExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement Entrée existant\n");
                return;
            }

            // Vérifiez si un enregistrement de type "Entrée_Pause" existe
            char selectSqlEntréePause[100];
            snprintf(selectSqlEntréePause, sizeof(selectSqlEntréePause), "SELECT * FROM Pointages WHERE Type = 'Entrée_Pause' AND Date = '%s';", dateP);
            int entréePauseExists = 0;
            // Exécutez la requête SELECT pour "Entrée_Pause"
            if (sqlite3_exec(db, selectSqlEntréePause, selectCallback, &entréePauseExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement Entrée_Pause existant\n");
                return;
            }

            // Vérifiez si un enregistrement de type "Sortie_Pause" existe
            char selectSqlSortiePause[100];
            snprintf(selectSqlSortiePause, sizeof(selectSqlSortiePause), "SELECT * FROM Pointages WHERE Type = 'Sortie_Pause' AND Date = '%s';", dateP);
            int sortiePauseExists = 0;
            // Exécutez la requête SELECT pour "Sortie_Pause"
            if (sqlite3_exec(db, selectSqlSortiePause, selectCallback, &sortiePauseExists, 0) != SQLITE_OK) {
                fprintf(stderr, "Erreur lors de la sélection de l'enregistrement Sortie_Pause existant\n");
                return;
            }

            if (recordExists == 1){                
                clearScreen();
                fprintf(stderr, "Vous êtes déjà pointé\n");
            } else if (entréeExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Entrée' d'abord\n");
            } else if (entréePauseExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Entrée_Pause' d'abord\n");
            } else if (sortiePauseExists == 0) {
                clearScreen();
                printf("Vous devez pointer 'Sortie_Pause' d'abord\n");
            } else {
                // Maintenant, insérez le type "Sortie"
                char insertSqlTypeSortie[100];
                snprintf(insertSqlTypeSortie, sizeof(insertSqlTypeSortie), "INSERT INTO Pointages (Type, Date, Time) VALUES ('%s', '%s', '%s');", type, dateP, timeP);
                if (sqlite3_exec(db, insertSqlTypeSortie, 0, 0, 0) != SQLITE_OK) {
                    fprintf(stderr, "Erreur lors de l'insertion des données de type 'Sortie'\n");
                }else{
                    clearScreen();
                    fprintf(stderr, "Vous êtes pointé avec succès\n");
                }
            }

    } else {
        printf("Le type ne correspond à aucun des cas ci-dessus");
    }

}





int main() {
    if (sqlite3_open("/home/dell/pointage/pointage.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Impossible d'ouvrir la base de données.\n");
        return 1;
    }

    createTable();

    int choice;
    int choiceExport;

    while (1) {
        clearScreen();
        printMainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (1) {
                    //clearScreen();
                    printPointageMenu();
                    scanf("%d", &choice);
                    
                    if (choice == 5) break;

                    switch (choice) {
                        case 1:
                            recordPointage("Entrée");
                            break;
                        case 2:
                            recordPointage("Sortie_Pause");
                            break;
                        case 3:
                            recordPointage("Entrée_Pause");
                            break;
                        case 4:
                            recordPointage("Sortie");
                            break;
                        default:
                            printf("Choix invalide. Réessayez.\n");
                    }
                }
                break;
            case 2:
                int choiceExport;
                int month, year;
                clearScreen();
                printDisplayExportMenu();
                scanf("%d", &choiceExport);

                switch (choiceExport) {
                    case 1:
                        printf("Entrez le mois (01-12) : ");
                        scanf("%d", &month);
                        printf("Entrez l'année : ");
                        scanf("%d", &year);
                        listPointages(month,year);
                        exit(0);
                    case 2:
                        printf("Entrez le mois (01-12) : ");
                        scanf("%d", &month);
                        printf("Entrez l'année : ");
                        scanf("%d", &year);
                        listPointagesFile(month,year);
                        break;
                    case 3:
                        // Retour au menu principal
                        break;
                    default:
                        printf("Choix invalide. Réessayez.\n");
                }
                break;
            case 3:
                sqlite3_close(db);
                return 0;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}
