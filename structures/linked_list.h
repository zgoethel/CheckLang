#pragma once

#include "collection.h"

template <typename E>
struct linked_list_node
{
    std::shared_ptr<E> element;

    linked_list_node<E>* next;
    linked_list_node<E>* prev;
};

template <typename E>
class linked_list_iterator;

template <typename E>
class linked_list : public list<E>
{
private:
    linked_list_node<E> head;
    linked_list_node<E> tail;

    int size = 0;

public:
    linked_list()
    {
        this->head->next = tail;
        this->tail->prev = head;
    }

    ~linked_list()
    {
        linked_list_node* current = &head;

        while (current != &tail)
        {
            auto delete_reference = current;
            current = current->next;

            delete delete_reference;
        }
    }

    std::shared_ptr<iterator<E>> create_iterator()
    {
        return std::shared_ptr<iterator<E>>(new linked_list_iterator(this));
    }

    int get_size()
    {
        return this->size;
    }

    //TODO Equals comparison
    bool contains(std::shared_ptr<E> element)
    {
        this->for_each([](std::shared_ptr<E> e)
        {
            if (element == e)
                return true;
        });

        return false;
    }

    //TODO Equals comparison
    //TODO
    bool remove(std::shared_ptr<E> element)
    {

        return false;
    }

    //TODO
    void add(std::shared_ptr<E> element)
    {

    }

    //TODO
    void set(int index, std::shared_ptr<E> element)
    {
        
    }

    //TODO
    std::shared_ptr<E> get(int index)
    {

        return std::shared_ptr<E>(nullptr);
    }

    //TODO
    std::shared_ptr<E> remove(int index)
    {
        
        return std::shared_ptr<E>(nullptr);
    }

    friend class linked_list_iterator<E>;
};

template <typename E>
class linked_list_iterator : public iterator<E>
{
private:
    linked_list<E>* parent;

    linked_list_node<E>* current;

public:
    linked_list_iterator(linked_list<E>* parent)
    {
        this->parent = parent;
    }

    bool has_next()
    {
        return current->next != &parent->tail;
    }

    std::shared_ptr<E> get_next()
    {
        if (!this->has_next())
            return std::shared_ptr<E>(nullptr);
            
        this->current = this->current->next;

        return this->current->element;
    }
};