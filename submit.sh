#!/bin/sh

### ### - This is a comment
### #SBATCH - this is a slurm option

### Number of threads to use (required)
#SBATCH -n 8

### Maximum run time is 1 hours 0 minutes 0 seconds
### this may be increased up to the queue limit
### (optional unmark)
##SBATCH --time=01:00:00

### Job name (optional unmark)
#SBATCH -J G2

##SBATCH --tasks-per-node=16

### The host names
##SBATCH -w exw1e5s2,exw1e6s1
##SBATCH -w exw1e7s[1-2]


### output files (optional)
#SBATCH --output=job.%J.out.txt
#SBATCH --error=job.%J.err.txt

### partition (required)
### for the large partition
#SBATCH --partition=exw1A
### for the small partition
##SBATCH --partition=exw1AB

### mail to send (optional unmark)
### notify on state change: BEGIN, END, FAIL or ALL
##SBATCH --mail-type=ALL
##SBATCH --mail-user=YOUR-EMAIL-HERE@COM.COM

### below this line everything is:
### REQUIRED (!!! change your program name )

hostname
whoami
pwd
ulimit -a
### ldd ~/ YOUR_PROGRAM_NAME
ldd `which mpirun`

mpirun --loadbalance --display-allocation \
-mca btl_openib_want_fork_support 0 \
-mca btl_openib_warn_no_device_params_found 0 \
-mca btl openib,self,sm \
~/a.out > output

### The end ###
