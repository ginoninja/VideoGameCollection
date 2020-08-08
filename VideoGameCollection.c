/***********************************************************************
 * VideoGameCollection.c
 * Maintains a collection of video games
 * Alexander Lee
 * Version 1.0
 * ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "VideoGameCollection.h"

int main(void) {
	struct Game *list = malloc(sizeof(struct Game) * 50);
	struct Game *gamesByDev;
	char select = 'X';
	int noOfGames = readFile(list);
	printf("Welcome to your Video Game collection,"
			" please use one of the instructions listed!\n");
	while (select != '5') {
		printf("\n1. Add a new game\n"
				"2. Display all games\n"
				"3. Display all games by publisher or developer\n"
				"4. Delete a game\n"
				"5. Exit\n");
		printf("\n");
		scanf("%c%*c", &select);
		switch (select) {
		case '1':
			noOfGames = addGame(list, noOfGames);
			writeFile(list, noOfGames);
			break;
		case '2':
			displayAll(list, noOfGames);
			break;
		case '3':
			gamesByDev = selectByDeveloper(list, noOfGames);
			free(gamesByDev);
			break;
		case '4':
			noOfGames = deleteGame(list, noOfGames);
			writeFile(list, noOfGames);
			break;
		case '5':
			free(list);
			break;
		default:
			puts("\nPlease enter a valid instruction.");
		}
	}
	return 0;
}

/* Adds a new game the collection */
int addGame(struct Game list[], int noOfGames) {
	printf("Enter title: ");
	scanf("%50[^\n]", list[noOfGames].title);
	getchar();
	printf("Enter developer/publisher: ");
	scanf("%50[^\n]", list[noOfGames].developer);
	printf("Enter year purchased: ");
	scanf("%d", &list[noOfGames].yearPurchased);
	getchar();
	printf("Enter category: ");
	scanf("%50[^\n]", list[noOfGames].category);
	getchar();
	return ++noOfGames;
}

/* Deletes a game from the collection */
int deleteGame(struct Game list[], int noOfGames) {
	int boolean = 0; 
	char title[50];
	printf("Enter title: ");
	scanf("%50[^\n]", title);
	getchar();
	int recordNo = 0;
	for (int i = 0; i < noOfGames; i++) {
		if (strcmp(list[i].title, title) == 0) {
			recordNo = i;
			boolean = 1; 
		}
	}
	if (boolean == 0) {
		printf("Video game not found in collection!");
		return noOfGames;
	}
	noOfGames--;
	while (recordNo < noOfGames) {
		list[recordNo] = list[recordNo + 1];
		recordNo++;
	}
	return noOfGames;
}

/* Displays all games onto the console */
void displayAll(struct Game list[], int noOfGames) {
	if (noOfGames < 1) {
		printf("\nNo games in collection!\n");
		return;
	}
	for (int i = 0; i < noOfGames; i++) {
		printf(
				"Game Title: %s, Developer: %s, Year Purchased: %d," 
				" Category: %s\n",
				list[i].title, list[i].developer, list[i].yearPurchased,
				list[i].category);
	}
}

/* Finds all games by a developer/publisher */
struct Game *selectByDeveloper(struct Game list[], int noOfGames) {
	struct Game *gamesByDev = malloc(sizeof(struct Game) * noOfGames);
	char developer[50];
	int noOfGamesByDev = 0;
	printf("Enter developer/publisher: ");
	scanf("%50[^\n]", developer);
	getchar();
	for (int i = 0; i < noOfGames; i++) {
		if (strcmp(list[i].developer, developer) == 0) {
			strcpy(gamesByDev[i].title, list[i].title);
			strcpy(gamesByDev[i].developer, list[i].developer);
			int yearPurchased = list[i].yearPurchased;
			gamesByDev[i].yearPurchased = yearPurchased;
			strcpy(gamesByDev[i].category, list[i].category);
			noOfGamesByDev++;
			printf(
					"Game Title: %s, Developer: %s, Year Purchased: %d, Category: %s\n",
					gamesByDev[i].title, gamesByDev[i].developer,
					gamesByDev[i].yearPurchased, gamesByDev[i].category);
		}
	}
	if (noOfGamesByDev == 0) {
		printf("No games by developer or publisher in collection!\n");
	}

	return gamesByDev;
}

/* Writes the game to a file */
void writeFile(struct Game list[], int noOfGames) {
	FILE *fptr;
	if ((fptr = fopen("games.txt", "w")) == NULL) 
	{
		printf("\nError: %s\n", strerror(errno));
		return;
	}
	if (noOfGames <= 0) 
			{
		fclose(fptr);
		remove("games.txt");
	}
	for (int i = 0; i < noOfGames; i++) {
		fprintf(fptr, "%s: %s: %d %s\n", list[i].title, list[i].developer,
				list[i].yearPurchased, list[i].category);
	}
	fclose(fptr);
}

/* Reads the file to array if it exist */
int readFile(struct Game list[]) { 
	FILE *fptr;
	int noOfGames = 0;
	struct Game rec;
	if ((fptr = fopen("games.txt", "r")) == NULL) {
		printf("Error: %s\n", strerror(errno));
		return noOfGames;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%50[^:]: %50[^:]: %d %50[^\n]\n", rec.title,
				rec.developer, &rec.yearPurchased, rec.category); 
		list[noOfGames++] = rec;
	}
	fclose(fptr);
	return noOfGames;
}
