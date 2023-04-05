#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CHANCES 6
#define WORD_LENGTH 5
#define DICTIONARY_FILE "dictionary.txt"
#define SCORES_FILE "scores.txt"


void read_line(char *buffer, int max_length) 
{
    fgets(buffer, max_length, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; 
}

void save_score(char *name, char *word, int attempts, int time) {
    FILE *fp;
    fp = fopen(SCORES_FILE, "a");
    fprintf(fp, "%s,%s,%d,%d\n", name, word, attempts, time);
    fclose(fp);
}


void show_scores() {
    FILE *fp;
    fp = fopen(SCORES_FILE, "r");
    if (fp == NULL) {
        printf("Nenhum resultado encontrado.\n");
        return;
    }

    printf("\nRanking:\n");
    printf("%-20s %-10s %-10s %-10s\n", "Nome", "Palavra", "Tentativas", "Tempo (s)");
    printf("--------------------------------------------------------\n");

    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char *name = strtok(line, ",");
        char *word = strtok(NULL, ",");
        char *attempts_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        int attempts = atoi(attempts_str);
        int time = atoi(time_str);

        printf("%-20s %-10s %-10d %-10d\n", name, word, attempts, time);
    }

    fclose(fp);
}

int main() 
{
    
    FILE *fp;
    fp = fopen(DICTIONARY_FILE, "r");
    if (fp == NULL) 
    {
        printf("Erro ao abrir o arquivo do dicionÃ¡rio.\n");
        return 1;
    }

    
    int num_words;
    fscanf(fp, "%d", &num_words);

    
    int i;
    char *dictionary = (char *) malloc(num_words * sizeof(char *));
    for (i = 0; i < num_words; i++) 
    {
        dictionary[i] = (char *) malloc((WORD_LENGTH + 1) * sizeof(char));
        fscanf(fp, "%s", dictionary[i]);
    }

    
    fclose(fp);

    time_t start_time = time(NULL);
    srand(time(NULL));
    int word_index = rand() %num_words;
    char *word = dictionary[word_index];

    
    int num_chances = MAX_CHANCES;
    int guessed_letters[WORD_LENGTH] = {0};
    int all_letters_guessed = 0;


    while (num_chances > 0 && !all_letters_guessed) 
    {
    
        printf("\nPalavra: ");
        int i;
        for (i = 0; i < WORD_LENGTH; i++) 
        {
            if (guessed_letters[i]) 
            {
                printf("%c ", word[i]);
            } 
            else 
            {
            printf("_ ");
            }
        }
    
    
        printf("\nLetras acertadas: ");
        int any_letter_guessed = 0;
        for (i = 0; i < WORD_LENGTH; i++) 
        {
            if (guessed_letters[i]) 
            {
                printf("%c ", word[i]);
                any_letter_guessed = 1;
            } 
            else 
            {
                printf("^ ");
            }
        }
        if (!any_letter_guessed) 
        {
            printf("X ");
        }
    
        printf("\n");
    
    
        printf("Tentativa (letra ou palavra): ");
        char guess[WORD_LENGTH + 1];
        read_line(guess, WORD_LENGTH + 1);
    
    
    

	
	    
	    if (strlen(guess) == 1) {
	        
	        char letter = guess[0];
	
	        
	        int letter_found = 0;
	        int i;
	        for (i = 0; i < WORD_LENGTH; i++) 
            {
	            if (word[i] == letter) 
                {
	                guessed_letters[i] = 1;
	                letter_found = 1;
	            }
	        }
	
	        
	        if (!letter_found) 
            {
	            num_chances--;
	            printf("Letra nÃ£o encontrada. Restam %d chances.\n", num_chances);
	        }
	    } 
        else 
        {
	        
	        if (strcmp(guess, word) == 0) 
            {
	            
	            all_letters_guessed = 1;
	        } 
            else 
            {
	            
	            printf("Palavra incorreta.\n");
	            num_chances--;
	            printf("Restam %d chances.\n", num_chances);
	        }
	    }
	}
    printf("\nFim do jogo!\n");

    if (all_letters_guessed) 
    {
        printf("Parabéns! Você venceu.\n");

        printf("Digite seu nome: ");
        char name[50];
        read_line(name, 50);

        FILE *fp;
        fp = fopen(SCORES_FILE, "a");
        fprintf(fp, "%s,%s,%d,%d\n", name, word, MAX_CHANCES - num_chances, (int) difftime(time(NULL), start_time));
        fclose(fp);

    } 
    else 
    {
        printf("Que pena! Você perdeu. A palavra era %s.\n", word);
    }
}  