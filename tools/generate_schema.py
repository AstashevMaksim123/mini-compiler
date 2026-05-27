from pathlib import Path
import shutil
import tempfile

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(r"\\wsl.localhost\Ubuntu-24.04\home\matveevda\projects\mini_compiler")
OUT_DIR = ROOT / "artifacts"
OUT_PATH = OUT_DIR / "schema_grammar.png"
DOWNLOADS_PATH = Path(r"C:\Users\matve\Downloads\schema_grammar.png")

W, H = 1780, 1480
BG = (248, 248, 248)
PANEL_FILL = (250, 250, 250)
PANEL_OUTLINE = (80, 80, 80)
TERMINAL_FILL = (255, 255, 255)
TERMINAL_OUTLINE = (214, 94, 94)
NONTERM_FILL = (221, 234, 255)
NONTERM_OUTLINE = (127, 161, 227)
TEXT = (30, 30, 30)
MUTED = (90, 90, 90)
ARROW = (40, 40, 40)


def load_font(name: str, size: int) -> ImageFont.FreeTypeFont:
    candidates = [
        Path(r"C:\Windows\Fonts") / name,
        Path(r"C:\Windows\Fonts\arial.ttf"),
    ]
    for path in candidates:
        if path.exists():
            return ImageFont.truetype(str(path), size)
    return ImageFont.load_default()


FONT_TITLE = load_font("arialbd.ttf", 30)
FONT_SUB = load_font("arial.ttf", 16)
FONT_LABEL = load_font("arialbd.ttf", 15)
FONT_TEXT = load_font("arial.ttf", 13)
FONT_SMALL = load_font("arial.ttf", 11)
FONT_TINY = load_font("arial.ttf", 10)


def text_size(draw: ImageDraw.ImageDraw, text: str, font) -> tuple[int, int]:
    bbox = draw.textbbox((0, 0), text, font=font)
    return bbox[2] - bbox[0], bbox[3] - bbox[1]


def draw_center(draw, x, y, text, font, fill=TEXT):
    w, h = text_size(draw, text, font)
    draw.text((x - w / 2, y - h / 2), text, font=font, fill=fill)


def draw_panel(draw, x1, y1, x2, y2, title):
    draw.rounded_rectangle((x1, y1, x2, y2), radius=8, fill=PANEL_FILL, outline=PANEL_OUTLINE, width=2)
    draw.text((x1 + 8, y1 + 6), f"{title} =", font=FONT_LABEL, fill=TEXT)


def draw_node(draw, x, y, text, kind="nonterm", pad_x=10, pad_y=5, min_w=36):
    font = FONT_TEXT
    tw, th = text_size(draw, text, font)
    w = max(min_w, tw + pad_x * 2)
    h = th + pad_y * 2
    x1, y1, x2, y2 = x, y, x + w, y + h
    fill = NONTERM_FILL if kind == "nonterm" else TERMINAL_FILL
    outline = NONTERM_OUTLINE if kind == "nonterm" else TERMINAL_OUTLINE
    draw.rounded_rectangle((x1, y1, x2, y2), radius=6, fill=fill, outline=outline, width=2)
    draw.text((x1 + (w - tw) / 2, y1 + (h - th) / 2 - 1), text, font=font, fill=TEXT if kind == "nonterm" else TERMINAL_OUTLINE)
    return x2, y2, w, h


def arrow(draw, x1, y1, x2, y2):
    draw.line((x1, y1, x2, y2), fill=ARROW, width=2)
    if x2 >= x1:
        draw.polygon([(x2, y2), (x2 - 8, y2 - 4), (x2 - 8, y2 + 4)], fill=ARROW)
    else:
        draw.polygon([(x2, y2), (x2 + 8, y2 - 4), (x2 + 8, y2 + 4)], fill=ARROW)


def draw_sequence(draw, x, y, items, line_w=18, note=None):
    cur = x
    cy = y + 18
    arrow(draw, cur, cy, cur + line_w, cy)
    cur += line_w
    for idx, (text, kind) in enumerate(items):
        _, _, w, h = draw_node(draw, cur, y, text, kind=kind)
        cur += w
        if idx != len(items) - 1:
            arrow(draw, cur, cy, cur + line_w, cy)
            cur += line_w
    arrow(draw, cur, cy, cur + line_w, cy)
    end_x = cur + line_w
    if note:
        draw.text((x + 8, y + 42), note, font=FONT_SMALL, fill=MUTED)
    return end_x


def draw_stack(draw, x, y, rows):
    for i, row in enumerate(rows):
        draw_sequence(draw, x, y + i * 34, row)


