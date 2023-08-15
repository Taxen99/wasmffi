#include <ffi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// int myFunction(int num, int num1, int num2, int num3, int num4, int num5,
//                int num6, int num7, int num8, int num9, int numA, int numB,
//                int numC, int numD

// ) {
//   printf("Inside myFunction %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
//   num,
//          num1, num2, num3, num4, num5, num6, num7, num8, num9, numA, numB,
//          numC, numD);
//   return 59;
// }

int fn(char val) {
  printf("%hhi\n", val);
  return -69;
}

int main() {
  //   void *ptr = fn;
  //   void *rvalue = malloc(4);
  //   void *avalue[1];
  //   char a1 = 69;
  //   avalue[0] = &a1;
  //   *((uint32_t *)rvalue) =
  //       ((uint32_t(*)(uint32_t))ptr)(*((uint32_t *)(avalue[0x0])));

  //   printf("rvalue = %d", *(uint32_t *)rvalue);

  //   free(rvalue);

  ffi_cif cif;
  ffi_type *args[1];
  void *values[1];
  char a1;
  ffi_arg rc;

  args[0] = &ffi_type_sint8;
  values[0] = &a1;

  if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, args) != FFI_OK)
    exit(EXIT_FAILURE);

  a1 = 67;
  ffi_call(&cif, fn, &rc, values);
  printf("res = %d\n", rc);

  //   void (*fn)() = myFunction;
  //   fn(69, 17, 88, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  //   emscripten_run_script("Module.ccall('printshit', )");

  // ffi_cif cif;
  // ffi_type *args[1];
  // void *values[1];
  // char *s;
  // ffi_arg rc;

  // /* Initialize the argument info vectors */
  // args[0] = &ffi_type_pointer;
  // values[0] = &s;

  // /* Initialize the cif */
  // if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, args) ==
  //     FFI_OK) {
  //   s = "Hello World!";
  //   ffi_call(&cif, myFunction, &rc, values);
  //   /* rc now holds the result of the call to puts */

  //   /* values holds a pointer to the function's arg, so to
  //      call puts() again all we need to do is change the
  //      value of s */
  //   s = "This is cool!";
  //   ffi_call(&cif, myFunction, &rc, values);
  // }

  // return 0;
}