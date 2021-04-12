# Partie 3: Multiplexage, threads, mutex et IPC

## Exercise 1: Multiplexage

* Question 1: PTTY is the communication channel made trough a pseudo terminal, being the commands sent using one of them seen as if they had been sent from a normal terminal, and interpreted as such in the other end. 

* Question 2: Looking at the reader.c file,  

* Question 3: The time is defined in the GPGLL data, as the second last value, between the fields 5 (longitude direction, E/W) and 7 (data status, A/V). It is presented in the shape hours/minutes/seconds/decimal seconds.

* Question 4: Inside reader.c the following functions are used:
  - opening: *open()*, opening the virtual port and reading the fd;
  - listening: *select()* and *FD_ISSET*, pointing to which fd listen and checking if it is present in the set;
  - reading: *read()*, getting the contents into the buffer;
  - closing: *close()*, closing the virtual port.
  
* Question 5: Modified in the file.

* Question 6:

* Question 7:


## Exercise 2: Mémoire partagée et sémaphore

* Question 1: 

* Question 2: 

* Question 3: 

* Question 4: 

* Question 5: 

* Question 6: 

* Question 7: 

