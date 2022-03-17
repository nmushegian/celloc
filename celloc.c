// GPL3

typedef int atom;

typedef enum _side {
  L, R
} side;

typedef enum _quad {
  AA, AC, CA, CC // atom x cell
} quad;

typedef struct _ring {
  void* list; // whose list is this in   (cell/pair)
  void* item; // the other type of thing (cell/pair)
  struct _ring* prev; // or 'tail'
  struct _ring* next; // or 'head'
} ring;

typedef struct _cell {
  struct _pair* children;
  ring* references; // pair**
} cell;

typedef struct _pair {
  quad tag;
  union { atom LA; cell* LC; };
  union { atom RA; cell* RC; };
  ring* references; // cell**
} pair;

#define CELLS 1000000
int   cellc = 0;
cell  cells[CELLS];
cell* fcells = &cells[0];

#define PAIRS 1000000
int  pairc = 0;
pair  pairs[PAIRS];
pair* fpairs = &pairs[0];

#define RINGS 1000000
int  ringc = 0;
ring  rings[RINGS];
ring* frings = &rings[0];

cell* cursor;
cell* root;
cell* zoot; // null but actually well-formed linked cell [root, root]

cell* init() {
  cell* c0 = &cells[0];
  pair* p0 = &pairs[0];
  ring* r0 = &rings[0];
  ring* r1 = &rings[1];

  cellc = 1;
  ringc = 2;
  pairc = 1;

  c0->children = p0;
  c0->references = r1;

  p0->tag = AA;
  p0->LC = c0;
  p0->RC = c0;
  p0->references = r0;

  r0->list = c0;
  r0->item = p0;
  r0->prev = r0;
  r0->next = r0;

  r1->list = p0;
  r1->item = c0;
  r1->prev = r1;
  r1->next = r1;

  zoot = c0;
  root = zoot;
  cursor = root;
  return cursor;
}

void upsert(side s, cell* child) {
  //
}

void _start() {
}

int main() {
}
