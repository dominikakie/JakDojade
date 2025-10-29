#include <iostream>
#include "Structure.h"
using namespace std;

int searchForIndex(City** tab, char* nameToSearch, int numberOfCities);
int BFS(int width, int height, int x, int y, char** tab, int xEnd, int yEnd);
char* getName(char** tab, int x, int y, int height, int width);
int mapAndCities(int height, int width, char** map);
void dijkstra(int** matrix, int numberOfCities, int startPoint, int finishPoint, int mode, City** cities);


int  main() {
	int counterOfCities;
	int width;
	int height;
	int numberOfFlights;
	int numberOfQuestions;
	int i;
	char nameOfCity[10];
	int fromCity;
	int toCity;
	int lenght;
	int* shortestPath;
	int type;

	cin >> width >> height;

	//allocating place for map
	char** map = new char* [height];
	for (int y = 0; y < height; y++)
		map[y] = new char[width + 1];

	//getting map
	counterOfCities = mapAndCities(height, width, map);

	//allocating place for array of cities
	City** cities = new City * [counterOfCities];
	i = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == '*') {
				City* city = new City(getName(map, x, y, height, width), x, y);
				cities[i] = city;
				i++;
			}
		}
	}

	//allocating place for matrix 
	int** matrixOfCities = new int* [counterOfCities];
	for (int y = 0; y < counterOfCities; y++)
		matrixOfCities[y] = new int[counterOfCities];

	//getting shortest direct route and adding to matrix from every city to every city
	for (i = 0; i < counterOfCities; i++) {
		for (int j = 0; j < counterOfCities; j++) {
			int path = BFS(width, height, cities[i]->x, cities[i]->y, map, cities[j]->x, cities[j]->y);
			matrixOfCities[i][j] = path;
		}
	}
	cin >> numberOfFlights;
	//adding flights to matrix
	for (int k = 0; k < numberOfFlights; k++) {
		cin >> nameOfCity;
		fromCity = searchForIndex(cities, nameOfCity, counterOfCities);
		cin >> nameOfCity;
		toCity = searchForIndex(cities, nameOfCity, counterOfCities);
		cin >> lenght;
		if ((matrixOfCities[fromCity][toCity] > lenght) || (matrixOfCities[fromCity][toCity] < 0)) {
			matrixOfCities[fromCity][toCity] = lenght;
		}
	}

	cin >> numberOfQuestions;
	// searching for the shortest way to city from city using dijkstra and data from matrix
	for ( i = 0; i < numberOfQuestions; i++) {
		cin >> nameOfCity;
		fromCity = searchForIndex(cities, nameOfCity, counterOfCities);
		cin >> nameOfCity;
		toCity = searchForIndex(cities, nameOfCity, counterOfCities);
		cin >> type;
		dijkstra(matrixOfCities, counterOfCities, fromCity, toCity, type, cities);
	}

	for ( i = 0; i < height; ++i)
		delete[] map[i];
	delete[] map;
	delete[] cities;
	for ( i = 0; i < counterOfCities; ++i)
		delete[] matrixOfCities[i];
	delete[] matrixOfCities;
	return 0;
}
int searchForIndex(City** tab, char* nameToSearch, int numberOfCities) {
	for (int j = 0; j < numberOfCities; j++) {
		int i = 0;
		while (tab[j]->name[i] == nameToSearch[i]) {
			if (nameToSearch[i] == '\0') {
				return j;
			}
			i++;
		}
	}
	return -1;
}
int mapAndCities(int height, int width, char** map) {
	int counter = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cin >> map[y][x];
			if (map[y][x] == '*') {
				counter++;
			}
		}
		map[y][width] = '\0';
	}
	return counter;
}

bool IsLetter(char** tab, int x, int y) {
	if ((tab[y][x] != '#') && (tab[y][x] != '.') && (tab[y][x] != '*') && (tab[y][x] != '\0'))
		return true;
	return false;
}


char* cityName(char** tab, int x, int y) {
	int lenght = 0;
	while (x >= 0 && IsLetter(tab, x, y)) {
		x--;
	}
	x++;
	while (IsLetter(tab, x, y)) {
		x++;
		++lenght;
	}
	char* name = new char[lenght + 1];
	for (int i = 0; i < lenght; i++) {
		name[i] = tab[y][x - lenght + i];
	}
	name[lenght] = '\0';
	return name;
}

