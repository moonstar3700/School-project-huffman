#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <assert.h>
#include "memory"
#include <functional>

namespace data {
	template<typename T>
	class Node {

	public:
		virtual ~Node() {}
		virtual bool isLeaf() const { return false; }
		const T& getValue() const { return T(); }


	};
	template<typename T>
	class Branch : public Node<T> {
	private:
		std::unique_ptr<Node<T>> _left_child;
		std::unique_ptr<Node<T>> _right_child;
	public:
		Branch(std::unique_ptr<Node<T>> left_child, std::unique_ptr<Node<T>> right_child) : _left_child(std::move(left_child)), _right_child(std::move(right_child)) {
			assert(_left_child != nullptr);
			assert(_right_child != nullptr);
		}
		const Node<T>& getLeftNode() const {
			return *_left_child;
		}
		const Node<T>& getRightNode() const {
			return *_right_child;
		}


	};
	template<typename T>
	class Leaf : public Node<T> {
	private:
		T _value;
	public:
		Leaf() {}
		Leaf(const T& value) : _value(value) {}
		const T& getValue() const { return _value; }
		virtual bool isLeaf() const {
			return true;
		}


	};


}



#endif