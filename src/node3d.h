#ifndef NODE3D_H
#define NODE3D_H

#include <cmath>

#include "nav_msgs/OccupancyGrid.h"

#include "dubins.h"
#include "node2d.h"

struct cfg;

class Node3D {
 public:
  // CONSTRUCTOR
  Node3D(int x, int y, float t, float g, float h, Node3D* pred) {
    this->x = x;
    this->y = y;
    this->t = t;
    this->g = g;
    this->h = h;
    this->pred = pred;
  }
  // GETTER METHODS
  int getX() const { return x; }
  int getY() const { return y; }
  float getT() const { return t; }
  float getG() const { return g; }
  float getH() const { return h; }
  Node3D* getPred() const { return pred; }
  // returns total estimated cost for node
  float getC() const { return g + h; }

  // SETTER METHODS
  void setX(const int& x) { this->x = x; }
  void setY(const int& y) { this->y = y; }
  void setT(const float& t) { this->t = t; }
  void setG(const float& g) { this->g = g; }
  void setH(const float& h) { this->h = h; }
  void setPred(Node3D* pred) { this->pred = pred; }

  // UPDATE METHODS
  // from start
  void updateG(const Node3D& pred) { g += movementCost(pred); }
  // to goal
  void updateH(const Node3D& goal, const nav_msgs::OccupancyGrid::ConstPtr& grid,
               float costGoal[]) { h = costToGo(goal, grid, costGoal); }
  // COST CALCULATION
  // cost for movement, g
  float movementCost(const Node3D& pred) const;
  // cost to go, dubins path / 2D A*
  float costToGo(const Node3D& goal,
                 const nav_msgs::OccupancyGrid::ConstPtr& oGrid, float costGoal[]) const;
  //  aStar algorithm
  static Node3D* aStar(Node3D& start, const Node3D& goal,
                       const nav_msgs::OccupancyGrid::ConstPtr& oGrid);
  // CONSTANT VALUES
  // possible directions
  static const int dir;
  // possible movements
  static const int dx[];
  static const int dy[];
  static const int dt[];
 private:
  // x = position (length), y = position (width), t = heading, g = cost, h = cost to go, pred = pointer to predecessor node
  int x;
  int y;
  float t;
  float g;
  float h;
  Node3D* pred;
};

////###################################################
////                                  CONST DECLARATION
////###################################################
///*
//    HEADING => 0 - 359 degrees, 0 being north pointing towards negative X
//    X-COORDINATE => designating the length of the grid/world
//    Y-COORDINATE => designating the width of the grid/world
//*/

//// PATH TRACE
//bool path[length][width];
//int pathClosed[length][width];
//// ALGORITHM LISTS
//// 2D
//bool listOpen2D[length][width];
//bool listClosed2D[length][width];
//float listCost2D[length][width];
//float listCostToGo2D[length][width];
//float listCostGoal2D[length][width];

//// USER CHOICE
//bool penalty = true;
//bool dubins = true;
//bool twoD = true;

#endif // NODE3D_H