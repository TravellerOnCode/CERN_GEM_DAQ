#ifndef GEM_CORE_LAYOUT_TREE_BACKEND_NODES_H
#define GEM_CORE_LAYOUT_TREE_BACKEND_NODES_H

/// @file
/// @brief Defines @ref node classes for components of the backend electronics

#include "gem/core/layout-tree/child_of.h"
#include "gem/core/layout-tree/node.h"
#include "gem/core/layout-tree/parent_mixin.h"

#include <string_view>

namespace gem::core::layout_tree {

/// @defgroup layout_tree_nodes Layout tree nodes
/// @brief Classes that make up nodes of the hardware layout tree.
///
/// Nodes in the layout tree follow the following hierarchy:
///
/// * @ref root_node
///   * @ref crate_node
///     * @ref amc13_node
///     * @ref backend_board_node
///       * @ref link_node
///         * @ref optohybrid_fpga_node
///         * @ref vfat_node
///         * @ref gbt_node
///
/// @{

/// @brief Represents a hardware crate.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// A crate groups an @ref amc13_node "AMC13" and up to 12
/// @ref backend_board_node "backend_boards".
class crate_node : public multiple_child_of<root_node>, public parent_mixin {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "crate";

    /// @brief Minimal constructor.
    explicit crate_node(const parent_ptr<root_node>& parent)
        : multiple_child_of<root_node>(parent)
    {
    }
};

/// @brief Represents an AMC13 card.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// This node has no children.
class amc13_node : public child_of<crate_node> {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "amc13";

    /// @brief Minimal constructor.
    explicit amc13_node(const parent_ptr<crate_node>& parent)
        : child_of<crate_node>(parent)
    {
    }
};

/// @brief Represents a CTP7 or GLIB.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// Direct children of this node are @ref link_node "links".
class backend_board_node : public multiple_child_of<crate_node>, public parent_mixin {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "backend_board";

    /// @brief Minimal constructor.
    explicit backend_board_node(const parent_ptr<crate_node>& parent)
        : multiple_child_of<crate_node>(parent)
    {
    }
};

/// @brief Groups everything that is accessible through an optical link.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// In the GE1/1 world, this can be thought of as the components of a chamber. A
/// complete GE1/1 link has the following children:
///
///  * 1 @ref optohybrid_fpga_node "optohybrid FPGA"
///  * 24 @ref vfat_node "VFATs"
///  * 3 @ref gbt_node "GBTs"
class link_node : public multiple_child_of<backend_board_node>, public parent_mixin {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "link";

    /// @brief Minimal constructor.
    explicit link_node(const parent_ptr<backend_board_node>& parent)
        : multiple_child_of<backend_board_node>(parent)
    {
    }
};

/// @brief Represents the FPGA soldered on OptoHybrid cards.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// This node has no children.
class optohybrid_fpga_node : public child_of<link_node> {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "optohybrid_fpga";

    /// @brief Minimal constructor.
    explicit optohybrid_fpga_node(const parent_ptr<link_node>& parent)
        : child_of<link_node>(parent)
    {
    }
};

/// @brief Represents an individual VFAT.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// This node has no children.
class vfat_node : public multiple_child_of<link_node> {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "vfat";

    /// @brief Minimal constructor.
    explicit vfat_node(const parent_ptr<link_node>& parent)
        : multiple_child_of<link_node>(parent)
    {
    }
};

/// @brief Represents a GBTX.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// This node has no children.
class gbt_node : public multiple_child_of<link_node> {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "gbt";

    /// @brief Minimal constructor.
    explicit gbt_node(const parent_ptr<link_node>& parent)
        : multiple_child_of<link_node>(parent)
    {
    }
};

/// @brief Loads a layout tree from the system configuration.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
///
/// This function recursively searches for files in the @c etc/gem/layout-tree.d
/// folder. All files found in that folder are first concatenated into a single
/// YAML document, then converted to a node tree using the appropriate
/// @ref loader. Concatenation is done in lexicographical order, so files whose
/// name starts with @c a will come before files whose name starts with @c z.
/// This is important when using YAML anchors.
///
/// A possible file naming convention is outlined below. It isn't enforced in
/// any way, and following it or not is up to the operator.
///
/// ~~~
/// gem/layout-tree.d/
///     00-vfat/
///         vfat-0-to-100.yaml
///         vfat-100-to-200.yaml
///         ...
///     10-optohybrid-fpga/
///     30-gbt/
///     40-link/
///     50-backend-board/
///     60-amc13/
///     70-crate/
/// ~~~
///
/// In the folder structure above, we leverage lexicographical sorting to make
/// sure that the VFATs appear at the top of the YAML document; this way, they
/// can be referenced from directories with lower precedence. Since nodes of a
/// given type don't reference other nodes of the same type, the order of files
/// within a subfolder isn't important and we choose human-readable names.
///
/// This function may throw IO-related exceptions, YAML exceptions
/// (@c YAML::Exception and derived classes) or @ref load_error. If no
/// configuration file is found, an empty tree (root node without children) is
/// returned.
std::unique_ptr<root_node> load();

/// @}

} // namespace gem::core::layout_tree

#endif // GEM_CORE_LAYOUT_TREE_BACKEND_NODES_H
