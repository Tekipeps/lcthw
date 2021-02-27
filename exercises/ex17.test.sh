#!/bin/bash
set -e
echo "-------- Without valgrind"
echo "Creating database ..."
./ex17 db.dat c
echo ""

echo "Saving zed, frank, joe to database ..."
./ex17 db.dat s 1 zed zed@zedshaw.com
./ex17 db.dat s 2 frank frank@zedshaw.com
./ex17 db.dat s 3 joe joe@zedshaw.com
echo ""

echo "Printing all records ..."
# output=$(./ex17 db.dat l)
# echo $output
./ex17 db.dat l
echo ""

echo "Deleting record by id 3 ..."
./ex17 db.dat d 3
echo ""

echo "Printing all records ..."
./ex17 db.dat l
echo ""

echo "Getting record by id 2 ..."
./ex17 db.dat g 2

echo "--------With valgrind"

echo "Creating database ..."
./ex17 db.dat c
echo ""

echo "Saving zed, frank, joe to database ..."
valgrind ./ex17 db.dat s 1 zed zed@zedshaw.com
valgrind ./ex17 db.dat s 2 frank frank@zedshaw.com
valgrind ./ex17 db.dat s 3 joe joe@zedshaw.com
echo ""

echo "Printing all records ..."
valgrind ./ex17 db.dat l
echo ""

echo "Deleting record by id 3 ..."
valgrind ./ex17 db.dat d 3
echo ""

echo "Printing all records ..."
valgrind ./ex17 db.dat l
echo ""

echo "Getting record by id 2 ..."
valgrind ./ex17 db.dat g 2