#include "IteratorUtilityLL.h"

/*
Name: clearIterator
Process: recursively clears all data in iterator linked list, 
         returns memory to OS
Function input/parameters: working linked list pointer (StudentType *)
Function output/parameters: none
Function output/returned: NULL
Device input/file: none
Device output/monitor: none
Dependencies: free, clearIterator (recursive)
*/
StudentType *clearIterator( StudentType *wkgStudentPtr )
  {
  // variables 
  // local ptr to this function
  StudentType *tempPtr;   
      
  // check if iterator LL is already empty
  if( !isEmpty( wkgStudentPtr ) )
    {    
    // check if has next ptr
    // has next did not work here
    if( wkgStudentPtr->nextPtr != NULL ) 
      {
      // set tempPtr to the data passed in
      tempPtr = wkgStudentPtr->nextPtr;
      
      // set wkgStudentPtr to the next value
      wkgStudentPtr->nextPtr = tempPtr->nextPtr;
      
      // free the data at the tempPtr
      free( tempPtr );
      
      // call clear iterator again with the wkgStudentPtr
      clearIterator( wkgStudentPtr );
      }
      
    else
      {
      // we are at the end if the nextPtr is NULL
      // free the wkgStudnetPtr   
      free( wkgStudentPtr ); 
      }  
        
    }    
  
  // return completion
  return NULL;    
  }

/*
Name: copyIterator
Process: creates new linked list with new nodes
         from given linked list, returns head pointer
Function input/parameters: source linked list head pointer (const StudentType *)
Function output/parameters: none
Function output/returned: destination linked list head pointer (StudentType *),
                          or NULL if source pointer is NULL
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
StudentType *copyIterator( const StudentType *studentHeadPtr )
  {
  // check if data is even avaliable ( source poiter is not NULL )
  if( !isEmpty( studentHeadPtr ) )
    {
    // variables            
    // create new LL headPtr
    StudentType *cpyHeadPtr;

    // create wkgPtrs for each LL
    StudentType *srcWkgPtr, *destWkgPtr;
    
    // set new head ptr to null
    cpyHeadPtr = NULL;
    
    // set wkgPtrs to start
    srcWkgPtr = studentHeadPtr->nextPtr;
    
    // plug in first value into the new LL
    cpyHeadPtr = createStudentNodeFromStruct( *studentHeadPtr );
    
    // set the destWkgPtr to the new iterator head
    destWkgPtr = cpyHeadPtr;
    
    // check if first value was the current
    if( studentHeadPtr->current )
      {
      // set the head of the copyHeadPtr to current
      cpyHeadPtr->current = true;    
      }
    
    // iterate through LL until source wkgPtr is NULL
    while( srcWkgPtr != NULL )
      {
      // plug value into LL
      destWkgPtr->nextPtr = createStudentNodeFromStruct( *srcWkgPtr );
      
      // check if current needs to be put in this node
      if( srcWkgPtr->current )
        {
        // set the dest current to true    
        destWkgPtr->current = true;    
        }
      
      // increment dest wkgPtrs
      destWkgPtr = destWkgPtr->nextPtr;
      
      // increment source wkgPtr
      srcWkgPtr = srcWkgPtr->nextPtr;
      } 
      
    // once at end of LL return headPtr of new LL
    return cpyHeadPtr;    
        
    }    
   
  // if empty
  return NULL;    
  }

/*
Name: copyIteratorString
Process: copies one string to another, assumes destination string
         has allocated memory
Function input/parameters: c-style source string (const char *)
Function output/parameters: c-style destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyIteratorString( char *destStr, const char *sourceStr )
  {
  // variables
  int index = 0;
  
  // iterate while not at end of src string
  while( sourceStr[index] != NULL_CHAR )
    {
    // copy letter to destStr
    destStr[index] = sourceStr[index];
    
    // increment index
    index++;
    
    // set end of destStr
    destStr[index] = NULL_CHAR;        
    }
  }

/*
Name: copyStudentData
Process: copies all parts of the student data, sets next pointer to NULL
Function input/parameters: source Student data (const StudentType)
Function output/parameters: destination Student data (StudentType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: copyIteratorString
*/
void copyStudentData( StudentType *destStudent, const StudentType srcStudent )
  {
  // copy all parts of student data
  destStudent->current = srcStudent.current;
  destStudent->gender = srcStudent.gender;
  destStudent->gpa = srcStudent.gpa;
  destStudent->studentId = srcStudent.studentId;
  
  // copy name with copyIteratorString
  copyIteratorString( destStudent->name, srcStudent.name );  

  // set next pointer to NULL
  destStudent->nextPtr = NULL;
      
  }

