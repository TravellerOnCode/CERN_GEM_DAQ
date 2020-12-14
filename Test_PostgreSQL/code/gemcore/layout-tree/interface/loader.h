#ifndef GEM_CORE_LAYOUT_TREE_LOADER_H
#define GEM_CORE_LAYOUT_TREE_LOADER_H

/// @file
/// @brief Utilities to load trees from files

#include "gem/core/layout-tree/child_of.h"
#include "gem/core/layout-tree/node.h"
#include "gem/core/layout-tree/parent_mixin.h"

#include <yaml-cpp/yaml.h>

#include <limits>
#include <sstream>

namespace gem::core::layout_tree {

/// @brief Exception thrown by @ref loader on failure
/// @headerfile loader.h "gem/core/layout-tree/loader.h"
///
/// Load errors are standard runtime errors with additional detailed information
/// and location strings. They can be used to provide detailed information to
/// the user.
class load_error : public std::runtime_error {
public:
    /// @brief Constructor
    ///
    /// The resulting error reports `(unknown location)`.
    explicit load_error(
        const std::string& generic_message,
        const std::string& detailed_message = "");

    /// @brief Constructor
    ///
    /// The resulting error reports a location based on `node`.
    template <class T, std::enable_if_t<std::is_base_of_v<node, T>, int> = 0>
    explicit load_error(
        const T& node,
        const std::string& generic_message,
        const std::string& detailed_message = "");

    /// @brief Retrieves a string describing the location of the error
    const std::string& location() const noexcept { return m_location; }

    /// @brief Retrieves a string with contextual details about the error
    const std::string& details() const noexcept { return m_detailed; }

    /// @brief Checks whether an error has detailed information available
    bool has_details() const noexcept { return !m_detailed.empty(); }

private:
    std::string m_location, m_detailed;
};

load_error::load_error(
    const std::string& generic_message,
    const std::string& detailed_message)
    : std::runtime_error(generic_message)
    , m_location("(unknown location)")
    , m_detailed(detailed_message)
{
}

template <class T, std::enable_if_t<std::is_base_of_v<node, T>, int>>
load_error::load_error(
    const T& node,
    const std::string& generic_message,
    const std::string& detailed_message)
    : std::runtime_error(generic_message)
    , m_detailed(detailed_message)
{
    // node of type T, with uid="uid" and display name="name"
    std::stringstream ss;
    ss << "node of type " << T::node_name;
    if (!node.uid().empty() || !node.display_name().empty()) {
        ss << " with ";
        if (!node.uid().empty()) {
            ss << "uid=\"" << node.uid();
            if (!node.display_name().empty()) {
                ss << "\" and ";
            }
        }
        if (!node.display_name().empty()) {
            ss << "display name=\"" << node.display_name();
        }
        ss << "\"";
    }
    m_location = ss.str();
}

/// @brief Writes a @ref load_error to a stream
///
/// A typical error is presented as follows:
///
/// ~~~{.txt}
/// node of type b: ERROR: "number" must be a positive integer
///
///   Expected a number >= 0, got -1
///
/// ~~~
///
/// @relates load_error
std::ostream& operator<<(std::ostream& out, const load_error& error)
{
    out << error.location() << ": ERROR: " << error.what() << std::endl;
    if (error.has_details()) {
        out << std::endl;
        out << "  " << error.details();
    }
    return out;
}

namespace helper {
    /// @brief Finds the type of a YAML node as a string
    std::string yaml_type_name(const YAML::Node& node)
    {
        switch (node.Type()) {
        case YAML::NodeType::Undefined:
            return "undefined";
        case YAML::NodeType::Null:
            return "null";
        case YAML::NodeType::Scalar:
            return "scalar";
        case YAML::NodeType::Sequence:
            return "sequence";
        case YAML::NodeType::Map:
            return "map";
        }
        return "(unknown)";
    }
}

/// @brief Converts YAML documents to layout trees
/// @headerfile loader.h "gem/core/layout-tree/loader.h"
///
/// The target layout tree is specified by providing its root as a template
/// parameter. Allowed child nodes must be registered (using
/// register_child_node()) before they can be used. Once all nodes have been
/// registered, documents can be loaded with load().
///
/// ### Data format
///
/// The YAML format is designed around a tree of maps, each representing a node.
/// Node type information is provided through standard YAML type tags (`!type`,
/// where `type` is the desired `node_name`). The hierarchy structure is defined
/// by adding a `children` list to nodes (this is supported only for
/// @ref parent_mixin "parent nodes"). A typical document might look as follows:
///
/// ~~~
/// root: !a # The root is a node of type a
///     # Optional properties of the root:
///     property 1: X
///     property 2: Y
///     # The list of child nodes:
///     children:
///         - !b # The first child is a node of type b
///             property: 42
///             children:
///                 - ...
///         - !c # The second child is a node of type c
///             property: y
///             children:
///                 - ...
/// ~~~
///
/// The root of the YAML document must be a map with an element called `root`
/// that represents the root node. All other names at the root are reserved for
/// future extension of the format, except ones starting with a dot.
///
/// The use of standard YAML structures such as aliases is encouraged.
///
/// ### Node properties
///
/// By default, the loader handles the @ref node.uid "uid",
/// @ref node.display_name "display name" and
/// @ref multiple_child_of.number "number" properties. Custom fields can be
/// added by overloading the initialize() function for the relevant node types.
///
/// @todo Once we have yaml-cpp >= 0.5.2, report source location of errors.
template <class T, std::enable_if_t<is_root_node<T>, int> = 0>
class loader {
    /// @brief Information about a node type
    class node_type_info_base {
    public:
        /// @brief Creates a node of the type represented by this object
        ///
        /// All error checking is the responsibility of this function, as well
        /// as handling of the initialization (using initialize()).
        ///
        /// @param loader the loader from which this is called
        /// @param parent the parent node (may not be of the correct type)
        /// @param yaml the YAML node to properties from
        virtual void create(
            const loader<T>& loader,
            node* parent,
            const YAML::Node& yaml) const = 0;

