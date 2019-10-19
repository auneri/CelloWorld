#ifndef LIBRARY_H_
#define LIBRARY_H_

class Library {

 public:
  Library(int x) { value_ = x; }

  int add(int x) { value_ += x; return value_; }
  int sub(int x) { value_ -= x; return value_; }

 private:
  int value_;
};

#endif  // LIBRARY_H_
