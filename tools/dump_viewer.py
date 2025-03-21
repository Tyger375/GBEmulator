import cv2
import numpy as np
import sys

def read_file(filename: str) -> bytes:
    with open(filename, "rb") as f:
        return f.read()

"""
for (int i = 0; i < 8; ++i) {
        Byte mask = 1 << (7 - i);
        Byte first = (tile_data_low & mask) > 0;
        Byte second = (tile_data_high & mask) > 0;

        Byte BGP = mem[BGP_REG];
        pixels[i] = {first + second, BGP, 0};
    }
"""
def decode_tile(tile_data: bytes):
    pixels = []
    for i in range(8):
        first_byte = tile_data[i * 2]
        second_byte = tile_data[(i * 2) + 1]
        for j in range(8):
            mask = 1 << (7 - j)
            first = (first_byte & mask) > 0
            second = (second_byte & mask) > 0
            pixels.append(first+second)

    # print([hex(tile) for tile in tile_data], pixels)

    return pixels

def pixel_color(value: int):
    if value == 0:
        return 255, 255, 255
    elif value == 1:
        return 169, 169, 169
    elif value == 2:
        return 84, 84, 84
    elif value == 3:
        return 0, 0, 0
    return 0,0,0

if __name__ == "__main__":
    data = read_file(sys.argv[1])

    TILE_SIZE = 8
    TILES = 16

    board = np.zeros([TILE_SIZE * TILES, TILE_SIZE * TILES, 3])

    tiles = data[0x8000:0x9010]
    TILE_BYTES = 16
    tiles_num = len(tiles) // TILE_BYTES

    for i in range(min(TILES**2, tiles_num)):
        pixels = decode_tile(tiles[(i * TILE_BYTES):((i + 1) * TILE_BYTES)])

        row = i // TILES
        col = i % TILES

        for j in range(TILE_SIZE * TILE_SIZE):
            tile_x = j % TILE_SIZE
            tile_y = j // TILE_SIZE

            x = col * TILE_SIZE + tile_x
            y = row * TILE_SIZE + tile_y

            board[y][x] = pixel_color(pixels[j])

    scale = 5

    def mouse_click(event, x, y, flags, param):
        x = x // scale
        y = y // scale
        if event == cv2.EVENT_LBUTTONDOWN:
            tile_row = y // TILE_SIZE
            tile_col = x // TILE_SIZE

            tile_number = tile_row * TILES + tile_col
            print(tile_number, hex(0x8000 + tile_number * 16))

    cv2.namedWindow("Dump Viewer")
    cv2.setMouseCallback("Dump Viewer", mouse_click)

    while True:
        cv2.imshow("Dump Viewer", np.uint8(board.repeat(scale, 0)).repeat(scale, 1))
        key = cv2.waitKey(int(1000 / 12))
        if key == 27:
            break
