//Vidya Jayaraman 
// vijayara
// 12B
// February 26, 2018
//Queue implements QueueInterface

public class Queue implements QueueInterface{

   //private inner Node class
   private class Node{
	   Object item;
	   Node next;

	   Node(Object item) {
		   this.item = item;
		   next = null;
		}
	}

   // Fields
   private int numItems;       
   private Node head;			
   private Node tail;			

   //Queue constructor
   Queue() {
	   head = null;
	   tail = null;
	   numItems = 0;
	}
 
   //returns true if this Queue is empty, false otherwise
   public boolean isEmpty(){
	   return(numItems == 0);
   }

   //returns the length of this Queue.
   public int length(){
	   return numItems;
   }

   // adds newItem to back of this Queue
   public void enqueue(Object newItem){
	   if(head != null){
		   Node N = head;
		   while(N.next != null){
			N = N.next;
		   }
		   N.next = new Node(newItem);
	           tail   = N.next;
		   numItems++;
	   }else{
		   head = new Node(newItem);
		   numItems++;
	   }
   }

   // deletes and returns item from front of this Queue
   public Object dequeue() throws QueueEmptyException{
	   if(head==null){
		   throw new QueueEmptyException("unable to dequeue empty queue");
	   }else{
		Node N = head;
                head = N.next;
           	numItems--;
           	return N.item;
	   }
   }

   // returns item at front of Queue
   public Object peek() throws QueueEmptyException{
	   if(isEmpty()){
		   throw new QueueEmptyException("unable to peek() empty queue");
	   }
	   return head.item;
   }

  
   // sets this Queue to the empty state
   public void dequeueAll() throws QueueEmptyException{
	   if(numItems==0){
		   throw new QueueEmptyException("unable to dequeueAll() empty queue");
	   }
	   numItems = 0;
	   head = null;
	   tail = null;
   }

   // overrides Object's toString() method
   public String toString(){
	   String s = "";
	   Node N = head;
       while(N != null){
		   s +=  N.item + " ";
		   N = N.next;
	   }
	   return s;
   }
}
