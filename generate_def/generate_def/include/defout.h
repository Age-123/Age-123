#ifndef DEFOUT_H_
#define DEFOUT_H_
#include <fstream>

#include "group_manager.h"
class DefOut {
 public:
  void Write(fstream* os);
  DefOut(GroupManager* group_manager) : group_manager_(group_manager) {}

 private:
  void WriteTitle(fstream* os);
  void WriteDesign(fstream* os);
  void WriteComponet(fstream* os);
  void WriteProperty(fstream* os);
  void WriteVia(fstream* os);
  void WritePin(fstream* os);
  void WriteNet(fstream* os);

  GroupManager* group_manager_;
};
#endif