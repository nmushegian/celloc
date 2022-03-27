// celloc2 -- ARC with no live dedupe
// simpler code for developing cursor API

typedef enum _tag {
  FREE, ATOM, CELL
} tag;

typedef int atom;

typedef struct _cell {
  int ltag;
  int rtag;
  int lval;
  int rval;
  int refs;
} cell;

#define CELLS 1000000

cell cells[CELLS];
int cellc = 0;
int free = 0;

int _dealloc(int cidx) {
  cell fcell = cells[cidx];
  fcell.ltag = FREE;
  fcell.lval = free;
  free = cidx;
  return free;
}

int upsert(int cidx, int side, int nidx) {
  cell pcell = cells[cidx];
  cell ncell = cells[nidx];
  int fidx;
  cell fcell;
  if (pcell.ltag == FREE) return -1;
  if (ncell.ltag == FREE) return -1;
  if (side == 0) {
    if (pcell.ltag == CELL) {
      fidx = pcell.lval;
      fcell = cells[fidx];
      fcell.refs--;
      if (fcell.refs == 0) {
        _dealloc(fidx);
      }
    } else {
      pcell.ltag = CELL;
    }
    pcell.lval = nidx;
  } else {
    if (pcell.rtag == CELL) {
      fidx = pcell.rval;
      fcell = cells[fidx];
      fcell.refs--;
      if (fcell.refs == 0) {
        _dealloc(fidx);
      }
    } else {
      pcell.rtag = CELL;
    }
    pcell.rval = nidx;
  }
  ncell.refs++;
  return 0;
}

int main() {
  return 1;
}
