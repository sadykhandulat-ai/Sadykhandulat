import math
import random
import tkinter as tk


WIDTH, HEIGHT = 900, 600
BACKGROUND = "#03070d"
RAIN_COLORS = ("#29bda8", "#42d9c1", "#74fbd3", "#31a9c7")
AMBER = "#ffd166"


class DigitalRainEye:
    def __init__(self, root):
        self.root = root
        root.title("EYE // DIGITAL RAIN")
        root.resizable(False, False)
        root.configure(bg=BACKGROUND)

        self.canvas = tk.Canvas(
            root,
            width=WIDTH,
            height=HEIGHT,
            bg=BACKGROUND,
            highlightthickness=0,
            cursor="crosshair",
        )
        self.canvas.pack()

        self.columns = [
            {
                "x": x,
                "y": random.randint(-HEIGHT, 0),
                "speed": random.uniform(1.8, 5.5),
                "length": random.randint(7, 19),
                "color": random.choice(RAIN_COLORS),
                "bright": random.random() > 0.82,
            }
            for x in range(8, WIDTH, 16)
        ]
        self.blink = 0.0
        self.blink_direction = 0
        self.next_blink = random.randint(100, 180)
        self.mouse_x = WIDTH // 2
        self.mouse_y = HEIGHT // 2
        self.target_mouse_x = WIDTH // 2
        self.target_mouse_y = HEIGHT // 2
        self.frame = 0
        self.glitch = 0
        self.pulse = 0.0
        self.signal = [random.random() for _ in range(42)]
        self.particles = [
            {
                "x": random.randint(20, WIDTH - 20),
                "y": random.randint(20, HEIGHT - 20),
                "phase": random.uniform(0, math.tau),
                "size": random.choice((1, 1, 2)),
            }
            for _ in range(55)
        ]

        self.canvas.bind("<Motion>", self.track_mouse)
        self.animate()

    def track_mouse(self, event):
        self.target_mouse_x = event.x
        self.target_mouse_y = event.y

    def draw_background(self):
        horizon = HEIGHT // 2
        for y in range(0, HEIGHT, 24):
            shade = "#071116" if y % 48 == 0 else "#050c11"
            self.canvas.create_line(0, y, WIDTH, y, fill=shade, width=1)
        for x in range(0, WIDTH, 24):
            shade = "#071116" if x % 48 == 0 else "#050c11"
            self.canvas.create_line(x, 0, x, HEIGHT, fill=shade, width=1)

        # Vignette-like edge shadows
        for inset in (0, 12, 24):
            alpha = "#081118" if inset == 0 else "#050b10"
            self.canvas.create_rectangle(
                inset, inset, WIDTH - inset, HEIGHT - inset,
                outline=alpha, width=2,
            )

        # Moving radar sweep behind the subject
        angle = math.radians((self.frame * 1.1) % 360)
        cx, cy = WIDTH // 2, horizon
        self.canvas.create_oval(
            cx - 330, cy - 220, cx + 330, cy + 220,
            outline="#0a2427", width=1,
        )
        ex = cx + math.cos(angle) * 330
        ey = cy + math.sin(angle) * 220
        self.canvas.create_line(cx, cy, ex, ey, fill="#123a3a", width=1)

        for x, y, sx, sy in (
            (30, 30, 1, 1),
            (WIDTH - 30, 30, -1, 1),
            (30, HEIGHT - 30, 1, -1),
            (WIDTH - 30, HEIGHT - 30, -1, -1),
        ):
            self.canvas.create_line(
                x, y, x + 70 * sx, y, fill="#1d514b", width=2
            )
            self.canvas.create_line(
                x, y, x, y + 70 * sy, fill="#1d514b", width=2
            )

        self.canvas.create_text(
            38, 22,
            text="VISUAL SENSOR // 09",
            fill="#52766f",
            font=("Consolas", 9),
            anchor="w",
        )
        self.canvas.create_text(
            WIDTH // 2, 22,
            text="NEURAL OPTICS  /  LIVE",
            fill="#69d7c2",
            font=("Consolas", 10, "bold"),
        )
        self.canvas.create_text(
            WIDTH - 38, 22,
            text=f"FRAME {self.frame:06d}",
            fill="#52766f",
            font=("Consolas", 9),
            anchor="e",
        )
        self.canvas.create_text(
            WIDTH - 38, HEIGHT - 22,
            text="TRACKING ACTIVE",
            fill="#52766f",
            font=("Consolas", 9),
            anchor="e",
        )

        for particle in self.particles:
            flicker = 0.35 + 0.65 * (
                math.sin(particle["phase"] + self.frame * 0.035) + 1
            ) / 2
            if flicker > 0.72:
                self.canvas.create_oval(
                    particle["x"] - particle["size"],
                    particle["y"] - particle["size"],
                    particle["x"] + particle["size"],
                    particle["y"] + particle["size"],
                    fill="#5abfb1",
                    outline="",
                )

        # Signal strip
        strip_x = 38
        strip_y = 64
        self.canvas.create_line(
            strip_x, strip_y + 14, strip_x + 250, strip_y + 14,
            fill="#102b2d", width=1,
        )
        for i, value in enumerate(self.signal):
            x = strip_x + i * 6
            h = 3 + int(value * 15)
            color = AMBER if i % 11 == (self.frame // 8) % 11 else "#39736b"
            self.canvas.create_rectangle(
                x, strip_y + 14 - h, x + 3, strip_y + 14,
                fill=color, outline="",
            )

    def draw_rain(self):
        for drop in self.columns:
            x, y = drop["x"], drop["y"]
            eye_distance = abs(x - WIDTH // 2)
            muted = eye_distance < 280
            for i in range(drop["length"]):
                yy = y - i * 15
                if 0 <= yy < HEIGHT:
                    if i == 0:
                        color = "#bfffee" if drop["bright"] else drop["color"]
                        font_size = 12
                        weight = "bold"
                    else:
                        color = "#123a38" if i > 7 else ("#1d5f58" if muted else "#238176")
                        font_size = 11
                        weight = "normal"
                    char = random.choice("01アイウエオカキクケコ")
                    self.canvas.create_text(
                        x, yy,
                        text=char,
                        fill=color,
                        font=("Consolas", font_size, weight),
                    )

            drop["y"] += drop["speed"]
            if drop["y"] - drop["length"] * 15 > HEIGHT:
                drop.update(
                    y=random.randint(-260, -20),
                    speed=random.uniform(1.8, 5.5),
                    length=random.randint(7, 19),
                    color=random.choice(RAIN_COLORS),
                    bright=random.random() > 0.82,
                )

    def draw_eye(self):
        cx, cy = WIDTH // 2, HEIGHT // 2 + 8
        openness = max(0.04, 1.0 - self.blink)
        half_height = 118 * openness

        dx = max(-24, min(24, (self.mouse_x - cx) / 15))
        dy = max(-14, min(14, (self.mouse_y - cy) / 20))
        pulse = 0.5 + 0.5 * math.sin(self.frame * 0.09)

        # Layered technical glow
        for expand, color, width in (
            (12, "#071f22", 8),
            (7, "#103739", 5),
            (2, "#2aa394", 2),
        ):
            self.canvas.create_oval(
                cx - 300 - expand, cy - 170 - expand,
                cx + 300 + expand, cy + 170 + expand,
                outline=color, width=width,
            )

        self.canvas.create_oval(
            cx - 300, cy - 170, cx + 300, cy + 170,
            fill="#090d16", outline="#1b7c74", width=2,
        )
        self.canvas.create_oval(
            cx - 282, cy - 152, cx + 282, cy + 152,
            outline="#28435a", width=1,
        )
        for angle in range(0, 360, 30):
            rad = math.radians(angle)
            x1 = cx + math.cos(rad) * 292
            y1 = cy + math.sin(rad) * 162
            x2 = cx + math.cos(rad) * 282
            y2 = cy + math.sin(rad) * 152
            self.canvas.create_line(x1, y1, x2, y2, fill="#62e0c7", width=2)

        sclera = [
            cx - 245, cy,
            cx - 180, cy - half_height,
            cx, cy - half_height,
            cx + 180, cy - half_height,
            cx + 245, cy,
            cx + 180, cy + half_height,
            cx, cy + half_height,
            cx - 180, cy + half_height,
        ]
        self.canvas.create_polygon(
            *sclera,
            smooth=True,
            fill="#d5ddd8",
            outline="#8affdf",
            width=3,
        )

        iris_radius = 70 * openness + 12
        ix, iy = cx + dx, cy + dy
        self.canvas.create_oval(
            ix - iris_radius, iy - iris_radius,
            ix + iris_radius, iy + iris_radius,
            fill="#175d63", outline="#73fbd3", width=6,
        )

        inner_radius = iris_radius * 0.72
        self.canvas.create_oval(
            ix - inner_radius, iy - inner_radius,
            ix + inner_radius, iy + inner_radius,
            fill="#102e43", outline="#38a6b1", width=3,
        )

        # Dense iris fibers
        for angle in range(0, 360, 12):
            rad = math.radians(angle)
            r1 = iris_radius * 0.42
            r2 = iris_radius * 0.92
            if 160 < angle < 220:
                continue
            self.canvas.create_line(
                ix + math.cos(rad) * r1,
                iy + math.sin(rad) * r1,
                ix + math.cos(rad) * r2,
                iy + math.sin(rad) * r2,
                fill="#3c8d82",
                width=1,
            )

        pupil_radius = 25 * openness + 7
        self.canvas.create_oval(
            ix - pupil_radius, iy - pupil_radius,
            ix + pupil_radius, iy + pupil_radius,
            fill="#020609", outline="#06131a",
        )
        self.canvas.create_oval(
            ix - pupil_radius - 5, iy - pupil_radius - 5,
            ix + pupil_radius + 5, iy + pupil_radius + 5,
            outline="#75dcca", width=1,
        )
        self.canvas.create_oval(
            ix - 27, iy - 31,
            ix - 10, iy - 14,
            fill="#eafff9", outline="",
        )

        for ring in range(8, int(iris_radius), 10):
            self.canvas.create_oval(
                ix - ring, iy - ring, ix + ring, iy + ring,
                outline="#286f70", width=1,
            )

        upper = []
        lower = []
        for step in range(61):
            t = step / 60
            x = cx - 245 + 490 * t
            upper_y = cy - half_height * math.sin(math.pi * t) - 4
            lower_y = cy + half_height * math.sin(math.pi * t) + 4
            upper.extend((x, upper_y))
            lower.extend((x, lower_y))

        self.canvas.create_line(
            *upper, fill="#0b1b22", width=10, smooth=True
        )
        self.canvas.create_line(
            *lower, fill="#0b1b22", width=10, smooth=True
        )

        for t in (0.08, 0.18, 0.30, 0.42, 0.58, 0.70, 0.82, 0.92):
            x = cx - 245 + 490 * t
            y = cy - half_height * math.sin(math.pi * t) - 8
            direction = (t - 0.5) * 38
            self.canvas.create_line(
                x, y, x + direction, y - 22,
                fill="#2a5960", width=3, smooth=True,
            )

        for t in (0.12, 0.26, 0.38, 0.62, 0.74, 0.88):
            x = cx - 245 + 490 * t
            y = cy + half_height * math.sin(math.pi * t) + 8
            direction = (t - 0.5) * 24
            self.canvas.create_line(
                x, y, x + direction, y + 15,
                fill="#1d4549", width=2, smooth=True,
            )

        # Precision reticle
        reticle = 104
        self.canvas.create_line(
            ix - reticle, iy, ix - pupil_radius - 8, iy,
            fill="#73fbd3", width=1,
        )
        self.canvas.create_line(
            ix + pupil_radius + 8, iy, ix + reticle, iy,
            fill="#73fbd3", width=1,
        )
        self.canvas.create_line(
            ix, iy - reticle, ix, iy - pupil_radius - 8,
            fill="#73fbd3", width=1,
        )
        self.canvas.create_line(
            ix, iy + pupil_radius + 8, ix, iy + reticle,
            fill="#73fbd3", width=1,
        )

        if self.blink > 0:
            cover = 155 * self.blink
            self.canvas.create_rectangle(
                cx - 246, cy - 155,
                cx + 246, cy - 155 + cover,
                fill="#03070d", outline="",
            )
            self.canvas.create_rectangle(
                cx - 246, cy + 155 - cover,
                cx + 246, cy + 155,
                fill="#03070d", outline="",
            )

        # Rare digital glitch accents
        if self.glitch > 0:
            offset = 8 + random.randint(-5, 12)
            for band in range(3):
                y = cy - 120 + band * 80 + random.randint(-18, 18)
                self.canvas.create_rectangle(
                    cx - 220, y,
                    cx + 220 + offset, y + random.randint(1, 4),
                    fill=random.choice(("#62e0c7", "#1b4e57", "#ffd166")),
                    outline="",
                )

        # Animated scan line
        scan_y = (self.frame * 3) % HEIGHT
        self.canvas.create_line(
            0, scan_y, WIDTH, scan_y,
            fill="#0e2e31", width=1,
        )

    def animate(self):
        self.canvas.delete("all")
        self.frame += 1
        self.mouse_x += (self.target_mouse_x - self.mouse_x) * 0.12
        self.mouse_y += (self.target_mouse_y - self.mouse_y) * 0.12
        self.draw_background()
        self.draw_rain()
        self.draw_eye()

        if self.blink_direction == 0:
            self.next_blink -= 1
            if self.next_blink <= 0:
                self.blink_direction = 1
        else:
            self.blink += 0.22 * self.blink_direction
            if self.blink >= 1:
                self.blink = 1
                self.blink_direction = -1
            elif self.blink <= 0:
                self.blink = 0
                self.blink_direction = 0
                self.next_blink = random.randint(100, 180)

        if random.random() < 0.012:
            self.glitch = random.randint(2, 6)
        elif self.glitch > 0:
            self.glitch -= 1

        self.root.after(40, self.animate)


if __name__ == "__main__":
    window = tk.Tk()
    DigitalRainEye(window)
    window.mainloop()
