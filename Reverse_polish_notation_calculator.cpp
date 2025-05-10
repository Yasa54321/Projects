#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class Node{
    public:
        double data;
        Node* next;
    
    
};


class LinkedList{
    private:
        Node* front;
        Node* temp;
    public:

        int count;
        
        
        LinkedList(){
            front = 0;
        }
    
    
    void push(double num){
        Node* n = new Node();
        n->data = num;
        n->next = front;
        front = n;
        count++;
    }
    
    double pop (){
        if (front == 0)
        {
            //cout<<"error the stack is empty"<<endl;
            return -1;
            
        }
        else 
        {
           temp = front;
           front = front->next;
           double int_to_be_returned = temp->data;
           delete temp;
           count--;
            return int_to_be_returned;
        }
    }
    bool isEmpty(){
        if (front == 0)
        {
            return true;
        }
        else
            return false;
    }
    
    void clearstack(){
        for (int i = 0; i<=count; i++)
        {
            pop();
        }
    }

    
};

int main(){
    
    //Declaration of Variables
    string user_input;
    string orig_user_input;
    double first_operand;  // Declaration left unchanged
    double second_operand;
    int number_of_operands = 0;
    int number_of_operators = 0;
    bool error = 0;
    
    //instantiate the stack
    LinkedList stack;
    
    //Initial prompt
    cout<<"Please enter a polish expression (Press 0 to exit)"<<endl;
    getline(cin,orig_user_input);
    
    
    //While loop terminates with 0
    while (orig_user_input!= "0")
    {
        stringstream user_input2(orig_user_input);
    
    //parses user input
    while (user_input2 >> user_input)
    {
    
        //checks to see if user inputs an operator
        if (user_input == "+" ||  user_input == "-" || user_input == "/" || user_input == "*")
        {
            number_of_operators++;
            second_operand = stack.pop(); 
            second_operand = stack.pop();

            //checks to see if division by zero error
           if (user_input == "/" && second_operand == 0.00 && error == 0)
            {
                cout<<"Error: Division by zero"<<endl;
                error = 1;
            }
            //does the operation otherwise
            else {
                
            char switch_statement = user_input[0];
            switch(switch_statement){
                case '+': stack.push(second_operand + second_operand);
                break;
                case '-': stack.push(second_operand - second_operand);
                break;
                case '/': stack.push(second_operand / second_operand);
                break;
                case '*': stack.push(second_operand * second_operand);
                break;
                default: break;
            }
        }
        }
        //if equal operator no change needed
        else if (user_input == "=")
        {
            continue;
        }
        //pushes the operand onto the stack
        else
        {
            second_operand = stof(user_input);
            stack.push(second_operand);
            number_of_operands++;
        }
    }
        
    //checking at the end if there are too many operands or operators
    if (number_of_operators >= number_of_operands)
    {
        cout<<"Error: Too many operators"<<endl;
        error = 1;
    }
    else if (stack.count > 1){
        cout<<"Error: Too many operands"<<endl;
        error = 1;
    }
    //outputs the answer if correct
    else{
        if (error == 0)
        {
            cin.sync();
            cout << stack.pop() << endl;
        }
    }

    //clears stack and clears error and counters for next run
    stack.clearstack();
    number_of_operands = 0;
    number_of_operators = 0;
    error = 0;
  
    cout<<"Please enter a polish expression (Press 0 to exit) "<<endl;
    getline(cin, orig_user_input);
    }
}