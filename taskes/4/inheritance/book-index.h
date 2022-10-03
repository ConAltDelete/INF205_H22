/* Week 39, problem 3: Turn BookIndex into a subclass of LiteratureIndex */

#ifndef BOOK_INDEX_H
#define BOOK_INDEX_H

#include <cassert>
#include <iostream>
#include "litindex.h"

namespace litindex
{
   class BookIndex: public LiteratureIndex
   {
   public:
      BookIndex() {}
      BookIndex(int c, int s, int p);
      
      int get_chapter() const { return this->chapter; }
      int get_section() const { return this->section; }
      int get_page() const { return this->page; }
      
      void set_chapter(int c) { assert(c >= 0); this->chapter = c; }
      void set_section(int s) { assert(s >= 0); this->section = s; }
      void set_page(int p) { assert(p >= 0); this->page = p; }
      
      int next_chapter();  /* goes to next chapter, returns new chapter number */
      int next_section();  /* goes to next section, returns new section number */
      int next_page();     /* goes to next page, returns new page number */
   
      void out(std::ostream* target) const;  // write to *target
   
   private:
      int chapter = 1;
      int section = 1;
      int page = 1;
   };
}

#endif
