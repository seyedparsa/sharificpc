#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
int main()
{
	ordered_set s;
	s.insert(1);
	s.insert(2);
	s.erase(3);
	cout << *s.find_by_order(0) << "\n";
	cout << s.order_of_key(2) << "\n";
	return 0;
}
