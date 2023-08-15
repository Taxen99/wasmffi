# WasmFFI

A quick and dirty port of libffi to WebAssembly!
Based on https://github.com/tweag/libffi-wasm32

# Supported Features

WasmFFI supports ```ffi_prep_cif```, ```ffi_call``` (with a limited amount of arguments)
and 10 types, including:
```
ffi_type_void
ffi_type_uint8
ffi_type_uint16
ffi_type_sint8
ffi_type_sint16
ffi_type_sint32
ffi_type_sint64
ffi_type_float
ffi_type_double
ffi_type_pointer
```

Closure API is not supported.

# Building

Run ```make all``` to build ```example``` and ```libffi.a```

Optionally specify ```MAX_NUM_ARGS``` to specify the maximum number of arguments ```ffi_call``` can take (default = 2)