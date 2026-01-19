class MyStack {
public:
queue<int>q1;
    MyStack() {
        
    }
    
    void push(int x) {
        if(q1.empty())
            q1.push(x);
        else{
            queue<int>q2;
            while(!q1.empty()){
                // copy Q1 in Q2
                q2.push(q1.front());
                q1.pop();
            }
            // insert new val in front of q1
            q1.push(x);
            while(!q2.empty()){
                // copy Q2 in Q1
                q1.push(q2.front());
                q2.pop();
            }
            }
    }
    
    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */