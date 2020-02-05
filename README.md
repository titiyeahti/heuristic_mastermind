#Heuristic mastermind

## Usage

```bash
cd bin
make
./[ea,rls,ga].out
```

Actually, there is not much to play with since all the current programs are designed to plot specific curves.

## Goal 

Try to analyze different heuristic algorithms for the resolution of the mastermind game with n colors and n slots.

## Files

- `bin/`, a makefile and the binaries;
- `src/`, the source code;
	+ the structure manipultation code is mainly documented in `mastermind.h`;
	+ the algo is in `metaheuristic.c` and his doc in the corresponding header file.
- `data/`, the data for plots AND the gnuplot code used for the plots;
- `plots/`, the corresponding plots in png;
- `rapport.pdf` a short report in french with lots of images :).


