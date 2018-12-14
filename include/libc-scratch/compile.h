
#ifndef  __LIB_SCRATCH_COMPILE_H
#define __LIB_SCRATCH_COMPILE_H 1

#ifndef LIBC_SCRATCH_IMPORT
#define LIBC_SCRATCH_IMPORT  __declspec(dllimport)
#endif

#ifndef LIBC_SCRATCH_EXPORT
#define LIBC_SCRATCH_EXPORT   __declspec(dllexport)
#endif

#ifndef LIBC_SCRATCH_LINKAGE
//适用于用于导入第三库，而不是本地实现，但本地需要提供接口的函数
#define LIBC_SCRATCH_LINKAGE   LIBC_SCRATCH_IMPORT
#endif

#ifdef LIBC_SCRATCH_EXPORTS
#define LIBCAPI LIBC_SCRATCH_EXPORT
#else
#define LIBCAPI LIBC_SCRATCH_IMPORT
#endif


#endif /** __LIB_SCRATCH_COMPILE_H */
