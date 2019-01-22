//Vidya Jayaraman 
//vijayara
//12B 
//February 6, 2018
//DictionaryTest.java tests Dictionary.java
class DictionaryTest {
	public static void main(String[] args) {
		String value;
		Dictionary D = new Dictionary();
		//inserts pair in linked list
		D.insert("1", "a");
		D.insert("2", "b");
		D.insert("3", "c");
		D.insert("4", "d");
		D.insert("5", "e");
		D.insert("6", "f");
		D.insert("7", "g");
		//prints out linked list
		System.out.println(D.toString());
		//prints out the key with the value, if the value is found
		value = D.lookup("1");
		System.out.println("key=1 ");
		if(value==null)
		    System.out.println("not found");
		else
		    System.out.println("value="+value);

		value = D.lookup("3");
		System.out.println("key=3 ");
		if(value==null) 
		    System.out.println("not found");
		else 
		    System.out.println("value="+value); 

		value = D.lookup("7");
		System.out.println("key=7 ");
		if(value==null) 
		    System.out.println("not found");
		else 
		    System.out.println("value="+value);

		value = D.lookup("8");
		System.out.println("key=8 ");
		if(value==null)
		    System.out.println("not found");
		else 
		    System.out.println("value="+value);
		System.out.println();
		//deletes the key from the list
		D.delete("1");
		D.delete("3");
		D.delete("7");
		System.out.println(D.toString());

		//returns true if the list is empty
		System.out.println(D.isEmpty());
		//prints out the size of the list
		System.out.println(D.size());
		//makes the list empty
		D.makeEmpty();
		System.out.println(D.isEmpty());
              
	}
}


