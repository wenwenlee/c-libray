/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       ListNode * result = new ListNode(0);
		ListNode * current = result;
		int carry = 0;
		int tmp, data1,data2,data3;
		
		while (l1 || l2)
		{
			data1 = 0;
            data2 = 0;
			if (l1)
			{
				data1 = l1->val;
				l1 = l1->next;
			}

			if (l2)
			{
				data2 = l2->val;
				l2 = l2->next;
			}

			tmp = carry + data1 + data2;
		    data3 = tmp % 10;
			carry = tmp / 10;
			current->next = new ListNode(data3);
			current = current->next;




		}
		if (carry)
			current->next = new ListNode(carry);
		return result->next;
    }
};
