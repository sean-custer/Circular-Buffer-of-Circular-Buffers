# Circular-Buffer-of-Circular-Buffers
Based on the idea of First in First Out (FIFO) Queues, this Data structure is made up of a Queue of Queues. Upon adding elements to the queue, once it exceeds it's capacity, another Queue is allocated. All of these Queues are indexed by pointers in an outer circular Queue/Buffer, that only stores the data and circulates back around.
