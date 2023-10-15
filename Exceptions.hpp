#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class UserQuitException : public std::runtime_error {
public:
  UserQuitException();
};

class InvalidChoiceException : public std::runtime_error {
public:
  InvalidChoiceException();
};

// ... Additional exception classes ...

#endif // EXCEPTIONS_HPP
