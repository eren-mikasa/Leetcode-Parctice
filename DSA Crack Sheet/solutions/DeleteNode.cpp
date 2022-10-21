class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(!head || !head->next) return NULL;
        ListNode* first=head;
        ListNode* second=head->next;
        while(second->next && second->next->next){
            first=first->next;
            second=second->next->next;
        }
        ListNode* temp = first->next;
        first->next=first->next->next;
        delete temp;
        return head;
    }
};