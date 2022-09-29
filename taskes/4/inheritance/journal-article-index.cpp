#include <cassert>
#include "journal-article-index.h"

using namespace litindex;

JournalArticleIndex::JournalArticleIndex(
   std::string in_journal_name, int in_volume, int in_number,
   int in_first_page, int in_last_page, int in_year, std::string in_pid
) {
   this->set_bibliographic_data(in_journal_name, in_volume, in_number,
                                in_first_page, in_last_page, in_year, in_pid);
   this->page = this->first_page;
}

void JournalArticleIndex::set_bibliographic_data(
   std::string in_journal_name, int in_volume, int in_number,
   int in_first_page, int in_last_page, int in_year, std::string in_pid
) {
   this->journal_name = in_journal_name;
   
   assert(in_volume >= 0);
   this->volume = in_volume;
   
   assert(in_number >= 0);
   this->number = in_number;
   
   assert(in_first_page >= 0);
   this->first_page = in_first_page;
   
   assert(in_last_page >= in_first_page);
   this->last_page = in_last_page;
   
   this->set_year(in_year);
   this->set_persistent_identifier(in_pid);
}

void JournalArticleIndex::set_page(int in_page)
{
   assert((in_page >= this->first_page) && (this->last_page >= in_page));
   this->page = in_page;
}
      
int JournalArticleIndex::next_page()
{
   if(this->page < this->last_page) this->page++;
   return this->page;
}

void JournalArticleIndex::out(std::ostream* target) const
{
   *target << "p. " << this-> page << " in " << this->journal_name;
   if(this->volume)
   {
      *target << " " << this->volume;
      if(this->number) *target << "(" << this->number << ")";
   }
   if(this->first_page)
   {
      *target << ": " << first_page;
      if(this->last_page) *target << "-" << last_page;
   }
   if(this->get_persistent_identifier() != "")
      *target << ", " << this->get_persistent_identifier();
   if(this->get_year())
      *target << " (" << this->get_year() << ")";
   *target << "\n";
}
