`celloc` is a memory allocator with hard-real-time O(1) garbage collection **and deduplication**.
Memory will grow *only* if all cells have live references and there are *no* duplicate structures
in the entire expression. The data structure for the purposes of defining structural equality
is an S-expression of pointer-sized values (e.g, recursive lists of `u64`). The internal representation of this S-expression requires 3 levels of indirection, desribed below.


it was designed for S-expressions in the [term rewrite system minilang](https://github.com/nmushegian/minilang) but can be used more broadly

it is essentially a cell allocator with reference counting, with the following data structure used in place of numeric reference counts
- a *cell* points to *one child link* and *N parent links*. (The one child link is called 'children', that means the link contains the information about the two children. The link field in a cell is a reference to that pair, which is a distinct object in memory).
- a *link* points to *two neighbor cells* and *K parent cells* (The neighbor cells are the child cells of the parent cell. The parent cells are all references to this cell).

A link is content-addressed by the values of the neighbor cells' child links, which provides
the basis of deduplication: the parent cells are the ones that can be deduped. Cells that
have no parent links can be dealloced.

`celloc`  uses the following assumptions about expressions, which come from properties of term rewrite systems:
- cells have 2 items *[1]
- no circular references exist (an S-expression is a concrete tree; circular references require reference types) *[2]
- there is one root object (no 'co-circular' expressions, again, this is a nested list and not an expression with reference types) *[2]

[1] lists can be represented with cons, the runtime complexity increases as you would expect.
it might be possible to create 'raw list' (tree) and 'raw object' (trie) forms that reduce
this overhead from O(n) to O(log(n)) for random access, but it is not clear.
[2] you can *implement* reference types, which makes memory management the user's problem again. These are not the underlying pointers; you cannot dereference an atom to get anything, but you can use it to represent an index into a big list of atoms.
