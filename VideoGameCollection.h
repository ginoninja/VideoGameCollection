#ifndef VIDEOGAMECOLLECTION_H
#define VIDEOGAMECOLLECTION_H

struct Game
{
	char title[50];
	char developer[50];
	int yearPurchased;
	char category[50];
};

int addGame(struct Game list[], int noOfGames);
int deleteGame(struct Game list[], int noOfGames);
void displayAll(struct Game list[], int noOfGames);
struct Game *selectByDeveloper(struct Game list[], int noOfGames);
void writeFile(struct Game list[], int noOfGames);
int readFile(struct Game list[]);

#endif

