# Radix Sort using OpenMP

Consider numbers with a maximum of 'n' digits. Radix sort sorts these numbers digit by digit. We use a stable sorting algorithm to sort these numbers in the first place. The stable sorting algorithm that we use is called count sort which counts the number of a particular occurance of a digit and then based on the that we place the number based on this count. 

More details about counting sort can be found [here]. 

We split the array of the numbers that we want to split into 'm', where m stands for the number of threads the program is gonna use. 

In this particular 
  
  
  
  
  
  [here]: https://www.geeksforgeeks.org/counting-sort/