def draw_alt_rows(draw, x, y, prefix, rows, note=None):
    draw.text((x, y + 6), prefix, font=FONT_SMALL, fill=TEXT)
    for i, row in enumerate(rows):
        draw_sequence(draw, x + 18, y + i * 34, row)
    if note:
        draw.text((x + 18, y + len(rows) * 34 + 8), note, font=FONT_SMALL, fill=MUTED)


def draw_precedence_table(draw, x1, y1, x2, y2):
    draw_panel(draw, x1, y1, x2, y2, "Operator precedence")
    draw.text((x1 + 12, y1 + 28), "(lowest to highest)", font=FONT_SMALL, fill=MUTED)
    rows = [
        ("1", "||", "left-associative"),
        ("2", "&&", "left-associative"),
        ("3", "==, !=", "left-associative"),
        ("4", "<, <=, >, >=", "left-associative"),
        ("5", "+, -", "left-associative"),
        ("6", "*, /, %", "left-associative"),
        ("7", "unary !, -", "right-associative"),
    ]
    top = y1 + 50
    col1 = x1 + 16
    col2 = x1 + 60
    col3 = x1 + 172
    for i, (n, op, assoc) in enumerate(rows):
        yy = top + i * 42
        draw.rounded_rectangle((x1 + 10, yy - 4, x2 - 10, yy + 28), radius=4, outline=(160, 160, 160), width=1)
        draw.text((col1, yy + 2), n, font=FONT_TEXT, fill=TEXT)
        draw.text((col2, yy + 2), op, font=FONT_TEXT, fill=TERMINAL_OUTLINE)
        draw.text((col3, yy + 4), assoc, font=FONT_TINY, fill=TEXT)


def draw_token_group(draw, x1, y1, x2, y2, title, items):
    draw.rounded_rectangle((x1, y1, x2, y2), radius=8, fill=PANEL_FILL, outline=PANEL_OUTLINE, width=2)
    draw_center(draw, (x1 + x2) / 2, y1 + 12, title, FONT_LABEL)
    cur_x = x1 + 10
    cur_y = y1 + 28
    max_w = x2 - 10
    row_h = 0
    for text, kind in items:
        tw, th = text_size(draw, text, FONT_TEXT)
        w = max(34, tw + 20)
        h = th + 10
        if cur_x + w > max_w:
            cur_x = x1 + 10
            cur_y += row_h + 8
            row_h = 0
        draw_node(draw, cur_x, cur_y, text, kind=kind, min_w=w)
        cur_x += w + 8
        row_h = max(row_h, h)


