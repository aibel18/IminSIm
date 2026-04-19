#include "octree.h"
#include "util/logger.h"

OctreeNode::OctreeNode(const vec3& min, const vec3& max, int d)
    : minBound(min), maxBound(max), isDivided(false), depth(d) {
  midPoint = (minBound + maxBound) * 0.5f;
  LOG_DEBUG("constructor octreeNode %p", this);
}

OctreeNode::OctreeNode(float dimension, int d) : isDivided(false), depth(d) {
  minBound = {-dimension, -dimension, -dimension};
  maxBound = {dimension, dimension, dimension};
  midPoint = (minBound + maxBound) * 0.5f;
  LOG_DEBUG("constructor octreeNode %p", this);
}

OctreeNode::~OctreeNode() {
  LOG_DEBUG("Destructor octreeNode %p", this);
}

thread_local int outlierPoints = 0;

inline bool pointInBounds(const vec3& point, const vec3& min, const vec3& max) {
  // SIMD-friendly: restructured for better branch prediction and auto-vectorization
  // Using bitwise & instead of logical && eliminates branching
  const bool x_in = (point.x >= min.x) & (point.x <= max.x);
  const bool y_in = (point.y >= min.y) & (point.y <= max.y);
  const bool z_in = (point.z >= min.z) & (point.z <= max.z);
  return x_in & y_in & z_in;
}

inline int getChildIndex(const vec3& point, const vec3& midPoint) {
  return ((point.x > midPoint.x) ? 1 : 0) | ((point.y > midPoint.y) ? 2 : 0) |
         ((point.z > midPoint.z) ? 4 : 0);
}

void insertOctree(OctreeNode* node, const vec3& point, int pointIndex) {

  if (!node->isDivided) {

    // If there is space in this node, add the point here
    if (node->numPoints < OCTREE_CAPACITY) {
      node->points[node->numPoints].index = pointIndex;
      node->points[node->numPoints].position = {point.x, point.y, point.z};
      node->numPoints++;
      return;
    }

    // If at max depth, consider as outlier and do not insert
    if (node->depth + 1 > OCTREE_MAX_DEPTH) {
      outlierPoints++;
      return;
    }

    // Create children nodes and cache midpoint
    for (int i = 0; i < OCTREE_CHILDREN; ++i) {
      node->children[i] = new OctreeNode(
          {(i & 1) ? node->midPoint.x : node->minBound.x, (i & 2) ? node->midPoint.y : node->minBound.y,
           (i & 4) ? node->midPoint.z : node->minBound.z},
          {(i & 1) ? node->maxBound.x : node->midPoint.x, (i & 2) ? node->maxBound.y : node->midPoint.y,
           (i & 4) ? node->maxBound.z : node->midPoint.z},
          node->depth + 1);
    }
    node->isDivided = true;

    // Redistribute all existing points into children
    for (int i = 0; i < node->numPoints; ++i) {
      const Point& pt = node->points[i];
      int childIdx = getChildIndex(pt.position, node->midPoint);
      insertOctree(node->children[childIdx], pt.position, pt.index);
    }
    node->numPoints = 0;
  }

  // Insert the new point into the appropriate child
  int childIdx = getChildIndex(point, node->midPoint);
  insertOctree(node->children[childIdx], point, pointIndex);
}

