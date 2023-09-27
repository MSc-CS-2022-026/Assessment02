# Assessment02

## Instructions

Use the `make` command to execute the Makefile. This will generate two executable files:

- `medge_serial`
- `medge_parallel`

### Running the Serial Version

To detect edges using the serial version of the program, run the following command:
```
./medge_serial q image/in_file_name.bmp out_file_name.bmp 1 high
```

### Running the Parallel Version

To detect edges using the parallel version of the program, run the following command:

```
./medge_parallel q image/in_file_name.bmp out_file_name.bmp 1 high
```

### Running with the Job file

Change desired number of threads in `parallel.job` file

```
export OMP_NUM_THREADS=number_of_threads
```

To submit job file to the cluster

```
qsub parallel.job
```
