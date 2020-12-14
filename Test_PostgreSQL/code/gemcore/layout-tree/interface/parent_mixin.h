#ifndef GEM_CORE_LAYOUT_TREE_PARENT_MIXIN_H
#define GEM_CORE_LAYOUT_TREE_PARENT_MIXIN_H

/// @file
/// @brief Defines the @c parent_mixin class

#include <memory>
#include <vector>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/range/adaptors.hpp>

#include "gem/core/layout-tree/node.h"

namespace gem::core::layout_tree {

/// @brief An iterator that recurses into children's children
/// @headerfile parent_mixin.h "gem/core/layout-tree/parent_mixin.h"
///
/// This is an iterator in the same sense as the ones in the STL library (eg
/// @c std::vector::iterator). As such, it can be used as an input for the
/// [standard algorithms].
///
/// Dereferencing a @c recursive_iterator yields a const reference to a
/// `std::unique_ptr<node>`.
///
/// Using this iterator, one can loop over all the descendants of a node. The
/// parents always come before their children. For instance, given the tree
/// below, using @c recursive_iterator on @c a will yield `b1 b2 c1 c2 b3 c3
/// c4`.
///
/// ~~~
/// a
///   b1
///   b2
///     c1
///     c2
///   b3
///     c3
///     c4
/// ~~~
///
/// recursive_iterator supports the decrement operator: `it--` is a valid
/// expression. Moving backwards is the exact opposite of moving forward.
/// Technically speaking, recursive_iterator satisfies the requirements of a
/// [BidirectionalIterator].
///
/// This class is normally used through @ref parent_mixin.recursive_children().
///
/// [standard algorithms]: https://en.cppreference.com/w/cpp/algorithm
/// [BidirectionalIterator]: https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator
class recursive_iterator : public boost::iterator_facade<
                               recursive_iterator,
                               std::unique_ptr<node>,
                               boost::bidirectional_traversal_tag,
                               const std::unique_ptr<node>&> {
    // Shorthand to make changes easier
    using vector = std::vector<std::unique_ptr<node>>;
    using iterator = typename vector::const_iterator;

    // The iterator maintains a stack with the path to the currently visited
    // node. The current node is always at the end (back()) of the stack.
    struct stack_entry {
        iterator begin; // The begin() iterator of the node's parent
        iterator current; // Points to the current node
        iterator end; // The end() iterator of the node's parent
    };
    std::vector<stack_entry> m_stack;

public:
    /// @brief Constructs an invalid iterator
    recursive_iterator() noexcept {}

    /// @brief Constructs an iterator associated with the non-recursive iterator
    ///        @c it.
    recursive_iterator(const iterator& it)
        // Note that we don't set .begin and .end. We don't know them and they
        // are never needed.
        : m_stack({ stack_entry { .current = it } })
    {
    }

    /// @brief Copy constructor
    recursive_iterator(const recursive_iterator&) = default;

    /// @brief Copy-assignment operator
    recursive_iterator& operator=(const recursive_iterator&) = default;

    /// @brief Implementation of @c operator--
    inline void decrement();

    /// @brief Implementation of @c operator++
    inline void increment();

    /// @brief Implementation of @c operator*
    vector::const_reference dereference() const noexcept
    {
        return *m_stack.back().current;
    }

    /// @brief Compares two recursive iterators for equality
    ///
    /// Two iterators are considered equal if they point to the same node.
    bool equal(const recursive_iterator& other) const noexcept
    {
        return m_stack.back().current == other.m_stack.back().current;
    }

private:
    // Pushes an entry to the stack if the current node has children. Sets
    // begin and end but not current.
    inline bool maybe_push_entry();
};

/// @brief The base class for all nodes in the tree that have children
/// @headerfile parent_mixin.h "gem/core/layout-tree/parent_mixin.h"
///
/// The @c parent_mixin class can be combined with @ref node or @ref child_of to
/// create a node class that can have children. A typical class for a parent node
/// is declared as follows:
///
/// ~~~{.cpp}
/// class node_with_children: public node, public parent_mixin {
/// ~~~
///
/// A parent node keeps track of its children, accessible through the
/// @ref children method. The parent owns its children, and deletes them in its
/// destructor.
class parent_mixin {
    // create_child needs to manipulate m_children
    template <class T, class... Args>
    friend T* create_child(typename T::parent_type*, Args&&...);

public:
    /// @brief The pointer type used to pass children around
    using pointer = std::unique_ptr<node>;

    /// @brief Retrieves direct children of this node
    /// @warning Don't rely on the result being a @c vector as it is going to
    ///          change. You can use @c auto, @c begin and @c end.
    const std::vector<pointer>& children() const { return m_children; }

