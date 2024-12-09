# my take on how tiling would be most preferable

## what do we consider optimal?
- ease of slicing
    - on at least one axis you have to be able to make a cut that goes from edge to edge
    - said cut must not cut trough any cell
    - this shall apply recursively to every piece that is a result of a cut
    - tldr: vágóasztallal kényelmesen vágható kell legyen
- least amount of paper wasted
    - in other words, we aim to make the documents height as low as possible, since the width is fixed

## [guillotine cutting](https://en.wikipedia.org/wiki/Guillotine_cutting)
- after typing allat stuff down i found a wiki page about this exact problem
    - an optimal solution is still NP hard
    - 1 of our sides are constrainted
- an exact algorithm is unnecessary tho
    - most of the time we deal with a single type of tile
        - with that constraint there is a polynomial-time alogrithm
    - in other cases a heuristic algorithm is more than enough imo
        - but what should the heuristic be?
- how do we deal with waste if the required amount of the tiles has been met already?
    - probably an indicator for each input file on how many more could fit of that type
        - heavily complicates things...
        - would the output be of same height?
