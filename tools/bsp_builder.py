import os

nodes = []
flat_walls = []

def build_bsp_spatial(depth, x1, y1, x2, y2):
    """
    Genera ricorsivamente uno spazio diviso ad albero binario.
    Ogni taglio genera una parete che non ne interseca mai altre.
    """
    if depth == 0:
        return "NULL"
    
    current_id = len(nodes)
    nodes.append(None)  # Allocazione del posto nell'array
    
    # Alterna tagli verticali e orizzontali in base alla profondità dell'albero
    if depth % 2 == 0:
        # Taglio Verticale
        mid_x = (x1 + x2) / 2.0
        wall = {"sx": mid_x, "sy": y1, "ex": mid_x, "ey": y2}
        
        # Destra è Front, Sinistra è Back
        front_child = build_bsp_spatial(depth - 1, mid_x, y1, x2, y2)
        back_child = build_bsp_spatial(depth - 1, x1, y1, mid_x, y2)
    else:
        # Taglio Orizzontale
        mid_y = (y1 + y2) / 2.0
        wall = {"sx": x1, "sy": mid_y, "ex": x2, "ey": mid_y}
        
        # Sopra è Front, Sotto è Back
        front_child = build_bsp_spatial(depth - 1, x1, mid_y, x2, y2)
        back_child = build_bsp_spatial(depth - 1, x1, y1, x2, mid_y)
        
    # Registra la parete per il benchmark Brute Force
    flat_walls.append(wall)
    
    # Salva il record del nodo
    nodes[current_id] = {
        "id": current_id,
        "wall": wall,
        "front": front_child,
        "back": back_child
    }
    
    return f"&nodes[{current_id}]"

def main():
    # Imposta la profondità dell'albero: 
    # Profondità 6 = (2^6 - 1) = 63 pareti/nodi. Un'ottima mappa "Grande" per il Pico.
    TREE_DEPTH = 6
    
    # Avvia la generazione nello spazio di coordinate [0.0, 0.0] a [100.0, 100.0]
    root_pointer = build_bsp_spatial(TREE_DEPTH, 0.0, 0.0, 100.0, 100.0)
    total_walls = len(nodes)
    
    output_path = "src/cpu/sorting/map_creation.c"
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    
    with open(output_path, "w") as f:
        f.write('#include "map_creation.h"\n\n')
        
        # 1. Scrittura del sotto-array dei nodi BSP (Risoluzione statica dei puntatori)
        f.write(f"static BSPNode nodes[{total_walls}] = {{\n")
        for node in nodes:
            w = node["wall"]
            f.write(f"    [{node['id']}] = {{\n")
            f.write(f"        .divider = {{ {{ {w['sx']}f, {w['sy']}f }}, {{ {w['ex']}f, {w['ey']}f }} }},\n")
            f.write(f"        .front = {node['front']},\n")
            f.write(f"        .back = {node['back']}\n")
            f.write("    },\n")
        f.write("};\n\n")
        
        # 2. Scrittura dell'array piatto per il Brute Force
        f.write(f"static Wall flat_map[{total_walls}] = {{\n")
        for w in flat_walls:
            f.write(f"    {{ {{ {w['sx']}f, {w['sy']}f }}, {{ {w['ex']}f, {w['ey']}f }} }},\n")
        f.write("};\n\n")
        
        # 3. Implementazione delle funzioni pubbliche richieste da map_creation.h
        f.write("BSPNode* GetMapRoot() {\n")
        f.write(f"    return {root_pointer};\n")
        f.write("}\n\n")
        
        f.write("int GetMapSize() {\n")
        f.write(f"    return {total_walls};\n")
        f.write("}\n\n")
        
        f.write("void GetFlatMap(Wall* wall_array) {\n")
        f.write(f"    for(int i = 0; i < {total_walls}; i++) {{\n")
        f.write("        wall_array[i] = flat_map[i];\n")
        f.write("    }\n")
        f.write("}\n")

    print(f"Mappa generata con successo! Nodi creati: {total_walls} -> Scritta in {output_path}")

if __name__ == "__main__":
    main()