#ifndef GEM_CORE_LAYOUT_TREE_NODE_H
#define GEM_CORE_LAYOUT_TREE_NODE_H

/// @file
/// @brief Defines the @c node class

#include <memory>
#include <string>

namespace gem::core::layout_tree {

/// @brief Nodes are the elements making up the layout tree.
/// @headerfile node.h "gem/core/layout-tree/node.h"
///
/// Every node has a @ref display_name "display name", which is intended to be
/// a short user-provided name. It can also have a @ref uid "unique identifier",
/// which if provided should be unique within GEM.
///
/// The tree structure is defined using @ref parent_mixin and @ref child_of.
class node {
protected:
    /// @brief Constructor.
    explicit node()
    {
    }

public:
    /// @brief Destructor.
    virtual ~node() noexcept {}

    /// @brief Retrieves the user-provided display name of the node.
    const std::string& display_name() const noexcept { return m_display_name; }

    /// @brief Sets the user-provided display name of the node.
    void set_display_name(const std::string& display_name)
    {
        m_display_name = display_name;
    }

    /// @brief Retrieves the identifier of this part (unique with GEM).
    const std::string& uid() const noexcept { return m_uid; }

    /// @brief Sets the identifier of this part (unique with GEM).
    void set_uid(const std::string& uid) { m_uid = uid; }

private:
    std::string m_display_name;
    std::string m_uid;
};

} // namespace gem::core::layout_tree

#endif // GEM_CORE_LAYOUT_TREE_NODE_H
