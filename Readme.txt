Input Format: 
	metadata.txt containing the information about the column size. 
	<column name 1>,<size of the column> 
	<column name 2>,<size of the column> <column name 3>,<size of the column> 
	...... 
	<column name n>,<size of the column> 

input.txt 
	Containing the records with the column values separated by the space. 
	All the values will be in the string only. 
 
Command Line Inputs 
1. Input file name (containing the raw records) 
2. Ouput file name (containing sorted records) 
3. Main  memory size (in MB) 
4. Order code (asc/desc) asc means to sort in ascending order and desc means  to sort 
in descending order 
5. Columname1 
6. Columnname2

 
Example 
● ./sort  input.txt output.txt 50 asc c0 c1 
● ./sort  input.txt output.txt 100 desc c0 
● ./sort  input.txt output.txt 100 asc c1 c0 
● ./sort  input.txt output.txt 500 asc c2 
 
As in the first example, the file input.txt to be sorted in ascending order with 50 MB space 
based on column c0 and if any column have same value for c0 then on the basis of c1, 
available. (Similar to ORDER BY clause in SQL). 
In case if the value is same for all the available columns, then the order should be the same 
as in the input file. 