/*
 * Zombie Apocalypse Survival Game
 * A console-based survival game where a player must navigate through a zombie-infested city
 * to reach a safe zone. Implements custom data structures (graph, queue, linked list).
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <windows.h>
#include <limits>
#include <cstring>

 // ANSI Color Codes
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"

using namespace std;

// Constants
const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 10;
const int MAX_ZOMBIES = 10;
const int MAX_ITEMS = 10;
const char WALL = '#';
const char PLAYER = 'P';
const char ZOMBIE = 'Z';
const char ITEM = '*';
const char SAFE_ZONE = 'S';
const char EMPTY = '.';

// Custom implementation of a String class
class String {
private:
    char* str;
    int length;

public:
    // Default constructor
    String() {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }

    // Constructor with C-style string
    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy_s(str, sizeof(str), s);
    }

    // Copy constructor
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy_s(str, sizeof(str), other.str);
    }

    // Destructor
    ~String() {
        delete[] str;
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy_s(str, sizeof(str), other.str);
        }
        return *this;
    }

    // Get the C-style string
    const char* c_str() const {
        return str;
    }

    // Get the length of the string
    int size() const {
        return length;
    }

    // Concatenation operator
    String operator+(const String& other) {
        String result;
        result.length = length + other.length;
        delete[] result.str;
        result.str = new char[result.length + 1];
        strcpy_s(result.str, sizeof(result.str), str);
        strcat_s(result.str, sizeof(result.str), other.str);
        return result;
    }
};

// Custom implementation of a Vector class
template <typename T>
class Vector {
private:
    T* data;
    int capacity;
    int count;

    // Resize the vector
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Default constructor
    Vector() {
        capacity = 10;
        count = 0;
        data = new T[capacity];
    }

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Add an element to the vector
    void push_back(const T& element) {
        if (count == capacity) {
            resize(capacity * 2);
        }
        data[count++] = element;
    }

    // Get element at index
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            // Handle out of bounds
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Get the size of the vector
    int size() const {
        return count;
    }

    // Check if the vector is empty
    bool empty() const {
        return count == 0;
    }

    // Clear the vector
    void clear() {
        count = 0;
    }

    // Iterator implementation
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}

        T& operator*() { return *ptr; }

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + count); }
};

// Custom implementation of a Stack class (will be used for pathfinding)
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top;
    int size;

public:
    // Default constructor
    Stack() : top(nullptr), size(0) {}

    // Destructor
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    // Push an element onto the stack
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    // Pop an element from the stack
    T pop() {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }

        Node* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }

    // Check if the stack is empty
    bool empty() const {
        return top == nullptr;
    }

    // Peek at the top element
    T peek() const {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }
        return top->data;
    }

    // Get the size of the stack
    int getSize() const {
        return size;
    }
};

// Custom implementation of a Queue class
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    // Default constructor
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Destructor
    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    // Enqueue an element
    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (empty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    // Dequeue an element
    T dequeue() {
        if (empty()) {
            throw out_of_range("Queue is empty");
        }

        Node* temp = front;
        T value = temp->data;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    // Check if the queue is empty
    bool empty() const {
        return front == nullptr;
    }

    // Peek at the front element
    T peek() const {
        if (empty()) {
            throw out_of_range("Queue is empty");
        }
        return front->data;
    }

    // Get the size of the queue
    int getSize() const {
        return size;
    }
};

// Position struct for coordinates
struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

// Item struct for collected items
struct Item {
    String name;
    int value;
    int healthBoost;

    Item(const String& name = "", int value = 0, int healthBoost = 0)
        : name(name), value(value), healthBoost(healthBoost) {
    }
};

// Custom implementation of a Linked List for items
class ItemList {
private:
    struct Node {
        Item data;
        Node* next;

        Node(const Item& item) : data(item), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    // Default constructor
    ItemList() : head(nullptr), size(0) {}

    // Destructor
    ~ItemList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Insert an item
    void insert(const Item& item) {
        Node* newNode = new Node(item);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        size++;
    }

    // Display all items
    void display() const {
        Node* current = head;
        cout << "[";
        bool first = true;

        while (current != nullptr) {
            if (!first) {
                cout << ", ";
            }
            cout << current->data.name.c_str();
            first = false;
            current = current->next;
        }

        cout << "]";
    }

    // Get the size of the list
    int getSize() const {
        return size;
    }

    // Get the total value of all items
    int getTotalValue() const {
        int total = 0;
        Node* current = head;

        while (current != nullptr) {
            total += current->data.value;
            current = current->next;
        }

        return total;
    }

    // Get the total health boost
    int getTotalHealthBoost() const {
        int total = 0;
        Node* current = head;

        while (current != nullptr) {
            total += current->data.healthBoost;
            current = current->next;
        }

        return total;
    }
};

// Graph class for city map and navigation
class Graph {
private:
    struct Node {
        Position pos;
        Vector<Node*> neighbors;

        Node(const Position& p) : pos(p) {}
    };

    Vector<Node*> nodes;
    char map[MAP_HEIGHT][MAP_WIDTH];

    // Find a node by position
    Node* findNode(const Position& pos) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->pos == pos) {
                return nodes[i];
            }
        }
        return nullptr;
    }

public:
    // Constructor
    Graph() {
        // Initialize the map with empty spaces
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                map[y][x] = EMPTY;
            }
        }
    }

    // Destructor
    ~Graph() {
        for (int i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
    }

    // Build the graph from the map
    void buildFromMap() {
        // Clear existing nodes
        for (int i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
        nodes.clear();

        // Create nodes for each non-wall cell
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] != WALL) {
                    Node* node = new Node(Position(x, y));
                    nodes.push_back(node);
                }
            }
        }

        // Create edges between adjacent nodes
        for (int i = 0; i < nodes.size(); i++) {
            Position pos = nodes[i]->pos;
            int x = pos.x;
            int y = pos.y;

            // Check four directions
            Position directions[4] = {
                Position(x, y - 1),  // Up
                Position(x + 1, y),  // Right
                Position(x, y + 1),  // Down
                Position(x - 1, y)   // Left
            };

            for (int j = 0; j < 4; j++) {
                Position nextPos = directions[j];
                if (nextPos.x >= 0 && nextPos.x < MAP_WIDTH &&
                    nextPos.y >= 0 && nextPos.y < MAP_HEIGHT &&
                    map[nextPos.y][nextPos.x] != WALL) {

                    Node* neighbor = findNode(nextPos);
                    if (neighbor != nullptr) {
                        nodes[i]->neighbors.push_back(neighbor);
                    }
                }
            }
        }
    }

    // Find the shortest path using BFS
    Vector<Position> findPath(const Position& start, const Position& end) {
        Vector<Position> path;

        // Check if start and end positions are valid
        Node* startNode = findNode(start);
        Node* endNode = findNode(end);
        if (startNode == nullptr || endNode == nullptr) {
            return path;  // Return empty path if invalid
        }

        // Arrays for BFS
        bool visited[MAP_HEIGHT][MAP_WIDTH] = { false };
        Position parent[MAP_HEIGHT][MAP_WIDTH];
        Queue<Node*> q;

        // Mark start as visited and enqueue
        visited[start.y][start.x] = true;
        q.enqueue(startNode);

        bool found = false;
        while (!q.empty() && !found) {
            Node* current = q.dequeue();
            Position currentPos = current->pos;

            // Check if we've reached the end
            if (currentPos == end) {
                found = true;
                break;
            }

            // Check all neighbors
            for (int i = 0; i < current->neighbors.size(); i++) {
                Node* neighbor = current->neighbors[i];
                Position neighborPos = neighbor->pos;

                if (!visited[neighborPos.y][neighborPos.x]) {
                    visited[neighborPos.y][neighborPos.x] = true;
                    parent[neighborPos.y][neighborPos.x] = currentPos;
                    q.enqueue(neighbor);
                }
            }
        }

        // Reconstruct the path if we found one
        if (found) {
            Position current = end;
            Stack<Position> stack;

            while (!(current == start)) {
                stack.push(current);
                current = parent[current.y][current.x];
            }

            // Start position
            path.push_back(start);

            // Add positions from stack to path
            while (!stack.empty()) {
                path.push_back(stack.pop());
            }
        }

        return path;
    }

    // Get the character at a position
    char getCell(const Position& pos) const {
        if (pos.x < 0 || pos.x >= MAP_WIDTH || pos.y < 0 || pos.y >= MAP_HEIGHT) {
            return WALL;  // Out of bounds is a wall
        }
        return map[pos.y][pos.x];
    }

    // Set the character at a position
    void setCell(const Position& pos, char c) {
        if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT) {
            map[pos.y][pos.x] = c;
        }
    }

    // Generate a random map
    void generateRandomMap() {
        // Create the border
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) {
                    map[y][x] = WALL;
                }
                else {
                    map[y][x] = EMPTY;
                }
            }
        }

        // Add some random walls
        for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT / 10; i++) {
            int x = rand() % (MAP_WIDTH - 2) + 1;
            int y = rand() % (MAP_HEIGHT - 2) + 1;
            map[y][x] = WALL;
        }

        // Add the player at a random position
        int px, py;
        do {
            px = rand() % (MAP_WIDTH - 2) + 1;
            py = rand() % (MAP_HEIGHT - 2) + 1;
        } while (map[py][px] != EMPTY);
        map[py][px] = PLAYER;

        // Add some zombies
        for (int i = 0; i < MAX_ZOMBIES / 2; i++) {
            int zx, zy;
            do {
                zx = rand() % (MAP_WIDTH - 2) + 1;
                zy = rand() % (MAP_HEIGHT - 2) + 1;
            } while (map[zy][zx] != EMPTY);
            map[zy][zx] = ZOMBIE;
        }

        // Add some items
        for (int i = 0; i < MAX_ITEMS / 2; i++) {
            int ix, iy;
            do {
                ix = rand() % (MAP_WIDTH - 2) + 1;
                iy = rand() % (MAP_HEIGHT - 2) + 1;
            } while (map[iy][ix] != EMPTY);
            map[iy][ix] = ITEM;
        }

        // Add the safe zone
        int sx, sy;
        do {
            sx = rand() % (MAP_WIDTH - 2) + 1;
            sy = rand() % (MAP_HEIGHT - 2) + 1;
        } while (map[sy][sx] != EMPTY);
        map[sy][sx] = SAFE_ZONE;

        // Build the graph
        buildFromMap();
    }

    // Draw the map
    void draw() const {
        cout << "  Map:" << endl;
        for (int y = 0; y < MAP_HEIGHT; y++) {
            cout << "  ";
            for (int x = 0; x < MAP_WIDTH; x++) {
                char c = map[y][x];
                if (c == PLAYER) {
                    cout << GREEN << c << RESET;
                }
                else if (c == ZOMBIE) {
                    cout << RED << c << RESET;
                }
                else if (c == ITEM) {
                    cout << YELLOW << c << RESET;
                }
                else if (c == SAFE_ZONE) {
                    cout << BLUE << c << RESET;
                }
                else {
                    cout << c;
                }
            }
            cout << endl;
        }
    }
};

// Game class
class ZombieGame {
private:
    Graph cityMap;
    Position playerPos;
    Vector<Position> zombiePositions;
    Queue<Position> zombieQueue;
    ItemList playerItems;
    int playerHealth;
    int score;
    int zombiesEncountered;
    int distanceTraveled;
    bool gameOver;
    bool playerWon;

    // Find the player position
    Position findPlayer() {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (cityMap.getCell(Position(x, y)) == PLAYER) {
                    return Position(x, y);
                }
            }
        }
        return Position(1, 1);  // Default position
    }

    // Find all zombie positions
    void findZombies() {
        zombiePositions.clear();
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (cityMap.getCell(Position(x, y)) == ZOMBIE) {
                    zombiePositions.push_back(Position(x, y));
                }
            }
        }
    }

    // Move the player
    bool movePlayer(int dx, int dy) {
        Position newPos(playerPos.x + dx, playerPos.y + dy);
        char cell = cityMap.getCell(newPos);

        // Check if the new position is valid
        if (cell == WALL) {
            return false;
        }

        // Process the new position
        if (cell == ITEM) {
            // Collect the item
            int itemValue = rand() % 10 + 1;
            int healthBoost = rand() % 5 + 1;

            // Create a random item name
            String itemName;
            int itemType = rand() % 3;
            if (itemType == 0) {
                itemName = "Medkit";
            }
            else if (itemType == 1) {
                itemName = "Food";
            }
            else {
                itemName = "Weapon";
            }

            // Add the item to the player's inventory
            Item item(itemName, itemValue, healthBoost);
            playerItems.insert(item);

            // Boost health
            playerHealth += healthBoost;
            if (playerHealth > 100) {
                playerHealth = 100;
            }

            // Update score
            score += itemValue * 10;
        }
        else if (cell == ZOMBIE) {
            // Encounter a zombie
            playerHealth -= 20;
            zombiesEncountered++;
            score -= 5;

            // Check if player is dead
            if (playerHealth <= 0) {
                gameOver = true;
                playerWon = false;
                return false;
            }
        }
        else if (cell == SAFE_ZONE) {
            // Reach the safe zone
            gameOver = true;
            playerWon = true;
            score += 100;  // Bonus for reaching the safe zone
            return true;
        }

        // Update the map
        cityMap.setCell(playerPos, EMPTY);
        cityMap.setCell(newPos, PLAYER);
        playerPos = newPos;

        // Update stats
        distanceTraveled++;
        score += 2;  // Points for moving

        return true;
    }

    // Move zombies
    void moveZombies() {
        // Move existing zombies
        Vector<Position> newZombiePositions;
        for (int i = 0; i < zombiePositions.size(); i++) {
            Position zombiePos = zombiePositions[i];

            // Choose a direction to move
            int dx = 0, dy = 0;

            // 50% chance to move toward player, 50% chance to move randomly
            if (rand() % 2 == 0) {
                // Move toward player
                Vector<Position> path = cityMap.findPath(zombiePos, playerPos);
                if (path.size() > 1) {
                    // Next position is the second element in the path (first is the zombie's current position)
                    Position nextPos = path[1];
                    dx = nextPos.x - zombiePos.x;
                    dy = nextPos.y - zombiePos.y;
                }
                else {
                    // No path to player, move randomly
                    int dir = rand() % 4;
                    if (dir == 0) dy = -1;  // Up
                    else if (dir == 1) dx = 1;  // Right
                    else if (dir == 2) dy = 1;  // Down
                    else dx = -1;  // Left
                }
            }
            else {
                // Move randomly
                int dir = rand() % 4;
                if (dir == 0) dy = -1;  // Up
                else if (dir == 1) dx = 1;  // Right
                else if (dir == 2) dy = 1;  // Down
                else dx = -1;  // Left
            }

            // Calculate new position
            Position newPos(zombiePos.x + dx, zombiePos.y + dy);
            char cell = cityMap.getCell(newPos);

            // Check if the new position is valid
            if (cell != WALL && cell != SAFE_ZONE && cell != ZOMBIE && cell != ITEM) {
                // Check if the zombie caught the player
                if (cell == PLAYER) {
                    playerHealth -= 20;
                    zombiesEncountered++;
                    score -= 5;

                    // Check if player is dead
                    if (playerHealth <= 0) {
                        gameOver = true;
                        playerWon = false;
                    }

                    // Zombie doesn't move onto player's position
                    newZombiePositions.push_back(zombiePos);
                }
                else {
                    // Update the map
                    cityMap.setCell(zombiePos, EMPTY);
                    cityMap.setCell(newPos, ZOMBIE);
                    newZombiePositions.push_back(newPos);
                }
            }
            else {
                // Zombie stays in place
                newZombiePositions.push_back(zombiePos);
            }
        }

        // Update zombie positions
        zombiePositions = newZombiePositions;

        // Spawn new zombies from the queue
        if (!zombieQueue.empty() && zombiePositions.size() < MAX_ZOMBIES) {
            Position spawnPos = zombieQueue.dequeue();
            if (cityMap.getCell(spawnPos) == EMPTY) {
                cityMap.setCell(spawnPos, ZOMBIE);
                zombiePositions.push_back(spawnPos);
            }
            else {
                // Try again later
                zombieQueue.enqueue(spawnPos);
            }
        }

        // Add new zombies to the queue
        if (rand() % 10 == 0 && zombieQueue.getSize() < MAX_ZOMBIES) {
            // Choose a random edge of the map to spawn from
            int edge = rand() % 4;
            int x, y;

            if (edge == 0) {  // Top edge
                x = rand() % (MAP_WIDTH - 2) + 1;
                y = 1;
            }
            else if (edge == 1) {  // Right edge
                x = MAP_WIDTH - 2;
                y = rand() % (MAP_HEIGHT - 2) + 1;
            }
            else if (edge == 2) {  // Bottom edge
                x = rand() % (MAP_WIDTH - 2) + 1;
                y = MAP_HEIGHT - 2;
            }
            else {  // Left edge
                x = 1;
                y = rand() % (MAP_HEIGHT - 2) + 1;
            }

            // Enqueue the new zombie
            Position spawnPos(x, y);
            if (cityMap.getCell(spawnPos) == EMPTY) {
                zombieQueue.enqueue(spawnPos);
            }
        }
    }

    // Clear the screen
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // Draw the game state
    void drawGame() {
        clearScreen();

        // Draw the border
        cout << RED << "=============================================" << RESET << endl;
        cout << RED << "|" << RESET << "        " << MAGENTA << "ZOMBIE APOCALYPSE SURVIVAL" << RESET << "        " << RED << "|" << RESET << endl;
        cout << RED << "=============================================" << RESET << endl;

        // Draw the menu
        cout << RED << "|" << RESET << " [1] Manual Mode | [2] Automated Mode | [3] Exit " << RED << "|" << RESET << endl;
        cout << RED << "=============================================" << RESET << endl;

        // Draw the status
        cout << RED << "|" << RESET << " Health: " << CYAN << playerHealth << RESET << "  |  ";
        cout << "Score: " << YELLOW << score << RESET << "  |  ";
        cout << "Inventory: ";
        playerItems.display();
        cout << RED << " |" << RESET << endl;
        cout << RED << "=============================================" << RESET << endl;

        // Draw the map
        cout << RED << "|" << RESET;
        cityMap.draw();
        cout << RED << "|" << RESET << endl;
        cout << RED << "=============================================" << RESET << endl;

        // Draw the legend
        cout << "Legend:" << endl;
        cout << GREEN << "P" << RESET << " = Player  ";
        cout << RED << "Z" << RESET << " = Zombie  ";
        cout << BLUE << "S" << RESET << " = Safe Zone  ";
        cout << YELLOW << "*" << RESET << " = Item  ";
        cout << "#" << " = Wall/Obstacle" << endl;

        // Game over message
        if (gameOver) {
            cout << endl;
            if (playerWon) {
                cout << GREEN << "Congratulations! You reached the safe zone!" << RESET << endl;
                cout << "Your final score: " << YELLOW << score << RESET << endl;
            }
            else {
                cout << RED << "Game Over! You were caught by zombies!" << RESET << endl;
                cout << "Your final score: " << YELLOW << score << RESET << endl;
            }
        }
    }

    // Save the high score
    void saveHighScore(const String& playerName) {
        ofstream file("highscores.txt", ios::app);
        if (file.is_open()) {
            file << playerName.c_str() << "," << score << endl;
            file.close();
        }
    }

    // Display the high scores
    void displayHighScores() {
        clearScreen();
        cout << CYAN << "===== HIGH SCORES =====" << RESET << endl;

        ifstream file("highscores.txt");
        if (file.is_open()) {
            char line[256];
            while (file.getline(line, 256)) {
                char* context = nullptr; // Required for strtok_s
                char* name = strtok_s(line, ",", &context);
                char* scoreStr = strtok_s(nullptr, ",", &context);

                if (name && scoreStr) {
                    int highScore = atoi(scoreStr);
                    cout << name << ": " << highScore << endl;
                }
            }
            file.close();
        }
        else {
            cout << "No high scores yet!" << endl;
        }

        cout << endl << "Press Enter to continue...";
        string temp;
        getline(cin, temp);
    }

    // Manual mode
    void playManualMode() {
        gameOver = false;
        playerWon = false;

        // Game loop
        while (!gameOver) {
            // Draw the game
            drawGame();

            // Get input
            cout << "Use WASD to move, Q to quit: ";
            string inputLine;
            getline(cin, inputLine);
            char input = inputLine.empty() ? '\0' : inputLine[0];


            // Process input
            bool moved = false;
            if (input == 'w' || input == 'W') {
                moved = movePlayer(0, -1);  // Up
            }
            else if (input == 'a' || input == 'A') {
                moved = movePlayer(-1, 0);  // Left
            }
            else if (input == 's' || input == 'S') {
                moved = movePlayer(0, 1);   // Down
            }
            else if (input == 'd' || input == 'D') {
                moved = movePlayer(1, 0);   // Right
            }
            else if (input == 'q' || input == 'Q') {
                gameOver = true;
                break;
            }

            // Move zombies if player moved
            if (moved) {
                moveZombies();
            }
        }

        // Final game state
        drawGame();

        // Save score if the player won
        if (playerWon) {
            cout << "Enter your name: ";
            string nameInput;
            getline(cin, nameInput);
            String playerName(nameInput.c_str());  // Assuming you have a String class that accepts const char*
            saveHighScore(playerName);
        }

        cout << "Press Enter to continue...";
        string pause;
        getline(cin, pause);

    }
    // Automated mode
    void playAutomatedMode() {
        gameOver = false;
        playerWon = false;

        // Find the safe zone
        Position safeZonePos;
        bool foundSafeZone = false;
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (cityMap.getCell(Position(x, y)) == SAFE_ZONE) {
                    safeZonePos = Position(x, y);
                    foundSafeZone = true;
                    break;
                }
            }
            if (foundSafeZone) break;
        }

        // Find the path to the safe zone
        Vector<Position> path = cityMap.findPath(playerPos, safeZonePos);

        // Check if a path was found
        if (path.size() <= 1) {
            drawGame();
            cout << "No path to the safe zone found!" << endl;
            cout << "Press Enter to continue...";
            string pause;
            getline(cin, pause);
            return;
        }


        // Game loop - follow the path
        for (int i = 1; i < path.size() && !gameOver; i++) {
            Position nextPos = path[i];
            int dx = nextPos.x - playerPos.x;
            int dy = nextPos.y - playerPos.y;

            // Move the player
            bool moved = movePlayer(dx, dy);

            // Move zombies
            if (moved) {
                moveZombies();
            }

            // Draw the game
            drawGame();

            // Wait for a moment
            cout << "Automatic movement in progress... Press Q to stop." << endl;

            // Check for input to cancel
            cout << "Press Q then Enter to stop automatic movement (or just wait): ";
            string input;
            getline(cin, input);
            if (input == "q" || input == "Q") {
                break;
            }


            // Delay
#ifdef _WIN32
            std::this_thread::sleep_for(std::chrono::seconds(2));
#else
            usleep(500000);  // 500000 microseconds = 500 milliseconds
#endif
        }

        // Final game state
        drawGame();

        // Save score if the player won
        if (playerWon) {
            cout << "Enter your name: ";
            char nameInput[50];
            cin.getline(nameInput, 50);
            String playerName(nameInput);
            saveHighScore(playerName);
        }

        cout << "Press Enter to continue...";
        string temp;
        getline(cin, temp);

    }

public:
    // Constructor
    ZombieGame() {
        // Initialize the game
        cityMap = Graph();
        playerHealth = 100;
        score = 0;
        zombiesEncountered = 0;
        distanceTraveled = 0;
        gameOver = false;
        playerWon = false;
    }

    // Start the game
    void start() {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(nullptr)));

        // Main menu loop
        bool quit = false;
        while (!quit) {
            // Display menu
            clearScreen();

            cout << MAGENTA << "===== ZOMBIE APOCALYPSE SURVIVAL =====" << RESET << endl;
            cout << "1. Start Manual Mode" << endl;
            cout << "2. Start Automated Mode" << endl;
            cout << "3. View High Scores" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            // Get user choice
            string input;
            getline(cin, input);
            char choice = input.empty() ? ' ' : input[0];

            // Process choice
            switch (choice) {
            case '1':
                // Start manual mode
                initializeGame();
                playManualMode();
                break;

            case '2':
                // Start automated mode
                initializeGame();
                playAutomatedMode();
                break;

            case '3':
                // View high scores
                displayHighScores();
                break;

            case '4':
                // Exit
                quit = true;
                break;

            default:
                // Invalid choice
                string dummyInput;

                cout << "Invalid choice! Press Enter to continue...";
                getline(cin, dummyInput);
                break;
            }
        }

        // Goodbye message
        clearScreen();
        cout << MAGENTA << "Thank you for playing Zombie Apocalypse Survival!" << RESET << endl;
    }

    // Initialize the game
    void initializeGame() {
        // Reset game state
        playerHealth = 100;
        score = 0;
        zombiesEncountered = 0;
        distanceTraveled = 0;
        gameOver = false;
        playerWon = false;

        // Generate a random map
        cityMap.generateRandomMap();

        // Find player position
        playerPos = findPlayer();

        // Find zombie positions
        findZombies();

        // Clear zombie queue
        while (!zombieQueue.empty()) {
            zombieQueue.dequeue();
        }

        // Clear player items
        playerItems = ItemList();
    }
};

// Main function
int main() {
    // Create and start the game
    ZombieGame game;
    game.start();

    return 0;
}