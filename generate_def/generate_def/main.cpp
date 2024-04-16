#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "defout.h"
#include "group_manager.h"
#include "net.h"
#include "net_group.h"
#include "verilogout.h"
using namespace std;
int main(int argc, char* argv[]) {
  int net_number;
  int width;
  int length;
  int left_x;
  int below_y;
  int spacing;
  int dir;
  int layer_number;
  ifstream ifs;
  ifs.open(argv[1], std::ios::in);
  if (!ifs.is_open()) {
    cout << "fail to open csv file" << endl;
    return 0;
  }
  string str;
  std::vector<string> item;
  while (getline(ifs, str)) {
    item.push_back(str);
  }
  GroupManager& group_manager = GroupManager::GetManager();
  for (int i = 1; i < item.size(); i++) {
    string words;
    std::istringstream istr(item[i]);
    std::vector<int> arr;
    while (getline(istr, words, ',')) {
      arr.push_back(stoi(words));
    }
    layer_number = arr[0];
    net_number = arr[1];
    width = arr[2];
    length = arr[3];
    spacing = arr[4];
    left_x = arr[5];
    below_y = arr[6];
    dir = arr[7];
    NetGroup* netgroup = new NetGroup(net_number, layer_number, width, spacing,
                                      length, left_x, below_y, dir);
    if (group_manager.CheckValid(netgroup)) {
      netgroup->Create();
      group_manager.InsertNetGroup(netgroup);
    } else {
      cout << "the " << i << " net group is illegal!" << endl;
    }
  }
  DefOut defout(&group_manager);
  VerilogOut verilogout(&group_manager);
  fstream def("test.def", ios::out);
  fstream verilog("test.v", ios::out);
  defout.Write(&def);
  verilogout.Write(&verilog);
  return 0;
}