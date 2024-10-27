#pragma once
#include "../Queue/Queue.hpp"
#include "../Tsv/Tsv.hpp"

namespace Sandpile {

class Table {
 private:
  static const uint8_t kTopUpValue = 50;
  static const uint8_t kResize = 5;

  uint8_t** array;
  uint16_t width;   // x
  uint16_t height;  // y

  Queue queue_in;
  Queue queue_out;
  StartArray start_array;

  void Clear();

  void TopUp();

  bool NeedResize() const;

  void Resize();

public:
  Table(const std::string& input_path);

  ~Table();

  Table(const Table& other) = delete;

  Table& operator=(const Table& other) = delete;

  bool Stable() const;

  void Iteration();

  uint16_t Width() const;

  uint16_t Height() const;

  uint8_t Value(uint16_t x, uint16_t y) const;
};

}  // namespace Sandpile