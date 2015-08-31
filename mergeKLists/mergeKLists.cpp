#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <functional>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

typedef pair<int, vector<ListNode*>::iterator> vp;

class Solution {

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<vp, vector<vp>, greater<vp>> minheap;
        vector<ListNode*> pointers(lists);
        // add all value to heap
        for (auto iter = pointers.begin(); iter != pointers.end(); iter++) {
            if (*iter == NULL)
                continue;
            auto temp = make_pair((*iter)->val, iter);
            minheap.push(temp);
        }

        // Initial result
        ListNode *result = NULL;
        ListNode *pnow = NULL;
        // Merge all lists
        while (minheap.size() > 0) {

            auto top = minheap.top();
            minheap.pop();
            int val = top.first;
            auto iter = top.second;

            auto node = new ListNode(val);
            if (pnow == NULL)
                result = node;
            else
                pnow->next = node;
            pnow = node;

            *iter = (*iter)->next;
            if (*iter != NULL)
                minheap.push(make_pair((*iter)->val, iter));
        }
        return result;
    }
};

int main() {
    ListNode *a1 = new ListNode(10);
    ListNode *a2 = new ListNode(20);
    ListNode *a3 = new ListNode(30);
    vector<ListNode*> v{a1, a2, a3};
    auto result = Solution().mergeKLists(v);
    cout << result->val << ' '<< result->next->val << endl;
    return 0;
}

