#pragma once

#include <functional>
#include <memory>

template <typename E>
/**
 * Represents an objects which iterates over a progression of elements
 */
class iterator
{
    /**
     * @returns Whether the iterable object has a next element
     */
    bool has_next();

    /**
     * @returns The next element in the sequence, or nothing if there isn't one
     */
    std::shared_ptr<E> get_next();
};

template <typename E>
/**
 * Represents a progression of elements which can be iterated over
 */
class iterable
{
private:
    /**
     * @returns An iterator which can be used to iterate over this sequence
     */
    std::shared_ptr<iterator<E>> create_iterator();

public:
    /**
     * Executes the given action for each element in the sequence
     * 
     * @param action Action function to call on each element
     */
    void for_each(std::function<void(std::shared_ptr<E> element)> action)
    {
        auto iterator = this->create_iterator();

        while (iterator->has_next())
        {
            auto next = iterator->get_next();
            action(next)
        }
    }
};

template <typename E>
/**
 * An ordered or unordered, keyed or unkeyed collection of elements
 */
class collection : public iterable<E>
{
    /**
     * @returns The number of elements contained in the collection
     */
    int get_size();
    
    /**
     * @param element Element to search for in the collection
     * 
     * @returns Whether the given element exists anywhere in the collection
     */
    bool contains(std::shared_ptr<E> element);
    
    /**
     * Removes the given element from the collection if it exists
     * 
     * @param element Element to find and remove
     * 
     * @return Whether the collection was changed
     */
    bool remove(std::shared_ptr<E> element);
};

template <typename E>
/**
 * Represents specifically an unkeyed collection
 */
class set : public collection<E>
{
    /**
     * Adds the given element to the set
     * 
     * @param element Element to add
     */
    void add(std::shared_ptr<E> element);
};

template <typename E>
/**
 * Represents specifically an ordered collection with integer indices
 */
class list : public set<E>
{
    /**
     * Replaces the element at the given index, or appends it if at the end
     * 
     * @param index Index at which to place the element
     * @param element Element to place in the list at the given index
     */
    void set(int index, std::shared_ptr<E> element);

    /**
     * @param index Index in the list to retrieve
     * 
     * @return Element located at the given index in the list
     */
    std::shared_ptr<E> get(int index);

    /**
     * @param index Index in the list to remove
     * 
     * @return Element removed at the given index in the list
     */
    std::shared_ptr<E> remove(int index);
};

template <typename K, typename V>
struct key_value_pair
{
    std::shared_ptr<K> key;

    std::shared_ptr<V> value;
};

template <typename K, typename V>
/**
 * A collection of items which can be retrieved by their key
 */
class keyed_collection : public collection<key_value_pair<K, V>>
{
    std::shared_ptr<V> get(std::shared_ptr<K> key);

    void put(std::shared_ptr<K> key, std::shared_ptr<V> value);
};