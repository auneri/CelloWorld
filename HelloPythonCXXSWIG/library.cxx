#include "library.h"


Library::Library(int x) {
  value_ = x;
}


int Library::add(int x) {
  value_ += x;
  return value_;
}


int Library::sub(int x) {
  value_ -= x;
  return value_;
}
