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

  inline bool intersects(vec3 min_, vec3 max_) {
    if (min.x > max_.x || max.x < min_.x || min.y > max_.y || max.y < min_.y || min.z > max_.z ||
        max.z < min_.z) {
      return false;
    }
    return true;
  };

  inline bool intersects(vec3 min_, vec3 max_) const {
    if (min.x > max_.x || max.x < min_.x || min.y > max_.y || max.y < min_.y || min.z > max_.z ||
        max.z < min_.z) {
      return false;
    }
    return true;
  };
};

struct OctreeNode {
  vec3 minBound, maxBound, midPoint;
  bool isDivided = false;
  int depth = 0;
  int numPoints = 0;
  Point points[OCTREE_CAPACITY];
  AABB aabbs[OCTREE_CAPACITY];

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
  void insert(const vec3& min, const vec3& max, int aabbIndex);

  void clear();

  void query(const vec3& minBound, const vec3& maxBound, std::vector<int>& results) const;

  void numElements();

  // void query(CollisionShape* collision, std::vector<int>& results) const;

  // void setBounds(const BoxCollision& bounds);
};

// }  // namespace physics_lib
#endif
