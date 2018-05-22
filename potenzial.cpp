#include <bits/stdc++.h>
using namespace std;

int suppliersAmmount;
int consumersAmmount;
vector < vector <int> > costArr;
vector < vector <int> > finalArr;
bool pathFinderEnd = false;
struct vertex {
  int x;
  int y;
};
vector <vertex> finalPath;

bool pathFinder (vector <vertex> currentPath, int previousPath, vertex currVertex) {
  vertex nextVertex;
  //up
  if (previousPath != 1)
    for (int i = 0; i < currVertex.x; ++i) {
      if (finalArr[i][currVertex.y] != -1) {
        if (currentPath[0].x == i && currentPath[0].y == currVertex.y) {
          pathFinderEnd = true;
          finalPath = currentPath;
          return true;
        }
        nextVertex.x = i;
        nextVertex.y = currVertex.y;
        vector <vertex> tempPath = currentPath;
        tempPath.push_back(nextVertex);
        if (pathFinder(tempPath, 1, nextVertex))
          return true;

      }
    }
  //down
  if (previousPath != 1)
    for (int i = suppliersAmmount - 1; i > currVertex.x; --i) {
      if (finalArr[i][currVertex.y] != -1) {
        if (currentPath[0].x == i && currentPath[0].y == currVertex.y) {
          pathFinderEnd = true;
          finalPath = currentPath;
          return true;
        }
        nextVertex.x = i;
        nextVertex.y = currVertex.y;
        vector <vertex> tempPath = currentPath;
        tempPath.push_back(nextVertex);
        if (pathFinder(tempPath, 1, nextVertex))
          return true;
      }
    }
  //left
  if (previousPath != 2)
    for (int j = 0; j < currVertex.y; ++j) {
      if (finalArr[currVertex.x][j] != -1) {
        if (currentPath[0].x == currVertex.x && currentPath[0].y == j) {
          pathFinderEnd = true;
          finalPath = currentPath;
          return true;
        }
        nextVertex.x = currVertex.x;
        nextVertex.y = j;
        vector <vertex> tempPath = currentPath;
        tempPath.push_back(nextVertex);
        if (pathFinder(tempPath, 2, nextVertex))
          return true;
      }
    }
  //right
  if (previousPath != 2)
    for (int j = consumersAmmount - 1; j > currVertex.y; --j) {
      if (finalArr[currVertex.x][j] != -1) {
        if (currentPath[0].x == currVertex.x && currentPath[0].y == j) {
          pathFinderEnd = true;
          finalPath = currentPath;
          return true;
        }
        nextVertex.x = currVertex.x;
        nextVertex.y = j;
        vector <vertex> tempPath = currentPath;
        tempPath.push_back(nextVertex);
        if (pathFinder(tempPath, 2, nextVertex))
          return true;
      }
    }
  return false;
}

