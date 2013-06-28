
#ifndef __MAYBE_H
#define __MAYBE_H

#include <iostream>
#include <exception>

namespace maybe {

  class novalue: public std::exception {
    virtual const char* what() const throw() {
      return "Tried to get value from <Nothing>";  
    }
  };

  static novalue err_noval;

  template<typename T>
  struct Maybe {
    bool isJust;
    T value;
  };

  template<typename T> 
  Maybe<T> nothing() {
    Maybe<T> m;
    m.isJust = false;
    return m;
  }

  template<typename T>
  Maybe<T> just(const T& x) {
    Maybe<T> m;
    m.isJust = true;
    m.value = x;
    return m;
  }

  template<typename T>
  bool isJust(const Maybe<T>& m) {
    return m.isJust;
  }

  template<typename T>
  bool isNothing(const Maybe<T>& m) {
    return !isJust(m);
  }

  template<typename T>
  T fromJust(const Maybe<T>& m) throw(novalue) {
    if (isNothing(m))
      throw err_noval;
    else
      return m.value;
  }

  template<typename T>
  bool operator==(const Maybe<T>& m, const Maybe<T>& n) {
    return !(isJust(m) ^ isJust(n)) && (isNothing(m) || fromJust(m) == fromJust(n));
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& o, const Maybe<T>& m) {
    if (isNothing(m))
      o << "Nothing";
    else
      o << "Just " << m.value;
    return o;
  }
}

#endif

