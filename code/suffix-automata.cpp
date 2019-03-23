const int maxn = 2 e5 + 42; // Maximum amount of states
map < char , int > to [ maxn ]; // Transitions
int link [ maxn ]; // Suffix links
int len [ maxn ]; // Lengthes of largest strings in states
int last = 0; // State corresponding to the whole string
int sz = 1; // Current amount of states
void add_letter ( char c ) { // Adding character to the end
    int p = last ; // State of string s
    last = sz ++; // Create state for string sc
    len [ last ] = len [ p ] + 1;
    for (; to [ p ][ c ] == 0; p = link [ p ]) // (1)
        to [ p ][ c ] = last ; // Jumps which add new suffixes
    if ( to [ p ][ c ] == last ) { // This is the first occurrence of c if we are here
        link [ last ] = 0;
        return ;
    }
    int q = to [ p ][ c ];
    if ( len [ q ] == len [ p ] + 1) {
        link [ last ] = q ;
        return ;
    }
    // We split off cl from q here
    int cl = sz ++;
    to [ cl ] = to [ q ]; // (2)
    link [ cl ] = link [ q ];
    len [ cl ] = len [ p ] + 1;
    link [ last ] = link [ q ] = cl ;
    for (; to [ p ][ c ] == q ; p = link [ p ]) // (3)
        to [ p ][ c ] = cl ; // Redirect transitions where needed
}
