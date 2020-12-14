#ifndef GEM_CORE_LAYOUT_TREE_CHILD_OF_H
#define GEM_CORE_LAYOUT_TREE_CHILD_OF_H

/// @file
/// @brief Defines the @c child_of class

#include <algorithm>
#include <memory>

#include "gem/core/layout-tree/parent_mixin.h"
#include <iostream>
namespace gem::core::layout_tree {

/// @brief Wrapper used to enforce the use of create_child()
/// @headerfile child_of.h "gem/core/layout-tree/child_of.h"
///
/// This class works like a smart pointer to an object of type @c T, except that
/// it doesn't manage the lifetime of the stored pointer.
template <class T>
class parent_ptr {
public:
    /// @brief Dereferences the stored pointer
    T& operator*() const noexcept { return *m_ptr; }

    /// @brief Dereferences the stored pointer
    T* operator->() const noexcept { return m_ptr; }

    /// @brief Returns the stored pointer
    T* get() const noexcept { return m_ptr; }

    /// @brief Checks that the stored pointer is null
    bool operator==(std::nullptr_t) const { return m_ptr == nullptr; }

    /// @brief Checks that the stored pointer is not null
    bool operator!=(std::nullptr_t) const { return m_ptr != nullptr; }

private:
    // create_child is the only function able to create this class
    template <class U, class... Args>
    friend U* create_child(typename U::parent_type*, Args&&...);

    // Constructor, only usable from create_child
    explicit parent_ptr(T* pointer)
        : m_ptr(pointer)
    {
    }

    T* m_ptr;
};

/// @brief Tags a node type as being a child_of
class child_node_tag {
};

#if !IS_DOXYGEN
// Undefined class for SFINAE purposes, see specialization
template <class T, class U = std::enable_if_t<std::is_base_of_v<parent_mixin, T>, void>>
class child_of;
#endif

/// @brief Allows the declaration of child nodes
/// @headerfile child_of.h "gem/core/layout-tree/child_of.h"
///
/// Child nodes keep a reference to their parent, accessible using the @ref parent
/// function. The parent is set at construction time (by create_child()) and cannot
/// be changed afterwards.
///
/// @c child_of allows only one child of a given type in a parent. Use
/// @ref multiple_child_of if multiple childs of the same type should be allowed.
///
/// @note While the uniqueness is currently not checked, it will be in the
///       future.
///
/// ### Subclassing
///
/// Subclasses must provide a constructor taking a
/// <TT>const parent_ptr<parent_type>&</TT> as its first argument, and forward it to
/// the base class constructor. This enables the use of create_child(). A typical
/// subclass will be declared as follows:
///
/// ~~~{.cpp}
/// class parent_node: public node, public parent_mixin {};
/// class child_node: public child_of<parent_node> {
/// public:
///     explicit child_node(const parent_ptr<parent_node>& parent, int param)
///         : child_of<parent_node>(parent)
///         , m_param(param)
///     {
///     }
/// private:
///     int m_param;
/// };
/// ~~~
///
/// Note that since @c child_of already inherits @ref node, there is no need to
/// specify it explicitly.
///
/// Some features (mainly serialization) require a @c node_name public string
/// attribute, typically declared as:
///
/// ~~~{.cpp}
/// inline constexpr static std::string_view node_name = "name";
/// ~~~
#if IS_DOXYGEN
template <class T>
class child_of : public node {
#else
template <class T>
class child_of<T, void> : public node, public child_node_tag {
#endif

public:
    /// @brief The type of the parent node
    using parent_type = T;

    /// @brief Retrieves the parent of a node
    ///
    /// The pointer remains valid as long as the root of the tree is not destroyed.
    /// The returned pointer is null if a parent wasn't set in the constructor.
    parent_type* parent() const { return m_parent; }

protected:
    /// @brief Constructor
    /// @param parent The future parent of this node.
    /// @note The only way to get a value suitable for @c parent is using the
    ///       create_child() function.
    explicit child_of(const parent_ptr<parent_type>& parent)
        : m_parent(parent.get())
    {
    }

private:
    // The parent owns the child, so no need for a smart pointer.
    parent_type* const m_parent;
};

/// @brief Tags a node type as being a multiple_child_of
class multiple_child_node_tag {
};

/// @brief Allows several child nodes of the same type to be added to the same
///        parent
/// @headerfile child_of.h "gem/core/layout-tree/child_of.h"
///
/// Multiple children must be @ref number "numbered". The numbering scheme is
/// user-defined, but not two children of the same type and same parent node can
/// have the same number.
///
/// @note While the uniqueness is currently not checked, it will be in the
///       future.
///
/// This class is used in the same way as @ref child_of.
template <class T>
class multiple_child_of : public child_of<T>, public multiple_child_node_tag {
public:
    /// @brief The type of the parent node
    using parent_type = T;

