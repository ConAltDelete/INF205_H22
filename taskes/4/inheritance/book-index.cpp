/* Week 39, problem 3: Turn BookIndex into a subclass of LiteratureIndex */

#include "book-index.h"
#include <iostream>

using namespace litindex;

BookIndex::BookIndex(int c, int s, int p)
{
   this->set_chapter(c);
   this->set_section(s);
   this->set_page(p);
}

/*
 * goes to next chapter, returns new chapter number
 * this implementation also automatically goes to the next page
 */
int BookIndex::next_chapter()
{
   chapter++;
   section = 1;
   page++;
   return chapter;
}

/*
 * goes to next section, returns new section number
 */
int BookIndex::next_section()
{
   section++;
   return section;
}

/*
 * goes to next page, returns new page number
 */
int BookIndex::next_page()
{
   page++;
   return page;
}

/*
 * write to *target
 */
void BookIndex::out(std::ostream* target) const
{
   *target << "Section " << this->chapter << "."
           << this->section << ", p. " << this->page << "\n";
}
