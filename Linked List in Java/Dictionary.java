//Vidya Jayaraman 
//vijayara
//12B
//February 6, 2018
//Dictionary.java implements the linked list data structure with the elements in pairs (key, value). There are 7 ADT operations that are also implemented 


public class Dictionary implements DictionaryInterface {
	//define Node class with two String fields 
	private class Node{
		String key;
		String value;
		Node next; 

		Node (String key, String value) {
			this.key = key;
			this.value = value;
			next = null; 
		}
	}
	//define private variables
	private Node head; 
	private int numList;
	//initialize variables 
	public Dictionary() {
		head = null;
		numList = 0;
	}

        //returns reference to the Node containing its argument key, or returns null, if no Node exists
	private Node findKey(String key){
		Node N = head; 
		while(N != null) {
			if(N.key ==key) 
				return N; 
			else 
				N = N.next;	
		}
		return null; 
	}
        //returns true, if the Dictionary contains no pairs, false otherwise
	public boolean isEmpty() {
		return(numList == 0);
	}
	//returns the number of (key, value) pairs in the Dictionary
	public int size() {
		return numList;
	}
	//if pair matches the argument key, lookup returns associated value field
	public String lookup(String key) {
		Node N = findKey(key);

		while (N != null) {
			if (N.key.equals(key)) 
				return N.value;
			N = N.next;
		}
		//otherwise null is returned 
		return null;
	}
	//adds a pair into the linked list, if it hasn't already been added in 
	public void insert(String key, String value) throws DuplicateKeyException {
		//exception if it already contains it 
		if(lookup(key)!=null) {
			throw new DuplicateKeyException("cannot insert duplicate keys");
		} else {
			if(head != null) {
				Node N = head;
				while(N != null){
				       if(N.next == null) {
					        break;
					}
						N = N.next;
					}
					N.next = new Node(key, value);
				}
			else {
				Node N = new Node(key, value);
				head = N;
			}
				numList++;
			}
		}


	
        //removes the pair in the linked list, if it exists  
	public void delete(String key) throws KeyNotFoundException {
		//if it doesn't exist, throws an exception 
		if(lookup(key) == null){
			throw new KeyNotFoundException("cannot delete non-existent key");
		}else{
			if(numList == 1) {
				Node N = head; 
				head = head.next;
				N.next = null;

			}else{
				Node N = head;
				if(N.key.equals(key)){
					head = N.next;

				}else{
					while(!N.next.key.equals(key)){
						N = N.next;
					}
					N.next = N.next.next;

				}
			}
			numList--;
		}
	}

        //resets the Dictionary to the empty state
	public void makeEmpty() {
		head = null; 
		numList = 0;
	}
        //returns String representation of the Dictionary
	public String toString() {
		String s= ""; 
		Node N = head; 
		while(N != null) {
			s += N.key + " " + N.value + "\n";
			N = N.next;
		}
		return s;
	}
}

