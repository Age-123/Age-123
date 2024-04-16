#ifndef GROUP_MANAGER_H_
#define GROUP_MANAGER_H_
#include "net_group.h"
class GroupManager {
 public:
  bool CheckValid(NetGroup* netgroup);
  void InsertNetGroup(NetGroup* netgroup);
  static GroupManager& GetManager() {
    static GroupManager group_manager;
    return group_manager;
  }
  list<NetGroup*> GetGroupList() { return group_list_; }
  void GetBound(int& leftx, int& belowy, int& rightx, int& topy);
  int GetNetNumbers();

 private:
  list<NetGroup*> group_list_;
  GroupManager(){};
  GroupManager(GroupManager&) = delete;
  GroupManager& operator=(GroupManager&) = delete;
};
#endif
