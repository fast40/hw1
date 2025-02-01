#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val) {
  if (tail_ == nullptr || tail_->last == ARRSIZE) {
    Item* newItem = new Item();

    newItem->prev = tail_;

    if (tail_ == nullptr) {
      head_ = newItem;
    }
    else {
      tail_->next = newItem;
    }

    tail_ = newItem;
  }

  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}

void ULListStr::push_front(const std::string& val) {
  if (head_ == nullptr || head_->first == 0) {
    Item* newItem = new Item();

    newItem->next = head_;
    newItem->first = ARRSIZE;
    newItem->last = ARRSIZE;

    if (head_ == nullptr) {
      tail_ = newItem;
    }
    else {
      head_->prev = newItem;
    }

    head_ = newItem;
  }
  
  head_->val[head_->first - 1] = val;
  head_->first--;
  size_++;
}

void ULListStr::pop_back() {
  if (tail_ == nullptr) {
    return;
  }

  tail_->last--;
  size_--;

  if (tail_->first == tail_->last) {
    Item* temp = tail_;
    tail_ = tail_->prev;
    delete temp;

    if (tail_ == nullptr) {
      head_ = nullptr;
    }
    else {
      tail_->next = nullptr;
    }
  }
}

void ULListStr::pop_front() {
  if (head_ == nullptr) {
    return;
  }

  head_->first++;
  size_--;

  if (head_->first == head_->last) {
    Item* temp = head_;
    head_ = head_->next;
    delete temp;

    if (head_ == nullptr) {
      tail_ = nullptr;
    }
    else {
      head_->prev = nullptr;
    }
  }
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  Item* current = head_;
  size_t index = 0;

  while (current != nullptr) {
    size_t occupied = current->last - current->first;

    if (loc < index + occupied) {
      return &current->val[current->first + (loc - index)];
    }

    index += occupied;

    current = current->next;
  }

  return nullptr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
