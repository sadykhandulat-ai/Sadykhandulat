import math
import random
import time
import tkinter as tk

WIDTH, HEIGHT = 1000, 720
random.seed(12)

root = tk.Tk()
root.title("Для Томирис")
root.configure(bg="#07070c")
root.resizable(False, False)

canvas = tk.Canvas(
    root, width=WIDTH, height=HEIGHT,
    bg="#07070c", highlightthickness=0
)
canvas.pack()

# Тёмная комната и мягкое сияние
canvas.create_oval(150, 35, 850, 580, fill="#0d0b13", outline="")
canvas.create_oval(300, 65, 700, 520, fill="#110d16", outline="")

# Дождь на заднем плане
rain = []
rain_colors = ["#373b52", "#46445c", "#343b50", "#51465d"]

for _ in range(110):
    x = random.randint(0, WIDTH)
    y = random.randint(0, HEIGHT)
    length = random.randint(14, 32)
    speed = random.uniform(3, 8)
    item = canvas.create_line(
        x, y, x - 5, y + length,
        fill=random.choice(rain_colors), width=1
    )
    rain.append([item, x, y, length, speed])

# Одиннадцать пионов, собранных в пышный букет
flower_centers = [
    (250, 220), (375, 185), (500, 205), (625, 185), (750, 220),
    (315, 295), (438, 285), (562, 285), (685, 295),
    (440, 365), (560, 365),
]

# Укороченные стебли и листья
for index, (x, y) in enumerate(flower_centers):
    stem_end_x = 500 + (x - 500) * 0.12
    canvas.create_line(
        x, y + 34, stem_end_x, 470,
        fill="#526b53", width=5, smooth=True
    )

    leaf_y = 365 + (index % 3) * 10
    canvas.create_oval(
        x - 56, leaf_y, x + 3, leaf_y + 22,
        fill="#435b48", outline=""
    )
    canvas.create_oval(
        x - 2, leaf_y + 23, x + 55, leaf_y + 45,
        fill="#526b53", outline=""
    )

# Глиняная ваза — немного выше прежней
canvas.create_polygon(
    422, 466, 578, 466, 568, 492,
    552, 505, 570, 580, 548, 612,
    500, 625, 452, 612, 430, 580,
    448, 505, 432, 492,
    fill="#9a543b", outline="#d28a62", width=3
)
canvas.create_oval(
    420, 455, 580, 485,
    fill="#bd7652", outline="#e0a078", width=3
)
canvas.create_oval(
    438, 462, 562, 480,
    fill="#59372f", outline="#d59670", width=2
)
canvas.create_line(444, 500, 458, 584, fill="#d28a62", width=4)
canvas.create_line(555, 510, 543, 590, fill="#754238", width=5)
canvas.create_oval(
    453, 599, 547, 622,
    fill="#874735", outline="#c47c56", width=2
)

# Цифры составляют лепестки и сердцевины пионов
targets = []
petal_colors = ["#f3a5bb", "#e987aa", "#f7bfd0", "#d9799c"]
center_colors = ["#f6d58a", "#ffe9ad", "#d9a95c"]

for cx, cy in flower_centers:
    for petal in range(12):
        angle = 2 * math.pi * petal / 12
        petal_cx = cx + math.cos(angle) * 23
        petal_cy = cy + math.sin(angle) * 23

        for gx in range(-27, 28, 12):
            for gy in range(-38, 39, 12):
                if (gx / 27) ** 2 + (gy / 38) ** 2 <= 1:
                    px = petal_cx + gx * math.cos(angle) - gy * math.sin(angle)
                    py = petal_cy + gx * math.sin(angle) + gy * math.cos(angle)
                    targets.append((px, py, random.choice(petal_colors)))

    for step in range(14):
        angle = 2 * math.pi * step / 14
        for radius in (7, 14, 20):
            targets.append((
                cx + math.cos(angle) * radius,
                cy + math.sin(angle) * radius,
                random.choice(center_colors)
            ))

# Пиксельный шрифт для надписи «Для Томирис»
font = {
    "д": ["00110", "01010", "01010", "01010", "10001", "11111", "10001"],
    "л": ["00110", "01010", "01010", "01010", "01010", "10010", "10001"],
    "я": ["01111", "10001", "10001", "01111", "00101", "01001", "10001"],
    "т": ["11111", "00100", "00100", "00100", "00100", "00100", "00100"],
    "о": ["01110", "10001", "10001", "10001", "10001", "10001", "01110"],
    "м": ["10001", "11011", "10101", "10101", "10001", "10001", "10001"],
    "и": ["10001", "10001", "10011", "10101", "11001", "10001", "10001"],
    "р": ["11110", "10001", "10001", "11110", "10000", "10000", "10000"],
    "с": ["01111", "10000", "10000", "10000", "10000", "10000", "01111"],
}

message = "для томирис"
scale = 7
advance = 6 * scale
space_width = 3 * scale
text_width = sum(space_width if char == " " else advance for char in message)
text_x = (WIDTH - text_width) / 2
text_y = 650

for char in message:
    if char == " ":
        text_x += space_width
        continue

    for row, line in enumerate(font[char]):
        for column, pixel in enumerate(line):
            if pixel == "1":
                targets.append((
                    text_x + column * scale + scale / 2,
                    text_y + row * scale + scale / 2,
                    random.choice(["#f7d8e5", "#f2bfd2", "#ffe8bd"])
                ))
    text_x += advance

# Цифры падают сверху и складываются в букет и надпись
particles = []
for target_x, target_y, color in targets:
    start_x = random.randint(20, WIDTH - 20)
    start_y = random.randint(-HEIGHT, -20)
    item = canvas.create_text(
        start_x, start_y,
        text=random.choice("0123456789"),
        fill=color,
        font=("Consolas", 10, "bold")
    )
    particles.append({
        "item": item,
        "x": start_x,
        "y": start_y,
        "tx": target_x,
        "ty": target_y,
        "start": time.monotonic() + random.uniform(0, 1.8),
        "duration": random.uniform(2.8, 4.5),
    })

canvas.create_line(340, 710, 660, 710, fill="#6e5268", width=1)
canvas.create_text(
    WIDTH // 2, 710, text="✦",
    fill="#d4a3ba", font=("Georgia", 12)
)


def animate():
    now = time.monotonic()

    # Движение капель дождя
    for drop in rain:
        item, x, y, length, speed = drop
        y += speed

        if y > HEIGHT:
            y = random.randint(-60, -10)
            x = random.randint(0, WIDTH)

        drop[1] = x
        drop[2] = y
        canvas.coords(item, x, y, x - 5, y + length)

    # Цифры постепенно занимают места в рисунке
    for particle in particles:
        if now < particle["start"]:
            continue

        progress = min(
            1.0,
            (now - particle["start"]) / particle["duration"]
        )
        eased = 1 - (1 - progress) ** 3

        x = particle["x"] + (particle["tx"] - particle["x"]) * eased
        y = particle["y"] + (particle["ty"] - particle["y"]) * eased
        canvas.coords(particle["item"], x, y)

    root.after(30, animate)


animate()
root.mainloop()