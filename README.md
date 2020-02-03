#Heuristic mastermind

## Usage

```bash
cd bin
make
./test.out n k
```

With `n` the size of the grid/number of colors and `k` the number of runs.

## Goal 

Try to analyze different heuristic algorithms for the resolution of the mastermind game with n colors and n slots.

## Todo

- Collectivize some code
- Implement the nloglog(n) algo of the teacher
- Choose what to plot ! and why ! 
1 One program per function (RLS, GA, EA) with param passed to command line ?
2 then bash script 
or
- two functions for acquiring data (mean, (median, quartiles), variance)
	- convergence (number of steps to reach each score)
	- experimental performance (blackbox complexity, time)

## Outline

Goal compare EA, GA, RLS. 
Parameters variation in EA and GA.
- Crossover
	- Uniform crossover
	- k-point crossover
	- Majority vote
- Mutation 
	- sbm
- Selection
	- Elitist because no local maxima
- lambda, mu;

Analysis :
plot : complexity w/r n
- Black box complexity
- Experimental time complexity




## Functions documentation
### Data collecting 

- `stat_t* progression(fct, int n, int runs)` return an array of size n. The slot i 
indicate the first time the scrore i have been reached;
- `stat_t[2] perf(fct, int n, int runs)` return two stats, res[0] time perf, res[1] BBperf;

### Algorithms
Common parameters :
- Instance a;
- `void modif(uint* target, uint* src, uint size)`;
- lamba, mu;
- selection (lambda, mu) ou (lambda + mu).


