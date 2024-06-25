#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H
#include <data/binary-tree.h>

namespace tests {
    template<typename T>
    std::vector<T> TreeTraversal(const data::Node<T>& node) {

        if (node.isLeaf()) {
            const data::Leaf<T>& NodeToLeafCastedObject = dynamic_cast<const data::Leaf<T>&>(node);
            return std::vector<T> {NodeToLeafCastedObject.getValue()};
        }

        const data::Branch<T>& NodeToBranchCastedObject = dynamic_cast<const data::Branch<T>&>(node);

        std::vector<T> leftvector = TreeTraversal(NodeToBranchCastedObject.getLeftNode());
        std::vector<T> rightvector = TreeTraversal(NodeToBranchCastedObject.getRightNode());
        leftvector.insert(leftvector.end(), rightvector.begin(), rightvector.end());
        return leftvector;

    }
}
#endif