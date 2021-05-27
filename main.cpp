#include <memory>
#include <iostream>

template <class T> 
class Vector 
{
    public:
        typedef T* iterator; // pridėta
        typedef const T* const_iterator; // pridėta
        typedef size_t size_type; // pridėta
        typedef T value_type; // pridėta
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    //rule of three
        //default
        Vector() { create(); }
        
        //sukuria n didumo vektoriu su val reiksme, jei nezinoma val reiksme sukuria n tusciu
        explicit Vector(size_type n, const T& val = T{}) { create(n, val); }
        
        //sukuria nauja vektoriu darydamas kito vector copy
        Vector(const Vector& v){create(v.begin(), v.end()); }

        Vector& operator=(const Vector& rhs)
        {
            if(&rhs != this)
            {
                //atlaisvina seno obj atminti
                uncreate();
                //copy elementus
                create(rhs.begin(), rhs.end());
            }
            return *this;
        }
        ~Vector(){uncreate(); }

    //iterators
        iterator begin() {return data; }
        const_iterator begin() const { return data; }

        iterator end() {return dataEnd; }
        const_iterator end() const { return dataEnd; }

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator  rbegin() const { return const_reverse_iterator(end()); }
        
    // size funkcija
        size_type size(){ return limit - data; }
        size_type max_size(){ return alloc.max_size;}
        void resize(size_type n, const T& val = T{})
        {
            if( n > size() ){
                std::cout<<n-size()<<"\n";
                insert(end(), n-size(),val);
            }
            else if (n< size()){
                erase(begin()+n, end());
            }
        }
            size_type capacity() const noexcept{
                return limit-data;
            }
            bool empty() const noexcept{
                return data-dataEnd==0;
            }
            void reserve (size_type n){
                if(n > capacity()){
                    grow(n);
                }
            }
            void shrink_to_size(){
                grow(size());
            }

    // indeksavimas
        T& operator[](size_type i) { return data[i]; }
        const T& operator[](size_type i) const { return data[i]; }
    //at
        T& at(size_type n){ return data[n]; }
        const T& at (size_type n) const{ return data[n]; }
    //head
        T& head(){ return *data; }
        const T& head() const { return *data; }

    //tail
        T& tail(){ return *(dataEnd - 1); }
        const T& tail() const{ return *(dataEnd - 1); }
    //data
        T* data1() noexcept{ return data; }
        const T* data1() const noexcept{ return data; }

    // push_back() realizacija
        void push_back(const T& val)
        {
        if (dataEnd == limit) // išskirti vietos, jei reikia
        grow(); // TODO: reikia realizuoti
        unchecked_append(val) ; // įdėti naują elementą
        }
    
    // pop_back() realizacija
        void pop_back()
        {
            alloc.destroy(dataEnd - 1);
        }
    
    // assign() realizacija 
        void assign(size_type n, const T& val)
        {
            uncreate();
            create(n, val);
        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last){
            uncreate();
            create(first,last);
        }
    
    // erase() realizacija
        iterator erase(iterator position)
        {
            if(position < begin() || position > end())
            {
                return position;
            }
            else
            {
                alloc.destroy(position);
                dataEnd = std::uninitialized_copy(position + 1, end(), position);
                return position;
            }
        }

        iterator erase(iterator first, iterator last)
        {
            if (first < begin() || last > end()) { return first; } 
            else
            {
                iterator it = last;
                while(it != first) alloc.destroy(--it); //delete elements in range [first,last)

                dataEnd = std::uninitialized_copy(last, end(), first); // copy elements from [last,end())

                return first+1; 
            }
        }
     
    //clear() realizacija
        void clear()
        {
            uncreate();
        }

    //insert() realizacija
        iterator insert(iterator position, const T& val)
        {
            if(position < data || position > dataEnd){ return data; } //should add error
            else{
                int index = std::distance(data,position);
                if(dataEnd == limit) grow(); //changes pointer
                push_back(*(dataEnd-1));
                for(size_t i= size()-1; i>index; i-- ){
                    data[i]= data[i-1];
                }
                data[index] = val;

                return &data[index];
            }
        }

        iterator insert (iterator position, size_type n, const T& val){
            for(size_t i = 0; i< n; i++){
                position = insert(position,val);
            }
            return position;
        }
    private:
        iterator data; // pakeista iš T* į iterator
        iterator dataEnd;
        iterator limit; // pakeista iš T* į iterator

        std::allocator<T> alloc;

    void create()
    {
        data = dataEnd = limit = nullptr;
    }

    void create(size_type n, const T& val)
    {
        data = alloc.allocate(n);
        limit = dataEnd = data + n;
        unintialized_fill(data, dataEnd, val);
    }

    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate(j-i);
        limit = dataEnd = std::uninitialized_copy(i, j, data);
    }

    void uncreate()
    {
        if (data)
        {
            iterator it = dataEnd;
            while(it != data)
            {
                alloc.destroy(it);
                it--;
            }
            alloc.deallocate(data, limit - data);
        }
        data = limit = dataEnd = nullptr;
    }

    void grow()
    {
        size_type newSize = std::max(2 * (limit - data), ptrdiff_t(1));

        iterator newPlace = alloc.allocate(newSize);
        iterator newLast = std::uninitialized_copy(data, dataEnd, newPlace);

        uncreate();

        data = newPlace;
        dataEnd = newLast;
        limit = data + newSize;
    }

    void grow(size_type newSize)
    {
        iterator newPlace = alloc.allocate(newSize);
        iterator newLast = std::uninitialized_copy(data, dataEnd, newPlace);

        uncreate();

        data = newPlace;
        dataEnd = newLast;
        limit = data + newSize;
    }

    void unchecked_append(const T& val)
    {
        alloc.construct(dataEnd++, val);
    }
};
