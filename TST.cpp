#include <iostream>
#include <string>
#include <stack>

struct node
{
    node(char c) : data{c}, end{false}, left{nullptr}, right{nullptr}, equal{nullptr} {}
    char data ;
    bool end;
    node* left = nullptr;
    node* equal = nullptr;
    node* right = nullptr;
};

class Ternary
{
public:
    Ternary(std::string str);
    void insert(char* s);
    void insert(std::string str);
    bool search(std::string str);
    void remove(std::string str);
private:
    node* root_;
};


Ternary::Ternary(std::string str)
{
    int len = static_cast<int>(str.length());
    //std::cout << "word len : " << len << "\n";
    if(len == 0)
        return;
    
    root_ = new node(str[0]);
    node* prev = root_;
    for(int i = 1;i < len;i++)
    {
        prev -> equal = new node(str[i]);
        prev = prev -> equal;
    }
    prev -> end = true;
}

void Ternary::insert(std::string str)
{
    int len = static_cast<int>(str.length());
    
    node* prev = nullptr;
    node* current = root_;
    for(int i = 0;i < len;i++)
    {
        if(current == nullptr)
        {
            prev -> equal = new node(str[i]);
            current = prev -> equal;
            
        }
        else if(str[i] == current -> data)
        {
            if(current -> equal == nullptr)
            {
                current -> equal = new node(str[i]);
                prev = current;
                current = current -> equal;
            }
            
            prev = current;
            current = current -> equal;
        
        }
        else if(str[i] > current -> data)
        {
            if(current -> right == nullptr)
            {
                current -> right = new node(str[i]);
                prev = current;
                current = current -> right;
            
            }
            
            prev = current;
            current = current -> right;
        }
        else if(str[i] <  current -> data)
        {
            if(current -> left == nullptr)
            {
                current -> left = new node(str[i]);
                prev = current;
                current = current -> left;
            }
            
            prev = current;
            current = current -> left;
        }
    }
    prev -> end = true;
}

bool Ternary::search(std::string str)
{
    int len = static_cast<int>(str.length());
    
    node* prev = root_;
    
    for(int i = 0;i < len;i++)
    {
        if(prev == nullptr)
            return false;
        if(str[i] == prev -> data)
        {
            prev = prev -> equal;
        }
        else if(str[i] > prev -> data)
        {
            prev = prev -> right;
        }
        else if(str[i] <  prev -> data)
        {
            prev = prev -> left;
        }
    }
    return prev -> end;
}

void Ternary::remove(std::string str)
{
    //用一個容器紀錄經過的位址，然後從最下面檢查上去
    std::stack<node*> address;
    
    int len = static_cast<int>(str.length());
    node* prev = root_;
    
    for(int i = 0;i < len;i++)
    {
        if(prev == nullptr)
            break;
        address.push(prev);
        if(str[i] == prev -> data)
        {
            prev = prev -> equal;
        }
        else if(str[i] > prev -> data)
        {
            prev = prev -> right;
        }
        else if(str[i] <  prev -> data)
        {
            prev = prev -> left;
        }
    }
    address.push(prev);
    prev -> end = false;
    
    while(!address.empty())
    {
        node* now = address.top();
        address.pop();
        if(now -> equal == nullptr && now -> left == nullptr && now -> right == nullptr)
        {
            delete now;
        }
        else
        {
            break;
        }
    }
}


int main()
{
    //std::cout << "testing...\n";
    Ternary t(std::string("Hello"));
    t.insert(std::string("Hell"));
    t.insert(std::string("Help"));
    t.insert(std::string("Hellish"));
    
    std::cout << std::boolalpha <<t.search(std::string("Hell")) << std::endl;

    t.remove(std::string("Help"));
    
    std::cout << std::boolalpha <<t.search(std::string("Help")) << std::endl;
    
    return 0;
}
