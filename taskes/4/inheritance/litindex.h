/* Week 39, problem 3: Turn BookIndex into a subclass of LiteratureIndex */

#ifndef LITINDEX_H
#define LITINDEX_H

#include <iostream>
#include <string>

namespace litindex
{
   class LiteratureIndex
   {
   public:
      LiteratureIndex() {}
      LiteratureIndex(std::string in_pid) { this->pid = in_pid; }
      
      int get_year() const { return this->year; }
      std::string get_persistent_identifier() const { return this->pid; }
      
      void set_year(int in_year) { this->year = in_year; }
      void set_persistent_identifier(std::string in_pid) { this->pid = in_pid; }
      
      virtual int next_page() { return 0; }
      
      // write to *target
      virtual void out(std::ostream* target) const {
         *target << this->pid << " (" << this->year << ")\n";
      }
      
   private:
      int year = 0;
      std::string pid = "";  // persistent identifier of the literature item, e.g., DOI or ISBN
   };
}

#endif