/*
Name: createStudentNodeFromStruct
Process: creates struct node,
         sets student struct to another StudentType struct,
         sets current Boolean to false, and nextPtr to NULL
Function input/parameters: student data from struct
Function output/parameters: none
Function output/returned: pointer to student data (StudentType *)
Device input/file: none
Device output/monitor: none
Dependencies: malloc, sizeof, setStudentData
*/
StudentType *createStudentNodeFromStruct( StudentType studentData )
  {
  // variables
  StudentType *wkgPtr;
  
  // set wkgPtr memory, create new node
  wkgPtr = ( StudentType *)malloc( sizeof( StudentType ) );
  
  // set data in new node
  setStudentData( wkgPtr, studentData.name, studentData.studentId,
                                  studentData.gender, studentData.gpa );
  
  // set the node current to false
  wkgPtr->current = false;
  
  // set next Ptr to NULL
  wkgPtr->nextPtr = NULL;
  
  // return the new node
  return wkgPtr;    
      
  }

/*
Name: displayIterator
Process: displays iterator linked list if it is not empty,
         shows bottom to top of iterator data organization,
         if empty, displays "Iterator is empty - Display not conducted"
Function input/parameters: iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: printf, printIteratorChars
*/
void displayIterator( StudentType *wkgPtr )
  {
  // check if list is not empty
  if( !isEmpty( wkgPtr ) )
    {
    // variables
    StudentType *displayPtr;
    int spacing = 24, offset = 2 ;    
        
    // set the displayPtr to the headPtr    
    displayPtr = wkgPtr;
        
    // display text
    printf( "\nIterator Display:\n" );
    
    // print left side of iterator
    printf( "Left side of iterator-> " );  
    
    // iterate through LL until hitting NULL
    while( displayPtr != NULL )
      {       
      // check if we are at the current bool
      if( displayPtr->current )
        {
        // print the left bracket
        printf( "[ " );
        }    
          
      // print the data in the current node
      printf( "%s, %d, %c, %.4f", displayPtr->name, displayPtr->studentId, 
                                    displayPtr->gender, displayPtr->gpa  );
      
      // check if at current
      if( displayPtr->current )
        {
        // print the right bracket
        printf( " ]" );    
        }    
          
      // check if not at end
      if( displayPtr->nextPtr != NULL )
        {
        // print semicolon and new line with correct spacing
        printf( ";\n" );
        
        // calculate spacing
        spacing += offset;
        
        // print the offset with spaces
        printIteratorChars( spacing, SPACE );    
        }    
       
      // increment node
      displayPtr = displayPtr->nextPtr;	        
      }
    
    // print right side of iterator text
    printf( " <-Right side of iterator\n" );    
         
    }
    
  // else the LL is empty
  else
    {
    // report failure
    printf( "Iterator is empty - Display not conducted\n" );     
    }
      
  }

/*
Name: getPtrBeforeCurrent
Process: finds pointer immediately prior to current node,
         if list is empty or first node is current, returns NULL,
         assumes list has valid current node
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: pointer to node prior to current (StudentType *)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
StudentType *getPtrBeforeCurrent( StudentType *studentHeadPtr )
  {
  // check if list is empty AND isnt the current
  if( !isEmpty( studentHeadPtr ) && !studentHeadPtr->current )    
    {          
    // variables
    StudentType *wkgPtr;
  
    // set wkg pointer to the head
    wkgPtr = studentHeadPtr;
    
    // iterate through until wkg pointers next poiter is 
    //current and not hitting the end
    while( wkgPtr != NULL && !wkgPtr->nextPtr->current )
      {
      // move wkgPtr over to the next ptr
      wkgPtr = wkgPtr->nextPtr;   
      }
    
    // not we have the node prior to the current node
    // return the node
    return wkgPtr;      
    }
      
  return NULL;    
  }

/*
Name: getValueAtCurrent
Process: if data is available, returns the value at the current location 
         in the iterator linked list,
         if data not available, returns StudentType value
         with dummy/empty struct
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: student item to load and return(StudentType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: getPtrBeforeCurrent, copyStudentData, setEmptyStudentData
*/
void getValueAtCurrent( StudentType *resultStructHolder, 
                                                  StudentType *studentHeadPtr )
  {     
  // check if data is avaliable
  if( !isEmpty( studentHeadPtr ) )
    {
    // variables
    StudentType *wkgPtr;    
        
    // set the working pointer to the head pointer
    wkgPtr = studentHeadPtr;
    
    // iterate until wkgPtr is at the current
    while( !wkgPtr->current )
      {
      // move to next node
      wkgPtr = wkgPtr->nextPtr;        
      }
        
    // once at the current return the node
    copyStudentData( resultStructHolder, *wkgPtr );        
    }   
      
  // data is not avaliable
  // set the dummy/ empty struct
  setEmptyStudentData( resultStructHolder );  
  }

