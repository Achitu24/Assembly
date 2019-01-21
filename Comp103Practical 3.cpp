//Comp103, Practical session 3
//Name: Adrian Chitu
//Student ID: 201193718
//Student e-mail: A.chitu@student.liverpool.ac.uk


#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
int main(void) {
	int poscount = 0; // intialise the counter for positive numbers
	int negcount = 0; // initialise the counter for negative numbers 
	int zerocount = 0; // initialise the counter for
	char format[] = "%d"; // format for the calling the printf function
	int input;
	char firstMessage[] = "How many times is the loop going for? ";
	char secondMessage[] = "Please input a number ";
	char poscountMessage[] = "The number of positive numers is: %d\n";
	char negcountMessage[] = "The number of negative numbers is %d\n";
	char zerocountMessage[] = "The numbers of zeros is: %d";
	char invalidinput[] = "Wrong input. Please enter a positive number \n";
	_asm {

		start_again: 
		//Print FirstMessage
		lea eax, firstMessage //load address of FirstMessage into eax
		push eax // address of string, stack parameter
		call printf // use library code subroutine
		add esp, 4

		//Ask for the input
		lea eax, input
		push eax
		lea eax, format //address of the format string is saved in eax
		push eax //push the address of the string to the stack
		call scanf //call scanf, it will take two parameters from
		add esp, 8

		cmp input, 0 
		jle invalid_input

		//Start Of Loop
		mov ecx, input
		
		for_loop :
			push ecx
			//Print SecondMessage
			lea eax, secondMessage //load address of SecondMessage into eax
			push eax // address of string, stack parameter
			call printf // use library code subroutine
			add esp, 4

			//Ask for the input a second time 
			lea eax, input
			push eax
			lea eax, format //address of the format string is saved in eax
			push eax //push the address of the string to the stack
			call scanf //call scanf, it will take two parameters from
			add esp, 8

			mov eax, input
			cmp eax, 0 //compare 0 to accumulator
			jg poscount_label //if greater than 0, jump to poscount_label
			jl negcount_label // if less , jump to negcount_label
			jz zerocount_label //if equal to 0, jump to zerocount_label
		
		//decrements the counter and jump to printing label if the counter is equal to 0 and back again if greater than 0
		back_to_the_loop :
			pop ecx
			dec ecx
			cmp ecx, 0
			jz print_result
			jg for_loop


		//increments the positive number counter 
		poscount_label :
			mov eax, poscount
			inc eax
			mov poscount, eax
			jmp back_to_the_loop

		//increments the negative number counter
		negcount_label :
			mov eax, negcount
			inc eax
			mov negcount, eax
			jmp back_to_the_loop

		//increments the zero counter number
		zerocount_label :
			mov eax, zerocount
			inc eax
			mov zerocount, eax
			jmp back_to_the_loop


		//label for validating the user input
		invalid_input :
				lea eax, invalidinput //load address of FirstMessage into eax
				push eax // address of string, stack parameter
				call printf // use library code subroutine
				add esp, 4
				jmp start_again


		print_result :

			push poscount  //push the value of the variable onto the stack
			lea eax, poscountMessage //address of the format string is saved in eax
			push eax //push the address of the string to the stack
			call printf //call printf
			add esp, 8

			push negcount  //push the value of the variable onto the stack
			lea eax, negcountMessage //address of the format string is saved in eax
			push eax //push the address of the string to the stack
			call printf //call printf
			add esp, 8

			push zerocount  //push the value of the variable onto the stack
			lea eax, zerocountMessage //address of the format string is saved in eax
			push eax //push the address of the string to the stack
			call printf //call printf
			add esp, 8


	} // back to C
	Sleep(5000); // sleep command so the windows showing the results will not close
	
	return 0;
}