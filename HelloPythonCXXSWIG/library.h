#ifndef LIBRARY_H_
#define LIBRARY_H_

class Library {

 public:
  Library(int x);

  int add(int x);
  int sub(int x);

 private:
  int value_;
};

#endif  // LIBRARY_H_
