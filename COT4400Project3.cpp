// Celina Vo u92686024
// COT4400 Project 3

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>

struct Point{   // represents (row, column) coordinate in graph
    int r;
    int c;
};
bool operator ==(const Point& p1, const Point& p2){
    return (p1.r == p2.r) && (p1.c == p2.c);
}

// functions getColor and getDirection are used to access the information stored within that location of the graph
int getColor(Point p, std::vector <std::vector<std::string> > graph){   // RED = 0, BLUE = 1
    if (graph[p.r][p.c].find('R') != std::string::npos){
        return 0;
    }
    else return 1;
}
int getDirection(Point p, std::vector <std::vector<std::string> > graph){   // E=1, W=2, S=3, N=4, SE=5, SW=6, NE=7, NW=8
    // std::cout << graph[p.r][p.c] << std::endl;
    if (graph[p.r][p.c].find('E') != std::string::npos){
        if (graph[p.r][p.c].find('S') != std::string::npos) return 5;
        else if (graph[p.r][p.c].find('N') != std::string::npos) return 7;
        else return 1;
    } else if (graph[p.r][p.c].find('W') != std::string::npos){
        if (graph[p.r][p.c].find('S') != std::string::npos) return 6;
        else if (graph[p.r][p.c].find('N') != std::string::npos) return 8;
        else return 2;
    } else if (graph[p.r][p.c].find('S') != std::string::npos) return 3;
    else if (graph[p.r][p.c].find('N') != std::string::npos) return 4;
    else return 0;
}

// functions to examine directions (check for endpoint when looking E, S, and SE); these are responsible for creating the adjacency lists to represent edges of a vertex
std::vector <Point> getEast(Point p, Point end, std::vector <std::vector<std::string> > graph){         // get vector of all possible next nodes to the East (check for endpoint)
    std::vector <Point> eastNodes;
    std::vector <std::string> row = graph[p.r];
    int currentColor = getColor(p, graph);
    for (int i = p.c; i < row.size(); i++){
        Point temp = {p.r, i};
        if ((temp.r == end.r) && (temp.c == end.c)){    // check for endpoint
            eastNodes.clear();
            eastNodes.push_back(temp); 
            return eastNodes;
        }
        // std::cout << row[i] << " color: " << getColor(temp, graph) <<std::endl;
        if (getColor(temp, graph) != currentColor){
            eastNodes.push_back(temp);
        }
    }
    return eastNodes;
}

std::vector <Point> getWest(Point p, Point end, std::vector <std::vector<std::string> > graph){         // get vector of all possible next nodes to the West
    std::vector <Point> westNodes;
    std::vector <std::string> row = graph[p.r];
    int currentColor = getColor(p, graph);
    for (int i = p.c; i > -1; i--){
        Point temp = {p.r, i};
        if (getColor(temp, graph) != currentColor){
            westNodes.push_back(temp);
        }
    }
    return westNodes;
}

std::vector <Point> getSouth(Point p, Point end, std::vector <std::vector<std::string> > graph){        // get vector of all possible next nodes to the South (check for endpoint)
    std::vector <Point> southNodes;
    int currentColor = getColor(p, graph);
    for (int i = p.r; i < (end.r + 1); i++){
        Point temp = {i, p.c};
        if ((temp.r == end.r) && (temp.c == end.c)){    // check for endpoint
            southNodes.clear();
            southNodes.push_back(temp); 
            return southNodes;
        }
        if (getColor(temp, graph) != currentColor){
            southNodes.push_back(temp);
        }
    }
    return southNodes;
}

std::vector <Point> getNorth(Point p, Point end, std::vector <std::vector<std::string> > graph){        // get vector of all possible next nodes to the North
    std::vector <Point> northNodes;
    int currentColor = getColor(p, graph);
    for (int i = p.r; i > -1; i--){
        Point temp = {i, p.c};
        if (getColor(temp, graph) != currentColor){
            northNodes.push_back(temp);
        }
    }
    return northNodes;
}

