/*
 ============================================================================
 Name        : SundayProject.c
 Author      : Apurv Amurtkar, Anurag Jadhav, Dishant Ratnam, Shraddha Vora.
 Version     :
 Copyright   : Your copyright notice
 Description : This program will except queries such as Select, Update, Truncate, Delete and will perform operations on employee table.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct employee {
	char name[50];
	char designation[50];
	char department[50];
	int salary;
	int id;
	struct employee *next;
};

struct attributeData{
	char attr[50];
	char value[50];
	struct attributeData *next;
};


struct employee *node = NULL;

/*Function= Copy String
 *Complexity=  O(n)
 *Failure Condition= if string is equal to size of char array*/

char * copystring(char *a, char *b, int start, int end) {
	int i = 0, j = 0;

	for (i = start; i <= end; i++) {
		b[j++] = a[i];
	}
	b[j] = 0;

	return b;
}



/*Linked List Implementation
Complexity=O(n)
Failure Condition:if malloc returns zero there is insufficient memory*/
void add(struct employee **p, char *nam, char *desin, char *dep, int sala) {
	struct employee *x;
	x=(struct employee *)malloc(sizeof(struct employee));
	struct employee *temp;
	int idnum = 0;
	strcpy(x->name,nam);
	strcpy(x->designation,desin);
	strcpy(x->department,dep);
	x->salary = sala;
	x->id = 0;
	x->next = NULL;

	if (*p == NULL) {
		*p = x;
	} else {
		temp = *p;
		while (temp->next != NULL) {
			temp = temp->next;
			idnum = temp->id;
		}

		x->id = idnum + 1;
		temp->next = x;
	}

}

/* Function=
 * Complexity=O(n)
   Failure Condition:No failure  */

void deletequery(char *q,struct employee **p) {
	int i, j, k, tempid;
	struct employee *temp1, *temp2;

	char a[50] = "from employee where id=";
	char r[50], t[10];

	for (i = 0; q[i] != '='; i++) {
		r[i] = q[i];
	}
	r[i]='=';
	r[++i] = '\0';
	for (j = i, k = 0; q[j] != ';'; j++, k++) {
		t[k] = q[j];
	}
	t[k] = '\0';
	sscanf(t, "%d", &tempid);
	if (strcmp(r, a) == 0) {
		temp1 = *p;
		temp2=*p;
		if (*p == NULL) {
			printf("no records found\n");
		}
		else if(temp1->id==tempid){
			*p=temp1->next;
		}
		else {

			while (temp1->next != NULL) {
				temp2 = temp1;
				temp1 = temp1->next;
				if ((temp1->id) == tempid) {
					temp2->next = temp1->next;
				}

			}
			free(temp1);
		}
	} else
		printf("syntax error");
}
/* Complexity=O(n)
   Failure Condition:No failure  */

void truncatequery(char *u, struct employee **p) {
	struct employee *temp;
	int i, j;
	char c[50] = "table employee;";
	char y[50];

	if (strcmp(c, u) == 0) {
		while ((*p) != NULL) {
			temp = (*p);
			(*p) = (*p)->next;
			free(temp);
		}
		*p = NULL;

	} else
		printf("syntax error");
}

/* Complexity=O(n)
   Failure Condition:No failure  */

void display(struct employee **p) {

	struct employee *temp;
	int i = 0;


	temp = *p;
	if (temp == NULL) {
		printf("No records present\n");
	} else {
		printf("\nName\tDesignation\tDepartment\tSalary\tId\n");
		while (temp != NULL) {
			printf("%s\t%s\t%s\t%d\t%d\n",temp->name, temp->designation, temp->department,temp->salary, temp->id);
			temp = temp->next;
		}
		printf("\n");
	}
}


/* Complexity=O(n)
   Failure Condition:No failure */

char * addstring(char *a, char *b, int start, int end) {
	int i = 0;

	for (i = 0; a[i]; i++) {

		b[start++] = a[i];
	}
	b[start] = 0;

	return b;
}

/*Select Query
  Complexity=O(n^2)
  Failure Condition:No failure  */

