#include <vector>
#include <iostream>

using namespace std;

template<class T> class counted_ptr{
  T* t;
  int* count;

public:
  counted_ptr(): t{nullptr}, count{nullptr} {}
  explicit counted_ptr(T t1): t{new T(t1)}, count{new int(1)} { cerr << "counted_ptr creation\n"; }

  counted_ptr(const counted_ptr& a);
  counted_ptr& operator=(const counted_ptr& a);
  T* operator*(); // Pointer opperator

  ~counted_ptr(){
    if(*count == 1){
      delete t;
      delete count;
      cerr << "last counted_ptr deleted\n";
    }
    else {
      (*count)--;
      cerr << "counted_ptr count is " << *count << endl;
    }
  }

  int get_count(){return *count;}
  int* get_count_address(){return count;}
};

template<class T> counted_ptr<T>::counted_ptr(const counted_ptr<T>& a){
  cerr << "counted_ptr copy construction\n";
  t = a.t;
  count = a.count;
  (*count)++;
}

template<class T> counted_ptr<T>& counted_ptr<T>::operator=(const counted_ptr<T>& a){
  cerr << "counted_ptr copy assignment\n";
  if(this == &a) return *this;

  if(t == a.t && count == a.count) return *this;

  t = a.t;
  count = a.count;
  (*count)++;
}

template<class T> T* counted_ptr<T>::operator*(){ return t; }

int main(){
  counted_ptr<int> c(2);
  counted_ptr<int> d = c;
  counted_ptr<int> e{c};
  counted_ptr<int> f;
  f = e;
  c = d;

  cout << *c  << endl;
  cout << *d  << endl;
  cout << *e  << endl;
  cout << *f  << endl;

  cout << c.get_count()<< endl;
  cout << d.get_count()<< endl;
  cout << e.get_count()<< endl;
  cout << f.get_count()<< endl;

  cout << c.get_count_address()<< endl;
  cout << d.get_count_address()<< endl;
  cout << e.get_count_address()<< endl;
  cout << f.get_count_address()<< endl;
}
