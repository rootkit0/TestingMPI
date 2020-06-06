# Makefile generico
SHELL = /bin/sh

tutorial1: Tutorial1.c
	mpicc -o tutorial1 Tutorial1.c
	mpiexec -n 4 ./tutorial1

tutorial2: Tutorial2.c
	mpicc -o tutorial2 Tutorial2.c
	mpiexec -n 2 ./tutorial2 2
	mpiexec -n 2 ./tutorial2 8
	mpiexec -n 2 ./tutorial2 32
	mpiexec -n 2 ./tutorial2 128
	mpiexec -n 2 ./tutorial2 1024
	mpiexec -n 2 ./tutorial2 8192

tutorial3: Tutorial3.c
	mpicc -o tutorial3 Tutorial3.c
	mpicc -o tutorial3nbloq Tutorial3NBloq.c
	mpicc -o tutorial3sincro Tutorial3Sincro.c
	mpicc -o tutorial3buff Tutorial3Buff.c
	mpiexec -n 10 ./tutorial3
	mpiexec -n 10 ./tutorial3nbloq
	mpiexec -n 10 ./tutorial3sincro
	mpiexec -n 10 ./tutorial3buff

tutorial4a: Tutorial4a.c
	mpicc -o tutorial4a Tutorial4a.c
	mpiexec -n 6 ./tutorial4a


tutorial4b: Tutorial4b.c
	mpicc -o tutorial4b Tutorial4b.c
	mpiexec -n 6 ./tutorial4b

tutorial5: Tutorial5.c
	mpicc -o tutorial5 Tutorial5.c
	mpiexec -n 2 ./tutorial5 5

all:
	mpicc -o tutorial1 Tutorial1.c
	mpiexec -n 4 ./tutorial1
	mpicc -o tutorial2 Tutorial2.c
	mpiexec -n 2 ./tutorial2 2
	mpiexec -n 2 ./tutorial2 8
	mpiexec -n 2 ./tutorial2 32
	mpiexec -n 2 ./tutorial2 128
	mpiexec -n 2 ./tutorial2 1024
	mpiexec -n 2 ./tutorial2 8192
	mpicc -o tutorial3 Tutorial3.c
	mpicc -o tutorial3nbloq Tutorial3NBloq.c
	mpicc -o tutorial3sincro Tutorial3Sincro.c
	mpicc -o tutorial3buff Tutorial3Buff.c
	mpiexec -n 10 ./tutorial3
	mpiexec -n 10 ./tutorial3nbloq
	mpiexec -n 10 ./tutorial3sincro
	mpiexec -n 10 ./tutorial3buff
	mpicc -o tutorial4a Tutorial4a.c
	mpiexec -n 6 ./tutorial4a
	mpicc -o tutorial4b Tutorial4b.c
	mpiexec -n 6 ./tutorial4b
	mpicc -o tutorial5 Tutorial5.c
	mpiexec -n 2 ./tutorial5 5