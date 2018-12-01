#include <string>
#include <fstream>
#include <iostream>
#include <set>

#define WHITESPACE " \t"

using namespace std;

set<string> already;

void create_record(ostream &out, string domain) {
   // Domains with whitespace are invalid and cause errors
   if (string::npos != domain.find_first_of(WHITESPACE)) {
      return;
   }

   out <<
      "rr {"
      // "authrec = off; "
         "name = " << domain << ";"
      // "ns = localhost; "
      // "soa = localhost, root.localhost, 42, 86400, 900, 86400, 86400; "
      "}"
      << endl <<
      "rr {"
         "name = *." << domain << ";"
         "a = 127.0.0.1; "
      "}"
      << endl;
}

int doit(string infile, string outfile, int depth) {
   ifstream infile_fh(infile);
   ofstream outfile_fh(outfile);

   string s;
   size_t p;

   while (infile_fh.good()) {
      getline(infile_fh, s);

      p = s.find_first_of(WHITESPACE);
      if (p == string::npos) {
         continue;
      }

      p = s.find_first_not_of(WHITESPACE, p);
      if (p == string::npos) {
         continue;
      }

      string ip = s.substr(0, p - 1);
      string domain = s.substr(p);
      string domain2 = "eh.eh";

      p = string::npos;
      for (int i = depth; i > 0; --i) {
         p = domain.rfind('.', p - 1);

         /*
         if (p != string::npos) {
            domain2 = domain;
         }
         */
      }

      if (p != string::npos) {
         domain2 = domain.substr(p + 1);
      }

      if (! already.contains(domain2)) {
         already.insert(domain2);

         //cout << ip << ':' << domain << '=' << domain2 << endl;
         create_record(outfile_fh, domain2);
      }
   }

   return 0;
}

const char *prog;

void perr(const char *s) {
   cerr << prog << ": " << s << endl;
}

int main(int argc, char *argv[]) {
   prog = argv[0];

   if (argc != 3) {
      perr("2 args required");
      return 1;
   }

   const char *infile = argv[1];
   const char *outfile = argv[2];

   doit(infile, outfile, 2);
   return 0;
}
