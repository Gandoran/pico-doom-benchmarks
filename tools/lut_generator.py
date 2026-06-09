import math
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent

OUTPUT_FILE = SCRIPT_DIR.parent / "src" / "cpu" / "trigonometric" / "cpu_lut.c"

SinArray = []
TanArray = []
ATanArray = []

INT32_MAX = 2147483647
INT32_MIN = -2147483648

def CheckOverflow(value):
    if value > INT32_MAX:
        return INT32_MAX
    elif value < INT32_MIN:
        return INT32_MIN
    return value

for i in range (0,8192):
    #Conversion Bam to Radiant
    rad = (i / 8192.0) * 2.0 * math.pi

    fixed_sin = CheckOverflow(int(math.sin(rad) * 65536))
    fixed_tan = CheckOverflow(int(math.tan(rad) * 65536))
    fixed_atan = CheckOverflow(int(math.atan(rad) * 65536))

    SinArray.append(math.sin(rad))
    TanArray.append(math.tan(rad))
    ATanArray.append(math.atan(rad))


with open(OUTPUT_FILE, "w") as f:
    f.write('#include "cpu_lut.h"\n\n')

    f.write('const n_fixed sin_table[8192] ={\n')
    f.write(",\n".join(map(str, SinArray)))
    f.write('\n};\n\n')

    f.write('const n_fixed tan_table[8192] ={\n')
    f.write(",\n".join(map(str, TanArray)))
    f.write('\n};\n\n')

    f.write('const n_fixed atan_table[8192] ={\n')
    f.write(",\n".join(map(str, ATanArray)))
    f.write('\n};\n\n')


