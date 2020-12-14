/// @file
/// @brief Tests for the layout tree node classes.

#include <type_traits>

#include "gem/core/layout-tree/nodes.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE node_classes
#include <boost/test/unit_test.hpp>

namespace gem::core::layout_tree {

/// @brief Tests the layout tree node classes.
BOOST_AUTO_TEST_SUITE(node_classes)

/// @brief Tests that a complete GE1/1 tree can be built.
BOOST_AUTO_TEST_CASE(build_ge11_tree)
{
    const int crate_count = 2;
    const int amc_count = 12; // per crate
    const int link_count = 12; // per amc
    const int vfat_count = 24; // per link
    const int gbt_count = 3; // per link

    auto root = std::make_unique<root_node>();
    for (int icrate = 0; icrate < crate_count; ++icrate) {
        auto crate = create_child<crate_node>(root);

        create_child<amc13_node>(crate);
        for (int iamc = 0; iamc < amc_count; ++iamc) {
            auto amc = create_child<backend_board_node>(crate);

            for (int ilink = 0; ilink < link_count; ++ilink) {
                auto link = create_child<link_node>(amc);

                create_child<optohybrid_fpga_node>(link);
                for (int ivfat = 0; ivfat < vfat_count; ++ivfat) {
                    create_child<vfat_node>(link);
                }
                for (int igbt = 0; igbt < gbt_count; ++igbt) {
                    create_child<gbt_node>(link);
                }
            }
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace gem::core::layout_tree