void queryOctree(const OctreeNode* node, const vec3& minBound, const vec3& maxBound,
                 std::vector<int>& results) {

  if (minBound.x > node->maxBound.x || maxBound.x < node->minBound.x || minBound.y > node->maxBound.y ||
      maxBound.y < node->minBound.y || minBound.z > node->maxBound.z || maxBound.z < node->minBound.z) {
    return;
  }

  if (node->isDivided) {
    // Manual loop unrolling - eliminates loop overhead and improves instruction cache
    if (node->children[0])
      queryOctree(node->children[0], minBound, maxBound, results);
    if (node->children[1])
      queryOctree(node->children[1], minBound, maxBound, results);
    if (node->children[2])
      queryOctree(node->children[2], minBound, maxBound, results);
    if (node->children[3])
      queryOctree(node->children[3], minBound, maxBound, results);
    if (node->children[4])
      queryOctree(node->children[4], minBound, maxBound, results);
    if (node->children[5])
      queryOctree(node->children[5], minBound, maxBound, results);
    if (node->children[6])
      queryOctree(node->children[6], minBound, maxBound, results);
    if (node->children[7])
      queryOctree(node->children[7], minBound, maxBound, results);
  } else {
    // Check if query fully contains node
    bool fullyContained = (minBound.x <= node->minBound.x && maxBound.x >= node->maxBound.x &&
                           minBound.y <= node->minBound.y && maxBound.y >= node->maxBound.y &&
                           minBound.z <= node->minBound.z && maxBound.z >= node->maxBound.z);

    if (fullyContained) {
      // Add all points without bounds checking
      for (int i = 0; i < node->numPoints; ++i) {
        results.push_back(node->points[i].index);
      }
    } else {
      // Check each point individually
      for (int i = 0; i < node->numPoints; ++i) {
        const vec3& position = node->points[i].position;
        if (pointInBounds(position, minBound, maxBound)) {
          results.push_back(node->points[i].index);
        }
      }
    }
  }
}
/*
void queryOctree(const OctreeNode* node, CollisionShape* collision, std::vector<int>& results) {

  if (!collision->intersects(node->minBound, node->maxBound)) {
    return;
  }

  if (node->isDivided) {
    // Manual loop unrolling - eliminates loop overhead and improves instruction cache
    if (node->children[0])
      queryOctree(node->children[0], collision, results);
    if (node->children[1])
      queryOctree(node->children[1], collision, results);
    if (node->children[2])
      queryOctree(node->children[2], collision, results);
    if (node->children[3])
      queryOctree(node->children[3], collision, results);
    if (node->children[4])
      queryOctree(node->children[4], collision, results);
    if (node->children[5])
      queryOctree(node->children[5], collision, results);
    if (node->children[6])
      queryOctree(node->children[6], collision, results);
    if (node->children[7])
      queryOctree(node->children[7], collision, results);
  } else {
    for (int i = 0; i < node->numPoints; ++i) {
      if (collision->contains(node->points[i].position)) {
        results.push_back(node->points[i].index);
      }
    }
  }
}
//*/

void clearOctree(OctreeNode* node) {
  if (!node)
    return;

  if (node->isDivided) {
    for (int i = 0; i < OCTREE_CHILDREN; ++i) {
      clearOctree(node->children[i]);
      delete node->children[i];
      node->children[i] = nullptr;
    }
    node->isDivided = false;
  }
  node->numPoints = 0;
}

void countPointsInOctree(const OctreeNode* node, int& count, int& leaf, int& depth) {
  if (!node)
    return;

  if (node->isDivided) {
    for (int i = 0; i < OCTREE_CHILDREN; ++i) {
      countPointsInOctree(node->children[i], count, leaf, depth);
    }
  } else {
    count += node->numPoints;
    leaf++;
    depth = std::fmax(node->depth, depth);
    LOG_INFO(">> l: %d n:%d d: %d", leaf, node->numPoints, node->depth);
  }
}

int getOutlierPoints() {
  int outlierPointsCopy = outlierPoints;
  outlierPoints = 0;
  return outlierPointsCopy;
}

Octree::Octree() {
  // TODO: consider dynamically resizing, and adjust the initial dimension based on the world bounds
  root = new OctreeNode(100.0f); // Initialize with a large bounding box
}

Octree::Octree(float dimension) {
  LOG_INFO("Octree constructor");
  root = new OctreeNode(dimension);
}

// Octree::Octree(const BoxCollision& bounds) {
//   root = new OctreeNode(bounds.minBound, bounds.maxBound);
// }

Octree::~Octree() {
  clearOctree(root);
  delete root;
  root = nullptr;
  LOG_INFO("Octree destroyed. Total outlier points during lifetime: %d", getOutlierPoints());
}

void Octree::insert(const vec3& point, int pointIndex) {
  insertOctree(root, point, pointIndex);
}

// void Octree::insertBatch(const vec3* points, const int* indices, size_t count) {
//   for (size_t i = 0; i < count; ++i) {
//     insertOctree(root, points[i], indices[i]);
//   }
// }

void Octree::clear() {
  outlierPoints = 0;
  clearOctree(root);
}

void Octree::query(const vec3& minBound, const vec3& maxBound, std::vector<int>& results) const {
  queryOctree(root, minBound, maxBound, results);
}

void Octree::numElements() {
  int count = 0;
  int leaf = 0;
  int depth = 0;
  countPointsInOctree(root, count, leaf, depth);
  LOG_INFO("[Octree] points: %d leafs: %d depth: %d", count, leaf, depth);
}

// void Octree::query(CollisionShape* collision, std::vector<int>& results) const {
//   queryOctree(root, collision, results);
// }