std::vector <Point> getSouthEast(Point p, Point end, std::vector <std::vector<std::string> > graph){    // get vector of all possible next nodes to the SouthEast (check for endpoint)
    std::vector <Point> southEastNodes;
    int currentColor = getColor(p, graph);
    for (int curRow = p.r, curCol = p.c; curRow < (end.r + 1) && curCol < (end.c + 1); curRow++, curCol++){
        Point temp = {curRow, curCol};
        if ((temp.r == end.r) && (temp.c == end.c)){    // check for endpoint
            southEastNodes.clear();
            southEastNodes.push_back(temp); 
            return southEastNodes;
        }
        if (getColor(temp, graph) != currentColor){
            southEastNodes.push_back(temp);
        }
    }
    return southEastNodes;
}

std::vector <Point> getSouthWest(Point p, Point end, std::vector <std::vector<std::string> > graph){    // get vector of all possible next nodes to the SouthWest
    std::vector <Point> southWestNodes;
    int currentColor = getColor(p, graph);
    for (int curRow = p.r, curCol = p.c; curRow < (end.r + 1) && curCol > -1; curRow++, curCol --){
        Point temp = {curRow, curCol};
        if (getColor(temp, graph) != currentColor){
            southWestNodes.push_back(temp);
        }
    }
    return southWestNodes;
}

std::vector <Point> getNorthEast(Point p, Point end, std::vector <std::vector<std::string> > graph){    // get vector of all possible next nodes to the NorthEast
    std::vector <Point> northEastNodes;
    int currentColor = getColor(p, graph);
    for (int curRow = p.r, curCol = p.c; curRow > -1 && curCol < (end.c + 1); curRow--, curCol++){
        Point temp = {curRow, curCol};
        if (getColor(temp, graph) != currentColor){
            northEastNodes.push_back(temp);
        }
    }
    return northEastNodes;
}

std::vector <Point> getNorthWest(Point p, Point end, std::vector <std::vector<std::string> > graph){    // get vector of all possible next nodes to the NorthWest
    std::vector <Point> northWestNodes;
    int currentColor = getColor(p, graph);
    for (int curRow = p.r, curCol = p.c; curRow > -1 && curCol > -1; curRow--, curCol--){
        Point temp = {curRow, curCol};
        if (getColor(temp, graph) != currentColor){
            northWestNodes.push_back(temp);
        }
    }
    return northWestNodes;
}

std::vector <Point> getChildren(Point p, Point end, std::vector <std::vector<std::string> > graph){     // gets all the possible next locations from a point
    int direction = getDirection(p, graph);
    std::vector <Point> children;
    if (direction == 1) children = getEast(p, end, graph);
    else if (direction == 2) children = getWest(p, end, graph);
    else if (direction == 3) children = getSouth(p, end, graph);
    else if (direction == 4) children = getNorth(p, end, graph);
    else if (direction == 5) children = getSouthEast(p, end, graph);
    else if (direction == 6) children = getSouthWest(p, end, graph);
    else if (direction == 7) children = getNorthEast(p, end, graph);
    else children = getNorthWest(p, end, graph);
    return children;
}

bool isIn(Point p, std::vector <Point> container){  //helper function to determine whether an element is in a container
    for (int i = 0; i < container.size(); i++){
        if (p == container[i]) return 1;
    }
    return 0;
}

// backtracking algorithm that performs DFS search of graph.
std::vector <Point> findSolution(Point p, Point end, std::vector <std::vector<std::string> > graph, std::vector <Point> path = {}){
    path.push_back(p);  // add current node to path
    std::vector<Point> nextNodes = getChildren(p, end, graph);  // get all edges of the vertex

    // test code
    // std::cout << "Current: " << "(" << p.r << ", " << p.c << ") ";
    // for (int i = 0; i < nextNodes.size(); i++){
    //     std::cout << "Children: " << "(" << nextNodes[i].r << ", " << nextNodes[i].c << ") " << getDirection(nextNodes[i], graph) << " D ";
    // }
    // std::cout << std:: endl;

    if (nextNodes.empty()) return {};  // If the node has no children, it's a dead end.
    for (int i = 0; i < nextNodes.size(); i++) {
        if (isIn(end, path)) return path;  // Once the endpoint has been found, stop computing.
        if (nextNodes[i] == end) {  // if child leads to endpoint
            path.push_back(end);
            return path;
        }
        else {
            if (!isIn(nextNodes[i], path)) {    // if child is not already in recorded path
                std::vector<Point> returnedPath = findSolution(nextNodes[i], end, graph, path);
                if (!returnedPath.empty()) return returnedPath; // if not a dead end, return path
            }
        }
    }
    return {};  // return empty path if no solution is found.
}

