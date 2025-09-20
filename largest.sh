#!/bin/bash

echo "Enter 3 numbers"
read num1
read num2
read num3

if [[ $num1 -gt $num2 ]]     
then
  largest=$num1
else
  largest=$num2  
fi

if [[ $largest -lt $num3 ]]
then
  largest=$num3
fi

echo "The largest of the given 3 numbers is $largest"