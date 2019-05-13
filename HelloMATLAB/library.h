#ifndef LIBRARY_H_
#define LIBRARY_H_

#ifndef EXPORT
#  ifdef _WIN32
#    define EXPORT __declspec(dllexport)
#  else
#    define EXPORT
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int add(int a, int b);
EXPORT int sub(int a, int b);

#ifdef __cplusplus
}
#endif

#endif  // LIBRARY_H_
