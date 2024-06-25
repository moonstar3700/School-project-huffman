#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H
#include <iomanip>
#include <iostream>
#include <map>
#include <utility>
#include "data/binary-tree.h"
#include "util.h"
#include <vector>
#include <stdexcept>
#include <assert.h>
#include <algorithm>
#include <set>
#include <memory>


namespace data {
    template<typename T>
    class FrequencyTable
    {
        std::map<T, unsigned> freqTable;  

    public:
        FrequencyTable() {}
        FrequencyTable(std::vector<Datum> input) {
            for (auto const& i : input) {
                increment(i);
            }
        }
        void increment(const T& x) {
            ++freqTable[x];
        }

        int operator[](const T& x) {
            return freqTable[x];
        }

        std::vector<T> values() {
            std::vector<T> keys;
            for (auto const& it : freqTable) {
                keys.push_back(it.first);
            }
            return keys;
        }

        std::vector<std::unique_ptr<data::Node<std::pair<T, unsigned>>>> getAsleaves() {
            struct {
                bool operator() (const Leaf<std::pair<T, unsigned>>& leaf1, const Leaf<std::pair<T, unsigned>>& leaf2) const {
                    return leaf1.getValue().second > leaf2.getValue().second;
                }
            } sortpairs;

            std::vector<Leaf<std::pair<T, unsigned>>> keys; 
            for (auto const& it : freqTable) {
                std::pair<T, unsigned> pair(it.first, it.second);
                data::Leaf<std::pair<T, unsigned>>leaf(pair);
                keys.push_back(leaf);
            }

            std::sort(keys.begin(), keys.end(), sortpairs); 

            std::vector< std::unique_ptr<Node<std::pair<T, unsigned>>>> keys2;
            for (auto pair : keys) {
                keys2.push_back(std::make_unique<data::Leaf<std::pair<T, unsigned>>>(pair));
            }
            return keys2;
        }

    };
    template<typename T>
    FrequencyTable<T> count_frequencies(const std::vector<T> vector) {
        FrequencyTable<T> table;
        for (T freq : vector) {
            table.increment(freq);
        }
        return table;

    }

}
#endif