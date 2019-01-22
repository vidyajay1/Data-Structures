
//Vidya Jayaraman 
//vijayara
//12B
//February 26, 2018
//Simulation.java calculates the job processing, using the pseudo code in the StimulationStub. It calculates the wait time, average time, and total time as well as the finish and arrival time of each of the jobs from the Queue  

import java.io.*;
import java.util.Scanner;

public class Simulation{

//-----------------------------------------------------------------------------
//
// The following function may be of use in assembling the initial backup and/or
// storage queues.  You may use it as is, alter it as you see fit, or delete it
// altogether.
//
//-----------------------------------------------------------------------------

   public static Job getJob(Scanner in) {
      String[] s = in.nextLine().split(" ");
      int a = Integer.parseInt(s[0]);
      int d = Integer.parseInt(s[1]);
      return new Job(a, d);
   }
   public static void main(String[] args) throws IOException{
	   //declare variables needed for later 
	   Scanner in;
       PrintWriter report;
       PrintWriter trace;
       Queue myQueue  = new Queue();
       Queue myQueue2 = new Queue();   
       
       // check command line arguments
       // if no input file is specified 
       if ( args.length != 1 ){
	   System.err.println("Usage: Simulation <input_file>");
	   System.exit(1);
       }

       
       // opens files for reading and writing 
       try{
	   in = new Scanner(new File(args[0]));
       }
       catch(IOException e){
	   // if file fails to open 
	   throw new IOException("Unable to open specified input file");
       }

       // make output files
       try{
	   report = new PrintWriter(new FileWriter(args[0]+".rpt"));
	   trace  = new PrintWriter(new FileWriter(args[0]+".trc"));
       }
       catch(IOException e){
	   // if output files are failing to be created 
	   throw new IOException("Unable to create files");
       }
       //declare variable m for runnng in m jobs from input file
       int m = in.nextInt();
       
       in.nextLine();
       
       
       for (int i = 0; i < m; i++){
	   Job j = new Job(in.nextInt(), in.nextInt());
	   myQueue.enqueue(j);
	   myQueue2.enqueue(j);
       }
       //print out report and trace files 
          trace.println("Trace file: "+args[0]+".trc");
          trace.println(m+" Jobs:");
          trace.println(myQueue2.toString());
          trace.println();

        
          report.println("Report file: "+args[0]+".rpt");
          report.println(m+" Jobs:");
          report.println(myQueue2.toString());
          report.println();
          report.println("***********************************************************");
       

       // run simulation with n processors for n=1 to n=m-1  
       for(int n = 1; n < m; n++){

	  //processors in trace file 
    	   trace.println("*****************************");
    	   if ( n == 1 ){
    	       trace.println(n+" processor:");
    	   }
    	   else{
    	       trace.println(n+" processors:");
    	   }
    	   trace.println("*****************************");	   

	   // declare the variables for the time of the next arrival or finish event 
	   int wait               = 0;
	   int arrive    = 0;
	   int finish     = 0;

	   // declare jobs counting the time variables
	   int count  = 0;
	   int jobsProcessed = 0;

	   // declare array of n processors
	   Queue[] process = new Queue[n];

	   // initialize n processors array
	   for(int i = 0; i < n; i++){
	       process[i] = new Queue();
	   }
	   
	   //initialize necessary storage Queues 
	   if( myQueue2.isEmpty() ){
	       for(int i = 0; i < m; i++){
		   Job J = (Job) myQueue.dequeue();
		   J.resetFinishTime();
		   myQueue.enqueue(J);
		   myQueue2.enqueue(J);
	       }
	   }

	   // print storage and processor Queues 
	   	    trace.println("time="+wait);
			trace.println("0: "+myQueue2.toString());
			for(int i = 1; i <= process.length ; i++){
			    trace.println(i+": "+process[i-1].toString());
			}
			trace.println();
		 //if job  processed is less than total, check times 
	   while ( count < m ){
		   
	       if( jobsProcessed < m ){
	    	   //determine the time of the next arrival or finish event 
		   finish  = processFinish(process);
		   arrive = processArrival(myQueue2);
		 //complete Job if it finishes now 
		   if( finish < arrive && finish != Job.UNDEF ){
			   //update time 
		       count += completeJobs(trace, process, myQueue2, finish);
		       wait = finish;
		       trace.println("time="+wait);
				trace.println("0: "+myQueue2.toString());
				for(int i = 1; i <= process.length ; i++){
				    trace.println(i+": "+process[i-1].toString());
				}
				trace.println();
		   }
		  
		 //finish finished jobs first, if jobs arrive and finish at same time
		   else if ( finish == arrive ){
		       count += completeJobs(trace, process, myQueue2, finish);
		       jobsProcessed += arrivingProcessor(trace, process, myQueue2, arrive);
		       wait = finish;
		       trace.println("time="+wait);
				trace.println("0: "+myQueue2.toString());
				for(int i = 1; i <= process.length ; i++){
				    trace.println(i+": "+process[i-1].toString());
				}
				trace.println();
		   }
		   //if Job is arriving now, add it to the processor 
		   else if ( finish > arrive || finish == Job.UNDEF ){
		       wait = arrive;
		       jobsProcessed += arrivingProcessor(trace, process, myQueue2, arrive);
		       trace.println("time="+wait);
				trace.println("0: "+myQueue2.toString());
				for(int i = 1; i <= process.length ; i++){
				    trace.println(i+": "+process[i-1].toString());
				}
				trace.println();
		   }
	       
	       }
	       // check finish time for next job
	       else{
	    	  
	    	   finish= processFinish(process);
	    	   count += completeJobs(trace, process, myQueue2, finish);
		   wait = finish;
		     trace.println("time="+wait);
			trace.println("0: "+myQueue2.toString());
			for(int i = 1; i <= process.length ; i++){
			    trace.println(i+": "+process[i-1].toString());
			}
			trace.println();
	       }
	  
	   }
	   		//declare variables for report file 
			int   waitT   = 0;
			int   waitMax     = 0;
			int   numJobs     = myQueue2.length();
			float avgWait = 0;

			//figure out the waitMax 
			for(int i = 0; i < numJobs; i++){
			    Job J = (Job)myQueue2.dequeue();
			    waitT += J.getWaitTime();
			    if( J.getWaitTime() > waitMax ){
				waitMax = J.getWaitTime();
			    }
			}
			//calculate the average wait 
			avgWait = ((float)waitT/m);
			avgWait = (float)Math.round(avgWait*100)/100;
			//print  out the total wait time, the maximum wait time and the average time 
			if( n == 1 ){
			    report.println(n+" processor: totalWait="+waitT+", maxWait="+waitMax+", averageWait="+String.format("%.2f", avgWait));
			}
			else{
			    report.println(n+" processors: totalWait="+waitT+", maxWait="+waitMax+", averageWait="+String.format("%.2f", avgWait));
			}
		    }

     	   in.close();
           report.close();
	   trace.close();
   }

