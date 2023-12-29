#pragma once
#include "config.h"
#include <stdlib.h>
#include <initializer_list>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#define mem_alloc malloc
#define mem_realloc realloc
namespace Chaos{
    template <typename T>
    class Set{
        private:
            T * data;
            size_t allocated_length;
            size_t count;
        public: 
        //default constructor
        Set(){
            #ifdef DEBUG_MEMORY
            printf("default constructor called\n");
            #endif
            #ifdef DEBUG_ALL
            printf("default constructor called\n");
            #endif
            this->data = (T*)mem_alloc(8*sizeof(T));
            this->count = 0;
            this->allocated_length = 8;
        }
        //copy constructor
        Set(Set<T> &t){
            #ifdef DEBUG_MEMORY
            printf("copy constructor called on: ");
            t.debug_println();
            #endif
            #ifdef DEBUG_ALL
            printf("copy constructor called on: ");
            t.debug_println();
            #endif
            this->data = (T*)mem_alloc(t.allocated_length*sizeof(T));
            this->count = t.count;
            this->allocated_length = t.allocated_length;
            memset(this->data, 0, this->allocated_length*sizeof(T));
            memcpy(this->data, t.data, this->count*sizeof(T));
        }
        //constructor from initalizer list
        Set(std::initializer_list<T> list){
            #ifdef DEBUG_MEMORY
            printf("initializer list constructor called: ");
            #endif
            #ifdef DEBUG_ALL
            printf("initializer list constructor called: ");
            #endif
            size_t alloc_sz = pow(2,ceil(log2(list.size())));
            alloc_sz = alloc_sz>8 ? alloc_sz :8;
            #ifdef DEBUG_MEMORY
            printf("alloc size: %zu list size %zu\n", alloc_sz, list.size());
            #endif
            #ifdef DEBUG_ALL
            printf("alloc size: %zu list size %zu\n", alloc_sz, list.size());
            #endif
            this->data =(T*)mem_alloc(alloc_sz*sizeof(T));
            for(int i =0; i<list.size(); i++){
                this->data[i] = list.begin()[i];
            }
            this->count = list.size();
            this->allocated_length = alloc_sz;
            #ifdef DEBUG_MEMORY
            debug_println();
            #endif
            #ifdef DEBUG_ALL
            debug_println();
            #endif
        }
        //destructor
        ~Set(){
            #ifdef DEBUG_MEMORY
            printf("destructor called: ");
            debug_println();
            #endif
            #ifdef DEBUG_ALL
            printf("destructor called: ");
            debug_println();
            #endif
            void * tmp = this->data;
            free(tmp);
        }
        void operator= (const Set<T> &t)const &{
            #ifdef DEBUG_MEMORY
            printf("assignment operator called on: ");
            debug_print();
            printf(" to ");
            t.debug_println();
            #endif
            #ifdef DEBUG_ALL
            printf("assignment operator called on: ");
            debug_print();
            printf(" to ");
            t.debug_println();
            #endif
            mem_realloc(this->data, this->allocated_length*sizeof(T));
        }
        bool operator== (const Set<T> &t) const &{
            if(t.count != this->count){
                return false;
            }
            for(int i =0; i<this->count; i++){
                if(t.data[i] != this->data[i]){
                    return false;
                }
            }
            return true;
        }
        void Add(T value){
            int idx = FindLocation(value);
            if(this->data[idx] == value){
                return;
            }
            if(this->count+1>this->allocated_length){
                this->allocated_length = this->allocated_length*2;
                void * tmp = realloc(this->data, this->allocated_length*sizeof(T));
                if (tmp == NULL) {
                     free(tmp);
                } 
                else {
                    this->data = (int*)tmp;
                }
            }
            for(int i =this->count+1; i>idx; i--){
                    this->data[i] = this->data[i-1];
            }
            this->data[idx] = value;
            this->count++;
        }
        void Remove(T value){
            int idx = FindLocation(value);
            if(idx>=this->count || idx<0){
                return;
            }
            for(int i = idx+1; i<this->count; i++){
                this->data[i-1] = this->data[i];
            }
            this->count--;
        }
        bool Contains(const T &value) const &{
            return this->data[FindLocation(value)] == value;
        }
        size_t Cardinality() const &{
            return this->count;
        }
        int64_t FindLocation(const T &value) const &{
            if(this->count<1){
                return 0;
            }
            for(int i =0; i<this->count; i++){
                if(value<=this->data[i]){
                    return i;
                }
            }
            return this->count;
        }
        void debug_println() const &{
            printf("{");
            for(int i =0; i<this->count; i++){
                std::cout<<this->data[i];
                if(i != this->count-1){
                    printf(", ");
                }
            }
            printf("}\n");
        }
        void debug_print() const &{
            printf("{");
            for(int i =0; i<this->count; i++){
                std::cout<<this->data[i];
                if(i != this->count-1){
                    printf(", ");
                }
            }
            printf("}");
        }
        void iter(void(*foo)(T const))const &{
            for(int i =0; i<this->count;i++){
                foo(data[i]);
            }
        }
        void iter_mut(void(*foo)(T&)){
            for(int i =0; i<this->count; i++){
                foo(data[i]);
            }
        }
        void iter(void(*foo)(T const , void *),void * args = NULL) const &{
            for(int i =0; i<this->count;i++){
                foo(data[i],args);
            }
        }
        void iter_mut( void(*foo)(T&, void *), void * args = NULL){
            for(int i =0; i<this->count; i++){
                foo(data[i], args);
            }
        }
    };
};
#undef mem_alloc