import math
from pathlib import Path
from typing import List, Tuple

SCRIPT_DIR = Path(__file__).parent

OUTPUT_FILE = SCRIPT_DIR.parent / "src" / "cpu" / "trigonometric" / "cpu_lut.c"

TABLE_SIZE      = 8192         
HALF_TABLE_SIZE = TABLE_SIZE // 2  
FIXED_POINT_SCALE = 65536      
MASK_NAME       = "MASK"
HALF_MASK_NAME  = "(ANGLES/2 - 1)"

INT32_MAX = 2147483647
INT32_MIN = -2147483648

def check_overflow(value):
    if value > INT32_MAX: return INT32_MAX
    elif value < INT32_MIN: return INT32_MIN
    return int(round(value))

def calculate_sin_table(size: int, scale: int) -> List[int]:
    table = []
    for i in range(size):
        rad = (i / size) * 2.0 * math.pi
        table.append(check_overflow(math.sin(rad) * scale))
    return table

def calculate_tan_table(half_size: int, scale: int) -> List[int]:
    table = []
    for i in range(half_size):
        rad = (i / half_size) * math.pi
        try:
            val = math.tan(rad)
            if math.isinf(val) or math.isnan(val):
                raise OverflowError
            table.append(check_overflow(val * scale))
        except (ValueError, OverflowError):
            table.append(INT32_MAX if math.cos(rad) >= 0 else INT32_MIN)
    return table

def calculate_atan_table(half_size: int, full_size: int) -> List[int]:
    table = []
    last = half_size - 1
    for i in range(half_size):
        ratio = i / last
        atan_rad = math.atan(ratio)
        atan_bam = (atan_rad / (2.0 * math.pi)) * full_size
        table.append(int(round(atan_bam)))
    return table

def write_array(name: str, type_name: str, data: List[int], size: int) -> str:
    lines = []
    for i in range(0, size, 8):
        chunk = data[i:i + 8]
        lines.append("    " + ", ".join(map(str, chunk)))
    elements = ",\n".join(lines)
    return f"const {type_name} {name}[{size}] = {{\n{elements}\n}};\n\n"

def write_lut_sin() -> str:
    return (
        "n_fixed LutSin(angle_bam a) {\n"
        f"    return sin_table[a & {MASK_NAME}];\n"
        "}\n\n"
    )

def write_lut_tan() -> str:
    return (
        "n_fixed LutTan(angle_bam a) {\n"
        f"    return tan_table[a & {HALF_MASK_NAME}];\n"
        "}\n\n"
    )

def write_lut_atan(half_size: int, scale: int, full_size: int) -> str:
    last = half_size - 1
    quarter_size = full_size // 4
    return (
        "angle_bam LutAtan(n_fixed ratio) {\n"
        "    int sign = 0;\n"
        "    if (ratio < 0) {\n"
        "        sign = 1;\n"
        "        ratio = -ratio;\n"
        "    }\n"
        "    angle_bam result;\n"
        f"    if (ratio > {scale}) {{\n"
        f"        n_fixed inv_ratio = ((int64_t){scale} * {scale}) / ratio;\n"
        f"        unsigned idx = ((unsigned)inv_ratio * {last}u) / {scale}u;\n"
        f"        if (idx >= {half_size}u) idx = {last}u;\n"
        f"        result = {quarter_size}u - atan_table[idx];\n"
        "    } else {\n"
        f"        unsigned idx = ((unsigned)ratio * {last}u) / {scale}u;\n"
        f"        if (idx >= {half_size}u) idx = {last}u;\n"
        "        result = atan_table[idx];\n"
        "    }\n"
        "    if (sign) {\n"
        "        return (angle_bam)(-((int)result));\n"
        "    }\n"
        "    return result;\n"
        "}\n\n"
    )

def write_lut_file(file_path: Path, full_size: int, half_size: int, sin_data: List[int], tan_data: List[int], atan_data: List[int],) -> None:
    file_path.parent.mkdir(parents=True, exist_ok=True)
    file_path.unlink(missing_ok=True)
 
    with open(file_path, "w", encoding="utf-8") as f:
        f.write('#include "cpu_lut.h"\n\n')
 
        # Arrays
        f.write(write_array("sin_table",  "n_fixed",   sin_data,  full_size))
        f.write(write_array("tan_table",  "n_fixed",   tan_data,  half_size))
        f.write(write_array("atan_table", "angle_bam", atan_data, half_size))
 
        # Functions
        f.write(write_lut_sin())
        f.write(write_lut_tan())
        f.write(write_lut_atan(half_size, FIXED_POINT_SCALE,TABLE_SIZE))


def main() -> None:
    sin_table  = calculate_sin_table(TABLE_SIZE, FIXED_POINT_SCALE)
    tan_table  = calculate_tan_table(HALF_TABLE_SIZE, FIXED_POINT_SCALE)
    atan_table = calculate_atan_table(HALF_TABLE_SIZE, TABLE_SIZE)
 
    write_lut_file(OUTPUT_FILE, TABLE_SIZE, HALF_TABLE_SIZE, sin_table, tan_table, atan_table,)
 
 
if __name__ == "__main__":
    main()