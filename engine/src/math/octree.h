#ifndef MATH_OCTREE_H
#define MATH_OCTREE_H

#include "math_defines.h"
#include <vector>

#define OCTREE_CHILDREN 8
#define OCTREE_MAX_DEPTH 8
#define OCTREE_CAPACITY 5

struct Point {
  int index;
  vec3 position;
};

struct AABB {
  int index;
  vec3 min;
  vec3 max;
};

struct OctreeNode {
  vec3 minBound, maxBound, midPoint;
  bool isDivided = false;
  int depth = 0;
  int numPoints = 0;
  Point points[OCTREE_CAPACITY];

  OctreeNode* children[OCTREE_CHILDREN];
  OctreeNode(float dimension, int d = 0);
  OctreeNode(const vec3& min, const vec3& max, int d = 0);
  ~OctreeNode();
};

class Octree {
public:
  OctreeNode* root;
  Octree();
  Octree(float dimension);

  ~Octree();

  void insert(const vec3& point, int pointIndex);

  void clear();

  void query(const vec3& minBound, const vec3& maxBound, std::vector<int>& results) const;

  void numElements();

  // void query(CollisionShape* collision, std::vector<int>& results) const;

  // void setBounds(const BoxCollision& bounds);
};

// }  // namespace physics_lib
#endif
