#pragma once
#include <fstream>
#include <iostream>

namespace Sandpile {

struct StartCoords {
  uint16_t x;
  uint16_t y;
  uint64_t value;
};

class StartArray {
 private:
  static const size_t kShiftCoords = INT16_MIN * (-1);

  StartCoords* array;
  size_t count_elements;

  void GetValues(const std::string& input_path);

  void FixCoords();

  uint16_t GetMinX() const;

  uint16_t GetMinY() const;

  uint16_t GetMaxX() const;

  uint16_t GetMaxY() const;

 public:
  StartArray(const std::string& input_path);

  ~StartArray();

  StartArray(const StartArray& other) = delete;

  StartArray& operator=(const StartArray& other) = delete;

  void Increase();

  size_t Size() const;

  StartCoords& operator[](size_t idx);

  uint16_t Width() const;

  uint16_t Height() const;

  bool Empty() const;
};

}  // namespace Sandpile