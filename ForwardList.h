#pragma once


#include "Vector.h"
#include "Company.h"


/**
 * Связный односторонний список
 * Элементы списка - объекты класса Company
 *
 * Функционал
 * 1. Конструкторы: по умолчанию, копирования, перемещения
 * 2. Деструктор
 * 3. Операторы присваивания: копированием, перемещением
 * 4. Вставка объекта в начало списка
 * 5. Удаление объекта по ключу (название компании)
 * 6. Константный/неконстантный поиск объекта по ключу
 * 7. Преобразование списка в Vector<Company>
 * 8. Получение размера списка
 * 9. Проверка 1на пустоту
 * 10. Получение последнего количества сравнений при
 *     поиске/удалении объекта.
 */


namespace Aleksei {

    class ForwardList {
    public:
        typedef Company value_t;
        typedef decltype(Company::name) key_t;

        ForwardList() noexcept;
        ~ForwardList() noexcept;
        ForwardList(const ForwardList& another) noexcept;
        ForwardList& operator=(const ForwardList& another) noexcept;
        ForwardList(ForwardList&& another) noexcept;
        ForwardList& operator=(ForwardList&& another) noexcept;

        void Push(value_t value) noexcept;
        bool Erase(const key_t& key) noexcept;
        const value_t* Find(const key_t& key) const noexcept;
        value_t* Find(const key_t& key) noexcept;
        Vector<value_t> ToVector() const noexcept;
        Vector<const value_t*> ToPointerVector() const noexcept;
        template <typename Predicate>
        void ForEach(Predicate pred) const noexcept;
        size_t Size() const noexcept;
        bool Empty() const noexcept;
        template <typename Predicate>
        Vector<const Company*> LookUp(Predicate pred) const noexcept;
        size_t LastComparisonAmount() const noexcept;
    private:
        // узел списка
        struct Node {
            Company data;
            // указатель на следующий узел
            Node* next;
        };

        // указатель на начало списка
        Node* head;
        // количество элементов в списке
        size_t size;
        // количество сравнений объектов Company
        // за последний вызов Find/Erase
        mutable size_t last_comparison_amount;

        Node* AllocateNode(value_t data) const noexcept;
        void DeallocateNode(Node* node) const noexcept;
        size_t DeallocateList(Node* start) const noexcept;
        bool Equals(const key_t& lhs, const key_t& rhs) const noexcept;
    };


    template <typename Predicate>
    Vector<const Company*> ForwardList::LookUp(Predicate pred) const noexcept {
        Vector<const Company*> result;

        ForEach([&result, &pred](const value_t &value) {
            if (pred(value))
                result.PushBack(&value);
        });
       
        return result;
    }


    template <typename Function>
    void ForwardList::ForEach(Function func) const noexcept {

        for (Node* it = head; it != nullptr; it = it->next) {
            func(it->data);
        }

    }

}