/*
Name: hasNext
Process: reports if current node is not at the last element location,
         also returns false if list is empty
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: Boolean result of test
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool hasNext( StudentType *studentHeadPtr )
  {
  // check is list is not empty and if not at end of list
  return !isEmpty( studentHeadPtr ) && studentHeadPtr->nextPtr != NULL;        
  }

/*
Name: hasPrev
Process: reports if current location is not at the first element location,
         also returns false if list is empty, one line of code
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: Boolean result of test
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool hasPrev( StudentType *studentHeadPtr ) 
  {
  // check if list is not empty and not at first node
  return !isEmpty( studentHeadPtr ) && !studentHeadPtr->current;    
  }

/*
Name: initializeIterator
Process: initializes iterator by returning NULL to head pointer
         assigned to the function
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
StudentType *initializeIterator()
  {
  // return the headPtr that has NULL
  return NULL;    
  }

/*
Name: insertAtCurrent
Process: inserts value at current location,
         maintains current location where new value was inserted,
         if list was empty, sets new node to current
Function input/parameters: Iterator linked list head pointer (StudentType *),
                           new student to insert (StudentType)
Function output/parameters: none
Function output/returned: pointer to possibly updated head pointer 
                          (StudentType *)
Device input/file: none
Device output/monitor: none
Dependencies: createStudentNodeFromStruct, getPtrBeforeCurrent
*/
StudentType *insertAtCurrent( StudentType *studentHeadPtr,
                                                       StudentType newStudent )
  {
  // variables
  StudentType *wkgPtr, *tempPtr;
    
  // point the the node before current
  wkgPtr = getPtrBeforeCurrent( studentHeadPtr );
    
  // break the LL into to
  tempPtr = wkgPtr->nextPtr;
    
  // set old current to false
  tempPtr->current = false;
    
  // add value to nex pointer of wkgPtr
  wkgPtr->nextPtr = createStudentNodeFromStruct( newStudent );   
    
  // check if list was empty
  if( isEmpty( studentHeadPtr ) )  
    {
    // set the current to new node
    wkgPtr->current = true;
    } 
  
  else
    {
    // set the current to the next node
    wkgPtr->nextPtr->current = true;
    }  
  
  // increment wkgPtr
  wkgPtr = wkgPtr->nextPtr; 
    
  // reconnect the link list back to the temp
  wkgPtr->nextPtr = tempPtr;   
       
  return studentHeadPtr;    
  }

/*
Name: insertAtEnd
Process: inserts value at end of list,
         if list empty, set node to current, 
         otherwise, no change to current location
Function input/parameters: Iterator linked list head pointer (StudentType *),
                           new student data (StudentType)
Function output/parameters: none
Function output/returned: pointer to possibly updated head pointer 
                          (StudentType *)
Device input/file: none
Device output/monitor: none
Dependencies: createStudentNodeFromStruct
*/
StudentType *insertAtEnd( StudentType *studentHeadPtr, 
                                                       StudentType newStudent )
  { 
  // variables
  StudentType *wkgPtr;
    
  // set the wkgPtr to headPtr
  wkgPtr = studentHeadPtr;
    
  // check if list is not empty
  if( !isEmpty( studentHeadPtr ) )
    {
    // iterate through till next ptr is NULL
    while( wkgPtr->nextPtr != NULL )
      {
      // increment the wkgPtr
      wkgPtr = wkgPtr->nextPtr;       
      }
    }
    
  else
    {
    // else set the new node to current
    wkgPtr->nextPtr->current = true;  
    }
    
  // once at end. Create new node at end
  wkgPtr->nextPtr = createStudentNodeFromStruct( newStudent );
    
  // set NULL at end
  wkgPtr->nextPtr->nextPtr = NULL;

  // return updated headPtr
  return studentHeadPtr;        
  }

