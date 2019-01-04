#include "BVH.h"

#include "stretchy_buffer.h"

void bvh_init_tree( struct BVHTree* tree_ptr, uint32_t max_nodes_count )
{
    assertf( tree_ptr && max_nodes_count != 0,
             "Invalid input to BVH init: tree_ptr(%s), max_nodes_count(%u)",
             tree_ptr == NULL ? "null" : "valid",
             max_nodes_count );

    sb_add( tree_ptr->node_bin, (int)max_nodes_count );
    sb_add( tree_ptr->data_bin, (int)max_nodes_count );

	tree_ptr->active_nodes = 0;

    assertf( tree_ptr->node_bin && tree_ptr->data_bin,
             "Failed to allocate space for BVH tree" );
}

float bvh_calc_aabb_cost( struct AABBox* bbox )
{
    assertf( bbox, "Null AABBox parameter" );

    return bbox->extents_xyz.x * ( bbox->extents_xyz.y + bbox->extents_xyz.z ) +
           bbox->extents_xyz.y * bbox->extents_xyz.z;
}

float bvh_calc_sphere_cost( struct Sphere* sphere )
{
	assertf( sphere, "Null Sphere parameter" );

	return sphere->radius * sphere->radius;
}

uint32_t bvh_insert_node( struct BVHTree* tree, struct AABBox* bbox )
{
    assertf( tree && bbox,
             "Invalid input provided : tree (%s), bbox (%s)",
             tree ? "valid" : "null",
             bbox ? "valid" : "null" );

    assertf( tree->active_nodes < (uint32_t)sb_count( tree->node_bin ),
             "BVH tree bin oob exception : %u < %u",
             tree->active_nodes,
             (uint32_t)sb_count( tree->node_bin ) );

    uint32_t node_idx = tree->active_nodes;
    tree->active_nodes++;

    struct BVHNode* leaf = &tree->node_bin[node_idx];
	struct BVHNodeData* leaf_data = &tree->data_bin[node_idx];
    *leaf = ( struct BVHNode ){
            .id = node_idx, .left_child = -1, .right_child = -1};
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