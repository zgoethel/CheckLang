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
    bool remove(std::shared_ptr<E> element)
    {
        auto current = &head;

        for (int i = 0; i < size; i++)
        {
            if (current->element == element)
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;

                delete current;

                size--;

                return true;
            }

            current = current->next;
        }

        return false;
    }

    void add(std::shared_ptr<E> element)
    {
        auto node = new linked_list_node { element, tail, tail->prev };

        tail->prev->next = node;
        tail->prev = node;

        size++;
    }

    void insert(int index, std::shared_ptr<E> element)
    {
        if (index < 0 || index > size)
            throw std::exception("Index out of bounds");

        auto current = &head;

        for (int i = 0; i < index; i++)
            current = current->next;
            
        auto node = new linked_list_node { element, current->next, current };

        current->next->prev = node;
        current->next = node;

        size++;
    }

    void set(int index, std::shared_ptr<E> element)
    {
        if (index < 0 || index >= size)
            throw std::exception("Index out of bounds");

        auto current = &head;

        for (int i = 0; i < index; i++)
            current = current->next;
            
        auto node = new linked_list_node { element, current->next, current };

        current->next->element = element;
    }

    std::shared_ptr<E> get(int index)
    {
        if (index < 0 || index >= size)
            throw std::exception("Index out of bounds");

        auto current = &head;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current->next->element;
    }

    std::shared_ptr<E> remove(int index)
    {
        if (index < 0 || index >= size)
            throw std::exception("Index out of bounds");

        auto current = &head;

        for (int i = 0; i < index; i++)
            current = current->next;

        auto result = current->next->element;
        auto delete_reference = current->next;

        current->next->prev = current;
        current->next = current->next->next;

        delete delete_reference;

        size--;

        return result;
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