/*
Name: insertAtFront
Process: inserts value at front of list,
         if list empty, set node to current, 
         otherwise, no change to current location
Function input/parameters: Iterator linked list head pointer (StudentType *),
                           new student to insert (StudentType)
Function output/parameters: none
Function output/returned: possibly updated head pointer (StudentType *)
Device input/file: none
Device output/monitor: none
Dependencies: createStudentNodeFromStruct
*/
StudentType *insertAtFront( StudentType *studentHeadPtr, 
                                                       StudentType newStudent )
  {
  // variables
  StudentType *wkgPtr;
    
  // set the wkgPtr
  wkgPtr = studentHeadPtr;
    
  // set new node at head
  studentHeadPtr = createStudentNodeFromStruct( newStudent );
  
  // check if data is avaliable
  if( isEmpty( wkgPtr ) )
    {
    // set new node to current
    studentHeadPtr->current = true;			
    } 	
     
  // reconnect LL
  studentHeadPtr->nextPtr = wkgPtr;
          
  // return headPtr
  return studentHeadPtr;
  }

/*
Name: isEmpty
Process: checks for iterator linked list empty, if it is, returns true,
         otherwise returns false, one line of code
Function input/parameters: Iterator linked list head pointer data 
                           (StudentType *)
Function output/parameters: none
Function output/returned: Boolean result of test
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
bool isEmpty( const StudentType *studentHeadPtr )
  {
  // check if the head is NULL
  return studentHeadPtr == NULL;        
  }

/*
Name: moveNext
Process: moves current node to the next location in the list
         if possible (aka moveRight)
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: Boolean result of test
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool moveNext( StudentType *studentHeadPtr )
  {
  // variables
  StudentType *wkgPtr;    
  
  // set wkgPtr to current
  wkgPtr = getPtrBeforeCurrent( studentHeadPtr );
  wkgPtr = wkgPtr->nextPtr;
    
  // check if it has valid next location
  if( hasNext(wkgPtr) )
    {
    // set wkgPtr current to false
    wkgPtr->current = false;
    
    // increment wkgPtr
    wkgPtr = wkgPtr->nextPtr;
    
    // set the new current
    wkgPtr->current = true;
    
    // return sucess
    return true;        
    }
      
  // else return failure
  return false;     
  }

/*
Name: movePrev
Process: moves iterator to the previous location in the list
         if possible (aka moveLeft)
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: none
Function output/returned: Boolean result of test
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool movePrev( StudentType *studentHeadPtr ) 
  {
  // variables
  StudentType *wkgPtr;
  
  // if the current is at the head or empty
  if( !hasPrev( studentHeadPtr ) )
    {
    // cant go back so return false
    return false;        
    }
  
  // iterate until hitting current before current
  wkgPtr = getPtrBeforeCurrent( studentHeadPtr ); 
    
  // set wkgPtr to true
  wkgPtr->current = true;
  
  // increment Ptr
  wkgPtr = wkgPtr->nextPtr;
  
  // set old current to false
  wkgPtr->current = false;
  
  // return sucess
  return true;
      
  }

/*
Name: printIteratorChars
Process: recursively prints a specified number of characters
Function input/parameters: number of characters (int),
                           character to be printed (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf, printIteratorChars (recursive)
*/
void printIteratorChars( int numChars, char outChar )
  {
  // check if we are out of values
  if( numChars > 0 )
    {
    // print the character
    printf( "%c", outChar );
    
    // recursivly call back
    printIteratorChars( numChars - 1, outChar );       
    }       
  }

