// GPL3

typedef int atom;

typedef enum _side {
  L, R
} side;

typedef enum _quad {
  AA, AC, CA, CC // atom x cell
} quad;

typedef struct _ring {
  struct _ring* next;
  struct _ring* prev;
  union { struct _cell* clist; struct _tube* tlist; };
  union { struct _cell* citem; struct _tube* titem; };
} ring;

typedef struct _cell {
  union { ring* refs; ring* next; };
  struct _tube* axis;
} cell;

typedef struct _tube {
  union { ring* refs; ring* next; }; // 'next'
  quad  tag;
  union { atom LA; cell* LC; };
  union { atom RA; cell* RC; };
} tube;

#define CELLS 1000000
int   cellc = 0;
cell  cells[CELLS];
cell* fcells = &cells[0];

#define TUBES 1000000
int   tubec = 0;
tube  tubes[TUBES];
tube* ftubes = &tubes[0];

#define RINGS 1000000
int   ringc = 0;
ring  rings[RINGS];
ring* frings = &rings[0];

cell* cursor;
cell* root;
cell* zoot; // null but an actual linked cell [root, root]

cell* init() {
  cell* c0 = &cells[0];
  tube* t0 = &tubes[0];
  ring* r0 = &rings[0];
  ring* r1 = &rings[1];

  cellc = 1;
  tubec = 1;
  ringc = 2;

  c0->axis = t0;
  c0->refs = r1;

  t0->tag = AA;
  t0->LC = c0;
  t0->RC = c0;
  t0->refs = r0;

  r0->clist = c0;
  r0->titem = t0;
  r0->prev = r0;
  r0->next = r0;

  r1->tlist = t0;
  r1->citem = c0;
  r1->prev = r1;
  r1->next = r1;

  zoot = c0;
  root = zoot;
  cursor = root;

  return cursor;
}

ring* grab_ring() {
}

void upsert(side s, cell* child) {
}

void _start() {
}

int main() {
}
