class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {

        if (head == NULL) {
            return head;
        }
        else if (head->next == NULL) {
            return head;
        }

        ListNode* temp = head;
        int len = 1;

        while (temp->next != NULL) {
            temp = temp->next;
            len++;
        }

        k = k % len;
        if (k == 0) return head;

        temp->next = head;

        ListNode* p = head;
        for (int i = 1; i < len - k; i++) {
            p = p->next;
        }

        head = p->next;
        p->next = NULL;

        return head;
    }
};