/*
Name: removeAtCurrent
Process: removes current value if data is available, returns the value
         if data not available, returns StudentType value
         with dummy/empty struct
Function input/parameters: Iterator linked list head pointer 
                           (StudentType *)
Function output/parameters: pointer to removed student (StudentType *)
Function output/returned: pointer to possibly updated linked list head
Device input/file: none
Device output/monitor: none
Dependencies: getPtrBeforeCurrent, copyStudentData, free
*/
StudentType *removeAtCurrent( StudentType *resultStructHolder, 
                                                  StudentType *studentHeadPtr )
  {
  // check if data is avaliable
  if( !isEmpty( studentHeadPtr ) )
    {
    // variables
    StudentType *wkgPtr, *tempPtr;
  
    // set the wkg pointer
    wkgPtr = studentHeadPtr;
  
    // check if current is at the head
    if( wkgPtr->current )
      {
      // set temp to wkg 
      tempPtr = wkgPtr;
      
      // increment the wkgPtr
      wkgPtr = wkgPtr->nextPtr;
      
      // set the studentHeadPtr to the wkgPtr
      studentHeadPtr = wkgPtr;
      
      // set new current
      studentHeadPtr->current = true;
      }
  
    // else assume its somewhere in bewtween front and end
    else
      {
      // find the ptr before current
      wkgPtr = getPtrBeforeCurrent( studentHeadPtr );
    
      // set the temp to the current
      tempPtr = wkgPtr->nextPtr;
    
      // unlink the current and reconnect LL
      wkgPtr->nextPtr = tempPtr->nextPtr;
          
      // check if at end
      if( wkgPtr->nextPtr == NULL )
        {
        // set current to wkgPtr    
        wkgPtr->current = true;
        }  
    
      else
        {
        // else put current at next val
        wkgPtr->nextPtr->current = true;
        } 
       
      }
      
    // copy node into the result
    copyStudentData( resultStructHolder, *tempPtr );
      
    // free the temp
    free( tempPtr );
     
    // retrn iterator
    return studentHeadPtr;  
    }
  
  // set the return struct holer as empty  
  setEmptyStudentData( resultStructHolder );

  // return back iterator
  return studentHeadPtr;
  }

/*
Name: setEmptyStudentData
Process: sets student node to empty data, one line of code
Function input/parameters: 
Function output/parameters: pointer to student data holder (StudentType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: setStudentData
*/
void setEmptyStudentData( StudentType *studentDataHolder )
  {
  // set the student data to empty
  setStudentData( studentDataHolder, "", 0, 'x', 0 );       
  }

/*
Name: setStudentData
Process: sets student data to a StudentType struct,
         sets current Boolean to false, and nextPtr to NULL
Function input/parameters: student data: name (const char *),
                                         student id (int),
                                         gender (char),
                                         gpa (double)
Function output/parameters: updated student data (StudentType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: copyIteratorString
*/
void setStudentData( StudentType *studentDataHolder, 
                     const char *name, int studentId, char gender, double gpa )
  {		
  // set the studentId, gender, and gpa
  studentDataHolder->studentId = studentId;
  studentDataHolder->gender = gender;
  studentDataHolder->gpa = gpa;
  
  // copy the name
  copyIteratorString( studentDataHolder->name, name);      
  }

/*
Name: setToFirst
Process: if data is available, sets current location to first element location,
         returns true, otherwise returns false
Function input/parameters: Iterator linked list head pointer (StudentType *)
Function output/parameters: possibly updated Iterator linked list head pointer 
                            (StudentType *)
Function output/returned: Boolean result of operation
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool setToFirst( StudentType *studentHeadPtr )
  {
  // check if data is avaliable
  if( !isEmpty( studentHeadPtr ) )
    {
    // variables
    StudentType *wkgPtr;
    
    // set the wkgPtr to the head
    wkgPtr = studentHeadPtr;
    
    // set the wkgPtr current to true
    wkgPtr->current = true;
    
    // increment the wkgIndex
    wkgPtr = wkgPtr->nextPtr;
    
    // iterate through to the end
    while(wkgPtr != NULL)
      {
      // set the current to false
      wkgPtr->current = false;
      
      // increment wkgPtr
      wkgPtr = wkgPtr->nextPtr;       
      }
        
    return true;
    }    
    
  return false;    
  }

/*
Name: setToLast
Process: if data is available, sets current location to last element location,
         returns true, otherwise returns false  
Function input/parameters: Iterator linked list head pointer (StudentType *)
Function output/parameters: possibly updated iterator linked list head pointer 
                            (StudentType *)
Function output/returned: Boolean result of operation
Device input/file: none
Device output/monitor: none
Dependencies: variable options
*/
bool setToLast( StudentType *studentHeadPtr )
  {
  // check if data is abaliable
  if( !isEmpty( studentHeadPtr ) )
    {    
    // variables
    StudentType *wkgPtr;
    
    // set the wkgPtr to headPtr    
    wkgPtr = studentHeadPtr;
        
    // loop until next pointer is NULL   
    while( wkgPtr->nextPtr != NULL )
      {
      // set the current to false
      wkgPtr->current = false;
      
      // increment wkgPtr
      wkgPtr = wkgPtr->nextPtr;
      }
      
    // now that we are at last value set it to true
    wkgPtr->current = true;
    
    // return sucess
    return true;    
    }
  // otherwise
  return false;    
  }

