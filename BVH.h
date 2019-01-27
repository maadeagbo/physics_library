#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "PhysicsInterface.h"
  enum BVHBaseType
  {
    BVH_TYPE_AABB = 0x1,
    BVH_TYPE_OBB = 0x2,
    BVH_TYPE_SPH = 0x4
  };

  struct BVHNodeData
  {
    int32_t id;
    enum BVHBaseType base_type;

    struct AABBox cached_bbox;
    union
	{
      struct OBBox obb;
      struct AABBox aabb;
      struct Sphere sphere;
    } data;
  };

  struct BVHNode
  {
    int32_t id;
    float node_cost;

    int32_t left_child;
    int32_t right_child;
  };

  struct BVHTree
  {
    struct BVHNode* node_bin;
    struct BVHNodeData* data_bin;

    uint32_t active_nodes;
    uint32_t root_node;
  };

  void bvh_init_tree( struct BVHTree* tree_ptr, uint32_t max_nodes_count );

  // Cost : surface area of aabb (based on projective geometry)
  float bvh_calc_aabb_cost( struct AABBox* bbox );
  float bvh_calc_sphere_cost( struct Sphere* sphere );

  uint32_t bvh_insert_node( struct BVHTree* tree, struct AABBox* bbox );

#ifdef __cplusplus
}
#endif