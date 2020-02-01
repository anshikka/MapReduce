/*test machine: CSELAB_KH-1250-16
* date: 10/23/2019
* name: Ansh Sikka
* x500: sikka008
*/

# MapReduce
Implementation of MapReduce, a tool/algorithm that uses multiple processes large datasets and synchronize output of key-value pairs.
## Purpose
The purpose of this project is to keep large datasets in sync by using mapper and reducer processes. This project also show how to manipulate
different filesystems to edit, create, and parse files/directories. Additionally processes and symbolic links are a major area of
learning in this project.

## How to compile

Make sure you have a directory you can pass in. Also have in mind the number of mapper processes.

Before executing all recipes, do this: 
`make clean`
`make`

Then,
`./mapreduce <sample folder> <number of mapper processes>`

## Assumptions
* Can use atoi function from standard string library
* Can utilize some global variables
* Can create an array of child processes (process fan under parent)

## Team Names and x500 + Contributions
Ansh Sikka -sikka008

I did have a partner: Jacob Isler: isle0011
We did work on the project individually. However we did use each other to
bounce off each others ideas on how to move forward with the product. There 
was little to no overlap of code. The general strategies were similar between the projects.

## Extra Credit
Extra credit was attempted and appeared to be successful in identifying a symbolic link (with lstat). However, I could not figure out how to 
avoid processing it.
 
