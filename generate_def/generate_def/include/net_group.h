#ifndef NET_GROUP_
#define NET_GROUP_
#include <list>
#include <string>

#include "net.h"
using namespace std;
class Net;
class NetGroup {
 public:
  NetGroup(int net_number, int layer_number, int width, int spacing, int length,
           int leftx, int belowy, int dir) {
    net_number_ = net_number;
    width_ = width;
    spacing_ = spacing;
    left_x_ = leftx;
    below_y_ = belowy;
    dir_ = dir;
    length_ = length;
    layer_number_ = layer_number;
  }
  enum DIR { VERTICAL, HORIZONTAL };
  DIR GetDir() { return static_cast<DIR>(dir_); }
  int GetWidth() { return width_; }
  int GetSpacing() { return spacing_; }
  int GetNetNumber() { return net_number_; }
  int GetLength() { return length_; }
  int GetLayerNumber() { return layer_number_; }
  list<Net *> GetNetList() { return netlist_; }
  void InsertNet(Net *net) { netlist_.push_back(net); }
  void Create();
  void GetBound(int &lx, int &by, int &rx, int &ty);
  void Delete();

 private:
  int width_;
  int length_;
  int dir_;
  int net_number_;
  int spacing_;
  int left_x_;
  int below_y_;
  int layer_number_;
  list<Net *> netlist_;
};
#endif