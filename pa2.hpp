#ifndef pa2_hpp
#define pa2_hpp

#include <string>
#include <iostream>

using namespace std;

//Page represents a chunk of memory
class Page {
public:
    string name;
    Page *next;
    
    Page(string name) : name(name) {
        next = NULL;
    }
};


//Memory represents the whole place where operation systems use to allocate
//requested processes.
//Page to Memory is analogous to Node to Linkedlist.

class Memory {
public:
    
    //Head is like the head node of a linkedlist, which indicates where
    //the list starts. Here, it points to the start position of memory space
    Page *head;
    
    //Constructor of the class memory
    Memory() {
        
        head = new Page("Free");
        Page *crt = head;
      
        int i = 1;
        while (i < 32) {
            crt->next = new Page("Free");
            crt = crt->next;
            i++;
        }
    }
    
    /*  Implement Best-Fit Strategy :
        Find the start position of the smallest hole that is big enough */
    
    void bestFitAlgorithm(string programName, int programSize) {
        
        //smallestHole function here is used to return the start position to put the newly-requested program. if such position does not exist, return -1 instead
        Page* start = smallestHole(programName, programSize);
            
        //Store the  value of how many pages are needed in variable pagesUsed
        int pagesUsed = getSize(programSize);
        
        if (start) {
            //Calculate the end position to put the program
            Page* end = start;
            int i = 0;
            while (i <  getSize(programSize) && end != NULL) {
                end = end->next;
                i++;
            }
            
            //Allocate the program based its start and end position
            allocation(programName, start, end);
            printf("Program %s added successfully: %d page(s) used.\n\n", programName.c_str(), pagesUsed);
        }
    }
    
    /*  Implement Worst-Fit Strategy :
        Find the start position of the smallest hole that is big enough */
    
    void worstFitAlgorithm(string programName, int programSize) {
        
        //largestHole function here is used to return the start position to put the newly-requested program. if such position does not exist, return NULL instead
        Page* start = largestHole(programName, programSize);
        
        //Store the  value of how many pages are needed in variable pagesUsed
        int pagesUsed = getSize(programSize);
        
        if (start) {
            //Calculate the end position to put the program
            Page* end = start;
            int i = 0;
            while (i < getSize(programSize) && end != NULL){
                end = end->next;
                i++;
            }
            
            //Allocate the program based its start and end position
            allocation(programName, start, end);
            printf("Program %s added successfully: %d page(s) used.\n\n", programName.c_str(), pagesUsed);
        }
    }
    
    //Kill program
    void kill(string programName) {
        Page *crt = head;
        int cnt = 0;
        
        //Traverse the whole memory system by moving the crt pointer one step per time
        while (crt) {
            if (programName == crt->name) {
                crt->name = "Free";
                cnt++;
            }
            crt = crt->next;
        }
        
        //if cnt is 0, it means the programName is not found during the traverse process of the whole memory system
        if (cnt == 0) {
            cout << "No such program to kill.\n" << endl;
            return;
        }
        
        printf("Program %s successfully killed, %d page(s) reclaimed.\n\n", programName.c_str(), cnt);
        
    }
    
    //calculate how many fragments are out there, and return it
    int fragments() {
        int cnt = 0;
        Page* crt = head;
        
        while(crt) {
            if (crt->name == "Free") {
                do{
                    //Crt pointer moves to next until it is null or not free
                    crt = crt->next;
                }while (crt != NULL && crt->name == "Free");
                
                cnt++;
            }
            if (crt) crt = crt->next;
        }
        return cnt;
    }
    
    //Print memory
    void printMemory() {
        Page *crt = head;
        while (crt) {
            for (int i = 0; i < 8; i++) {
                printf("%-6s", crt->name.c_str());
                crt = crt->next;
            }
            cout << endl;
        }
        cout << endl;
    }
  
//Functions below are only for internal use, therefore are private
private:
    
    //Get the number of pages needed to allocate the program
    int getSize(int programSize) {
        return programSize % 4 == 0 ? programSize / 4 : programSize / 4 + 1;
    }
    
    //Return the start position of the smallest hole that is large enough to put a program based on best-fit strategy
    
    Page* smallestHole(string programName, int programSize) {
        if (duplicate(programName)) {
            printf("Error, Program %s already running.\n\n", programName.c_str());
            return NULL;
        }
        
        int min = 33;
        Page* start = NULL;
        Page* crt = head;
        int programPages = getSize(programSize);
    
        while (crt) {
            int cnt = 0;
            
            if (crt->name == "Free") {
                Page* tmp = crt;

                do {
                    cnt++;
                    crt = crt->next;
                } while (crt != NULL && crt->name == "Free");
            
            
                if (cnt >= programPages && cnt < min) {
                    start = tmp;
                    min = cnt;
                }
            }
            
            if(crt) crt = crt->next;
        }
        
        if (min == 33) {
            printf("Error, Not enough memory for Program %s.\n\n", programName.c_str());
            return NULL;
        }
        
        return  start;
    }

    //Return the start position of the largest hole that is big enough to put the program based on worst-fit strategy
    
    Page* largestHole(string programName, int programSize) {
        if (duplicate(programName)) {
            printf("Error, Program %s already running.\n\n", programName.c_str());
            return NULL;
        }
       
        int max = 0;
        Page* start = NULL;
        Page* crt = head;
        int programPages = getSize(programSize);
        
        while (crt)  {
            int cnt = 0;
          
            if(crt->name == "Free") {
              
                Page* tmp = crt;
                do {
                    cnt++;
                    crt = crt->next;
                } while (crt != NULL && crt->name == "Free");
            
            
                if (cnt >= programPages && cnt > max) {
                    start = tmp;
                    max = cnt;
                }
            }
            if (crt) crt = crt->next;
        }
        
        if (max == 0) {
            printf("Error, Not enough memory for Program %s.\n\n", programName.c_str());
            return NULL;
        }
         return  start;
    }

    //Allocate the program
    void allocation(string programName, Page* start, Page* end) {
        
            while (start != end && start != NULL) {
                start->name = programName;
                start = start->next;
        }
    }
    
    //Check if the program is already added
    bool duplicate(string programName) {
        Page* crt = head;
        while (crt) {
            if (crt->name == programName) return true;
            crt = crt->next;
        }
        return false;
    }
    
};


#endif /* pa2_hpp */