    /// @brief Retrieves the logical number of a node within its parent.
    /// @see set_number
    std::size_t number() const { return m_number; }

    /// @brief Sets the logical number of a node within its parent.
    ///
    /// The numbering scheme is user-defined, but not two children of the same
    /// type and same parent node can have the same number.
    void set_number(std::size_t number) { m_number = number; }

protected:
    /// @brief Constructor
    /// @param parent The future parent of this node.
    /// @note The only way to get a value suitable for @c parent is using the
    ///       create_child() function.
    explicit multiple_child_of(const parent_ptr<parent_type>& parent)
        : child_of<parent_type>(parent)
    {
    }

private:
    std::size_t m_number;
};

namespace helper {
    /// @brief Helper function to calculate the value of @ref is_child_node
    template <class Child, class Parent>
    constexpr bool is_child_node()
    {
        if constexpr (!std::is_base_of_v<child_node_tag, Child>) {
            // All child node classes inherit from child_node_tag.
            return false;
        } else if constexpr (std::is_base_of_v<Parent, Child>) {
            // A node class cannot be a child of itself or one of its base
            // classes.
            return false;
        } else {
            // The interesting case: Child is a child node. Check whether the
            // direct parent is compatible with Parent or recurse.
            using direct_parent = typename Child::parent_type;
            return std::is_base_of_v<Parent, direct_parent> || is_child_node<direct_parent, Parent>();
        }
    }
}

/// @brief Checks whether a node type is a child of another
///
/// This variable can be used in two ways:
///
///  * If `Parent` is not specified, it checks whether a node type is a child
///    (of anything)
///  * If `Parent` is specified, it checks whether `Child` is a child node of
///    `Parent`
///
/// @hideinitializer
/// @relates child_of
template <class Child, class Parent = void>
constexpr bool is_child_node = helper::is_child_node<Child, Parent>();

#if !IS_DOXYGEN
template <class Child>
constexpr bool is_child_node<Child, void> = std::is_base_of_v<child_node_tag, Child>;
#endif

/// @brief Checks whether a node type is a multiple child of another
///
/// This variable can be used in two ways:
///
///  * If `Parent` is not specified, it checks whether a node type is a child
///    (of anything)
///  * If `Parent` is specified, it checks whether `Child` is a child node of
///    `Parent`
///
/// @hideinitializer
/// @relates multiple_child_of
template <class Child, class Parent = void>
constexpr bool is_multiple_child_node = std::is_base_of_v<multiple_child_node_tag, Child>&& is_child_node<Child, Parent>;

/// @brief Checks whether a node type is a parent of another
///
/// This variable can be used in two ways:
///
///  * If `Child` is not specified, it checks whether a node type is a parent
///    (of anything)
///  * If `Child` is specified, it checks whether `Child` is a child node of
///    `Parent`
///
/// @hideinitializer
/// @relates child_of
template <class Parent, class Child = void>
constexpr bool is_parent_node = is_child_node<Child, Parent>;

#if !IS_DOXYGEN
template <class Parent>
constexpr bool is_parent_node<Parent, void> = std::is_base_of_v<parent_mixin, Parent>;
#endif

/// @brief Creates a child of @c parent
///
/// This function creates a child of @c parent using the given @c arguments.
/// Internally, it calls the @c Child constructor with a @ref parent_ptr object
/// and the forwarded @c arguments. Schematically, the child is constructed
/// using from following expression:
///
/// ~~~{.cpp}
/// new Child(parent_ptr, arguments...)
/// ~~~
///
/// The lifetime of the created @c Child is managed by @c parent.
///
/// @relates child_of
template <class Child, class... Args>
Child* create_child(typename Child::parent_type* parent, Args&&... arguments)
{
    Child* child = new Child(parent_ptr(parent), std::forward<Args>(arguments)...);
    parent->m_children.emplace_back(child);
    return child;
}

/// @brief Creates a child of @c parent
///
/// This function creates a child of @c parent using the given @c arguments.
/// Internally, it calls the @c Child constructor with a @ref parent_ptr object
/// and the forwarded @c arguments. Schematically, the child is constructed
/// using from following expression:
///
/// ~~~{.cpp}
/// new Child(parent_ptr, arguments...)
/// ~~~
///
/// The lifetime of the created @c Child is managed by @c parent.
///
/// @relates child_of
template <class Child, class... Args>
Child* create_child(
    const std::unique_ptr<typename Child::parent_type>& parent,
    Args&&... arguments)
{
    return create_child<Child>(parent.get(), std::forward<Args>(arguments)...);
}

} // namespace gem::core::layout_tree

#endif // GEM_CORE_LAYOUT_TREE_CHILD_OF_H
