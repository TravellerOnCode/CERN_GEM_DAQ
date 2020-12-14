/// @file
/// @brief Tests for the layout tree base classes @c node, @c parent and @c child_of.

#include <string_view>
#include <type_traits>

#include "gem/core/layout-tree/child_of.h"
#include "gem/core/layout-tree/loader.h"
#include "gem/core/layout-tree/node.h"
#include "gem/core/layout-tree/parent_mixin.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE core_classes
#include <boost/test/unit_test.hpp>

namespace gem::core::layout_tree {

namespace /* anonymous */ {
    /// @brief A node of an A-B-C-D tree.
    class a_node : public root_node {
    public:
        /// @brief The name of this node type
        inline constexpr static std::string_view node_name = "a";
    };

    /// @brief B node of an A-B-C-D tree.
    class b_node : public multiple_child_of<a_node>, public parent_mixin {
    public:
        /// @brief The name of this node type
        inline constexpr static std::string_view node_name = "b";

        /// @brief Minimal constructor.
        explicit b_node(const parent_ptr<a_node>& parent)
            : multiple_child_of<a_node>(parent)
        {
        }
    };

    /// @brief C node of an A-B-C-D tree.
    class c_node : public multiple_child_of<b_node>, public parent_mixin {
    public:
        /// @brief The name of this node type
        inline constexpr static std::string_view node_name = "c";

        /// @brief Minimal constructor.
        explicit c_node(const parent_ptr<b_node>& parent)
            : multiple_child_of<b_node>(parent)
        {
        }
    };

    /// @brief D node of an A-B-C-D tree.
    class d_node : public child_of<c_node> {
    public:
        /// @brief The name of this node type
        inline constexpr static std::string_view node_name = "d";

        /// @brief Minimal constructor.
        explicit d_node(const parent_ptr<c_node>& parent)
            : child_of<c_node>(parent)
        {
        }
    };

    /// @brief Node that throws on construction
    class throw_node : public child_of<a_node> {
    public:
        /// @brief The name of this node type
        inline constexpr static std::string_view node_name = "throw";