std::string convertToPath(Point start, Point end, std::vector <std::vector<std::string> > graph){   // converts two points into number of steps and direction
    std::string stringPath;
    int steps;
    // calculate distance between points
    if (start.r == end.r) steps = abs(start.c - end.c);
    else if (start.c == end.c) steps = abs(start.r - end.r);
    else steps = abs(start.r - end.r);
    stringPath.append(std::to_string(steps));

    int direction = getDirection(start, graph);
    // E=1, W=2, S=3, N=4, SE=5, SW=6, NE=7, NW=8
    if (direction == 1) stringPath.append("E ");
    else if (direction == 2) stringPath.append("W ");
    else if (direction == 3) stringPath.append("S ");
    else if (direction == 4) stringPath.append("N ");
    else if (direction == 5) stringPath.append("SE ");
    else if (direction == 6) stringPath.append("SW ");
    else if (direction == 7) stringPath.append("NE ");
    else if (direction == 8) stringPath.append("NW ");
    else stringPath.append("ERROR");
    // std::cout << stringPath;

    return stringPath;
}
std::string outputText(std::vector <Point> solution, std::vector <std::vector<std::string> > graph){    // strings together the path sequence for output file
    std::string outputText;
    for (int i = 0; i < solution.size() - 1; i++){
        Point start = solution[i];
        Point j = solution [i+1];
        outputText.append(convertToPath(start, j, graph));
    }
    return outputText;
}

int main(){
    //file input
    std::ifstream readFile;
    std::string line;
    std::string fileName;

    std::cout << "Enter file name: ";
    std::cin >> fileName;

    std::vector <std::string> row;
    std::vector <std::vector<std::string> > graph;
    int rows;
    int columns;

    readFile.open(fileName);
    if (readFile.is_open()){ 
        while(getline(readFile, line)){
            // std::cout << line << std::endl;
            if (line.size() == 3){ // get the size of the array
                rows = int(line[0]) - 48;
                columns = int(line[2]) - 48;
                // std::cout << rows << ", " << columns << std::endl;
            }
            else{
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) row.push_back(word);
                graph.push_back(row);
                row.clear();
                // for (const auto& w : row) std::cout << w << std::endl;
                // std::cout << "Row complete" << std::endl; // test code
            }
        }
    }
    else {
        std::cout << "Failed to find input file.";
        return 1;
    }
    readFile.close();

    // starting and end points of graph
    Point start = {0,0};
    Point end = {rows - 1, columns - 1};
    if (graph[end.r][end.c].find('O') == std::string::npos){    // determines if graph is valid, meaning goal in bottom right corner
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    // //test code
    // std::cout << "Currently looking at: " << graph[start.r][start.c] << std::endl;

    // compute the solution of the graph
    std::vector <Point> solution;
    solution = findSolution(start, end, graph);
    //test code
    // for (int i = 0; i < solution.size(); i++){
    //     std::cout << "(" << solution[i].r << ", " << solution[i].c << ") " << " : ";
    // }

    // write solution to output file
    std::string text = outputText(solution, graph);
    // std::cout << text << std::endl;
    std::ofstream writeFile;
    writeFile.open("output.txt");
    if (writeFile.is_open()){
        writeFile << text;
        std::cout << "Solution written to output.txt" << std::endl;
    } else {
        std::cout << "Error opening writeFile" << std::endl;
        return 1;
    }
}