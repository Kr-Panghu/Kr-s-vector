#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP
#include "exceptions.hpp"
#include <climits>
#include <cstddef>
#include <iostream>
using namespace std;

namespace sjtu {
template<typename T>
class vector{
private:
    T **elements;//a dynamic array of elements;
    int capacity;//the size of array;
    int count;//the number of elements in use;
    friend class iterator;
    friend class const_iterator;

public:
    class const_iterator;//先声明一个const迭代器
    class iterator {

    private:

    const vector *vp;
    int index;//position
    T **_elements;  //for "operate*" only;
    friend class const_iterator;
    friend class vector;

    public:
        iterator(){
            T** elements = nullptr;
            this->vp = nullptr;
            _elements = nullptr;
        }
        iterator(const iterator &it){
            this->vp = it.vp;
            this->index = it.index;
            _elements = it._elements;
        }
        iterator(const vector *vp, int index){
            this->vp = vp;
            this->index = index; 
            _elements = vp -> elements;
        }
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            return iterator(vp, index + n);
        }
        iterator operator-(const int &n) const {
            return iterator(vp, index - n);
        }

        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (vp != rhs.vp) throw std::string("invaild_iterator");
            return index - rhs.index;
        }
        iterator& operator+=(const int &n) {
            index += n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            index -= n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator tmp = *this;
            index++;
            return tmp;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            index++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator tmp = *this;
            index--;
            return tmp;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            index--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *_elements[index];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return vp == rhs.vp && index == rhs.index;
        }
        bool operator==(const const_iterator &rhs) const {
            return vp == rhs.vp && index == rhs.index;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }
        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }
    };

    class const_iterator {
    private:
    
    const vector *vp;
    int index;//position
    T **_elements;

    friend class iterator;
    friend class vector;

    public:
        const_iterator(){
            T** elements = nullptr;
            this->vp = nullptr;
            _elements = nullptr;
        }
        const_iterator(const iterator &it){
            this->vp = it.vp;
            this->index = it.index;
            _elements = it._elements;
        }
        const_iterator(const vector *vp, int index){
            this->vp = vp;
            this->index = index; 
            _elements = vp -> elements;
        }
        const_iterator operator+(const int &n) const {
            return iterator(vp, index + n);
        }
        const_iterator operator-(const int &n) const {
            return iterator(vp, index - n);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            if (vp != rhs.vp) throw std::string("invaild_iterator");
            return index - rhs.index;
        }
        const_iterator& operator+=(const int &n) {
            index += n;
            return *this;
        }
        const_iterator& operator-=(const int &n) {
            index -= n;
            return *this;
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            index++;
            return tmp;
        }
        /**
         * TODO ++iter
         */
        const_iterator& operator++() {
            index++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            index--;
            return tmp;
        }
        /**
         * TODO --iter
         */
        const_iterator& operator--() {
            index--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *_elements[index];
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return vp == rhs.vp && index == rhs.index;
        }
        bool operator==(const const_iterator &rhs) const {
            return vp == rhs.vp && index == rhs.index;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }
        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }
    };
    
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    vector(){
        capacity = 10;
        elements = new T *[capacity];
        count = 0;
    }
    /*vector() :
        capacity(10), // for example
        count(0),
        elements(static_cast<T*>(malloc(sizeof(T) * capacity))) {
    }*/
    vector(const vector &other) {
        capacity = other.capacity;
        count = other.count;
        elements = new T *[capacity];
        for (int i = 0; i < count; i++)
        {
            elements[i] = new T(*other.elements[i]);
        }
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        for (int i = 0; i < count; i++)
        {
            delete elements[i];
            elements[i] = nullptr;
        }
        delete[] elements;
    }
    /**
     * TODO Assignment operator
     */
    
    vector &operator=(const vector &other) {
        iterator tmp1 = this -> end();
        const_iterator tmp2 = other.cend();
        if (tmp1 != tmp2){
            if (elements != nullptr) delete[] elements;
            deepCopy(other);
        }
        return *this;
    }
    vector deepCopy(const vector &other){
        capacity = other.capacity;
        count = other.count;
        elements = new T *[capacity];
        for (int i = 0; i < count; i++)
        {
            elements[i] = new T(*other.elements[i]);
        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos) {
        if (pos < 0 || pos >= count) throw std::string("index_out_of_bound");
        return *elements[pos];
    }
    const T & at(const size_t &pos) const {
        if (pos < 0 || pos >= count) throw std::string("index_out_of_bound");
        return *elements[pos];
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) {
        if (pos < 0 || pos >= capacity) throw std::string("index_out_of_bound");
        return *elements[pos];
    }
    const T & operator[](const size_t &pos) const {
        if (pos < 0 || pos >= capacity) throw std::string("index_out_of_bound");
        return *elements[pos];
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if (count == 0) throw std::string("container_is_empty");
        return *elements[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if (count == 0) throw std::string("container_is_empty");
        return *elements[count-1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(this, 0);
    }
    const_iterator cbegin() const {
        return const_iterator(this, 0);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(this, count);
    }
    const_iterator cend() const {
        return const_iterator(this, count);
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        return count == 0;
    }
    /**
     * returns the number of elements
     */ 
    size_t size() const {
        return count;
    }
    /**
     * clears the contents
     */
    void clear() {/////////////////////////////////////////
        for (int i =0; i < count; i++){
        if (*elements != nullptr) delete[] elements;
        *elements = nullptr;
        }
        count = 0; capacity = 10;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        if (count == capacity) doubleCapacity();
        elements[count] = new T(*elements[count - 1]);
        for (int i = count - 2; i >= pos.index; i--)
        {
            delete elements[i + 1];
            elements[i + 1] = new T(*elements[i]);
        }
        count++;
        delete elements[pos.index];
        elements[pos.index] = new T(value);
        return pos;
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */

    iterator insert(const size_t &ind, const T &value) {
        if(ind < 0 || ind > count) throw std::string("index_out_of_bound");
        if (count == capacity) doubleCapacity();
        if (count == ind){
            elements[ind] = new T(value);
            count++; return this-> begin();
        }
        elements[count] = new T(*elements[count - 1]);
        for (int i = count - 2; i >= ind; i--)
        {
            delete elements[i + 1];
            elements[i + 1] = new T(*elements[i]);
        }
        //std::cout << ind << "!" << std::endl;
        //std::cout << elements[ind] << std::endl;
        delete elements[ind];
        elements[ind] = new T(value);
        count++;
        return this -> begin() + ind;
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        if (pos.index == count - 1)
        {
            delete elements[count - 1];
            elements[count - 1] = nullptr;
            count--; return pos;
        }
        for (int i = pos.index + 1; i < count; i++)
        {
            delete elements[i - 1];
            elements[i - 1] = new T(*elements[i]);
        }
        delete elements[count - 1];
        elements[count - 1] = nullptr;
        count--;
        return pos;
    }
    /** 
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if (ind < 0 || ind >= count) throw std::string("index_out_of_bound");
        if (ind == count - 1)
        {
            delete elements[count - 1];
            elements[count - 1] = nullptr;
            count--;
            return iterator(this, ind);
        }
        for (int i = ind + 1; i < count; i++)
        {
            delete elements[i - 1];
            elements[i - 1] = new T(*elements[i]);
        }
        count--;
        return iterator(this, ind);
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        insert(count, value);
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if (count == 0) throw std::string("container_is_empty!");
        erase(count-1);
    }

 /*
 * This function doubles the array capacity, copies the old elements
 * into the new array, and then frees the old one.
 */

    void doubleCapacity(){
        T **tmp = new T *[count];
        for (int i = 0; i < count; i++)
        {
            tmp[i] = new T(*elements[i]);
            delete elements[i];
            elements[i] = nullptr;
        }
        delete[] elements;
        capacity *= 2;
        elements = new T *[capacity];
        //T *array = (T*)malloc(capacity * sizeof(T));
        for (int i = 0; i < count; i++){
            elements[i] = new T(*tmp[i]);
            delete tmp[i];
            tmp[i] = nullptr;
        }
        delete[] tmp;
        //cout << elements[0] << '!' << endl;
    }
}; 

}

#endif
