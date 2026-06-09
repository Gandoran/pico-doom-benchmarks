from pathlib import Path
import random

SCRIPT_DIR = Path(__file__).parent

OUTPUT_FILE = SCRIPT_DIR.parent / "src" / "memory" / "fileSystem" / "wad_benchmark_data.h"

def generate_lump_name(index):
    categories = ["WALL", "FLAT", "DOOR", "E1M", "BOSS", "SOUND"]
    category = categories[index % len(categories)]
    num = f"{index:04d}"
    return f"{category}{num}"[:8]

def main():
    TOTAL_LUMPS = 200
    
    lumps = []
    for i in range(TOTAL_LUMPS):
        name = generate_lump_name(i)
        size = random.randint(512, 65536)
        lumps.append((name, size))
        
    queries = []
    for _ in range(30):
        queries.append(random.choice(lumps)[0])
    queries.extend(["FAKEWALL", "NOTFOUND", "NULL_LMP", "UNKNOWN8"])

    #Writing the C file
    with open(OUTPUT_FILE, "w") as f:
        f.write("#ifndef WAD_BENCHMARK_DATA_H\n")
        f.write("#define WAD_BENCHMARK_DATA_H\n\n")
        f.write('#include "wad.h"\n\n')
        
        #Lump Array
        f.write(f"static const v_lump virtual_wad_directory[{TOTAL_LUMPS}] = {{\n")
        for name, size in lumps:
            f.write(f'    {{"{name}", {size}}},\n')
        f.write("};\n\n")
        
        #Query Array
        f.write(f"static const char* search_queries[{len(queries)}] = {{\n")
        for q in queries:
            f.write(f'    "{q}",\n')
        f.write("};\n\n")
        
        #Calculate Dimensions
        f.write(f"#define TOTAL_LUMPS {TOTAL_LUMPS}\n")
        f.write(f"#define TOTAL_QUERIES {len(queries)}\n\n")
        f.write("#endif\n")

if __name__ == "__main__":
    main()