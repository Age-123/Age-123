#include "group_manager.h"

#include <algorithm>
#include <climits>
bool GroupManager::CheckValid(NetGroup *netgroup) {
  int lx1, by1, rx1, ty1, layer_number1;
  int lx2, by2, rx2, ty2, layer_number2;
  netgroup->GetBound(lx1, by1, rx1, ty1);
  layer_number1 = netgroup->GetLayerNumber();
  for (auto group : group_list_) {
    group->GetBound(lx2, by2, rx2, ty2);
    layer_number2 = group->GetLayerNumber();
    if (layer_number1 != layer_number2 || lx1 > rx2 || rx1 < lx2 || by1 > ty2 ||
        ty1 < by2) {
      continue;
    }
    return false;
  }
  return true;
}

void GroupManager::InsertNetGroup(NetGroup *netgroup) {
  group_list_.push_back(netgroup);
}

int GroupManager::GetNetNumbers() {
  int total_numbers = 0;
  for (auto group : group_list_) {
    total_numbers += group->GetNetNumber();
  }
  return total_numbers;
}

void GroupManager::GetBound(int &leftx, int &belowy, int &rightx, int &topy) {
  int lx = INT_MAX;
  int by = INT_MAX;
  int rx = INT_MIN;
  int ty = INT_MIN;
  int x1, x2, y1, y2;
  for (auto group : group_list_) {
    group->GetBound(x1, y1, x2, y2);
    lx = min(lx, x1);
    by = min(by, y1);
    rx = max(rx, x2);
    ty = max(ty, y2);
  }
  leftx = x1;
  belowy = y1;
  rightx = x2;
  topy = y2;
  return;
}