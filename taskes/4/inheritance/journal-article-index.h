#ifndef JOURNAL_ARTICLE_INDEX_H
#define JOURNAL_ARTICLE_INDEX_H

#include <iostream>
#include <string>
#include "litindex.h"

namespace litindex
{
   class JournalArticleIndex: public LiteratureIndex
   {
   public:
      JournalArticleIndex(
         std::string in_journal_name, int in_volume, int in_number,
         int in_first_page, int in_last_page, int in_year, std::string in_pid
      );
      
      std::string get_journal_name() const { return this->journal_name; }
      int get_volume() const { return this->volume; }
      int get_number() const { return this->number; }
      int get_first_page() const { return this->first_page; }
      int get_last_page() const { return this->last_page; }
      int get_page() const { return this->page; } 
      
      void set_bibliographic_data(
         std::string in_journal_name, int in_volume, int in_number,
         int in_first_page, int in_last_page, int in_year, std::string in_pid
      );
      void set_page(int in_page);
      
      int next_page();
      void out(std::ostream* target) const;  // write to *target
      
   private:
      std::string journal_name = "";
      int volume = 0;
      int number = 0;
      int first_page = 0;  // where in the journal does the article begin?
      int last_page = 0;   // where does it end?
      
      int page = 0;  // what page within the article are we referring to?
   };
}

#endif