        /// @brief Always-throwing constructor
        explicit throw_node(const parent_ptr<a_node>& parent)
            : child_of<a_node>(parent)
        {
            throw 1;
        }
    };

} // anonymous namespace

// Static checks
static_assert(is_root_node<a_node>);

static_assert(is_child_node<b_node>);
static_assert(is_child_node<b_node, a_node>);
static_assert(is_multiple_child_node<b_node>);
static_assert(is_multiple_child_node<b_node, a_node>);

static_assert(is_child_node<c_node>);
static_assert(is_child_node<c_node, a_node>);
static_assert(is_child_node<c_node, b_node>);
static_assert(is_multiple_child_node<c_node>);
static_assert(is_multiple_child_node<c_node, a_node>);
static_assert(is_multiple_child_node<c_node, b_node>);

static_assert(is_child_node<d_node, a_node>);
static_assert(is_child_node<d_node, b_node>);
static_assert(is_child_node<d_node, c_node>);
static_assert(!is_multiple_child_node<d_node>);

/// @brief Tests the core classes of the layout tree API
///
/// The following classes are tested by this test suite:
///
///  * @ref child_of
///  * @ref node
///  * @ref parent_mixin
BOOST_AUTO_TEST_SUITE(core_classes)

/// @brief Tests the @ref node public API
BOOST_AUTO_TEST_CASE(node_api)
{
    BOOST_CHECK(std::is_polymorphic_v<node>);

    // Check display_name() and uid()
    auto node = std::make_unique<a_node>();
    node->set_display_name("display_name");
    BOOST_CHECK(node->display_name() == "display_name");
    node->set_uid("uid");
    BOOST_CHECK(node->uid() == "uid");
}

/// @brief Tests parent/child relationships
BOOST_AUTO_TEST_CASE(parent_child)
{
    auto a = std::make_unique<a_node>();
    // Check that we can create a tree with three layers
    for (int i = 0; i < 5; ++i) {
        auto b = create_child<b_node>(a);
        // Check that the node added itself to its parent
        BOOST_CHECK(a->children().size() == i + 1);
        BOOST_CHECK(b->parent() == a.get());
        for (int j = 0; j < 2; ++j) {
            auto c = create_child<c_node>(b);
            // Same for the next level
            BOOST_CHECK(b->children().size() == j + 1);
            BOOST_CHECK(c->parent() == b);
        }
    }
    // Check that we can loop over the children
    for (auto& pb : a->children()) {
        BOOST_CHECK(dynamic_cast<parent_mixin*>(pb.get()) != nullptr);
        const auto b = dynamic_cast<b_node*>(pb.get());
        BOOST_CHECK(b != nullptr);
        // Same for the next level
        for (auto& pc : b->children()) {
            BOOST_CHECK(dynamic_cast<parent_mixin*>(pc.get()) != nullptr);
            const auto& c = dynamic_cast<c_node*>(pc.get());
            BOOST_CHECK(c != nullptr);
        }
    }
    // Node constructor throwing should not affect the tree
    a = std::make_unique<a_node>();
    BOOST_CHECK_THROW(auto t = create_child<throw_node>(a), int);
    BOOST_CHECK(a->children().empty());
}

/// @brief Tests iterators
BOOST_AUTO_TEST_CASE(iterators)
{
    // Create a tree with four layers
    // We need four to check that the recursive_iterator can move up several
    // levels at once
    const int nb = 5, nc = 2, nd = 1;
    int nchildren = 0;
    auto a = std::make_unique<a_node>();
    for (int i = 0; i < nb; ++i) {
        auto b = create_child<b_node>(a);
        nchildren++;
        // Need to test parent nodes with no children, so include one
        if (i == 0) {
            continue;
        }
        for (int j = 0; j < nc; ++j) {
            auto c = create_child<c_node>(b);
            nchildren++;

            create_child<d_node>(c); // d_node isn't a multiple_child_of
            nchildren++;
        }
    }
    // Check that we get all the child nodes by recursing
    auto range = a->recursive_children();
    BOOST_CHECK(std::distance(range.begin(), range.end()) == nchildren);
    // Same in reverse order
    auto reversed = range | boost::adaptors::reversed;
    BOOST_CHECK(std::distance(reversed.begin(), reversed.end()) == nchildren);

    // recursive_iterator copy constructor
    auto it = range.begin(); // explicit copy
    // Get to somewhere more interesting than the start
    for (int i = 0; i < 5; ++i) {
        ++it;
    }
    BOOST_CHECK(it == recursive_iterator(it));

    // Check filter_nodes
    auto b_range = range | filter_nodes<b_node>;
    // It finds the correct number of nodes
    BOOST_CHECK(std::distance(b_range.begin(), b_range.end()) == nb);
}

/// @brief Tests loading from YAML
BOOST_AUTO_TEST_CASE(loading)
{
    // Test the error class first
    auto err = load_error("A", "B");
    BOOST_CHECK_EQUAL(err.what(), "A");
    BOOST_CHECK_EQUAL(err.details(), "B");

    a_node a;
    a.set_uid("uid");
    a.set_display_name("dn");
    err = load_error(a, "A", "B");
    BOOST_CHECK_EQUAL(err.what(), "A");
    BOOST_CHECK_EQUAL(err.details(), "B");
    BOOST_CHECK(
        err.location() == R"(node of type a with uid="uid" and display name="dn")");

    std::stringstream ss;
    ss << err << std::endl;
    BOOST_CHECK(ss.good()); // Hard to check more without a template file

    // Now test the loader
    loader<a_node> l;
    l.register_child_node<b_node>();
    l.register_child_node<c_node>();
    l.register_child_node<d_node>();

    // Valid documents

    // Minimal
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(root: !a {})")));
    // Attributes on root
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    uid: test
    display name: test root node
)")));
    // Children
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children: []
)")));
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b { number: 0 }
)")));
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b { number: 0 }
        - !b { number: 1 }
)")));
    // Attributes on child
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b
            uid: test
            display name: test b node
            number: 0
)")));
    // Grand-children
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b
            number: 0
            children:
                - !c { number: 0 }
                - !c { number: 1 }
)")));
    // Complete graph
    BOOST_CHECK_NO_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b
            number: 0
            children:
                - !c
                    number: 0
                    children: [ !d {} ]
                - !c
                    number: 0
                    children: [ !d {} ]
)")));

    // Invalid documents

    // Not a map
    BOOST_CHECK_THROW(l.load(YAML::Load(R"([])")), load_error);
    // Unknown keys
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(a: b)")), load_error);
    // No root
    BOOST_CHECK_THROW(l.load(YAML::Load(R"({})")), load_error);
    // Scalar root
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(root: 5)")), load_error);
    // Map root with wrong type tag
    BOOST_CHECK_THROW(
        l.load(YAML::Load(R"(root: !b {})")), load_error);
    // Map root with unknown type tag
    BOOST_CHECK_THROW(
        l.load(YAML::Load(R"(root: !x {})")), load_error);

    // "children" is not a sequence
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children: {}
)")),
        load_error);
    // Child is not a map
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - "b"
)")),
        load_error);
    // Child with unknown type
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !x {}
)")),
        load_error);
    // multiple_child_of without number field
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b {}
)")),
        load_error);
    // multiple_child_of with number field of the wrong type
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b { number: "" }
)")),
        load_error);
    // multiple_child_of with negative number field
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b { number: -1 }
)")),
        load_error);
    // Child with forbidden type (wrong parent)
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !c { number: 0 }
)")),
        load_error);
    // Non-parent node with children
    BOOST_CHECK_THROW(l.load(YAML::Load(R"(
root: !a
    children:
        - !b
            number: 0
            children:
                - !c
                    number: 0
                    children:
                        - !d
                            children: []
)")),
        load_error);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace gem::core::layout_tree
