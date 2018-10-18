# Hit ratio

Ideal hit ratio would be if only one page will be referenced

e.g.

10  # page frames

1
1
1
...
1  # page references only '1'


For N page references this would result in N - 1 hits and only 1 miss.

### Minimizing the misses
There could not be less than 1 miss in any input (except for zero), 
thus 1 miss is the minimal amount

### Maximising the hits
N - 1 could grow arbitrarily large depending on the amount of references.

# Miss ratio

Big miss ratio would be achieved if all page references would be unique

e.g.

10  # page frames

1
2
3
...
999
1000
...
N

### Maximizing the misses
There are already N out of N misses, so that could not be maximized further.

### Minimizing the hits
There are already 0 hits, so that could not be minimized further.

### Reality
In reality, of course there would not be enough pages to count to infinity.
It is sufficent then to evenly space out at least K + 1 pages so that every
time a page is needed, it is already too old

e.g.

10  # page frames

1
...
10
11
1
2
...
10
... and so on

This would still give the desired result of 0 hits.