void selectquery(char *a, struct employee **p) {
	int i, j, k, n, length;
//struct emp *first;
	struct employee *x1;
	x1=*p;
	char x[50], y[50], z[50];
	char s[] = { 'name', 'designation', 'department', 'salary', 'id' };
	char string[50] = "fromemployee;";

	for (i = 0; a[i]; i++)
		;
	int size = i;
	char b = a[0];
	int start = 0;
	for (i = 0; a[i] != ';'; i++) {
		if (start == 0 && a[i] == ' ') {
			int beg = i + 1;
			for (j = beg, k = 0; a[j] != ' '; j++, k++, i++) {
				x[k] = a[j];
			}
			x[k] = '\0';

			n = k;
			copystring(x, z, 0, n - 1);
			start = 1;
			i++;
		}
		if (start == 1 && a[i] == ' ') {
			int beg = i + 1;
			for (j = beg, k = 0; a[j] != ';'; j++, k++, i++) {
				y[k] = a[j];
			}
			y[k] = '\0';
			addstring(y, z, n, k + n);

		}
	}
	z[k + n] = ';';
	z[k + n + 1] = '\0';

	if (strcmp(z, string) != 0) {
		printf("Invalid Query");
	} else if (b == '*') {
		display(&node);
	}

	else {
		for (i = 0; a[i] != ' '; i++) {
			length = i;
		}
		char col[50];

		copystring(a, col, 0, length);
		col[length + 1] = '\0';
		if (strcmp(col, "name") == 0) {
			printf("Id\tName");
			while(x1!=NULL){
				printf("%d\t%s\t", x1->id,x1->name);
				x1 = x1->next;
			}
		} else {
			if (strcmp(col, "designation") == 0) {
				printf("Id\tDesignation");
				while(x1!=NULL){
					printf("%d\t%s\n", x1->id,x1->designation);
					x1 = x1->next;
				}
			} else {
				if (strcmp(col, "department") == 0) {
					printf("Id\tDepartment");
					while(x1!=NULL){
					printf("%d\t%s\n", x1->id,x1->department);
					x1=x1->next;
					}
				} else {
					if (strcmp(col, "salary") == 0) {
						printf("Id\tSalary");
						while(x1!=NULL){
						printf("%d\t%d\n",x1->id,x1->salary);
						x1=x1->next;
						}
					} else {
						printf("Id");
						while(x1!=NULL){
							printf("%d\n",x1->id);
							x1=x1->next;
						}
					}
				}
			}
		}
	}

}



/*Insert Function
  Complexity=O(n^2)
  Failure Condition:if designaion,department and name string contains single quotes */

void insertquery(char *input, struct employee **p) {

	int i, size, j, k, g, b, h;
	char *xname, *xdesignation, *xdept;
	int salary;
	int count = 6;
	char data[4][50];
	char temp[50];
	char temp1[50] = "into employee values(";
	char a[50];
	int z = 0, d = 0, flag = 0, n;

	for (g = 0, n = 0; input[g] != '('; g++, n++) {
		temp[n] = input[g];
	}
	temp[n] = '(';
	temp[n + 1] = '\0';
	if (strcmp(temp, temp1) == 0) {

		for (b = g + 1, h = 0; input[b]; b++, h++) {
			a[h] = input[b];
		}
		a[h] = '\0';

		for (i = 0; a[i]; i++) {
			if (a[i] == 39 && count >= 0) {
				count--;
				for (j = i + 1, k = 0; a[j] != 39; j++, k++) {
					data[z][k] = a[j];
					i++;
				}
				data[z][k] = 0;
				count--;
				i++;
				z++;

			}

			if (count == 0 && flag == 0) {
				for (d = j + 1, k = 0; a[d] != ')'; d++) {
					if (a[d] != ',') {
						data[z][k] = a[d];

						k++;
					}

				}
				data[z][k] = '\0';
				flag = 1;
				i = d;

			}

		}

		xname = data[0];
		xdesignation = data[1];
		xdept = data[2];
		salary = 0;
		sscanf(data[3], "%d", &salary);

		add(p, xname, xdesignation, xdept, salary);
	} else
		printf("syntax error");
}






/*Query Parser
 * Complexity= O(n)
 * Failure condition= No Failure condition*/


int firstWordParser(char *query) {
	char firstWord[8];
	char remString[50];
	int i = 0, first = 0, remstart = 0;
	for (i = 0; query[i]; i++) {
		if (query[i] == ' ') {
			if (first == 0) {
				copystring(query, firstWord, 0, i - 1);

				first = 1;
			}
		}
		if (first == 1 && query[i] > 32 && remstart == 0) {
			remstart = i;
		}

	}
	copystring(query, remString, remstart, i - 1);
	strcpy(query, remString);

	char *definedArray[] =
			{ "select", "insert", "update", "delete", "truncate" };
	for (i = 0; i < 5; i++) {
		if (strcmp(firstWord, definedArray[i]) == 0) {
			return i + 1;
		}
	}

	return 0;
}

