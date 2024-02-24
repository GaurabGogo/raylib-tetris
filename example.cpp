// C++ Program to initialize
// vector of struct
// Using push_back()
#include <bits/stdc++.h>

using namespace std;

// Declaring a structure
struct Author
{
  string author_name;
  int article_count;
  int article_views;
};

int main()
{
  // Declaring the vector of structs
  struct Author A[] = {{"Geek1", 124, 65000},
                       {"Geek2", 156, 100000},
                       {"Geek3", 10, 200}};
  vector<Author> v;

  // Insertion of elements using push_back()
  for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
  {
    v.push_back(A[i]);
  }

  cout << "author_name"
       << " "
       << "article_count"
       << " "
       << "article_views" << endl;

  for (auto &a : v)
  {
    cout << a.author_name << "			 "
         << a.article_count << "		 "
         << a.article_views << endl;
  }

  return 0;
}
