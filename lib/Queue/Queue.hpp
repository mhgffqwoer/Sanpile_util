#pragma once
#include <iostream>

namespace Sandpile {

struct Coords {
  uint16_t x;
  uint16_t y;
};

class Queue {
 private:
  Coords* array;
  size_t capacity;
  size_t head;
  size_t tail;

 public:
  Queue();

  ~Queue();

  Queue(const Queue& other) = delete;

  Queue& operator=(const Queue& other);

  void Push(uint16_t coord_x, uint16_t coord_y);

  Coords Pop();

  void Increase();

  void Clear();

  bool Empty() const;
};

}  // namespace Sandpile