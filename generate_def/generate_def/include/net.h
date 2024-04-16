#ifndef NET_H_
#define NET_H_
#include <string>
using namespace std;
class NetGroup;
class Net {
 public:
  enum DIR { VERTICAL, HORIZONTAL };
  Net(int leftx, int belowy, int length, int width, int layer_number, int dir,
      NetGroup* netgroup)
      : left_x_(leftx),
        below_y_(belowy),
        length_(length),
        width_(width),
        layer_number_(layer_number),
        dir_(dir),
        net_group_(netgroup) {
    name_ = to_string(leftx) + "_" + to_string(belowy) + "_" +
            to_string(layer_number);
  }
  int GetLeftX() { return left_x_; }
  int GetBelowY() { return below_y_; }
  int GetLength() { return length_; }
  int GetWidth() { return width_; }
  NetGroup* GetNetGroup() { return net_group_; }
  string GetName() { return name_; }
  int GetLayerNumber() { return layer_number_; }
  void SetNetGroup(NetGroup* netgroup) { net_group_ = netgroup; }
  bool IsVertical() { return static_cast<DIR>(dir_) == DIR::VERTICAL; }

 private:
  int left_x_;
  int below_y_;
  int length_;
  string name_;
  int layer_number_;
  NetGroup* net_group_;
  int width_;
  int dir_;
};
#endif