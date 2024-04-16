#include "net_group.h"
void NetGroup::GetBound(int &lx, int &by, int &rx, int &ty) {
  if (GetDir() == DIR::VERTICAL) {
    lx = left_x_;
    by = below_y_;
    rx = left_x_ + width_ * net_number_ + spacing_ * (net_number_ - 1);
    ty = by + length_;
  } else {
    lx = left_x_;
    by = below_y_;
    rx = lx + length_;
    ty = below_y_ + width_ * net_number_ + spacing_ * (net_number_ - 1);
  }

  return;
}
void NetGroup::Create() {
  for (int i = 0; i < net_number_; ++i) {
    int leftx = left_x_ + i * (spacing_ + width_);
    Net *net =
        new Net(leftx, below_y_, length_, width_, layer_number_, dir_, this);
    InsertNet(net);
  }
  return;
}
void NetGroup::Delete() {
  for (auto net : netlist_) {
    delete net;
    net = nullptr;
  }
  return;
}
