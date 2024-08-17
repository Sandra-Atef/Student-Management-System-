/*
 ============================================================================
 Name        : C Project about Student Management System
 Author      : Sandra Atef Kamal Kamel
 Date        : 11/8/2024
 Description : It allows the user to perform various operations such as
               adding new students, displaying all students,
               searching for a student by ID, updating student details,
               calculating the average GPA, and finding the student with the highest GPA.
 ============================================================================
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "prototypes.h"
struct node*head=NULL;
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	struct student s;
	int choice,id;
	while(1){
		printf("\n1.Add a Student\n");
		printf("2.Display All Students\n");
		printf("3.Search for a Student by ID\n");
		printf("4.Update Student Information\n");
		printf("5.Delete a Student\n");
		printf("6.Calculate Average GPA\n");
		printf("7.Find Student with Highest GPA\n");
		printf("8.Exit\n");
		// make the user choose which function he wanted to operate
		printf("Enter your choice:\n");
		scanf(" %d",&choice);
		// switch case to select the function choosen by the user
		switch (choice){
		// Prompts the user for new student details and adds them to the system
		case 1:
			printf("Enter Student's ID:\n");
			scanf(" %d",&s.id);
			printf("Enter Name:\n");
			scanf(" %[^\n]s",s.name);
			printf("Enter Age:\n");
			scanf(" %d",&s.age);
			printf("Enter GPA:\n");
			scanf(" %f",&s.gpa);
			addStudent(&s);
			break;
			// Shows a list of all stored student records
		case 2:
			displayStudents();
			break;
			// Allows the user to find a specific student using his unique ID.
		case 3:
			printf("Enter Student ID to search:\n");
			scanf(" %d",&id);
			searchStudentByID(id);
			break;
			// Updating of details for an existing student identified by his ID
		case 4:
			printf("Enter Student ID to update his information:\n");
			scanf(" %d",&id);
			updateStudent(id);
			break;
			// Removes a student's record based on their ID
		case 5:
			printf("Enter Student ID to delete his data:\n");
			scanf(" %d",&id);
			deleteStudent(id);
			break;
			// Computes and displays the average GPA of all students
		case 6:
			printf("the average GPA of all students is %f\n",calculateAverageGPA());
			break;
			// Identifies and displays the student with the highest GPA
		case 7:
			searchHighestGPA();
			break;
			// Terminates the program
		case 8:
			printf("Exit the program\n");
			return 0;
		}   //end of switch case
	} // end of while loop
} //end of main_function


// Create Linked List
void addStudent(const struct student *const ptr)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	current=head;
	// loop to check if student's ID already exists
	while(current!=NULL)
	{
		if(ptr->id==current->data.id)
		{
			printf("This ID is already reserved\n");
			return;
		}
		current=current->next;
	}

	// Allocate memory for new node
	struct node*link=(struct node*)malloc(sizeof(struct node));//create new node

	// Check if memory allocation fails
	if(link==NULL)
	{
		printf("memory allocation fails\n");
		return;
	}

	//copy the student's data to the new node and make the next point to NULL
	link->data.id=ptr->id;
	strcpy(link->data.name,ptr->name);
	link->data.age=ptr->age;
	link->data.gpa=ptr->gpa;
	link->next=NULL;

	// If head is empty, create new list
	if(head==NULL)
	{
		head=link;
		return;
	}

	current=head;

	// loop until reach the last node in the old list
	while(current->next!=NULL)
	{
		current=current->next;
	}

	// Make the last node in the old list point to new node
	current->next=link;
}   // end of addStudent_function


// Display the list
void displayStudents(void)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	// Check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
	}

	// Start looping from the head until reach the last node to display all the students in the list
	current=head;
	while(current!=NULL)
	{
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
		current=current->next;
	}

}  // end of displayStudents_function


// Search for a student by his ID
void searchStudentByID(int id)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	// Check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
		return;
	}

	// Start checking from the first node
	current=head;
	while(current!=NULL)
	{
		// If student's ID is found display all his details
		if(current->data.id==id)
		{
			printf("Student found:\n");
			printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
			return;
		}
		current=current->next;
	}

	// Student's ID is not found in the list
	printf("Student with ID %d not found.\n",id);

} // end of searchStudentByID_function


// Update the details of a student with the given ID.
void updateStudent(int id)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	//check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
		return;
	}

	// Start checking from the first node
	current=head;
	while(current!=NULL)
	{
		// If student's ID is found update all his details
		if(current->data.id==id)
		{
			printf("Enter new details for the student with ID %d:\n",id);
			printf("Enter new name:\n");
			scanf(" %[^\n]s",current->data.name);
			printf("Enter new age:\n");
			scanf(" %d",&current->data.age);
			printf("Enter new GPA:\n");
			scanf(" %f",&current->data.gpa);
			printf("Student details updated successfully.\n");
			return;
		}
		current=current->next;
	}
	// Student's ID is not found in the list
	printf("Student with ID %d not found.\n",id);

} // end of updateStudent_function


// Return the average GPA of all students
float calculateAverageGPA(void)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	// Initialize sum
	float sum=0;

	// Initialize the total number of the students
	int total_no=0;

	// Check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
		return 0.0;
	}

	// start looping from the head until reach the last node in list
	current=head;
	while(current!=NULL)
	{
		// calculate sum of GPA and the total number of the students
		sum+=current->data.gpa;
		total_no++;
		current=current->next;
	}
	// Return the average of students'GPA
	return(sum/total_no);

}  // end of calculateAverageGPA_function


// Search for the student with the highest GPA
void searchHighestGPA(void)
{
	// pointer to loop in linked list
	struct node*current=NULL;

	// variable to store the highest GPA
	float max;

	//check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
		return;
	}

	current=head;
	// store the first GPA in max
	max=current->data.gpa;

	// start checking from the second node to not to compare first id with itself
	current=head->next;
	while(current!=NULL)
	{
		// If GPA of the next node is greater put it in max
		if((current->data.gpa)>max)
		{
			max=current->data.gpa;
		}
		current=current->next;
	}
	// Start looping from the head until reach the last node in list
	current=head;
	while(current!=NULL)
	{
		// If student's GPA is the highest GPA display all his details
		if((current->data.gpa)==max)
		{
			printf("Student with the highest GPA:\n");
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
			return;
		}
		current=current->next;
	}
} // end of searchHighestGPA_function


// Delete a student from the list by his ID.
void deleteStudent(int id)
{
	// pointer point to loop in linked list
	struct node*current=NULL;
	struct node*prev=NULL;

	// Check if list is empty
	if(head==NULL)
	{
		printf("there are no students\n");
		return;
	}

	// Check the first node in list
	if(head->data.id==id)
	{
		current=head;
		// move head to next node
		head=head->next;
		free(current);
		printf("Student with ID %d is deleted successfully.\n",id);
		return;
	}
	// Check the rest of nodes in list
	current=head->next;
	prev=head;
	while(current!=NULL)
	{
		if(current->data.id==id)
		{
			prev->next=current->next;
			free(current);
			printf("Student with ID %d is deleted successfully.\n",id);
			return;
		}
		current=current->next;
		prev=prev->next;
	}

	// Student's ID is not found in the list
	printf("Student with ID %d not found.\n",id);
	return;
}   // end of deleteStudent_function