int main() {
  vector<int> suppliers;
  vector<int> consumers;

  ifstream ist("input.txt");
  ist >> suppliersAmmount >> consumersAmmount;
  int temp;
  int suppliersCheck = 0, consumersCheck = 0;
  for (int i = 0; i < suppliersAmmount; ++i) {
    ist >> temp;
    suppliersCheck += temp;
    suppliers.push_back(temp);
  }
  for (int i = 0; i < consumersAmmount; ++i) {
    ist >> temp;
    consumersCheck += temp;
    consumers.push_back(temp);
  }
  if (consumersCheck != suppliersCheck) {
    cout << "Data input error: needs dont equal to holdings";
    exit(0);
  }

  costArr.resize(suppliersAmmount);
  for (int i = 0; i < suppliersAmmount; ++i)
    costArr[i].resize(consumersAmmount);
  int tempCostArr[suppliersAmmount][consumersAmmount];
  for (int i = 0; i < suppliersAmmount; ++i)
    for (int j = 0; j < consumersAmmount; ++j) {
      ist >> costArr[i][j];
      tempCostArr[i][j] = costArr[i][j];
    }


  /*for (int i = 0; i < suppliersAmmount; ++i) {
      for (int j = 0; j < consumersAmmount; ++j)
          cout << costArr[i][j] << " ";
      cout << endl;
  }*/

  finalArr.resize(suppliersAmmount);
  for (int i = 0; i < suppliersAmmount; ++i)
    finalArr[i].resize(consumersAmmount);
  for (int i = 0; i < suppliersAmmount; ++i)
    for (int j = 0; j < consumersAmmount; ++j)
      finalArr[i][j] = 0;

  int potentialStepCntr = 1;
  while (true) {
    int remI, remJ, mini = 1E10;
    for (int i = 0; i < suppliersAmmount; ++i) {
      for (int j = 0; j < consumersAmmount; ++j) {
        if ((tempCostArr[i][j] < mini) && (tempCostArr[i][j] >= 0)) {
          mini = tempCostArr[i][j];
          remI = i;
          remJ = j;
        }
      }
    }
    if (suppliers[remI] >= consumers[remJ]) {
      finalArr[remI][remJ] = consumers[remJ];
      suppliers[remI] -= consumers[remJ];
      consumers[remJ] = 0;
    } else {
      finalArr[remI][remJ] = suppliers[remI];
      consumers[remJ] -= suppliers[remI];
      suppliers[remI] = 0;
    }
    tempCostArr[remI][remJ] = -1;
    int cntr = 0;
    for (int i = 0; i < suppliersAmmount; ++i) {
      if (suppliers[i] == 0)
        cntr++;
    }
    if (cntr == suppliersAmmount)
      break;
  }
  int finalScore = 0;
  for (int i = 0; i < suppliersAmmount; ++i)
    for (int j = 0; j < consumersAmmount; ++j)
      finalScore += finalArr[i][j] * costArr[i][j];

  cout << "Current Cost: " << finalScore << endl;

  //******************************************Potential
  cout << "Starting potential method..." << endl;
  int uArr[suppliersAmmount];
  for (int i = 0; i < suppliersAmmount; ++i)
    uArr[i] = -10000;
  int vArr[consumersAmmount];
  for (int i = 0; i < consumersAmmount; ++i)
    vArr[i] = -10000;
  int uCount = 0;
  int vCount = 0;


  int tempRow = -1;
  int maxElemInRow = -1;


  cout << "Final array: " << endl;
  for (int i = 0; i < suppliersAmmount; ++i) {
    for (int j = 0; j < consumersAmmount; ++j) {
      if (finalArr[i][j] == 0)
        finalArr[i][j] = -1;
      cout << setw(3) << finalArr[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;


  //********************************Potential computing started
  while (true) {
    for (int i = 0; i < suppliersAmmount; ++i) {
      int cntr = 0;
      for (int j = 0; j < consumersAmmount; ++j)
        if (finalArr[i][j] != -1)
          cntr++;
      if (cntr >= maxElemInRow) {
        maxElemInRow = cntr;
        tempRow = i;
      }
    }
    uArr[tempRow] = 0;
    while (uCount != suppliersAmmount && vCount != consumersAmmount) {
      bool smthChanged = 0;
      for (int i = 0; i < suppliersAmmount; ++i) {
        if (uArr[i] != -10000)
            for (int j = 0; j < consumersAmmount; ++j) {
            if ((finalArr[i][j] != -1) && (vArr[j] == -10000)) {
              vArr[j] = costArr[i][j] - uArr[i];
              smthChanged = 1;
              vCount++;
            }
          }
      }

      for (int j = 0; j < consumersAmmount; ++j) {
        if (vArr[j] != -10000)
          for (int i = 0; i < suppliersAmmount; ++i) {
            if ((finalArr[i][j] != -1) && (uArr[i] == -10000)) {
              uArr[i] = costArr[i][j] - vArr[j];
              smthChanged = 1;
              uCount++;
            }
            /*cout << "uArr:" << endl;
            for (int i = 0; i < suppliersAmmount; ++i)
              cout << uArr[i] << " ";
            cout << endl;
            cout << "vArr:" << endl;
            for (int i = 0; i < consumersAmmount; ++i)
              cout << vArr[i] << " ";
            cout << endl << endl;*/
          }
      }

      if (smthChanged == 0) {
        //find empty row and column
        int remI = 0;
        int remJ = 0;
        for (int i = 0; i < suppliersAmmount; ++i)
          if (uArr[i] == -10000)
            for (int j = 0; j < consumersAmmount; ++j)
              if (vArr[j] == -10000) {
                remI = i;//down
                remJ = j;
              }

        //find minimum element
        int rem2I = remI;
        int rem2J = remJ;
        int minCost = 10000;
        for (int i = 0; i < suppliersAmmount; ++i) {
          if ((costArr[i][remJ] < minCost) && (finalArr[i][remJ] == -1)) {
            minCost = costArr[i][remJ];
            rem2I = i;
          }
        }
        for (int j = 0; j < consumersAmmount; ++j) {
          if ((costArr[remI][j] < minCost) && (costArr[remI][j] == -1)) {
            minCost = costArr[remI][j];
            rem2J = j;
          }
        }
        finalArr[rem2I][rem2J] = 0;
      }
      cout << "Step " << potentialStepCntr++ << ":" << endl;
      cout << "uArr:" << endl;
      for (int i = 0; i < suppliersAmmount; ++i)
        cout << uArr[i] << " ";
      cout << endl;
      cout << "vArr:" << endl;
      for (int i = 0; i < consumersAmmount; ++i)
        cout << vArr[i] << " ";
      cout << endl << endl;
    }


    //Optimize
    //Making array
    int cArr[suppliersAmmount][consumersAmmount];
    int minimumC = -1;
    int remI = 0, remJ = 0;
    int checkC = 0;
    for (int i = 0; i < suppliersAmmount; ++i) {
      for (int j = 0; j < consumersAmmount; ++j) {
        cArr[i][j] =  costArr[i][j] - (uArr[i] + vArr[j]);
        if (cArr[i][j] <= minimumC) {
          remI = i;
          remJ = j;
          minimumC = cArr[i][j];
          checkC++;
        }
      }
    }

    //Check for end
    if (checkC == 0) {
      cout << "Final array: " << endl;
      for (int i = 0; i < suppliersAmmount; ++i) {
        for (int j = 0; j < consumersAmmount; ++j)
          cout << setw(3) << finalArr[i][j] << " ";
        cout << endl;
      }
      cout << endl;
      cout << "uArr:" << endl;
      for (int i = 0; i < suppliersAmmount; ++i)
        cout << uArr[i] << " ";
      cout << endl;
      cout << "vArr:" << endl;
      for (int i = 0; i < consumersAmmount; ++i)
        cout << vArr[i] << " ";
      cout << endl << endl;
      break;
    }
    //PathFinder
    finalPath.clear();
    struct vertex firstVertex;
    firstVertex.x = remI;
    firstVertex.y = remJ;
    finalPath.push_back(firstVertex);
    if (finalArr[remI][remJ] == -1) {
      finalArr[remI][remJ] = -2;
    }
    pathFinder(finalPath, -1, firstVertex);
    if (finalArr[remI][remJ] == -2) {
      finalArr[remI][remJ] = -1;
    }
    cout << "Final array: " << endl;
      for (int i = 0; i < suppliersAmmount; ++i) {
        for (int j = 0; j < consumersAmmount; ++j)
          cout << setw(3) << finalArr[i][j] << " ";
        cout << endl;
      }
    cout << "Found next path (x, y): " << endl;
    for (int i = 0; i < finalPath.size(); ++i) {
      cout << finalPath[i].x << " " << finalPath[i].y << endl;
    }
    cout << endl;

    //Plus-minus
    int minusMinimum = finalArr[finalPath[1].x][finalPath[1].y];
    for (int i = 3; i < finalPath.size(); i += 2) {
      minusMinimum = min(minusMinimum, finalArr[finalPath[i].x][finalPath[i].y]);
    }
    for (int i = 0; i < finalPath.size(); ++i) {
      if (finalArr[finalPath[i].x][finalPath[i].y] == -1)
        finalArr[finalPath[i].x][finalPath[i].y] = 0;
      else
      if (finalArr[finalPath[i].x][finalPath[i].y] == 0 && minusMinimum == 0)
        finalArr[finalPath[i].x][finalPath[i].y] = -1;
      if (i % 2 == 0)
        finalArr[finalPath[i].x][finalPath[i].y] += minusMinimum;
      else
        finalArr[finalPath[i].x][finalPath[i].y] -= minusMinimum;
    }
    cout << "Final array after distribution: " << endl;
      for (int i = 0; i < suppliersAmmount; ++i) {
        for (int j = 0; j < consumersAmmount; ++j)
          cout << setw(3) << finalArr[i][j] << " ";
        cout << endl;
      }
    //reseting u, v
    for (int i = 0; i < suppliersAmmount; ++i)
      uArr[i] = -10000;
    for (int i = 0; i < consumersAmmount; ++i)
      vArr[i] = -10000;
    uCount = 0;
    vCount = 0;
    potentialStepCntr = 1;
    tempRow = -1;
    maxElemInRow = -1;
  }
  finalScore = 0;
  for (int i = 0; i < suppliersAmmount; ++i)
    for (int j = 0; j < consumersAmmount; ++j)
      if (finalArr[i][j] != -1)
        finalScore += finalArr[i][j] * costArr[i][j];
  cout << "Potential Computed" << endl;
  cout << "Final Score: " << finalScore;

  return 0;
}
