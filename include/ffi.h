#ifndef FFI_H
#define FFI_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
  _FFI_TYPE_VOID = 0,
  _FFI_TYPE_I32,
  _FFI_TYPE_I64,
  _FFI_TYPE_F32,
  _FFI_TYPE_F64,
} _FFI_TYPE_ENUM;

typedef enum {
  FFI_DEFAULT_ABI = 0,
} ffi_abi;

typedef struct {
  _FFI_TYPE_ENUM type;
} ffi_type;

typedef enum {
  FFI_OK = 0,
  FFI_BAD_TYPEDEF,
  FFI_BAD_ABI,
  FFI_BAD_ARGTYPE
} ffi_status;

typedef struct {
  unsigned int encoding;
  unsigned int nargs;
  ffi_type **arg_types;
  ffi_type *rtype;
} ffi_cif;

typedef unsigned long long ffi_arg;

#define ffi_type_void _ffi_type_void
#define ffi_type_uint8 _ffi_type_i32
#define ffi_type_uint16 _ffi_type_i32
#define ffi_type_sint8 _ffi_type_i32
#define ffi_type_sint16 _ffi_type_i32
#define ffi_type_sint32 _ffi_type_i32
#define ffi_type_sint64 _ffi_type_i64
#define ffi_type_float _ffi_type_f32
#define ffi_type_double _ffi_type_f64
#define ffi_type_pointer _ffi_type_i32

extern ffi_type _ffi_type_void;
extern ffi_type _ffi_type_i32;
extern ffi_type _ffi_type_i64;
extern ffi_type _ffi_type_f32;
extern ffi_type _ffi_type_f64;

ffi_status ffi_prep_cif(ffi_cif *cif, ffi_abi abi, unsigned int nargs,
                        ffi_type *rtype, ffi_type **atypes);

void ffi_call(ffi_cif *cif, void (*fn)(void), void *rvalue, void **avalue);

#if defined(__cplusplus)
}
#endif

#endif