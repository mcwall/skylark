import sys

# Parse a txt file with opcodes and comments, and output the opcodes as valid binary file
def to_bin(fn_in, fn_out):
    file_in = open(fn_in, 'r')
    out_bytes = []
    for line in file_in:
        s = line.replace('//', '#').split('#')[0].strip()
        if len(s) == 0:
            continue
        
        if len(s) != 4:
            raise 'Invalid opcode'
        
        out_bytes.append(int(s[0:2], 16))
        out_bytes.append(int(s[2:4], 16))

    with open(fn_out, 'wb') as file_out:
        file_out.write(bytearray(out_bytes))

to_bin(sys.argv[1], sys.argv[2])