char* getName(char** tab, int x, int y, int height, int width) {
	char* name = nullptr;

	if ((x > 0) && (y > 0) && (IsLetter(tab, x - 1, y - 1))) {
		name = cityName(tab, x - 1, y - 1);
	}
	if ((x > 0) && (y + 1 < height) && (IsLetter(tab, x - 1, y + 1))) {
		name = cityName(tab, x - 1, y + 1);
	}
	if ((x > 0) && (IsLetter(tab, x - 1, y))) {
		name = cityName(tab, x - 1, y);
	}
	if ((y > 0) && (IsLetter(tab, x, y - 1))) {
		name = cityName(tab, x, y - 1);
	}
	if ((y > 0) && (x + 1 < width) && (IsLetter(tab, x + 1, y - 1))) {
		name = cityName(tab, x + 1, y - 1);
	}
	if ((x + 1 < width) && (IsLetter(tab, x + 1, y))) {
		name = cityName(tab, x + 1, y);
	}
	if ((y + 1 < height) && (x + 1 < width) && (IsLetter(tab, x + 1, y + 1))) {
		name = cityName(tab, x + 1, y + 1);
	}
	if ((y + 1 < height) && (IsLetter(tab, x, y + 1))) {
		name = cityName(tab, x, y + 1);
	}
	return name;
}


int BFS(int width, int height, int x, int y, char** tab, int xEnd, int yEnd) {
	bool* checked = new bool[height * width];
	int* distance = new int[height * width];
	//setting defalut values
	for (int i = 0; i < (height * width); i++) {
		checked[i] = false;
		distance[i] = 0;
	}

	Position position;
	LinkedList* Queue = new LinkedList;

	checked[(y * width) + x] = true;
	position.x = x;
	position.y = y;
	Queue->addElement(position);
	//default value of result -1 (if cant find direct way result -1)
	int result = -1;

	while (Queue->lengthOfLinkedList() > 0) {
		Position currentPosition = Queue->getFirst();
		Position temp;
		Queue->deleteFirst();
		//checking if found finishing point
		if ((currentPosition.x == xEnd) && (currentPosition.y == yEnd)) {
			result = distance[(currentPosition.y) * width + currentPosition.x];
			break;
		}
		//checking 4 neighbours
		for (int i = 0; i < 4; i++) {
			temp = currentPosition;
			if ((i == 0) && (currentPosition.x < width - 1))
				temp.x++;
			else if ((i == 1) && (currentPosition.y < height - 1))
				temp.y++;
			else if ((i == 2) && (currentPosition.x > 0))
				temp.x--;
			else if ((i == 3) && (currentPosition.y > 0))
				temp.y--;
			// adding to queue if # is the sign of neighbour
			if (((tab[temp.y][temp.x] == '#')) && (!checked[(temp.y * width) + temp.x])) {
				checked[(temp.y * width) + temp.x] = true;
				distance[(temp.y) * width + temp.x] = distance[(currentPosition.y) * width + currentPosition.x] + 1;
				Queue->addElement(temp);
			}
			//returning if * is the sign of neighbour
			if ((tab[temp.y][temp.x] == '*') && (!checked[(temp.y * width) + temp.x])) {
				if ((temp.x == xEnd) && (temp.y == yEnd)) {
					result = distance[(currentPosition.y) * width + currentPosition.x] + 1;
					delete[] checked;
					delete[] distance;
					return result;
				}

			}
		}
	}
	delete[] checked;
	delete[] distance;
	return result;

}

void dijkstra(int** matrix, int numberOfCities, int startPoint, int finishPoint, int mode, City** cities) {
	int* prev = new int[numberOfCities];
	int* citiesVisited = new int[numberOfCities];
	int* distance = new int[numberOfCities];
	bool* checked = new bool[numberOfCities];
	int i;

	//setting defalut values
	for ( i = 0; i < numberOfCities; i++) {
		distance[i] = INT_MAX;
		checked[i] = false;
		prev[i] = -1;
		citiesVisited[i] = -1;
	}
	distance[startPoint] = 0;

	//finding shortest path from starting point
	for ( i = 0; i < numberOfCities; i++) {
		int h = 0;
		int minimum = INT_MAX;
		for (int k = 0; k < numberOfCities; k++) {
			if (checked[k] != true) {
				if (distance[k] <= minimum) {
				//setting minimum if found shorter distance
				minimum = distance[k];
				//sttting h to index
				h = k;
			}
			}
		}
		//setting array from index as checked
		checked[h] = true;
		for (int j = 0; j < numberOfCities; j++) {
			if ((checked[j] != true) && (distance[h] != INT_MAX)) {
				if (distance[h] + matrix[h][j] < distance[j]) {
					if (matrix[h][j] > 0) {
					//adding to distance the wage of matrix
					distance[j] = distance[h] + matrix[h][j];
					//adding index to remember cities visited while reaching finish city
					prev[j] = h;
					}
				}
			}
		}
	}
	if (mode == 0) {
		cout << distance[finishPoint];
		cout << endl;
	}
	else {
		cout << distance[finishPoint];
		i = finishPoint;
		int n = 0;
		// adding loop to print cities from begin to end
		while (i != startPoint) {
			citiesVisited[n] = i;
			i = prev[i];
			n++;
		}
		// printing cities visitesd
		while (n > 0) {
			if (citiesVisited[n] != -1) {
				cout << " " << cities[citiesVisited[n]]->getName();
			}
			n--;
		}
		cout << endl;
	}
	delete[] checked;
	delete[] distance;
	delete[] prev;
	delete[] citiesVisited;
	return;
}

