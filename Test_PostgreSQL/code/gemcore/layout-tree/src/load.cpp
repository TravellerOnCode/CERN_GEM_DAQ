#include "constants.h"

#include <gem/core/layout-tree/loader.h>
#include <gem/core/layout-tree/nodes.h>

// Boost
#include <boost/filesystem.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

namespace fs = boost::filesystem;

namespace gem::core::layout_tree {

namespace detail {

    /// @brief Discovers the configuration files present in the data directory
    std::vector<fs::path> get_files()
    {
        // Build the path to the data directory
        const fs::path root_dir(tree_dir.data());

        // If the directory doesn't exist, there's nothing to load
        if (!fs::is_directory(root_dir)) {
            return {};
        }

        // Collect all files under the directory
        auto files = std::vector<fs::path>();
        auto it = fs::recursive_directory_iterator(root_dir,
            fs::symlink_option::recurse);
        for (; it != fs::recursive_directory_iterator(); ++it) {
            // Avoid following a link to a parent directory
            if (it.level() > max_recursion_depth) {
                throw std::runtime_error("too much recursion");
            }
            if (is_regular_file(*it)) {
                files.push_back(*it);
            }
        }

        // Sort the files in lexicographical order
        std::sort(files.begin(), files.end());
        return files;
    }

    /// @brief A Boost.Iostreams @c Source that concatenates multiple files.
    class multi_file_source : public boost::iostreams::source {
    public:
        /// @brief Constructor. Using an empty file list is undefined behavior.
        explicit multi_file_source(const std::vector<fs::path>& files)
            : _files(files)
            , _position(0)
            , _current(files.front().native())
        {
        }

        /// @brief Read up to n characters the buffer @c s
        /// @returns The number of characters read, or -1 after reaching the end
        std::streamsize read(char* s, std::streamsize n)
        {
            auto read = _current.read(s, n);
            while (read < 0 && ++_position < _files.size()) {
                // Reached the end of the current file, move on the the next.
                // We may need to do it several times if some files are empty.
                _current = boost::iostreams::file_source(_files[_position].native());
                read = _current.read(s, n);
            }
            return read;
        }

    private:
        std::vector<fs::path> _files; // The files
        std::size_t _position;
        boost::iostreams::file_source _current;
    };

} // namespace detail

std::unique_ptr<root_node> load()
{
    // Get the files that we're going to load
    auto files = detail::get_files();
    if (files.empty()) {
        return std::make_unique<root_node>();
    }

    // Create a stream to read our files
    using stream = boost::iostreams::stream<detail::multi_file_source>;
    stream in = stream(detail::multi_file_source(files));

    // Parse the YAML
    auto yaml = YAML::Load(in);

    // Initialize the loader
    loader<root_node> l;
    l.register_child_node<crate_node>();
    l.register_child_node<amc13_node>();
    l.register_child_node<backend_board_node>();
    l.register_child_node<link_node>();
    l.register_child_node<gbt_node>();
    l.register_child_node<optohybrid_fpga_node>();
    l.register_child_node<vfat_node>();

    return l.load(yaml);
}

} // namespace gem::core::layout_tree
