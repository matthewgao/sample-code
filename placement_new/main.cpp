#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <memory.h>

using namespace std;
class base{
    public:
    base(){}
    ~base(){}
    virtual void print1(){
        printf("base class\n");
    }
};

class test : public base{
    public:
    test():vec(nullptr){
        vec = new vector<string>();
        vec->push_back("test string1");
        vec->push_back("test string2");
    }
    ~test(){
        delete vec;
        vec = nullptr;
    }
    void print(){
        
        for(auto itr: *vec){

            printf("test::out: %s\n", itr.c_str());
        }
    }
    virtual void print1(){
        printf("test1\n");
    }
    vector<string> *vec;
    static string str;
    int i;
};
string test::str = "static str";
//int test::i = 25;
int main(){
    vector<string>* ptr = (vector<string>*)malloc(sizeof(vector<string>));
    printf("sizeof %ld\n", sizeof(vector<string>));
    /*
     * Even if the ptr didn't been called by a placement new, 
     * No constructor be called, we can still use it, as long as the 
     * constructor didn't new any object.
     */
    ptr = new (ptr) vector<string>;
    ptr->push_back("abcde");
    ptr->push_back("1234");
    printf("sizeof %ld\n", sizeof(vector<string>));
    for(auto itr: *ptr){

        printf("out: %s\n", itr.c_str());
    }

    ptr->~vector<string>();
    free(ptr);

    printf("test sizeof %ld\n",sizeof(test));
    test *t_ptr = (test*)malloc(sizeof(test));
    base *b_ptr = t_ptr;

    printf("print static member without construct:%s\n", t_ptr->str.c_str());
    memset(t_ptr,0,sizeof(test));
    printf("print static member without construct:%s\n", t_ptr->str.c_str());
    t_ptr = new (t_ptr) test;
    /*
     * if there is a virtual function, we can't use it without 
     * construct.
     */
    b_ptr->print1();
    t_ptr->print1();
    t_ptr->print();

    printf("vec addr %lx\n",(unsigned long)t_ptr->vec);
    void* temp_ptr = t_ptr->vec;
    memset(t_ptr,0,sizeof(test));
    printf("vec addr %lx\n",(unsigned long)t_ptr->vec);
    t_ptr->vec = (vector<string>*)temp_ptr;
    t_ptr->print1();
    t_ptr->print();
    /*
     * class ptr and vec are at the same address.
     * that means class cost no space.
     * but a class without any variable member, the sizeof it is 1(long ago is 0)
     */
    printf("test addr %lx\n",(unsigned long)t_ptr);
    printf("vec addr %lx\n",(unsigned long)&(t_ptr->vec));

    free(t_ptr);

    return 0;

}
