//file: CBofCB.cpp
//author: Sean Custer
//date: 9/14/18
//email: sea4@umbc.edu
//description: source code for circular buffer of circular buffers

#include "CBofCB.h"
#include <iostream>
using namespace std;

CBofCB::CBofCB(){
  m_oldest = 0;
  m_newest = 0;
  m_buffers[0] = new InnerCB();
  m_obSize = 1;
}

CBofCB::CBofCB(const CBofCB& other){
  m_obSize = other.m_obSize;
  m_oldest = other.m_oldest;
  m_newest = other.m_newest;
  
  //copy m_buffers using innerCB copy constructor
  //regular case
  if(m_obSize != 0){
    for(int i = m_oldest; i<=m_newest; i++){
      int index = i%m_obCapacity;
      this->m_buffers[index] = new InnerCB(*other.m_buffers[index]);
    }
  }
}

CBofCB::~CBofCB(){
  for(int i=0; i<m_obSize; i++){
    delete m_buffers[i];
  }
}

void CBofCB::enqueue(int data){
  //Enqueueing to an empty buffer
  if(isEmpty() == true){
    m_buffers[m_newest]->enqueue(data);
  }

  //if outer circular buffer is full, throw exception
  else if(this->isFull() == true){
    throw overflow_error("Outer Circular Buffer is full.");
  }

  //if m_newest InnerCB is full, create a new InnerCB with double capacity
  else if(m_buffers[m_newest]->isFull() && m_newest != m_obCapacity -1){
    int n = m_buffers[m_newest]->capacity() * 2;
    m_newest++;
    m_obSize++;
    m_buffers[m_newest] = new InnerCB(n);
    m_buffers[m_newest]->enqueue(data);
  }

  //wrap around case
  else if(m_newest == m_obCapacity-1 && m_buffers[m_newest]->isFull() == true
	  &&  m_oldest != 0){
    int n = m_buffers[m_newest]->capacity() * 2;
    //reset m_newest to beginning of queue
    m_newest = 0;
    m_obSize++;
    m_buffers[m_newest] = new InnerCB(n);
    m_buffers[m_newest]->enqueue(data);

  }
  //regular enqueue
  else{
    m_buffers[m_newest]->enqueue(data);
  }
}

int CBofCB::dequeue(){

  int popNum;
  
  //if entire data structure is empty
  if(isEmpty()){
    throw underflow_error("CBofCB is empty!");
  }
  //if dequeueing from an empty innerCB that isnt the first one
  else if(m_obSize != 1 and (m_buffers[m_oldest]->size() == 1)
	  and m_oldest != m_obCapacity - 1){
    popNum = m_buffers[m_oldest]->dequeue();
    delete m_buffers[m_oldest];
    m_oldest++;
    m_obSize--;
    return popNum;
  }
  //wrap around for dequeue
  else if(m_oldest == m_obCapacity - 1 && m_buffers[m_oldest]->size() == 1){
    m_obSize--;
    popNum = m_buffers[m_oldest]->dequeue();
    delete m_buffers[m_oldest];
    m_oldest = 0;
    return popNum;
  }
  //regular dequeue
  else{
    popNum = m_buffers[m_oldest]->dequeue();
    return popNum;
  }
}

bool CBofCB::isFull(){
  if(m_obSize == m_obCapacity){
    if(m_buffers[m_oldest]->isFull() && m_buffers[m_newest]->isFull())
      return true;
  }
  return false;
}

bool CBofCB::isEmpty(){
  if(size() == 0){
    return true;
  }
  return false;

}

int CBofCB::size(){
  int size = 0;
  //iterate through the entire data struct
  for(int i = m_oldest; i <= m_newest; i++){
    int index = i % m_obCapacity;
    size += m_buffers[index]->size();
    }
    
  return size;
}

const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  //check for self assignment
  if(this != &rhs){
    for(int i = 0; i < m_obSize; i++){
      delete m_buffers[i];
      m_buffers[i] = NULL;
    }

    m_obSize = rhs.m_obSize;
    m_oldest = rhs.m_oldest;
    m_newest = rhs.m_newest;
    if(m_obSize != 0){
      ///copy buffers
      for(int i = 0; i == m_obSize; i++){
	m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
	
      }      
    }
  }
  return *this;
}

void CBofCB::dump(){
  
  if(this->isEmpty() == true){
    throw "Error; Queue is empty!";
  }
  //standard print through queue
  else if(m_oldest <= m_newest){
    //if our first ICCB is at the first index, print < m_obSize
    if(m_oldest == 0){
      for(int i = m_oldest; i <= m_newest; i++){
	m_buffers[i]->dump();
      }
    }
    //if our first ICCB is not at our first index, print <= m_obSize
    else{
      for(int i = m_oldest; i < m_obCapacity; i++){
	
	m_buffers[i]->dump();
      }      
    }
  }
  //if queue wraps around
  else{
    //print out from start to end
    for(int i = m_oldest; i<m_obCapacity; i++){
      m_buffers[i]->dump();
    }
    for(int i = m_newest; i<m_oldest; i++){
      m_buffers[i]->dump();
    }
  }
}
