//Hamilton Nguyen 1000538439
// *** command for compiling ***
// gcc test_lab1.c 
// a.out < lab1fall19.a.dat
// a.out < lab1fall19.b.dat
// a.out < lab1fall19.c.dat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100

void ranksByMerge(int a, int b, int tableA[], int tableB[], int yRank[], int zRank[]);
int binarySearch(int arr[], int l, int r, int x);
void interactive();


int main (int argc, char *argv[]) 
{
	interactive();
}

void interactive()
{
	char raw[1000];
	int i=0;
	int j;
	//int d;
	int a, b, c;
	int integer[1000];
	i=0;
	
	scanf("%d %d %d", &a, &b, &c);
	
	int yRank[a];
	int zRank[b];
	int tableA[a+2];
	int tableB[b+2];
	int tablequery[c];
	
	while(fgets(raw, 255, stdin))
	{
		sscanf(raw,"%d",&integer[i]);
		++i;
	}
	
	tableA[0] = -99999999;
	tableB[0] = -99999999;
	
	j =1;
	for(i=1; i<a+1; i++)
	{
		tableA[j] = integer[i];
		++j;
	}	
	
	j =1;
	for(i=a+1; i<(a+b)+1; i++)
	{
		tableB[j] = integer[i];
		++j;
	}
	
	j =0;
	for(i=a+b+1; i<(a+b+c)+1; i++)
	{
		tablequery[j] = integer[i];
		++j;
	}
	
	tableA[a+1]=99999999;
	tableB[b+1]=99999999;

	ranksByMerge(a, b, tableA, tableB, yRank, zRank);
	
	for(i=0; i<c;i++)
	{
		if(tablequery[i]!=0)
		{
			int q = tablequery[i];
			
			int n = sizeof(yRank)/sizeof(yRank[0]);
			int n1 = sizeof(zRank)/sizeof(zRank[0]);
			
			
			int result = binarySearch(yRank, 0, n+7, q); 
			if(result == -1)
			{
				int result1 = binarySearch(zRank, 0, n1+7, q);
				
				//finding desired i
				int index = q-result1;
				
				int low = 0;
				int high = sizeof(tableA)/sizeof(tableA[0]);
				
				while (low <= high) 
				{ 
					int middle = low + (high - low) / 2; 
  
					// Check if x is present at middle, note that index is a true target for rank 
					if (middle == index)
					{			
						if(tableA[middle] <= tableB[result1] && tableB[result1] < tableA[middle+1])
						{
							printf("\nlow %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d\n", low, high, middle, result1, middle, tableA[middle],result1,tableB[result1],middle+1, tableA[middle+1]);
							printf("b[%d]=%d has rank %d", result1,tableB[result1],q);
						}	
					}

					// If x greater, ignore left half 
					if (middle < index)
					{	
						
						int propindex= q-middle;
						
						if(tableA[middle] <= tableB[propindex] && propindex>0 && tableB[propindex] > tableA[middle+1])
						{
							printf("\nlow %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d", low, high, middle, propindex, middle, tableA[middle],propindex,tableB[propindex],middle+1, tableA[middle+1]);
						}	

						
						low = middle + 1;
								
					}
					// If x is smaller, ignore right half 
					else
					{
						
						int propindex= q-middle;
						if(tableA[middle] <= tableB[propindex] && propindex>0 && tableB[propindex] > tableA[middle+1])
						{
							printf("\nlow %d high %d i %d j %d a[%d]=%d b[%d]=%d a[%d]=%d", low, high, middle, propindex, middle, tableA[middle],propindex,tableB[propindex],middle+1, tableA[middle+1]);
						}	
						
						
						high = middle - 1;	
					}	
					
				}
			}
		
			else
			{	
				//finding desired j
				int index = q-result;
				
				int low = 0;
				int high = sizeof(tableB)/sizeof(tableB[0]);
				
				while (low <= high) 
				{ 
					int middle = low + (high - low) / 2; 
			  
					// Check if x is present at mid 
					if (middle == index)
					{		
						if(tableB[middle] < tableA[result] && tableA[result]<= tableB[middle+1])
						{
							printf("\nlow %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d\n", low, high, result, middle, middle, tableB[middle],result,tableA[result],middle+1, tableB[middle+1]);
							printf("a[%d]=%d has rank %d", result,tableA[result],q);
						}	
					}
			  
					
					// If x greater, ignore left half 
					if (middle < index)
					{
						
						int propindex= q-middle;
						if(tableB[middle] < tableA[propindex] && propindex>0 && tableA[result] > tableB[middle+1] && middle!=0)
						{
							printf("\nlow %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d", low, high, propindex, middle, middle, tableB[middle],propindex,tableA[propindex],middle+1, tableB[middle+1]);
						}
						
						
						low = middle + 1; 
					}
					
					// If x is smaller, ignore right half 
					else 
					{
						int propindex= q-middle;
						if(tableB[middle] < tableA[propindex] && propindex>0 && tableA[result] > tableB[middle+1] && middle!=0)
						{
							printf("\nlow %d high %d i %d j %d b[%d]=%d a[%d]=%d b[%d]=%d", low, high, propindex, middle, middle, tableB[middle],propindex,tableA[propindex],middle+1, tableB[middle+1]);
						}
						
						high = middle - 1; 
					}
					
					
				}
			}
		}	
	}
	

	printf("\n");
	
}

void ranksByMerge(int a, int b, int tableA[], int tableB[], int yRank[], int zRank[])
{
	int i,j,k;
	
	i=j=k=1;
	
	while(i<=a && j<=b)
		if(tableA[i]<=tableB[j])
			yRank[i++]=k++;
		else
			zRank[j++]=k++;

	while(i<=a)
		yRank[i++]=k++;	
	
	while(j<=b)
		zRank[j++]=k++;
}

int binarySearch(int arr[], int l, int r, int x) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (arr[m] == x) 
            return m; 
  
        // If x greater, ignore left half 
        if (arr[m] < x) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return -1; 
} 