    /// @brief Retrieves direct and indirect children of this node
    ///
    /// This function returns a [range] object based on recursive_iterator.
    /// Ranges have `begin`/`end` functions and can be used in C++11 range-based
    /// `for` loops:
    ///
    /// ~~~{.cpp}
    /// for (const auto &child: parent->recursive_children()) {
    /// ~~~
    ///
    /// [range]: https://www.boost.org/doc/libs/master/libs/range/doc/html/index.html
    auto recursive_children() const
    {
        return boost::make_iterator_range(
            recursive_iterator(children().begin()),
            recursive_iterator(children().end()));
    }

protected:
    /// @brief Protected constructor to prevent direct instantiation.
    explicit parent_mixin() = default;

private:
    // The node's children. Note that the vector is destroyed
    std::vector<pointer> m_children;
};

/// @brief The root of the layout tree.
/// @headerfile nodes.h "gem/core/layout-tree/nodes.h"
class root_node : public node, public parent_mixin {
public:
    /// @brief The name of this node type
    inline constexpr static std::string_view node_name = "root";
};

/// @brief Checks whether a node type can be used as a root node
/// @hideinitializer
/// @relates root_node
template <class T>
constexpr bool is_root_node = std::is_base_of_v<root_node, T>;

void recursive_iterator::decrement()
{
    if (m_stack.back().current == m_stack.back().begin) {
        // Reached the start of the child list, move up (exactly one level).
        // Iteration reaches the child's parent.
        m_stack.pop_back();
    } else {
        --m_stack.back().current;
        // If the new node has children, process them first (may need to go down
        // several levels)
        while (maybe_push_entry()) {
            auto& added = m_stack.back();
            added.current = added.end; // Finish initialization
            --added.current; // Reach a valid state
        }
    }
}

void recursive_iterator::increment()
{
    // If the current node has children, process them
    if (maybe_push_entry()) {
        auto& added = m_stack.back();
        added.current = added.begin; // Finish initialization
    } else {
        // Move to the next node
        ++m_stack.back().current;
        // If we reached the end, move up (possibly several levels)
        while (m_stack.back().current == m_stack.back().end) {
            m_stack.pop_back();
            ++m_stack.back().current;
        }
    }
}

bool recursive_iterator::maybe_push_entry()
{
    if (auto as_parent = dynamic_cast<parent_mixin*>(m_stack.back().current->get());
        as_parent != nullptr) {
        // The node may have children. But maybe it doesn't have any...
        if (const auto& children = as_parent->children();
            !children.empty()) {
            // Current node has children, enter state B.
            m_stack.push_back(stack_entry {
                .begin = children.begin(),
                .end = children.end() });
            return true;
        }
    }
    return false;
}

/// @brief Helper classes
namespace helper {
    /// @brief Used for @ref filter_nodes
    template <class Child>
    class filter_nodes_tag {
        // Empty
    };
} // namespace helper

/// @brief Range filter that selects nodes of a given type
/// @headerfile parent_mixin.h "gem/core/layout-tree/parent_mixin.h"
///
/// This filter can be applied to the ranges returned by
/// parent_mixin::children() and parent_mixin::recursive_children() to select
/// only nodes of a given type. The basic syntax is:
///
/// ~~~{.cpp}
/// parent->children() | filter_nodes<child_node_type>
/// ~~~
///
/// The resulting expression is a [range] that can be used in C++11 range-based
/// `for` loops or as an input to [standard algorithms]. For instance:
///
/// ~~~{.cpp}
/// for (const child_node &child: parent->children() | filter_nodes<child_node>)
/// ~~~
///
/// @note Applying this filter results in a range of references, whereas the
///       original ranges use `std::unique_ptr`.
///
/// @relates helper::filter_nodes_tag
///
/// [standard algorithms]: https://en.cppreference.com/w/cpp/algorithm
/// [range]: https://www.boost.org/doc/libs/master/libs/range/doc/html/index.html
template <class Child>
constexpr helper::filter_nodes_tag<Child> filter_nodes;

/// @brief Applies @ref filter_nodes to a range
/// @relates helper::filter_nodes_tag
template <class Range, class Child>
auto operator|(const Range& range, helper::filter_nodes_tag<Child>)
{
    using namespace boost::adaptors;
    // The following definition is required for Boost 1.53
    struct transform_op {
        using result_type = const Child*;
        result_type operator()(const std::unique_ptr<node>& child) const
        {
            return dynamic_cast<Child*>(child.get());
        }
    };
    return range
        | transformed(transform_op {})
        | filtered([](const auto* child) { return child != nullptr; })
        | indirected;
}

} // namespace gem::core::layout_tree

#endif // GEM_CORE_LAYOUT_TREE_PARENT_MIXIN_H
