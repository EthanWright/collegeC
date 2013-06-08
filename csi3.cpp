//Ethan Wright linked list program

#include <iostream>
#include <string.h>
using namespace std;

class clicker {
      public:
             int clicks;
             clicker();
             clicker(string thelocation);
             void click();
             void reset();
             void display();
             void changeLocation();
             int getClicks();
             clicker *next;
             string location;
};

clicker::clicker() {
    clicks=0;
}

int clicker::getClicks(){
    return clicks;
}
clicker::clicker(string thelocation) {
    clicks=0;
    location=thelocation;
}

void clicker::click() {
     clicks++;
}

void clicker::reset() {
     clicks=0;
}

void clicker::display() {
     cout << "location: " << location << endl;
     cout << "clicks: " << clicks << endl << endl;
}

void clicker::changeLocation() {
     cout << "location? ";
     cin >> location;
}

class linkedlist {
      public:
       linkedlist() {start=NULL;}
       clicker *start;
       void insert(string targetloc, clicker* temp);
       void display(string targetloc);
       void displayall();
       void remove(string targetloc);
       void reset(string targetloc);
       int average();
       int count();
       void removeall();
};

void linkedlist::removeall() {
     start=0;
}

int linkedlist::average() {
     clicker *p=start;
     int total=0;
     while (p!=NULL) {
           total+=p->getClicks();
           p=p->next;
     }
     cout<< total/(linkedlist::count()) << endl;
}

void linkedlist::displayall() {
     clicker *p=start;
     while (p!=NULL) {
           p->display();
           p=p->next;
     }
}

void linkedlist::display(string targetloc) {
     clicker *p=start, *lastp;
     while (p && p->location<targetloc) {
           lastp=p;
           p=p->next;
     } 
     if (!p)
        cout << "not found" << endl;
     else
           p->display();
}

int linkedlist::count() {
    clicker *p=start;
    int count=0;
    while (p) {
          count++;
          p=p->next;
    }
    return count;
}

void linkedlist::reset(string targetloc) {
     clicker *p=start, *lastp;
     while (p && p->location<targetloc) {
           lastp=p;
           p=p->next;
     } 
     if (!p)
        cout << "not found" << endl;
     else
         //lastp->next=p->next;
         p->reset();
}

void linkedlist::insert(string targetloc, clicker* temp) {
     clicker *p=start, *lastp;
     while (p && p->location<=targetloc) {
           lastp=p;
           p=p->next;
     }
         if (p==start) {
            temp->next=start;
            start=temp;
         } else {
             temp->next=p;
             lastp->next=temp;
         }
}

void linkedlist::remove(string targetloc) {
     clicker *p=start, *lastp;
     while (p && p->location<targetloc) {
           lastp=p;
           p=p->next;
     }
      if (!p)
        cout << "not found" << endl;
     else
         if (p==start)
             start=p->next;
         else {
             lastp->next=p->next;
             delete p;
         }
}

int main() {
linkedlist list;
int input=1;
string location1;
clicker myclicker[20];
int count=1;
int numclicks;
while(input<9&&input>0) {
     input=0;
     location1="";
     cout <<
     "(1) enter an element into the list" << endl <<
     "(2) remove an element from the list" << endl <<
     "(3) display the contents of an element" << endl <<
     "(4) reset an element" << endl <<
     "(5) display all elements in the list" << endl <<
     "(6) display a count of how many elements there are in the list" << endl <<
     "(7) display the average number of clicks of the elements in the list" << endl <<
     "(8) remove all elements from the list" << endl <<
     "(9) remove all elements from the list and quit" << endl; 
     cin >> input;
     switch (input) {
         case 1:
              cout << "enter location" <<endl;
              cin >> location1;
              cout << "enter num of clicks" << endl;
              cin >> numclicks;
              myclicker[count].location=location1;
              myclicker[count].clicks=numclicks;
              list.insert(location1, &myclicker[count]);
              count++;
              break;
         case 2:
              cout << "enter location" <<endl;
              cin >> location1;
              list.remove(location1);
              break;
         case 3:
              cout << "enter location" <<endl;
              cin >> location1;
              list.display(location1);
              break;
         case 4:
              cout << "enter location" <<endl;
              cin >> location1;
              list.reset(location1);
              break;
         case 5:
              list.displayall();
              break;
         case 6:
              cout << "there are " << list.count() << " elements" <<endl;
              break;
         case 7:
              list.average();
              break;
         case 8:
              list.removeall();
              break;
         case 9:
              list.removeall();
              break;
         default:
              break;
     }
}
system("PAUSE");
return 0;   

}
