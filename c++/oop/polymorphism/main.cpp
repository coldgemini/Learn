#include<iostream> 
using namespace std; 
   
class Base 
{ 
public: 
    virtual void show() { cout<<" In Base \n"; } 
}; 
   
class Derived: public Base 
{ 
public: 
    void show() { cout<<"In Derived \n"; } 
}; 
   
int main(void) 
{ 
    Base *bp = new Derived; 
    bp->show();  // RUN-TIME POLYMORPHISM 
	/* bp = static_cast<Base*>(bp); */
    /* bp->show();  // RUN-TIME POLYMORPHISM */ 
	bp = dynamic_cast<Base*>(bp);
    bp->show();  // RUN-TIME POLYMORPHISM 

    Base *bb = new Base; 
    bb->show();  // RUN-TIME POLYMORPHISM 
	bb = static_cast<Base*>(bb);
    bb->show();  // RUN-TIME POLYMORPHISM 


    return 0; 
} 
