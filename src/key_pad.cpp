#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keypad.h>

#define CS 10
#define RST 12
#define DC A0
#define SUDOKU_SIZE 9
#define NUM_ELEM (SUDOKU_SIZE*SUDOKU_SIZE)

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, RST);

int start_boards[1][NUM_ELEM] = {
  {5, 3, 0, 0, 7, 0, 0, 0, 0,
   6, 0, 0, 1, 9, 5, 0, 0, 0,
   0, 9, 8, 0, 0, 0, 0, 6, 0,
   8, 0, 0, 0, 6, 0, 0, 0, 3,
   4, 0, 0, 8, 0, 3, 0, 0, 1,
   7, 0, 0, 0, 2, 0, 0, 0, 6,
   0, 6, 0, 0, 0, 0, 2, 8, 0,
   0, 0, 0, 4, 1, 9, 0, 0, 5,
   0, 0, 0, 0, 8, 0, 0, 7, 9}
};

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {2, 3, 4, 5};
byte pin_column[COLUMN_NUM] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

int cell_height;
int cell_width;
byte pos_x;
byte pos_y;
byte cells_filled;
byte blocked[NUM_ELEM];
int sudoku_board[NUM_ELEM];

void draw_grid() {
  for (int i = 0; i <= SUDOKU_SIZE; i++) {
    uint16_t color = (i % 3 == 0) ? ST7735_BLUE : ST7735_WHITE; int lineWidth = (i % 3 == 0) ? 3 : 1;
    tft.fillRect(0, i * cell_height, tft.width(), lineWidth, color);
    tft.fillRect(i * cell_width, 0, lineWidth, tft.height(), color);
  }
}

void draw_sudoku() {
  tft.fillScreen(ST7735_BLACK);
  draw_grid();
  tft.setTextSize(1);

  for (int i = 0; i < SUDOKU_SIZE; i++) {
    for (int j = 0; j < SUDOKU_SIZE; j++) {
      int value = sudoku_board[i * SUDOKU_SIZE + j];
      if (value > 0) {
        tft.setCursor(j * cell_width + cell_width / 4, i * cell_height + cell_height / 4);
        tft.setTextColor(blocked[i * SUDOKU_SIZE + j] ? ST7735_RED : ST7735_WHITE);
        tft.print(value);
      }
    }
  }

  tft.drawRect(pos_y * cell_width, pos_x * cell_height, cell_width, cell_height, ST7735_YELLOW);
}

void set_board() {
  cells_filled = 0;
  int *board = start_boards[0];
  for (int i = 0; i < NUM_ELEM; i++) {
    sudoku_board[i] = board[i];
    blocked[i] = board[i] != 0;
    if (board[i] != 0) cells_filled++;
  }
}

bool is_valid_move(int x, int y, int num) {
  for (int i = 0; i < SUDOKU_SIZE; i++) {
    if (sudoku_board[x * SUDOKU_SIZE + i] == num || sudoku_board[i * SUDOKU_SIZE + y] == num) {
      return false;
    }
  }

  int startRow = (x / 3) * 3;
  int startCol = (y / 3) * 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (sudoku_board[(startRow + i) * SUDOKU_SIZE + (startCol + j)] == num) {
        return false;
      }
    }
  }

  return true;
}

void reset_game() {
  set_board();
  draw_sudoku();
}

void check_completion() {
  for (int i = 0; i < NUM_ELEM; i++) {
    if (sudoku_board[i] == 0) return;
  }

  tft.fillScreen(ST7735_GREEN);
  tft.setTextColor(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, tft.height() / 2 - 10);
  tft.print("Felicitari!");
}

void handle_key(char key) {
  if (key == 'A') pos_x = (pos_x == 0) ? SUDOKU_SIZE - 1 : pos_x - 1;
  else if (key == 'B') pos_x = (pos_x + 1) % SUDOKU_SIZE;
  else if (key == 'C') pos_y = (pos_y + 1) % SUDOKU_SIZE;
  else if (key == 'D') pos_y = (pos_y == 0) ? SUDOKU_SIZE - 1 : pos_y - 1;
  else if (key == '#') reset_game();
  else if (key >= '1' && key <= '9') {
    int num = key - '0';
    int index = pos_x * SUDOKU_SIZE + pos_y;
    if (!blocked[index] && is_valid_move(pos_x, pos_y, num)) {
      sudoku_board[index] = num;
      cells_filled++;
      draw_sudoku();
      check_completion();
    }
  } else if (key == '0') {
    int index = pos_x * SUDOKU_SIZE + pos_y;
    if (!blocked[index]) {
      sudoku_board[index] = 0;
      draw_sudoku();
    }
  }
}

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  cell_height = tft.height() / SUDOKU_SIZE;
  cell_width = tft.width() / SUDOKU_SIZE;

  randomSeed(analogRead(0));
  set_board();
  draw_sudoku();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    handle_key(key);
    draw_sudoku();
  }
}
