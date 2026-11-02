#!/bin/sh
# Shell script for Address Book Management

while [ 1 ]
do

echo "1) Create address book.\n2) View address book. \n3) Insert a record. \n4) Delete a record. \n5) Modify a record. \n6) Exit \n\nENTER YOUR CHOICE : "
read choice
echo "\n"

case $choice in
1)
	if [ -f record ]
	then
		echo "----x Record Already Exists x----\n\n"
	else
		touch record
		echo "---x Record created successfully x----\n\n"
		echo "rollNO\tyear\tbranch\tCGPA" > record
	fi
;;
2)
	if [ -f record ]
	then 
		cat record
		echo "\n\n"
	else
		echo "File does not exit \n\n"
	fi
;;
3)
	echo "insert in format : \n"
	echo -e "rollNO\tyear\tbranch\tCGPA\n"
	cat >> record
;;
4)
	if [ -f record ]
	then
		echo "Enter Roll No of the record to be deleted : "
		read rollno
		
		grep -v "$rollno" record > temp_record
		
		mv temp_record record
		echo "---x Record deleted successfully x----\n\n"
	else
		echo "File does not exist\n\n"
	fi
;;
5)
	cat record 
	echo "\t\t"

	if [ -f record ]
	then
		echo "Enter record to be edited "
		read oldd
		echo "Enter the chanage "
		read newd
		echo "\n\n"
		# FIXED: Changed single quotes to double quotes so variables expand
		sed -i "s/$oldd/$newd/" record
	fi
;;
6)
	echo "Exiting program. Goodbye!\n"
	exit 0
;;
*)
	echo "Invalid option. Please try again.\n\n"
;;
esac
done
