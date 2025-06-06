import cv2
import numpy as np


# tamanho da imagem padrão
FALLBACK_WIDTH  = 800
FALLBACK_HEIGHT = 600

# caminho do seu PNG
IMAGE_PATH = 'mapa.png'
# arquivo de saída
OUT_PATH   = 'walls.txt'

walls = []
current_pt = None

def click_handler(event, x, y, flags, param):
    global current_pt, walls
    if event == cv2.EVENT_LBUTTONDOWN:
        if current_pt is None:
            current_pt = (x, y)
            print(f"Primeiro ponto: {current_pt}")
        else:
            p0 = current_pt
            p1 = (x, y)
            walls.append((p0, p1))
            print(f"Adicionado parede: {p0} → {p1}")
            current_pt = None

def main():
    global walls
    img = cv2.imread(IMAGE_PATH)
    if img is None:
        print(f"Falha ao carregar '{IMAGE_PATH}', criando imagem preta de {FALLBACK_WIDTH}x{FALLBACK_HEIGHT}.")
        # cria imagem preta
        img = np.zeros((FALLBACK_HEIGHT, FALLBACK_WIDTH, 3), dtype=np.uint8)
    cv2.namedWindow('map editor')
    cv2.setMouseCallback('map editor', click_handler)

    print("Clique dois pontos para cada parede; pressione 's' para salvar e sair.")
    while True:
        disp = img.copy()
        # desenha paredes já clicadas
        for (p0, p1) in walls:
            cv2.line(disp, p0, p1, (0,0,255), 2)
        cv2.imshow('map editor', disp)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break

    cv2.destroyAllWindows()
    # salva em formato C++
    with open(OUT_PATH, 'w') as f:
        f.write("vector<pair<Vector2,Vector2>> walls = {\n")
        for (p0, p1) in walls:
            f.write(f"    {{{{ {p0[0]}, {p0[1]} }}, {{ {p1[0]}, {p1[1]} }}}},\n")
        f.write("};\n")
    print(f"Salvo em {OUT_PATH}")

if __name__ == '__main__':
    main()
