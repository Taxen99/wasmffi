# WasmFFI

A quick and dirty implementation of libffi in WebAssembly!
Based on https://github.com/tweag/libffi-wasm32

# Building

Run ```make all``` to build ```example``` and ```libffi.a```

Optionally specify ```MAX_NUM_ARGS``` to specify the maximum number of arguments ```ffi_call``` can take (default = 2)