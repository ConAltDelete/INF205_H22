/* Week 39, problem 3: Turn BookIndex into a subclass of LiteratureIndex */

#include "book-index.h"
#include "journal-article-index.h"
#include <iostream>

namespace
{
   void next_page_and_status(litindex::LiteratureIndex* li)
   {
      std::cout << "next_page_and_status(litindex::LiteratureIndex* li)\n";

      li->next_page();      // go to next page
      li->out(&std::cout);  // print status
   }

   void start_chapter(litindex::BookIndex* b)
   {
      std::cout << "start_chapter(litindex::BookIndex* b)\n";

      b->next_chapter();
      b->out(&std::cout);  // print status
   }
}

int main()
{
   /*
    * declare and initialize a JournalArticleIndex object
    */
   std::cout << "JournalArticleIndex example:\n";
   litindex::JournalArticleIndex jenul_et_al_2021(
      "IEEE_Access", 9, 0, 152333, 152346, 2021, "doi:10.1109/access.2021.3126429"
   );
   jenul_et_al_2021.next_page();      // go to next page
   jenul_et_al_2021.out(&std::cout);  // print status
   
   std::cout << "\nBookIndex example:\n";
   litindex::BookIndex idx(1, 11, 24);
   idx.out(&std::cout);  // print status
   start_chapter(&idx);
   
   /*
    * once BookIndex is a subclass of LiteratureIndex,
    * the following should work:
    * 
   idx.set_year(2022);
   idx.set_persistent_identifier("ISBN 978-1-1196-0096-1");
   next_page_and_status(&idx);
    *
    */
}