        /// @brief Destructor
        virtual ~node_type_info_base() noexcept = default;
    };

    /// @brief Concrete specialization of @ref node_type_info_base
    template <class U>
    class node_type_info : public node_type_info_base {
        /// @brief The type of the node being created
        using node_type = U;

    public:
        /// @copydoc node_type_info_base::create
        virtual void create(
            const loader<T>& loader,
            node* parent,
            const YAML::Node& yaml) const override
        {
            auto cast_parent = dynamic_cast<typename node_type::parent_type*>(parent);
            if (cast_parent == nullptr) {
                throw load_error(
                    "wrong parent type",
                    "Nodes of type " + std::string(U::node_name) + " must have parent of type " + std::string(U::parent_type::node_name));
            }
            if (!yaml.IsMap()) {
                throw load_error(*cast_parent, "nodes must be maps");
            }
            auto node = create_child<node_type>(cast_parent);
            try {
                initialize(*node, yaml);
            } catch (const YAML::Exception& e) {
                std::throw_with_nested(load_error(
                    "initialization failure"
                    "Node initialization failed with YAML error: "
                    + std::string(e.what())));
            }
            loader.create_children(*node, yaml["children"]);
        }
    };

public:
    /// @brief Registers a node type
    ///
    /// This function registers a node type for use in loaded document. The root
    /// node is always implicitly registered, and cannot be registered again
    /// using this function.
    template <
        class U,
        std::enable_if_t<!is_root_node<U> && is_parent_node<T, U>, int> = 0>
    void register_child_node()
    {
        // yaml-cpp keeps the exclamation mark in the tag name. Add it here so
        // we don't need to do it later.
        m_types["!" + std::string(U::node_name)] = std::make_unique<node_type_info<U>>();
    }

