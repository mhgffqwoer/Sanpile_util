#include "Queue.hpp"

namespace Sandpile {

Queue::Queue() : head(0), tail(0), capacity(0), array(new Coords[1]) {}

Queue::~Queue() { delete[] array; }

Queue& Queue::operator=(const Queue& other) {
  if (this != &other) {
    delete[] array;
    head = other.head;
    tail = other.tail;
    capacity = other.capacity;
    array = other.array;
  }
  return *this;
}

void Queue::Push(uint16_t coord_x, uint16_t coord_y) {
  if (tail == capacity) {
    capacity = (tail - head + 1) * 2;
    Coords* tmp = new Coords[capacity];
    for (size_t idx = 0; idx < tail - head; ++idx) {
      tmp[idx] = array[head + idx];
    }
    delete[] array;
    array = tmp;
    tail -= head;
    head = 0;
  }
  array[tail].x = coord_x;
  array[tail].y = coord_y;
  ++tail;
}

Coords Queue::Pop() {
  Coords result = array[head];
  ++head;
  return result;
}

void Queue::Increase() {
  for (int idx = head; idx < tail; ++idx) {
    array[idx].y++;
    array[idx].x++;
  }
}

void Queue::Clear() {
  head = 0;
  tail = 0;
  capacity = 0;
  array = new Coords[0];
}

bool Queue::Empty() const { return head == tail; }

}  // namespace Sandpile