   // adds arriving jobs to arrival to Queues with minimum  length and lowest index 
   private static int arrivingProcessor(PrintWriter trace, Queue[] process, Queue myQueue2, int arrival){
   	int jobsProcessed = 0;	
   	while( true ){
   		//if job's arrival time is not equal to arrival 
   	    if( myQueue2.isEmpty() || ((Job)myQueue2.peek()).getArrival() != arrival ){
   		break;
   	    }
   	    //if it is equal, then take off the Queue 
   	    Job J = (Job)myQueue2.dequeue();
   	    //compute the minimum length and lowest index 
   	    int index = getMinQueue(process);
   	    //update that finish time first if it is empty
   	    if( process[index].isEmpty() ){
   		J.computeFinishTime(arrival);
   	    }
   	    process[index].enqueue(J);

   	    jobsProcessed++;
   	}
   	
   	return jobsProcessed;
       }
   //for the arrival time 
    private static int  processArrival(Queue storageQ){
	return (((Job)storageQ.peek()).getArrival());
    }
    //to finish the jobs that are finished now 
    private static int completeJobs(PrintWriter trace, Queue[] process, Queue myQueue2, int finish){
	int jobCount = 0;
	
	for(int i =0; i < process.length; i++){
		//if processor Queue is empty
	    if ( !process[i].isEmpty() ){
		if ( ((Job)process[i].peek()).getFinish() ==  finish ){
			//remove from the Queue
		    Job J = (Job)process[i].dequeue();
		    jobCount++;
		    myQueue2.enqueue(J);
		    //if processor Queue is not empty
		    if ( !process[i].isEmpty() ){
		    	//compute the Job's finish time 
			((Job)process[i].peek()).computeFinishTime(finish);
		    }
		}
	    }
	}
	
	return (jobCount);
    }
    
   //compute the job's minumum index and length 
    private static int getMinQueue(Queue[] process){
    	//declare variables 
	int minQIndex = -1;
	int minQLength = -1;
	int indexQ = 0;
	boolean found = false;
	
	//if it is not found and the length of it is greater than indexQ 
	while ( !found && indexQ < process.length ){
	    //if indexQ is empty
	    if ( process[indexQ].isEmpty() ){
		minQIndex = indexQ;
		found = true;
	    }
	    //if indexQ is less than the mimimum length
	    else if ( process[indexQ].length() < minQLength ){
		    minQIndex = indexQ;
		    minQLength = process[indexQ].length();
		}
	    else{
		if( minQIndex == -1 ){
		    minQIndex = indexQ;
		    minQLength = process[indexQ].length();
		}
		
	    }
	    indexQ++;
	}

	return (minQIndex);
    }
    //calculates the next finish 
    private static int  processFinish(Queue[] process){
	int finish = Job.UNDEF;
	//find the next job's finish time if myQueue2 is empty
	for(int i = 0; i < process.length; i++){
	    if ( !process[i].isEmpty() ){
		Job J = (Job)process[i].peek();
		if ( finish == Job.UNDEF ){
		    finish = J.getFinish();
		}
		else if ( finish > J.getFinish() ){
		    finish = J.getFinish();
		}
	    }
	}
	
	return (finish);
    }

    
}