/* Update Parser
 * Complexity= O(n^2)
 * Failure condition= No Failure condition*/

char ** updateparser(char *query) {
	char data[6][50];
	char **dTB=(char **)malloc(sizeof(char)*2);
	int i=0;
	int *y = (int *) malloc(2 * 50 * sizeof(char));
	for (i = 0; i < 2; i++) {
		dTB[i] = y + (i * 50);
	}
	char *definedArray[] = { "name", "designation", "department", "salary" };
	char str[50];
	char remString[50];

	int first = 0, remstart = 0, j = 0, z = 0, attribute_string = 0, k =0;

	while (query[i] && z<=5) {
		for (i = 0; query[i]; i++) {
			if (z == 2 && first==0) {
				for (j = 0;!(query[i] == 'w' && query[i + 1] == 'h' && query[i + 2] == 'e'); j++)
					i++;
				for (k = i-1; !(query[k] >= 'a' && query[k] <= 'z'); k--)
					;

				copystring(query, str, 0, k);
				strcpy(data[z], str);
				z++;
				first = 1;
			}
			if (z == 4 && first==0) {
				for (j = 0;!(query[i] == '='); j++)
					i++;
				for (k = i; !(query[k] >= 'a' && query[k] <= 'z'); k--)
					;

				copystring(query, str, 0, k);
				strcpy(data[z], str);
				z++;
				first = 1;
			}
			if (query[i] == ' ' || query[i]==';') {

				if (first == 0) {
					copystring(query, str, 0, i - 1);
					strcpy(data[z], str);
					z++;
					first = 1;
				}

			}
			if (first == 1 && ((query[i] >= 'a' && query[i] <= 'z') || (query[i] >='0' && query[i]<='9')) && remstart == 0) {
				remstart = i;
				break;
			}

		}
		copystring(query, remString, remstart, strlen(query) - 1);
		strcpy(query, remString);
		first = 0;
		remstart = 0;
		i = 0;

	}



	for (i = 0; i < 6; i++) {
		if (strcmp(data[i], "employee") != 0) {
			printf("Incorrect tablename");

			break;
		}
		i++;
		if (strcmp(data[i], "set") != 0) {
			printf("Incorrect query");

			break;
		}
		i++;
		/*for (j = 0; j < 5; i++) {
			if (strcmp(data[i], definedArray[i]) == 0) {
				break;
			}
		}
		if (j < 5)
			sprintf(dataToBeSent[0], "%d", j + 1);
		else {
			printf("Incorrect attribute");
			break;
		}*/
		strcpy(dTB[0],data[i]);
		i++;

		if (strcmp(data[i], "where") != 0) {
			printf("Incorrect syntax at where clause");
			break;
		}
		i++;
		if (strcmp(data[i], "id") != 0) {
			printf("Incorrect syntax, no id entered");
			break;
		}
		i++;
		strcpy(dTB[1],data[i]);
		i++;
	}
	return dTB;
}







//Update




struct employee * find(struct employee **e,int empId){
	struct employee *tmp;
	tmp=*e;
	while(tmp!=NULL && tmp->id!=empId){
		tmp=tmp->next;
	}

	return tmp;
}

/* Updating query passing
 * Complexity= O(n)
 * Failure condition= No Failure condition*/