    /// @brief Loads a tree from a YAML document
    ///
    /// The argument to this function must be the root node of a document that
    /// complies with the expected format (see class description).
    ///
    /// @throws load_error with eventually a nested `YAML::Exception`
    std::unique_ptr<T>&& load(const YAML::Node& yaml) const
    {
        if (!yaml.IsMap()) {
            using helper::yaml_type_name;
            throw load_error(
                "document is not a map",
                "The root of the document must be a map, found a " + yaml_type_name(yaml));
        }
        for (auto& pair : yaml) {
            auto name = pair.first.as<std::string>();
            if (name[0] != '.' && name != "root") {
                throw load_error(
                    "unknown attribute",
                    "Found unknown attribute \"" + name + "\" at the root of the tree");
            }
        }
        const auto& root_node = yaml["root"];
        if (!root_node.IsMap()) {
            using helper::yaml_type_name;
            throw load_error(
                "node is not a map",
                "The root node must be a YAML map, found a " + yaml_type_name(root_node));
        }
        if (root_node.Tag() != "!" + std::string(T::node_name)) {
            throw load_error(
                "wrong node type",
                "The root node has type " + root_node.Tag() + ", expected !" + std::string(T::node_name));
        }
        // All checks ok as far as this function is concerned, create the root
        auto root = std::make_unique<T>();
        try {
            initialize(*root, root_node);
        } catch (const YAML::Exception& e) {
            std::throw_with_nested(load_error(
                "initialization failure"
                "Node initialization failed with YAML error: "
                + std::string(e.what())));
        }
        create_children(*root, root_node["children"]);
        return std::move(root);
    }

private:
    /// @brief Creates the children of a node
    template <class U>
    void create_children(U& parent, const YAML::Node& children) const
    {
        if (!children) {
            return;
        }
        if constexpr (!is_parent_node<U>) {
            throw load_error(
                parent,
                "node cannot have children",
                "The \"children\" attribute was set for a node of type " + std::string(U::node_name) + ", which doesn't have children");
        } else {
            if (!children.IsSequence()) {
                using helper::yaml_type_name;
                throw load_error(
                    parent,
                    "children attribute is not a sequence",
                    "The \"children\" attribute must be a sequence, got a " + yaml_type_name(children));
            }
            for (auto& child : children) {
                if (!child.IsMap()) {
                    using helper::yaml_type_name;
                    throw load_error(
                        parent,
                        "child node is not a map",
                        "Elements of the \"children\" list must be maps, got a " + yaml_type_name(child));
                }
                auto tag = child.Tag();
                if (tag.empty()) {
                    throw load_error(
                        parent,
                        "child has no type tag",
                        "An element of the \"children\" list doesn't have a !type tag");
                }
                if (m_types.count(tag) == 0) {
                    throw load_error(
                        parent,
                        "child has unknown type",
                        "An element of the \"children\" list has unknown type " + tag);
                }
                m_types.at(tag)->create(*this, &parent, child);
            }
        }
    }

    std::map<std::string, std::unique_ptr<node_type_info_base>> m_types;
};

/// @brief Initializes a @ref node from a YAML node
///
/// This function is called when a node is being loaded from YAML data. It
/// initializes the node content based on its YAML description.
///
/// This function can be specialized to add custom fields to specific node
/// types. Specializations should call the relevant specializations for their
/// base classes.
///
/// @throws load_error
/// @relates loader
void initialize(node& init, const YAML::Node& yaml)
{
    init.set_uid(yaml["uid"].as<std::string>(""));
    std::string display_name = yaml.Tag().substr(1); // Drop the !
    init.set_display_name(yaml["display name"].as<std::string>(display_name));
}

/// @brief Handles the @ref multiple_child_of.number "number" attribute
///
/// `number` (a positive integer) is mandatory for nodes that inherit from
/// @ref multiple_child_of.
///
/// @throws load_error
/// @relates loader
template <class T, std::enable_if_t<is_multiple_child_node<T>, int> = 0>
void initialize(T& init, const YAML::Node& yaml)
{
    initialize(static_cast<node&>(init), yaml);
    if (!yaml["number"]) {
        throw load_error(
            init,
            "multiple_child_of without \"number\" attribute",
            "Node type " + std::string(T::node_name) + " inherits from multiple_child_of, so it needs a \"number\" attribute");
    }
    try {
        // Workaround for https://github.com/jbeder/yaml-cpp/issues/859
        auto number = yaml["number"].as<long>();
        if (number < 0L || number > std::numeric_limits<std::size_t>::max()) {
            throw load_error(
                init,
                "\"number\" must be a positive integer",
                "Expected a number >= 0, got " + std::to_string(number));
        }
        init.set_number(std::size_t(number));
    } catch (const YAML::BadConversion&) {
        throw_with_nested(load_error(
            init,
            "\"number\" must be a positive integer",
            "Expected a number >= 0, got " + yaml["number"].Scalar()));
    }
    // Override the display name set by initialize(node&)
    std::string display_name = std::string(T::node_name) + " " + std::to_string(init.number());
    init.set_display_name(yaml["display name"].as<std::string>(display_name));
}

} // namespace gem::core::layout_tree

#endif // GEM_CORE_LAYOUT_TREE_LOADER_H
