#include <iostream>

namespace RISKY_POINTER {
struct Something {
  auto perform() -> void { std::cout << "perform" << std::endl; }
};

auto do_something() -> void {
  Something *ptr = new Something();
  ptr->perform();
  delete ptr;
}
} // namespace RISKY_POINTER

namespace SINGLE_OWNER_POINTER {
template <typename T> class Holder {
public:
  Holder() : ptr(0) {}
  explicit Holder(T *p) : ptr(p) {}
  ~Holder() {
    std::cout << "delete ptr" << std::endl;
    delete ptr;
  }
  Holder<T> &operator=(T *p) { // assign
    delete ptr;
    ptr = p;
    return *this;
  }
  T &operator*() const { return *ptr; }
  T *operator->() const { return ptr; }
  T *get() const { return ptr; }
  void release() { // 소유권 해제
    ptr = 0;
  }
  void exchange_with(Holder<T> &h) { std::swap(ptr, h.ptr); }

private:
  T *ptr;
  Holder(Holder<T> const &);               // do not copy construct
  Holder<T> &operator=(Holder<T> const &); // do not copy allocation
};

auto do_something() -> void {
  Holder<RISKY_POINTER::Something> ptr(new RISKY_POINTER::Something());
  ptr->perform();
}
} // namespace SINGLE_OWNER_POINTER

namespace SHARED_POINTER {
size_t *alloc_counter() {
  return static_cast<size_t *>(malloc(sizeof(size_t)));
}
void dealloc_counter(size_t *counter) { free(counter); }
class SimpleReferenceCounter {
public:
  SimpleReferenceCounter() { counter = nullptr; }
  template <typename T> void init(T *) {
    counter = alloc_counter();
    *counter = 1;
    std::cout << "inited counter " << *counter << std::endl;
  }
  template <typename T> void dispose(T *) { dealloc_counter(counter); }
  template <typename T> void increment(T *) {
    ++*counter;
    std::cout << "inc-ed counter " << *counter << std::endl;
  }
  template <typename T> void decrement(T *) {
    --*counter;
    std::cout << "dec-ed counter " << *counter << std::endl;
  }
  template <typename T> bool is_zero(T *) { return *counter == 0; }

private:
  size_t *counter;
};

class StandardObjectPolicy {
public:
  template <typename T> void dispose(T *object) { delete object; }
};

template <typename T, typename CounterPolicy = SimpleReferenceCounter,
          typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr : private ObjectPolicy, private CounterPolicy {
private:
  typedef CounterPolicy CP;
  typedef ObjectPolicy OP;

public:
  CountingPtr() : object_pointed_to(nullptr) {}
  explicit CountingPtr(T *p) { init(p); }
  CountingPtr(CountingPtr<T, CP, OP> const &cp) : OP(cp), CP(cp) { attach(cp); }
  ~CountingPtr() { detach(); }
  CountingPtr<T, CP, OP> &operator=(T *p) { // 내장 포인터 할당
    assert(p != object_pointed_to);
    detach();
    init(p);
    return *this;
  }
  CountingPtr<T, CP, OP> &
  operator=(CountingPtr<T, CP, OP> const &p) { // 복사 할당자
    if (object_pointed_to != p.object_pointed_to) {
      detach();
      CP::operator=(p);
      OP::operator=(p);
      attach(p);
    }
    return *this;
  }
  T *operator->() const { return object_pointed_to; }
  T &operator*() const { return *object_pointed_to; }

private:
  void init(T *p) {
    if (p)
      CounterPolicy::init(p);
    object_pointed_to = p;
  }
  void attach(CountingPtr<T, CP, OP> const &p) {
    object_pointed_to = p.object_pointed_to;
    if (p.object_pointed_to)
      CounterPolicy::increment(p.object_pointed_to);
  }

  void detach() {
    if (object_pointed_to) {
      CounterPolicy::decrement(object_pointed_to);
      if (CounterPolicy::is_zero(object_pointed_to)) {
        std::cout << "detached" << std::endl;
        CounterPolicy::dispose(object_pointed_to);
        ObjectPolicy::dispose(object_pointed_to);
      }
    }
  }

private:
  T *object_pointed_to; //가리키고 있는 객체가 없다면 nullptr
};

auto do_something() -> void {
  SHARED_POINTER::CountingPtr<RISKY_POINTER::Something> ptr(
      new RISKY_POINTER::Something());
  auto ptr2 = ptr;

  SHARED_POINTER::CountingPtr<RISKY_POINTER::Something> ptr3(
      new RISKY_POINTER::Something());
  auto ptr4 = ptr3;
}

} // namespace SHARED_POINTER

auto main() -> int {
  RISKY_POINTER::do_something();
  SINGLE_OWNER_POINTER::do_something();
  SHARED_POINTER::do_something();
  return 0;
}
