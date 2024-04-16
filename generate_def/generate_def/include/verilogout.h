#ifndef VERILOGOUT_H_
#define VERILOGOUT_H_

#include <fstream>

#include "group_manager.h"
class VerilogOut {
 public:
  VerilogOut(GroupManager* group_manager) : group_manager_(group_manager) {}
  void Write(fstream* os);

 private:
  void WriteInput(fstream* os);
  void WriteOutput(fstream* os);
  void WriteWire(fstream* os);
  void WriteAssign(fstream* os);
  GroupManager* group_manager_;
};
#endif