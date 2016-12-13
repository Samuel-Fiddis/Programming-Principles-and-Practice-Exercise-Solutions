template<class T>
class Count_ptr {
	T* p;
	int* cnt;
public:
	explicit Count_ptr(T* arg) :p{ arg }, count{ new int(1) } {}
	explicit Count_ptr(Count_ptr arg) : p{ arg.p }, count { arg.count } { ++(*count) }
	~Count_ptr();

	T operator*() { return *p; }
	T* operator->() { return p; }

	void set_pointer(T arg) { *p = arg; }

	int count() { return *cnt; }
};

template<class T> Count_ptr<T>::~Count_ptr() {
	if (cnt <= 1)
	{
		delete cnt;
		detele p;
	}
	else --(*cnt);
}