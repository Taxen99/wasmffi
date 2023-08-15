from math import log, floor
import re
import subprocess
import sys

def is_number(s):
    """Check if the given string can be converted to a int."""
    try:
        int(s)
        return True
    except ValueError:
        return False

def clang_format_code(code: str) -> str:
    """Format a C/C++ code string using clang-format."""
    process = subprocess.Popen(
        ['clang-format'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True  # Use text mode
    )
    
    stdout, stderr = process.communicate(input=code)
    
    if process.returncode != 0:
        raise RuntimeError(f"clang-format failed with error: {stderr}")

    return stdout

def FFI_CALL_IMPL():
    max_number_of_arguments = int(sys.argv[1]) if len(sys.argv) > 1 and is_number(sys.argv[1]) else 2
    type_map = [
        "void",
        "uint32_t",
        "uint64_t",
        "float",
        "double",
    ]

    def to_base_5(num):
        """Convert a decimal number to its base 5 representation as a string."""
        if num == 0:
            return "0"
        base_5_str = ""
        while num:
            remainder = num % 5
            base_5_str = str(remainder) + base_5_str
            num //= 5
        return base_5_str
    
    def valid_encoding(num):
        return not "0" in to_base_5(num)[:-1]

    # "5^0*[0-4]+5^1*[0-4]+5^2*[0-4]..." "(encoding // (5 ** index)) % 5"
    def encoding_to_type(encoding, index):
        return type_map[(encoding // (5 ** index)) % 5]
    
    def encoding_to_arg_num(encoding):
        return floor(log(encoding, 5)) if encoding > 0 else 0

    return f"""

    switch(cif->encoding) {{
        {"".join(f'''
        case###{hex(encoding)}:
            {f"*(({encoding_to_type(encoding, 0)} *)rvalue) =" if encoding_to_type(encoding, 0) != "void" else ""}
            (({encoding_to_type(encoding, 0)}(*)({", ".join(encoding_to_type(encoding, arg_index + 1) for arg_index in range(0, encoding_to_arg_num(encoding)))}))fn)
            ({", ".join(f"*(({encoding_to_type(encoding, arg_index + 1)} *)(avalue[{hex(arg_index)}]))" for arg_index in range(0, encoding_to_arg_num(encoding)))});
            return;
        
        ''' if valid_encoding(encoding) else "" for encoding in range(0, len(type_map) ** (max_number_of_arguments + 1)))}
default:
    fprintf(stderr, "Invalid###cif:###%u,###Aborting###the###program.\n", cif->encoding);
    exit(EXIT_FAILURE);
    }}
    """

def custom_replace(match):
    function_name = match.group(1)
    # try:
        # Using eval to call the function
    result = (eval(function_name + "()").replace("\n","").replace(" ", "").replace("###", " "))
    # except Exception as e:
        # print(f"Error calling function {function_name}: {str(e)}")
        # result = ""
    return result

def process_file(input_filepath, output_filepath):
    with open(input_filepath, 'r') as file:
        content = file.read()

    # Using regex to replace every occurrence of @@[text]@@
    content = re.sub(r'@@(\w+)@@', custom_replace, content)

    with open(output_filepath, 'w') as file:
        file.write(content)

if __name__ == "__main__":
    input_path = 'src/ffi_call.c.template'
    output_path = 'src/ffi_call.c'
    process_file(input_path, output_path)
    print(f"Processed {input_path} and saved to {output_path}")
