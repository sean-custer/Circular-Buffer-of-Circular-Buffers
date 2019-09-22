//file: InnerCB.cpp
//name: Sean Custer
//email: sea4@umbc.edu
//date: 9/14/18
//description: source code for Inner Circular Buffer

#include "InnerCB.h"
#include <iostream>
using namespace std;

InnerCB::InnerCB(int n){

  m_buffer = new int[n];
  m_capacity = n;
  m_size = 0;
  m_start = -1;
  m_end = -1;
}

InnerCB::InnerCB(const InnerCB& other){
  m_capacity = other.m_capacity;
  m_buffer = new int[m_capacity];

  for(int i = 0; i < m_capacity; i++){
    m_buffer[i] = other.m_buffer[i];
  }

  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;

}

InnerCB::~InnerCB(){
  delete [] m_buffer;
  m_buffer = NULL;
}

void InnerCB::enqueue(int data){
  //if queue is empty
  if(m_size == 0){
    m_buffer[0] = data;
    m_start = 0;
    m_end = 0;
    m_size++;
    
  }

  //if queue isn't empty
  else if(m_size != 0){

    //if queue is full
    if(this->isFull() == true){
      throw overflow_error("InnerCB is full!");
      return;
    }
    //circular case
    else if(m_end == (m_capacity - 1) && m_start != 0){   
      m_end = 0;
      m_buffer[0] = data;
      m_size++;
    }
    //regular enqueue
    else{
      m_end++;
      m_buffer[m_end] = data;
      m_size++;
    }
  }
}

int InnerCB::dequeue(){
  //if queue is empty
  if(this->isEmpty() == true){
    throw "InnerCB is empty!";
  }
  
  //if wrapping around, m_start is now at the beginning of queue
  else if(m_start == m_capacity -1){
    int temp = m_buffer[m_start];
    m_start = 0;
    m_size--;
    return temp;
  }
  //regular dequeue
  else{
    int temp = m_buffer[m_start];
    m_start++;
    m_size--;
    return temp;
  }
}

bool InnerCB::isFull(){
  if( m_size == m_capacity)
    return true;
  return false;      
}

bool InnerCB::isEmpty(){

  if(m_size == 0)
    return true;
  return false;
}

int InnerCB::capacity(){
  return m_capacity;
}

int InnerCB::size(){
  return m_size;
}

const InnerCB& InnerCB::operator=(const InnerCB& rhs){

  //check for self assignment
  if(this != &rhs){
    delete [] m_buffer;
    m_buffer = NULL;
    m_buffer = new int [rhs.m_capacity];
    
    m_start = rhs.m_start;
    m_end = rhs.m_end;
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;

    //copy m_buffer
    for(int i = 0; i < m_capacity; i++){
      m_buffer[i] = rhs.m_buffer[i];
    }
  }
    return *this;
}

void InnerCB::dump(){
  //standard print through queue
  if(m_start <= m_end ){
    for(int i = m_start; i<= m_end; i++){
      cout << m_buffer[i] << endl;
    }
  }
  //if m_end < m_start, meaning that the queue has wrapped around
  else{
    //print out from m_start to end
    for(int i = m_start; i< m_capacity; i++){
      cout << m_buffer[i] << endl;
    }
    //print out the remaining data from beginning to m_end
    for(int i = 0; i < (m_end + 1); i++){
      cout << m_buffer[i] << endl;
    }
  }
}



