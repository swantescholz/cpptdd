#ifndef TDD_SINGLETON_H_
#define TDD_SINGLETON_H_

namespace tdd {

template <typename T>
class Singleton {
protected:
	static T* instance;
	Singleton() {}
private:
	Singleton(const Singleton& other) = delete;
	Singleton& operator= (const Singleton& other) = delete;
public:
	static T& getInstance() {
		if (instance == nullptr)
			instance = new T();
		return *instance;
	}
		
};

template<typename T> T* Singleton<T>::instance = nullptr;

} // namespace tdd




#endif
