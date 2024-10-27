#include "Tsv.hpp"

namespace Sandpile {

StartArray::StartArray(const std::string& input_path) : count_elements(0) {
  std::ifstream file(input_path);

  if (!file.is_open()) {
    std::cerr << "Can't open file: " << input_path << std::endl;
    exit(1);
  }

  char line[64];
  while (file.getline(line, 64)) {
    count_elements++;
  }

  array = new StartCoords[count_elements];
  file.close();

  GetValues(input_path);
}

StartArray::~StartArray() { delete[] array; }

size_t StartArray::Size() const { return count_elements; }

StartCoords& StartArray::operator[](size_t idx) { return array[idx]; }

void StartArray::GetValues(const std::string& input_path) {
  std::ifstream file(input_path);

  char line[64];
  for (int idx = 0; file.getline(line, 64); ++idx) {
    int coord_x, coord_y;
    uint64_t value;
    StartCoords tmp;

    sscanf(line, "%d %d %llu", &coord_x, &coord_y, &value);
    array[idx].x = coord_x + kShiftCoords;
    array[idx].y = coord_y + kShiftCoords;
    array[idx].value = value;
  }

  file.close();
  FixCoords();
}

void StartArray::Increase() {
  for (int idx = 0; idx < count_elements; ++idx) {
    array[idx].x++;
    array[idx].y++;
  }
}

void StartArray::FixCoords() {
  int min_x = GetMinX();
  int min_y = GetMinY();
  for (int idx = 0; idx < count_elements; ++idx) {
    array[idx].x -= min_x;
    array[idx].y -= min_y;
  }
}

uint16_t StartArray::GetMinX() const {
  uint16_t result = array[0].x;
  for (int idx = 1; idx < count_elements; ++idx) {
    if (array[idx].x < result) {
      result = array[idx].x;
    }
  }
  return result;
}

uint16_t StartArray::GetMinY() const {
  uint16_t result = array[0].y;
  for (int idx = 1; idx < count_elements; ++idx) {
    if (array[idx].y < result) {
      result = array[idx].y;
    }
  }
  return result;
}

uint16_t StartArray::GetMaxX() const {
  uint16_t result = array[0].x;
  for (int idx = 1; idx < count_elements; ++idx) {
    if (array[idx].x > result) {
      result = array[idx].x;
    }
  }
  return result;
}

uint16_t StartArray::GetMaxY() const {
  uint16_t result = array[0].y;
  for (int idx = 1; idx < count_elements; ++idx) {
    if (array[idx].y > result) {
      result = array[idx].y;
    }
  }
  return result;
}

bool StartArray::Empty() const { 
  for (int idx = 0; idx < count_elements; ++idx) {
    if (array[idx].value != 0) return false;
  }
  return true;
}

uint16_t StartArray::Width() const { return GetMaxX() - GetMinX() + 1; }

uint16_t StartArray::Height() const { return GetMaxY() - GetMinY() + 1; }

}  // namespace Sandpile