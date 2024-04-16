#include "verilogout.h"

#include "net.h"
void VerilogOut::Write(fstream* os) {
  *os << "module blk (" << endl;
  auto group_list = group_manager_->GetGroupList();
  for (auto group : group_list) {
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "  " << net->GetName() << "," << endl;
      *os << "  " << net->GetName() << "_BL," << endl;
    }
  }
  *os << ");" << endl;
  WriteInput(os);
  WriteOutput(os);
  WriteWire(os);
  WriteAssign(os);
  *os << "end module" << endl;
}
void VerilogOut::WriteInput(fstream* os) {
  auto group_list = group_manager_->GetGroupList();
  for (auto group : group_list) {
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "input " << net->GetName() << "_BL ;" << endl;
    }
  }
}
void VerilogOut::WriteOutput(fstream* os) {
  auto group_list = group_manager_->GetGroupList();
  for (auto group : group_list) {
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "output " << net->GetName() << " ;" << endl;
    }
  }
  return;
}
void VerilogOut::WriteWire(fstream* os) {
  auto group_list = group_manager_->GetGroupList();
  for (auto group : group_list) {
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "wire " << net->GetName() << " ;" << endl;
      *os << "wire " << net->GetName() << "_BL ;" << endl;
    }
  }
  return;
}
void VerilogOut::WriteAssign(fstream* os) {
  list<NetGroup*> group_list = group_manager_->GetGroupList();
  for (NetGroup* group : group_list) {
    list<Net*> netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "assign " << net->GetName() << " = " << net->GetName() << "_BL ;"
          << endl;
    }
  }
}
