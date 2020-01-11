# Radix Sort using OpenMP

Consider numbers with a maximum of 'n' digits. Radix sort sorts these numbers digit by digit. We use a stable sorting algorithm to sort these numbers in the first place. The stable sorting algorithm that we use is called count sort which counts the number of a particular occurance of a digit and then based on the that we place the number based on this count. 

More details about counting sort can be found [here]. 

We split the array of the numbers to be sorted into 'm', where m stands for the number of threads the program is gonna use. We traverse the array from (i x m) to (i x (m+1)) in a thread and sort the elements using count sort. The 'i' refers to the thread number and  'm' stands for the number of threads initialized in the program. 

We go on sorting the array based on every individual digits. This type of sorting is really helpful when the number of elements to be sorted is of the order of few thousands. 

The trace file for this particular program contains information in the following format. 

                                        ' Source node ' ' Destination node'
In this program we try to sort the elements that form the edge of a graph. We are basically sorting the edges of a huge graph to make sure that we end up reducing the time taken for breadth wise search for a node. 

More details about this is provided in the spec document. 

## Usage
  
I have attached a make file, running the make file would attach the required flags to gcc to make sure that openMP part is compiled without any errors. Running the " make run " command would compile the code, create an executable and run the code. 

On a windows machine, make sure that you enable the right flags. 


  
  
  I will not be able to upload any 
  [here]: https://www.geeksforgeeks.org/counting-sort/
