#include "BVH.h"

void bvh_init_tree( struct BVHTree* tree_ptr, uint32_t max_nodes_count )
{
  ASSERT_F( tree_ptr && max_nodes_count != 0,
           "Invalid input to BVH init: tree_ptr(%s), max_nodes_count(%u)",
           tree_ptr == NULL ? "null" : "valid",
           max_nodes_count );

  tree_ptr->node_bin = (struct BVHNode*)phys_system_alloc( sizeof( struct BVHNode ) * max_nodes_count );
  tree_ptr->data_bin = (struct BVHNodeData*)phys_system_alloc( sizeof( struct BVHNodeData ) * max_nodes_count );

  tree_ptr->active_nodes = 0;

  ASSERT_F( tree_ptr->node_bin && tree_ptr->data_bin,
           "Failed to allocate space for BVH tree" );

  tree_ptr->max_bin_count = max_nodes_count;
}

float bvh_calc_aabb_cost( struct AABBox* bbox )
{
  ASSERT_F( bbox, "Null AABBox parameter" );

  return bbox->m_ExtentsXYZ.x * ( bbox->m_ExtentsXYZ.y + bbox->m_ExtentsXYZ.z ) + bbox->m_ExtentsXYZ.y * bbox->m_ExtentsXYZ.z;
}

float bvh_calc_sphere_cost( struct Sphere* sphere )
{
   ASSERT_F( sphere, "Null Sphere parameter" );

  return sphere->m_Radius * sphere->m_Radius;
}

uint32_t bvh_insert_node( struct BVHTree* tree, struct AABBox* bbox )
{
  ASSERT_F( tree && bbox,
           "Invalid input provided : tree (%s), bbox (%s)",
           tree ? "valid" : "null",
           bbox ? "valid" : "null" );

  ASSERT_F( tree->active_nodes < tree->max_bin_count,
           "BVH tree bin oob exception : %u < %u",
           tree->active_nodes,
           tree->max_bin_count );

  uint32_t node_idx = tree->active_nodes;
  tree->active_nodes++;

  struct BVHNode* leaf = &tree->node_bin[node_idx];
  struct BVHNodeData* leaf_data = &tree->data_bin[node_idx];

  *leaf = ( struct BVHNode ){.id = node_idx, .left_child = -1, .right_child = -1};
  *leaf_data = ( struct BVHNodeData ){.id = node_idx,
                                      .base_type = BVH_TYPE_AABB,
                                      .cached_bbox = *bbox,
                                      .data.aabb = *bbox};

  // Apply 2 rules when inserting nodes into tree:
  // - incremental inheritance cost : cost added to each passed ancestor node
  //	 during hierarchy traversal
  // - object : label of non-leaf node
  //
  // 1. Object && leaf paired under new node :
  //		- applies when pairing object and old root under new root
  //		- incremental inheritance cost -> 2 * cost( insert node )
  // 2. Object added as new child to existing node :
  //		- k = # of active children in node
  //		- insert node cost -> ( k + 1 ) * cost( insert node )
  //		- incremental inheritance cost ->
  //			cost( insert node ) - cost( old node ) ->
  //			k * ( cost( insert node ) - cost( old node ) )
  //			  + cost( insert node )

  return node_idx;
}
