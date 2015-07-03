 #include <iostream>
 #include <iterator>
 #include <vector>
 #include <string.h>
 #include <algorithm>
 using namespace std;
 class test{
public:
    test(){}
     ~test(){}
     void print(){

         cout<< str.c_str() <<endl;
     }
     void set(string s){
         str = s;
     }
    static 
     string str;
 };
 string test::str = "abc";
 int main(){
    // std::ostream_iterator< test > out_iter(cout, " \n " );
     std::string str1("abbb");
    test *t = new test();
     t->print();
     t->set(str1);
     t->print();
    // *out_iter++ = *t;


 }