def build():
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    img = Image.new("RGB", (W, H), BG)
    draw = ImageDraw.Draw(img)

    draw_center(draw, W / 2, 24, "mini_compiler parser grammar", FONT_TITLE)
    draw_center(draw, W / 2, 56, "Railroad-style diagram generated from src/parser.y", FONT_SUB, MUTED)

    left_x, mid_x, right_x, prec_x = 12, 586, 1150, 1488
    panel_w, mid_w, right_w, prec_w = 560, 550, 324, 280
    y = 78

    # Left column
    draw_panel(draw, left_x, y, left_x + panel_w, y + 54, "program")
    draw_sequence(draw, left_x + 16, y + 16, [("function_list", "nonterm")])
    y += 64

    draw_panel(draw, left_x, y, left_x + panel_w, y + 66, "function_list")
    draw_sequence(draw, left_x + 16, y + 18, [("function", "nonterm")], note="One or more functions")
    y += 76

    draw_panel(draw, left_x, y, left_x + panel_w, y + 74, "function")
    draw_sequence(draw, left_x + 10, y + 18, [
        ("fn", "term"), ("IDENT", "term"), ("(", "term"), ("params", "nonterm"),
        (")", "term"), ("->", "term"), ("type", "nonterm"), ("block", "nonterm")
    ], line_w=10, note="Function declaration")
    y += 84

    draw_panel(draw, left_x, y, left_x + panel_w, y + 66, "params")
    draw_alt_rows(draw, left_x + 14, y + 18, "A)", [[("empty", "nonterm")], [("param_list_nonempty", "nonterm")]])
    y += 76

    draw_panel(draw, left_x, y, left_x + panel_w, y + 66, "param_list_nonempty")
    draw_sequence(draw, left_x + 8, y + 18, [
        ("param", "nonterm"), (",", "term"), ("param", "nonterm")
    ], line_w=10, note="One or more params separated by commas")
    y += 76

    draw_panel(draw, left_x, y, left_x + panel_w, y + 60, "param")
    draw_sequence(draw, left_x + 12, y + 14, [("IDENT", "term"), (":", "term"), ("type", "nonterm")], line_w=14)
    y += 70

    draw_panel(draw, left_x, y, left_x + panel_w, y + 78, "type")
    draw_alt_rows(draw, left_x + 14, y + 18, "A)", [[("int", "term")], [("bool", "term")]])
    y += 88

    draw_panel(draw, left_x, y, left_x + panel_w, y + 94, "var_decl_stmt")
    draw_alt_rows(
        draw,
        left_x + 12,
        y + 18,
        "A)",
        [
            [("let", "term"), ("mut", "term"), ("IDENT", "term"), (":", "term"), ("type", "nonterm"), ("=", "term"), ("expr", "nonterm")],
            [("let", "term"), ("IDENT", "term"), (":", "term"), ("type", "nonterm"), ("=", "term"), ("expr", "nonterm")],
        ],
    )

    # Middle column
    y = 78
    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 54, "block")
    draw_sequence(draw, mid_x + 18, y + 16, [("{", "term"), ("stmt_list", "nonterm"), ("}", "term")], line_w=16)
    y += 64

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 66, "stmt_list")
    draw_alt_rows(draw, mid_x + 14, y + 18, "A)", [[("empty", "nonterm")], [("stmt_list stmt", "nonterm")]], note="Zero or more statements")
    y += 76

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 160, "stmt")
    draw_alt_rows(
        draw,
        mid_x + 10,
        y + 18,
        "A)",
        [
            [("simple_stmt", "nonterm")],
            [("block", "nonterm")],
            [("if_stmt", "nonterm")],
            [("for_stmt", "nonterm")],
            [("switch_stmt", "nonterm")],
        ],
    )
    y += 170

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 210, "simple_stmt")
    draw_alt_rows(
        draw,
        mid_x + 10,
        y + 16,
        "A)",
        [
            [("var_decl_stmt", "nonterm"), (";", "term")],
            [("assign_stmt", "nonterm"), (";", "term")],
            [("return_stmt", "nonterm"), (";", "term")],
            [("break_stmt", "nonterm"), (";", "term")],
            [("continue_stmt", "nonterm"), (";", "term")],
            [("expr_stmt", "nonterm"), (";", "term")],
        ],
    )
    y += 220

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 94, "if_stmt")
    draw_alt_rows(
        draw,
        mid_x + 10,
        y + 18,
        "A)",
        [
            [("if", "term"), ("expr", "nonterm"), ("block", "nonterm"), ("else", "term"), ("block", "nonterm")],
            [("if", "term"), ("expr", "nonterm"), ("block", "nonterm")],
        ],
    )
    y += 104

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 92, "for_stmt")
    draw_alt_rows(
        draw,
        mid_x + 8,
        y + 16,
        "A)",
        [
            [("for", "term"), ("var_decl_stmt", "nonterm"), (";", "term"), ("expr", "nonterm"), (";", "term"), ("assign_stmt", "nonterm"), ("block", "nonterm")],
            [("for", "term"), ("assign_stmt", "nonterm"), (";", "term"), ("expr", "nonterm"), (";", "term"), ("assign_stmt", "nonterm"), ("block", "nonterm")],
        ],
    )
    y += 102

    draw_panel(draw, mid_x, y, mid_x + mid_w, y + 60, "switch_stmt")
    draw_sequence(draw, mid_x + 10, y + 14, [("switch", "term"), ("expr", "nonterm"), ("{", "term"), ("case_list", "nonterm"), ("}", "term")], line_w=10)
    y += 70

    bottom_y = y
    draw_panel(draw, mid_x, bottom_y, mid_x + 158, bottom_y + 60, "assign_stmt")
    draw_sequence(draw, mid_x + 8, bottom_y + 14, [("IDENT", "term"), ("=", "term"), ("expr", "nonterm")], line_w=8)

    draw_panel(draw, mid_x + 170, bottom_y, mid_x + 328, bottom_y + 60, "return_stmt")
    draw_sequence(draw, mid_x + 178, bottom_y + 14, [("return", "term"), ("expr", "nonterm")], line_w=10)

    draw_panel(draw, mid_x + 340, bottom_y, mid_x + 424, bottom_y + 60, "break_stmt")
    draw_sequence(draw, mid_x + 348, bottom_y + 14, [("break", "term")], line_w=10)

    draw_panel(draw, mid_x + 436, bottom_y, mid_x + mid_w, bottom_y + 60, "continue_stmt")
    draw_sequence(draw, mid_x + 444, bottom_y + 14, [("continue", "term")], line_w=10)

    # Right column
    y = 78
    draw_panel(draw, right_x, y, right_x + right_w, y + 66, "arg_list")
    draw_alt_rows(draw, right_x + 10, y + 18, "A)", [[("empty", "nonterm")], [("arg_list_nonempty", "nonterm")]])
    y += 76

    draw_panel(draw, right_x, y, right_x + right_w, y + 66, "arg_list_nonempty")
    draw_sequence(draw, right_x + 8, y + 18, [("expr", "nonterm"), (",", "term"), ("expr", "nonterm")], line_w=8, note="One or more expressions")
    y += 76

    draw_panel(draw, right_x, y, right_x + right_w, y + 620, "expression")
    draw.text((right_x + 10, y + 24), "A. Primary expressions", font=FONT_SMALL, fill=TEXT)
    draw_stack(draw, right_x + 12, y + 42, [
        [("INT_LITERAL", "term")],
        [("true", "term")],
        [("false", "term")],
        [("IDENT", "term")],
        [("(", "term"), ("expr", "nonterm"), (")", "term")],
    ])
    draw.text((right_x + 10, y + 146), "B. Function calls", font=FONT_SMALL, fill=TEXT)
    draw_stack(draw, right_x + 12, y + 164, [
        [("IDENT", "term"), ("(", "term"), ("arg_list", "nonterm"), (")", "term")],
    ])
    draw.text((right_x + 10, y + 212), "C. Unary expressions", font=FONT_SMALL, fill=TEXT)
    draw_stack(draw, right_x + 12, y + 228, [
        [("-", "term"), ("expr", "nonterm")],
        [("!", "term"), ("expr", "nonterm")],
    ])
    draw.text((right_x + 10, y + 292), "D. Binary expressions", font=FONT_SMALL, fill=TEXT)
    left_rows = [
        [("expr", "nonterm"), ("||", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("&&", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("==", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("!=", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("<", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("<=", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), (">", "term"), ("expr", "nonterm")],
    ]
    right_rows = [
        [("expr", "nonterm"), (">=", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("+", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("-", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("*", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("/", "term"), ("expr", "nonterm")],
        [("expr", "nonterm"), ("%", "term"), ("expr", "nonterm")],
    ]
    for idx, row in enumerate(left_rows):
        draw_sequence(draw, right_x + 8, y + 308 + idx * 30, row, line_w=6)
    for idx, row in enumerate(right_rows):
        draw_sequence(draw, right_x + 162, y + 308 + idx * 30, row, line_w=6)
    y += 630

    draw_panel(draw, right_x, y, right_x + right_w, y + 92, "case_clause")
    draw_alt_rows(
        draw,
        right_x + 10,
        y + 16,
        "A)",
        [
            [("case", "term"), ("INT_LITERAL", "term"), ("block", "nonterm")],
            [("default", "term"), ("block", "nonterm")],
        ],
    )
    y += 102

    draw_panel(draw, right_x, y, right_x + right_w, y + 66, "case_list")
    draw_alt_rows(draw, right_x + 10, y + 18, "A)", [[("case_clause", "nonterm")], [("case_list case_clause", "nonterm")]])

    # Precedence
    draw_precedence_table(draw, prec_x, 78, W - 12, 456)

    # Bottom tokens
    base_y = 1260
    draw.rounded_rectangle((12, base_y - 18, W - 12, H - 12), radius=10, fill=PANEL_FILL, outline=PANEL_OUTLINE, width=2)
    draw_center(draw, W / 2, base_y - 4, "Parser tokens", FONT_LABEL)

    draw_token_group(draw, 24, base_y + 12, 420, H - 26, "Keywords", [
        ("fn", "term"), ("let", "term"), ("mut", "term"), ("if", "term"), ("else", "term"), ("for", "term"),
        ("return", "term"), ("switch", "term"), ("case", "term"), ("default", "term"), ("break", "term"),
        ("continue", "term"), ("int", "term"), ("bool", "term"), ("true", "term"), ("false", "term"),
    ])
    draw_token_group(draw, 434, base_y + 12, 670, H - 26, "Identifiers and literals", [
        ("IDENT", "term"), ("INT_LITERAL", "term")
    ])
    draw_token_group(draw, 684, base_y + 12, 1176, H - 26, "Operators", [
        ("=", "term"), ("+", "term"), ("-", "term"), ("*", "term"), ("/", "term"), ("%", "term"),
        ("==", "term"), ("!=", "term"), ("&&", "term"), ("||", "term"), ("!", "term"),
        ("<", "term"), ("<=", "term"), (">", "term"), (">=", "term"), ("->", "term")
    ])
    draw_token_group(draw, 1190, base_y + 12, 1390, H - 26, "Separators", [
        (";", "term"), (",", "term"), ("(", "term"), (")", "term"), ("{", "term"), ("}", "term"), (":", "term")
    ])
    draw_token_group(draw, 1402, base_y + 12, W - 24, H - 26, "Legend", [
        ("blue = nonterminal", "nonterm"), ("red = terminal", "term")
    ])

    tmp_path = Path(tempfile.gettempdir()) / "schema_grammar.png"
    img.save(tmp_path)
    shutil.copyfile(tmp_path, OUT_PATH)
    shutil.copyfile(tmp_path, DOWNLOADS_PATH)
    print(OUT_PATH)


if __name__ == "__main__":
    build()
