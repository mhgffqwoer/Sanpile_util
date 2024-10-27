#include "Table.hpp"

namespace Sandpile {

Table::Table(const std::string& input_path)
    : start_array(StartArray(input_path)) {
  width = start_array.Width();
  height = start_array.Height();
  array = new uint8_t*[width];
  for (int idx = 0; idx < width; ++idx) {
    array[idx] = new uint8_t[height]{0};
  }

  for (int idx = 0; idx < start_array.Size(); ++idx) {
    if (start_array[idx].value >= 4) {
      queue_in.Push(start_array[idx].x, start_array[idx].y);
    }
  }

  TopUp();
}

Table::~Table() {
  for (int idx = 0; idx < width; ++idx) {
    delete[] array[idx];
  }
  delete[] array;
};

void Table::Clear() {
  for (int idx = 0; idx < width; ++idx) delete[] array[idx];
  delete[] array;
}

void Table::TopUp() {
  for (int idx = 0; idx < start_array.Size(); ++idx) {
    uint16_t x = start_array[idx].x;
    uint16_t y = start_array[idx].y;
    if (array[x][y] <= 10) {
      if (start_array[idx].value >= kTopUpValue) {
        array[x][y] += kTopUpValue;
        start_array[idx].value -= kTopUpValue;
      } else {
        array[x][y] += start_array[idx].value;
        start_array[idx].value = 0;
      }
    }
  }
}

bool Table::NeedResize() const {
  for (int idx = 0; idx < width; ++idx) {
    if (array[idx][0] >= 4) return true;
  }
  for (int idx = 0; idx < width; ++idx) {
    if (array[idx][height - 1] >= 4) return true;
  }
  for (int idx = 0; idx < height; ++idx) {
    if (array[0][idx] >= 4) return true;
  }
  for (int idx = 0; idx < height; ++idx) {
    if (array[width - 1][idx] >= 4) return true;
  }
  return false;
}

void Table::Resize() {
  if (NeedResize()) {
    uint8_t** new_array = new uint8_t*[width + 2];
    for (int idx = 0; idx < width + 2; ++idx) {
      new_array[idx] = new uint8_t[height + 2]{0};
    }
    for (int idx = 0; idx < width; ++idx) {
      for (int idx2 = 0; idx2 < height; ++idx2) {
        new_array[idx + 1][idx2 + 1] = array[idx][idx2];
      }
    }
    Clear();
    height += 2;
    width += 2;
    array = new_array;
    start_array.Increase();
    queue_in.Increase();
  }
}

bool Table::Stable() const { return queue_in.Empty(); }

uint16_t Table::Width() const { return width; }

uint16_t Table::Height() const { return height; }

uint8_t Table::Value(uint16_t x, uint16_t y) const { return array[x][y]; }

void Table::Iteration() {
  TopUp();
  Resize();

  while (!queue_in.Empty()) {
    Coords coords = queue_in.Pop();
    
    array[coords.x][coords.y] -= 4;
    array[coords.x - 1][coords.y] += 1;
    array[coords.x + 1][coords.y] += 1;
    array[coords.x][coords.y - 1] += 1;
    array[coords.x][coords.y + 1] += 1;

    if (array[coords.x][coords.y] >= 4) {
      queue_out.Push(coords.x, coords.y);
    }
    if (array[coords.x - 1][coords.y] == 4) {
      queue_out.Push(coords.x - 1, coords.y);
    }
    if (array[coords.x + 1][coords.y] == 4) {
      queue_out.Push(coords.x + 1, coords.y);
    }
    if (array[coords.x][coords.y - 1] == 4) {
      queue_out.Push(coords.x, coords.y - 1);
    }
    if (array[coords.x][coords.y + 1] == 4) {
      queue_out.Push(coords.x, coords.y + 1);
    }
  }

  queue_in = queue_out;
  queue_out.Clear();
}

}  // namespace Sandpile