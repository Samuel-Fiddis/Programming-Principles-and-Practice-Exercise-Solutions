// Implement a simple unique_ptr supporting only a constructor, destructor, –>, *, and release().
// In particular, don’t try to implement an assignment or a copy constructor.


template<class T>
class Unique_ptr {
	T* p;
public:
	explicit Unique_ptr(T* arg) : p{arg} {}

	T operator*() { return *p; }
	T operator->() { return p; }

	T* release() {
		T* s = p;
		p = nullptr;
		return s; 
	}

	~Unique_ptr() { delete p; }
};