void updatequery(char *query, struct employee **e) {

	char **d;

	d = updateparser(query);
	int i = 0, j = 0;

	char *definedArray[] = { "name", "designation", "department", "salary" };
	struct attributeData *attributeStart = NULL;
	struct attributeData x;
	char attr[50], value[50];
	int equal = 0;
	for (i = 0; d[0][i]; i++) {
		if (d[0][i] == '=') {
			equal = 1;
			continue;
		}
		if (d[0][i] >= 'a' && d[0][i] <= 'z') {
			int beg = i;
			while (d[0][i] >= 'a' && d[0][i] <= 'z')
				i++;
			i--;
			if (equal == 0) {

				copystring(d[0], attr, beg, i);
				strcpy(x.attr, attr);

			} else {
				copystring(d[0], value, beg, i);
				strcpy(x.value, value);
				x.next = NULL;
				if (attributeStart == NULL) {
					attributeStart = &x;
				} else {
					struct attributeData *t = attributeStart;
					while (t != NULL) {
						t = t->next;
					}
					t->next = &x;
				}
				equal = 0;
			}
		}
	}
		int empId = 0;
		sscanf(d[1], "%d", &empId);
		struct employee *tmp;
		tmp = find(&node, empId);
		if (tmp == NULL) {
			printf("No record present.\n");
			return;
		}
		int salary = 0;
		while (attributeStart != NULL) {
			for (j = 0; j < 5; j++) {
				if (strcmp(attributeStart->attr, definedArray[j]) == 0) {
					break;
				}
			}
			switch (j + 1) {
			case 1:
				strcpy(tmp->name, attributeStart->value); //d[1]
				break;
			case 2:
				strcpy(tmp->designation, (attributeStart)->value); //d[1]
				break;
			case 3:
				strcpy(tmp->department, (attributeStart)->value); //d[1]
				break;
			case 4:
				salary = 0;
				sscanf((attributeStart)->value, "%d", &salary); //d[1]
				tmp->salary = salary;
				break;
			default:
				break;
			}
			attributeStart = attributeStart->next;
		}

		free(*d);
		free(d);

}

/*
 All to lower case
* Complexity= O(n)
* Failure condition= No Failure condition
*/

void queryTolowerCase(char *query){
	int i=0;
	for(i=0;query[i];i++){
		if(query[i]>='A' && query[i]<='Z'){
			query[i]+=32;
		}
	}
}

/*Complexity= O(0)
 * Failure Condition= There is no failure condition*/

void file_handling_write(struct employee **p){
	FILE *ptr_myfile;
	struct employee *temp;
	temp=*p;
	ptr_myfile = fopen("database.bin", "wb+");

	while(temp!=NULL){
		fwrite(temp, sizeof(struct employee), 1, ptr_myfile);
		temp=temp->next;
	}
	truncatequery("table employee;",&node);
	fclose(ptr_myfile);
}

/*Complexity= O(0)
 * Failure Condition= There is no failure condition*/
void file_handling_read(struct employee **p){
	FILE *ptr_myfile;
	char *filename = "database.bin";
	ptr_myfile = fopen("database.bin", "rb+");
	if (!ptr_myfile) {
		printf("No database present currently,please create a database\n");
		return;
	}

	fseek(ptr_myfile, 0, SEEK_END);
	long eof = ftell(ptr_myfile);
	fseek(ptr_myfile,0,SEEK_SET);
	long cur_pos=0;
	struct employee *temp1,*temp2;
	temp1 = *p;

	temp1 = (struct employee *)malloc(sizeof(struct employee));
	fread(temp1, sizeof(struct employee), 1, ptr_myfile);
	*p=temp1;
	temp2 = (struct employee *)malloc(sizeof(struct employee));
	while(cur_pos<eof){

		fread(temp2, sizeof(struct employee), 1, ptr_myfile);
		temp1->next=temp2;
		temp1=temp2;

		cur_pos=ftell(ptr_myfile);
	}
	temp1->next=NULL;
	fclose(ptr_myfile);
}

//Main


int main(void) {


		file_handling_read(&node);
		int exitQuerying=0;
		char query[100];

		do{
		start:printf("Enter the query\n");

		gets(query);

		queryTolowerCase(query);
		int b;
		b=firstWordParser(query);


		 switch(b){
		 case 1:selectquery(query,&node);
		 	 	 break;
		 case 2: {
			insertquery(query, &node);
			printf("Data added");
			b = 0;
			break;
		 }
		 case 3:updatequery(query,&node);
		 	 	 b=0;
		 	 	break;
		 case 4:deletequery(query,&node);
		 	 	 b=0;
		 	 	 break;
		 case 5:truncatequery(query,&node);
		 	 	 b=0;
		 	 	 break;
		 default: printf("Entered query is incorrect");
		 	 	  exitQuerying=1;
		 	 	 	 break;
		 }
		 display(&node);
		}while(exitQuerying==0);

		file_handling_write(&node);

		return EXIT_SUCCESS;
	}


	//temporary entries
	//Select * from employee
	//SELECT name from employee;
	//Insert into employee VALUES('Apurv','CEO','Finance',25000000);
	//Update employee Set name=ABC where id=2;
	//delete from employee where id=1;
	//delete from employee where id=2;
	//truncate Table employee;


