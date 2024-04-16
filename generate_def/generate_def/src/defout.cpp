#include "defout.h"

#include "net_group.h"
void DefOut::Write(fstream* os) {
  WriteTitle(os);
  WriteDesign(os);
}
void DefOut::WriteTitle(fstream* os) {
  *os << "VERSION 5.8 ;" << endl;
  *os << "NAMESCASESENSITIVE ON ;" << endl;
  *os << "DIVIDERCHAR \" \/ \" ;" << endl;
  *os << "BUSBITCHARS \" [] \" ;" << endl;
}
void DefOut::WriteDesign(fstream* os) {
  int x1, x2, y1, y2;
  group_manager_->GetBound(x1, y1, x2, y2);
  *os << "DESIGN blk  ;" << endl;
  *os << "UNITS DISTANCE MICRONS 1000 ;" << endl;

  *os << "DIEAREA ( " << x1 - 1000 << " " << y1 - 1000 << " ) ( " << x2 + 1000
      << " " << y2 + 1000 << " ) ;" << endl;
  WriteComponet(os);
  WriteProperty(os);
  WritePin(os);
  WriteNet(os);
  WriteVia(os);
  *os << "END DESIGN" << endl;
}
void DefOut::WriteComponet(fstream* os) {
  *os << "COMPONENTS 0;" << endl;
  *os << "END COMPONETS;" << endl;
}
void DefOut::WriteProperty(fstream* os) {}
void DefOut::WriteVia(fstream* os) {}
void DefOut::WritePin(fstream* os) {
  int net_numbers = 0;
  int pin_numbers;
  auto group_list = group_manager_->GetGroupList();
  net_numbers = group_manager_->GetNetNumbers();
  pin_numbers = net_numbers * 2;
  *os << "PINS " << pin_numbers << " ;" << endl;
  for (auto group : group_list) {
    auto dir = group->GetDir();
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      // add first pin
      *os << "- " << net->GetName() << " + "
          << "NET " << net->GetName() << "_BL" << endl;
      *os << "  + PORT + DIRECTION OUTPUT + USE SIGNAL" << endl;
      *os << "  + LAYER M" << net->GetLayerNumber() << " ( "
          << -1 * net->GetWidth() / 2 << " " << -1 * net->GetWidth() / 2
          << " ) "
          << " ( " << net->GetWidth() / 2 << " " << net->GetWidth() / 2 << " ) "
          << endl;
      int x, y;
      if (dir == NetGroup::VERTICAL) {
        x = net->GetLeftX() + net->GetWidth() / 2;
        y = net->GetBelowY();
      } else {
        x = net->GetLeftX();
        y = net->GetBelowY() + net->GetWidth() / 2;
      }
      *os << "  + PLACED"
          << " ( " << x << " " << y << " ) N ;" << endl;
      // add second pin
      *os << "- " << net->GetName() << "_BL"
          << " + "
          << "NET " << net->GetName() << "_BL" << endl;
      *os << "  + PORT + DIRECTION INPUT + USE SIGNAL" << endl;
      *os << "  + LAYER M" << net->GetLayerNumber() << " ( "
          << -1 * net->GetWidth() / 2 << " " << -1 * net->GetWidth() / 2
          << " ) "
          << " ( " << net->GetWidth() / 2 << " " << net->GetWidth() / 2 << " ) "
          << endl;
      if (dir == NetGroup::VERTICAL) {
        x = net->GetLeftX() + net->GetWidth() / 2;
        y = net->GetBelowY() + net->GetLength();
      } else {
        x = net->GetLeftX() + net->GetLength();
        y = net->GetBelowY() + net->GetWidth() / 2;
      }
      *os << "  + PLACED"
          << " ( " << x << " " << y << " ) N ;" << endl;
    }
  }
  *os << "END PINS" << endl;
  return;
}
void DefOut::WriteNet(fstream* os) {
  int x1, x2, y1, y2;
  int net_numbers = group_manager_->GetNetNumbers();
  list<NetGroup*> group_list = group_manager_->GetGroupList();
  *os << "NETS " << net_numbers << " ;" << endl;
  for (auto group : group_list) {
    auto dir = group->GetDir();
    auto netlist = group->GetNetList();
    for (auto net : netlist) {
      *os << "- " << net->GetName() << "_BL"
          << " ( "
          << "PIN " << net->GetName() << " ) ( "
          << "PIN " << net->GetName() << "_BL ) + USE SIGNAL" << endl;
      if (dir == NetGroup::VERTICAL) {
        x1 = net->GetLeftX() + net->GetWidth() / 2;
        y1 = net->GetBelowY();
        x2 = net->GetLeftX() + net->GetWidth() / 2;
        y2 = net->GetBelowY() + net->GetLength();
      } else {
        x1 = net->GetLeftX();
        y1 = net->GetBelowY() + net->GetWidth() / 2;
        x2 = net->GetLeftX() + net->GetLength();
        y2 = net->GetBelowY() + net->GetWidth() / 2;
      }
      *os << "  +ROUTED M" << net->GetLayerNumber() << " ( " << x1 << " " << y1
          << " 0"
          << " ) ( " << x2 << " " << y2 << " 0"
          << " ) ;" << endl;
    }
  }
  *os << "END NETS" << endl;
}
