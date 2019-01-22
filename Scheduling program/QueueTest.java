// Vidya Jayaraman 
// vijayara
// 12B
// 2/22/18
// QueueTest.java tests Queue.java
public class QueueTest {

	public static void main(String[] args){
		//create a new Queue 
		Queue A = new Queue();
     		//if the Queue is empty, return true
		System.out.println(A.isEmpty());
		//add integers and strings to the Queue 
		A.enqueue((int)5);
      		A.enqueue("two"); 
		A.enqueue((int)7); 
		A.enqueue("five"); 
		A.enqueue((int)8);
      		//print out the Queue
		System.out.println(A.toString());
		//print out the length of the Queue 
	  	System.out.println(A.length());
      		//take out the first two items added to the Queue 
		A.dequeue(); 
		A.dequeue();
      		
		System.out.println(A.toString());
      		System.out.println(A.length());
      		
		System.out.println(A.isEmpty());
      		
		A.enqueue((int)8); 
      		A.enqueue("twelve");
	
		Queue V = new Queue();
		
		V.enqueue((int)7);
		V.enqueue("nine");
     	 	
		System.out.println(A.toString());
      		System.out.println(V.toString());
      		//delete all the items in the Queue, V
		V.dequeueAll();
      		System.out.println(V.toString());
		//return, but do not remove the first item in the Queue, A
		System.out.println(A.peek());
		System.out.println(A.isEmpty());
   }
}
