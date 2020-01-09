#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>

#include "sort.h"
#include "edgelist.h"

// Order edges by id of a source vertex, 
// using the Counting Sort
// Complexity: O(E + V)
void countSortEdgesBySource(struct Edge *edges_sorted, struct Edge *edges, int numVertices, int numEdges) {

    
    int i;
    int key;
    int pos;

    // auxiliary arrays, allocated at the start up of the program
    int *vertex_cnt = (int*)malloc(numVertices*sizeof(int)); // needed for Counting Sort

    for(i = 0; i < numVertices; ++i) {
        vertex_cnt[i] = 0;
    }

    // count occurrence of key: id of a source vertex
    for(i = 0; i < numEdges; ++i) {
        key = edges[i].src;
        vertex_cnt[key]++;
    }

    // transform to cumulative sum
    for(i = 1; i < numVertices; ++i) {
        vertex_cnt[i] += vertex_cnt[i - 1];
    }

    // fill-in the sorted array of edges
    for(i = numEdges - 1; i >= 0; --i) {
        key = edges[i].src;
        pos = vertex_cnt[key] - 1;
        edges_sorted[pos] = edges[i];
        vertex_cnt[key]--;
    }


    free(vertex_cnt);

}


void radixSortEdgesBySource(struct Edge *edges_sorted, struct Edge *edges, int numVertices, int numEdges)
{

	omp_set_dynamic(0);
	int max_digits=0;
	int temp = 0,t;
	int pos, key;
	int t_id,t_stop;
	int i,j,k,t_start;
	int ** digits_count;
	int num_of_threads=2;

	int *b = malloc(numEdges*sizeof(int));
	for(i=0;i<numEdges;i++)
	{
		b[i]=0;
	}

	digits_count=malloc(num_of_threads*sizeof(int*));
	for(i=0;i<num_of_threads;i++)
	{
		digits_count[i] = malloc(num_of_threads*sizeof(int));
	}

	// The max number in the array
	#pragma omp parallel default(none) shared (temp,edges,numEdges,num_of_threads) private (i,t_id,t_start,t_stop) num_threads(num_of_threads)
	{
		t_id=omp_get_thread_num();
		t_start=t_id*numEdges/num_of_threads;
		t_stop=(t_id+1)*numEdges/num_of_threads;
			if(numEdges-t_stop<numEdges/num_of_threads)
				t_stop=numEdges;
		temp=edges[0].src;
		for(i=t_start;i<t_stop;i++)
		{
			if(temp<edges[i].src)
				temp=edges[i].src;
		}
	}
	
		
	max_digits=0;
	while(temp>0)
	{
		max_digits++;
		temp=temp/10;
	}
 	
		
	for(i=1;i<=max_digits;i++)
	{
		// Initializing the count loop
		for(k=0;k<num_of_threads;k++)
		for(j=0;j<10;j++)
			{
				digits_count[k][j]=0;
			}
		
		// counting the number of digits.	
		#pragma omp parallel default(none) shared(edges, numEdges,digits_count,i,num_of_threads) private(j,temp, t_id,t,t_stop) num_threads(num_of_threads)
		{	
			t_id=omp_get_thread_num();
			j=(omp_get_thread_num())*numEdges/num_of_threads;
			
			t_stop=(omp_get_thread_num()+1)*numEdges/num_of_threads;
			
			if((numEdges-t_stop)<numEdges/num_of_threads)
				t_stop=numEdges;
				
			
						 
			for(;j<t_stop;j++)
			{
				t=edges[j].src;
				for(k=1;k<=i;k++)
				{	
					temp=t%10;
					t=t/10;
				}
				digits_count[t_id][temp]++;
				
			
			}
		
		
		}
		
		// Sequential part of the code. To add all the elements to gether
				
		int sum=0;
		
		for(j=0;j<10;j++)
		for(k=0;k<num_of_threads;k++)
		{
			digits_count[k][j]+=sum;
			sum=digits_count[k][j];
		}
		
		// Assigning the correct position to all the elements

		#pragma omp parallel default(none) shared(edges,edges_sorted,digits_count,i,num_of_threads,numEdges) private(j,t,k,key,pos,t_id,t_stop,t_start) num_threads(num_of_threads) 
		{
			t_id=omp_get_thread_num();
			t_start=(t_id)*numEdges/num_of_threads;
			t_stop=(t_id+1)*numEdges/num_of_threads;
			if((numEdges-t_stop)<numEdges/num_of_threads)
				t_stop=numEdges;
					
			for( j = t_stop-1; j>=t_start ;j--) 
			{
				t = edges[j].src;
				for(k=1;k<=i;k++)
				{	
					key=t%10;
        			t=t/10;
				
				}
        		pos = digits_count[t_id][key]-1;
        		edges_sorted[pos] = edges[j];
        		digits_count[t_id][key]--;
        	
        	}
		
		}
			
		//reassigning the sorted array to the original array	
		#pragma omp parallel default(none) shared(edges,edges_sorted,num_of_threads,numEdges) private(k,t_start,t_stop,t_id) num_threads(num_of_threads)
		{
			t_id=omp_get_thread_num();
			t_start=(t_id)*numEdges/num_of_threads;
			t_stop=(t_id+1)*numEdges/num_of_threads;
			if((numEdges-t_stop)<numEdges/num_of_threads)
				t_stop=numEdges;
			for(k=t_start;k<t_stop;k++)
        	{
        		edges[k]=edges_sorted[k];
        		
			}
		}
	
	}
		

}
