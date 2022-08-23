/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m,vector<int> (n,-1));
        int left=0,right=n-1,up=0,down=m-1,d=0, i=0, j=0;
        vector<vector<int>> dir{ {0,1} , {1,0} , {0,-1} , {-1,0}};
        ListNode* temp = head;
        while(temp){
          ans[i][j]=temp->val;
          if(d==0 && j==right){
            d++;
            up++;
          }else if(d==1 && i==down){
            d++;
            right--;
          }else if(d==2 && j==left){
            d++;
            down--;
          }else if(d==3 && i==up){
            d=0;
            left++;
          }
          i += dir[d][0];
          j += dir[d][1];
          temp=temp->next;
        }
        return ans;
    }
};