#include "ffi.h"

ffi_type _ffi_type_void = {.type = _FFI_TYPE_VOID};
ffi_type _ffi_type_i32 = {.type = _FFI_TYPE_I32};
ffi_type _ffi_type_i64 = {.type = _FFI_TYPE_I64};
ffi_type _ffi_type_f32 = {.type = _FFI_TYPE_F32};
ffi_type _ffi_type_f64 = {.type = _FFI_TYPE_F64};

ffi_status ffi_prep_cif(ffi_cif *cif, ffi_abi abi, unsigned int nargs,
                        ffi_type *rtype, ffi_type **atypes) {

  cif->rtype = rtype;
  cif->arg_types = atypes;
  cif->nargs = nargs;

  unsigned int acc = 0;
  for (unsigned int i = 0, rdx = 1; i < nargs; ++i, rdx *= 5) {
    acc += rdx * atypes[i]->type;
  }
  acc = acc * 5 + rtype->type;
  cif->encoding = acc; // 0e100

  return FFI_OK;
}
