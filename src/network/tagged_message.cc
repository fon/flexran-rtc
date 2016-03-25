#include "tagged_message.h"

progran::network::tagged_message::tagged_message(char * msg, std::size_t size, int tag):
  size_(size), tag_(tag) {
  if (size <= max_normal_msg_size) {
    msg_contents_ = p_msg_;
    dynamic_alloc_ = false;
  } else {
    msg_contents_ = new char[size];
    dynamic_alloc_ = true;
  }
  std::memcpy(msg_contents_, msg, size);
}

progran::network::tagged_message::tagged_message(std::size_t size, int tag):
  size_(size), tag_(tag) {
  if (size > max_normal_msg_size) {
    msg_contents_ = new char[size];
    dynamic_alloc_ = true;
  } else {
    msg_contents_ = p_msg_;
    dynamic_alloc_ = false;
  }
}
  
progran::network::tagged_message::tagged_message(const tagged_message& m) {
  tag_ = m.getTag();
  size_ = m.getSize();
  if (size_ > max_normal_msg_size) {
    msg_contents_ = new char[size_];
    dynamic_alloc_ = true;
  } else {
    msg_contents_ = p_msg_;
    dynamic_alloc_ = false;
  }
  std::memcpy(msg_contents_, m.getMessageContents(), size_);
}

progran::network::tagged_message::tagged_message(tagged_message&& other) {
  tag_ = other.getTag();
  size_ = other.getSize();

  if (size_ > max_normal_msg_size) {
    msg_contents_ = new char[size_];
    dynamic_alloc_ = true;
  } else {
    msg_contents_ = p_msg_;
    dynamic_alloc_ = false;
  }
  std::memcpy(msg_contents_, other.getMessageContents(), size_);
}
  
progran::network::tagged_message& progran::network::tagged_message::operator=(progran::network::tagged_message&& other) {
  if (dynamic_alloc_) {
    delete [] msg_contents_;
  }

  tag_ = other.getTag();
  size_ = other.getSize();
  if (size_ > max_normal_msg_size) {
    msg_contents_ = new char[size_];
    dynamic_alloc_ = true;
  } else {
    msg_contents_ = p_msg_;
    dynamic_alloc_ = false;
  }
  std::memcpy(msg_contents_, other.getMessageContents(), size_);
  return *this;
}

progran::network::tagged_message::~tagged_message() {
  if (dynamic_alloc_) {
    delete [] msg_contents_;
  }
}
